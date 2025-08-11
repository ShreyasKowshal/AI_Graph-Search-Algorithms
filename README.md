# Graph Search AI Algorithms

This repository contains implementations of **15 different graph search algorithms** used in Artificial Intelligence and pathfinding problems. Each algorithm is implemented in C++ with a focus on demonstrating key AI search strategies, from uninformed brute force to heuristic and informed search.


---

## Algorithms Included

1. **British Museum Search (Brute Force Search)**  
   Explores the entire search space by brute force without any heuristic guidance. It systematically checks every possible option to find the goal. This method guarantees a solution if one exists but is often computationally expensive.

2. **Depth-First Search (DFS)**  
   Explores as far down a branch as possible before backtracking. DFS is memory-efficient but may get stuck exploring deep paths and does not guarantee the shortest path.

3. **Breadth-First Search (BFS)**  
   Explores nodes level-by-level, expanding all neighbors at the current depth before moving deeper. BFS finds the shortest path in unweighted graphs and guarantees the shortest solution if all edges have equal cost.

4. **DFS + BFS Hybrid**  
   Combines depth-first exploration with breadth-first search to balance deep search with systematic coverage, aiming to improve search efficiency and completeness.

5. **DFS with History**  
   An enhanced DFS that keeps track of visited nodes to avoid cycles and repeated state expansions, improving efficiency in cyclic or large graphs.

6. **BFS with History**  
   Similar to BFS but tracks visited states to prevent redundant expansions, ensuring the algorithm does not revisit nodes and improving performance.

7. **Hill Climbing Search**  
   A heuristic-based local search that moves iteratively towards a better neighboring state. It is simple and fast but can get stuck in local maxima or plateaus.

8. **Beam Search**  
   A heuristic search that expands only a fixed number of best nodes (beam width) at each level, trading completeness for speed and memory efficiency.

9. **Hill Climbing with History**  
   Hill Climbing augmented with memory of previously visited states to avoid revisiting and cycling, helping to escape local traps.

10. **Beam Search with History**  
    Combines beam search with history tracking to avoid repeated states, improving robustness and search quality.

11. **Oracle Search**  
    An idealized search that assumes perfect knowledge of the solution path or heuristic, used for benchmarking other algorithms.

12. **Branch and Bound**  
    A systematic search method that prunes paths exceeding the best known cost, efficiently finding optimal solutions in weighted graphs.

13. **Branch and Bound with Cost and Estimated Heuristics**  
    Extends branch and bound by integrating heuristic estimates to guide pruning, improving search speed while maintaining optimality.

14. **Branch and Bound + Cost + History**  
    Further improves branch and bound by tracking visited states and costs to avoid repeated work and cycles, enhancing efficiency and optimality.

15. **A Star**  
    Combines uniform-cost search and heuristics to efficiently find the lowest-cost path. A* guarantees optimality when the heuristic is admissible and consistent.

---

## Usage

1. Clone the repository:  
   ```bash
   git clone https://github.com/ShreyasKowshal/AI_Graph-Search-Algorithms.git
   cd AI_Graph-Search-Algorithms
