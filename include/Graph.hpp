/* * *
 * Createed by Rade Mathis for the LaBRI
 * All right reserved by the LaBRI
 * * *
 * v1.0.0 (13/05/2015)
 * * *
 * This is an interface
 * This class is 1:1 linked with class Vertice, who've been to be consider as
 * its inner class.
 * Considering here that a Vertice only make sens in a graph, vertices won't be
 * encapsulated in graphs.
 * * */

#pragma once 

#include <string>
#include <iterator>
#include <vector>

#include <Vertice.hpp>

class Vertice;
class Iterator; //Definied lower // Defini plus bas.

class Graph {
    friend class Iterator;

  public:
    /*** This constructors should be present in all implementations ***
     *** Ces constructeurs devraient etre dans toute implementation ***
     * Graph();
     * Graph(string dataFile);
     * Graph(Graph const& g);
     */
    virtual ~Graph();

    virtual Graph* clone() const = 0;
        /* Just return a pointer to a graph copy as in JAVA
         # Cree tout simplement un ecopie du graphe et retourne un pointeur
         # sur la copie. */ 
    virtual int getNbSommets() const = 0;
        /* Return how many vertice there are in the graph.
         # Retourne le nombre de sommet presents dans le grahe. */
    virtual void setNbQuadri_(int) = 0; // You should not use this, never.
    virtual int getNbQuadri() const = 0;
        /* Return/set the number of square in the graph.
         # Retourne/definit le nombre de quadrilat. presents dans le graphe.*/
    virtual void setNbPenta_(int) = 0; // You should not use this, never.
    virtual int getNbPenta() const = 0;
        /* Return/set the number of pentagon in the graph.
         # Retourne/definit le nombre de pentagones presents dans le graphe. */
    virtual int getCourbure() const = 0;
        /* Return the "curvature" degree (nbPenta + 2nbQuadri).
         # Retourne le degre de courbure (nbPenta + 2nbQUadri). */
    virtual int ajouterSommet() = 0;
        /* Ad an empty vertice in the graph, return the place it has been put.
         * throw FullGraphException if th eimplementation isn't able to contain
         * a new Vertice.
         # Rajoute un sommet vierge dans le graphe et retourne la place a la
         # quelle il a ete range. 
         # Lance une FullGraphException si l'implementation n'est pas capable
         # D'ajoutuer une nouveau sommmet. */
    virtual void supprimerSommet(Vertice* n) = 0;
    virtual void supprimerSommet(int n) = 0;
        /* Delete the n-th vertice and free the n-th place. /!\ care about the
         * fact there isn't any vertice knowing n as neighbour!
         * Can throws a NonExistentVerticeException.
         # Detruit le n-ieme sommet et libere la n-ieme place. /!\ Attention a
         # ce qu'il n'y ai plus aucun sommet considerant n comme son voisin! 
         # Peut lancer une NonExistentVerticeException. */
    virtual Vertice* getSommet(int n) const = 0;
        /* Return a pointer to the vertice at the n-th place in the graph.
         * Can throws a NonExistentVerticeException.
         # Retourne un pointeur sur le sommet range a la n-eme place. 
         # peut lancer une NonExistentVerticeException. */
    virtual int reserverMarque() = 0;
        /* Reserve a marker. It return a number you'll be able to use in 
         * Vertice's functions: bool isMarked(int), void mark(int) and 
         * void unmark(int). You'll have to free the mark (see below).
         * Throws a NoMoreMarksException if the implementation cannot deliver
         * more marks. (remember to free your marks)
         # Reserve un marqueur. Retourne un numero utilisable dans les methodes
         # de Vertice: bool isMarked(int), void mark(int) and void unmark(int).
         # Pensez a liberer le marqueur (voir la methode ci-dessous). 
         # Lance une NoMoreMarksException si l'implementation n'est pas capable
         # de delivrer plus de marques. (pensez a liberer vos marques) */
    virtual void libererMarque(int n) = 0;
        /* Free a reserved marker by above function.
         # Libere un markeur reserve par le methode ci-dessus. */
    virtual int distance(Vertice* v1, Vertice* v2) /*const*/ = 0;
    virtual int distance(int v1, int v2) /*const*/ = 0;
        /* Return distance between vertices in v1 and v2.
         * Return 0 if v1==v2, return 1 if they are neighbours ... etc ...
         * Return -1 if there isn't any path between v1 and v2.
         # Retourne la distance entre les sommets ranges en v1 et v2
         # Retourne 0 si v1 ==v2, retourn 1 s'ils sont voisins ... etc ... 
         # Retourne -1 s'il n'existe pas de chemin entre v1 et v2.*/
    virtual Iterator begin() const = 0;
        /* Return an iterator to "first" Vertice*.
         # retourne un iterateur sur le "premier" Vertice*. */
    virtual Iterator end() const = 0;
        /* Return an iterator to the "end", after "last" Vertice*.
         # Retourne un iterateur sur la "fin", après le "dernier" Vertice*. */
    virtual bool bienFormer() = 0;
        /* Put the graph "as he has to be" (see the "forme d'un graphe")
         * part of the manifest. Return false if it cannot form the graph.
         # Met le graphe en forme tel que decrit dans le manifest. 
         # Retourne false si on ne peut "bien former" le graphe. */
    virtual void initialiserPenta() = 0; 
        /* Create the graph composed of one pentagon.
         # Cree le grpahe compose d'un pentagone. */
    virtual void initialiserQuadri() = 0; 
        /* Create the graph composed of one square.
         # Cree le graphe compose d'un quadrilaltere. */
    virtual Graph* replierPenta(Vertice* v, int d) const = 0;
    virtual Graph* replierPenta(int v, int d) const = 0;
        /* Bend over "in stays" to form a pentagon as described in the manifest
         * v is the vertice to transform in pentagon
         * its merged neighbours will be the d-th abd the (d+1)mod(6)-th
         * If we can do that without toutching Arken, will return the formed
         * graph. Else, will return NULL. Will also return NULL if the graph
         * formed get two neighbored quadrilaterals.
         # Replie en corset pour former un pentagone comme ecrit dans les notes
         # v est le sommet a transformer en pentagone
         # ses voisins fusionnes seront le d-ieme et le (d+1)mod(6)-ieme.
         # Si on peut replier ainsi sans toucher a l'Arken, alors retourne le
         # graphe genere. Sinon, retourne NULL. Retourne aussi NULL si la graphe
         # genere contenait deux quadrilateres voisins. */
    virtual Graph* replierQuadri(Vertice* v, int d) const = 0;    
    virtual Graph* replierQuadri(int v, int d) const = 0;
        /* Bend over "in stays" to form a square as described in the manifest
         * v is the vertice to transform in quadrilateral
         * its merged neighbours will be the d-th abd the (d+2)mod(6)-th
         * If we can do that without toutching Arken, will return the formed
         * graph. Else, will return NULL. Will also return NULL if the graph
         * formed get two neighbored quadrilaterals.
         # Replie en corset pour former un carre comme ecrit dans le manifest
         # v est le sommet a transformer en quadrilaterre
         # ses voisins fusionnes seront le d-ieme et le (d+2)mod(6)-ieme.
         # Si on peut replier ainsi sans toucher a l'Arken, alors retourne le
         # graphe genere. Sinon, retourne NULL. Retourne aussi NULL si la graphe
         # genere contenait deux quadrilateres voisins. */
    virtual void writeInFile(std::string dataFile) const = 0;
        /* Write the graph in a .graph.data file as described in the manifest.
         * Can throw an OpenFaileFailurException.
         # Ecrit le graphe dans un fichier .graph.data comme decrit dans le
         # manifest. 
         # peut lancer une OpenFileFailureException. */
    virtual bool isArkenMarked(Vertice* v) const = 0;
    virtual bool isArkenMarked(int v) const = 0;
        /* Return true if the parameter's passed vertice is arkenMarked.
         # retourne vrai si the sommet passe en parametre est arkenMarque. */
    virtual void markArken() = 0;
        /* All the Vertice in the Arken will be arkenMarked. (see manifest).
         # Tout les sommets de l'arken seront arkenMarqués. (cf manifest).*/
    virtual bool isomorphe(Graph* g) const = 0;
        /* Return true if this and g are isomorph. Else, return false.
         # Retourne true si this et g sont isomorphes. false sinon. */

//should be protected: don't know why I cannot:
    virtual int getCeinture(int array[][2]) const = 0;
        // Calculate the graph's belt, put it in array. Return belt's size.
        // Array should be int[TAILLE_TABLEAU][2] minimum.

  protected:

  private:

    virtual int next_(int indice) const = 0;
    virtual Vertice* element_ (int indice) const = 0;

};

class Iterator : std::iterator<std::random_access_iterator_tag, Vertice*> {

  public:

    Iterator(Graph* g, int indice);
    Iterator & operator++();
    bool operator!=(Iterator const&) const;
    Vertice* operator*() const;

  private:

    Graph* g_;
    int indice_;

};