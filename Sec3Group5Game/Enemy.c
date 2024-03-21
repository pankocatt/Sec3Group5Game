#include "Enemy.h"

int enemyTakeDmg(int dmg, ENEMY *enemy)
{
    enemy->health -= dmg;
    if (enemy->health <= 0)
        return -1;
    else
        return 1;
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
	ENEMY enemy;
	enemy.health = health;
	enemy.damage = damage;
	enemy.enemyName = strncpy(enemy.enemyName, enemyName, 100);

	return enemy;
}

ENEMY* readEnemyFromFile(char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		createNewFile(fileName);
		fp = fopen(fileName, "r");
		if (fp == NULL) {
			fprintf(stderr, "Could not open file...\n");
			exit(EXIT_FAILURE);
		}
	}
	ENEMYLIST* enemies = makeEnemyList(5);
	//read from each file item
	for (int i = 0; i < 5; i++) {
		//get information from file to populate seats
		char buf[100];
		char enemyName[100];
		fgets(buf, 100, fp);

		if (0 > buf[0] || buf[0] > 128)
			strncpy(enemyName, "NA\n", 100);
		else
			strncpy(enemyName, buf, 100);

		
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

		//get rid of the pesky newline
		fgets(buf, 100, fp);

		enemies->enemies[i] = makeEnemy(health, damage, enemyName);
	}

	fclose(fp);

	return enemies;
}
