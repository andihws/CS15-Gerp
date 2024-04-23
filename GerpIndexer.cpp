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
            processLine(line);
        }
    }
}

set<string> GerpIndexer::processLine(const string& line) {
    if (not isCRLF) 
        cLN = cLN + line.length() + 1;
    else 
        cLN = cLN + line.length() + 2;
    stringstream ss(line);
    string word;
    set<string> words;

    while (ss >> word) {
        word = stripNonAlphaNum(word);
        words.insert(word);
    }

    return words;
}

string GerpIndexer::toLower(string word){
    string newWord = "";
    for(int i = 0; i < word.length(); i++){
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

    while (hashTable[value].key != "" or hashTable[value].key != word)
        value = quadraticProbe(value, ++attempts);     

    /* Case 1: Word is already on the hash table */
    if (hashTable[value].key == word) {
        /* If it is converting the word to lower case, add to insens */
        if (insen == true) 
            hashTable[value].isLines.back().lines.push_back(cLN);
        /* If the word is already lower case, add to both */
        else if (word == toLower(word)) { 
            hashTable[value].sLines.back().lines.push_back(cLN);
            hashTable[value].isLines.back().lines.push_back(cLN);
        } 
        /* Otherwise, add word to caseSens if not all lowercase*/
        else 
            hashTable[value].sLines.back().lines.push_back(cLN);
    } else {
        Word newWord;
        newWord.key = word;
        newWord.value = value;
        Line lineCaseSens;
        Line lineCaseInSens;
        /*add the caseSen line if it doesnt exist*/
        hashTable[newWord.value] = newWord;
        lineCaseSens.filePath = currFilePath;
        lineCaseSens.lines.push_back(cLN);
        hashTable[newWord.value].sLines.push_back(lineCaseSens);    

        /*add the caseSen line if it doesnt exist and lowercase*/
        if (insen = true) {
            hashTable[newWord.value] = newWord;
            lineCaseInSens.filePath = currFilePath;
            lineCaseInSens.lines.push_back(cLN);
            hashTable[newWord.value].isLines.push_back(lineCaseInSens);            
        }
    }
}

    

//we need the file path for each word...
void GerpIndexer::insertCaseSensWord(string word, string currFilePath) {
    
}

//need to avoid rehashing words that are already all lowercase 
// if( word != toLower(word) ) add it into the hash table using another function 
/*
void GerpIndexer::insertCaseSensWord(string word, string currFilePath) {
    Line lineCaseSens;
    Word newWord;
    int attempts = 0;
    newWord.key = word;
    newWord.value = hashWord(word);
    while (hashTable[newWord.value].key != "" or hashTable[newWord.value].key == word) {
        newWord.value = quadraticProbe(newWord.value, attempts);

        //check of word isnt already lowercase
        if (word != toLower(word)){
            caseinsensInsert(word, currFilePath)
        }
    }
        
    hashTable[newWord.value] = newWord;
    lineCaseSens.filePath = currFilePath;
    lineCaseSens.lines.push_back(cLN);
    hashTable[newWord.value].sLines.push_back(lineCaseSens);
}


void GerpIndexer::insertInsensWord(string word, string currFilePath) {
    
}
*/




void GerpIndexer::rehash() {
    if (float(elements)/float(hashTable.capacity()) > 0.72) {
        vector<Word> tempHashTable = hashTable;
        primeIndex++;
        vector<Word> newHashTable {size_t(prime[primeIndex])};
        hashTable = newHashTable;
        for (int i = 0; i < tempHashTable.size(); i++) {
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