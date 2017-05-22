#include "Module.hpp"
#include <iostream>

struct TestModule : Module {
	void onModuleLoaded() {
		std::cout << "test worked" << std::endl;
	}
};

extern "C" Module* create() {
	return new TestModule;
}
