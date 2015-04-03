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

string City::getName(){
	return this->name;
}

int City::getLat(){
	return this->lat;
}

int City::getLon(){
	return this->lon;
}

int City::getPleasure(){
	return this->pleasure;
}
