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