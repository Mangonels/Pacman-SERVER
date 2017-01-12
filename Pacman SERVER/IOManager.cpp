#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

#include "xml/rapidxml.hpp"
#include "xml/rapidxml_iterators.hpp"
#include "xml/rapidxml_print.hpp"
#include "xml/rapidxml_utils.hpp"

#include "Resource.cpp"

using namespace std;

//Function which recieves the name of a player and the score, and stores them inside an xml file with the same name as the player "player.xml"
static void XMLCreateOrSetPlayer(std::string name, int score) {

	//Simple File IO for generating the player file:
	ofstream playerscore;
	playerscore.open(RESOURCE_FILE(name));
	playerscore << "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>\n";
	playerscore.close();

	//XML Parse/Edit starts here:
	rapidxml::file<> xmlFile(RESOURCE_FILE(name)); //loads file to an XML file variable
	rapidxml::xml_document<> doc; //Creates memory space for XML document
	doc.parse<0>(xmlFile.data()); //Parses "doc", and assigns the content "data()" from "xmlFile"

	
	rapidxml::xml_node<> *node = doc.allocate_node(node_type type, const Ch *name = 0, const Ch *value = 0);
	rapidxml::xml_node<> *node2 = doc.allocate_node(node_element, Player); //(node_type type, const Ch *name=0, const Ch *value=0, std::size_t name_size=0, std::size_t value_size=0)
}