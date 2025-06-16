# Tetravex Solver Algorithms

**Tetravex** is an edge-matching puzzle where each tile has four numbered edges. The goal is to arrange all tiles on an *n × n* grid such that adjacent tiles have matching numbers on shared edges.

This puzzle caught my attention due to its deceptively simple rules and computationally complex solution space. It's an excellent problem to demonstrate core data structure and algorithmic skills—particularly in solving constraint satisfaction problems efficiently.

## Simulated Annealing Implementations

My initial solver was implemented in three languages to explore performance trade-offs and system-level differences:

* **Python (high-level)** – for rapid prototyping and testing ideas
* **C++ (mid-level)** – for performance with modern language features
* **C (low-level)** – for maximum speed and control

I used a **Simulated Annealing (SA)** approach in all three implementations. The C version proved the fastest, solving 6×6 boards in under 0.1 seconds. However, performance dropped sharply for 7×7 boards due to the exponential search space.

## Current Focus

To tackle larger board sizes (up to 14×14), I'm currently exploring more efficient algorithms and solvers:

* **Dancing Links (DLX)** – Knuth's Algorithm X for solving exact cover problems
* **MiniSAT** – A modern SAT solver that can be adapted to this puzzle with proper encoding

These implementations will be written in **C++**, leveraging:

* Efficient standard data structures (e.g., maps, vectors)
* Asynchronous programming and multithreading for parallel search
* A balance between low-level performance and high-level abstraction

## Goals

* Solve puzzles up to **14×14** in under a few seconds
* Demonstrate mastery of:

  * Algorithmic optimization
  * Scalability under combinatorial explosion
  * Practical application of advanced DSA techniques
* Evaluate and compare performance across approaches

## Why This Matters

This project is part of my broader portfolio to showcase:

* Real-world application of advanced algorithms
* Use of performance profiling and optimization
* Cross-language implementation for performance benchmarking
* Research and adaptability in exploring multiple solving strategies

It's a strong representation of my problem-solving approach and depth in both software engineering and theoretical computer science.
