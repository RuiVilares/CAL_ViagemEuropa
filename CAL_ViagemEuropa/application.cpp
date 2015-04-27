#include "application.h"


Interface *Application::iface = new Interface();

Application::Application(){
	gv = new GraphViewer(1200, 600, false);
	gv->createWindow(1200, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	lastEdge = 0;
	lastNode = 0;
	start();
}


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
	City city = City(name, pleasure, hours, minutes);
	if (city.getLat() == 0.0 || city.getLon() == 0.0)
		iface->drawString("\n\n\tCity didn't found");
	else
	{
		city.setIndex(lastNode);
		cities.addVertex(city);
		gv->addNode(city.getIndex(), calcX(city.getLon()), calcY(city.getLat()));
		gv->setVertexLabel(lastNode, city.getName());
		gv->rearrange();
		lastNode++;
	}
}
void Application::addConnection(){
	string nameSrc;
	string nameDst;
	TopMenu("ADD CONNECTION");
	iface->drawString("Source city: ");
	iface->read(nameSrc);
	iface->drawString("Destination city: ");
	iface->read(nameDst);
	int citySource = -1;
	int cityDestination = -1;
	for (size_t i = 0; i < cities.getNumVertex(); i++)
	{
		if (cities.getVertexSet()[i]->getInfo().getName() == nameSrc)
		{
			citySource = i;
		}
		else if (cities.getVertexSet()[i]->getInfo().getName() == nameDst){
			cityDestination = i;
		}
	}
	if (citySource != -1 && cityDestination != -1){
		int time = getTravelDuration(cities.getVertexSet()[citySource]->getInfo().getLat(), cities.getVertexSet()[citySource]->getInfo().getLon(), cities.getVertexSet()[cityDestination]->getInfo().getLat(), cities.getVertexSet()[cityDestination]->getInfo().getLon());
		int hour;
		double min;
		cities.getVertexSet()[citySource]->addEdge(cities.getVertexSet()[cityDestination], (double)time/3600.0);
		cities.getVertexSet()[cityDestination]->addEdge(cities.getVertexSet()[citySource], (double)time/3600.0);
		gv->addEdge(lastEdge, cities.getVertexSet()[citySource]->getInfo().getIndex(), cities.getVertexSet()[cityDestination]->getInfo().getIndex(), EdgeType::UNDIRECTED);
		hour = time / 3600;
		min = time % 3600;
		min = (min / 3600) * 60;
		gv->setEdgeLabel(lastEdge, to_string(hour) + ":" + to_string(int(min)));
		gv->rearrange();
		lastEdge++;
		return;
	}
	iface->drawString("\n\n\tCity didn't found");
	iface->getInput();
}


void Application::removeCity(){
	unsigned int command;
	while(1){
		TopMenu("REMOVE CITY");
		for (unsigned int i = 0; i < cities.getNumVertex(); i++){
			iface->drawString(to_string(i + 1) + ". " + cities.getVertexSet()[i]->getInfo().getName());
			iface->newLine();
		}
		iface->drawString("\n0. Return");
		iface->drawString("\n\n   > ");
		iface->read(command);
		if (command == 0)
			return;
		else if (command > 0 && command <= cities.getNumVertex()){
			TopMenu("REMOVE CITY");
			iface->drawString("\n\n\n" + cities.getVertexSet()[command-1]->getInfo().getName() + " was sucefully removed!!!\n");
			gv->removeNode(cities.getVertexSet()[command - 1]->getInfo().getIndex());
			cities.removeVertex(cities.getVertexSet()[command - 1]->getInfo());
			iface->getInput();
		}
	}
}

void Application::showCities(){
	char command;
	int hour;
	double min;
	while (1){
		TopMenu("SHOW CITIES");
		iface->drawString("   NAME\t\tLAT\t\tLON\t   PLEASURE\tTIME IN CITY\n");
		for (unsigned int i = 0; i < cities.getNumVertex(); i++){
			iface->drawString("-> " + cities.getVertexSet()[i]->getInfo().getName());
			hour = cities.getVertexSet()[i]->getInfo().getTime()/60;
			min = cities.getVertexSet()[i]->getInfo().getTime() % 60;
			iface->drawString("\t" + to_string(cities.getVertexSet()[i]->getInfo().getLat()) + "\t" + to_string(cities.getVertexSet()[i]->getInfo().getLon()) + "\t" + to_string(cities.getVertexSet()[i]->getInfo().getPleasure()) + "\t" + to_string(hour) + ":" + to_string((int)min));
			iface->newLine();
			vector <Edge<City>> edges = cities.getVertexSet()[i]->getAdj();
			for (size_t j = 0; j < edges.size(); j++)
			{
				double weight = edges[j].getWeight();
				int hours = (int) weight;
				int minutes = (weight-hours)*60;
				stringstream ss;
				ss << hours << "h" << minutes;
				iface->drawString("\t|__" + edges[j].getDest()->getInfo().getName() + " " + ss.str());
				iface->newLine();
			}

		}
		iface->drawString("\nq. Return");
		iface->drawString("\n\n   > ");
		iface->read(command);
		if (command == 'q')
			return;
	}
}

Graph<City> Application::getCities(){
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
			return;
		}
		else if (command == 'b'){
			main();
			return;
		}
	}
}
void Application::limitedTimeRoute(){
	string name;
	TopMenu("MAXIMIZE PLEASURE");
	int inputTime;
	double totalTime; 
	iface->drawString("Total time (in hours): ");
	iface->read(inputTime);
	int time = inputTime;
	int totalPleasure;
	vector<int > route;
	cities.knapsack(inputTime);
	do{
		route = cities.getKnapsackSolution(time);

		totalPleasure = 0;
		totalTime = 0;
		
		totalTime += cities.getCityTime(route);
		for (size_t i = 0; i < route.size() - 1; i++)
		{
			totalPleasure += cities.getVertexSet()[route[i+1]]->getInfo().getPleasure();
			double time = cities.getW(route[i], route[i + 1]);
			totalTime += time;
		}
		totalPleasure -= cities.getVertexSet()[route[route.size() - 1]]->getInfo().getPleasure();
		if (totalTime >(double)inputTime){
			time--;
		}
		else{
			break;
		}
	} while (1);
	iface->drawString("Total Pleasure: " + to_string(totalPleasure) + "\n\n");

	for (size_t i = 0; i < route.size() - 1; i++)
	{
		double time = cities.getW(route[i], route[i + 1]);
		iface->drawString("\n \n " + cities.getVertexSet()[route[i]]->getInfo().getName() + "-" + cities.getVertexSet()[route[i + 1]]->getInfo().getName() + ": ");
		iface->drawString(to_string((int)time) + "h" + to_string((int)((time - (double)(int)time) * 60)));
		double timeCity = cities.getVertexSet()[route[i + 1]]->getInfo().getTimeInHours();
		if (i != route.size() - 2){
			iface->drawString("\n \n " + cities.getVertexSet()[route[i + 1]]->getInfo().getName() + ": ");
			iface->drawString(to_string((int)timeCity) + "h" + to_string((int)((timeCity - (double)(int)timeCity) * 60)));
		}
	}
	
	result = new GraphViewer(1200, 600, false);
	result->defineVertexColor("green");
	result->defineEdgeColor("green");
	result->createWindow(1200, 600);
	result->addNode(0, calcX(cities.getVertexSet()[0]->getInfo().getLon()), calcY(cities.getVertexSet()[0]->getInfo().getLat()));
	result->setVertexLabel(0, cities.getVertexSet()[0]->getInfo().getName());
	for (size_t i = 0; i < route.size() - 1; i++){
		result->addNode(i + 1, calcX(cities.getVertexSet()[route[i + 1]]->getInfo().getLon()), calcY(cities.getVertexSet()[route[i + 1]]->getInfo().getLat()));
		result->setVertexLabel(i + 1, cities.getVertexSet()[route[i + 1]]->getInfo().getName());
		result->addEdge(i, i, i + 1, EdgeType::UNDIRECTED);
		result->setEdgeLabel(i, to_string(i + 1));
		result->setEdgeThickness(i, 5);
	}
	result->addEdge(route.size(), 0, route.size() - 1, EdgeType::UNDIRECTED);
	result->setEdgeLabel(route.size(), to_string(route.size()));
	result->setEdgeThickness(route.size(), 5);
	result->rearrange();
	iface->getInput();
	result->closeWindow();
}


void Application::main()
{
	while (1){
		char command;
		TopMenu("MAIN MENU");
		iface->drawString("a. Add city\n");
		iface->drawString("b. Remove city\n");
		iface->drawString("c. Show cities\n");
		iface->drawString("d. Best route with a limited time\n");
		iface->drawString("e. Ideal route\n");
		iface->drawString("f. Save cities\n");
		iface->drawString("g. Add conection\n");
		iface->drawString("h. Swap Home City\n");
		iface->drawString("q. Quit(!)\n\n");
		iface->drawString("   > ");
		iface->readChar(command);
		if (command == 'a'){
			addCity();
		}
		else if (command == 'b'){
			removeCity();
		}
		else if (command == 'c'){
			showCities();
		}
		else if (command == 'd') {
			limitedTimeRoute();
		}
		else if (command == 'e'){
			idealRoute();
		}
		else if (command == 'f'){
			saveCities();
		}
		else if (command == 'g'){
			addConnection();
		}
		else if (command == 'h'){
			swapHome();
		}
		else if (command == 'q'){
			return;
		}
	}
}
void Application::swapHome(){
	TopMenu("SWAP HOME CITY");
	iface->drawString("Enter new home city: ");
	string name;
	iface->readLine(name);
	for (size_t i = 0; i < cities.getNumVertex(); i++)
	{
		if (cities.getVertexSet()[i]->getInfo().getName() == name){
			cities.swap(0, i);
			return;
		}
	}
	iface->drawString("City not found!!!");
	iface->getInput();
	
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
		while (i<cities.getNumVertex())
		{
			myfile << cities.getVertexSet()[i]->getInfo().getName() << " " << cities.getVertexSet()[i]->getInfo().getLat() << " " << cities.getVertexSet()[i]->getInfo().getLon() << " " << cities.getVertexSet()[i]->getInfo().getPleasure() << " " << cities.getVertexSet()[i]->getInfo().getTime() << endl;
			i++;
		}
		i = 0;
		myfile << "#" << endl;
		vector<string>names;
		while (i<cities.getNumVertex())
		{
			unsigned int j = 0;
			while (j < cities.getVertexSet()[i]->getAdj().size()){
				if (find(names.begin(), names.end(), cities.getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getName()) == names.end()){
					myfile << cities.getVertexSet()[i]->getInfo().getName() << " " << cities.getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getName() << " " << cities.getVertexSet()[i]->getAdj()[j].getWeight() << endl;
				}
				names.push_back(cities.getVertexSet()[i]->getInfo().getName());
				j++;
			}
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
		if (!myfile.is_open()){
			iface->drawString("\n\n\nFile not found!");
			iface->getInput();
			continue;
		}
		stringstream ss;
		string line = "", name, src, dst;
		double lat, lon, duration;
		int pleasure, time;
		while (!myfile.eof() && line !="#")
		{
			ss.clear();
			getline(myfile, line);
			if (line != "" && line != "#"){
				ss << line;
				ss >> name >> lat >> lon >> pleasure >> time;
				City cidade(name, lat, lon, pleasure, time);
				cidade.setIndex(lastNode);
				cities.addVertex(cidade);
				gv->addNode(cidade.getIndex(), calcX(lon), calcY(lat));
				gv->setVertexLabel(lastNode, name);
				gv->rearrange();
				lastNode++;
			}
		}
		while (!myfile.eof())
		{
			ss.clear();
			getline(myfile, line);
			if (line != ""){
				ss << line;
				ss >> src >> dst >> duration;
				int citySource = -1;
				int cityDestination = -1;
				for (size_t i = 0; i < cities.getNumVertex(); i++)
				{
					if (cities.getVertexSet()[i]->getInfo().getName() == src)
					{
						citySource = i;
					}
					else if (cities.getVertexSet()[i]->getInfo().getName() == dst){
						cityDestination = i;
					}
				}
				if (citySource != -1 && cityDestination != -1){
					int hour;
					double min;
					cities.getVertexSet()[citySource]->addEdge(cities.getVertexSet()[cityDestination], duration);
					cities.getVertexSet()[cityDestination]->addEdge(cities.getVertexSet()[citySource], duration);
					gv->addEdge(lastEdge, citySource, cityDestination, EdgeType::UNDIRECTED);
					hour = duration;
					min = duration - hour;
					min *= 60;
					gv->setEdgeLabel(lastEdge, to_string(hour) + ":" + to_string(int(min)));
					gv->rearrange();
					lastEdge++;
				}
			}
		}
		myfile.close();
		iface->drawString("\n\n\nCities were sucefully loaded.");
		iface->getInput();
		return;
	}
}

void Application::launch(){
	string url;
	url = "start http://map.project-osrm.org/?hl=pt\"";
	unsigned int i = 0;
	while (i<cities.getNumVertex())
	{
		url += "&loc=" + to_string(cities.getVertexSet()[i]->getInfo().getLat()) + "," + to_string(cities.getVertexSet()[i]->getInfo().getLon());
		i++;
	}
	url += "&loc=" + to_string(cities.getVertexSet()[0]->getInfo().getLat()) + "," + to_string(cities.getVertexSet()[0]->getInfo().getLon());

	system(url.c_str());
}

int Application::calcX(double lon){
	int aux;
	aux = ((lon + 10) * 1200) / 70;
	return aux;
}
int Application::calcY(double lat){
	int aux;
	aux = 600-(((lat - 35) * 600) / 35);
	return aux;
}
void Application::idealRoute(){
	cities.BB_TSP();
	TopMenu("IDEAL ROUTE");
	string path = cities.getHamiltonPath();
	if (path == ""){
		iface->drawString("There is no hamilton cycleo \n");
		iface->getInput();
		return;
	}
	else{
		double totalTime = cities.getTotalCost();
		for (size_t i = 1; i < cities.getNumVertex(); i++){
			int hours = cities.getVertexSet()[i]->getInfo().getTimeInHours();
			double minutes = (cities.getVertexSet()[i]->getInfo().getTimeInHours() - (double)hours) * 60.0;
			iface->drawString("Time in " + cities.getVertexSet()[i]->getInfo().getName() + ": " + to_string(hours) + "h" + to_string((int)minutes) + "\n");
			totalTime += cities.getVertexSet()[i]->getInfo().getTimeInHours();
		}
		int totalhours = totalTime;
		double totalminutes = (totalTime - (double)totalhours)*60.0;
		int totalM = (int)totalminutes;
		iface->drawString("Total time including all car trips: " + to_string(totalhours) + "h" + to_string(totalM) + "\n");
	}
	result = new GraphViewer(1200, 600, false);
	result->createWindow(1200, 600);
	result->defineVertexColor("green");
	result->defineEdgeColor("green");
	result->addNode(0, calcX(cities.getVertexSet()[0]->getInfo().getLon()), calcY(cities.getVertexSet()[0]->getInfo().getLat()));
	result->setVertexLabel(0, cities.getVertexSet()[0]->getInfo().getName());
	int j = 1;
	string index;
	
	int indexNode;
	for (size_t i = 2; i < path.length() -2; i+=2){
		index[0] = path[i];
		indexNode = stoi(index);
		result->addNode(j, calcX(cities.getVertexSet()[indexNode]->getInfo().getLon()), calcY(cities.getVertexSet()[indexNode]->getInfo().getLat()));
		result->setVertexLabel(j, cities.getVertexSet()[indexNode]->getInfo().getName());
		result->addEdge(j-1, j-1, j, EdgeType::UNDIRECTED);
		result->setEdgeLabel(j-1, to_string(j));
		result->setEdgeThickness(j - 1, 5);
		j++;
	}
	result->addEdge(j - 1, j - 1, 0, EdgeType::UNDIRECTED);
	result->setEdgeLabel(j - 1, to_string(j));
	result->setEdgeThickness(j - 1, 5);
	result->rearrange();
	iface->getInput();
	result->closeWindow();

}