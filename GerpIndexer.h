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
#include <utility>
#include <sstream>
#include <functional>
#include <iostream>
#include <fstream>
#include <set>
#include "FSTree.h"
#include "DirNode.h"

size_t static prime[25] = {10, 7474967, 14161729, 29499439, 37139213};

class GerpIndexer {
    public:
        GerpIndexer();
        ~GerpIndexer();

        struct sensWord {
            std::vector<std::pair<std::vector<int>, int> > lines;
            std::string key;
            int value = -1;
        };

        /* Structs */
        struct Word {
            /*
                Lines where the word is case exact, if the word is "The", it 
                will only contain lines with "The"
            */
            std::vector<sensWord> wordVar; //sensitive lines
            /*
                Lines where the word is case inexact, if the word is "the", it 
                will contain "THe", "The", "THE", and "tHe".
            */
            std::vector<std::pair<std::vector<int>, std::string> > lines;
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
        
        int primeIndex = 0;
        bool isCRLF = false; //type of end line sequence
        int cLN = 0; //current line number
        int rehashAmount = 0;

        /* Member Functions */
        void indexFiles(std::string directory);
        void indexFile();
        void processLine(const std::string &line, int currFilePath);
        // void insertWord(std::string word, std::string currFilePath, 
        //                 bool insen = false);
        void addNewWord(std::string word, int wordHash);
        void insert(std::string word, std::string currFilePath, bool insen);
        void insertWord(std::string word, int currFilePath, bool insen = false);
        void insertSensWord(Word &w, std::string word, std::string currFile);
        void rehash(int capacity);
        int  hashWord(std::string word, int capacity);
        int  quadraticProbe(int value, int attempts);
        std::string toLower(std::string word);
        

        /* Helper Functions */
        void getFileNames(DirNode *root, std::string path);
        bool isAlphaNum(char c);
        std::string stripNonAlphaNum(std::string input);
        void insertNewLine(std::string currFile, Word &word, bool insen);


};



#endif 