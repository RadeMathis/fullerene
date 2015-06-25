/* * *
 * Createed by Rade Mathis for the LaBRI
 * All right reserved by the LaBRI
 * * *
 * v1.1.0 (13/05/2015)
 * * *
 * This is the first implementation of v1.Graph
 * * */

#ifndef INCLUDED_GRAPH_01_HPP
#define INCLUDED_GRAPH_01_HPP

#include <string>
#include <vector>
 
#include <Graph.hpp>
#include <Vertice_01.hpp>
#include <graphExceptions.hpp>

#define TAILLE_TABLEAU 256

class Graph_01 : public Graph {

  public:

    Graph_01();
    Graph_01(std::string dataFile); 
      //throw OpenFileFailureException if dataFile fail to open.
    Graph_01(Graph_01 const& g);
    Graph_01(Graph const* g);
    ~Graph_01(); //totest (Valgrind?)

    static Graph* readFromFile(std::string dataFile); //find a solution
    Graph* clone() const;

    int getNbSommets() const;
    int getNbPenta() const;
    int getNbQuadra() const;
    int ajouterSommet();
    void supprimerSommet(int n);
    Vertice* getSommet(int n) const;
    int reserverMarque();
    void libererMarque(int n);

    int distance(int v1, int v2) /*const*/; //totest
    void bienFormer(); //work in simple cases
    void initialiserPenta();
    void initialiserQuadri();
    void replierPenta(int v, int d); //work in simple cases
    void replierQuadri(int v, int d); //work in simple cases
    void writeInFile(std::string dataFile) const;

    bool isomorphe(Graph const& g) const;

  private:

    void relier(int v); //totest
    void replier(int v, int d, int type); //totest
    void relier(); //totest
    void completerADistance1(); //totest
    void completerADistance2(); //totest

    int m_nbSommets;
    int m_nbPenta;
    int m_nbQuadra;

    Vertice* m_sommets[TAILLE_TABLEAU];

    bool m_marquesReserves[8];


};


#endif /* INCLUDED_GRAPH_01_HPP */