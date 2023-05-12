/**
* \file utils.h
* Functions independent of the rest of the modules
*/

#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include <string>

/// default file paths for data
#define PATH_CHAR "../data/characters.txt"
#define PATH_EQ "../data/equipment.txt"
#define PATH_TMP "../data/tmp.txt"


using std::string;

/**  \brief Remove a line starting with a word
 *  Remove item/character from file and save the new version
 * limits characters to unique names.
 * \param name chosen word
 * \param file_path path of the file used
*/
void remove_from_file(string name, string file_path);


#endif // UTILS_H
