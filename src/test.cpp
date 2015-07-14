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
    g1->replierPenta(1,3);
    cout << g1->getNbSommets() << endl;
    for(Iterator it = g1->begin(); it != g1->end(); ++it)
        cout << **it << endl;

    delete g1;
    delete g2;

    return 0;
}