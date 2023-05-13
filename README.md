# Manual

A program to create an RPG character and modify its inventory.

## When started, the program asks how to initialize the character.

### Available options

1. create a new character

    You are redirected to the character creation menu:

    - Entering the name of the character (required)

    - Selection via radio button:

        - race: human, elf, orc

        - Class: mage, archer, warrior 


Loading a character from a file 

    - Entering the name of the character from the available list and loading it with the inventory

    

Then go to the character menu


___


## Character menu

Managing the current character.

### Available options:

1. Save the current character and its inventory to a file.

2. Switch to the inventory menu.

3. return to the main menu.


On the right side, a preview of the current character's statistics is available.


___


## Inventory menu

Management of the current item and the ability to create a new item.

### Available options.

1. put on / take off the item.

2. deleting the current item.

3. Creating a new item and adding it to the inventory:

    - Entering the name of the item

    - Selecting the type of item using the radio button

Move to the next item in the inventory. 5.

5. return to the Character Menu.


___


# Modules


## inventory

**Item structure**.

Inventory management -> linked_list with functions:

- total weight

- adding items with total weight protection

- summing received statistics

- deletion of inventory / individual items

- generating items


___


## characters

**Class Character**.

Stats:

- Strength -> hp

- Intelligence -> mana

- Agility -> attack speed

- damage (weapons)

- range (weapons)


Characters, management and creation, features:

- statistics based on class and race

- initialization of equipment

- feeding statistics *total (base)*.

- writing + reading the character in the file (deleting the old character entry)

- only 1 item of a given type possible put on


___


## mainwindow

Graphical interface.


___


## utils

Additional features.


