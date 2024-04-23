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
#include <sstream>
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

        /* Structs */
        struct Line {
            std::set<int> lines;
            std::string filePath;
        };

        struct Word {
            /*
                Lines where the word is case exact, if the word is "The", it 
                will only contain lines with "The"
            */
            std::vector<Line> sLines; //sensitive lines
            /*
                Lines where the word is case inexact, if the word is "the", it 
                will contain "THe", "The", "THE", and "tHe".
            */
            std::vector<Line> isLines; //insensitive lines
            std::string key;
            int value = -1;
        };
        
        /* Member Variables */

        /* Lists for file paths and hashtable */
        std::vector<std::string> paths;
        std::vector<Word> hashTable;

        /* Hash Function */
        std::hash<std::string> hasher;

        /* isCRLF is whether the text documents use CRLF or LF */
<<<<<<< HEAD
        size_t prime[14] = {6131, 11621, 23291, 35671, 42013, 61543, 81667, 102161, 
                         116239, 137239, 257591, 307283, 507961, 1000003};
=======
        size_t prime[25] = {6131, 11621, 23291, 35671, 42013, 61543, 81667, 
                            102161, 116239, 137239, 257591, 307283, 507961, 
                            1000003, 2269733, 3042161, 4535189, 7474967,
                            9737333, 14161729, 17624813, 19734581, 23391799, 
                            29499439, 37139213};
>>>>>>> 8deddd4 (insert method comparison)
        int primeIndex = 0;
        bool isCRLF = false; //type of end line sequence
        int elements = 0;
        int cLN = 0; //current line number
        int test = 0;

        /* Member Functions */
        void indexFiles(std::string directory);
        void indexFile();
        void processLine(const std::string &line, std::string currFilePath);
        void insertWord(std::string word, std::string currFilePath, 
                        bool insen = false);
        // void insertCaseSensWord(std::string word, std::string currFilePath);
        // void insertCaseInSensWord(std::string word, std::string currFilePath);
        void rehash();
        int  hashWord(std::string word);
        int  quadraticProbe(int value, int attempts);
        std::string toLower(std::string word);
        

        /* Helper Functions */
        void getFileNames(DirNode *root, std::string path);
        bool isAlphaNum(char c);
        std::string stripNonAlphaNum(std::string input);
        void insertNewLine(std::string currFile, int hash, bool insens);


};



#endif 