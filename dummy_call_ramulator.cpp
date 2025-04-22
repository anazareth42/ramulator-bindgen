#include "wrapper.hpp"
#include "call_ramulator.h"
#include <iostream>

using namespace std;

extern "C" {

struct RamulatorWrapper {
    RamulatorWrapper(const char *config_file) {
        cout << "TODO: initialize" << endl;
    }
};

RamulatorWrapper *create_ramulator_wrapper(const char *config_file) {
    return new RamulatorWrapper(config_file);
}

unsigned long long get_latency_for_request(RamulatorWrapper *system, unsigned long long addr) {
    cout << "TODO: send a memory request" << endl;

    // TODO: return actual number of cycles
    return 0;
}

}
