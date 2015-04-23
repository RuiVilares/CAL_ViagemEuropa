#pragma once

#include <string>

using namespace std;

class City{
	private:
		string name;
		double lat;
		double lon;
		int pleasure;
		int time;
	
	public:
		City(string name, int pleasure, int hours, int minutes);
		City(string name, double lat, double lon, int pleasure, int time);
		string getName();
		double getLat();
		double getLon();
		int getPleasure();
		int getTime();
		double getTimeInHours();
		bool operator <(const City city);
		bool operator ==(const City city);
};