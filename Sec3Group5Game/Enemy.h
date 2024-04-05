#pragma once
#include "Player.h"
#include "constants.h"
typedef struct enemy {
	int health;
	int damage;
	//int critChance;
	char enemyName[NAMELENGTH];
}ENEMY;

typedef struct enemyList {
	ENEMY enemies[TOTALENEMIES];
}ENEMYLIST;

int enemyTakeDmg(int dmg, ENEMY *enemy);

ENEMY* readEnemyFromFile(char* fileName);

ENEMY makeEnemy(int health, int damage, char* enemyName);

ENEMYLIST* makeEnemyList(int maxEnemies);

int enemyDealDmg(ENEMY* enemy);




