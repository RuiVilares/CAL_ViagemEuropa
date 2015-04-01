#pragma once

#include <string>

using namespace std;

class City{
	private:
		string name;
		int lat;
		int lon;
	
	public:
		City(string name, int lat, int lon);
		string getName();
		int getLat();
		int getLon();
};