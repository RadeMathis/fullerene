#include <iostream>
#include <string>

#include <Graph_01.hpp>
#include <functions.hpp>
#include <graphPrinter.hpp>
//#include <graphGenerator.hpp>

using namespace std;

int
main(void)
{
    Graph* g1 = new Graph_01();
    vector<int> v;
    g1->initialiserPenta();
    Graph* g2 = g1->replierPenta(6,3);
    Graph* g3 = g2-> replierPenta(7,0);
    Graph* g4 = g2-> replierPenta(7,3);
    if(g1)
        g1->writeInFile("cetExemple");
    if(g2)
        g2->writeInFile("detExemple");
    if(g3)
        g3->writeInFile("eetExemple");
    if(g4)
        g4->writeInFile("fetExemple");   
    graphPrinter("cetExemple");
    graphPrinter("detExemple");
    graphPrinter("eetExemple");
    graphPrinter("detExemple");

    delete g1;
    delete g2;

    return 0;
}