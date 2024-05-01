/*
 *  Gerp.cpp
 *  Allison Zhang and Baydan Hussen (bhusse01 and yzhang80)
 *  4/14/23
 *
 *  CS 15 Project 4 Gerp - Gerp.
 *
 *  Implentation of the Gerp class
 *
 */

#include "GerpIndexer.h"
#include "Gerp.h"

using namespace std;

/*
 * name: commandLoop
 * purpose: runs and handles the program queries
 * arguments: a string for the directory queries will run on 
 *            and a file to output the results
 * returns: technically void, but asks for queries in cout 
 *          and sends results of queries to the outfile
 * effects: none
 */
void Gerp::commandLoop(string dir, string outfile) {
    GerpIndexer indexer;
    indexer.indexFiles(dir);
    ofstream outstream;
    open_or_die(outstream, outfile);

    cout << "Query? ";
    string commands;
    string command;

    bool quit = false;
    cin >> command;
    while(not quit) {
        if(command == "@q") {
            quit = true;
        } else if(command == "@quit") {
            quit = true;
        } else if(command == "@i") {
            cin >> command;
            string word = indexer.stripNonAlphaNum(command);
            indexer.insensSearch(word, outstream);
        } else if(command == "@insensitive") {
            cin >> command;
            string word = indexer.stripNonAlphaNum(command);
            indexer.insensSearch(word, outstream);            
        } else if(command == "@f") {
            outstream.close();
            cin >> command;
            open_or_die(outstream, command);

        } else {
            string word = indexer.stripNonAlphaNum(command);
            indexer.sensSearch(word, outstream);    
        }

        if(not quit) {
            cout << "Query? ";
            cin >> command;
        }    
    }
    outstream.close();
    cout << "Goodbye! Thank you and have a nice day." << endl;
}

/*
 * name:      open_or_die
 * purpose:   to check if the file opens correctly 
 * arguments: ofstream object, string filename
 * returns:   technically void, but returns a cerr error message if the file
 *            doesn't open correctly.
 * effects:   ends the program if the file doesn't open correctly
 */
void Gerp::open_or_die(ofstream &stream, string fileName) {
    stream.open(fileName);
    if(not stream.is_open()){
        cout << "Could not open output file" << endl;
        exit(EXIT_FAILURE);
    }
}