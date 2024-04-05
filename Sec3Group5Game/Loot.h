#pragma once
#include "constants.h"

//each attribute of the structs will add to player statistic
typedef struct weapon {
	int dmg;
	int crit;
} WEAPON;

typedef struct armour {
	int def;
} ARMOUR;

typedef struct healthPot {
	int health;
} HEALTHPOT;

typedef enum type { NONE = 0, WEAPON_TYPE, ARMOUR_TYPE, HEALTHPOT_TYPE } TYPE;

typedef union loot {
	WEAPON weapon;
	ARMOUR armour;
	HEALTHPOT healthpot;
} LOOT;

typedef struct item {
	TYPE lootType;
	LOOT loot;
} ITEM;

typedef struct lootPool {
	ITEM* pool[10];
} LOOTPOOL;

ITEM CreateItemFromWeapon(WEAPON w);
ITEM CreateItemFromArmour(ARMOUR a);
ITEM CreateItemFromHealthPot(HEALTHPOT p);

LOOTPOOL* readLootPoolFromFile(char* argv); // Used for loot pool initialization, upon entering a new area

ITEM returnItem(LOOTPOOL* lp); //Passed to kyle, should randomly pull item from lootpool and give to him for pickup

