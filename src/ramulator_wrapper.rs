use crate::bindings::*;
use std::ffi::CString;
use std::ptr;

// Define the wrapper
pub struct RamulatorWrapperRs {
    // Fields and methods for your wrapper
    wrapper: *mut RamulatorWrapper,
}

impl RamulatorWrapperRs {
    pub fn new(config_path: &str) -> Self {
        let config_path = CString::new(config_path).unwrap();
        Self {
            wrapper: unsafe { create_ramulator_wrapper(config_path.as_ptr() as *const i8) },
        }
    }

    pub fn simulate_request(&self, addr: u64) -> u64 {
        unsafe { get_latency_for_request(self.wrapper, addr) }
    }

    pub fn print_stats(&self) {
        unsafe { print_stats(self.wrapper) }
    }
}
