/**
 * \file characters.h
 * \brief Character class
 * character class and it's functions
 */

#ifndef CHARACTERS_H
#define CHARACTERS_H


#include "inventory.h"


using std::string;

/// Current number of classes in creator
#define CLASSES_COUNT 3
/// Current number of races in creator
#define RACES_COUNT 3

/// List of available races
extern string races[RACES_COUNT];
/// List of available classes
extern string classes[CLASSES_COUNT];


/**
 * @brief The Character class
 */
class Character{
    public:
        /// Name of the character
        string name;

        /// Race
        string race;
        /// Class
        string class_;

        /// Basic stats: intelligence, dexterity, strength
        int stats[3];
        //// Main stat used by the character, used in calculating damage dealt
        int main_stat;

        /// Range of the character
        int range = 1;
        /// Min and max values of damage dealt
        int damage[2] = {0, 0};

        /// Ptr to character's inventory
        Item *inventory = nullptr;

        /**
         * @brief Character constructor
         * @param Name name
         * @param Race race
         * @param Class_ class
         * @param Stats basic stats
         * @param Main_stat main stat
         */
        Character(string Name, string Race, string Class_, int *Stats, int Main_stat);

        /**
         * @brief Destructor
         */
        ~Character();

        /**
         * @brief Save character
         * Saves character into the PATH_CHAR file
         */
        void save();
};


/**
 * @brief Create a character
 * Creates a character with default stats adjusted to it's class and race
 * @param name name of the character
 * @param class_ used in classes array
 * @param race used in races array
 * @return ptr to the created character object
 */
Character *create_character(string name, int class_, int race);

/**
 * @brief load a character
 * Loads character from PATH_CHAR file, uses line number
 * @param nr number of line to laod the character from
 * @return ptr to the created character object
 */
Character *load_character(int nr);


#endif 
