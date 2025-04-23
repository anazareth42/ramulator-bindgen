# Ramulator Wrapper
This project implements the C++ wrapper around CMU's [Ramulator2](https://github.com/CMU-SAFARI/ramulator2/tree/main/src) intended for high-level synthesis development. The wrapper displays the statistics for both the frontend and memory system of Ramulator. The wrapper can be accessed from both C and Rust through bindgen which generates FFI bindings. The C++ interface (`call_ramulator.cpp`) simulates the frontend and memory system setup through YAML configuration. This provides access to internal simulation statistics such as instruction counts and DRAM throughput. The hybrid C++/Rust architecture allows for intergration within HLS simulation tool flows which promotes greater accuracy of memory modeling and timing.

## Ramulator 2.0
Ramulator 2.0 is a cycle-accurate DRAM simulator developed by researchers from Carnegie Mellon University. It enables rapid and agile implementation of design changes within the memory controller. This tool is widely used by computer architecture researchers for modeling memory performance, validating timing parameters, and evaluating interactions between controllers and memory systems. 

Ramulator can support the following DRAM standards: DDR3, DDR4, LPDDR4, LPDDR5, GDDR5, HBM2, HBM3, etc. Developers can customize these standards through YAML config inputs. Its C++ API allows for bindings with external simulators and wrappers.

## Structure
These are the files that are important to the functionality of this project:
- **src**
  - **bindings.rs** - Rust bindings created through bindgen
  - **lib.rs** - Rust crate entry point 
  - **ramulator_wrapper.rs** - Rust interface that creates an instance of `call_ramulator.cpp` through FFI bindings
- **build.rs** - Rust script that implements bindgen and configures the C++ build
- **call_ramulator.cpp** - Main C++ file that initializes Ramulator2. Contains methods that simulate frontend and memory system
- **cargo.lock** - Auto-generated lock file that specifies exact Rust version used
- **cargo.toml** - Rust package manifest that defines dependencies
- **Makefile** - Manual build script for C/C++ compliation
- **test_call_ramulator.c** - C test file that verifies the functionality of `call_ramulator.cpp`
- **wrapper.hpp** - header file with necessary .c files from Ramulator2

## Requirements
- **C++17 compatible compiler** (e.g., g++ ≥ 8)
- [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) installed (for YAML config parsing)
- [`spdlog`](https://github.com/gabime/spdlog) headers available (used internally by Ramulator2)
- Ramulator2 source code downloaded (not a precompiled binary)

## Run Simulation
To build this project, we need to generate the FFI bindings from bindgen. Type the following command in the terminal:

`cargo build`

This should compile the C++ code in addition to creating the Rust project. To test the output of `call_ramulator.cpp`, you need to call test_call_ramulator.c, which is a standalone C test harness:

`./test_call_ramulator`

## Example Output
You should expect DRAM statistics from the frontend and memory system. Here are the latency results when address 0x12345678 is provided:
```Loaded configuration from file.
Created frontend instance.
Created memory system instance.
Sent a memory request.

--- Frontend Statistics ---
Frontend:
  impl: SimpleO3
  memory_access_cycles_recorded_core_0: 0
  llc_mshr_unavailable: 0
  llc_read_access: 34
  llc_eviction: 0
  llc_read_misses: 34
  llc_write_misses: 8
  cycles_recorded_core_0: 0
  num_expected_insts: 500000
  llc_write_access: 8
  Translation:
    impl: RandomTranslation



--- Memory System Statistics ---
MemorySystem:
  impl: GenericDRAM
  total_num_other_requests: 0
  total_num_write_requests: 0
  memory_system_cycles: 37
  total_num_read_requests: 7
  DRAM:
    impl: DDR4
  AddrMapper:
    impl: RoBaRaCoCh


  Controller:
    impl: Generic
    id: Channel 0
    priority_queue_len_avg_0: 0
    queue_len_avg_0: 1.72972977
    priority_queue_len_0: 0
    write_queue_len_0: 0
    read_queue_len_0: 64
    read_row_conflicts_0: 0
    write_queue_len_avg_0: 0
    write_row_conflicts_0: 0
    read_row_misses_0: 5
    read_row_hits_0: 0
    num_read_reqs_0: 7
    avg_read_latency_0: 5.28571415
    row_conflicts_0: 0
    row_misses_0: 5
    row_hits_0: 0
    write_row_misses_0: 0
    write_row_hits_0: 0
    num_other_reqs_0: 0
    read_row_hits_core_0: 0
    read_row_misses_core_0: 4
    read_queue_len_avg_0: 1.72972977
    read_row_conflicts_core_0: 0
    queue_len_0: 64
    read_latency_0: 37
    num_write_reqs_0: 0
    Scheduler:
      impl: FRFCFS
    RefreshManager:
      impl: AllBank


    RowPolicy:
      impl: ClosedRowPolicy
      num_close_reqs: 0
```
