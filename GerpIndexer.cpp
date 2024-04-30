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

/*
 * name: 
 * purpose: 
 * arguments: 
 * returns:
 * effects: 
 */
GerpIndexer::GerpIndexer() {
    hashTable.resize(prime[primeIndex]);
}

/*
 * name: 
 * purpose: 
 * arguments: 
 * returns:
 * effects: 
 */
GerpIndexer::~GerpIndexer() {}


/*
 * name: 
 * purpose: 
 * arguments: 
 * returns:
 * effects: 
 */

/*
 * name: indexFiles
 * purpose: adds all the words from all of the files to a hash table
 * arguments: a string to represent the directory specified by the user
 * returns: nothing
 * effects: creates a hash table from a specficied directory
 */
void GerpIndexer::indexFiles(string directory) {
    makeFileTree(directory);
    ifstream instream;
    int linenum = 0;
    string line = "";

    for(size_t i = 0; i < filepaths.size(); i++){
        open_or_die(instream, filepaths[i]);
        //open or die output file in gerp
        vector<string> lineholder;
        files.push_back(lineholder);

        while (getline(instream, line)) {
            //add to files vector 
            files[i].push_back(line);

            //hash words in the line
            if(line.length() > 0) {
               insertUniqueWords(linenum, i, line); 
            }

            linenum++;
        }
        instream.close();

        //reset variables
        linenum = 0;
    }
}

/*
 * name: insertUniqueWords()
 * purpose: inserts the unique words from a line into the hash table
 * arguments: a string for the word, an int as the line number, and
 *            a string as the filepath
 * returns: none
 * effects: adds to the hashtable
 */
void GerpIndexer::insertUniqueWords(int linenum, int filepath, string line) {
    set<string> uniqueWords;
    size_t currSize = 0;
    string theWord;
    stringstream ss(line);

    while(ss >> theWord) {
        theWord = stripNonAlphaNum(theWord);
        if(theWord.length() > 0) {
            uniqueWords.insert(theWord);

            //if the set gets bigger, the word is unique, add to hashtable
            if(uniqueWords.size() > currSize) {
                numElements++;
                rehash();
                wordInsert(theWord, linenum, filepath);
                currSize = uniqueWords.size();
            }            
        }
    }
}

/*
 * name: wordInsert
 * purpose: inserts a word into the hash table in its correct spot
 * arguments: a string for the word, an int as the line number, and
 *            a string as the filepath
 * returns: none
 * effects: makes a new word struct, adds to the hashtable
 */
void GerpIndexer::wordInsert(string word, int linenum, int filepath) {
    WordData neWord;
    neWord.word = word; neWord.lineNum = linenum; neWord.filePath = filepath;
    size_t value = getHash(toLower(word));
    //word doesn't exist in hash table
    if(hashTable[value].empty()) {
        vector<WordData> buckets;
        buckets.push_back(neWord);
        hashTable[value] = buckets;
    //word already exits 
    } else if(toLower(hashTable[value][0].word) == toLower(word)) {
        hashTable[value].push_back(neWord);
    //collision between different words, find pos, make new array, add word
    } else if(toLower(hashTable[value][0].word) != toLower(word)) {
        int attempts = 1;
        bool found = false;
        int newVal = 0;
        while(not found) {
            newVal = linearProbe(value, attempts);
            attempts++;
            if(hashTable[newVal].empty()) {
                vector<WordData> buckets;
                buckets.push_back(neWord);
                hashTable[newVal] = buckets;
                found = true;
            } else if(toLower(hashTable[newVal][0].word) == toLower(word)){
                hashTable[newVal].push_back(neWord);
                found = true;
            } 
        }
    } 
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

/*
 * name: traverseDirectory
 * purpose: Prints all paths of all files accessible from a specified directory
 * arguments: A string representing the root directory
 * returns: N/A
 * effects: Prints out the paths
//  */
// void traverseDirectory(string directory) {
//     vector<string> paths;
//     FSTree fileTree = FSTree(directory);
//     DirNode *root = fileTree.getRoot();
//     if (not root->isEmpty())
//         getFileNames(paths, root, "");
//     for (int i = 0; i < int(paths.size()); i++) 
//         cout << paths[i] << endl;
// }   

/*
 * name: getFileNames
 * purpose: adds all paths of all files 
 *          accessible from a specified directory to a 
 *          vector
 * arguments: a vector for the paths, the root node, and 
 *            a string for the current path name
 * returns: N/A
 * effects: Prints out the paths
 */
void GerpIndexer::getFileNames(vector<string> &paths, 
                                DirNode *root, string path) {
    path = path + root->getName() + "/";

    for (int i = 0; i < root->numFiles(); i++) 
        paths.push_back(path + root->getFile(i));

    for (int i = 0; i < root->numSubDirs(); i++) 
        getFileNames(paths, root->getSubDir(i), path);
}

/*
 * name: makeFileTree
 * purpose: makes the file tree and adds the paths to an array
 * arguments: a string to represent the directory
 * returns: 
 * effects: creates file tree
 */
void GerpIndexer::makeFileTree(string directory) {
    //make the file tree
    FSTree fileTree = FSTree(directory);
    DirNode *root = fileTree.getRoot();

    //make the file paths vector
    getFileNames(filepaths, root, "");
}

/*
 * name: rehash
 * purpose: rehashes the hash table when the load balance is greater than 0.72
 * arguments: none
 * returns: none
 * effects: increases the size of the hash table, allocates more space on the
 *          for the hash table
 */
// void GerpIndexer::rehash() {
//     //check if load balance is greater than 0.72
//     if (float(numElements)/float(hashTable.capacity()) > 0.72) {
//         cout << "going to rehash" << endl;

//         //create a temp hash table
//         //my question is: is the size for the hash too big??? lets go to office hours and ask
//         vector<vector<WordData>> tempTable = hashTable;
//         primeIndex++;

//         //make the new hash table with the new size
//         vector<vector<WordData>> newTable;
//         newTable.resize(prime[primeIndex]);

//         //add the old hash table elements to the new hash table
//         hashTable = newTable;
//         for (size_t i = 0; i < tempTable.size(); i++) {
//             if (not tempTable[i].empty()) {
//                 string theWord = toLower(tempTable[i][0].word);
//                 int index = getHash(theWord);
//                 hashTable[index] = tempTable[i];
//             }
//         }
//     }
// }

void GerpIndexer::rehash() {
    if(float(numElements) / float(hashTable.capacity()) > 0.7) {
        
        size_t newCapacity = (hashTable.size() + 2) * 2;
        vector<vector<WordData>> newHash;
        newHash.resize(newCapacity);

        //maybe risky becasue i am just copying the whole vector over
        for(size_t i = 0; i < hashTable.size(); i++) {
            if(not hashTable[i].empty()) {
                size_t newIndex = hash(toLower(hashTable[i][0].word)) % newCapacity;
                newHash[newIndex] = hashTable[i];
            }            
        }

        hashTable = newHash;
    }
}

/*
 * name: toLower
 * purpose: to make a word all lower case
 * arguments: a string word to be lowercased
 * returns: the lowercase word
 * effects: none
 */
string GerpIndexer::toLower(string word) {
    string newWord = "";
    for(int i = 0; i < int(word.length()); i++) {
        newWord += char(tolower(word[i]));
    }
    
    return newWord;
}

/*
 * name: getHash
 * purpose: to hash a word
 * arguments: a string representing the word to be hashed
 * returns: an int represented the passed in word's hash value
 * effects: none
 */
int GerpIndexer::getHash(string word) {
    return hash(word) % hashTable.capacity();
}

/*
 * name: quadraticProbe
 * purpose: to deal with collisions in the hashtable
 * arguments: an int value for the words hash value and the number of 
 *            rehashing attempts
 * returns: the new hash value/ index for the hash table
 * effects: none
 */
int GerpIndexer::quadraticProbe(int value, int attempts) {
    return (value + attempts * attempts) % hashTable.capacity();
}

/*
 * name: linearProbe
 * purpose: to deal with collisions in the hashtable
 * arguments: an int value for the words hash value and the number of 
 *            rehashing attempts
 * returns: the new hash value/ index for the hash table
 * effects: none
 */
int GerpIndexer::linearProbe(int value, int attempts) {
    return (value + attempts) % hashTable.capacity();
}

/*
 * name:      abort(string errorMessage)
 * purpose:   to send an error message to the user and the program
 * arguments: string errorMessage
 * returns:   technically void, but returns a cerr error message if the file
 *            doesn't open correctly.
 * effects:   ends the program
 */
void GerpIndexer::abort(std::string errorMessage){
    cerr << errorMessage << endl;
    exit(EXIT_FAILURE);
}

/*
 * name:      open_or_die(streamtype &stream, string fileName)
 * purpose:   to check if the file opens correctly 
 * arguments: streamtype object, string filename
 * returns:   technically void, but returns a cerr error message if the file
 *            doesn't open correctly.
 * effects:   ends the program if the file doesn't open correctly
 */
void GerpIndexer::open_or_die(ifstream &stream, std::string fileName){
    stream.open(fileName);
    if(not stream.is_open()){
        abort("Error: could not open file " + fileName);
    }
}



int main() {

    GerpIndexer gerp;

    // gerp.makeFileTree("tinyData");

    // for(size_t i = 0; i < gerp.filepaths.size(); i++){
    //     cout << gerp.filepaths[i] << endl;
    // }

    // cout << gerp.hashTable.capacity() << endl;

//    gerp.indexFiles("largeGutenberg");
   gerp.indexFiles("medium");

    int value = gerp.getHash("a");

    
    // cout << "size array " << gerp.hashTable.size() << endl;
    // cout << "size path  " << gerp.filepaths.size() << endl;

    // for(size_t i = 0; i < gerp.hashTable[value].size(); i++ ){
    //     cout << gerp.hashTable[value][i].word << endl;
    // }

    //test by running insensitive search on demo 
    //then run this with one word

    // cout << "first" << gerp.hashTable[value][0].word  << "." << endl;

    // cout << gerp.files[gerp.hashTable[value][3].filePath][gerp.hashTable[value][3].lineNum] << endl;
    

    //basically insensitive search
    for(size_t i = 0; i < gerp.hashTable[value].size(); i++){
        int filenum = gerp.hashTable[value][i].filePath;
        int line = gerp.hashTable[value][i].lineNum + 1;
        if(i != 0) {
            int filenum2 = gerp.hashTable[value][i - 1].filePath;
            int line2 = gerp.hashTable[value][i -1].lineNum + 1;
            if(filenum2 != filenum && line != line2 ){
                cout << gerp.filepaths[filenum] << ":" << line << ": " << gerp.files[filenum][line - 1] << endl;
            } else if(line == line2 && filenum != filenum2) {
                cout << gerp.filepaths[filenum] << ":" << line << ": " << gerp.files[filenum][line - 1] << endl;

            } else if(line != line2 && filenum == filenum2) {
                cout << gerp.filepaths[filenum] << ":" << line << ": " << gerp.files[filenum][line - 1] << endl;

            } else if(line != line2 && filenum != filenum2){
                cout << gerp.filepaths[filenum] << ":" << line << ": " << gerp.files[filenum][line - 1] << endl;
            }
        }

        if(i == 0){
                cout << gerp.filepaths[filenum] << ":" << line << ": " << gerp.files[filenum][line - 1] << endl;
        }    
    }

    // for(size_t i = 0; i < gerp.hashTable[value].size(); i++){
    //     cout << gerp.filepaths[gerp.hashTable[value][i].filePath] << endl;
    // }
  

    // for(size_t i = 0; i < gerp.files.size(); i++){
    //     cout << gerp.filepaths[i] << endl;
    //     cout << endl;
    //     for(size_t j = 0; j < gerp.files[i].size(); j++){
    //         cout << gerp.files[i][j] << endl;
    //     }
    // }
}



//testing w unit tests idea
/*
1. make chekcing the size of the filepaths array with given values a unit test
2. 


*/

