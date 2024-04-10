#include "Enemy.h"
#include "constants.h"

int enemyTakeDmg(int dmg, ENEMY *enemy)
{
    enemy->health -= dmg;
    if (enemy->health <= 0)
        return -1;
    else
        return 1;
}

int enemyDealDmg(ENEMY* enemy, bool isCharged)
{
	if (isCharged == true) 
		return enemy->damage * 1.5;
	else
		return enemy->damage;
}

ENEMYLIST* makeEnemyList(int maxEnemies)
{
	ENEMYLIST* enemies = (ENEMYLIST*)malloc(maxEnemies * sizeof(ENEMY));
	if (enemies == NULL) {
		printf("Could not allocate space...\n");
		exit(1);
	}
	return enemies;
}

ENEMY makeEnemy(int health, int damage, char* enemyName)
{
	ENEMY enemy = { 0 };
	enemy.health = health;
	enemy.damage = damage;
	strncpy(enemy.enemyName, enemyName, NAMELENGTH);

	return enemy;
}

ENEMY* readEnemyFromFile(char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file...\n");
		exit(EXIT_FAILURE);
	}
	
	ENEMYLIST* enemies = makeEnemyList(TOTALENEMIES);
	//read from each file item
	for (int i = 0; i < TOTALENEMIES; i++) {
		//get information from file to populate enemies

		char enemyName[NAMELENGTH];
		fgets(enemyName, NAMELENGTH, fp);
		enemyName[strlen(enemyName) - 1] = '\0';
		
		int health = 0;
		//if scanf doesnt get 1 values, default them
		if (fscanf(fp, "%d", &health) != 1) {
			health = 0;
		}

		int damage = 0;
		//if scanf doesnt get 1 values, default them
		if (fscanf(fp, "%d", &damage) != 1) {
			damage = 0;
		}

		//get rid of the pesky newlines
		char buf[100];
		fgets(buf, 100, fp);
		fgets(buf, 100, fp);

		enemies->enemies[i] = makeEnemy(health, damage, enemyName);
	}

	fclose(fp);

	return enemies;
}
