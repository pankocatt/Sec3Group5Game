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
			SWORD s = CreateSword(dmg, crit, NULL);
			Assert::AreEqual(s.dmg, dmg);
		}
		TEST_METHOD(ITM_CRT_002)
		{
			// Regular armour creation test
			int def = 15;
			ARMOUR a = CreateArmour(def, NULL);
			Assert::AreEqual(a.def, def);
		}
		TEST_METHOD(ITM_CRT_003)
		{
			// Regular healthpot creation test
			int hp = 15;
			HEALTHPOT h = CreateHealthPot(hp, NULL);
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
			char* name = "Dagger";
			ARMOUR a = CreateArmour(def, name);
			Assert::AreEqual(a.name, name);
		}
		TEST_METHOD(ITM_CRT_006)
		{
			// Named healthpot creation test
			int hp = 15;
			char* name = "Dagger";
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
	};
}
