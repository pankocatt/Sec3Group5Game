#include "Loot.h"
#include <time.h>

SWORD CreateSword(int dmg, int crit) {
	SWORD s;
	s.dmg = dmg;
	s.crit = crit;
	return s;
}

bool CopySword(SWORD* dest, SWORD src) {
	if (dest == NULL || src.dmg == 0 ) {
		return false;
	}

	dest->dmg = src.dmg;
	dest->crit = src.crit;

	return true;
}

ARMOUR CreateArmour(int def) {
	ARMOUR a;
	a.def = def;
	return a;
}

bool CopyArmour(ARMOUR* dest, ARMOUR src) {
	if (dest == NULL || src.def == 0) {
		return false;
	}

	dest->def = src.def;

	return true;
}

HEALTHPOT CreateHealthPot(int health) {
	HEALTHPOT h;
	h.health = health;
	return h;
}

bool CopyHealthPot(HEALTHPOT* dest, HEALTHPOT src) {
	if (dest == NULL || src.health == 0) {
		return false;
	}

	dest->health = src.health;

	return true;
}

ITEM CreateItemFromSword(SWORD s) {
	ITEM i = { 0 };
	i.lootType = SWORD_TYPE;
	CopySword(&(i.loot.sword), s);
	return i;
}


ITEM CreateItemFromArmour(ARMOUR a) {
	ITEM i = { 0 };
	i.lootType = ARMOUR_TYPE;
	CopyArmour(&(i.loot.armour), a); 
	return i;
}

ITEM CreateItemFromHealthPot(HEALTHPOT p) {
	ITEM i = { 0 };
	i.lootType = HEALTHPOT_TYPE;
	CopyHealthPot(&(i.loot.healthpot), p); 
	return i;

}

LOOTPOOL* initLootPool(int maxLoot)
{
	LOOTPOOL* lootpool = (LOOTPOOL*)malloc(maxLoot * sizeof(ITEM));
	if (lootpool == NULL) {
		printf("Could not allocate space for lootpool...\n");
		exit(1);
	}
	return lootpool;
}

LOOTPOOL* readLootPoolFromFile(char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "Could not open LOOTPOOL file...\n");
		exit(EXIT_FAILURE);
	}

	LOOTPOOL* lootpool = initLootPool(MAXLOOT);
	ITEM item;
	//read from each file item
	for (int i = 0; i < MAXLOOT; i++) {
		//get information from file to populate seats
		char lootType[MAXNAME];

		// Gets loot type from file
		fgets(lootType, MAXNAME, fp);

		// Determines how to read file based on item type
		// Swords
		if (strncmp(lootType, "SWORD_TYPE\n", MAXNAME) == 0) {
			item.lootType = SWORD_TYPE;
			// Get damage and crit values
			int damage = 0, crit = 0;
			if (fscanf(fp, "%d%d", &damage, &crit) != 2) {
				item.loot.sword.crit = 10;
				item.loot.sword.dmg = 10;
			} else {
				item.loot.sword.crit = crit;
				item.loot.sword.dmg = damage;
			}
			// Get weapon name
			char itemName[100] = { 0 };
			fgets(itemName, MAXNAME, fp); // For newline
			fgets(itemName, MAXNAME, fp);
			itemName[strlen(itemName) - 1] = '\0';
			strncpy(item.loot.sword.name, itemName, MAXNAME);
		}
		// Armour
		else if (strncmp(lootType, "ARMOUR_TYPE\n", MAXNAME) == 0) {
			item.lootType = ARMOUR_TYPE;
			// Get defence value
			int defence = 0;
			if (fscanf(fp, "%d", &defence) != 1) {
				item.loot.armour.def = 5;
			}
			else {
				item.loot.armour.def = defence;
			}
			// Get armour name
			char itemName[100] = { 0 };
			fgets(itemName, MAXNAME, fp); // For newline
			fgets(itemName, MAXNAME, fp);
			itemName[strlen(itemName) - 1] = '\0';
			strncpy(item.loot.armour.name, itemName, MAXNAME);
		}
		// Health potions
		else if (strncmp(lootType, "HEALTHPOT_TYPE", MAXNAME)) {
			char itemName[100] = { 0 };
			fgets(itemName, MAXNAME, fp); // For newline
			item.lootType = HEALTHPOT_TYPE;
			item.loot.healthpot.health = HEALTHPOTHEALING;
		}
		// Default
		else {
			item.lootType = SWORD_TYPE;
			item.loot.sword.dmg = 10;
			item.loot.sword.crit = 10;
			char itemName[100];
			fgets(itemName, MAXNAME, fp); // For newline
			strncpy(item.loot.sword.name, "Unknown Type", MAXNAME);
		}
		//get rid of the pesky newlines
		char buf[100];
		fgets(buf, 100, fp);

		lootpool->pool[i] = item;
	}

	fclose(fp);

	return lootpool;
}

ITEM returnItem(LOOTPOOL* lp) {
	int randomElement = rand() % MAXLOOT;
	// Returns a random element from the lootpool
	return lp->pool[randomElement];
}

