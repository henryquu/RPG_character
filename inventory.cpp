#include "inventory.h"
#include <fstream>


string item_types[] = {"Helmet", "Chestplate", "Leggings", "Boots", "Wand", "Bow", "Sword"};


Item::Item(string Name, string Type, int Damage[2], int Range, int Stats[3], int Weight){
    name = Name;
    type = Type;

    if (is_weapon(Type))
        for (int i=0; i < 2; i++)
            damage[i] = Damage[i];

    for (int i=0; i < 3; i++)
        stats[i] = Stats[i];

    range = Range;
    weight = Weight;
}

// save into a file
void Item::save(std::ofstream &file){
    file << " | " << name <<  ' ' << type <<  ' ' << equipped <<  ' ' << weight;

    if (is_weapon(type))
        file <<  ' ' << damage[0] <<  ' ' << damage[1] <<  ' ' << range;

    for (int i=0; i < 3; i++)
        file << ' ' << stats[i];
}

// return sum of weights of the inventory
int inventory_weight(Item *ptr){
    int weight = 0;

    while (ptr){
        weight += ptr->weight;
        ptr = ptr->next;
    }

    return weight;
}

// avaible weight from the starting MAX_WEIGHT
int weight_avaible(Item *ptr){
    return MAX_WEIGHT - inventory_weight(ptr);
}

// checks if the type is a weapon
bool is_weapon(string type){
    if (type.compare("Wand") == 0 || type.compare("Bow") == 0 || type.compare("Sword") == 0)
        return true;
    return false;
}

// checks if chosen type of equipment is not used already
bool type_available(Item *ptr, string type){
    while (ptr){
        if (ptr->equipped)
            if (type.compare(ptr->type) == 0 || (is_weapon(type) && is_weapon(ptr->type)))
                return false;
        
        ptr = ptr->next;
    }

    return true;
}

// sums basic stats from equipped items
int *stats_from_equipment(Item *ptr){
    int *lst = new int[6]{0};

    while (ptr){
        if (ptr->equipped){
            for (int i=0; i < 3; i++)
                lst[i] += ptr->stats[i];
            if (is_weapon(ptr->type)){
                lst[3] = ptr->range;
                lst[4] = ptr->damage[0];
                lst[5] = ptr->damage[1];
            }
        }
        ptr = ptr->next;
    }

    return lst;
}

// adds items to the end of the inventory
void add_item(Item *&head, Item *item){
    if (!head){
        head = item;
        return;
    }

    Item *ptr = head;
    while (ptr->next)
        ptr = ptr->next;

    ptr->next = item;
}

// deletes item using it's name
void delete_item_name(Item *&head, string name){
    Item *ptr = head;
    Item *prev = head;

    while (ptr){
        if (name.compare(ptr->name) == 0){
            if (head == ptr)
                head = ptr->next;

            prev->next = ptr->next;

            delete ptr;
        }

        prev = ptr;
        ptr = ptr->next;
    }
}

// deletes the whole inventory
void delete_inventory(Item *&head){
    Item *ptr = head;

    while (ptr){
        head = head->next;
        delete ptr;
        ptr = head;
    }
}

// creates an item with random base stats
Item *create_item(string name, string type){
    int damage[2];
    int range = 0;
    int stats[3];
    int weight;

    srand(time(0));

    if (is_weapon(type)){
        damage[0] = 50 + rand() % 80;
        damage[1] = damage[0] + rand() % 20;

        range = 1;
        if(type.compare("Sword") != 0)
            range = 5;
    }

    for (int i=0; i < 3; i++)
        stats[i] = 10 + rand() % 20;

    weight = 60 + rand() % 10;

    Item *item = new Item(name, type, damage, range, stats, weight);
    return item;
}

// saves inventory to the file
void save_inventory(string name, Item *inventory){
    remove_from_file(name, PATH_EQ);

    std::ofstream file(PATH_EQ, std::ofstream::app);
    Item *ptr = inventory;
    
    file << name;

    if (!ptr)
        file << " | ";

    while(ptr){
        ptr->save(file);
        ptr = ptr->next;
    }

    file << '\n';
    file.close();
}

// takes as input a pointer in the file
// loads stats and creates an item
Item *load_item(std::ifstream &file){
    string name = "";
    string type;

    bool equipped = false;
    int weight = 0;

    int damage[2] = {0, 0};
    int range = 0;
    int stats[3] = {0, 0, 0};

    file >> name >> type >> equipped >> weight;

    if (is_weapon(type))
        file >> damage[0] >> damage[1] >> range;

    for (int i = 0; i < 3; i++)
        file >> stats[i];
    
    if (name.compare("") == 0)
        return nullptr;

    Item *ptr = new Item(name, type, damage, range, stats, weight);
    ptr->equipped = equipped;

    return ptr;
}

// loads all items owned by a character
Item *load_inventory(string char_name){
    Item *head = nullptr;
    Item *ptr;

    std::ifstream file(PATH_EQ);

    string name;
    char symbol;

    while (file.good()){
        file >> name;

        if (char_name.compare(name) == 0){

            while (file.good()){
                file >> symbol;

                if (symbol == '|'){
                    if (!head){
                        head = load_item(file);
                        ptr = head;
                    }
                    else{
                        ptr->next = load_item(file);
                        ptr = ptr->next;
                    }
                }
                else
                    break;
            }
        }
    }

    file.close();

    return head;
}
