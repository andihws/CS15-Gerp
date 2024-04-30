/*
 *  main.cpp
 *  Allison Zhang
 *  3/27/24
 *
 *  CS 15 Project 3 Zap - Zappity Zap Zap
 *
 *  main method for Zap
 *
 */

#include "GerpIndexer.h"

using namespace std;

/*
 * name: main
 * purpose: Runs Zap
 * arguments: N/A
 * returns: An int representing that the run was successful
 * effects: N/A
 */
int main(int argc, char *argv[]) {
    GerpIndexer l;
    l.indexFiles("./test-dir/largeGutenberg");
    l.indexFile();
    return 0;
}