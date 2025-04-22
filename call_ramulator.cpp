#include "wrapper.hpp"
#include "call_ramulator.h"

using namespace std;
using namespace Ramulator;

extern "C" {

struct RamulatorWrapper {
    YAML::Node config;
    IFrontEnd* frontend;
    IMemorySystem* memory_system;

    RamulatorWrapper(const char *config_file) {
        // call config
        config = Ramulator::Config::parse_config_file(config_file, {});
        cout << "Loaded configuration from file." << endl;

        // call frontend
        frontend = Ramulator::Factory::create_frontend(config);
        cout << "Created frontend instance." << endl;

        // call memory system
        memory_system = Ramulator::Factory::create_memory_system(config);
        cout << "Created memory system instance." << endl;

        frontend->connect_memory_system(memory_system);
        memory_system->connect_frontend(frontend);
    }
};

RamulatorWrapper *create_ramulator_wrapper(const char *config_file) {
    return new RamulatorWrapper(config_file);
}

unsigned long long get_latency_for_request(RamulatorWrapper *sys, unsigned long long addr) {
    // create request
    Addr_t addr_(addr); 
    Request request(addr_, Request::Type::Read);

    bool request_completed = false;
    request.callback = [&request_completed](Request& req) {
        request_completed = true;
    };

    // Record arrival time
    unsigned long long current_cycle = 0;

    // send request back to memory
    sys->memory_system->send(request);
    cout << "Sent a memory request." << endl;

    int frontend_tick = sys->frontend->get_clock_ratio();
    int mem_tick = sys->memory_system->get_clock_ratio();

    int tick_mult = frontend_tick * mem_tick;
    
    // simulate memory system
    for (uint64_t i = 0;; i++) {
        if (((i % tick_mult) % mem_tick) == 0) {
            sys->frontend->tick();
        }

        if (sys->frontend->is_finished()) {
            break;
        }

        if ((i % tick_mult) % frontend_tick == 0) {
            sys->memory_system->tick();
        }
        // Increment local cycle counter for each iteration
        current_cycle++;
        if (request_completed) {
            break;
        }
    }


    // Return the number of cycles the simulation ran
    return current_cycle;
}


void print_stats(RamulatorWrapper* sys) {
    if (!sys) {
        std::cerr << "RamulatorWrapper is null.\n";
        return;
    }

    // Frontend stats
    if (sys->frontend) {
        std::cout << "\n--- Frontend Statistics ---\n";
        sys->frontend->finalize();
    } else {
        std::cerr << "Frontend pointer is null.\n";
    }

    // Memory system stats
    if (sys->memory_system) {
        std::cout << "\n--- Memory System Statistics ---\n";
        sys->memory_system->finalize();
    } else {
        std::cerr << "Memory system pointer is null.\n";
    }

    std::cout << "==================================\n";
}

}