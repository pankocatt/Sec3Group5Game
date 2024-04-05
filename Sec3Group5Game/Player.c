#include "Player.h"
#include "constants.h"

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
