#ifndef ULL_MODULE_H
#define ULL_MODULE_H

#include <QtWidgets/QWidget>
#include <functional>
#include <map>
#include <ltdl.h>
#include <thread>
#include <atomic>

struct Module {
	std::thread thread;
	virtual void run() = 0;
	virtual void launch() = 0;
	lt_dlhandle lib;
	std::atomic<int> test;

	void unload();
};

struct ModuleLoader {
	static std::map<std::string, Module*> modules;
	static void loadModule(std::string path, std::string name, QWidget* parent);
	static void unloadModule(std::string name);
};

#endif
