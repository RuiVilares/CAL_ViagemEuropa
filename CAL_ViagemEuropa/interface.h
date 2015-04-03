#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <iostream>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <stdlib.h>
#endif


class Interface{
public:
	Interface();
	~Interface();
	void getInput();

	template<typename Type>
	void readChar(Type &var);
	void readLine(std::string &STRING);

	template<typename Type>
	void read(Type &var);
	void drawChar(char CHAR);

	template<typename Type>
	void drawString(Type STRING);
	void newLine();
	void cleanScr();
};

template<typename Type>
void Interface::readChar(Type &var){
	std::cin >> var;
	std::cin.ignore(1000, '\n');
	if (std::cin.fail())
		std::cin.clear();
}

template<typename Type>
void Interface::read(Type &var){
	std::cin >> var;
	std::cin.ignore(1000, '\n');
	if (std::cin.fail())
		std::cin.clear();
}

template<typename Type>
void Interface::drawString(Type STRING){
	std::cout << STRING;
}

#endif