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

        //search and indexing
        void indexFiles(std::string directory);
        void insensSearch(std::string word, std::ofstream &outstream);
        void sensSearch(std::string word, std::ofstream &outstream);
        std::string stripNonAlphaNum(std::string input);


    // private:
        //member variables for hash table
        std::vector<std::string> filepaths;
        struct WordData {
            std::string word = "";
            int filePath;
            int lineNum;
        };
        std::vector<std::vector<WordData>> hashTable;

        //file storing members and functions
        std::vector<std::vector<std::string>> files;
        void makeFileTree(std::string directory);

        //hash members and functions
        std::hash<std::string> hash;
        int numElements = 0;
        void rehash();
        int getHash(std::string word);
        int linearProbe(int value, int attempts);
        void wordInsert(std::string word, int linenum, int filepath);
        void insertUniqueWords(int linenum, int filepath, std::string line);

        //helper functions
        void getFileNames(std::vector<std::string> &paths, DirNode *root, 
                          std::string path);
        bool isAlphaNum(char c);
        std::string toLower(std::string word);
        void open_or_die(std::ifstream &stream, std::string fileName);
        void abort(std::string errorMessage);
        int probeCheck(std::string word);
        void insensPrint(int value, std::ofstream &outstream);
        void sensPrint(int value, std::string word, std::ofstream &outstream);

};



#endif 