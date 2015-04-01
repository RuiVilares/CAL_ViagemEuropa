#pragma once

#include <vector>
#include "city.h"

using namespace std;

class Application{
private:
	vector<City *> cities;
public:
	Application();
	void addCity(City * city);
	vector<City *> getCities();
};