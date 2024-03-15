#pragma once
#include <stdlib.h>
#include "Player.h"
typedef struct enemy {
	int health;
	int damage;
	//int critChance;
	char* enemyName;
}ENEMY;

typedef struct enemyList {
	ENEMY enemies[5];
}ENEMYLIST;

void enemyTakeDmg(int dmg);

ENEMY* readEnemyFromFile(char* fileName);

ENEMY* s(char* fileName);






