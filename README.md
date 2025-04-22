# Introduction
This is the Rust implementation of CMU's [Ramulator2](https://github.com/CMU-SAFARI/ramulator2/tree/main/src) intended for HLS development. As the original repository is written in C/C++, this project uses Bindgen to generate Rust FFI bidings to the necessary libraries.

## Ramulator

## Structure
These are the files that are important to the functionality of this project:
- src
  - bindings.rs
  - lib.rs
  - ramulator_wrapper.rs
- build.rs
- call_ramulator.cpp
- test_call_ramulator.c
- wrapper.hpp

# Requirements
- **C++17 compatible compiler** (e.g., g++ ≥ 8)
- [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) installed (for YAML config parsing)
- [`spdlog`](https://github.com/gabime/spdlog) headers available (used internally by Ramulator2)
- Ramulator2 source code downloaded (not a precompiled binary)

# Run Simulation
To run Ramulator, you need to call test_call_ramulator.c, which invokes call_ramulator.cpp.

`./test_call_ramulator`

# Example Output
You should expect DRAM statistics from the frontend and memory system. Here are some example numbers:
