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
    hashTable.resize(prime[primeIndex]);
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

void GerpIndexer::indexFile() {
    ifstream infile;
    string line = "";
    for (size_t i = 0; i < paths.size(); i++) {
        infile.open(paths[i]);
        while (getline(infile, line)) {
            processLine(line, paths[i]);
        }
        infile.close();
        cLN = 0;
    }
}

void GerpIndexer::processLine(const string& line, string currFilePath) {
    stringstream ss(line);
    string word;
    set<string> words;

    while (ss >> word) {
        word = stripNonAlphaNum(word);
        if (not word.empty()) 
            words.insert(word);
    }

    for (string w : words) {
        insertWord(w, currFilePath);
    }

    if (not isCRLF) 
        cLN = cLN + line.length() + 1;
    else 
        cLN = cLN + line.length() + 2;
}

string GerpIndexer::toLower(string word){
    string newWord = "";
    for(int i = 0; i < int(word.length()); i++) {
        newWord += char(tolower(word[i]));
    }
    
    return newWord;
}


void GerpIndexer::insertWord(string word, string currFilePath, bool insen) {
    elements++;
    rehash();
    int attempts = 0;
    int value = hashWord(word);
    if (word != toLower(word)) 
        insertWord(toLower(word), currFilePath, true);

    while (hashTable[value].key != "" and hashTable[value].key != word)
        value = quadraticProbe(value, ++attempts);

    /* Case 1: Word is already on the hash table */
    if (hashTable[value].key == word) {
        /* If it is converting the word to lower case, add to insens */
        if (insen == true) {    
            if (hashTable[value].isLines.back().filePath == currFilePath) 
                hashTable[value].isLines.back().lines.insert(cLN);
            else 
                insertNewLine(currFilePath, value, true);
        }
        /* If the word is already lower case, add to both */
        else if (word == toLower(word)) { 
            if (hashTable[value].sLines.back().filePath == currFilePath) 
                hashTable[value].sLines.back().lines.insert(cLN);
            else 
                insertNewLine(currFilePath, value, false);
            if (hashTable[value].isLines.back().filePath == currFilePath) 
                hashTable[value].isLines.back().lines.insert(cLN);
            else 
                insertNewLine(currFilePath, value, true);
        } 
        /* Otherwise, add word to caseSens if not all lowercase*/
        else {
            if (hashTable[value].sLines.back().filePath == currFilePath) 
                hashTable[value].sLines.back().lines.insert(cLN);
            else 
                insertNewLine(currFilePath, value, false);
        }
    } else {
        Word newWord;
        newWord.key = word;
        newWord.value = value;
        
        /*add the caseSen line if it doesnt exist*/
        hashTable[newWord.value] = newWord;
        insertNewLine(currFilePath, value, false);

        /*add the caseSen line if it doesnt exist and lowercase*/
        if (insen == true or word == toLower(word)) {
            insertNewLine(currFilePath, value, true);          
        }
    }   
}


void GerpIndexer::insertNewLine(std::string currFile, int hash, bool insens) {
    if (insens == false) {
        Line lineCaseSens;
        lineCaseSens.filePath = currFile;
        lineCaseSens.lines.insert(cLN);
        hashTable[hash].sLines.push_back(lineCaseSens);
    } else {
        Line lineCaseInSens;
        lineCaseInSens.filePath = currFile;
        lineCaseInSens.lines.insert(cLN);
        hashTable[hash].isLines.push_back(lineCaseInSens);         
    }
}


void GerpIndexer::rehash() {
    if (float(elements)/float(hashTable.capacity()) > 0.72) {
        cout << ++test << endl;
        vector<Word> tempHashTable = hashTable;
        primeIndex++;
        vector<Word> newHashTable;
        newHashTable.resize(prime[primeIndex]);
        hashTable = newHashTable;
        for (size_t i = 0; i < tempHashTable.size(); i++) {
            if (not tempHashTable[i].key.empty()) {
                tempHashTable[i].value = hashWord(tempHashTable[i].key);
                hashTable[tempHashTable[i].value] = tempHashTable[i];
            }
        }
    }
}

 
int GerpIndexer::hashWord(string word) {
    return hasher(word) % hashTable.capacity();
}

int GerpIndexer::quadraticProbe(int value, int attempts) {
    return (value + attempts * attempts) % hashTable.capacity();
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