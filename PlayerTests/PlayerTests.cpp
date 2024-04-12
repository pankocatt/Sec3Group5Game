#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
#include "../Sec3Group5Game/Player.h"
}

namespace PlayerTests
{
	TEST_CLASS(PlayerTests)
	{
	public:
		
		TEST_METHOD(PLR_RQ1_T1)
		{
			PLAYER* p = initPlayer();
			SWORD s = CreateSword(10, 5, "A pencil");
			equipWeapon(s, p);
			Assert::AreEqual(p->damage, 10);
		}
		TEST_METHOD(PLR_RQ1_T2)
		{
			PLAYER* p = initPlayer();
			ARMOUR a = CreateArmour(100, "paper armor");
			equipArmor(a, p);
			Assert::AreEqual(p->defence, 102);
		}
		TEST_METHOD(PLR_RQ1_T3)
		{
			PLAYER* p = initPlayer();
			addHealthPot(p);
			Assert::AreEqual(p->healthPots, 1);
		}
		TEST_METHOD(PLR_RQ2_T1)
		{
			//ENEMY* e = malloc(sizeof(ENEMY));
			PLAYER* p = initPlayer();
			playerTakeDmg(3, p);
			Assert::AreEqual(14, p->health);
		}
		TEST_METHOD(PLR_RQ2_T2)
		{
			PLAYER* p = initPlayer();
			Assert::AreEqual(playerTakeDmg(17, p), -1);
		}
		TEST_METHOD(PLR_RQ2_T3)
		{
			PLAYER* p = initPlayer();
			Assert::AreEqual(playerTakeDmg(14, p), 1);
		}
	};
}
