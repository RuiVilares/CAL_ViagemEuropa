#pragma once

/** @defgroup City City
* @{
* Functions to use in city representation
*/

#include <string>

using namespace std;

class City{
	private:
		string name; // represents city name
		double lat; // represents city latitude
		double lon; // represents city longitude
		int pleasure; // represents user pleasure to visit the city
		int time; // represents time to spend in the city
		int index; // represents city index
	
	public:
		/**
		* @brief City constructor
		*
		* @param name City name
		* @param pleasure User pleasure to visit the city
		* @param hours Hours to spend in the city
		* @param minutes Minutes to spend in the city
		*/
		City(string name, int pleasure, int hours, int minutes);

		/**
		* @brief City load constructor
		*
		* @param name City name
		* @param lat City latitude
		* @param lon City longitude
		* @param pleasure User pleasure to visit the city
		* @param time Time to spend in the city, in minutes
		*/
		City(string name, double lat, double lon, int pleasure, int time);

		/**
		* @brief Gets city name
		*
		* @return City name
		*/
		string getName();

		/**
		* @brief Gets city latitude
		*
		* @return City latitude
		*/
		double getLat();

		/**
		* @brief Gets city longitude
		*
		* @return City longitude
		*/
		double getLon();

		/**
		* @brief Gets user pleasure to visit the city
		*
		* @return User pleasure to visit the city
		*/
		int getPleasure();

		/**
		* @brief Gets time to spend in the city
		*
		* @return Time to spend in the city, in minutes
		*/
		int getTime();

		/**
		* @brief Set index city
		*
		* @param newIndex New index to the city
		*/
		void setIndex(int newIndex);

		/**
		* @brief Gets city index 
		*
		* @return City index
		*/
		int getIndex();

		/**
		* @brief Gets time in hours
		*
		* @return Time to spend in the city, in hours
		*/
		double getTimeInHours();

		/**
		* @brief Operator < overloading
		*
		* @param city City to compare
		* @return boolean answer 
		*/
		bool operator <(const City city);

		/**
		* @brief Operator == overloading
		*
		* @param city City to compare
		* @return boolean answer
		*/
		bool operator ==(const City city);
};