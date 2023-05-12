#ifndef INVENTORY_H
#define INVENTORY_H


#include "utils.h"

/// max weight available in inventory
#define MAX_WEIGHT 600
/// number of available types of items
#define ITEMS_TYPES_COUNT 7

/// list of available types of items
extern string item_types[ITEMS_TYPES_COUNT];

/**
 * @brief Item structure
 * Item structure with some basic stats and pointer to the next item
 */
struct Item {
    /// Name of the item
    std::string name;
    /// Type, from item_types array
    std::string type;

    /// Used when couting full stats and checking for type lost aailability
    bool equipped = false;
    /// Weight of the item
    int weight = 0;

    /// Min and max values of damage dealt
    int damage[2] = {0, 0};
    /// Range given by the item, 0 for non weapons
    int range = 0;
    /// Base stats: intelligence, dexterity, strength
    int stats[3] = {0, 0, 0};

    /// Pointer to the next item
    Item *next = nullptr;

    /**
     * @brief Item constructor
     * @param Name name
     * @param Type type
     * @param Damage min and max damage dealt
     * @param Range range
     * @param Stats base stats
     * @param Weight weight
     */
    Item(std::string Name, std::string Type, int Damage[2], int Range, int Stats[3], int Weight);

    /**
     * @brief Save file
     * Save item into the file stream
     * @param file already open file stream
     */
    void save(std::ofstream &file);
};


/**
 * @brief Inventory weight
 * Count weight of the whole inventory
 * @param ptr ptr to the inventory
 * @return weight
 */
int inventory_weight(Item *ptr);


/**
 * @brief Available weight
 * Count available inventory weight
 * @param ptr ptr to the inventory
 * @return available weight
 */
int weight_avaible(Item *ptr);

/**
 * @brief Is weapon?
 * CHeck if item is of weapon type
 * @param type type
 * @return true if item is a weapon
 */
bool is_weapon(string type);

/**
 * @brief Type available?
 * Check if the type is already equipped in the inventory
 * @param ptr ptr to the inventory
 * @param type type of the item
 * @return true if no such item equipped
 */
bool type_available(Item *ptr, string type);

/**
 * @brief Stats from equipment
 * Counts base stats from equipped items
 * and damage + range if it's a weapon
 * @param ptr ptr to the inventory
 * @return array with 6 numbers
 */
int *stats_from_equipment(Item *ptr);

/**
 * @brief Add item
 * Adds item to the end of the inventory
 * @param head ptr to the inventory
 * @param item item to add
 */
void add_item(Item *&head, Item *item);

/**
 * @brief Delete item using it's name
 * Deletes item from the inventory
 * by using it's name
 * @param head ptr to the inventory
 * @param name name of the item
 */
void delete_item_name(Item *&head, string name);


/**
 * @brief Delete inventory
 * Deletes the inventory from the memory
 * @param head ptr to the inventory
 */
void delete_inventory(Item *&head);

/**
 * @brief Create item
 * Creates an item of chosen type
 * @param name name
 * @param type type of the item
 * @return ptr to the item
 */
Item *create_item(string name, string type);

/**
 * @brief Save inventory
 * Save inventory into a file
 * @param name name of the character who owns the items
 * @param inventory ptr to the inventory
 */
void save_inventory(string name, Item *inventory);

/**
 * @brief Load item
 * Loads an item from a file stream
 * @param file file stream
 * @return ptr to the item
 */
Item *load_item(std::ifstream &file);

/**
 * @brief Load inventory
 * Loads inventory of a character
 * @param char_name name of the character
 * @return ptr to the first inventory
 */
Item *load_inventory(string char_name);

#endif // INVENTORY_H
