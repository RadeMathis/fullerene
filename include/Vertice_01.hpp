/* * *
 * Created by Rade Mathis for LaBRI
 * All right reserved by the LaBRI
 * * *
 * Version 1.1.0 ( 10/05/2015 )
 * * *
 * First Vertice(v1) implementation.
 * I don't know how will encapsulation result
 * I don't know if previous sentence make sens.
 * * */

#ifndef DEFINED_VERTICE_01_HPP
#define DEFINED_VERTICE_01_HPP

#include <iostream>
#include <exception>

#include "Vertice.hpp"

/* Here we consider a vertice as a list of neighborgs vertices */
class Vertice_01 : public Vertice {

  public:

    Vertice_01();
    Vertice_01(Vertice_01 const& s);
    Vertice_01(Vertice const* s);
    ~Vertice_01();
    Vertice* clone() const;
  	int getNbVoisins() const;
  	int getVoisin(int n) const; 
  		/* n is the nuber of the neighborg (0 <= n <= 5)
       * it return the position in the Graph's array of the wanted neighbour
       * it return -1 if it got a phantom neighbour (universe border) */
  	int const* getAllVoisins() const ;
  		/*!!!*\ It actally return a pointer on the the first int of an
				array of 6 Vertice*, arry who's an Vertice private attribute.
				You (I in fact) should use it safe, carrying about mem aloc */
  	void setVoisin(int n, int p);
    void addVoisin(int n, int p);
    void delVoisin(int n);
    int isXthVoisin(int n) const;
  	bool isMarked(int n) const; //0 <= n < 8, we got 8 marks
  	void mark(int n); //idem
  	void unmark(int n); //idem

  private:

    void afficher(std::ostream &stream) const;

    int m_nbVoisins;
    int m_voisins[6]; //we'll never have to treat more than 6 neightborgs
    bool m_marques[8]; //used in algorithm to mark vertices

};

class BadNeighborhoodException_01 : public std::exception {
  public:
    virtual const char* what() const throw();
};

#endif /* DEFINED_VERTICE_01_HPP */