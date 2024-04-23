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

void insertWordTestAllUpper() {
    GerpIndexer l;
    l.cLN = 100;
    l.insertWord("Bean", "/test/text.txt", false);
    cout << l.hashTable[l.hashWord("bean")].value << endl;
    cout << l.hashTable[l.hashWord("bean")].isLines[0].lines[0] << endl;
    cout << l.hashTable[l.hashWord("Bean")].value << endl;
    cout << l.hashTable[l.hashWord("Bean")].sLines[0].lines[0] << endl;
}

void insertWordTestRepeat() {
    GerpIndexer l;
    l.cLN = 100;
    l.insertWord("bean", "/test/text.txt", false); 
    l.cLN = 150;
    l.insertWord("bean", "/test/text.txt", false);
    cout << "Word: " << l.hashTable[l.hashWord("bean")].value << endl;
    cout << "Key: " << l.hashTable[l.hashWord("bean")].key << endl;
    cout << "File Path IS: " << l.hashTable[l.hashWord("bean")].isLines[0].filePath << endl;
    for (size_t i = 0; i < l.hashTable[l.hashWord("bean")].isLines[0].lines.size(); i++) {
        cout << "Line #: " << l.hashTable[l.hashWord("bean")].isLines[0].lines[i] << endl;
    }
    cout << "File Path S: " << l.hashTable[l.hashWord("bean")].sLines[0].filePath << endl;
    for (size_t i = 0; i < l.hashTable[l.hashWord("bean")].sLines[0].lines.size(); i++) {
        cout << "Line #: " << l.hashTable[l.hashWord("bean")].sLines[0].lines[i] << endl;
    }

}