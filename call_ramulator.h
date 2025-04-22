#ifndef __CALL_RAMULATOR_H__
#define __CALL_RAMULATOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Holds the state of the Ramulator simulation.
 */
struct RamulatorWrapper;
typedef struct RamulatorWrapper RamulatorWrapper;

/**
 * Initializes a RamulatorWrapper and returns it.
 */
RamulatorWrapper *create_ramulator_wrapper(const char *config_file);

/**
 * Makes a request to the given address and returns the latency in cycles.
 */
unsigned long long get_latency_for_request(RamulatorWrapper *system, unsigned long long addr);

/**
 * Prints statistics for the frontend and memory system.
 */
void print_stats(RamulatorWrapper* sys);

#ifdef __cplusplus
}
#endif

#endif // __CALL_RAMULATOR_H__