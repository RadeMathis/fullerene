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
    Graph* g2 = new Graph_01("isoPremTest.graph.data");
    g1->bienFormer();
    g2->bienFormer();
    /*graphPrinter("premierTest.graph.data");
    graphPrinter("isoPremTest.graph.data");*/
    cout << g1->isomorphe(g2) << endl;

    return 0;
}