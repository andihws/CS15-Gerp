/*
 *  GerpIndexer.h
 *  Allison Zhang and Baydan Hussen (bhusse01 and yzhang80)
 *  4/14/23
 *
 *  CS 15 Project 4 Gerp - Gerp.
 *
 *  Header file for the GerpIndexer class
 *
 */

#ifndef __GERPINDEXER_H
#define __GERPINDEXER_H

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include "FSTree.h"
#include "DirNode.h"


class GerpIndexer {
    public:
        GerpIndexer();
        ~GerpIndexer();

    private:
        /* Structs */
        struct Line {
            std::vector<int> lines;
            std::string filePath;
        };

        struct Word {
            std::vector<Line> caseSensLines;
            std::vector<Line> insensLines;
            std::string key;
            int value;
        };
        
        /* Member Variables */
        std::vector<std::string> paths;
        std::hash<std::string> hasher;
        std::vector<Word> hashTable;
        int elements;

        void indexFiles(std::string directory);
        void indexFile(std::string filePath);
        void processLine();
        void insertWord();
        void rehash();
        int  hashWord(std::string word);
        
    
        void getFileNames(DirNode *root, std::string path);


};



#endif 