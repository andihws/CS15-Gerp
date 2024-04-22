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
#include <set>
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
            /*
                Lines where the word is case exact, if the word is "The", it 
                will only contain lines with "The"
            */
            std::vector<Line> caseSensLines;
            /*
                Lines where the word is case inexact, if the word is "the", it 
                will contain "THe", "The", "THE", and "tHe".
            */
            std::vector<Line> insensLines;
            std::string key;
            int value = -1;
        };
        
        /* Member Variables */

        /* Lists for file paths and hashtable */
        std::vector<std::string> paths;
        std::vector<Word> hashTable {10000};

        /* Hash Function */
        std::hash<std::string> hasher;

        /* isCRLF is whether the text documents use CRLF or LF */
        bool isCRLF = false;
        int elements;
        int currLineNumber = 0;

        /* Member Functions */
        void indexFiles(std::string directory);
        void indexFile(std::string filePath);
        void processLine(std::string line, std::set<std::string> &words);
        void insertWord(std::string word);
        void rehash();
        int  hashWord(std::string word);
        

        /* Helper Functions */
        void getFileNames(DirNode *root, std::string path);
        bool isAlphaNum(char c);
        std::string stripNonAlphaNum(std::string input);


};



#endif 