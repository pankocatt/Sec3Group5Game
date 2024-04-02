#pragma once
typedef struct player {
	int health;
	int damage;
	int defence;
	int critChance;
	int healthPots;
	char* playerName; 
}PLAYER;

void setName(char* name, PLAYER* player);

void equipWeapon(int dmg, PLAYER* player);

void equipArmor(int dfc, PLAYER* player);

void addHealthPot(int healthPot, PLAYER* player);

int playerTakeDmg(int dmg, PLAYER* player);

void increaseCrit(int crit, PLAYER* player);

int playerDealDmg(int dmg, PLAYER* player);
