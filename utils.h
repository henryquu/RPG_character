#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include <string>

// default file paths for data
#define PATH_CHAR "data/characters.txt"
#define PATH_EQ "data/equipment.txt"
#define PATH_TMP "data/tmp.txt"


using std::string;

// remove item/character from file and save the new version
// limits characters to unique names
void remove_from_file(string name, string file_path);


#endif 
