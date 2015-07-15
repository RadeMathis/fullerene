/* * *
 * Createed by Rade Mathis for the LaBRI
 * All right reserved by the LaBRI
 * * *
 * v1.1.0 (13/05/2015)
 * * *
 * This is the first implementation of v1.Graph
 * * */

#pragma once

#include <string>
#include <vector>

#include <Graph.hpp>
#include <Vertice_01.hpp>
#include <graphExceptions.hpp>

#define TAILLE_TABLEAU 256

class Graph;

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
    int getNbQuadra() const;
    int getNbPenta() const;
    int ajouterSommet();
    void supprimerSommet(int n);
    Vertice* getSommet(int n) const;
    int reserverMarque();
    void libererMarque(int n);
    Iterator begin() const;
    Iterator end() const;

    int distance(int v1, int v2) /*const*/; //totest
    void bienFormer(); //work in simple cases
    void initialiserPenta();
    void initialiserQuadri();
    std::vector<int> peutReplierPenta(int v) const = 0;
    std::vector<int> peutReplierQuadri(int v) const = 0;
    void replierPenta(int v, int d); //work in simple cases
    void replierQuadri(int v, int d); //work in simple cases
    void writeInFile(std::string dataFile) const;
    bool isArkenMarked(int) const;
    void markArken();

    bool isomorphe(Graph* g) const; //totest, for real, realy
        //test it with serious... noob.
    int getCeinture(int array[][2]) const;//totest

  private:

    void relier(int v); //totest
    std::vector<int> peutReplier_(int v, int type);
    void replier(int v, int d, int type); //totest
    void relier(); //totest
    void completerADistance1(); //totest
    void completerADistance2(); //totest

    int next_(int indice) const;
    Vertice* element_ (int indice) const;

    int m_nbSommets;
    int m_nbPenta;
    int m_nbQuadra;

    Vertice* m_sommets[TAILLE_TABLEAU];

    bool m_marquesReserves[8];

};