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

        //search

    private:
        //member variables for hash table
        std::vector<std::string> filepaths;
        struct Word {
            std::string key = "";
            std::vector<std::pair<int, std::vector<int> > > lineNums;
        };
        
        std::vector<std::pair<std::string, std::vector<Word> > > hashTable;

        //file storing members and functions
        void makeFileTree(std::string directory);

        //hash members and functions
        std::hash<std::string> hasher;
        size_t prime[26] = {1013, 6131, 11621, 23291, 35671, 42013, 61543, 81667, 
                            102161, 116239, 137239, 257591, 307283, 507961, 
                            1000003, 2269733, 3042161, 4535189, 7474967,
                            9737333, 14161729, 17624813, 19734581, 23391799, 
                            29499439, 37139213};
        int primeIndex = 0;
        int capacity;
        int numElements = 0;
        void rehash();
        int  hashWord(std::string word);
        int  quadraticProbe(int value, int attempts);
        void wordInsert(std::string word, int linenum, int filepath);
        void insertUniqueWords(int linenum, int filepath, std::string line);

        //helper functions
        void getFileNames(std::vector<std::string> &paths, DirNode *root, std::string path);
        std::string stripNonAlphaNum(std::string input);
        bool isAlphaNum(char c);
        void indexFiles(std::string directory);
        std::string toLower(std::string word);
        void open_or_die(std::ifstream &stream, std::string fileName);
        void abort(std::string errorMessage);


};



#endif 