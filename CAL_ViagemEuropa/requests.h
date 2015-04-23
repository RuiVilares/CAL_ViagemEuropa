#pragma once

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


void getLatLong(string const &name, double &lat, double &lon);

int getTravelDuration(double const &latSrc, double const &lonSrc, double const &latDst, double const &lonDst);