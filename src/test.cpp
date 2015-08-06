#include <stdio.h>
#include <string>
#include <ctime>

#include <Graph_01.hpp>
#include <functions.hpp>
#include <graphPrinter.hpp>
#include <graphGenerator.hpp>

using namespace std;

int
main(void)
{
	///fullGenerator();
	///Graph* g1 = new Graph_01("0_3_23__0");
	///Graph* g2 = new Graph_01("0_3_23__1");

	///cout << boolalpha << g2->isomorphe(g1) << endl;
	Graph* g = new Graph_01("ceGrapheBug"); cout << "On cree le kibug" << endl;
	Graph* gx[9];
	gx[0] = new Graph_01("1_4_40__0"); cout << "On cree " << 0 << endl;
	gx[1] = new Graph_01("1_4_40__1"); cout << "On cree " << 1 << endl;
	gx[2] = new Graph_01("1_4_40__2"); cout << "On cree " << 2 << endl;
	gx[3] = new Graph_01("1_4_40__3"); cout << "On cree " << 3 << endl;
	gx[4] = new Graph_01("1_4_40__4"); cout << "On cree " << 4 << endl;
	gx[5] = new Graph_01("1_4_40__5"); cout << "On cree " << 5 << endl;
	gx[6] = new Graph_01("1_4_40__6"); cout << "On cree " << 6 << endl;
	gx[7] = new Graph_01("1_4_40__7"); cout << "On cree " << 7 << endl;
	gx[8] = new Graph_01("1_4_40__8"); cout << "On cree " << 8 << endl;

	for(int i(0); i < 9; ++i){
		cout << i << "\t" << boolalpha << gx[0]->isomorphe(g) << endl;
	}
	
    return 0;
}