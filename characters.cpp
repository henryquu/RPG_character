#include "characters.h"
#include <fstream>
#include <limits>

string classes[CLASSES_COUNT] = {"Mage", "Archer", "Warrior"};
string races[RACES_COUNT] = {"Human", "Elf", "Orc"};

Character::Character(string Name, string Race, string Class_, int *Stats, int Main_stat) { 
    name = Name;
    race = Race;
    class_ = Class_;
    
    for (int i = 0; i < 3; i++)
        stats[i] = Stats[i];

    main_stat = Main_stat;
};

Character::~Character(){
    delete_inventory(inventory);
}

void Character::save(){
    remove_from_file(name, PATH_CHAR);

    std::ofstream file(PATH_CHAR, std::ofstream::app);

    file << name << " " << race << " " << class_;
    for (int i = 0; i < 3; i++)
        file << " " << stats[i];
    file << " " << main_stat << '\n';

    file.close();

    save_equipment(name, inventory);
}

Character *create_character(string name, int class_, int race){
    int stats[3] = {40, 40, 40};

    switch (race){
    case 0:
            stats[0] += 20;
            stats[1] -= 10;
            stats[2] -= 10;
            break;
    case 1:
            stats[1] += 20;
            stats[2] -= 20;
            break;
    case 2:
            stats[0] -= 20;
            stats[1] -= 20;
            stats[2] += 40;
            break;
    }
    stats[class_] += 20;

    Character *character = new Character(name, races[race], classes[class_], stats, class_);
    return character;
}

Character *load_character(int nr){
    string name, race, class_;

    int stats[3] = {-1, -1, -1};
    int main_stat;

    std::ifstream file(PATH_CHAR);
    std::string line;

    for (int i = 0; i < nr; i++){
            if (!file.good())
                return nullptr;
            std::getline(file, line);
    }

    file >> name;

    file >> race >> class_;

    for (int i = 0; i < 3; i++)
            file >> stats[i];

    file >> main_stat;

    file.close();

    Character *character = new Character(name, race, class_, stats, main_stat);
    character->inventory = load_equipment(name);

    return character;
}
