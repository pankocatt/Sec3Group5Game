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
			SWORD s = CreateSword(dmg, crit);
			Assert::AreEqual(s.dmg, dmg);
		}
		TEST_METHOD(ITM_CRT_002)
		{
			// Regular armour creation test
			int def = 15;
			ARMOUR a = CreateArmour(def);
			Assert::AreEqual(a.def, def);
		}
		TEST_METHOD(ITM_CRT_003)
		{
			// Regular healthpot creation test
			int hp = 15;
			HEALTHPOT h = CreateHealthPot(hp);
			Assert::AreEqual(h.health, hp);
		}
		TEST_METHOD(ITM_CRT_004)
		{
			// Named sword creation test
			int dmg = 15;
			int crit = 10;
			char name[15] = "Dagger";
			SWORD s = CreateSword(dmg, crit);
			Assert::AreEqual(s.dmg, dmg);
		}
	};
}
