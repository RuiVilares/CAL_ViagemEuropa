#include "application.h"

Interface *Application::iface = new Interface();

Application::Application(){
	main();
}


// implementar comparador ==
void Application::addCity(){
	string name;
	int pleasure;
	TopMenu("ADD CITY");
	iface->drawString("City name: ");
	iface->read(name);
	iface->drawString("Pleasure of visiting the city: ");
	iface->read(pleasure);
	City* city = new City(name, pleasure);
	if (city->getLat() == 0.0 || city->getLon() == 0.0)
		iface->drawString("\n\n\tCity didn't found");
	else
	{
		//vector<City *>::iterator it;
		//it = find(cities.begin(), cities.end(), city);
		//if (it != cities.end())
			cities.push_back(city);
		//else
		//	iface->drawString("\n\n\tCity already exists");
	}
}

void Application::removeCity(){
	int command;
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

void Application::main()
{
	while (1){
		char command;
		TopMenu("MAIN MENU");
		iface->drawString("a. Add city\n");
		iface->drawString("b. Remove city\n");
		iface->drawString("c. Best route with a limited time\n");
		iface->drawString("d. Ideal route\n");
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
		}
		else if (command == 'd'){
			// Branch and Bound
		}
		else if (command == 'q'){
			return;
		}
	}
}