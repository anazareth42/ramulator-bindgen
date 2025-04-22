.PHONY: all clean

all: test_call_ramulator

libramulatorwrapper.so: call_ramulator.cpp
	g++ -Wall -Wextra -shared -fPIC -std=c++2a -g -o $@ -I/usr/scratch/anazareth8/ramulator2/src -I/usr/scratch/anazareth8/ramulator2/ext/spdlog/include -I/usr/scratch/anazareth8/ramulator2/ext/yaml-cpp/include $^

test_call_ramulator: test_call_ramulator.c libramulatorwrapper.so
	g++ -Wall -Wextra -g -o $@ -Wl,-rpath,. -Wl,-rpath,/usr/scratch/anazareth8/ramulator2 $^ /usr/scratch/anazareth8/ramulator2/libramulator.so

clean:
	-rm -f libramulatorwrapper.so test_call_ramulator