#pragma once
#include "Loot.h"
#include "Player.h"
#include "Enemy.h"

typedef struct map {
	int currentMap;
	LOOTPOOL lootPool;
} MAP;