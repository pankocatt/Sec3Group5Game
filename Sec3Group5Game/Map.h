#pragma once
#include <stdbool.h>
#include "Player.h"
#include "Enemy.h"
#include "Loot.h"

typedef struct map {
	short  currentMap;
	short previousMap;

	short totalFights;
} MAP;

// Map related items
// Create map
MAP* initMap();

// Enter game
void mainMenu();

// Gets user int input
int getIntInput(int, int);

// Used when you first enter a new area
int enterArea(MAP*, PLAYER*, LOOTPOOL*, short);

// Choose left or right path, adds interactivity but changes nothing
short choosePath(MAP*, PLAYER*, LOOTPOOL* lootpool);


// Fighting options
// Main fight menu
short fightMenu(PLAYER*, ENEMY*);

// Misc.
// Free Map Memory
void destroyMap(MAP*);

