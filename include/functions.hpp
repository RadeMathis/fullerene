/* * *
 * Createed by Rade Mathis for the LaBRI
 * All right reserved by the LaBRI
 * * *
 * v1.1.0 (13/05/2015)
 * * *
 * Usefull functions for the rest of the program
 * * */

#ifndef INCLUDED_FUNCTIONS_H
#define INCLUDED_FUNCTIONS_H

#include <vector>
#include <string>

std::vector<std::string> decouperString(std::string const& str);
    /* Return str words in a string vector.
     * Each element is a world of str string (are considered as words
     * substrings separated by ' ' character).
     # Retourne les mots de str dans un vector de string.
     # Chaque element contient un mot de str (sont consideres
     # comme mot les sous-string separees par le caractere ' '). */

#endif /* INCLUDED_FUNCTIONS_H */