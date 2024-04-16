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