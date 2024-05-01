/*
 *  main.cpp
 *  Allison Zhang and Baydan Hussen (bhusse01 and yzhang80)
 *  4/14/23
 *
 *  CS 15 Project 4 Gerp - Gerp.
 *  Purpose: to collect program arguments, validate them, then pass
 *          the arguments to be used. main also calls the functions,
 *          serving as a starting point for execution.
 *
 */
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <iostream>
#include <fstream>
#include <set>

#include "FSTree.h"
#include "DirNode.h"
#include "GerpIndexer.h"
#include "Gerp.h"

using namespace std;

//functions
void abort(std::string errorMessage);


/*
 * name:      main
 * purpose:   to run program
 * arguments: command line arguments: program, directory, outputfile
 * returns:   none
 * effects:   none
 */
int main(int argc, char *argv[]) {
    if(argc == 3) {
        Gerp gerpy;
        gerpy.commandLoop(argv[1], argv[2]);
    } else {
        abort("Usage: ./gerp inputDirectory outputFile");
    }

    return 0;
}

/*
 * name:      abort(string errorMessage)
 * purpose:   to send an error message to the user and the program
 * arguments: string errorMessage
 * returns:   technically void, but returns a cerr error message if the file
 *            doesn't open correctly.
 * effects:   ends the program
 */
void abort(std::string errorMessage){
    cerr << errorMessage << endl;
    exit(EXIT_FAILURE);
}
