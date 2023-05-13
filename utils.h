/**
* \file utils.h
* Functions independent of the rest of the modules
*/

#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include <string>

/// Default file paths for saving and loading characters
#define PATH_CHAR "../data/characters.txt"
/// Default file paths for saving and loading inventory
#define PATH_EQ "../data/equipment.txt"
/// Default file paths for creating a temporary file
#define PATH_TMP "../data/tmp.txt"


using std::string;

/**
 *  @brief Remove item/character from file and save the new version.
 * *limits characters to unique names*
 * \param name chosen word
 * \param file_path path of the file used
*/
void remove_from_file(string name, string file_path);


#endif // UTILS_H
