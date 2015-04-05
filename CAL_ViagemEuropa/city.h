#pragma once

#include <string>

using namespace std;

class City{
	private:
		string name;
		double lat;
		double lon;
		int pleasure;
	
	public:
		City(string name, int pleasure);
		City(string name, double lat, double lon, int pleasure);
		string getName();
		double getLat();
		double getLon();
		int getPleasure();
		bool operator <(const City city);
		bool operator ==(const City city);
};