#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
#include "../Sec3Group5Game/Enemy.h"
}

namespace EnemyTests
{
	TEST_CLASS(EnemyTests)
	{
	public:
		
		TEST_METHOD(EMY_RQ2_T1)
		{
			int health = 20, dmg = 10;
			char* enemyName = "John";
			//ENEMY* e = malloc(sizeof(ENEMY));
			ENEMY e = makeEnemy(health, dmg, enemyName);
			Assert::AreEqual(1, enemyTakeDmg(10, &e));
		}
		TEST_METHOD(EMY_RQ2_T2)
		{
			int health = 20, dmg = 20;
			char* enemyName = "John";
			//ENEMY* e = malloc(sizeof(ENEMY));
			ENEMY e = makeEnemy(health, dmg, enemyName);
			Assert::AreEqual(-1, enemyTakeDmg(dmg, &e));
		}
		TEST_METHOD(EMY_RQ2_T3)
		{
			int health = 20, dmg = 10;
			char* enemyName = "John";
			//ENEMY* e = malloc(sizeof(ENEMY));
			ENEMY e = makeEnemy(health, dmg, enemyName);
			enemyTakeDmg(10, &e);
			Assert::AreEqual(10, e.health);
		}
		TEST_METHOD(EMY_RQ1_T1)
		{
			ENEMYLIST* list = readEnemyFromFile("EnemyAreaOne.txt");
			if (list == NULL) {
				Assert::IsTrue(true);
			}
			else {
				Assert::IsTrue(false);
			}
			free(list);
		}
		TEST_METHOD(EMY_RQ1_T2)
		{
			ENEMYLIST* list = readEnemyFromFile("Bad file name");
			Assert::IsNull(list);
			free(list);
		}
		TEST_METHOD(EMY_RQ3_T1)
		{
			int health = 20, dmg = 10;
			char* enemyName = "John";
			//ENEMY* e = malloc(sizeof(ENEMY));
			ENEMY e = makeEnemy(health, dmg, enemyName);
			Assert::AreEqual(e.health, 20);
		}
		TEST_METHOD(EMY_RQ3_T2)
		{
			int health = 20, dmg = 10;
			char* enemyName = "John";
			//ENEMY* e = malloc(sizeof(ENEMY));
			ENEMY e = makeEnemy(health, dmg, enemyName);
			Assert::AreEqual(e.damage , 10);
		}
		TEST_METHOD(EMY_RQ3_T3)
		{
			int health = 20, dmg = 10;
			char* enemyName = "John";
			//ENEMY* e = malloc(sizeof(ENEMY));
			ENEMY e = makeEnemy(health, dmg, enemyName);
			Assert::AreEqual(e.enemyName, "John");
		}
		TEST_METHOD(EMY_RQ4_T1)
		{
			int maxEnemies = 5;
			ENEMYLIST* e = makeEnemyList(5);
			Assert::IsNotNull(e);
		}
	};
}
