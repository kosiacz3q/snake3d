#include "HighscoreHandler.h"

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "rapidXml/rapidxml.hpp"
#include "rapidXml/rapidxml_utils.hpp"
#include "rapidXml/rapidxml_print.hpp"

std::string Highscore::getName()
{
	return name;
}

std::string Highscore::getResult()
{
	return result;
}

void Highscore::setResult(int result)
{
	this->result = boost::lexical_cast<std::string>(result);
}

HighscoreHandler::HighscoreHandler()
{
	_highscores = std::vector<Highscore>();
}

HighscoreHandler::~HighscoreHandler()
{

}

void HighscoreHandler::loadAll()
{
	_highscores.clear();
	rapidxml::xml_document<> doc; //create xml_document object
	rapidxml::file<> xmlFile("data"); //open file
	doc.parse<0>(xmlFile.data()); //parse the contents of file
	rapidxml::xml_node<>* root = doc.first_node("root"); //find our root node
	rapidxml::xml_node<>* node1 = root->first_node("highscores")->first_node("highscore"); //->first_node("name"); //find our node1 node

	while (node1 != NULL)
	{
		this->add(Highscore(node1->first_node("name")->value(), boost::lexical_cast<int>(node1->first_node("result")->value())));
		node1 = node1->next_sibling();
	}

	sort();
}

std::vector<Highscore>& HighscoreHandler::getHighscores()
{
	return _highscores;
}

void HighscoreHandler::sort()
{
	std::sort(_highscores.begin(), _highscores.end(), [](Highscore x, Highscore y)
	{
		return boost::lexical_cast<int>(x.result ) > boost::lexical_cast<int>(y.result);
	});

	cut();
}

void HighscoreHandler::cut()
{
	while(_highscores.size() > 9)
	{
		_highscores.erase(_highscores.end() - 1);
	}
}

void HighscoreHandler::saveAll()
{
	rapidxml::xml_document<> doc;
	std::ofstream out("data");

// xml declaration node
	rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration); //allocate default xml declaration node
//apppend special attributes to it
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl); //finally, append node

//allocate root node
	rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "root"); //node element is the type of node
	doc.append_node(root);

	rapidxml::xml_node<>* rootHighscore = doc.allocate_node(rapidxml::node_element, "highscores");
	root->append_node(rootHighscore);

	BOOST_FOREACH( Highscore highscore, _highscores )
	{
		rapidxml::xml_node<>* nodeHighscore = doc.allocate_node(rapidxml::node_element, "highscore");
		rootHighscore->append_node(nodeHighscore);

		rapidxml::xml_node<>* nodeName = doc.allocate_node(rapidxml::node_element, "name");
		nodeName->value(highscore.name.c_str());
		nodeHighscore->append_node(nodeName);

		rapidxml::xml_node<>* nodeResult = doc.allocate_node(rapidxml::node_element, "result");
		nodeResult->value(highscore.result.c_str());
		nodeHighscore->append_node(nodeResult);
	}

	std::string xml_as_string;
	rapidxml::print(back_inserter(xml_as_string), doc); //print formatted XML to a string

	out << xml_as_string << "\0";
	out.close();
}

void HighscoreHandler::add(const Highscore newHighscore)
{
	_highscores.push_back(newHighscore);
	sort();
}

