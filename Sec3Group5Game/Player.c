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
	player->critChance = 0;
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

void equipWeapon(SWORD sword, PLAYER* player)
{
	player->damage += sword.dmg;
	player->critChance += sword.crit;
}

void equipArmor(ARMOUR armour, PLAYER* player)
{
	player->defence += armour.def;
}

void addHealthPot(PLAYER* player)
{
	player->healthPots++;
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

int playerDealDmg(PLAYER* player)
{
	// Saves players initial stats to modify
	int critChance = player->critChance;
	int damageShift = player->damage;

	// Loops while player has more crit chance remaining than 0
	while (critChance > 0) {
		// If crit chance is higher than 100, add crit damage
		if (critChance >= 100) {
			damageShift << 1;
			critChance -= 100;
			continue;
		}

		// If critchance is lower than 100, see if attack adds more crit then return damage
		int critHit = (rand() % 100) + 1;
		if (critHit <= critChance) {
			damageShift << 1;
			return damageShift;
		}
	}
	return player->damage;
}
