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

	LOOTPOOL* lootpool = initLootPool(TOTALENEMIES);
	//read from each file item
	for (int i = 0; i < TOTALENEMIES; i++) {
		//get information from file to populate seats
		char buf[100];
		char enemyName[100];
		fgets(buf, 100, fp);

		if (0 > buf[0] || buf[0] > 128)
			strncpy(enemyName, "NA\n", 100);
		else
			strncpy(enemyName, buf, 100);


		int health = 0;
		//if scanf doesnt get 1 values, default them
		if (fscanf(fp, "%d", &health) != 1) {
			health = 0;
		}

		int damage = 0;
		//if scanf doesnt get 1 values, default them
		if (fscanf(fp, "%d", &damage) != 1) {
			damage = 0;
		}

		//get rid of the pesky newline
		fgets(buf, 100, fp);

		enemies->enemies[i] = makeEnemy(health, damage, enemyName);
	}

	fclose(fp);

	return enemies;
}

ITEM returnItem(LOOTPOOL* lp) {

	srand(time(NULL));

	int size = (sizeof((*lp)) / sizeof((lp[0])));
	int randomElement = rand() % size + 1;
	// Returns a random element from the lootpool
	return(*(lp->pool[randomElement]));
}

