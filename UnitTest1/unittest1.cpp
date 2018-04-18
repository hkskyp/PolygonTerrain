#include "stdafx.h"
#include "CppUnitTest.h"
#include <PolygonMethod.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(determinePolygonCW)
		{
			// TODO: Your test code here
            std::vector<POINT> cw;
            POINT pt[] = { {-1, -1}, {0, 1}, {1, -1} };
            cw.emplace_back(pt[0]);
            cw.emplace_back(pt[1]);
            cw.emplace_back(pt[2]);
            Assert::IsTrue(IsWindingDirection(cw) == 1);
		}

		TEST_METHOD(determinePolygonCCW)
		{
			// TODO: Your test code here
            std::vector<POINT> ccw;
            POINT pt[] = { {-1, -1}, {1, -1}, {0, 1} };
            ccw.emplace_back(pt[0]);
            ccw.emplace_back(pt[1]);
            ccw.emplace_back(pt[2]);
            Assert::IsTrue(IsWindingDirection(ccw) == -1);
		}

        TEST_METHOD(crossProduct)
        {
            POINT p1 = {  0, 1 };
            POINT p2 = {  1, 0 };
            POINT p3 = { -1, 0 };

            Assert::IsTrue(CrossProduct(p1, p2) < 0.0); // right
            Assert::IsTrue(CrossProduct(p1, p3) > 0.0); // left
        }

	};
}