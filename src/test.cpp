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
    g1->writeInFile("cetExemple");
    g2->writeInFile("detExemple");
    graphPrinter("cetExemple");
    graphPrinter("detExemple");



    delete g1;
    delete g2;

    return 0;
}