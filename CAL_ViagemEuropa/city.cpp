#include "city.h"
#include "requests.h"

City::City(string name, int pleasure, int hours, int minutes){
	this->name = name;
	this->time = hours * 60 + minutes;
	double lat=0, lon=0;
	getLatLong(name, lat, lon);
	this->lat = lat;
	this->lon = lon;
	this->pleasure = pleasure;
}

City::City(string name, double lat, double lon, int pleasure, int time){
	this->name = name;
	this->time = time;
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

int City::getTime(){
	return this->time;
}
double City::getTimeInHours(){
	return (double)time/60.0;
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
void City::setIndex(int newIndex){
	index = newIndex;
}
int City::getIndex(){
	return index;
}