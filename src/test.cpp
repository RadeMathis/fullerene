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
    Graph* g2 = new Graph_01();
    vector<int> v;
    g1->initialiserPenta();
    g2->initialiserQuadri();
    g1->replierPenta(6,3);
    g1->writeInFile("cetExemple");
    graphPrinter("cetExemple");
    v = g1->peutReplierQuadriAll(0); 
    cout << 0 << ' ' << g1->peutReplierQuadri(0) << endl;
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';
    cout << endl;
    v = g1->peutReplierQuadriAll(1); 
    cout << 1 << ' ' << g1->peutReplierQuadri(1) << endl;
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';
    cout << endl;
    v = g1->peutReplierQuadriAll(5); 
    cout << 5 << ' ' << g1->peutReplierQuadri(5) << endl;
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';
    cout << endl;
    v = g1->peutReplierQuadriAll(7); 
    cout << 7 << ' ' << g1->peutReplierQuadri(7) << endl;
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';
    cout << endl;
    v = g1->peutReplierQuadriAll(19); 
    cout << 19 << ' ' << g1->peutReplierQuadri(19) << endl;
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';
    cout << endl;
    cout << g1->getSommet(19)->getVoisin(0) << endl;


    delete g1;
    delete g2;

    return 0;
}