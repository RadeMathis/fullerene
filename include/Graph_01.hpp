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
    void setNbQuadri_(int);
    int getNbQuadra() const;
    void setNbPenta_(int);
    int getNbPenta() const;
    int ajouterSommet();
    void supprimerSommet(Vertice* n);
    void supprimerSommet(int n);
    Vertice* getSommet(int n) const;
    int reserverMarque();
    void libererMarque(int n);
    Iterator begin() const;
    Iterator end() const;

    int distance(Vertice* v1, Vertice* v2) /*const*/; //totest
    int distance(int v1, int v2) /*const*/; //totest
    void bienFormer(); //work in simple cases
    void initialiserPenta();
    void initialiserQuadri();
    Graph* replierPenta(Vertice* v, int d) const; //work in simple cases
    Graph* replierPenta(int v, int d) const; //work in simple cases
    Graph* replierQuadri(Vertice* v, int d) const; //work in simple cases
    Graph* replierQuadri(int v, int d) const; //work in simple cases
    void writeInFile(std::string dataFile) const;
    bool isArkenMarked(Vertice*) const;
    bool isArkenMarked(int) const;
    void markArken();

    bool isomorphe(Graph* g) const; //totest, for real, realy
        //test it with serious... noob.
    int getCeinture(int array[][2]) const;//totest

  protected:
    

  private:

    void relier_(); //totest
    void relier_(int v); //totest
    Graph* replier_(int v, int d, int type) const; //totest
    void completerADistance1_(); //totest
    void completerADistance2_(); //totest

    int next_(int indice) const;
    Vertice* element_ (int indice) const;

    int m_nbSommets;
    int m_nbPenta;
    int m_nbQuadra;

    Vertice* m_sommets[TAILLE_TABLEAU];

    bool m_marquesReserves[8];

};