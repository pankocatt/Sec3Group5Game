#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
#define _CRT_SECURE_NO_WARNINGS
#include "../Sec3Group5Game/constants.h"
#include "../Sec3Group5Game/Player.h"
#include "../Sec3Group5Game/Enemy.h"
#include "../Sec3Group5Game/Loot.h"
#include "../Sec3Group5Game/Map.h"
}

namespace MapTests {
	TEST_CLASS(MapTests) {
	public:
		
		// initMap() function test to ensure it returns a malloc'd map
		TEST_METHOD(InitMap) {
			MAP* map = initMap();
			int expectedMap = 1, expectedFights = 5;
			Assert::AreEqual(expectedMap, map->currentMap);
			Assert::AreEqual(expectedFights, map->totalFights);
			Assert::IsNotNull(map);
			free(map);
		}
		// Area 1 untestable, has fgets(stdin) which infinite loops until the heatdeath of the universe
		// All tests were performed manually

		// Enter area 2
		TEST_METHOD(EnterArea2) {
			MAP* map = initMap();
			map->currentMap = 2;
			PLAYER* player = initPlayer();
			LOOTPOOL* loot = (LOOTPOOL*)malloc(sizeof(LOOTPOOL));
			if (loot == NULL)
				return;
			int mapNum = enterArea(map, player, loot);
			Assert::AreEqual(GOODCODE, mapNum);
			free(map);
			free(player);
			free(loot);
		}

		// Enter area 3
		TEST_METHOD(EnterArea3) {
			MAP* map = initMap();
			map->currentMap = 3;
			PLAYER* player = initPlayer();
			LOOTPOOL* loot = (LOOTPOOL*)malloc(sizeof(LOOTPOOL));
			if (loot == NULL)
				return;
			int mapNum = enterArea(map, player, loot);
			Assert::AreEqual(GOODCODE, mapNum);
			free(map);
			free(player);
			free(loot);
		}

		// Win
		TEST_METHOD(EnterAreaWin) {
			MAP* map = initMap();
			map->currentMap = 4;
			PLAYER* player = initPlayer();
			LOOTPOOL* loot = (LOOTPOOL*)malloc(sizeof(LOOTPOOL));
			if (loot == NULL)
				return;
			int mapNum = enterArea(map, player, loot);
			Assert::AreEqual(WIN, mapNum);
			free(map);
			free(player);
			free(loot);
		}

		// Enter invalid area
		TEST_METHOD(EnterAreaUnknown) {
			MAP* map = initMap();
			map->currentMap = 5;
			PLAYER* player = initPlayer();
			LOOTPOOL* loot = (LOOTPOOL*)malloc(sizeof(LOOTPOOL));
			if (loot == NULL)
				return;
			int mapNum = enterArea(map, player, loot);
			Assert::AreEqual(ERRORCODE, mapNum);
			free(map);
			free(player);
			free(loot);
		}

		// The choosePath() function is untestable due to scanf, all tests performed manually

		// The fightMenu() function is untestable due to scanf, all tests performed manually
	};
}
