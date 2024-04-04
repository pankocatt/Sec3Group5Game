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

static MAP* map;

// Map related items
// Create map
bool initMap();

// Enter game
void mainMenu();

// Gets user int input
int getIntInput(int, int);

// Used when you first enter a new area
int enterArea(PLAYER*, LOOTPOOL*, short);

// Choose left or right path, adds interactivity but changes nothing
short choosePath(PLAYER*, LOOTPOOL* lootpool);


// Fighting options
// Main fight menu
short fightMenu(PLAYER*, ENEMY*);

// Misc.
// Free Map Memory
void destroyMap();

