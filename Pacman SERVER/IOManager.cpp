#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

#include "xml/rapidxml.hpp"
#include "xml/rapidxml_iterators.hpp"
#include "xml/rapidxml_print.hpp"
#include "xml/rapidxml_utils.hpp"

#include "Resource.cpp"

using namespace std;
using namespace rapidxml;

//Function which recieves the name of a player and the score, and stores them inside an xml file with the same name as the player "player.xml"
static void CreateOrSetPlayerXML(string player, int score, string achievements) {

	string theScore = to_string(score);

	//Simple File IO for GENERATING THE PLAYER'S FILE:
	ofstream playerdata;
	playerdata.open(RESOURCE_FILE(player));
	playerdata.close();

	//VIRTUALLY GENERATING XML DOCUMENT + Parsing is done if file already exists:
	file<> xmlFile(RESOURCE_FILE(player)); //loads file to an XML file variable
	xml_document<> xmlDoc; //Creates memory space for XML document
	xmlDoc.parse<parse_no_data_nodes>(xmlFile.data()); //Parses "doc", and assigns the content "data()" from "xmlFile". With the singularity that we are parsing no nodes (lol).

	//GENERATING NODES FOR THE VIRTUAL XML DOCUMENT:
	//The first node we want to generate is the declaration node, so it should look like this inside the file: <?xml version="1.0" encoding="UTF-8"?>
	xml_node<> *declaration = xmlDoc.allocate_node(node_declaration); //Generates a node, which is allocated inside the xmlDoc. node_declaration is the enum node kind.
	declaration->append_attribute(xmlDoc.allocate_attribute("version", "1.0")); //Creates an attribute for the previously generated node.
	declaration->append_attribute(xmlDoc.allocate_attribute("encoding", "utf-8")); //Creates a second attribute.
	xmlDoc.append_node(declaration); //This actually sets the previously generated node as first child node inside the file. According to documentation.

	xml_node<> *root = xmlDoc.allocate_node(node_element, "Player"); //Generates a node for the playername.
	root->name(player.c_str()); //Sets the name of the node, same as the inserted player name.
	xmlDoc.append_node(root); //Joins the node to inside of the document.

	xml_node<>* childScore = xmlDoc.allocate_node(node_element, "Score"); //Generates child score node.
	childScore->value(theScore.c_str()); //Sets the value inside this node to the previously parsed to string, int score.
	root->append_node(childScore); //Sets the node inside the root node.

	xml_node<>* childAchievements = xmlDoc.allocate_node(node_element, "Achievements"); //Generates child achievements node.
	childAchievements->value(achievements.c_str()); //Same as with previous child node.
	root->append_node(childAchievements); // ""

	//WRITING THE VIRTUAL XML DOCUMENT ONTO THE FILE, again THROUGH FileIO:
	playerdata.open(RESOURCE_FILE(player));
	playerdata << xmlDoc;
	playerdata.close();
	xmlDoc.clear();

}
