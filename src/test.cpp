#include <iostream>
#include <string>

#include <Graph_01.hpp>
#include <functions.hpp>
#include <graphPrinter.hpp>

using namespace std;

int
main(void)
{
    Graph* g1 = new Graph_01();
    Graph* g2 = new Graph_01();
    g1->initialiserPenta();
    g2->initialiserQuadri();
    ///g1->bienFormer();
    ///g2->bienFormer();
    g1->replierQuadri(6,3);
    g2->replierPenta(6,3);
    g1->replierPenta(17, 3);
    g2->replierPenta(17, 3); 
    cout << boolalpha << g1->isomorphe(g2) << endl;
    g1->writeInFile("g1");
    g2->writeInFile("g2");
    graphPrinter("g1");
    graphPrinter("g2");
    delete g1;
    delete g2;

    return 0;
}