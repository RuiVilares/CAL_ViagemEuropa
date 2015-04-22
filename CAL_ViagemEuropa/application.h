#pragma once

#include <sstream>
#include <algorithm>
#include "requests.h"
#include <vector>
#include <fstream>
#include "city.h"
#include "interface.h"
#include "Graph.h"

using namespace std;

class Application{
private:
	Graph<City *> cities;
public:
	static Interface *iface;
	Application();
	void addCity();
	void removeCity();
	void addConnection();
	void showCities();
	Graph<City *> getCities();
	void TopMenu(string name);
	void start();
	void main();
	//void showFiles();
	void saveCities();
	void loadCities();
	void launch();
};