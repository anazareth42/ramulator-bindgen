## Ramulator
This is the Rust implementation of CMU's ['Ramulator2'](https://github.com/CMU-SAFARI/ramulator2/tree/main/src) intended for HLS development. As the Ramulator2 repository is written in C/C++, this project uses Bindgen to generate Rust FFI bidings to the libraries.

## Requirements
- **C++17 compatible compiler** (e.g., g++ ≥ 8)
- [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) installed (for YAML config parsing)
- [`spdlog`](https://github.com/gabime/spdlog) headers available (used internally by Ramulator2)
- Ramulator2 source code downloaded (not a precompiled binary)
