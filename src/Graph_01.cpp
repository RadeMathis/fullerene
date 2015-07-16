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
#include <array>
#include <string>
#include <exception>

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
        m_sommets[thisVertice] = new Vertice_01();
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
        m_nbPenta(g.getNbPenta()), m_nbQuadra(g.getNbQuadra())
{
    for(int i(0); i < 8; ++i)
        m_marquesReserves[i] = 0;
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        try{
            m_sommets[i] = g.getSommet(i)->clone();
        } catch(NonExistentVerticeException &e) {
            m_sommets[i] = NULL;
        }
    }
}

Graph_01::Graph_01(Graph const* g) : m_nbSommets(g->getNbSommets()), 
        m_nbPenta(g->getNbPenta()), m_nbQuadra(g->getNbQuadra()) 
{
    for(int i(0); i < 8; ++i)
        m_marquesReserves[i] = 0;
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        try{
            m_sommets[i] = g->getSommet(i)->clone();
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

int Graph_01::getNbQuadra() const {
    return m_nbQuadra;
}

int Graph_01::getNbPenta() const {
    return m_nbPenta;
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
    throw FullGraphException(TAILLE_TABLEAU);
}


void Graph_01::supprimerSommet(int n){
    if(m_sommets[n] == NULL)
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
    if(m_sommets[n] == NULL || n < 0 || n >= TAILLE_TABLEAU)
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

void Graph_01::bienFormer(){
        relier();
        completerADistance2();
        markArken();
}

void Graph_01::initialiserPenta(){
    m_nbSommets = 1;
    m_nbPenta = 1;
    m_sommets[0] = new Vertice_01();
    for(int i(0); i < 5; ++i)
        m_sommets[0]->addVoisin(i, -1);
    bienFormer();
}

void Graph_01::initialiserQuadri(){
    m_nbSommets = 1;
    m_nbQuadra = 1;
    m_sommets[0] = new Vertice_01();
    for(int i(0); i < 4; ++i)
        m_sommets[0]->addVoisin(i, -1);
    bienFormer();
}

int Graph_01::peutReplierPenta (int v) const {
    std::vector<int> tmp = peutReplier_(v, 5, true);
    if(tmp.empty())
        return -1;
    return tmp[0];
}

int Graph_01::peutReplierQuadri (int v) const {
    std::vector<int> tmp = peutReplier_(v, 4, true);
    if(tmp.empty())
        return -1;
    return tmp[0];
}

std::vector<int> Graph_01::peutReplierPentaAll(int v) const {
    return peutReplier_(v, 5, false);
}

std::vector<int> Graph_01::peutReplierQuadriAll(int v) const {
    return peutReplier_(v, 4, false);
}

void Graph_01::replierPenta(int v, int d){
    replier(v, d, 5);
}

void Graph_01::replierQuadri(int v, int d){
    replier(v, d, 4);
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
                    goto LABEL_END_OF_FOR_J;
                } 
            }
        } LABEL_END_OF_FOR_J:; //verifier qu'on fait bien comme ca
    }
}

bool Graph_01::isomorphe(Graph* g) const 
{
    if(getNbSommets() != g->getNbSommets())
        return false;
    if(getNbQuadra() != g->getNbQuadra())
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

std::vector<int> Graph_01::peutReplier_(int v, int type, bool just_one) const {
    std::vector<int> out;
    Vertice* v_v = getSommet(v);
    if(v_v->isArkenMarked())
        return out; //On retourne un vector<int> vide.
    bool dir_0 = false;
    bool dir_1 = false; // Only usefull for type == 4 , useless for type == 5 .
    bool dir_g = false;
    bool dir_m = false; // Only usefull for type == 4 , useless for type == 5 .
    bool dir_d = false;
    for(int i(0); i < v_v->getNbVoisins(); ++i){
        int previous = v;
        int   actual = v_v->getVoisin(i);
        if(type == 5){
            dir_d = dir_g;
        } else {
            dir_d = dir_m;
            dir_m = dir_g;
        }
        dir_g = true; //(Presompions d'innocence)
        while(true){ // see breaks
            Vertice* v_a;
            try{
                v_a = getSommet(actual);
            } catch(NonExistentVerticeException &e) {
                break;
            }
            if(v_a->isArkenMarked()){
                dir_g = false;
                break;
            }
            int in_a = v_a->isXthVoisin(previous); //The way we came in actual
            previous = actual;
            actual   = v_a->getVoisin((in_a + 3) % v_a->getNbVoisins());
        }
        if(!i) {
            dir_0 = dir_g;
        } else if (i == 1 && type == 4){
            dir_1 = dir_g;
        } else if(dir_g && dir_d) {
            out.push_back(i - 1);
            if(just_one)
                return out;
        }
        if(type == 4 && i == v_v->getNbVoisins() - 2 && dir_0 && dir_g){
            out.push_back(i);
            if(just_one)
                return out;
        }
        if(type == 5 && i == v_v->getNbVoisins() - 1 && dir_0 && dir_g){
            out.push_back(i);
            if(just_one)
                return out;
        }
        if(i == v_v->getNbVoisins() - 1 && dir_1 && dir_g)
            out.push_back(i);
    }
    return out;
}

void Graph_01::replier(int v, int d, int type){ //v: vertice, d: direction
  //First : Bend over "in stays".
    bool existRight = true;
    bool  existLeft = true;
    Vertice* origin = getSommet(v);
    Vertice*  right = NULL;
    Vertice*   left = NULL;
    int           r = origin->getVoisin(d);                    //right place
    int           l = origin->getVoisin((d + (6 - type)) % 6); // left place
    int  previous_r = v;
    int  previous_l = v;
    std::queue<int> toDel;
    int   isInQueue = reserverMarque();
    for(int i(0); i < TAILLE_TABLEAU; ++i){
        Vertice* vi;
        try{
            vi = getSommet(i);
        } catch(NonExistentVerticeException &e) {
            continue;
        }
        vi->unmark(isInQueue);
    }//this loop initialise the marking
    bool thereIsNoRight = false;
    try {
        right = getSommet(r);
    } catch(NonExistentVerticeException &e) {
        existRight = false;
        thereIsNoRight = true;
    }
    try {
        left = getSommet(l);
    } catch(NonExistentVerticeException &e) {
        existLeft = false;
    }
    if(existRight && existLeft){
        toDel.push(origin->getVoisin((d + 1) % 6));
        getSommet(toDel.front())->mark(isInQueue);
    }
    while(existRight && existLeft){ //Bend over "in stays"
        int in_r = right->isXthVoisin(previous_r);//The way we came in r
        int in_l =  left->isXthVoisin(previous_l);//The way we came in l
      //(1) Break links from inside to right.
        try{
            Vertice* interne_1 = getSommet(right->getVoisin((in_r + 5) % 6));
            interne_1->setVoisin(interne_1->isXthVoisin(r), -1);
        }catch(...){}
        try{
            Vertice* interne_2 = getSommet(right->getVoisin((in_r + 4) % 6));
            interne_2->setVoisin(interne_2->isXthVoisin(r), -1);
        }catch(...){}        
      //(2) Link right to left-outside.
        right->setVoisin((in_r +5) % 6, left->getVoisin((in_l + 5) % 6));
        right->setVoisin((in_r +4) % 6, left->getVoisin((in_l + 4) % 6));
      //(3) Link left-outside to right.
        try{
            Vertice* externe_1 = getSommet(left->getVoisin((in_l + 5) % 6));
            externe_1->setVoisin(externe_1->isXthVoisin(l), r);
        }catch(...){}
        try{
            Vertice* externe_2 = getSommet(left->getVoisin((in_l + 4) % 6));
            externe_2->setVoisin(externe_2->isXthVoisin(l), r);
        }catch(...){}
      //(4) Break links from left to left-outside.
        left->setVoisin((in_l + 5) % 6, -1);
        left->setVoisin((in_l + 4) % 6, -1);
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
            in_l = left->isXthVoisin(previous_l);
            left->setVoisin(in_l, previous_r);
            previous_l = previous_r; //need it for first while(existLeft) itter
        }
    }
    while(existRight){
        int in_r = right->isXthVoisin(previous_r);
      //(1) Break links from inside to right.
        try{
            Vertice* interne_1 = getSommet(right->getVoisin((in_r + 5) % 6));
            interne_1->setVoisin(interne_1->isXthVoisin(r), -1);
            if(toDel.empty()){
                toDel.push(right->getVoisin((in_r + 5) % 6));
                getSommet(toDel.front())->mark(isInQueue);
            }
        }catch(...){}
        try{
            Vertice* interne_2 = getSommet(right->getVoisin((in_r + 4) % 6));
            interne_2->setVoisin(interne_2->isXthVoisin(r), -1);
            if(toDel.empty()){
                toDel.push(right->getVoisin((in_r + 4) % 6));
                getSommet(toDel.front())->mark(isInQueue);
            }
        }catch(...){}
      //(2) Break links from right to inside.
        right->setVoisin((in_r + 5) % 6, -1);
        right->setVoisin((in_r + 4) % 6, -1);
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
        try{
            Vertice* interne_1 = getSommet(left->getVoisin((in_l + 1) % 6));
            interne_1->setVoisin(interne_1->isXthVoisin(l), -1);
            if(toDel.empty()){
                toDel.push(left->getVoisin((in_l + 1) % 6));
                getSommet(toDel.front())->mark(isInQueue);
            }
        }catch(...){}
        try{
            Vertice* interne_2 = getSommet(left->getVoisin((in_l + 2) % 6));
            interne_2->setVoisin(interne_2->isXthVoisin(l), -1);
            if(toDel.empty()){
                toDel.push(left->getVoisin((in_l + 2) % 6));
                getSommet(toDel.front())->mark(isInQueue);
            }
        }catch(...){}
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
    for(int i(0); i < 6-type; ++i){
        int delVois;
        try{
            if(thereIsNoRight)
                delVois = d;
            else
                delVois = (d + 1) % 6;
            Vertice* xi = getSommet(origin->getVoisin(delVois));
            xi->setVoisin(xi->isXthVoisin(v), -1);
        }catch(...){}
        origin->delVoisin(delVois);
    }
    m_nbPenta  += (type == 5);
    m_nbQuadra += (type == 4);
    while(!toDel.empty()){
        for(int i(0); i < 6; ++i){
            int neigh_place = getSommet(toDel.front())->getVoisin(i);
            if(neigh_place == -1)
                continue;
            Vertice* neigh = getSommet(neigh_place);
            neigh->setVoisin(neigh->isXthVoisin(toDel.front()), -1);
            if(neigh->isMarked(isInQueue))
                continue;
            toDel.push(neigh_place);
            neigh->mark(isInQueue);
        }
        supprimerSommet(toDel.front());
        toDel.pop();
    }
    libererMarque(isInQueue);
    bienFormer();
}

void Graph_01::relier(){
    for(int i(0); i < TAILLE_TABLEAU; ++i)
        if(m_sommets[i] != NULL)
            relier(i);
}

void Graph_01::relier(int i){
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

void Graph_01::completerADistance1(){
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
            if(v->getVoisin(j) != -1)
                continue;
            int nb = ajouterSommet();
            Vertice* newbie = getSommet(nb);
            newbie->addVoisin(0, i);
            while(newbie->getNbVoisins() < 6)
                newbie->addVoisin(newbie->getNbVoisins(), -1);
            v->setVoisin(j, nb);
            relier(nb);
        }
    }
}

void Graph_01::completerADistance2(){
    completerADistance1();
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
            if(v->getVoisin(j) != -1)
                continue;
            int nb = ajouterSommet();
            Vertice* newbie = getSommet(nb);
            newbie->addVoisin(0, i);
            while(newbie->getNbVoisins() < 6)
                newbie->addVoisin(newbie->getNbVoisins(), -1);
            v->setVoisin(j, nb);
            relier(nb);
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
        for(int j(0); j < vi->getNbVoisins(); ++j)
            if(vi->getVoisin(j) == -1){
                isOnBelt = true;
                break;
            }
        if(isOnBelt){
            actual = i;
            break;
        }
    }
    do{
        Vertice* va = getSommet(actual);
        array[sizeBelt][1] = 0;
        for(int i(0); i < va->getNbVoisins(); ++i)
            if(va->getVoisin(i) == -1)
                ++array[sizeBelt][1];
        array[sizeBelt][0] = actual;
        ++sizeBelt;
        int leftNeigh = 0;
        //first: go in none
        while(va->getVoisin(leftNeigh) != -1)
            ++leftNeigh;
        //then: go out of none
        while(va->getVoisin(leftNeigh) == -1)
            ++leftNeigh;
        actual = va->getVoisin(leftNeigh);
    }while(actual != array[0][0]);
    return sizeBelt;
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
    if (indice == 256)
        return NULL;
    return getSommet(indice);
}