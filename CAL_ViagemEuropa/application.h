#pragma once

/** @defgroup Application Application
* @{
* Functions for main application
*/

#include <sstream>
#include <algorithm>
#include "requests.h"
#include <vector>
#include <fstream>
#include "city.h"
#include "interface.h"
#include "Graph.h"
#include "graphviewer/graphviewer.h"

using namespace std;

class Application{
private:
	Graph<City> cities; // Graph with cities configuration 
	GraphViewer *gv; // Graphviewer window with cities representation
	GraphViewer *result; // Graphviewer window with solution
	int lastNode; // last node index
	int lastEdge; // last edge index 
public:
	
	/**
	* @brief Interface used on application
	*/
	static Interface *iface;
	
	/**
	* @brief Application constructor
	*/
	Application();
	
	/**
	* @brief Application menu to add a city 
	*/
	void addCity();
	
	/**
	* @brief Application menu to remove a city
	*/
	void removeCity();
	
	/**
	* @brief Application menu to add a cities connection
	*/
	void addConnection();
	
	/**
	* @brief Application menu to show cities
	*/
	void showCities();
	
	/**
	* @brief Get cities graph
	*
	* @return Graph with every cities and connections
	*/
	Graph<City> getCities();

	/**
	* @brief Top Menu configuration 
	*
	* @param name Top Menu name
	*/
	void TopMenu(string name);

	/**
	* @brief Start menu
	*/
	void start();

	/**
	* @brief Main menu
	*/
	void main();
	
	/**
	* @brief Limited time route menu
	*/
	void limitedTimeRoute();

	/**
	* @brief Swap home city menu 
	*/
	void swapHome();

	/**
	* @brief Save cities configuration function  
	*/
	void saveCities();

	/**
	* @brief Load cities configuration function
	*/
	void loadCities();

	/**
	* @brief Launch web route
	*/
	void launch();
	
	/**
	* @brief Ideal route menu
	*/
	void idealRoute();
	
	/**
	* @brief Calculates X position in the graph
	*
	* @param lon Longitude value
	* @return Int x position
	*/
	int calcX(double lon);
	
	/**
	* @brief Calculates Y position in the graph
	*
	* @param lat Latitude value
	* @return Int y position
	*/
	int calcY(double lat);
};