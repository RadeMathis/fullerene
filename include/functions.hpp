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
std::vector<int> stringToVectorInt(std::string const& str);
	/* All str character need to be an integer 0 <= x <= 9
	 * Will return an int vector containing one int (0..9) by element.
	 # Chaque caractere le str doit etre un chiffre.
	 # Le vector retourné ccntiendra un chiffre par element. */
std::string vectorToString(std::vector<int> const& vect);
	/* Like the previous function. The opposite way
	 # Simple inverse de la fonction precedente. */
std::vector<int> arrayEgalsCycle(int a[][2], int b[][2], int sizeArrays);
	/* Takes 2 int[][2] arrays as parameter, the 3rd parametre means we should
	 * look the arrays from 0 to sizeArrays-1. We'll only look for [][0].
	 * If a and b got the sames elements in the same order, but with a "gap" of
	 * i elements, i will be put in the vector wich'll be returned.
	 # Prend deux tableaux int[][2] en parametre, le troisieme signifie que les
	 # tableaux seront traites de 0 a sizeArrays-1.
	 # On traitera uniquement le champ [][0].
	 # Si a et b possedent les memes elements, dans le meme ordre, mais decales
	 # de i elements, alors i sera present dans le vector retoune. */
std::vector<int> vectorEgalsCycle(std::vector<int> a, std::vector<int> b);
	/* Will do the same as upper function, but a[x] and b[y] will be the new
	 * a[x][0] and b[y][0].
	 # Comme la fonction ci-dessus, sauf qu'au lieu de regarder les champs
	 # [x][0] des tableau, on regardera les [x] des vecteurs. */

#endif /* INCLUDED_FUNCTIONS_H */