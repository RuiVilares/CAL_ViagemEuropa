#include "city.h"

City::City(string name, int lat, int lon){
	this->name = name;
	this->lat = lat;
	this->lon = lon;
}

string City::getName(){
	return this->name;
}

int City::getLat(){
	return this->lat;
}
int City::getLon(){
	return this->lon;
}