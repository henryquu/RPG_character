#ifndef CHARACTERS_H
#define CHARACTERS_H


#include "inventory.h"


using std::string;


#define CLASSES_COUNT 3
#define RACES_COUNT 3


extern string races[RACES_COUNT];
extern string classes[CLASSES_COUNT];


class Character{
    public:
        string name;

        string race;
        string class_;

        int stats[3];
        int main_stat;

        int range = 1;
        int damage[2] = {0, 0};

        Item *inventory = nullptr;

        Character(string Name, string Race, string Class_, int *Stats, int Main_stat);

        ~Character();

        void save(); // save character in a file
};


// create a character
Character *create_character(string name, int class_, int race);

// load character from file using it's index number
Character *load_character(int nr);


#endif 
