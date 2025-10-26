```
# HPX_Documentation

This repository contains my experiments and notes from learning **HPX**, a modern C++ runtime system for parallel and distributed applications.  
The focus is on understanding HPX’s **asynchronous execution model**, **task-based parallelism**, and **standard-conforming APIs** through hands-on code examples located in the `src/` folder.

---

## Purpose

The main goal of this repository was to document my own learning process while studying HPX.  
By writing and analyzing small programs, I built an understanding of:

- how HPX manages lightweight user-level threads  
- how futures and continuations enable asynchronous programming  
- how parallel execution policies generalize C++17 algorithms  
- and how CMake integrates HPX as a modern C++ library

---

## Repository Structure

```

HPX_Documentation/
├── src/               # Example source files used for learning HPX
│   ├── async_examples.cpp
│   ├── futures_and_then.cpp
│   ├── parallel_algorithms.cpp
│   ├── three_vector_problem.cpp
│   └── ...
├── CMakeLists.txt     # HPX build configuration
├── rebuild.sh         # Convenience script for clean rebuilds
└── .gitignore

````

Each file in `src/` represents a self-contained experiment illustrating one HPX concept.  
For example, the *three vector problem* demonstrates how tasks can be expressed asynchronously and synchronized via futures rather than blocking operations.

---

## What I Learned

Through these examples, I gained practical understanding of HPX’s key abstractions:

### 1. Futures and Continuations
- Using `hpx::future` and `.then()` for non-blocking computation chains.  
- Understanding how HPX schedules these continuations using lightweight threads.  

### 2. Task-Based Parallelism
- Launching asynchronous tasks via `hpx::async` and composing them with data dependencies.  
- Learning how task granularity and scheduling affect performance.

### 3. Parallel Algorithms
- Rewriting standard loops using HPX equivalents like  
  `hpx::for_each`, `hpx::transform`, and `hpx::reduce`.  
- Comparing these with their C++17 counterparts to see HPX’s asynchronous execution benefits.

### 4. Execution and Synchronization
- How HPX’s thread pools and executors differ from OS threads.  
- Using `hpx::wait_all` and `hpx::when_all` to coordinate multiple futures.

### 5. Build System Integration
- Setting up HPX via CMake with  
  ```cmake
  find_package(HPX REQUIRED)
  add_executable(example src/example.cpp)
  target_link_libraries(example HPX::hpx)
````

* Using `rebuild.sh` to clean and rebuild efficiently during iterative testing.

---

## Environment

* **Language:** C++20
* **Runtime:** HPX (latest release from [STEllAR-GROUP/hpx](https://github.com/STEllAR-GROUP/hpx))
* **Build system:** CMake
* **Compilers tested:** GCC 12, Clang 15
* **Platforms:** Linux and macOS

---

## Notes

This repository was **not** created for benchmarking or production use — only for **learning HPX concepts through experimentation**.
Each program inside `src/` works independently and demonstrates a specific feature or API surface of HPX.

---
**Author:** Matko Petričić
**Purpose:** Self-study of HPX and asynchronous parallelism in modern C++.

