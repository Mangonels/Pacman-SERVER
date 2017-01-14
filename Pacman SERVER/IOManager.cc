#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include "xml/rapidxml.hpp"
#include "xml/rapidxml_iterators.hpp"
#include "xml/rapidxml_print.hpp"
#include "xml/rapidxml_utils.hpp"

#include "Resource.cc"

using namespace std;
using namespace rapidxml;

struct Player {
	string name = "Test";
	int score = 0;
	bool a1 = false;
	bool a2 = false;
	bool a3 = false;
	bool a4 = false;
	bool a5 = false;
};

namespace IOManager {

	//Function which recieves the name of a player and the score, and stores them inside an xml file with the same name as the player "player.xml"
	static void SetPlayerData(Player player) {

		string theScore = to_string(player.score);
		string theA1 = to_string(player.a1);
		string theA2 = to_string(player.a2);
		string theA3 = to_string(player.a3);
		string theA4 = to_string(player.a4);
		string theA5 = to_string(player.a5);
		//Simple File IO for GENERATING THE PLAYER'S FILE:
		ofstream playerdata;
		playerdata.open(RESOURCE_FILE(player.name));
		playerdata.close();

		//VIRTUALLY GENERATING XML DOCUMENT + Parsing is done if file already exists:
		file<> xmlFile(RESOURCE_FILE(player.name)); //loads file to an XML file variable
		xml_document<> xmlDoc; //Creates memory space for XML document
		xmlDoc.parse<parse_no_data_nodes>(xmlFile.data()); //Parses "doc", and assigns the content "data()" from "xmlFile". With the singularity that we are parsing no nodes (lol).

														   //GENERATING NODES FOR THE VIRTUAL XML DOCUMENT:
														   //The first node we want to generate is the declaration node, so it should look like this inside the file: <?xml version="1.0" encoding="UTF-8"?>
		xml_node<> *declaration = xmlDoc.allocate_node(node_declaration); //Generates a node, which is allocated inside the xmlDoc. node_declaration is the enum node kind.
		declaration->append_attribute(xmlDoc.allocate_attribute("version", "1.0")); //Creates an attribute for the previously generated node.
		declaration->append_attribute(xmlDoc.allocate_attribute("encoding", "utf-8")); //Creates a second attribute.
		xmlDoc.append_node(declaration); //This actually sets the previously generated node as first child node inside the file. According to documentation.

		xml_node<> *root = xmlDoc.allocate_node(node_element, player.name.c_str()); //Generates a node for the playername.
		root->name(player.name.c_str()); //Sets the name of the node, same as the inserted player name.
		xmlDoc.append_node(root); //Joins the node to inside of the document.

		xml_node<>* childName = xmlDoc.allocate_node(node_element, "Name"); //Generates child score node.
		childName->value(player.name.c_str()); //Sets the value inside this node to the previously parsed to string, int score.
		root->append_node(childName); //Sets the node inside the root node.

		xml_node<>* childScore = xmlDoc.allocate_node(node_element, "Score"); //Generates child score node.
		childScore->value(theScore.c_str()); //Sets the value inside this node to the previously parsed to string, int score.
		root->append_node(childScore); //Sets the node inside the root node.

									   //achievement1
		xml_node<>* childAchievement1 = xmlDoc.allocate_node(node_element, "Achievement1"); //Generates child achievements node.
		childAchievement1->value(theA1.c_str()); //Same as with previous child node.
		root->append_node(childAchievement1); // ""
											  //achievement2
		xml_node<>* childAchievement2 = xmlDoc.allocate_node(node_element, "Achievement2"); //Generates child achievements node.
		childAchievement2->value(theA2.c_str()); //Same as with previous child node.
		root->append_node(childAchievement2); // ""
											  //achievement3
		xml_node<>* childAchievement3 = xmlDoc.allocate_node(node_element, "Achievement3"); //Generates child achievements node.
		childAchievement3->value(theA3.c_str()); //Same as with previous child node.
		root->append_node(childAchievement3); // ""
											  //achievement4
		xml_node<>* childAchievement4 = xmlDoc.allocate_node(node_element, "Achievement4"); //Generates child achievements node.
		childAchievement4->value(theA4.c_str()); //Same as with previous child node.
		root->append_node(childAchievement4); // ""
											  //achievement5
		xml_node<>* childAchievement5 = xmlDoc.allocate_node(node_element, "Achievement5"); //Generates child achievements node.
		childAchievement5->value(theA5.c_str()); //Same as with previous child node.
		root->append_node(childAchievement5); // ""

											  //WRITING THE VIRTUAL XML DOCUMENT ONTO THE FILE, again THROUGH FileIO:
		playerdata.open(RESOURCE_FILE(player.name));
		playerdata << xmlDoc;
		playerdata.close();
		xmlDoc.clear();


	}

	static Player GetPlayerData(Player player)
	{
		try {
			rapidxml::file<> xmlFile(RESOURCE_FILE(player.name));
		}
		catch (exception e) {
			return player;
		}
		rapidxml::file<> xmlFile(RESOURCE_FILE(player.name)); //carreguem filename a un a variable file de XML
		rapidxml::xml_document<> doc; //creem un espai de memoria per a un document xml
		try {
			doc.parse<0>(xmlFile.data()); //parsejem doc i hi asignem el contingut (data()) de xmlFile
		}
		catch (rapidxml::parse_error err) {
			std::cout << err.what() << std::endl /*<< err.where() << std::endl*/;
			system("pause");
		}

		rapidxml::xml_node<> *root_node = doc.first_node(player.name.c_str()); //root node contindrá el primer node, que será <levels>

		rapidxml::xml_node<> *nameAttr = root_node->first_node("Name");
		player.name = nameAttr->value();

		rapidxml::xml_node<> *scoreAttr = root_node->first_node("Score"); //mateixa operacio
		player.score = std::stoi(scoreAttr->value());

		rapidxml::xml_node<> *a1Attr = root_node->first_node("Achievement1"); //same
		player.a1 = std::stoi(a1Attr->value());

		rapidxml::xml_node<> *a2Attr = root_node->first_node("Achievement2"); //same
		player.a2 = std::stoi(a2Attr->value());

		rapidxml::xml_node<> *a3Attr = root_node->first_node("Achievement3"); //same
		player.a3 = std::stoi(a3Attr->value());

		rapidxml::xml_node<> *a4Attr = root_node->first_node("Achievement4"); //same
		player.a4 = std::stoi(a4Attr->value());

		rapidxml::xml_node<> *a5Attr = root_node->first_node("Achievement5"); //same
		player.a5 = std::stoi(a5Attr->value());

		return player;
	}

	static void SetRanking(list<Player> ranking)
	{
		string names = "Ranking";

		ofstream playerdata;
		playerdata.open(RESOURCE_FILE(names));
		playerdata.close();

		file<> xmlFile(RESOURCE_FILE(names)); //loads file to an XML file variable
		xml_document<> xmlDoc;
		xmlDoc.parse<parse_no_data_nodes>(xmlFile.data());

		xml_node<> *declaration = xmlDoc.allocate_node(node_declaration); //Generates a node, which is allocated inside the xmlDoc. node_declaration is the enum node kind.
		declaration->append_attribute(xmlDoc.allocate_attribute("version", "1.0")); //Creates an attribute for the previously generated node.
		declaration->append_attribute(xmlDoc.allocate_attribute("encoding", "utf-8")); //Creates a second attribute.
		xmlDoc.append_node(declaration); //This actually sets the previously generated node as first child node inside the file. According to documentation.

		xml_node<> *root = xmlDoc.allocate_node(node_element, "Ranking"); //Generates a node for the playername.
		root->name("Ranking"); //Sets the name of the node, same as the inserted player name.
		xmlDoc.append_node(root); //Joins the node to inside of the document.

		
		int i = 1;
		for (list<Player>::const_iterator iterator = ranking.begin(), end = ranking.end(); iterator != end; ++iterator) {

			string theName = "player" + to_string(i);
			string theScore = to_string(iterator->score);
			
			xml_node<> *player = xmlDoc.allocate_node(node_element, "Player"); //Generates a node for the playername.
			player->name("Player"); //Sets the name of the node, same as the inserted player name.
			xmlDoc.append_node(player); //Joins the node to inside of the document.

			xml_node<>* name = xmlDoc.allocate_node(node_element, "Name"); //Generates child score node.
			name->value(iterator->name.c_str()); //Sets the value inside this node to the previously parsed to string, int score.
			player->append_node(name);
			
			xml_node<>* score = xmlDoc.allocate_node(node_element, "Score"); //Generates child score node.
			score->value(theScore.c_str()); //Sets the value inside this node to the previously parsed to string, int score.
			player->append_node(score);
			i++;
		}
		playerdata.open(RESOURCE_FILE(names));
		playerdata << xmlDoc;
		playerdata.close();
		xmlDoc.clear();
	}

	static void GetRanking()
	{

	}

}