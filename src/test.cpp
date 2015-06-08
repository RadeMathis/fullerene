#include <iostream>
#include <string>

#include <Vertice_01.hpp>
#include <functions.hpp>

using namespace std;

int
main(/*int argc, char *argv[]*/)
{
	Vertice* v1 = new Vertice_01();
	v1->addVoisin(0, 5);
	v1->addVoisin(1, 6);

	Vertice* v2 = v1->clone();
	v1->delVoisin(0);

	cout << "v1" <<"  "<< *v1 << endl;
	cout << "v2" <<"  "<< *v2 << endl;

	return 0;
}