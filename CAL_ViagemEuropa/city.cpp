#include "city.h"
#include "requests.h"

City::City(string name, int pleasure){
	this->name = name;
	double lat=0, lon=0;
	getLatLong(name, lat, lon);
	this->lat = lat;
	this->lon = lon;
	this->pleasure = pleasure;
}

City::City(string name, double lat, double lon, int pleasure){
	this->name = name;
	this->lat = lat;
	this->lon = lon;
	this->pleasure = pleasure;
}

string City::getName(){
	return this->name;
}

double City::getLat(){
	return this->lat;
}

double City::getLon(){
	return this->lon;
}

int City::getPleasure(){
	return this->pleasure;
}

bool City::operator <(const City city){
	if (name < city.name)
		return true;
	else
		return false;
}

bool City::operator ==(const City city){
	if (name == city.name)
		return true;
	else
		return false;
}
