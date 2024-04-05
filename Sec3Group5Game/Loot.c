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

LOOTPOOL* readLootPoolFromFile(char* argv) {
	//TODO
}

ITEM returnItem(LOOTPOOL* lp) {

	srand(time(NULL));

	int size = (sizeof((*lp)) / sizeof((lp[0])));
	int randomElement = rand() % size + 1;
	// Returns a random element from the lootpool
	return(*(lp->pool[randomElement]));
}

