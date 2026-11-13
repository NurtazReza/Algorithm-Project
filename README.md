# 🚚 Delivery Logistics Optimization

An algorithm-based **Delivery Logistics Optimization System** developed as part of the CSE246: Algorithms course at East West University.

This project addresses the package selection problem faced by delivery companies when loading vans with limited weight and volume capacities. It implements and compares multiple optimization algorithms to identify suitable package combinations while considering factors such as package value, weight, volume, delivery deadlines, and delivery zones.

## 📌 Project Overview

Delivery companies must select packages efficiently while satisfying multiple constraints. Choosing an unsuitable combination can result in wasted capacity, lower total package value, and inefficient delivery operations.

This project explores different algorithmic approaches to solve the package loading problem and evaluates their performance across various datasets.

## ✨ Key Features

- **Multiple Optimization Algorithms:** Implements and compares nine different package selection algorithms.
- **Multiple Constraints:** Considers package weight, volume, value, deadlines, and delivery zones.
- **Five Synthetic Datasets:** Tests algorithm performance under different scenarios.
- **Performance Evaluation:** Measures total value, weight utilization, volume utilization, selected package count, and execution time.
- **Algorithm Comparison:** Provides comparative results to identify the strengths and limitations of different approaches.
- **Interactive Menu:** Allows users to select datasets and run individual algorithms or comparisons.

## 🧠 Algorithms Implemented

The project implements the following nine algorithms:

| No. | Algorithm | Approach |
|---:|---|---|
| 1 | Brute Force | Exhaustive Search |
| 2 | 0/1 Knapsack | Dynamic Programming |
| 3 | 2D Knapsack | Dynamic Programming |
| 4 | Fractional Knapsack | Greedy |
| 5 | Greedy by Value | Greedy |
| 6 | Greedy by Weight | Greedy |
| 7 | Greedy by Value/Weight Ratio | Greedy |
| 8 | Greedy by Deadline | Greedy |
| 9 | Greedy by Zone | Greedy |

## 📊 Datasets

Five synthetic datasets were constructed to evaluate the algorithms under different conditions.

| Dataset | Purpose |
|---|---|
| Small Dataset | Tests algorithm functionality with a small number of packages |
| Medium Dataset | Evaluates performance with a moderate number of packages |
| Large Dataset | Examines scalability with larger inputs |
| 2D-Friendly Dataset | Tests scenarios involving weight and volume constraints |
| Adversarial Dataset | Examines algorithm behavior under challenging conditions |

Each package contains the following attributes:

- Package ID
- Weight
- Volume
- Value (Priority Score)
- Delivery Deadline
- Delivery Zone
- Coordinates

## ⚙️ Evaluation Metrics

The algorithms are evaluated using the following metrics:

- Total value of selected packages
- Weight utilization
- Volume utilization
- Number of selected packages
- Execution time
- Delivery deadline satisfaction
- Real-world practicality

The same datasets are used across the algorithms to maintain a fair comparison.

## 📈 Results & Findings

The comparison reveals important trade-offs between optimality and execution speed.

- **Brute Force:** Guarantees an optimal solution but becomes impractical for large datasets due to exponential time complexity.
- **0/1 Knapsack DP:** Provides optimal results under the weight constraint but does not account for volume.
- **2D Knapsack DP:** Considers both weight and volume constraints and produces optimal solutions for the modeled problem.
- **Fractional Knapsack:** Provides a fast upper-bound solution by allowing partial package selection.
- **Greedy Algorithms:** Execute quickly but may produce suboptimal results depending on the selection strategy.

According to the project's evaluation, 0/1 Knapsack DP offers a favorable trade-off between speed and optimality, while Greedy by Value/Weight Ratio provides a fast approximation.

## ⏱️ Time & Space Complexity

| Algorithm / Approach | Time Complexity |
|---|---|
| Brute Force | O(2ⁿ) |
| 0/1 Knapsack DP | O(nW) |
| 2D Knapsack DP | O(nWV) |
| Greedy Sorting / Filtering | O(n log n) |

Where:

- `n` = Number of packages
- `W` = Weight capacity
- `V` = Volume capacity

*Complexity depends on the algorithm and the constraints considered.*

## 🛠️ Implementation Details

The implementation includes:

- Dataset loading functions for five different datasets.
- Algorithm-specific functions for package selection.
- Utility functions for metric calculation and result display.
- Input validation and formatted output.
- A menu-driven interface for running algorithms and comparisons.

## ⚠️ Limitations

- Brute Force is not scalable for large datasets because of its exponential time complexity.
- 0/1 Knapsack DP may ignore volume constraints.
- Greedy approaches can produce suboptimal solutions.
- The current system does not optimize delivery routes.
- Extremely large package values may not be handled effectively.

## 🚀 Future Improvements

- Integrate delivery route optimization with package selection.
- Implement distributed multi-van coordination.
- Introduce real-time adaptive algorithms for dynamic package arrivals.
- Apply machine learning for predictive prioritization and package value estimation.
- Improve scalability for larger and more complex datasets.

---

*Developed as an academic project for the CSE246: Algorithms course, Fall 2025.*
