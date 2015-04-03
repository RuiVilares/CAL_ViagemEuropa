//#include "requests.h"
#include "application.h"


int main(){
	Application app;
	return 0;
}

/*int main()
{
	string src, dst;
	double latSrc, latDst, lonSrc, lonDst, timeTravel;
	cout << "Choose your source city: ";
	cin >> src;
	cout << "Choose your destination city: ";
	cin >> dst;
	getLatLong(src, latSrc, lonSrc);
	getLatLong(dst, latDst, lonDst);

	cout << "\n" << src << ": " << latSrc << ", " << lonSrc << endl;
	cout << dst << ": " << latDst << ", " << lonDst << "\n";

	timeTravel = getTravelDuration(latSrc, lonSrc, latDst, lonDst);
	cout << endl << "Travel time between cities: " << timeTravel << "\n\n";

	system("PAUSE");
	return 0; 
}*/