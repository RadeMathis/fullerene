/* * *
 * Createed by Rade Mathis for the LaBRI
 * All right reserved by the LaBRI
 * * *
 * v1.1.0 (13/05/2015)
 * * */

#include <fstream>

#include <Graph_01.hpp>
#include <functions.hpp>
#include <queue>

#define TAILLE_LIGNE_MAX 51 //assez arbitraire

Graph_01::Graph_01() : m_nbSommets(0), m_nbPenta(0), m_nbQuadra(0) {
    for(int i(0); i < 8; ++i)
        m_marquesReseves[i] = 0;
    for(int i(0); i < TAILLE_TABLEAU; ++i)
        m_sommets[i] = NULL;
}

Graph_01::Graph_01(std::string dataFile){
    ifstream dataStream(dataFile.c_str(), ios::in);
    if(! dataStream) 
    	throw OpenFileFailureException(dataFile);
    std::string lineBuffer;
    std::vector<std::string> sentenceBuffer;

    std::getline(dataStream, lineBuffer);
    sentenceBuffer = decouperString(lineBuffer);
    m_nbSommets = atoi(sentenceBuffer[0].c_str());
    m_nbPenta = atoi(sentenceBuffer[1].c_str());
    m_nbQuadra = atoi(sentenceBuffer[2].c_str());
    m_signature = stringToVectorInt(sentenceBuffer[3]);
    for(int i(0); i < 8; ++i)
        m_marquesReseves[i] = 0;

    for(int i(0); i < TAILLE_TABLEAU; ++i)
        m_sommets[i] = NULL; //on initialise le tableau.

    for(int i(0); i < m_nbSommets; ++i){
        std::getline(dataStream, lineBuffer);
        sentenceBuffer = decouperString(lineBuffer);
        thisVertice = atoi(sentenceBuffer[0].c_str());
        m_sommets[thisVertice] = new Vertice();
        for(int j(2); j < (2 + sentenceBuffer[1]); ++j){
            if(sentenceBuffer[j] == "none")
                m_sommets[thisVertice]->addVoisin(-1);
            m_sommets[thisVertice]->addVoisin(atoi(sentenceBuffer[j].c_str()));
        }
    }
}

Graph_01::Graph_01(Graph const& g) : m_nbSommets(g.m_nbSommets), 
        m_nbPenta(g.m_nbPenta), m_nbQuadra(g.m_nbQuadra) {
    for(int i(0); i < 8; ++i)
        m_marquesReseves[i] = 0;
    for(int i(0); i < TAILLE_TABLEAU; ++i)
        m_sommets[i] = g.m_sommets[i]->clone();
}

Graph* Graph_01::readFromFile(std::string dataFile){
    return new Graph_01(dataFile); //probably need a cast (Graph*)
}

Graph* Graph_01::clone() const {
    return new Graph_01(*this); // probably need a cast (Graph*)
}

int Graph_01::getNbSommets() const {
    return m_nbSommets;
}

int Graph_01::ajouterSommet(){
    int isFree(0);
    while(isFree < TAILLE_TABLEAU){
        if(m_sommets[isFree] == NULL){
            m_sommets[isFree] = new Vertice_01();
            ++m_nbSommets;
            return isFree;
        }
        ++isFree;
    }
    throw FullGraphException();
}


void Graph_01::supprimerSommet(int n){
    if(m_nbSommets[n] == NULL)
        throw NonExistentVerticeException(n);
    --m_nbSommets;
    if(m_sommets[n]->getNbVoisins() == 5)
        --m_nbPenta;
    if(m_sommets[n]->getNbVoisins() == 4)
        --m_nbQuadra;
    delete m_sommets[n];
    m_sommets[n] = NULL;
}

Vertice* Graph_01::getSommet(int n) const {
    if(m_nbSommets[n] == NULL)
        throw NonExistentVerticeException(n);
    return m_sommets[n];
}

int Graph_01::reserverMarque(){
    int reservation(0);
    while(reservation < 8){
        if(! m_marquesReseves[reservation]){
            m_marquesReseves[reservation] = true;
            return reservation;
        }
        ++reservation;
    }
    throw NoMoreMarksException();
}

void Graph_01::libererMarque(int n){
    m_marquesReseves[n] = false;
}

int Graph_01::distance(int v1, int v2) const { //stratum marked oigon algorithm
    queue<int> enCour;
    int distance = 0;
    int passed = reserverMarque();
    if(v1 == v2)
        return 0;
    else {
        enCour.push(-2); //stratum mark
        enCour.push(v1);
        getSommet(v1)->mark(passed); //we mark v1 as passed
    }
    while(! enCour.empty()){
        int va = enCour.pop(); //va for actaul vertice
        if(va == -2){ //if we are between 2 stratum
            ++distance;
            enCour.push(-2);
            continue;
        }
        int vaSize = getSommet(va)->getNbVoisins;
        int const* vaNeighbours = getSommet(va)->getVoisins();
        for(int i(0); i < vaSize; ++i){
            if(getSommet(vaNeighbours[i]) == -1)
                continue; // we don't wanna look about the border
            if(! getSommet(vaNeighbours[i])->isMarked(passed)){
                if(getSommet(vaNeighbours[i]) == v2){
                    libererMarque[passed];
                    return distance;
                }
                enCour.push(vaNeighbours[i]);
                getSommet(vaNeighbours[i])->mark();
            }
        }
    }
    libererMarque[passed];
    return -1; //There is no path between v1 and v2
}

void Graph_01::bienFormer(){
    relier();
    completerADistance2();
    boucherLesTrous(); //useless?
}

void Graph_01::intitialiserPenta(){
    m_nbSommets = 1;
    m_nbPenta = 1;
    for(int i(0); i < TAILLE_TABLEAU; ++i){

    }
    m_sommets[0] = new Vertice_01();
    for(int i(0); i < 5; ++i)
        m_sommets[0]->addVoisin(i, -1);
}

void Graph_01::initialiserQuadri(){
    m_nbSommets = 1;
    m_sommets[0] = new Vertice_01();
    for(int i(0); i < 4; ++i)
        m_sommets[0]->addVoisin(i, -1);
}


void Graph_01::replierPenta(int v, int d){
    replier(v, d, 5);
}

void Graph_01::replierQuadra(int v, int d){
    replier(v, d, 4);
}

void Graph_01::writeInFile(std::string dataFile) const {
    ofstream dataStream(dataFile.c_str(), ios::out | ios::trunc);
    if (! dataStream)
        throw OpenFileFailureException();
    dataStream << m_nbSommets << ' ' << m_nbPenta << ' ' << m_nbQuadra << ' '
               << vectorToString(m_ceinture) << std::endl;
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        if (m_sommets[i] == NULL)
            continue;
        dataStream << i ;
        for(int j(0); j < m_sommets[i]->getNbVoisins(); ++j)
            dataStream << ' ' << m_sommets[i]->getVoisin(j);
        dataStream << std::endl;
    }
}

void Graph_01::replier(int v, int d, int type){ //v: vertice, d: direction
  //First : Bend over "in stays".
    bool existRight = true;
    bool existLeft  = true;
    Vertice* origin = getSommet(v);
    Vertice*  right = NULL;
    Vertice*   left = NULL;
    int           r = origin->getVoisin(d);                    //right place
    int           l = origin->getVoisin((d + (6 - type)) % 6); // left place
    int  previous_r = v;
    int  previous_l = v;
    try {
        right = getSommet(r);
    } catch(NonExistentVerticeException &e) {
        existRight = false;
    }
    try {
        left = getSommet(l);
    } catch(NonExistentVerticeException &e) {
        existLeft = false;
    }
    while(existRight && existLeft){ //Bend over "in stays"
        int in_r = right->isXthVoisin(previous_r);//The way we came in r
        int in_l =  left->isXthVoisin(previous_l);//The way we came in l
      //(1) Break links from inside to right.
        Vertice* interne_1 = getSommet(right->getVoisin((in_r - 1) % 6));
        interne_1->setVoisin(interne_1->isXthVoisin(r), -1);
        Vertice* interne_2 = getSommet(right->getVoisin((in_r - 2) % 6));
        interne_2->setVoisin(interne_2->isXthVoisin(r), -1);
      //(2) Link right to left-outside.
        right->setVoisin((in_r -1) % 6, left->getVoisin((in_l - 1) % 6));
        right->setVoisin((in_r -2) % 6, left->getVoisin((in_l - 2) % 6));
      //(3) Link left-outside to right.
        Vertice* externe_1 = getSommet(left->getVoisin((in_l - 1) % 6));
        externe_1->setVoisin(externe_1->isXthVoisin(l), r);
        Vertice* externe_2 = getSommet(left->getVoisin((in_l - 2) % 6));
        externe_2->setVoisin(externe_2->isXthVoisin(l), r);
      //(4) Break links from left to left-outside.
        left->setVoisin((in_l - 1) % 6, -1);
        left->setVoisin((in_l - 2) % 6, -1);
      //(5) "Move" left and right to itterate.
        previous_r = r;
        previous_l = l;
        r = right->getVoisin((in_r + 3) % 6);
        l =  left->getVoisin((in_l + 3) % 6);
        try {
            right = getSommet(r);
        } catch(NonExistentVerticeException &e) {
            existRight = false;
        }
        try {
            left  = getSommet(l);
        } catch(NonExistentVerticeException &e) {
            existLeft = false;
        }
        if(existLeft && !existRight){
            Vertice* oldLeft = getSommet(previous_l);
            oldLeft->setVoisin(oldLeft->isXthVoisin(l), -1);
            getSommet(previous_r)->setVoisin((in_r + 3) % 6, l);
            left->setVoisin(in_l, previous_r);
            previous_l = previous_r; //need it for first while(existLeft) itter
        }
    }
    while(existRight){
        int in_r = right->isXthVoisin(previous_r);
      //(1) Break links from inside to right.
        Vertice* interne_1 = getSommet(right->getVoisin((in_r - 1) % 6));
        interne_1->setVoisin(interne_1->isXthVoisin(r), -1);
        Vertice* interne_2 = getSommet(right->getVoisin((in_r - 2) % 6));
        interne_2->setVoisin(interne_2->isXthVoisin(r), -1);
      //(2) Break links from right to inside.
        right->setVoisin((in_r - 1) % 6, -1);
        right->setVoisin((in_r - 2) % 6, -1);
      //(3) "Move" right to itterate.
        previous_r = r;
        r = right->getVoisin((in_r + 3) % 6);
        try{
            right = getSommet(r);
        } catch(NonExistentVerticeException &e) {
            existRight = false;
        }
    }
    while(existLeft){
        int in_l = left->isXthVoisin(previous_l);
      //(1) Break links from inside to left.
        Vertice* interne_1 = getSommet(left->getVoisin((in_l + 1) % 6));
        interne_1->setVoisin(interne_1->isXthVoisin(l), -1);
        Vertice* interne_2 = getSommet(left->getVoisin((in_l + 2) % 6));
        interne_2->setVoisin(interne_2->isXthVoisin(l), -1);
      //(2) Break links from left to inside.
        left->setVoisin((in_l + 1) % 6, -1);
        left->setVoisin((in_l + 2) % 6, -1);
      //(3) "Move" left to itterate.
        previous_l = l;
        l = left->getVoisin((in_l + 3) % 6);
        try{
            left = getSommet(l);
        } catch(NonExistentVerticeException &e) {
            existLeft = false;
        }
    }
  // Secondly : reduce v and delete what is useless.
    queue<int> toDel;
    toDel.push(origin->getVoisin((d + 1) % 6));
    for(int i(0); i < 6-type; ++i){
        Vertice* xi = getSommet(origin->getVoisin((d + 1) % 6));
        xi->setVoisin(xi->isXthVoisin(v), -1);
        origin->delVoisin((d + 1) % 6);
    }
    m_nbPenta  += (type == 5);
    m_nbQuadra += (type == 6);
    int isInQueue = reserverMarque();
    while(!queue.empty()){
        for(int i(0); i < 6; ++i){
            int neigh_place = getSommet(toDel.front())->getVoisin(i);
            Vertice* neigh = getSommet(neigh_place);
            if(neigh_place == -1 || neigh->isMarked(isInQueue))
                continue;
            neigh->setVoisin(neigh->isXthVoisin(toDel.front()), -1);
            toDel.push(getSommet(toDel.front())->getVoisin(i));
        }
        delete toDel.front();
        --m_nbSommets;
        toDel.pop();
    }
    relier();
}

void Graph_01::relier(){
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        if(m_sommets[i] == -1)
            continue;
        Vertice* v = getSommet(i);

        for(int j(0); j < 36 ; ++j){//We look every vertices, several times.
            if(v->getVoisin(j % 6) != -1)
                continue;
            if(v->getVoisin((j + 1) % 6) != -1) {
                Vertice* neigh = getSommet(v->getVoisin((j + 1) % 6));
                in_neigh = neigh->isXthVoisin(i);
                v->setVoisin(j % 6, neigh->getVoisin((in_neigh + 1) % 6));
            }
            if(v->getVoisin((j - 1) % 6) != -1) {
                Vertice* neigh = getSommet(v->getVoisin((j - 1) % 6));
                in_neigh = neigh->isXthVoisin(i);
                v->setVoisin(j % 6, neigh->getVoisin((in_neigh - 1) % 6));
            }
        }
    }
}

// TODO : replier() distance(1) distance(2)

/*** EXCEPTIONS ***/

OpenFileFailureException::OpenFileFailureException(std::string file) 
        : exception() , m_fileFailed(file) {}

const char* OpenFileFailureException::what() const throw(){
    return "Don't know why, but we were unable to open file : " + m_fileFailed;
}


const char* FullGraphException::what() const throw(){
    return "Sorry but this graph is only able to contain "
           + TAILLE_TABLEAU + " vertices.";
}

NonExistentVerticeException::NonExistentVerticeException(int place)
        : exception() , m_place(place) {}

const char* NonExistentVerticeException::what() const throw(){
    return "There isn't any vertice in place number " + m_place;
}


const char* NoMoreMarksException::what() const throw(){
    return "All the marks have been reserved, you can't get more, sorry.";
}