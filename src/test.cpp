#include <iostream>
#include <string>

#include <Graph_01.hpp>
#include <functions.hpp>

using namespace std;

int
main(/*int argc, char *argv[]*/)
{
	Graph* g1 = Graph_01::readFromFile("premierTest.graph.data");
	Graph* g2 = g1->clone();
	g2->writeInFile("deuxiemeTest.graph.data");
	delete g1;
	delete g2;

	return 0;
}