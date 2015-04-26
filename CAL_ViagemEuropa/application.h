#pragma once

#include <sstream>
#include <algorithm>
#include "requests.h"
#include <vector>
#include <fstream>
#include "city.h"
#include "interface.h"
#include "Graph.h"
#include "graphviewer/graphviewer.h"

using namespace std;

class Application{
private:
	Graph<City> cities;
	GraphViewer *gv;
	int lastNode;
	int lastEdge;
public:
	static Interface *iface;
	Application();
	void addCity();
	void removeCity();
	void addConnection();
	void showCities();
	Graph<City> getCities();
	void TopMenu(string name);
	void start();
	void main();
	void limitedTimeRoute();
	//void showFiles();
	void saveCities();
	void loadCities();
	void launch();
	void idealRoute();
	int calcX(double lon);
	int calcY(double lat);
};