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
- cargo.lock
- cargo.toml
- Makefile
- test_call_ramulator.c
- wrapper.hpp

## Requirements
- **C++17 compatible compiler** (e.g., g++ ≥ 8)
- [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) installed (for YAML config parsing)
- [`spdlog`](https://github.com/gabime/spdlog) headers available (used internally by Ramulator2)
- Ramulator2 source code downloaded (not a precompiled binary)

## Run Simulation
To run Ramulator, you need to call test_call_ramulator.c, which invokes call_ramulator.cpp.

`./test_call_ramulator`

## Example Output
You should expect DRAM statistics from the frontend and memory system. Here are some example numbers:
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
