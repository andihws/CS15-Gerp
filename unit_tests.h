/*
 *  Processing.cpp
 *  Allison Zhang and Baydan Hussen (bhusse01 and yzhang80)
 *  4/14/23
 *
 *  CS 15 Project 4 Gerp - Gerp.
 *
 *  Unit Testing for Processing.cpp
 *
 */

#include <cassert>
#include <istream>
#include <sstream>
#include <chrono>
#include "processing.h"
#include "GerpIndexer.h"

using namespace std;

//test for removing heading and tailing
//non-alpha numeric characters
void testRemoveNonAlphaNum() {
    assert(stripNonAlphaNum("..Allison..") == "Allison");
}

//test for a string with all non-alpha
//numeric characters
void testRemoveNonAlphaNumNone() {
    assert(stripNonAlphaNum("....") == "");
}

//test for removing non-alpha numeric
//characters from a string with a 
//single alpha-numeric character
void testRemoveNonAlphaNumOneLetter() {
    assert(stripNonAlphaNum("..A..") == "A");
}

//test for removing heading and tailing
//non alpha numeric characters and not
//alpha numeric characters within a word
void testRemoveNonAlphaLetterInside() { 
    assert(stripNonAlphaNum("...Jel-o//") == "Jel-o");
}

//test removeNonAlpha letters 
//when there is nothing to be removed
void testRemoveNonAlphaLetterNoRemoval() {
    assert(stripNonAlphaNum("When") == "When");
}

void testTraverseFile() {
    traverseDirectory("tinyData");
}

void correctHashTableSizeTest() {
    GerpIndexer l;
    assert(l.hashTable.capacity() == 6131);
}

void hashWordTest() {
    GerpIndexer l;
    cout << l.hashWord("Bean") << endl;
    cout << l.hashWord("bean") << endl;
}

void quadraticProbing() {
    GerpIndexer l;
    cout << l.quadraticProbe(l.hashWord("bean"), 1) << endl;
    cout << l.quadraticProbe(l.hashWord("bean"), 2) << endl;
    cout << l.quadraticProbe(l.hashWord("bean"), 10) << endl;
}

void rehashTest() {
    GerpIndexer l;
    GerpIndexer::Word w;
    w.key = "bean";
    w.value = l.hashWord("bean");
    cout << l.hashTable.capacity() << endl;
    cout << l.hasher("bean") << endl;
    cout << l.hasher("bean") % l.hashTable.capacity() << endl;
    l.hashTable[w.value] = w;
    l.rehash();
    cout << l.hashTable[l.hashWord("bean")].value << endl;
}

void toLowerTest() {
    GerpIndexer l;
    cout << l.toLower("BEAN") << endl;
}

void insertWordTestAllLower() {
    GerpIndexer l;
    l.insertWord("bean", "/test/text.txt", false);
    cout << l.hashTable[l.hashWord("bean")].value << endl;
}

// void insertWordTestAllUpper() {
//     GerpIndexer l;
//     l.cLN = 100;
//     l.insertWord("Bean", "/test/text.txt", false);
//     cout << l.hashTable[l.hashWord("bean")].value << endl;
//     cout << l.hashTable[l.hashWord("bean")].isLines[0].lines[0] << endl;
//     cout << l.hashTable[l.hashWord("Bean")].value << endl;
//     cout << l.hashTable[l.hashWord("Bean")].sLines[0].lines[0] << endl;
// }

// void insertWordTestRepeat() {
//     GerpIndexer l;
//     l.cLN = 100;
//     l.insertWord("bean", "/test/text.txt", false); 
//     l.cLN = 150;
//     l.insertWord("bean", "/test/text.txt", false);
//     cout << "Hash: " << l.hashTable[l.hashWord("bean")].value << endl;
//     cout << "Word: " << l.hashTable[l.hashWord("bean")].key << endl;
//     cout << "File Path IS: " << l.hashTable[l.hashWord("bean")].isLines[0].filePath << endl;
//     for (size_t i = 0; i < l.hashTable[l.hashWord("bean")].isLines[0].lines.size(); i++) {
//         cout << "Line #: " << l.hashTable[l.hashWord("bean")].isLines[0].lines[i] << endl;
//     }
//     cout << "File Path S: " << l.hashTable[l.hashWord("bean")].sLines[0].filePath << endl;
//     for (size_t i = 0; i < l.hashTable[l.hashWord("bean")].sLines[0].lines.size(); i++) {
//         cout << "Line #: " << l.hashTable[l.hashWord("bean")].sLines[0].lines[i] << endl;
//     }

// }

// void insertWordTestUpper() {
//     GerpIndexer l;
//     l.cLN = 100;
//     l.insertWord("bean", "/test/text.txt", false); 
//     l.cLN = 150;
//     l.insertWord("BEAN", "/test/text.txt", false);
//     l.cLN = 200;
//     l.insertWord("Bean", "/test/text.txt", false);
//     l.cLN = 250;
//     l.insertWord("bEan", "/test/text.txt", false);
//     l.cLN = 300;
//     l.insertWord("beAn", "/test/text.txt", false);
//     l.cLN = 350;
//     l.insertWord("beaN", "/test/text.txt", false);
//     cout << "Hash: " << l.hashTable[l.hashWord("bean")].value << endl;
//     cout << "Word: " << l.hashTable[l.hashWord("bean")].key << endl;
//     cout << "File Path IS: " << l.hashTable[l.hashWord("bean")].isLines[0].filePath << endl;
//     for (size_t i = 0; i < l.hashTable[l.hashWord("bean")].isLines[0].lines.size(); i++) {
//         cout << "Line #: " << l.hashTable[l.hashWord("bean")].isLines[0].lines[i] << endl;
//     }
//     cout << "File Path S: " << l.hashTable[l.hashWord("bean")].sLines[0].filePath << endl;
//     for (size_t i = 0; i < l.hashTable[l.hashWord("bean")].sLines[0].lines.size(); i++) {
//         cout << "Line #: " << l.hashTable[l.hashWord("bean")].sLines[0].lines[i] << endl;
//     }

//     cout << "Hash: " << l.hashTable[l.hashWord("BEAN")].value << endl;
//     cout << "Word: " << l.hashTable[l.hashWord("BEAN")].key << endl;
//     cout << "File Path IS: " << l.hashTable[l.hashWord("BEAN")].isLines.size() << endl;
//     // for (size_t i = 0; i < l.hashTable[l.hashWord("BEAN")].isLines[0].lines.size(); i++) {
//     //     cout << "Line #: " << l.hashTable[l.hashWord("BEAN")].isLines[0].lines[i] << endl;
//     // }
//     cout << "File Path S: " << l.hashTable[l.hashWord("BEAN")].sLines[0].filePath << endl;
//     for (size_t i = 0; i < l.hashTable[l.hashWord("BEAN")].sLines[0].lines.size(); i++) {
//         cout << "Line #: " << l.hashTable[l.hashWord("BEAN")].sLines[0].lines[i] << endl;
//     }
    
// }


void indexFilesTest() {
    GerpIndexer l;
    l.indexFiles("tinyData");
    for (size_t i = 0; i < l.paths.size(); i++) {
        cout << l.paths[i] << endl;
    }
    l.indexFiles("testData");
    for (size_t i = 0; i < l.paths.size(); i++) {
        cout << l.paths[i] << endl;
    }
}

void testOpenFile() {
    GerpIndexer l;
    l.indexFiles("tinyData");
    ifstream infile(l.paths[0]);
    string line;
    getline(infile, line);
    cout << line << endl;
}

void processLineTest() {
     GerpIndexer l;
    l.indexFiles("./proj4/tinyData");
    ifstream infile(l.paths[0]);
    string line;
    getline(infile, line);
    //set<string> words = l.processLine(line, l.paths[0]);
    // cout << words.size() << endl;
    // cout << *words.begin() << endl;
    // cout << "Hash: " << l.hashTable[l.hashWord("gerp")].value << endl;
    // cout << "Word: " << l.hashTable[l.hashWord("gerp")].key << endl;
    // cout << "File Path IS: " << l.hashTable[l.hashWord("gerp")].isLines[0].filePath << endl;
    // for (size_t i = 0; i < l.hashTable[l.hashWord("gerp")].isLines[0].lines.size(); i++) {
    //     cout << "Line #: " << l.hashTable[l.hashWord("gerp")].isLines[0].lines[i] << endl;
    // }
    // cout << "File Path S: " << l.hashTable[l.hashWord("gerp")].sLines[0].filePath << endl;
    // for (size_t i = 0; i < l.hashTable[l.hashWord("gerp")].sLines[0].lines.size(); i++) {
    //     cout << "Line #: " << l.hashTable[l.hashWord("gerp")].sLines[0].lines[i] << endl;
    // }
}

void indexFileTest() {
    GerpIndexer l;
    l.indexFiles("./test-dir/tinyData");
    l.indexFile();
    cout << "Hash: " << l.hashTable[l.hashWord("grep")].value << endl;
    cout << "Word: " << l.hashTable[l.hashWord("grep")].key << endl;
}

void indexFileTestSmall() {
    auto start = chrono::high_resolution_clock::now();
    GerpIndexer l;
    l.indexFiles("./testData");
    l.indexFile();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " milliseconds" << endl;

    cout << "Hash: " << l.hashTable[l.hashWord("hello")].value << endl;
    cout << "Word: " << l.hashTable[l.hashWord("hello")].key << endl;
    for (size_t j = 0; j < l.hashTable[l.hashWord("hello")].isLines.size(); j++) {
        cout << "File Path IS: " << l.hashTable[l.hashWord("hello")].isLines[j].filePath << endl;
        for (int ln : l.hashTable[l.hashWord("hello")].isLines[j].lines) {
            cout << ln << endl;
        }
    }
    for (size_t j = 0; j < l.hashTable[l.hashWord("hello")].sLines.size(); j++) {
        cout << "File Path S: " << l.hashTable[l.hashWord("hello")].sLines[j].filePath << endl;
        for (int ln : l.hashTable[l.hashWord("hello")].sLines[j].lines) {
            cout << ln << endl;
        }
    }
}
