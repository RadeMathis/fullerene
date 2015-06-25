#include <iostream>
#include <fstream>
#include <vector>

#include <graphPrinter.hpp>
#include <graphExceptions.hpp>
#include <functions.hpp>


void 
graphPrinter(std::string dataFile)
{
    std::ifstream iStream(dataFile + ".data", std::ios::in);
    if(!iStream)
        throw OpenFileFailureException(dataFile + ".data");
    
    std::ofstream oStream(dataFile + ".py", std::ios::out | std::ios::trunc);
    if(!oStream)
        throw OpenFileFailureException(dataFile + ".py");
    //todo: close both streams

    oStream << "import sys" << std::endl; 
    oStream << "sys.path.append('lib')" << std::endl;
    oStream << "from graphV3 import *" << std::endl;
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
        if(atoi(vectBuff[1].c_str()) == 5)
            arePentagon.push_back(atoi(vectBuff[0].c_str()));
        if(atoi(vectBuff[1].c_str()) == 4)
            areQuadrilateral.push_back(atoi(vectBuff[0].c_str()));
        for(int j(2); j < atoi(vectBuff[1].c_str()) + 2; ++j){
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
    oStream << "outFig.drawopts = 'rankdir=LR ratio=0.866 edge [len = 2]'" << std::endl;
    oStream << "dessiner(outFig, algo='twopi')" << std::endl;
}