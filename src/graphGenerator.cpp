#include <graphGenerator.hpp>

#include <stdio.h> //desole
#include <iostream>
#include <fstream>
#include <queue>
#include <sys/stat.h>

#include <Graph_01.hpp>
#include <functions.hpp>

void
fullGenerator(std::string path /* = "." */)
{
    try{
        mkdir(path.c_str(), S_IRWXU );
    } catch(...) {}

    if(path.back() != '/')
        path.push_back('/');

    std::ofstream graphList((path + "graphList.data").c_str(), std::ios::out
                                                             | std::ios::trunc);

    graphList << "          " << std::endl; 
        // On laisse une ligne pour y inscrire le nombre de graphes formes.

    int nbGraphGenerated;
    std::queue<std::string> toTreatGraph;
    Graph* actualGraph;
    
    // On cree le premier graphe (un pentagone)
    actualGraph = new Graph_01();
    actualGraph->initialiserPenta();
    actualGraph->writeInFile("0_1_16__0");
    toTreatGraph.push("0_1_16__0");
    graphList << "0_1_16__0" << std::endl;
    delete actualGraph;

    // On creer un autre graphe de base (un quadrilatere)
    actualGraph = new Graph_01();
    actualGraph->initialiserQuadri();
    actualGraph->writeInFile("1_0_13__0");
    toTreatGraph.push("1_0_13__0");
    graphList << "1_0_13__0" << std::endl;
    delete actualGraph;

    nbGraphGenerated = 2;

    // On genere tout le reste a parti de ces deux la.
    while(! toTreatGraph.empty()){
        fprintf(stdout, "\rGraph generated : %d.", nbGraphGenerated);
        fflush(stdout); //Afficher le buffer.
        actualGraph = new Graph_01(toTreatGraph.front());
        int courbure = 2 * actualGraph->getNbQuadri() 
                         + actualGraph->getNbPenta();
        if(courbure >= 7){
            toTreatGraph.pop();
            continue;
        }
        nbGraphGenerated += extrairePentaFront(toTreatGraph, path);
        if(courbure >= 6){
            toTreatGraph.pop();
            continue;
        }
        nbGraphGenerated += extraireQuadriFront(toTreatGraph, path);
        delete actualGraph;
        toTreatGraph.pop();
    }
    std::cout << std::endl;
    graphList.seekp(0, std::ios::beg); //retour au debut
    graphList << nbGraphGenerated; //inscription du nombre de graphes


///=uiiiii;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/// Thanks to my cat, for this amazing cat++ code.
}

int
extrairePentaFront(std::queue<std::string>& graphFiles, 
                   std::string path)
{
    return extraireFront_(graphFiles ,path, 5);
}

int
extraireQuadriFront(std::queue<std::string>& graphFiles, 
                    std::string path)
{
    return extraireFront_(graphFiles, path, 4);
}

int
extraireFront_(std::queue<std::string> & graphFiles,
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
            if(newGraph){//todel (et ce que ca ccontient)
                break; //Si on un graphe, c'est bon
            }
        }
        if(!newGraph)
            continue; //Si ce sommet n'a rien donne, on passe au suivant.
        int matricule;
        matricule = compareToOthers_(newGraph, path);
        if(matricule != -1){
            // Le graphe est nouveau, il faut l'ajouter.
            std::string newGraphName;
            newGraphName += std::to_string(newGraph->getNbQuadri());
            newGraphName += '_';
            newGraphName += std::to_string(newGraph->getNbPenta());
            newGraphName += '_';
            newGraphName += std::to_string(newGraph->getNbSommets());
            newGraphName += "__";
            newGraphName += std::to_string(matricule);
            graphFiles.push(newGraphName);
            std::ofstream graphList((path +"graphList.data").c_str()
                                               , std::ios::out | std::ios::app);
            graphList << newGraphName << std::endl;
            newGraph->writeInFile(newGraphName);
            ++nbGraphGenerated;
        }
        delete newGraph;
    }
    delete g;
    return nbGraphGenerated;
}

int
compareToOthers_(Graph* g, std::string path)
{
    int matricule = 0;
    std::string lineBuffer;
    std::vector<std::string> sentenceBuffer;
    std::ifstream graphList((path + "graphList.data").c_str(), std::ios::in);
    if(!graphList)
    std::getline(graphList, lineBuffer);
        // On passe la premiere ligne, car elle est vide.
    while(true){ //For in file's lines. (break two lines behind)
        std::getline(graphList, lineBuffer);
        if(graphList.eof())
            return matricule;
        sentenceBuffer = decouperString(lineBuffer);
        if((lineBuffer[0] - 48) != g->getNbQuadri())
            continue;
        if((lineBuffer[2] - 48) != g->getNbPenta())
            continue;
        int gfNbSommet = 0;
        unsigned int curseur = 4;
        while(lineBuffer[curseur] != '_'){
            gfNbSommet *= 10;
            gfNbSommet += (lineBuffer[curseur] - 48); // Using ASCII value.
            ++curseur;
        }
        if(gfNbSommet != g->getNbSommets())
            continue;
        Graph* g2 = new Graph_01(sentenceBuffer[0]);
        if(g->isomorphe(g2)){
            delete g2;
            return -1;
        }
        delete g2;
        curseur += 2; //"__"
        int gfMatricule = 0;
        while(curseur < sentenceBuffer[0].size()){
            gfMatricule *= 10;
            gfMatricule += (lineBuffer[curseur] - 48); //ASCII trick, again.
            ++curseur;
        }
        if(matricule <= gfMatricule)
            matricule = gfMatricule + 1;
    }
}