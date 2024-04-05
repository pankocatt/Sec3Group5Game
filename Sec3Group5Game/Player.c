#include "Player.h"
#include "constants.h"

void initPlayer(PLAYER* player) {
	player->critChance = 10;
	player->damage = 5;
	player->defence = 5;
	player->health = 15;
	player->healthPots = 3;
}

void setName(char* name, PLAYER* player)
{
	strncpy(player->playerName, name, 100);
}

void equipWeapon(int dmg, PLAYER* player)
{
	player->damage += dmg;
}

void equipArmor(int dfc, PLAYER* player)
{
	player->defence += dfc;
}

void addHealthPot(int healthPot, PLAYER* player)
{
	player->healthPots += healthPot;
}

int useHealthPot(PLAYER* player)
{
	if (player->healthPots > 0) {
		player->health += HEALTHPOTHEALING;
		return 1;
	}
	return -1;
}

int playerTakeDmg(int dmg, PLAYER* player)
{
	int actualDmg = dmg - player->defence;
	if (actualDmg <= 0) {
		player->health = player->health;
	}
	else{
		player->health -= actualDmg;
	}
	
	if (player->health <= 0)
		return -1;
	else
		return 1;
}

void increaseCrit(int crit, PLAYER* player)
{
	player->critChance += crit;
}

int playerDealDmg(PLAYER* player)
{
	int critHit = rand() % (100 - 1 + 1) + 1;
	if (critHit <= player->critChance) {
		return (player->damage * 2);
	}
	else {
		return player->damage;
	}
}
