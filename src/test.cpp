#include <iostream>
#include <string>

#include <Graph_01.hpp>
#include <functions.hpp>
#include <graphPrinter.hpp>

using namespace std;

int
main(/*int argc, char *argv[]*/)
{
    Graph* g1 = new Graph_01("premierTest.graph.data");
    g1->bienFormer();
    g1->writeInFile("deuxiemeTest.graph.data");

    graphPrinter("deuxiemeTest.graph");

    return 0;
}