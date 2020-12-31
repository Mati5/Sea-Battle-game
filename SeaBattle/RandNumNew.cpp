#include <random>

int randNumNew(int max) {
	static std::minstd_rand eng{ std::random_device{}() };
	return eng() % max;
}