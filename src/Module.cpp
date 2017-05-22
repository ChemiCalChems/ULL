#include "Module.hpp"
#include <ltdl.h>
#include <map>
#include <iostream>

std::map<std::string, Module*> ModuleLoader::modules = {};

void ModuleLoader::loadModule(std::string path, std::string name, QWidget* parent) {
	lt_dlhandle lib = lt_dlopen(path.c_str());
	if (!lib) std::cout << lt_dlerror() << std::endl;
	typedef Module* (*create_t)(QWidget*);
	create_t create = (create_t) lt_dlsym(lib, "create");
	

	Module* lm = create(parent);
	lm->lib = lib;
	
	modules.insert({name, lm});
}

void Module::unload() {
	lt_dlclose(this->lib);
}
