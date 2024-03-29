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
	player->health -= (dmg - player->defence);
	if (player->health <= 0)
		return -1;
	else
		return 1;
}
