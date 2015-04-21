#include "application.h"

Interface *Application::iface = new Interface();

Application::Application(){
	start();
}


// implementar comparador ==
void Application::addCity(){
	string name;
	int pleasure=-1, hours=-1, minutes=-1;
	TopMenu("ADD CITY");
	iface->drawString("City name: ");
	iface->read(name);
	while (pleasure <= 0 || pleasure > 10){
		iface->drawString("Pleasure of visiting the city(1-10): ");
		iface->read(pleasure);
	}
	iface->drawString("How much time do you pretend stay in the city?\n");
	while (hours < 0){
		iface->drawString("\tHours: ");
		iface->read(hours);
	}
	while (minutes < 0 || minutes > 60){
		iface->drawString("\tMinutes: ");
		iface->read(minutes);
	}
	City* city = new City(name, pleasure, hours, minutes);
	if (city->getLat() == 0.0 || city->getLon() == 0.0)
		iface->drawString("\n\n\tCity didn't found");
	else
	{
		vector<City *>::iterator it;
		it = find(cities.begin(), cities.end(), city);
		if (it == cities.end())
			cities.push_back(city);
		else
			iface->drawString("\n\n\tCity already exists");
	}
}

void Application::removeCity(){
	unsigned int command;
	while(1){
		TopMenu("REMOVE CITY");
		for (unsigned int i = 0; i < cities.size(); i++){
			iface->drawString(to_string(i + 1) + ". " + cities[i]->getName());
			iface->newLine();
		}
		iface->drawString("\n0. Return");
		iface->drawString("\n\n   > ");
		iface->read(command);
		if (command == 0)
			return;
		else if (command > 0 && command <= cities.size()){
			TopMenu("REMOVE CITY");
			iface->drawString("\n\n\n" + cities[command-1]->getName() + " was sucefully removed!!!\n");
			cities.erase(cities.begin() + (command - 1));
			iface->getInput();
		}
	}
}

vector<City *> Application::getCities(){
	return this->cities;
}

void Application::TopMenu(string name)
{
	iface->cleanScr();
	iface->drawString("\n\n\tEUROPE TRAVEL\n");
	iface->drawString("\n\t");
	iface->drawString(name);
	iface->drawString("\n\n\n\n");
}


void Application::start(){
	while (1){
		char command;
		TopMenu("WELCOME");
		iface->drawString("Do you want load a cities configuration?\n\n");
		iface->drawString("a. Yes\n");
		iface->drawString("b. No\n\n");
		iface->drawString("   > ");
		iface->readChar(command);
		if (command == 'a'){
			loadCities();
			main();
		}
		else if (command == 'b'){
			main();
		}
		return;
	}
}


void Application::main()
{
	while (1){
		char command;
		TopMenu("MAIN MENU");
		iface->drawString("a. Add city\n");
		iface->drawString("b. Remove city\n");
		iface->drawString("c. Best route with a limited time\n");
		iface->drawString("d. Ideal route\n");
		iface->drawString("e. Save cities\n");
		iface->drawString("q. Quit(!)\n\n");
		iface->drawString("   > ");
		iface->readChar(command);
		if (command == 'a'){
			addCity();
		}
		else if (command == 'b'){
			removeCity();
		}
		else if (command == 'c') {
			// Mochila
			launch();
		}
		else if (command == 'd'){
			// Branch and Bound
			launch();
		}
		else if (command == 'e'){
			saveCities();
		}
		else if (command == 'q'){
			return;
		}
	}
}

void Application::saveCities(){
	while (1){
		string file;
		TopMenu("SAVE CITIES");
		iface->drawString("r. Quit\n\n");
		iface->drawString("Enter file name: ");
		iface->readLine(file);
		if (file == "q")
			return;
		ofstream myfile;
		file = "Saves/" + file + ".txt";
		myfile.open(file);
		unsigned int i = 0;
		while (i<cities.size())
		{
			myfile << cities[i]->getName() << " " << cities[i]->getLat() << " " << cities[i]->getLon() << " " << cities[i]->getPleasure() << " " << cities[i]->getTime() << endl;
			i++;
		}
		myfile.close();
		iface->drawString("\n\n\nCities were sucefully saved.");
		iface->getInput();
		return;
	}
}

void Application::loadCities(){
	while (1){
		string file;
		TopMenu("LOAD CITIES");
		iface->drawString("q. Quit\n\n");
		iface->drawString("Enter file name: ");
		iface->readLine(file);
		if (file == "q")
			return;
		ifstream myfile;
		file = "Saves/" + file + ".txt";
		myfile.open(file);
		stringstream ss;
		string line, name;
		double lat, lon;
		int pleasure, time;
		while (!myfile.eof())
		{
			ss.clear();
			getline(myfile, line);
			if (line != ""){
				ss << line;
				ss >> name >> lat >> lon >> pleasure >> time;
				cities.push_back(new City(name, lat, lon, pleasure, time));
			}
		}
		myfile.close();
		iface->drawString("\n\n\nCities were sucefully loaded.");
		iface->getInput();
		return;
	}
}

void Application::launch(){
	system("start https://www.google.pt/maps");
}