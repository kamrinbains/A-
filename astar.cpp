// A* Search Algorithm Implementation in C++

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>
#include <algorithm>
#include <cmath>

// Edge structure: represents a directed edge to 'to' with weight 'cost'
struct Edge {
  int to;
  double cost;
};

// Reconstructs path by walking back through cameFrom
static std::vector<int> reconstructPath(const std::vector<int>& cameFrom, int current) {
  std::vector<int> path;
  for (int at = current; at != -1; at = cameFrom[at]) {
    path.push_back(at);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<int> AStar(int start, int goal, const std::vector<std::vector<Edge>>& graph, const std::function<double(int,int)>& heuristic) {
  int n = graph.size();
  std::vector<double> gScore(n, std::numeric_limits<double>::infinity());
  std::vector<double> fScore(n, std::numeric_limits<double>::infinity());
  std::vector<int> cameFrom(n, -1);
  std::vector<bool> closedSet(n, false);

  gScore[start] = 0.0;
  fScore[start] = heuristic(start, goal);

  using PQElement = std::pair<double,int>;
  std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> openSet;
  openSet.emplace(fScore[start], start);

  while (!openSet.empty()) {
    auto [currentF, current] = openSet.top();
    openSet.pop();

    if (closedSet[current]) 
      continue;
    if (current == goal)
      return reconstructPath(cameFrom, goal);

    closedSet[current] = true;

    for (const auto& edge : graph[current]) {
      int neighbor = edge.to;
      if (closedSet[neighbor]) 
        continue;

      double tentativeG = gScore[current] + edge.cost;
      if (tentativeG < gScore[neighbor]) {
        cameFrom[neighbor] = current;
        gScore[neighbor] = tentativeG;
        fScore[neighbor] = tentativeG + heuristic(neighbor, goal);
        openSet.emplace(fScore[neighbor], neighbor);
      }
    }
  }

  return {};
}

int main() {
  int n;
  std::cin >> n;
  // Store node coordinates by id (assumes ids in [0, n-1])
  std::vector<std::pair<double,double>> coords(n);
  for (int i = 0; i < n; ++i) {
    int id;
    double x, y;
    std::cin >> id >> x >> y;
    coords[id] = {x, y};
  }

  int m;
  std::cin >> m;
  std::vector<std::vector<Edge>> graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    double cost;
    std::cin >> u >> v >> cost;
    graph[u].push_back({v, cost});
    // For undirected graphs, uncomment:
    // graph[v].push_back({u, cost});
  }

  int start, goal;
  std::cin >> start >> goal;

  int choice;
  std::cin >> choice;

  // Define heuristic functions
  auto euclidean = [&](int u, int v) {
    double dx = coords[u].first - coords[v].first;
    double dy = coords[u].second - coords[v].second;
    return std::sqrt(dx*dx + dy*dy);
  };

  auto manhattan = [&](int u, int v) {
    return std::abs(coords[u].first - coords[v].first) + std::abs(coords[u].second - coords[v].second);
  };

  // Select heuristic based on choice
  std::function<double(int,int)> heuristic;
  if (choice == 1) {
    heuristic = euclidean;
  } 
  else if (choice == 2) {
    heuristic = manhattan;
  } 
  else {
    std::cerr << "Invalid heuristic choice. Using zero heuristic." << std::endl;
    heuristic = [](int, int)
    { return 0.0; };
  }

  // Run A* search
  std::vector<int> path = AStar(start, goal, graph, heuristic);

  if (path.empty()) {
    std::cout << "No path found from " << start << " to " << goal << std::endl;
  } 
  else {
    std::cout << "Optimal Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
      std::cout << path[i];
      if (i + 1 < path.size()) 
        std::cout << " -> ";
    }
    std::cout << std::endl;
  }

  return 0;
}

