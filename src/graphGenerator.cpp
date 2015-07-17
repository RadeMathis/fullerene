#include <graphGenerator.hpp>

#include <fstream>
#include <queue>

#include <Graph.hpp>
#include <Graph_01.hpp>
#include <functions.hpp>

void
fullGenerator(std::string path /* = '.' */)
{
    try{
        mkdir(path.c_str(), S_IRWXU );
    } catch(...) {}

    if(path.back() != '/')
        path.push_back('/');

    std::ofstream graphList((path + "graphList.data").c_str(), std::ios::out
                                                             | std::ios::trunc);

    graphList << '          ' << std::endl; 
        // On laisse une ligne pour y inscrire le nombre de graphes formes.

    int nbGraphGenerated;
    std::queue<std::string> toTreatGraph;
    Graph* actualGraph;
    
    actualGraph = new Graph_01();
    actualGraph->initialiserPenta();
    actualGraph->writeInFile("0_1_16__0");
    toTreatGraph.push("0_1_16__0");
    graphList << "0_1_16__0" << std::endl;
    delete actualGraph;

    actualGraph = new Graph_01();
    actualGraph->initialiserQuadri();
    actualGraph->writeInFile("1_0_13__0");
    toTreatGraph.push("1_0_13__0");
    graphList << "1_0_13__0" << std::endl;
    delete actualGraph;

    nbGraphGenerated = 2;

    while(! toTreatGraph.empty()){
        actualGraph = new Graph_01(toTreatGraph.front());
        int courbure = 2 * actualGraph->getNbquadri() 
                         + actualGraph->getNbPenta();
        if(courbure > 7)
        	continue;
        nbGraphGenerated += extrairePentaFront(toTreatGraph, path);
        if(courbure > 6)
        	continue;
        nbGraphGenerated += extraireQuadriFront(toTreatGraph, path);
        //TODO : creer les deux fonctions ci-dessus
        delete actualGraph;
        toTreatGraph.pop();
    }
    graphList.seekp(0, std::ios::beg); //retour au debut
    graphList << nbGraphGenerated; //inscription du nombre de graphes


///=uiiiii;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/// Thanks to my cat, for this amazing cat++ code.
}

int
extrairePentaFront(std::queue<std::string> graphFiles, 
                   std::string path)
{
    return extraireFront_(graphFiles ,path, 5);
}

int
extraireQuadriFront(std::queue<std::string> graphFiles, 
                    std::string path)
{
    return extraireFront_(graphFiles, path, 4);
}

int
extraireFront_(std::queue<std::string> graphFiles,
               std::string path, int type)
{
    int nbGraphGenerated = 0;
    Graph*             g = new Graph_01(graphFiles.front());
    // Tout d'abord, on tente de generer un graphe par sommet
    for(Iterator it = g->begin(); it != g->end(); ++it){
        Graph* newGraph;
        // Pour chaque sommet, on cherche une direction dans laquelle
        // on peut plier, si aucune ne va, on ne replie pas.
        for(int j(0); j < (*it)->getNbVoisins(); ++j){
            if(type == 5)
                newGraph = g->replierPenta(*it, j);
            if(type == 4)
                newGraph = g->replierQuadri(*it, j);
            if(newGraph)
                break; //Si ona un graphe, c'est bon
        }
        if(!newGraph)
            continue; //Si ce sommet n'a rien donne, on passe au suivant.
        if(compareToOthers_(newGraph, path) != -1){
            // TODO : coder la func si dessus
            // TODO : ENDIT
        }
    }
}

int
compareToOthers_(Graph* g, std::string path)
{
    int matricule = 0;
    std::string lineBuffer;
    std::vector<std::string> sentenceBuffer;
    std::ifstream graphList((path + "graphList.data").c_str(), std::ios::in);
    std::getline(graphList, lineBuffer);
    sentenceBuffer = decouperString(lineBuffer);
    int nbGraph atoi(sentenceBuffer[0].c_str());
    bool out = false; //Presomption d'innocence
    for(int i(0); i < nbGraph; ++i){ //For in file's lines.
        std::getline(graphList, lineBuffer);
        sentenceBuffer = decouperString(lineBuffer);
        if(lineBuffer[0] != g->getNbquadri())
            continue;
        if(lineBuffer[2] != g->getNbPenta())
            continue;
        int gfNbSommet = 0;
        int curseur = 4;
        while(lineBuffer[curseur] != '_'){
            gfNbSommet *= 10;
            gfNbSommet += (lineBuffer[curseur] - 48); // Using ASCII value.
            ++curseur;
        }
        if(gfNbSommet != g->getNbSommets())
            continue;
        curseur += 2;
        int gfMatricule = 0;
        while(curseur < sentenceBuffer[0].size()){
            gfMatricule *= 10;
            gfMatricule += (lineBuffer[curseur] - 48); //ASCII trick, again.
            ++curseur;
        }
        if(matricule <= gfMatricule)
            matricule = gfMatricule + 1;
        Graph* g2 = new Graph_01(sentenceBuffer[0]);
        if(g->isomorphe(g2))
            return -1;
    }
    ////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////
  //// TODO : ENDIT //////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
}