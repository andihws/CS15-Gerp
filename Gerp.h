/*
 *  Gerp.h
 *  Allison Zhang and Baydan Hussen (bhusse01 and yzhang80)
 *  4/14/23
 *
 *  CS 15 Project 4 Gerp - Gerp.
 *
 *  Header file for the Gerp class
 *
 */

#ifndef __GERP_H
#define __GERP_H

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


class Gerp {
    public:
        void commandLoop(std::string dir, std::string outfile);
    private:
        void open_or_die(std::ofstream &stream, std::string fileName);

};



#endif 