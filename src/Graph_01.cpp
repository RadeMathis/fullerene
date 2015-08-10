/* * *
 * Createed by Rade Mathis for the LaBRI
 * All right reserved by the LaBRI
 * * *
 * v1.1.0 (13/05/2015)
 * * */

#include <Graph_01.hpp>

#include <fstream>
#include <ctime>
#include <queue>
#include <array>
#include <string>
#include <exception>

#include <functions.hpp>

#define TAILLE_LIGNE_MAX 51 //assez arbitraire


Graph_01::Graph_01() : m_nbSommets(0), m_nbPenta(0), m_nbQuadra(0) {
    for(int i(0); i < 8; ++i)
        m_marquesReserves[i] = false;
    for(int i(0); i < TAILLE_TABLEAU; ++i)
        m_sommets[i] = NULL;
}

Graph_01::Graph_01(std::string dataFile){
    std::string fileName = dataFile + ".graph.data";
    std::ifstream dataStream(fileName.c_str(), std::ios::in);
    if(! dataStream) 
    	throw OpenFileFailureException(fileName);
    std::string lineBuffer;
    std::vector<std::string> sentenceBuffer;

    std::getline(dataStream, lineBuffer);
    sentenceBuffer = decouperString(lineBuffer);
    m_nbSommets = atoi(sentenceBuffer[0].c_str());
    m_nbPenta = atoi(sentenceBuffer[1].c_str());
    m_nbQuadra = atoi(sentenceBuffer[2].c_str());
    for(int i(0); i < 8; ++i)
        m_marquesReserves[i] = 0;

    for(int i(0); i < TAILLE_TABLEAU; ++i)
        m_sommets[i] = NULL; //on initialise le tableau.

    for(int i(0); i < m_nbSommets; ++i){
        std::getline(dataStream, lineBuffer);
        sentenceBuffer = decouperString(lineBuffer);
        int thisVertice = atoi(sentenceBuffer[0].c_str());
        m_sommets[thisVertice] = new Vertice_01(this, thisVertice);
        for(int j(2); j < (2 + atoi(sentenceBuffer[1].c_str())); ++j){
            if(sentenceBuffer[j] == "none")
                m_sommets[thisVertice]->addVoisin(j -2, -1);
            m_sommets[thisVertice]->addVoisin(j - 2, 
                                            atoi(sentenceBuffer[j].c_str()));
        }
        if(atoi(sentenceBuffer[atoi(sentenceBuffer[1].c_str()) + 2].c_str()))
            m_sommets[thisVertice]->markArken();
    }
}

Graph_01::Graph_01(Graph_01 const& g) : m_nbSommets(g.getNbSommets()), 
        m_nbPenta(g.getNbPenta()), m_nbQuadra(g.getNbQuadri())
{
    for(int i(0); i < 8; ++i)
        m_marquesReserves[i] = 0;
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        try{
            Graph const* g_ptr = &g;
            m_sommets[i] = g.getSommet(i)->clone(g_ptr, i);
        } catch(NonExistentVerticeException &e) {
            m_sommets[i] = NULL;
        }
    }
}

Graph_01::Graph_01(Graph const* g) : m_nbSommets(g->getNbSommets()), 
        m_nbPenta(g->getNbPenta()), m_nbQuadra(g->getNbQuadri()) 
{
    for(int i(0); i < 8; ++i)
        m_marquesReserves[i] = 0;
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        try{
            m_sommets[i] = g->getSommet(i)->clone(g, i);
        } catch(NonExistentVerticeException &e) {
            m_sommets[i] = NULL;
        }
    }
}

Graph_01::~Graph_01(){
    for(int i(0); i < TAILLE_TABLEAU; ++i)
        if(m_sommets[i] != NULL)
            delete m_sommets[i];
}

Graph* Graph_01::readFromFile(std::string dataFile){
    return new Graph_01(dataFile); //probably need a cast (Graph*)
}

Graph* Graph_01::clone() const {
    return new Graph_01(this); // probably need a cast (Graph*)
}

int Graph_01::getNbSommets() const {
    return m_nbSommets;
}

void Graph_01::setNbQuadri_(int n) {
    m_nbQuadra = n;
}

int Graph_01::getNbQuadri() const {
    return m_nbQuadra;
}

void Graph_01::setNbPenta_(int n) {
    m_nbPenta = n;
}

int Graph_01::getNbPenta() const {
    return m_nbPenta;
}

int Graph_01::getCourbure() const {
    return m_nbPenta + 2*m_nbQuadra;
}

int Graph_01::ajouterSommet(){
    int isFree(0);
    while(isFree < TAILLE_TABLEAU){
        if(m_sommets[isFree] == NULL){
            m_sommets[isFree] = new Vertice_01(this, isFree);
            ++m_nbSommets;
            return isFree;
        }
        ++isFree;
    }
    throw FullGraphException(TAILLE_TABLEAU);
}

void Graph_01::supprimerSommet(Vertice* n){
    supprimerSommet(n->getPlaceInGraph());
}

void Graph_01::supprimerSommet(int n){
    if(n < 0 || n > TAILLE_TABLEAU || m_sommets[n] == NULL)
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
    if(n < 0 || n >= TAILLE_TABLEAU || m_sommets[n] == NULL)
        throw NonExistentVerticeException(n);
    return m_sommets[n];
}

int Graph_01::reserverMarque(){
    int reservation(0);
    while(reservation < 8){
        if(! m_marquesReserves[reservation]){
            m_marquesReserves[reservation] = true;
            return reservation;
        }
        ++reservation;
    }
    throw NoMoreMarksException();
}

void Graph_01::libererMarque(int n){
    m_marquesReserves[n] = false;
}

Iterator Graph_01::begin() const{
    int i(0);
    while(m_sommets[i] == NULL)
        ++i;
    return Iterator((Graph*)this, i);
}

Iterator Graph_01::end() const{
    return Iterator((Graph*)this, TAILLE_TABLEAU);
}

int Graph_01::distance(Vertice* v1, Vertice* v2) {
    return distance(v1->getPlaceInGraph(), v2->getPlaceInGraph());
}
int Graph_01::distance(int v1, int v2)/*const*/ { //stratum marked oigon algorithm
    std::queue<int> enCour;
    int distance = 0;
    int passed = reserverMarque();
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* vi;
        try{
            vi = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        vi->unmark(passed);
    }
    if(v1 == v2)
        return 0;
    else {
        enCour.push(-2); //stratum mark
        enCour.push(v1);
        getSommet(v1)->mark(passed); //we mark v1 as passed
    }
    while(true){ // real stop condition 4 lines below (enCour.empty())
        int va = enCour.front(); //va for actual vertice
        enCour.pop();
        if(va == -2){ //if we are between 2 stratum
            if(enCour.empty())
                break;
            ++distance;
            enCour.push(-2);
            continue;
        }
        int vaSize = getSommet(va)->getNbVoisins();
        int const* vaNeighbours = getSommet(va)->getAllVoisins();
        for(int i(0); i < vaSize; ++i){
            if(vaNeighbours[i] == -1)
                continue; // we don't wanna look about the border
            if(! getSommet(vaNeighbours[i])->isMarked(passed)){
                if(vaNeighbours[i] == v2){
                    libererMarque(passed);
                    return distance;
                }
                enCour.push(vaNeighbours[i]);
                getSommet(vaNeighbours[i])->mark(passed);
            }
        }
    }
    libererMarque(passed);
    return -1; //There is no path between v1 and v2
}

bool Graph_01::bienFormer(){
    if(deuxQuadriColles_())
        return false;
    relier_();
    completerADistance2_();
    markArken();
    relier_();
    return true;
}

void Graph_01::initialiserPenta(){
    if(getNbSommets())
        for(int i(0); i < TAILLE_TABLEAU; ++i){
            try{
                supprimerSommet(i);
            } catch(...) {}
        }
    int place = ajouterSommet();
    Vertice* sommet = getSommet(place);
    for(int i(0); i < 5; ++i)
        sommet->addVoisin(i, -1);
    setNbPenta_(1);
    bienFormer();
}

void Graph_01::initialiserQuadri(){
    if(getNbSommets())
        for(int i(0); i < TAILLE_TABLEAU; ++i){
            try{
                supprimerSommet(i);
            } catch(...) {}
        }
    int place = ajouterSommet();
    Vertice* sommet = getSommet(place);
    for(int i(0); i < 4; ++i)
        sommet->addVoisin(i, -1);
    setNbQuadri_(1);
    bienFormer();
}

Graph* Graph_01::replierPenta(Vertice* v, int d) const {
    return replierPenta(v->getPlaceInGraph(), d);
}

Graph* Graph_01::replierPenta(int v, int d) const {
    return replier_(v, d, 5);
}

Graph* Graph_01::replierQuadri(Vertice* v, int d) const {
    return replierQuadri(v->getPlaceInGraph(), d);
}

Graph* Graph_01::replierQuadri(int v, int d) const {
    return replier_(v, d, 4);
}

void Graph_01::writeInFile(std::string dataFile) const {
    std::string fileName = dataFile + ".graph.data";
    std::ofstream dataStream(fileName.c_str(), std::ios::out | std::ios::trunc);
    if (! dataStream)
        throw OpenFileFailureException(fileName);
    dataStream << m_nbSommets <<' '<< m_nbPenta <<' '<< m_nbQuadra << std::endl;
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        if (m_sommets[i] == NULL)
            continue;
        dataStream << i << ' ' << m_sommets[i]->getNbVoisins();
        for(int j(0); j < m_sommets[i]->getNbVoisins(); ++j)
            dataStream << ' ' << m_sommets[i]->getVoisin(j);
        dataStream << ' ' << m_sommets[i]->isArkenMarked() << std::endl;
    }
}

bool Graph_01::isArkenMarked(Vertice* v) const {
    return v->isArkenMarked();
}

bool Graph_01::isArkenMarked(int v) const {
    return getSommet(v)->isArkenMarked();
}

void Graph_01::markArken()
{
    // D'abord, dans le doute, on demarque tout.
    // C'est peut etre inutile, je verrai ca plus tard.
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* vi;
        try{
            vi = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        vi->unmarkArken();
    }
    std::vector<int> indiceDistances; //see below
    std::vector<std::array<int, TAILLE_TABLEAU>> distances; //see below
        //distance[x][y] is the distance between indiceDistances[x] and y.
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* vi;
        try{
            vi = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        if(vi->getNbVoisins() == 6)
            continue;
        std::array<int, TAILLE_TABLEAU> distanceToVi;
        std::queue<int> oignon; //for stratum marked oignon algorithm (manifest)
        int isInQueue = reserverMarque();
        for(int j(0); j < TAILLE_TABLEAU; ++j){
            Vertice* vj;
            try{
                vj = getSommet(j);
            } catch(NonExistentVerticeException &e) {
                continue;
            }
            vj->unmark(isInQueue);
        }
        int actualDistance = 0;
        oignon.push(i);
        vi->mark(isInQueue);
        oignon.push(-1); //<-- This is the stratum marker.
        while(true){ //real stop condition 3 lines below (oignon.empty())
            if(oignon.front() == -1){
                oignon.pop();
                if(oignon.empty())
                    break;
                oignon.push(-1);
                ++actualDistance;
                continue;
            }
            distanceToVi[oignon.front()] = actualDistance;
            Vertice* vFront = getSommet(oignon.front());
            oignon.pop();
            for(int j(0); j < vFront->getNbVoisins(); ++j){
                if(vFront->getVoisin(j) == -1)
                    continue;
                Vertice* vj = getSommet(vFront->getVoisin(j));
                if(! vj->isMarked(isInQueue)){
                    vj->mark(isInQueue);
                    oignon.push(vFront->getVoisin(j));
                }
            }
        }
        libererMarque(isInQueue);
        indiceDistances.push_back(i);
        distances.push_back(distanceToVi);
    }
    for(int i(0); i < TAILLE_TABLEAU; ++i){ //for in sommets
        Vertice* vi;
        try{
            vi = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        if(vi->getNbVoisins() == 5 || vi->getNbVoisins() == 4){
            vi->markArken();
            continue;
        }
        for(unsigned int j(1); j < distances.size(); ++j){ //for in special sommets
            for(unsigned int k(0); k < j; ++k){ //for in special sommets ^2
                int dist_ij = distances[j][i];
                int dist_ik = distances[k][i];
                int dist_jk = distances[k][indiceDistances[j]];
                if(dist_ij + dist_ik == dist_jk){
                    vi->markArken();
                    goto LABEL_GRAPH_01_MARK_ARKEN_END_OF_FOR_J;
                } 
            }
        } LABEL_GRAPH_01_MARK_ARKEN_END_OF_FOR_J:;
    }
}

bool Graph_01::isomorphe(Graph* g) const{
    Graph_01* thisSym = mirrorGraph_();
    bool mirroirIso = thisSym->isomorpheSimple_(g);
    delete thisSym;
    return(isomorpheSimple_(g) || mirroirIso);
}

bool Graph_01::isomorpheSimple_(Graph* g) const {
    if(getNbSommets() != g->getNbSommets())
        return false;
    if(getNbQuadri() != g->getNbQuadri())
        return false;
    if(getNbPenta() != g->getNbPenta())
        return false;
    int ceintureThis[TAILLE_TABLEAU][2];
    int    ceintureG[TAILLE_TABLEAU][2];
    // each element get: [0]: place of a belt's Vertice, [1]: nb of -1 neigh.
    int sizeBeltThis = getCeinture(ceintureThis);
    int    sizeBeltG = g->getCeinture(ceintureG);
    if(sizeBeltThis != sizeBeltG)
        return false;
    std::vector<int> gaps = arrayEgalsCycle(ceintureThis, ceintureG, sizeBeltG);
    //for it in "ecart possible au niveau de l'== de ceinture"
    for (std::vector<int>::iterator it = gaps.begin(); it != gaps.end(); ++it){
        int isomorphisme[TAILLE_TABLEAU]; //Tableau des antecedants-image
        for(int j(0); j < TAILLE_TABLEAU; ++j)
            isomorphisme[j] = -1;
        for(int j(0); j < sizeBeltG; ++j){
            int image = ceintureG[(j + (*it)) % sizeBeltG][0];
            isomorphisme[ceintureThis[j][0]] = image;
        }
        bool continuer = true;
        //while on trouve des truc en commun
        while(continuer){
            continuer = false;
                //On continuera si on trouve un truc dans la boucle
            //for j in "les sommets de *this"
            for(int j(0); j < TAILLE_TABLEAU; ++j){
                Vertice* vj;
                try{
                    vj = getSommet(j);
                } catch(NonExistentVerticeException &e) {
                    continue;
                }
                if(isomorphisme[j] != -1)
                    continue;
                int nbTreatedVoisins = 0;
                std::vector<int> treatedVoisins;
                for(int k(0); k < vj->getNbVoisins(); ++k)
                    if(isomorphisme[vj->getVoisin(k)] != -1){
                        treatedVoisins.push_back(vj->getVoisin(k));
                        ++nbTreatedVoisins;
                    }else 
                        treatedVoisins.push_back(-1);
                if(nbTreatedVoisins < 3)
                    continue;
                std::vector<int>treatedVoisinsIso;
                int aTreatedVoisin;
                for(std::vector<int>::iterator kt = treatedVoisins.begin();
                                              kt != treatedVoisins.end(); ++kt)
                    if(*kt != -1){
                        treatedVoisinsIso.push_back(isomorphisme[*kt]);
                        aTreatedVoisin = *kt;
                    }
                    else
                        treatedVoisinsIso.push_back(-1);
                Vertice* isoATrVsn = g->getSommet(isomorphisme[aTreatedVoisin]);
                //for k in isoATrVsn's voisins (we serach j's image)
                for(int k(0); k < isoATrVsn->getNbVoisins(); ++k){
                    Vertice* vk;
                    try{
                        vk = g->getSommet(isoATrVsn->getVoisin(k));
                    } catch(NonExistentVerticeException &e) {
                        continue;
                    }
                    std::vector<int> isoVoisins;
                    for(int l(0); l < vk->getNbVoisins(); ++l)
                        isoVoisins.push_back(vk->getVoisin(l));
                    if(sameTreatedVoisins(treatedVoisinsIso, isoVoisins)){
                        isomorphisme[j] = isoATrVsn->getVoisin(k);
                        continuer = true;
                        break; //On a trouve et ajoute le voisin cherche.
                    }
                }
            }                
        }
        bool isomorphIsComplete = true;
        for(int j(0); j < TAILLE_TABLEAU; ++j){ //test if we get isomorphisme
            try{ 
                getSommet(j);
            }
            catch(NonExistentVerticeException &e){
                continue;
            }
            if(isomorphisme[j] == -1)
                isomorphIsComplete = false;
        }
        if(isomorphIsComplete)
            return true; 
    }
    return false;
}

Graph* Graph_01::replier_(int v, int d, int type) const { //v: vertice, d: direc.
  Graph* g = clone();
  try{ //Voir si on peut pas virer cette merde
  //First : Bend over "in stays".
    bool existRight = true;
    bool  existLeft = true;
    Vertice* origin = g->getSommet(v);
    if(origin->isArkenMarked()) {
        delete g;
        return NULL; 
    }
    Vertice*  right = NULL;
    Vertice*   left = NULL;
    int           r = origin->getVoisin(d);                    //right place
    int           l = origin->getVoisin((d + (6 - type)) % 6); // left place
    int  previous_r = v;
    int  previous_l = v;
    std::queue<int> toDel;
    int   isInQueue = g->reserverMarque();
    int inCicatrice = g->reserverMarque();
    origin->mark(inCicatrice);
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* vi;
        try{
            vi = g->getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        vi->unmark(isInQueue);
        vi->unmark(inCicatrice);
    }//this loop initialise the marking
    bool thereIsNoRight = false;
    try {
        right = g->getSommet(r);
    } catch(NonExistentVerticeException &e) {
        existRight = false;
        thereIsNoRight = true;
    }
    try {
        left = g->getSommet(l);
    } catch(NonExistentVerticeException &e) {
        existLeft = false;
    }
    if(existRight && existLeft){
        toDel.push(origin->getVoisin((d + (6 - type)) % 6));
        g->getSommet(toDel.front())->mark(isInQueue);
    }
    while(existRight && existLeft){ //Bend over "in stays"
        if(right->isMarked(inCicatrice) || left->isMarked(inCicatrice)){
            //On tourne en rond.
            delete g;
            return NULL;
        }
        right->mark(inCicatrice);
        if(right->isArkenMarked() || left->isArkenMarked()){
            delete g;
            return NULL;
        }
        int in_r = right->isXthVoisin(previous_r);//The way we came in r
        int in_l =  left->isXthVoisin(previous_l);//The way we came in l
      //(1) Break links from inside to right.
        try{
            Vertice* interne_1 = g->getSommet(right->getVoisin((in_r + 5) % 6));
            interne_1->setVoisin(interne_1->isXthVoisin(r), -1);
        }catch(...){}
        try{
            Vertice* interne_2 = g->getSommet(right->getVoisin((in_r + 4) % 6));
            if(interne_2->isMarked(inCicatrice)){ //On tourne en rond.
                delete g;
                return NULL;
            }
            interne_2->setVoisin(interne_2->isXthVoisin(r), -1);
        }catch(...){}        
      //(2) Link right to left-outside.
        right->setVoisin((in_r +5) % 6, left->getVoisin((in_l + 5) % 6));
        right->setVoisin((in_r +4) % 6, left->getVoisin((in_l + 4) % 6));
      //(3) Link left-outside to right.
        try{
            Vertice* externe_1 = g->getSommet(left->getVoisin((in_l + 5) % 6));
            externe_1->setVoisin(externe_1->isXthVoisin(l), r);
            externe_1->mark(inCicatrice);
        }catch(...){}
        try{
            Vertice* externe_2 = g->getSommet(left->getVoisin((in_l + 4) % 6));
            externe_2->setVoisin(externe_2->isXthVoisin(l), r);
            externe_2->mark(inCicatrice);
        } catch(...){}
      //(4) Break links from left to left-outside.
        left->setVoisin((in_l + 5) % 6, -1);
        left->setVoisin((in_l + 4) % 6, -1);
      //(5) "Move" left and right to itterate.
        previous_r = r;
        previous_l = l;
        r = right->getVoisin((in_r + 3) % 6);
        l =  left->getVoisin((in_l + 3) % 6);
        try {
            right = g->getSommet(r);
            if(right->isMarked(inCicatrice)){
                delete g;
                return NULL;
            }
        } catch(NonExistentVerticeException &e) {
            existRight = false;
        }
        try {
            left  = g->getSommet(l);
            if(left->isMarked(inCicatrice)){
                delete g;
                return NULL;
            }
        } catch(NonExistentVerticeException &e) {
            existLeft = false;
        }
        if(existLeft && !existRight){
            Vertice* oldLeft = g->getSommet(previous_l);
            oldLeft->setVoisin(oldLeft->isXthVoisin(l), -1);
            g->getSommet(previous_r)->setVoisin((in_r + 3) % 6, l);
            in_l = left->isXthVoisin(previous_l);
            left->setVoisin(in_l, previous_r);
            previous_l = previous_r; //need it for first while(existLeft) itter
        }
    }
    while(existRight){
        if(right->isMarked(inCicatrice)){ //On tourne en rond
            delete g;
            return NULL;
        }
        right->mark(inCicatrice);
        if(right->isArkenMarked()){
            delete g;
            return NULL;
        }
        int in_r = right->isXthVoisin(previous_r);
      //(1) Break links from inside to right.
        try{
            Vertice* interne_1 = g->getSommet(right->getVoisin((in_r + 5) % 6));
            interne_1->setVoisin(interne_1->isXthVoisin(r), -1);
            if(! interne_1->isMarked(isInQueue)) {
                toDel.push(right->getVoisin((in_r + 5) % 6));
                interne_1->mark(isInQueue);
            }
        }catch(...){}
        try{
            Vertice* interne_2 = g->getSommet(right->getVoisin((in_r + 4) % 6));
            if(interne_2->isMarked(inCicatrice)){ //On tourne en rond.
                delete g;
                return NULL;
            }
            interne_2->setVoisin(interne_2->isXthVoisin(r), -1);
            if(! interne_2->isMarked(isInQueue)){
                toDel.push(right->getVoisin((in_r + 4) % 6));
                interne_2->mark(isInQueue);
            }
        }catch(...){}
      //(2) Break links from right to inside.
        right->setVoisin((in_r + 5) % 6, -1);
        right->setVoisin((in_r + 4) % 6, -1);
      //(3) "Move" right to itterate.
        previous_r = r;
        r = right->getVoisin((in_r + 3) % 6);
        try{
            right = g->getSommet(r);
            if(right->isMarked(inCicatrice)){
                delete g;
                return NULL;
            }
        } catch(NonExistentVerticeException &e) {
            existRight = false;
        }
    }
    while(existLeft){
        if(left->isMarked(inCicatrice)){ //On tour en rond.
            delete g;
            return NULL;
        }
        left->mark(inCicatrice);
        if(left->isArkenMarked()){
            delete g;
            return NULL;
        }
        int in_l = left->isXthVoisin(previous_l);
      //(1) Break links from inside to left.
        try{
            Vertice* interne_1 = g->getSommet(left->getVoisin((in_l + 1) % 6));
            interne_1->setVoisin(interne_1->isXthVoisin(l), -1);
            if(! interne_1->isMarked(isInQueue)){
                toDel.push(left->getVoisin((in_l + 1) % 6));
                interne_1->mark(isInQueue);
            }
        }catch(...){}
        try{
            Vertice* interne_2 = g->getSommet(left->getVoisin((in_l + 2) % 6));
            if(interne_2->isMarked(inCicatrice)) {//On tourne en rond.
                delete g;
                return NULL;
            }
            interne_2->setVoisin(interne_2->isXthVoisin(l), -1);
            if(! interne_2->isMarked(isInQueue)){
                toDel.push(left->getVoisin((in_l + 2) % 6));
                interne_2->mark(isInQueue);
            }
        }catch(...){}
      //(2) Break links from left to inside.
        left->setVoisin((in_l + 1) % 6, -1);
        left->setVoisin((in_l + 2) % 6, -1);
      //(3) "Move" left to itterate.
        previous_l = l;
        l = left->getVoisin((in_l + 3) % 6);
        try{
            left = g->getSommet(l);
            if(left->isMarked(inCicatrice)){
                delete g;
                return NULL;
            }
        } catch(NonExistentVerticeException &e) {
            existLeft = false;
        }
    }
  // Secondly : reduce v and delete what is useless.
    for(int i(0); i < 6-type; ++i){
        int delVois;
        try{
            if(thereIsNoRight)
                delVois = d;
            else
                delVois = (d + 1) % 6;
            Vertice* xi = g->getSommet(origin->getVoisin(delVois));
            xi->setVoisin(xi->isXthVoisin(v), -1);
        }catch(...){}
        origin->delVoisin(delVois);
    }
    g->setNbPenta_(g->getNbPenta() + (type == 5));
    g->setNbQuadri_(g->getNbQuadri() + (type == 4));
    while(!toDel.empty()){
        for(int i(0); i < 6; ++i){
            int neigh_place = g->getSommet(toDel.front())->getVoisin(i);
            if(neigh_place == -1)
                continue;
            Vertice* neigh = g->getSommet(neigh_place);
            neigh->setVoisin(neigh->isXthVoisin(toDel.front()), -1);
            if(neigh->isMarked(isInQueue))
                continue;
            if(neigh->isArkenMarked()){
                delete g;
                return NULL;
            }
            toDel.push(neigh_place);
            neigh->mark(isInQueue);
        }
        g->supprimerSommet(toDel.front());
        toDel.pop();
    }
    g->libererMarque(isInQueue);
    if(! g->bienFormer()){
        delete g;
        return NULL;
    }
    return g;
  }catch(BadNeighborhoodException_01 &e){
      delete g;
      return NULL;
  }
}

void Graph_01::relier_(){
    for(int i(0); i < TAILLE_TABLEAU; ++i)
        if(m_sommets[i] != NULL)
            relier_(i);
}

void Graph_01::relier_(int i){
    Vertice* v = getSommet(i);
    int v_mod = v->getNbVoisins();
    for(int j(0); j < 36 ; ++j){//We look every vertices, several times.
        if(v->getVoisin(j % v_mod) != -1)
            continue;
        if(v->getVoisin((j + 1) % v_mod) != -1) {
            Vertice* neigh = getSommet(v->getVoisin((j + 1) % v_mod));
            int n_mod = neigh->getNbVoisins();
            int in_neigh = neigh->isXthVoisin(i);
            if(neigh->getVoisin((in_neigh + 1) % n_mod) != -1){
                v->setVoisin(j % v_mod, neigh->getVoisin((in_neigh + 1) % n_mod));
                Vertice* linked = getSommet(neigh->getVoisin((in_neigh + 1) % n_mod));
                int in_linked = linked->isXthVoisin(v->getVoisin((j + 1) % v_mod));
                int l_mod = linked->getNbVoisins();
                linked->setVoisin((in_linked + 1) % l_mod, i);
            }
        }
        if(v->getVoisin((j + (v_mod - 1)) % v_mod) != -1) {
            Vertice* neigh = getSommet(v->getVoisin((j + (v_mod - 1)) % v_mod));
            int n_mod = neigh->getNbVoisins();
            int in_neigh = neigh->isXthVoisin(i);
            if(neigh->getVoisin((in_neigh + (n_mod - 1)) % n_mod) != -1){
                v->setVoisin(j % v_mod, neigh->getVoisin((in_neigh + (n_mod - 1)) % n_mod));
                Vertice* linked = getSommet(neigh->getVoisin((in_neigh + (n_mod - 1)) % n_mod));
                int in_linked = linked->isXthVoisin(v->getVoisin((j + (v_mod - 1)) % v_mod));
                int l_mod = linked->getNbVoisins();
                linked->setVoisin((in_linked + (l_mod - 1)) % l_mod, i);
            }
        }
    }
}

void Graph_01::completerADistance1_(){
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* v;
        try {
            v = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        if(v->getNbVoisins() == 6)
            continue;
        for(int j(0); j < v->getNbVoisins(); ++j){
            if(getCourbure() >= 7 && getNbSommetsLibres_() <= 3)
                return; //La fameuse condition des familles.
            if(v->getVoisin(j) != -1)
                continue;
            int nb = ajouterSommet();
            Vertice* newbie = getSommet(nb);
            newbie->addVoisin(0, i);
            while(newbie->getNbVoisins() < 6)
                newbie->addVoisin(newbie->getNbVoisins(), -1);
            v->setVoisin(j, nb);
            relier_(nb);
        }
    }
}

void Graph_01::completerADistance2_(){
    completerADistance1_();
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* v;
        try {
            v = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        if(v->getNbVoisins() != 6)
            continue;
        bool needToComplete = false;
        for(int j(0); j < v->getNbVoisins(); ++j)
            if(v->getVoisin(j) != -1)
                if(getSommet(v->getVoisin(j))->getNbVoisins() != 6)
                    needToComplete = true;
        if(needToComplete == false)
            continue;
        for(int j(0); j < v->getNbVoisins(); ++j){
            if(getCourbure() >= 7 && getNbSommetsLibres_() <= 3)
                return; //La fameuse condition des familles.
            if(v->getVoisin(j) != -1)
                continue;
            int nb = ajouterSommet();
            Vertice* newbie = getSommet(nb);
            newbie->addVoisin(0, i);
            while(newbie->getNbVoisins() < 6)
                newbie->addVoisin(newbie->getNbVoisins(), -1);
            v->setVoisin(j, nb);
            relier_(nb);
        }
    }
}

int Graph_01::getCeinture(int array[][2]) const {
    int sizeBelt = 0;
    int actual;
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* vi;
        try{
            vi = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        bool isOnBelt = false;
        for(int j(0); j < vi->getNbVoisins(); ++j){
            if(vi->getVoisin(j) == -1){
                isOnBelt = true;
                break;
            }
        }
        if(isOnBelt){
            actual = i;
            break;
        }
    }
    do{
        Vertice* va = getSommet(actual);
        array[sizeBelt][1] = 0;
        for(int i(0); i < va->getNbVoisins(); ++i){
            if(va->getVoisin(i) == -1)
                ++array[sizeBelt][1];
        }
        array[sizeBelt][0] = actual;
        ++sizeBelt;
        int leftNeigh = 0;
        //first: go in none
        while(va->getVoisin(leftNeigh) != -1){
            leftNeigh += 1;
            leftNeigh %= va->getNbVoisins();
        }
        //then: go out of none
        while(va->getVoisin(leftNeigh) == -1){
            leftNeigh += 1;
            leftNeigh %= va->getNbVoisins();
        }
        actual = va->getVoisin(leftNeigh);
    }while(actual != array[0][0]);
    return sizeBelt;
}

Graph_01* Graph_01::mirrorGraph_() const {
    Graph_01* out = new Graph_01();
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* vi = m_sommets[i];
        if(!vi){
            out->m_sommets[i] = NULL;
            continue;
        }
        out->m_sommets[i] = new Vertice_01(out, i);
        Vertice* outVi = out->m_sommets[i];
        for(int j(0); j < vi->getNbVoisins(); ++j){
            outVi->addVoisin(j, 
                  vi->getVoisin((vi->getNbVoisins() - j) % vi->getNbVoisins()));
        }
        if(isArkenMarked(i))
            outVi->markArken();
        else
            outVi->unmarkArken();
    }
    out->m_nbPenta = m_nbPenta;
    out->m_nbQuadra = m_nbQuadra;
    out->m_nbSommets = m_nbSommets;
    return out;
}

bool Graph_01::deuxQuadriColles_() const {
    if(! getNbQuadri())
        return false;
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* vi;
        try{
            vi = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        if(vi->getNbVoisins() != 4)
            continue;
        for(int j(0); j < vi->getNbVoisins(); ++j){
            Vertice* vj;
            try{
                vj = getSommet(vi->getVoisin(j));
            } catch(NonExistentVerticeException &e) {
                continue;
            }
            if(vj->getNbVoisins() == 4)
                return true;
        }
    }
    return false;
}

int Graph_01::getNbSommetsLibres_() const {
    int out = 0;
    for(int i(0); i < TAILLE_TABLEAU; ++i) {
        Vertice* vi;
        try {
            vi = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        int nbNoneVertice = 0;
        for(int j(0); j < vi->getNbVoisins(); ++j) {
            if(vi->getVoisin(j) == -1)
                ++nbNoneVertice;
        }
        out += ((nbNoneVertice > 1) ? (nbNoneVertice - 1) : 0);
    }
    return out;
}


int Graph_01::next_(int indice) const {
    do{
        ++indice;
        if(indice >= TAILLE_TABLEAU)
            return TAILLE_TABLEAU;
    } while(m_sommets[indice] == NULL);
    return indice;
}

Vertice* Graph_01::element_ (int indice) const {
    if (indice == TAILLE_TABLEAU)
        return NULL;
    return getSommet(indice);
}