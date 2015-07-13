#include <Vertice_01.hpp>

Vertice_01::Vertice_01() : m_nbVoisins(0) , m_arkenMarque(0) {
    for(int i(0); i < 8; ++i)
        m_marques[i] = false;
}

Vertice_01::Vertice_01(Vertice_01 const& s) : m_nbVoisins(s.getNbVoisins()) {
    m_arkenMarque = s.isArkenMarked();
    for(int i(0); i < 8; ++i)
        m_marques[i] = false;
    for(int i(0); i < s.getNbVoisins(); ++i)
        m_voisins[i] = s.getVoisin(i);
}

Vertice_01::Vertice_01(Vertice const* s) : m_nbVoisins(s->getNbVoisins()) {
    m_arkenMarque = s->isArkenMarked();
    for(int i(0); i < 8; ++i)
        m_marques[i] = false;
    for(int i(0); i < s->getNbVoisins(); ++i)
        m_voisins[i] = s->getVoisin(i);
}

Vertice_01::~Vertice_01(){} //only statics variable, who cares?

Vertice* Vertice_01::clone() const {
    Vertice_01* out = new Vertice_01(this);
    return (Vertice*)out;
}

int Vertice_01::getNbVoisins() const {
    return m_nbVoisins;
}

int Vertice_01::getVoisin(int n) const {
    if(n < 0 || n >= getNbVoisins())
        throw BadNeighborhoodException_01();
    return m_voisins[n];
}

int const* Vertice_01::getAllVoisins() const {
    return &(m_voisins[0]); // == m_voisins ?
}

void Vertice_01::setVoisin(int n, int p){
    if(n >= getNbVoisins() || n < 0)
        throw BadNeighborhoodException_01();
    m_voisins[n] = p;
}

void Vertice_01::addVoisin(int n, int p){
    if(n < 0 || n > getNbVoisins() || n > 5)
        throw BadNeighborhoodException_01();
    for(int i(getNbVoisins()); i > n; --i)
        m_voisins[i] = m_voisins[i-1];
    m_voisins[n] = p;
    ++m_nbVoisins;
}

void Vertice_01::delVoisin(int n){
    if(n < 0 || n >= getNbVoisins())
        throw BadNeighborhoodException_01();
    for(int i(n); i < getNbVoisins() - 1; ++i)
        m_voisins[i] = m_voisins[i+1];
    --m_nbVoisins;
}

int Vertice_01::isXthVoisin(int n) const {
    for(int i(0); i < getNbVoisins(); ++i)
        if(getVoisin(i) == n)
            return i;
    return -1;
}

bool Vertice_01::isMarked(int n) const {
    return m_marques[n];
}

void Vertice_01::mark(int n){
    m_marques[n] = true;
}

void Vertice_01::unmark(int n){
    m_marques[n] = false;
}


void Vertice_01::afficher(std::ostream &stream) const {
    stream << "This vertex get " << getNbVoisins() ;
    if(getNbVoisins() < 0 || getNbVoisins() > 6)
        stream << " fucking source code maters!";
    else if(getNbVoisins() == 0 || getNbVoisins() == 1)
        stream << " neighbour." ;
    else
        stream << " neighbours." ;
}

bool Vertice_01::isArkenMarked() const {
    return m_arkenMarque;
}

void Vertice_01::markArken(){
    m_arkenMarque = true;
}

void Vertice_01::unmarkArken(){
    m_arkenMarque = false;
}

std::ostream& operator<<( std::ostream &out, Vertice const& vertex )
{
    vertex.afficher(out) ;
    return out;
}

const char* BadNeighborhoodException_01::what() const throw(){
    return "You're trying to acces an unaccessible neighbour of your vertex.\n"
           "Maybe less than 0th, more than its number of neighbours (+1).";
}