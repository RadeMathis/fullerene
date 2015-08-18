#include <iostream>
#include <getopt.h>
#include <string>

#include <graphGenerator.hpp>
#include <graphPrinter.hpp>

#define VERSION 1
#define RELEASE 1

using namespace std;


void usage(int status);


int
main(int argc, char *argv[])
{
    if(argc < 2)
    {
        usage(EXIT_FAILURE);
    }

    const static struct option longToShort[] =
    {
    	{"all",       required_argument, NULL, 'a'}, //argument is optional
        {"generate",  required_argument, NULL, 'g'}, //argument is optional
        {"help",      no_argument,       NULL, 'h'},
        {"output",    required_argument, NULL, 'o'},
        {"print",     required_argument, NULL, 'p'},
        {"print_all", no_argument,       NULL, 'P'},
        {"version",   no_argument,       NULL, 'v'},
        {0,0,0,0} //default
    };

    int   generateDegree = 0;
    bool       print_all = false;
    char outputPath[256] = ".";
    char      print[256] = "";

    int optc;
    while((optc = getopt_long(argc, argv, 
                                     ":a:g:ho:p:Pv", longToShort, NULL)) != -1){
        switch (optc) {
            case ':' :
                switch (optopt) {
                    case 'a' :
                        generateDegree = 7;
                        print_all = true;
                        break;
                    case 'g' :
                        generateDegree = 7;
                        break;
                    default :
                        usage(EXIT_FAILURE); // Ca va exit() // Will call exit()
                }
                break;
            case 'a' :
                generateDegree = atoi(optarg);
                print_all = true;
                break;
            case 'g' :
                generateDegree = atoi(optarg);
                break;
            case 'h' :
                usage(EXIT_SUCCESS); // Ca va exit() // Will call exit()
            case 'o' :
                for(int i(0); i < 256; ++i){
                    if(optarg[i] == '\0')
                        break;
                    outputPath[i] = optarg[i];
                }
                break;
            case 'p' :
                for(int i(0); i < 256; ++i){
                    if(optarg == '\0')
                        break;
                    print[i] = optarg[i];
                }
                break;
            case 'P' :
                print_all = true;
                break;
            case 'v' :
                cout << endl << "Mathis's sub-fullerene generator. Version : "
                     << VERSION << '.' << RELEASE << endl;
                break;
            default :
                usage(EXIT_FAILURE); // Ca va exit() // Will call exit()
        }
    }

    string s_outputPath(outputPath);
    if(generateDegree){
        fullGenerator(s_outputPath, generateDegree);
    }
    if(print_all) {
        graphPrinter_all(s_outputPath);
    } else if (print[0]) {
        string s_print(print);
        graphPrinter(s_print, s_outputPath);
    } else if (! generateDegree) {
        usage(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}


void
usage(int status)
{
    if(status != EXIT_SUCCESS){
        cerr << "Mistakes has been found, try -h or --help for more ";
        cerr << "informations." << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << endl 
             << "This program is generating fullrenes subgraphs." << endl
             << "Where : (numberOfPentagons) + (2 * numberOfQuadrilaterals) < 8"
             << endl
             << "And there are always at least 2 haxagones between the "
             << "\"graph's end\" and all " << endl
             << "\tpentagon or quadrilateral." << endl
             << "Read the manifest for more informations." << endl
             << endl
             << "Use ./test -<option> [argument] -<option2> [argument2]"
             << endl << endl
             << "OPTIONS : "
             << endl
             << "-a, --all [degree]      Same as -gP options." 
             << endl
             << "                        /!\\ do not use -a<option> [arg]"
             << endl
             << "                        /!\\ prefer use -a 7 -<options> [arg]"
             << endl << endl
             << "-g, --generate [degree] Generate all graphes with a curvature"
             << endl
             << "                        degree <= [degree]. [degree] is"
             << endl
             << "                        optional, if nothing is specifiate, a"
             << endl
             << "                        default [degree] will be set at 7."
             << endl
             << "                        /!\\ do not use -g<option> [arg]"
             << endl
             << "                        /!\\ prefer use -g 7 -<options> [arg]"
             << endl
             << "                        /!\\ prefer use -a to -gP"
             << endl << endl
             << "-h, --help              Display current message."
             << endl << endl
             << "-o, --output [path]     Absolute or relative [path] will be"
             << endl
             << "                        where it will put all .data files."
             << endl << endl
             << "-p, --print [graph]     Use the [graph].graph.data file to"
             << endl
             << "                        genrate a [graph].graph.py file."
             << endl
             << "                        You will be able to draw the graph, "
             << endl
             << "                        using >>> python [graph].graph.py"
             << endl << endl
             << "-P, --print_all         Like if you run with -p for all the"
             << endl
             << "                        graphs in the graphList.data file."
             << endl << endl
             << "-v, --version           Display the program's version."
             << endl
             << endl;
    	exit(EXIT_SUCCESS);
    }
}