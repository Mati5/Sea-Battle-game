#include "RandNum.h"

int RandNum(int max)
{
	static std::minstd_rand eng{ std::random_device{}() };

	return eng() % max;
}
