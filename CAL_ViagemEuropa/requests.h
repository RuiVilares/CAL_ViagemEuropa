#pragma once

/** @defgroup Requests Requests
* @{
* Functions for getting web data
*/

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/Dynamic/Var.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace Poco::Net;
using namespace Poco;
using namespace std;
using namespace JSON;
using namespace Dynamic;
using namespace Poco::JSON;


/**
* @brief Get latitude and longitude
*
* @param name Name of the city
* @param lat Lat value passed by reference
* @param lon Lon value passed by reference
*/
void getLatLong(string const &name, double &lat, double &lon);


/**
* @brief Get car travel duration 
*
* @param latSrc Latitude value of source city
* @param lonSrc Latitude value of source city
* @param latDst Latitude value of destination city
* @param lonDst Latitude value of destination city
* @return int with car travel duration in seconds
*/
int getTravelDuration(double const &latSrc, double const &lonSrc, double const &latDst, double const &lonDst);