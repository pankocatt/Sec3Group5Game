#pragma once
#include "constants.h"

#define MAXNAME 20
#define MAXLOOT 10
//each attribute of the structs will add to player statistic
typedef struct sword {
	int dmg;
	int crit;
	char name[MAXNAME];
} SWORD;

typedef struct armour {
	int def;
	char name[MAXNAME];
} ARMOUR;

typedef struct healthPot {
	int health;
	char name[MAXNAME];
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
	char name[MAXNAME];
} ITEM;

typedef struct lootPool {
	ITEM* pool[MAXLOOT];
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

LOOTPOOL* initLootPool(int maxLoot);
LOOTPOOL* readLootPoolFromFile(char* argv); // Used for loot pool initialization, upon entering a new area

ITEM returnItem(LOOTPOOL* lp); //Passed to kyle, should randomly pull item from lootpool and give to him for pickup

