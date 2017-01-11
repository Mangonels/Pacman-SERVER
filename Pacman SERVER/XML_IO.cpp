#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "xml/rapidxml.hpp"
#include <string>

using namespace std;

static void XMLParser(std::string &&filename, std::string &&level, int &PHealth, int &GTime, int &GInitSpeed) {
	rapidxml::file<> xmlFile(filename); //carreguem filename a un a variable file de XML
	rapidxml::xml_document<> doc; //creem un espai de memoria per a un document xml
	try {
		doc.parse<0>(xmlFile.data()); //parsejem doc i hi asignem el contingut (data()) de xmlFile
	}
	catch (rapidxml::parse_error err) {
		std::cout << err.what() << std::endl /*<< err.where() << std::endl*/;
		system("pause");
	}
	rapidxml::xml_node<> *root_node = doc.first_node("levels"); //root node contindrá el primer node, que será <levels>

	rapidxml::xml_node<> *difficulty_node = root_node->first_node(level.c_str()); //basicament aqui estem escalant de node en node, fins arrivar al nivell de l'arbre que volem.

	rapidxml::xml_node<> *healthAttr = difficulty_node->first_node("PHealth"); //busquem el node PHealth que conté la vida del frogger
	PHealth = std::stoi(healthAttr->value());//Canviem el tipus de la variable obtinguda (un string) a int, de manera que ens sera mes util

	rapidxml::xml_node<> *timeAttr = difficulty_node->first_node("GTime"); //mateixa operacio
	GTime = std::stoi(timeAttr->value());

	rapidxml::xml_node<> *initspeedAttr = difficulty_node->first_node("GInitSpeed"); //same
	GInitSpeed = std::stoi(initspeedAttr->value());
}