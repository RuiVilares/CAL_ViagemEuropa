#include "requests.h"



void getLatLong(string const &name, double &lat, double &lon)
{
	URI uri("http://nominatim.openstreetmap.org/search?q=" + name + "&format=json");
	HTTPClientSession session1(uri.getHost(), uri.getPort());

	// prepare path
	string path(uri.getPathAndQuery());
	if (path.empty()) path = "/";

	// send request
	HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
	session1.sendRequest(req);

	// get response
	HTTPResponse res;

	// print response
	istream &is = session1.receiveResponse(res);

	string str(static_cast<stringstream const&>(stringstream() << is.rdbuf()).str());

	Parser parser;
	Var result = parser.parse(str);

	Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();
	Object::Ptr object = arr->getObject(0);//
	Var test = object->get("lat");
	lat = stod(test.toString()); // val holds "value"
	test = object->get("lon");
	lon = stod(test.toString()); // val holds "value"
}

int getTravelDuration(double const &latSrc, double const &lonSrc, double const &latDst, double const &lonDst)
{
	stringstream latS; latS << setprecision(3) << latSrc;
	stringstream lonS; lonS << setprecision(3) << lonSrc;
	stringstream latD; latD << setprecision(3) << latDst;
	stringstream lonD; lonD << setprecision(3) << lonDst;
	// prepare session
	URI uri("http://osrm.mapzen.com/car/viaroute?loc=" + latS.str() + "," + lonS.str() + "&loc=" + latD.str() + "," + lonD.str());
	HTTPClientSession session(uri.getHost(), uri.getPort());

	// prepare path
	string path(uri.getPathAndQuery());
	if (path.empty()) path = "/";

	// send request
	HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
	session.sendRequest(req);

	// get response
	HTTPResponse res;

	// print response
	istream &is = session.receiveResponse(res);

	string str(static_cast<stringstream const&>(stringstream() << is.rdbuf()).str());

	Parser parser;
	Var result = parser.parse(str);

	Object::Ptr object = result.extract<Object::Ptr>();
	Var test = object->get("route_summary"); // holds { "property" : "value" }
	Object::Ptr subObject = test.extract<Object::Ptr>();
	test = subObject->get("total_time");


	// CORRIGIR OS 0.9 e as HORAS
	return ((stoi(test.toString())*0.8)); // val holds "value"
}