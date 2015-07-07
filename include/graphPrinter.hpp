/* * *
 * Created by Rade Mathis for LaBRI
 * All right reserved by the LaBRI
 * * *
 * Version 0.1 ( 20/06/2015 )
 * * *
 * Supposed to transform a .graph.data into .graph.py
 * * */

#pragma once

#include <string>

void graphPrinter(std::string, std::string dir);
	/* This function takes a .graph.data file (call it without .graph.data), 
	 * translate it into a .graph.py Using the command : 
	 * python <myFile>.graph will print the graph in your default browser.
	 * Will put .gaph.py in dir
	 # Cette fonction prend comme paramettre un fichier .graph.data et le
	 # traduit en .graph.py (passer seulement <monFichier>.graph en parametre)
	 # La commande : pyhton <monFichier>.graph affichera une image du graphe
	 # dans le navigateur par defaut. */
void graphPrinter(std::string);
	/* Just call graphPrinter( , "");
	 # Appelle juste graphPrinter( , ""); */