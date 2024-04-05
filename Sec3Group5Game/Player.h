#pragma once
#include "constants.h"
#include "Loot.h"
typedef struct player {
	int health;
	int damage;
	int defence;
	int critChance;
	int healthPots;
	char* playerName; 
}PLAYER;

PLAYER* initPlayer();

void setName(char* name, PLAYER* player);

void equipWeapon(SWORD sword, PLAYER* player);

void equipArmor(ARMOUR armour, PLAYER* player);

void addHealthPot(PLAYER* player);

int useHealthPot(PLAYER* player);

int playerTakeDmg(int dmg, PLAYER* player);

int playerDealDmg(PLAYER* player);
