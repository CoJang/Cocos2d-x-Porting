#include "WELLRAND.h"
#include <cstdlib>
#include <ctime>

#define ARY_SIZE(d) sizeof d / sizeof d[0]

static unsigned long long RECT4FState[16];
static unsigned long RECT4FIndex = 0;

void InitRand() {
    srand((unsigned long)time(nullptr));
    for (unsigned long i = 0; i < ARY_SIZE(RECT4FState); ++i)RECT4FState[i] = rand();
}

unsigned long long MakeRand() {
	unsigned long long a, b, c, d;

	a = RECT4FState[RECT4FIndex];
	c = RECT4FState[(RECT4FIndex + 13) & 15];
	b = a ^ c ^ (a << 16) ^ (c << 15);
	c = RECT4FState[(RECT4FIndex + 9) & 15];
	c ^= (c >> 11);
	a = RECT4FState[RECT4FIndex] = b ^ c;
	d = a ^ ((a << 5) & 0xDA442D20UL);
	RECT4FIndex = (RECT4FIndex + 15) & 15;
	a = RECT4FState[RECT4FIndex];
	RECT4FState[RECT4FIndex] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);

	return RECT4FState[RECT4FIndex];
}

unsigned long long MakeRandWithRange(unsigned long long MaxRange)
{
	return MakeRand() % (MaxRange + 1u);
}