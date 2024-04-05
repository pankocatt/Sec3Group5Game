#include "Player.h"
#include "constants.h"

PLAYER* initPlayer() {
	PLAYER* player = malloc(sizeof(PLAYER));
	if (player == NULL)
		return NULL;

	player->playerName = malloc(sizeof(char) * NAMELENGTH);
	if (player->playerName == NULL) {
		free(player);
		return NULL;
	}
	player->critChance = 10;
	player->damage = 0;
	player->defence = 2;
	player->health = 15;
	player->healthPots = 3;

	return player;
}

void setName(char* name, PLAYER* player)
{
	strncpy(player->playerName, name, NAMELENGTH);
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
		player->healthPots--;
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
	int critHit = (rand() % 100) + 1;
	if (critHit <= player->critChance) {
		return (player->damage << 1);
	}
	else {
		return player->damage;
	}
}
