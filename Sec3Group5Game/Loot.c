#include "Loot.h"
#include <time.h>

ITEM CreateItemFromSword(SWORD s) {


}


ITEM CreateItemFromArmour(ARMOUR a) {

}

ITEM CreateItemFromHealthPot(HEALTHPOT p) {


}

LOOTPOOL* readLootPoolFromFile(char* argv) {

}

ITEM returnItem(LOOTPOOL* lp) {

	srand(time(NULL));

	int size = (sizeof((*lp)) / sizeof((lp[0])));
	int randomElement = rand() % size + 1;
	return(*(lp->pool[randomElement]));
}

