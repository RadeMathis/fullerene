#include <iostream>
#include <fstream>
#include <vector>

#include <graphPrinter.hpp>
#include <graphExceptions.hpp>
#include <functions.hpp>

void
graphPrinter(std::string dataFile)
{
    graphPrinter(dataFile, "");
}

void 
graphPrinter(std::string dataFile, std::string dir)
{
    std::string fileName = dataFile + ".graph";
    std::ifstream iStream(fileName + ".data", std::ios::in);
    if(!iStream)
        throw OpenFileFailureException(fileName + ".data");
    
    std::ofstream oStream(dir+fileName+".py", std::ios::out | std::ios::trunc);
    if(!oStream)
        throw OpenFileFailureException(dir + fileName + ".py");
    //todo: close both streams

    std::string name = "graph_" + dataFile;

    oStream << "import sys" << std::endl; 
    oStream << "sys.path.append('lib')" << std::endl;
    oStream << "from graphV3 import *" << std::endl;
    oStream << std::endl;
    oStream << name << " = construireGraphe([";

    std::string buff;
    std::vector<std::string> vectBuff;
    std::vector<int> arePentagon;
    std::vector<int> areQuadrilateral; //Faut que j'apprenne a ecrire ca
    std::vector<int> areInArken;

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
        if(atoi(vectBuff[atoi(vectBuff[1].c_str()) + 2].c_str()))
            areInArken.push_back(atoi(vectBuff[0].c_str()));
    }
    oStream.seekp(-1, std::ios::cur); //Back one char to del last ','
    oStream << "], \"" << name << "\")" << std::endl;
    while(!arePentagon.empty()){
        oStream << "s = sommetNom(" << name << ", '";
        oStream << arePentagon.back() << "')" << std::endl;
        arePentagon.pop_back();
        oStream << "colorierSommet(s, 'black')" << std::endl;
    }
    while(!areQuadrilateral.empty()){
        oStream << "s = sommetNom(" << name << ", '";
        oStream << areQuadrilateral.back() << "')" << std::endl;
        areQuadrilateral.pop_back();
        oStream << "colorierSommet(s, 'blue')" << std::endl;
    }
    while(!areInArken.empty()){
        oStream << "s = sommetNom(" << name << ", '";
        oStream << areInArken.back() << "')" << std::endl;
        areInArken.pop_back();
        oStream << "marquerSommet(s)" << std::endl;
    }
    oStream << name << ".drawopts = 'rankdir=LR ratio=0.866 edge [len = 2]'" << std::endl;
    oStream << "dessiner(" << name << ", algo='twopi')" << std::endl;
}