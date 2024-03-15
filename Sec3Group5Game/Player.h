#pragma once
typedef struct player {
	int health;
	int damage;
	int defence;
	//int critChance;
	int healthPots;
	char* playerName; 
}Player;

void setName(char* name);

void equipWeapon(int dmg);

void equipArmor(int dfc);

void addHealthPot(int healthPot);

void playerTakeDmg(int dmg);
