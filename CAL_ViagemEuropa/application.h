#pragma once

#include <algorithm>
#include <vector>
#include "city.h"
#include "interface.h"

using namespace std;

class Application{
private:
	vector<City *> cities;
public:
	static Interface *iface;
	Application();
	void addCity();
	void removeCity();
	vector<City *> getCities();
	void TopMenu(string name);
	void main();
};