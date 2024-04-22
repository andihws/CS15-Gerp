/*
 *  GerpIndexer.cpp
 *  Allison Zhang and Baydan Hussen (bhusse01 and yzhang80)
 *  4/14/23
 *
 *  CS 15 Project 4 Gerp - Gerp.
 *
 *  Implentation of the GerpIndexer class
 *
 */


#include "GerpIndexer.h"

using namespace std;

GerpIndexer::GerpIndexer() {
    
}

GerpIndexer::~GerpIndexer() {

}

/*
 * name: indexFiles
 * purpose: Gets all paths of all files accessible from a specified directory
 * arguments: A string representing the root directory
 * returns: N/A
 * effects: Updates the paths vector member variable with al; possible file 
 *          paths
 */
void GerpIndexer::indexFiles(string directory) {
    FSTree fileTree = FSTree(directory);
    DirNode *root = fileTree.getRoot();
    if (not root->isEmpty()) 
        getFileNames(root, "");
}

void GerpIndexer::indexFile(string filePath) {
    ifstream infile;
    string line = "";
    for (size_t i = 0; i < paths.size(); i++) {
        infile.open(paths[i]);
        while (getline(infile, line)) {

        }
    }
}

void GerpIndexer::processLine(string line, set<string> &words) {
    set<string> words; 
    char seperator = ' ';
}

void GerpIndexer::insertWord(string word) {
    elements++;
    rehash();
    Word newWord;
    newWord.key = word;
    newWord.value = hashWord(word);
    hashTable[newWord.value];
}

void GerpIndexer::rehash() {
    if (float(elements)/float(hashTable.capacity()) > 0.72) {
        elements = 0;
        size_t currCapacity = hashTable.capacity();
        vector<Word> tempHashTable = hashTable;
        hashTable.resize(currCapacity * 2);
        for (int i = 0; i < tempHashTable.size(); i++) {
            if (not tempHashTable[i].key.empty()) {
                insertWord(tempHashTable[i].key);
            }
        }
    }
}

int GerpIndexer::hashWord(string word) {
    
}

/*
 * name: getFileNames
 * purpose: Push all file paths and files onto a provided vector from a file
 *          tree
 * arguments: A vector where paths are added, a DirNode pointer to the root
 *            of the file tree(or the current parent directory) and a string
 *            representing the actual file path 
 * returns: N/A
 * effects: Adds all file paths to the vector as strings
 */
void GerpIndexer::getFileNames(DirNode *root, string path) {
    path = path + root->getName() + "/";

    for (int i = 0; i < root->numFiles(); i++) 
        paths.push_back(path + root->getFile(i));

    for (int i = 0; i < root->numSubDirs(); i++) 
        getFileNames(root->getSubDir(i), path);
}

/*
 * name: isAlphaNum
 * purpose: Determines if a character is AlphaNumeric
 * arguments: A character that will be tested
 * returns: True or false depending on if the character is AlphaNumeric
 * effects: N/A
 */
bool GerpIndexer::isAlphaNum(char c) {
    if ((48 <= int(c) and int(c) <= 57) or (65 <= int(c) and int(c) <= 90) 
        or (97 <= int(c) and int(c) <= 122)) {
        return true;
    }
    return false;
}

/*
 * name: stripNonAlphaNum
 * purpose: Remove non-alphanumeric characters from the beginning and end of a
 *          string
 * arguments: String to be stripped
 * returns: A stripped string
 * effects: N/A
 */
string GerpIndexer::stripNonAlphaNum(string input) {
    int begin = 0;
    int end = 0;

    while (not isAlphaNum(input[begin]) && begin < int(input.length())) 
        begin++;

    input = input.erase(0, begin);

    for (int i = 0; i < int(input.length()); i++) 
        if (isAlphaNum(input[i])) 
            end = i;

    
    if (input.length() > 0) 
        input = input.erase(end + 1, input.length() - end); 
    

    return input;
}