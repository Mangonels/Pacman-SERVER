#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
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

	//Function which recieves the name of a player and the score, and stores them inside an xml file with the same name as the player "player.xml":
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

		//ROOT NODE
		xml_node<> *root = xmlDoc.allocate_node(node_element, player.name.c_str()); //Generates a node for the playername.
		root->name(player.name.c_str()); //Sets the name of the node, same as the inserted player name.
		xmlDoc.append_node(root); //Joins the node to inside of the document.

		//CHILD NODE PLAYERNAME
		xml_node<>* childName = xmlDoc.allocate_node(node_element, "Name"); //Generates child score node.
		childName->value(player.name.c_str()); //Sets the value inside this node to the previously parsed to string, int score.
		root->append_node(childName); //Sets the node inside the root node.

		//CHILD NODE PLAYER SCORE
		xml_node<>* childScore = xmlDoc.allocate_node(node_element, "Score"); //Generates child score node.
		childScore->value(theScore.c_str()); //Sets the value inside this node to the previously parsed to string, int score.
		root->append_node(childScore); //Sets the node inside the root node.

		//CHILD NODE ACHIEVEMENT 1
		xml_node<>* childAchievement1 = xmlDoc.allocate_node(node_element, "Achievement1"); //Generates child achievements node.
		childAchievement1->value(theA1.c_str()); //Same as with previous child node.
		root->append_node(childAchievement1); // ""

		//CHILD NODE ACHIEVEMENT 2
		xml_node<>* childAchievement2 = xmlDoc.allocate_node(node_element, "Achievement2");
		childAchievement2->value(theA2.c_str());
		root->append_node(childAchievement2);
		
		//CHILD NODE ACHIEVEMENT 3
		xml_node<>* childAchievement3 = xmlDoc.allocate_node(node_element, "Achievement3");
		childAchievement3->value(theA3.c_str());
		root->append_node(childAchievement3);
		
		//CHILD NODE ACHIEVEMENT 4
		xml_node<>* childAchievement4 = xmlDoc.allocate_node(node_element, "Achievement4");
		childAchievement4->value(theA4.c_str());
		root->append_node(childAchievement4);
		
		//CHILD NODE ACHIEVEMENT 5
		xml_node<>* childAchievement5 = xmlDoc.allocate_node(node_element, "Achievement5");
		childAchievement5->value(theA5.c_str());
		root->append_node(childAchievement5);

		//WRITING THE VIRTUAL XML DOCUMENT ONTO THE FILE, again THROUGH FileIO:
		playerdata.open(RESOURCE_FILE(player.name));
		playerdata << xmlDoc;
		playerdata.close();
		xmlDoc.clear();


	}

	//Function which recieves the name of a player, and extracts a Player struct with all the requested data:
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
		Player player[10];

		int i = 0;
			
		for (std::list<Player>::iterator it = ranking.begin(); it != ranking.end(); ++it) {
			player[i].name = it->name;
			player[i].score = it->score;
			i++;
		}

		// Simple File IO for GENERATING THE PLAYER'S FILE:
		string r = "Ranking";
		ofstream playerdata;
		playerdata.open(RESOURCE_FILE(r));
		playerdata.close();

		//VIRTUALLY GENERATING XML DOCUMENT + Parsing is done if file already exists:
		file<> xmlFile(RESOURCE_FILE(r)); //loads file to an XML file variable
		xml_document<> xmlDoc; //Creates memory space for XML document
		xmlDoc.parse<parse_no_data_nodes>(xmlFile.data()); //Parses "doc", and assigns the content "data()" from "xmlFile". With the singularity that we are parsing no nodes (lol).

														   //GENERATING NODES FOR THE VIRTUAL XML DOCUMENT:
														   //The first node we want to generate is the declaration node, so it should look like this inside the file: <?xml version="1.0" encoding="UTF-8"?>
		xml_node<> *declaration = xmlDoc.allocate_node(node_declaration); //Generates a node, which is allocated inside the xmlDoc. node_declaration is the enum node kind.
		declaration->append_attribute(xmlDoc.allocate_attribute("version", "1.0")); //Creates an attribute for the previously generated node.
		declaration->append_attribute(xmlDoc.allocate_attribute("encoding", "utf-8")); //Creates a second attribute.
		xmlDoc.append_node(declaration); //This actually sets the previously generated node as first child node inside the file. According to documentation.

		xml_node<> *root = xmlDoc.allocate_node(node_element, "ranking"); //Generates a node for the playername.
		root->name("ranking"); //Sets the name of the node, same as the inserted player name.
		xmlDoc.append_node(root); //Joins the node to inside of the document.

		///////////////////////
		int j = 0;
		string theScore1 = to_string(player[j].score).c_str();
		string n1 = "Name" + to_string(j);
		string s1 = "Score" + to_string(j);

		xml_node<> *name1 = xmlDoc.allocate_node(node_element, n1.c_str()); //Generates a node for the playername.
		name1->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name1); //Joins the node to inside of the document.

		xml_node<> *score1 = xmlDoc.allocate_node(node_element, s1.c_str()); //Generates a node for the playername.
		score1->value(theScore1.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score1); //Joins the node to inside of the document.
		////////////////////
		j += 1;
		string theScore2 = to_string(player[j].score).c_str();
		string n2 = "Name" + to_string(j);
		string s2 = "Score" + to_string(j);
		
		xml_node<> *name2 = xmlDoc.allocate_node(node_element, n2.c_str()); //Generates a node for the playername.
		name2->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name2); //Joins the node to inside of the document.

		xml_node<> *score2 = xmlDoc.allocate_node(node_element, s2.c_str()); //Generates a node for the playername.
		score2->value(theScore2.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score2); //Joins the node to inside of the document.
		
								   ////////////////////
		j += 1;
		string theScore3 = to_string(player[j].score).c_str();
		string n3 = "Name" + to_string(j);
		string s3 = "Score" + to_string(j);

		xml_node<> *name3 = xmlDoc.allocate_node(node_element, n3.c_str()); //Generates a node for the playername.
		name3->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name3); //Joins the node to inside of the document.

		xml_node<> *score3 = xmlDoc.allocate_node(node_element, s3.c_str()); //Generates a node for the playername.
		score3->value(theScore3.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score3); //Joins the node to inside of the document.

								   ////////////////////
		j += 1;
		string theScore4 = to_string(player[j].score).c_str();
		string n4 = "Name" + to_string(j);
		string s4 = "Score" + to_string(j);

		xml_node<> *name4 = xmlDoc.allocate_node(node_element, n4.c_str()); //Generates a node for the playername.
		name4->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name4); //Joins the node to inside of the document.

		xml_node<> *score4 = xmlDoc.allocate_node(node_element, s4.c_str()); //Generates a node for the playername.
		score4->value(theScore4.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score4); //Joins the node to inside of the document.

								   ////////////////////
		j += 1;
		string theScore5 = to_string(player[j].score).c_str();
		string n5 = "Name" + to_string(j);
		string s5 = "Score" + to_string(j);

		xml_node<> *name5 = xmlDoc.allocate_node(node_element, n5.c_str()); //Generates a node for the playername.
		name5->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name5); //Joins the node to inside of the document.

		xml_node<> *score5 = xmlDoc.allocate_node(node_element, s5.c_str()); //Generates a node for the playername.
		score5->value(theScore5.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score5); //Joins the node to inside of the document.

								   ////////////////////
		j += 1;
		string theScore6 = to_string(player[j].score).c_str();
		string n6 = "Name" + to_string(j);
		string s6 = "Score" + to_string(j);

		xml_node<> *name6 = xmlDoc.allocate_node(node_element, n6.c_str()); //Generates a node for the playername.
		name6->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name6); //Joins the node to inside of the document.

		xml_node<> *score6 = xmlDoc.allocate_node(node_element, s6.c_str()); //Generates a node for the playername.
		score6->value(theScore6.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score6); //Joins the node to inside of the document.

								   ////////////////////
		j += 1;
		string theScore7 = to_string(player[j].score).c_str();
		string n7 = "Name" + to_string(j);
		string s7 = "Score" + to_string(j);

		xml_node<> *name7 = xmlDoc.allocate_node(node_element, n7.c_str()); //Generates a node for the playername.
		name7->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name7); //Joins the node to inside of the document.

		xml_node<> *score7 = xmlDoc.allocate_node(node_element, s7.c_str()); //Generates a node for the playername.
		score7->value(theScore7.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score7); //Joins the node to inside of the document.

								   ////////////////////
		j += 1;
		string theScore8 = to_string(player[j].score).c_str();
		string n8 = "Name" + to_string(j);
		string s8 = "Score" + to_string(j);

		xml_node<> *name8 = xmlDoc.allocate_node(node_element, n8.c_str()); //Generates a node for the playername.
		name8->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name8); //Joins the node to inside of the document.

		xml_node<> *score8 = xmlDoc.allocate_node(node_element, s8.c_str()); //Generates a node for the playername.
		score8->value(theScore8.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score8); //Joins the node to inside of the document.

								   ////////////////////
		j += 1;
		string theScore9 = to_string(player[j].score).c_str();
		string n9 = "Name" + to_string(j);
		string s9 = "Score" + to_string(j);

		xml_node<> *name9 = xmlDoc.allocate_node(node_element, n9.c_str()); //Generates a node for the playername.
		name9->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name9); //Joins the node to inside of the document.

		xml_node<> *score9 = xmlDoc.allocate_node(node_element, s9.c_str()); //Generates a node for the playername.
		score9->value(theScore9.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score9); //Joins the node to inside of the document.

								   ////////////////////
		j += 1;
		string theScore10 = to_string(player[j].score).c_str();
		string n10 = "Name" + to_string(j);
		string s10 = "Score" + to_string(j);

		xml_node<> *name10 = xmlDoc.allocate_node(node_element, n10.c_str()); //Generates a node for the playername.
		name10->value(player[j].name.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(name10); //Joins the node to inside of the document.

		xml_node<> *score10 = xmlDoc.allocate_node(node_element, s10.c_str()); //Generates a node for the playername.
		score10->value(theScore10.c_str()); //Sets the name of the node, same as the inserted player name.
		root->append_node(score10); //Joins the node to inside of the document.

									  //WRITING THE VIRTUAL XML DOCUMENT ONTO THE FILE, again THROUGH FileIO:
		playerdata.open(RESOURCE_FILE(r));

		playerdata << xmlDoc;
		playerdata.close();
		xmlDoc.clear();
	}

	static list<Player> GetRanking(){
		list<Player> ranking;
		ranking.resize(10);

		Player playert[10];
		string r = "Ranking";

		try {
			rapidxml::file<> xmlFile(RESOURCE_FILE(r));
		}
		catch (exception e) {
			return ranking;
		}

		rapidxml::file<> xmlFile(RESOURCE_FILE(r)); //carreguem filename a un a variable file de XML
		rapidxml::xml_document<> doc; //creem un espai de memoria per a un document xml
		try {
			doc.parse<0>(xmlFile.data()); //parsejem doc i hi asignem el contingut (data()) de xmlFile
		}
		catch (rapidxml::parse_error err) {
			std::cout << err.what() << std::endl /*<< err.where() << std::endl*/;
			system("pause");
		}

		rapidxml::xml_node<> *root_node = doc.first_node("ranking"); //root node

		for (int i = 0; i < 10; i++) {
			string theName1 = "Name" + to_string(i);
			string theScore1 = "Score" + to_string(i);

			rapidxml::xml_node<> *nameAttr1 = root_node->first_node(theName1.c_str());
			playert[i].name = nameAttr1->value();

			rapidxml::xml_node<> *scoreAttr1 = root_node->first_node(theScore1.c_str()); //mateixa operacio
			playert[i].score = std::stoi(scoreAttr1->value());
		}
		int i = 0;
		for (std::list<Player>::iterator it = ranking.begin(); it != ranking.end(); ++it) {
			it->name = playert[i].name;
			it->score = playert[i].score;
			i++;
		}

		return ranking;
	}

	static void InsertResultInOrder(Player playerResult) { //<-Insert the new player result here

		list<Player> results = IOManager::GetRanking();
		if (results.empty()) results.emplace_front(playerResult); //If there's nothing, we set the results directly on first place.
		else {
			for (list<Player>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) { //"results" list iterator
				if (iterator->score < playerResult.score) { //when this condition is true means that the iterator is in the correct position
					results.insert(iterator, playerResult);
					results.resize(10); //This removes lower scores
					break;
				}
			}
		}
		IOManager::SetRanking(results);
	}
}