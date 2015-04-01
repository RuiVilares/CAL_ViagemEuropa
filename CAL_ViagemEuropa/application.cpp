#include "application.h"
#include <algorithm>


Application::Application(){
}


// implementar comparador ==
void Application::addCity(City * city){
	vector<City *>::iterator it;
	it = find(cities.begin(), cities.end(), city);
	if (it != cities.end()){
		cities.push_back(city);
	}
}
vector<City *> Application::getCities(){
	return this->cities;
}