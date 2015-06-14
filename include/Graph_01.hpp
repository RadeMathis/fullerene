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
#include <exception>
 
#include <Graph.hpp>
#include <Vertice_01.hpp>

#define TAILLE_TABLEAU 256

class Graph_01 : public Graph {

  public:

    Graph_01();
    Graph_01(std::string dataFile); 
      //throw OpenFileFailureException if dataFile fail to open.
    Graph_01(Graph const& g);
    ~Graph_01();

    static Graph* readFromFile(std::string dataFile);
    Graph* clone() const;

    int getNbSommets() const;
    int ajouterSommet();
    void supprimerSommet(int n);
    Vertice* getSommet(int n) const;
    int reserverMarque();
    void libererMarque(int n);

    int distance(int v1, int v2) const ;
    void bienFormer();
    void intitialiserPenta();
    void intitialiserQuadri();
    void replierPenta(int v, int d);
    void replierQuadri(int v, int d);
    void writeInFile(std::string dataFile) const;

  private:

    void replier(int v, int d, int type);
    void relier(int v);
    void relier();
    void completerADistance1();
    void completerADistance2();

    int m_nbSommets;
    int m_nbPenta;
    int m_nbQuadra;

    Vertice* m_sommets[TAILLE_TABLEAU];

    bool m_marquesReserves[8];


};

/*** EXCEPTIONS ***/

class OpenFileFailureException : public std::exception {
  public:
    OpenFileFailureException(string file);
    const char* what() const throw();
  private:
    string m_fileFailed;
};

class FullGraphException : public std::exception {
  public:
    const char* what() const throw();
};

class NonExistentVerticeException : public std::exception {
  public:
    NonExistentVerticeException(int place);
    const char* what() const throw();
  private:
    int m_place;
};

class NoMoreMarksException : public std::exception {
  public:
    const char* what() const throw();
};

#endif /* INCLUDED_GRAPH_01_HPP */