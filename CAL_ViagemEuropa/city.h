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
		string getName();
		int getLat();
		int getLon();
		int getPleasure();
};