#include <iostream>
#include <fstream>
#include <vector>

#include <graphPrinter.hpp>
#include <graphExceptions.hpp>


void 
graphPrinter(std::string dataFile)
{
    std::ifstream inStream(dataFile + ".data", std::ios::in);
    if(!iStream)
        throw OpenFileFailureException;
    
    std::ofstream oStream(dataFile + ".py", std::ios::out | ios::trunc);
    if(!oStream)
        throw OpenFileFailureException;
    //todo: close both streams

    oStream << "from lib/graphV3 import *" << std::endl;
    oStream << "import sys" << std::endl; // Si bug, tenter de del cette ligne
    oStream << std::endl;
    oStream << "outFig = construireGraphe([";

    std::string buff;
    std::vector<std::string> vectBuff;
    std::vector<int> arePentagon;
    std::vector<int> areQuadrilateral; //Faut que j'apprenne a ecrire ca

    getline(iStream, buff);
    vectBuff = decouperString(buff);
    int nbSommet = atoi(vectBuff[0].c_str());

    for(int i(0); i < nbSommet-1; ++i){
        getline(iStream, buff);
        vectBuff = decouperString(buff);
        if(vectBuff[1] == 5)
            arePentagon.push_back(vectBuff[0]);
        if(vectBuff[1] == 4)
            areQuadrilateral.push_back(vectBuff[0]);
        for(int j(2); j < vectBuff[1] + 2; ++j){
            if(atoi(vectBuff[j].c_str()) > atoi(vectBuff[0].c_str())){
                oStream << "['" << vectBuff[0] << "','" << vectBuff[j] << "'],";
            }
        }
    }
    oStream.seekp(-1, std::ios::cur); //Back one char to del last ','
    oStream << "], \"outFig\")" << std::endl;
    while(!arePentagon.empty()){
        oStream << "s = sommetNom(outFig, '" << arePentagon.back() << "')";
        oStream << std::endl;
        arePentagon.pop_back();
        oStream << "colorierSommet(s, 'black')" << std::endl;
    }
    while(!areQuadrilateral.empty()){
        oStream << "s = sommetNom(outFig, '" << areQuadrilateral.back() << "')";
        oStream << std::endl;
        areQuadrilateral.pop_back();
        oStream << "colorierSommet(s, 'blue')" << std::endl;
    }
    oStream << "dessiner(outFig, algo='fdp')" << std::endl;
}