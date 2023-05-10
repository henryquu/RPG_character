#ifndef INVENTORY_H
#define INVENTORY_H


#include "utils.h"


#define MAX_WEIGHT 450
#define ITEMS_TYPES_COUNT 7


extern string item_types[];


struct Item {
    std::string name;
    std::string type;

    bool equipped = false;
    int weight = 0;

    int damage[2] = {0, 0};
    int range = 0;
    int stats[3] = {0, 0, 0};

    Item *next = nullptr;

    Item(std::string Name, std::string Type, int Damage[2], int Range, int Stats[3], int Weight);

    void save(std::ofstream &file); // save into a file
};


// return sum of weights of the inventory
int inventory_weight(Item *ptr);

// returns avaible weight from the starting MAX_WEIGHT
int weight_avaible(Item *ptr);

// checks if the type is a weapon
bool is_weapon(string type);

// checks if chosen type of equipment is not used already
bool type_avaible(Item *ptr, string type);

// sums basic stats from equipped items
int *stats_from_equipment(Item *ptr);

// adds items to the end of the inventory
void add_item(Item *&head, Item *item);

// deletes item using it's name
void delete_item_name(Item *&head, string name);

// deletes the whole inventory, mainly for memory leaks
void delete_inventory(Item *&head);

// creates an item with random base stats
Item *create_item(string name, string type);

// saves equipment to the file
void save_equipment(string name, Item *inventory);

// takes as input a pointer in the file
// loads stats and creates an item
Item *load_item(std::ifstream &file);

// loads all items owned by a character
Item *load_equipment(string char_name);

#endif 
