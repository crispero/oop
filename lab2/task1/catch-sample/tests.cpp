#include "pch.h"
#include "vector/ProcessVector.h"
#include "vector/PrintVector.h"

TEST_CASE("ProcessVector() with standard input")
{
	numbers vf = { 24.4f, 41.2f, 94.4f };
	numbers vres = { 595.36f, 1005.28f, 2303.36f };
	ProcessVector(vf);
	CHECK(vf == vres);
}

TEST_CASE("ProcessVector() with negative input")
{
	numbers vf = { -8.0f, -90.2f, 34.4f };
	numbers vres = { 64.0f, 721.6f, -275.2f };
	ProcessVector(vf);
	CHECK(vf == vres);
}

TEST_CASE("PrintVector() with standard input")
{
	numbers vf = { -8.0f, -90.2f, 34.4f };
	numbers vres = { -8.0f, -90.2f, 34.4f };
	PrintVector(vf);
	CHECK(vf == vres);
}