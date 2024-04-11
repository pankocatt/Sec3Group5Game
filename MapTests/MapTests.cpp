#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
#include "../Sec3Group5Game/Map.h"
}

namespace MapTests {
	TEST_CLASS(MapTests) {
	public:
		
		TEST_METHOD(InitMap) {
			MAP* map = initMap();
			Assert::IsNotNull(map);
			free(map);
		}
	};
}
