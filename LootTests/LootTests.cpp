#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
#include "../Sec3Group5Game/Loot.h"
}

namespace LootTests
{
	TEST_CLASS(LootTests)
	{
	public:
		
		TEST_METHOD(ITM_CRT_001)
		{
			// Regular sword creation test
			int dmg = 15;
			int crit = 10;
			SWORD s = CreateSword(dmg, crit, "");
			Assert::AreEqual(s.dmg, dmg);
		}
		TEST_METHOD(ITM_CRT_002)
		{
			// Regular armour creation test
			int def = 15;
			ARMOUR a = CreateArmour(def, "");
			Assert::AreEqual(a.def, def);
		}
		TEST_METHOD(ITM_CRT_003)
		{
			// Regular healthpot creation test
			int hp = 15;
			HEALTHPOT h = CreateHealthPot(hp, "");
			Assert::AreEqual(h.health, hp);
		}
		TEST_METHOD(ITM_CRT_004)
		{
			// Named sword creation test
			int dmg = 15;
			int crit = 10;
			char name[15] = "Dagger";
			SWORD s = CreateSword(dmg, crit, name);
			Assert::AreEqual(s.name, name);
		}
		TEST_METHOD(ITM_CRT_005)
		{
			// Named armour creation test
			int def = 15;
			char* name = "Hat";
			ARMOUR a = CreateArmour(def, name);
			Assert::AreEqual(a.name, name);
		}
		TEST_METHOD(ITM_CRT_006)
		{
			// Named healthpot creation test
			int hp = 15;
			char* name = "Potion";
			HEALTHPOT h = CreateHealthPot(hp, name);
			Assert::AreEqual(h.name, name);
		}
		TEST_METHOD(ITM_CRT_007)
		{
			// Creating an Item from Sword test
			SWORD s = CreateSword(15, 10, "Dagger");
			ITEM i = CreateItemFromSword(s);
			Assert::AreEqual(i.loot.sword.dmg, s.dmg);
		}
		TEST_METHOD(ITM_CRT_008)
		{
			// Creating an Item from Armour test
			ARMOUR a = CreateArmour(15, "Hat");
			ITEM i = CreateItemFromArmour(a);
			Assert::AreEqual(i.loot.armour.def, a.def);
		}
		TEST_METHOD(ITM_CRT_009)
		{
			// Creating an Item from Healthpot test
			HEALTHPOT h = CreateHealthPot(15, "Potion");
			ITEM i = CreateItemFromHealthPot(h);
			Assert::AreEqual(i.loot.healthpot.health, h.health);
		}
		TEST_METHOD(ITM_CPY_001)
		{
			// Copying a sword to another sword
			SWORD* s1 = (SWORD*)malloc(sizeof(SWORD));
			SWORD s2 = CreateSword(15, 10, "Dagger");
			bool result = CopySword(s1, s2);
			Assert::AreEqual(result, true);
			Assert::AreEqual(s1->dmg, s2.dmg);
			free(s1);
		}
		TEST_METHOD(ITM_CPY_002)
		{
			// Copying an armour to another armour
			ARMOUR* a1 = (ARMOUR*)malloc(sizeof(ARMOUR));
			ARMOUR a2 = CreateArmour(15, "Hat");
			bool result = CopyArmour(a1, a2);
			Assert::AreEqual(result, true);
			Assert::AreEqual(a1->def, a2.def);
			free(a1);
		}
		TEST_METHOD(ITM_CPY_003)
		{
			// Copying a healthpot to another healthpot
			HEALTHPOT* a1 = (HEALTHPOT*)malloc(sizeof(HEALTHPOT));
			HEALTHPOT a2 = CreateHealthPot(15, "Potion");
			bool result = CopyHealthPot(a1, a2);
			Assert::AreEqual(result, true);
			Assert::AreEqual(a1->health, a2.health);
			free(a1);
		}
	};
}
