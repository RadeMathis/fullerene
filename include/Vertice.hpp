/* * *
 * Createed by Rade Mathis for the LaBRI
 * All right reserved by the LaBRI
 * * *
 * v1.0.0 (10/05/2015)
 * * *
 * This is an interface
 * This have to be considered as an inner class of Graph
 * A vertice will be considerered as a list of neighbours vertices.
 * Vertice will only be found in a graph, a graph will be an array.
 * So, neighbours will be represented by integers, their play in graph's array.
 * * */

#ifndef DEFINED_VERTICE_HPP
#define DEFINED_VERTICE_HPP

#include <iostream>

class Vertice{

  public:

    virtual ~Vertice() = 0;
    virtual  Vertice* clone() const = 0;
    virtual int getNbVoisins() const = 0;
    virtual int getVoisin(int n) const = 0; 
      // n is the nuber of the neighborg (0 <= n <= 5)
    virtual int const* getAllVoisins() const = 0;
      /*!!!*\ It actally return a pointer on the the first int of an
        array of 6 int, array who's an Vertice private attribute.
        You (I in fact) should use itsafe, carrying about mem aloc */
    virtual void setVoisin(int n, int p) = 0;
      // means that the p-th Vertice will be the n-th neighbour
    virtual void addVoisin(int n, int p) = 0;
      // same rules
    virtual void delVoisin(int n) = 0;
    virtual int isXthVoisin(int n) const = 0;
      // return the place we got the vertice 'n' as neighbour.
      // return -1 if 'n' isn't a neighbour of this vertice.
    virtual bool isMarked(int n) const = 0; //0 <= n < 8, we got 8 marks
    virtual void mark(int n) = 0; //idem
    virtual void unmark(int n) = 0; //idem
    virtual bool isArkenMarked() const = 0; //special mark, for arken.
    virtual void markArken() = 0;
    virtual void unmarkArken() = 0;

    friend std::ostream &operator<<( std::ostream &steam, Vertice const& s);

  private:

    virtual void afficher(std::ostream &stream) const = 0;

};

#endif /* DEFINED_VERTICE_HPP */