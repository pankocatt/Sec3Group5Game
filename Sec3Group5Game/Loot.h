#pragma once
#include "constants.h"

//each attribute of the structs will add to player statistic
typedef struct sword {
	int dmg;
	int crit;
} SWORD;

typedef struct armour {
	int def;
} ARMOUR;

typedef struct healthPot {
	int health;
} HEALTHPOT;

typedef enum type { NONE = 0, SWORD_TYPE, ARMOUR_TYPE, HEALTHPOT_TYPE } TYPE;

typedef union loot {
	SWORD sword;
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

SWORD CreateSword(int dmg, int crit);
bool CopySword(SWORD* dest, SWORD src);

ARMOUR CreateArmour(int def);
bool CopyArmour(ARMOUR* dest, ARMOUR src);

HEALTHPOT CreateHealthPot(int health);
bool CopyHealthPot(HEALTHPOT* dest, HEALTHPOT src);

ITEM CreateItemFromSword(SWORD s);
ITEM CreateItemFromArmour(ARMOUR a);
ITEM CreateItemFromHealthPot(HEALTHPOT p);

LOOTPOOL* readLootPoolFromFile(char* argv); // Used for loot pool initialization, upon entering a new area

ITEM returnItem(LOOTPOOL* lp); //Passed to kyle, should randomly pull item from lootpool and give to him for pickup

