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
    cout << "1  " << g2->reserverMarque() << endl;
    cout << "2  " << g2->reserverMarque() << endl;
    cout << "3  " << g2->reserverMarque() << endl;
    cout << "4  " << g2->reserverMarque() << endl;
    cout << "5  " << g2->reserverMarque() << endl;
    cout << "6  " << g2->reserverMarque() << endl;
   	cout << "7  " << g2->reserverMarque() << endl;
    cout << "8  " << g2->reserverMarque() << endl;
	cout << "9  " << g2->reserverMarque() << endl;
	

    g2->writeInFile("deuxiemeTest.graph.data");
    delete g1;
    delete g2;

    return 0;
}