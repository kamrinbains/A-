# A\* Algorithm Implementation

This repository contains a C++ implementation of the A\* pathfinding algorithm. The algorithm efficiently finds the shortest path between two nodes in a graph using heuristic functions.

---

## 📦 Compilation

To compile the source code, run:

```bash
g++ -std=c++17 -o a.out astar.cpp
```

This will produce an executable named `a.out`.

---

## 🚀 Running the Program and Tests

1. **Build the executable** (if you haven’t already):

   ```bash
   g++ -std=c++17 -o a.out astar.cpp
   ```

2. **Make the test runner executable** and run it:

   ```bash
   chmod +x run_tests.sh
   ./run_tests.sh
   ```

   Each test reads input from a file and compares the output against the expected optimal path.

---

## 🧪 Test Cases

Seven test cases are provided to verify correctness:

1. **Basic Linear Graph**

   ```
   0 --- 1 --- 2 --- 3 --- 4
   Start                Goal
   ```

2. **Multiple Paths**

   ```
       3 --- 4
      /       \
     0 --- 1 -- 2
           \   /
            \ /
             5
   ```

3. **Disconnected Graph**

   ```
   0 --- 1    2    3 --- 4
   Start                Goal
   ```

4. **Grid Graph (Manhattan)**

   ```
   6 --- 7 --- 8
   |     |     |
   3 --- 4 --- 5
   |     |     |
   0 --- 1 --- 2
   ```

5. **Varying Edge Weights**

   ```
           /----- 10 ------\
          /                 \
         0 ----- 5 -----> 2 -- 3 -- 4
          \                      /
           \----- 20 ----------/
   ```

6. **Directed Graph**

   ```
   0 --- 1    2 --- 3
   Start            Goal
   ```

7. **Start Equals Goal**

   ```
   0 --- 1 --- 2 --- 3 --- 4
           Start/Goal
   ```

---

## ⚙️ Important Notes

* Nodes are **0-indexed** (IDs range from 0 to `numNodes - 1`).
* The default graph is **directed**. To treat it as undirected, uncomment this line in `astar.cpp`:

  ```cpp
  // graph[v].push_back({u, cost});
  ```

---

## 📋 Input Format

```
numNodes
node1_id node1_x node1_y
node2_id node2_x node2_y
...
numEdges
from1_id to1_id weight1
from2_id to2_id weight2
...
startNodeId
goalNodeId
heuristicChoice (1 = Euclidean, 2 = Manhattan)
```

* **numNodes**: Number of nodes in the graph.
* **node*\_id*** and **node*\_x***/**node*\_y***: Unique ID and 2D coordinates for each node.
* **numEdges**: Number of directed edges.
* **from\_id**, **to\_id**, **weight**: Defines an edge and its traversal cost.
* **startNodeId** / **goalNodeId**: IDs for the start and goal nodes.
* **heuristicChoice**: Selects the heuristic:

  * `1` = Euclidean distance
  * `2` = Manhattan distance

---
