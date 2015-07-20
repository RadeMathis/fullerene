#pragma once

#include <string>
#include <queue>

#include <Graph.hpp>

void
fullGenerator(std::string path = ".");
    /* Will generate all the graphs blablabla.... as in manifest blablabla....
     * All the .graph.data will put in path/ (relative or absolute).
     * Empty path is like if path == "."
     * Will also generate a graphList.data who will contain all the files' name.
     # Genere tout les sous graphes toussa toussa comme prevu (manifest)....
     # Tout les .graph.data sront mis dans path/ (relatif ou absolu), si aucune
     # chaine n'est passee en parametre alors path == "."
     # Genere aussi un graphList.data contenant la liste de tout les fichiers.*/

int
extrairePentaFront(std::queue<std::string> & graphFiles, 
                   std::string path);
    /* Take graphFiles.front() and build all the graphs it can by bending in 
     * pentagon. It won't build the once who are isomorph to one graph in 
     * path/ . Graph generated will be write in file (in path/) and files' name
     * will be pushed in graphFiles. It respect manifest's way to name files.
     # Prend graphFiles.front() et contruit tout les graphes qu'il peut en 
     # extraire par replit par pentagone. Il ne construira pas les graphes qui
     # en ont un isomorphe dans path/ . Les graphes generes seont ecrit dans un
     # fichier dans path/ respectant la convention de nommage decrite dans 
     # le manifest. */

int
extraireQuadriFront(std::queue<std::string> & graphFiles, 
                    std::string path);
	/* Same as upper function but gerate new graphs by bending in quadrilaterals
	 # Semblable a la fonction ci-dessus, mais genere les graphes en repliant 
	 # par quadrilateres et non par pentagones. */

int
extraireFront_(std::queue<std::string> & graphFiles, 
                    std::string path, int type);
    /* Abstract to previous codes.
     # Factorise les codes precedents. */

int
compareToOthers_(Graph* g, std::string path);
    /* If g get an isomorphe graph in path, will return -1.
     * Else, will return the matricule (Q_P_S__matricule)
     # Si g possede un isomorphisme, retourne -1.
     # Sinon, retourne le matricule (Q_P_S__matricule). */