#include "interface.h"

using std::string;

//IOSTREAM
Interface::Interface(){
}

Interface::~Interface(){
}

void Interface::getInput(){
	std::cin.get();
}

void Interface::drawChar(char CHAR){
	std::cout << CHAR;
}

void Interface::readLine(std::string &STRING){
	getline(std::cin, STRING);
}

void Interface::cleanScr(){
#ifdef _WIN32 // Windows: Console command (alternative: Windows API)
	system("cls");
#else // UNIX: ANSI escape codes
	std::cout << "\x1B[2J\x1B[H";
#endif
}
void Interface::newLine(){
	std::cout << std::endl;
}