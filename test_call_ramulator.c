#include "call_ramulator.h"

int main() {

    // test the whole system
    RamulatorWrapper *sys = create_ramulator_wrapper("/usr/scratch/anazareth8/ramulator2/example_config.yaml");

    // enter a sample hex address
    unsigned long long test_addr = 0x12345678;

    unsigned long long latency = get_latency_for_request(sys, test_addr);
    print_stats(sys);

    return 0;
}
