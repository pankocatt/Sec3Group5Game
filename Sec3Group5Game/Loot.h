#pragma once

//each attribute of the structs will add to player statistic
typedef struct sword {
	int dmg;
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

ITEM CreateItemFromSword(SWORD s);
ITEM CreateItemFromArmour(ARMOUR a);
ITEM CreateItemFromHealthPot(HEALTHPOT p);

LOOTPOOL* setUpLootPool(char* argv); //{  //set up loot pool for internal handling
//	lootpool lp
//	read file
//	choose random items
//}

ITEM returnItem(LOOTPOOL* lp); //Passed to kyle, should randomly pull item from lootpool and give to him for pickup

