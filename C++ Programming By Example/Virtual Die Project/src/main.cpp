#include <iostream>
#include <random>
#include <cstdio>

class Dice
{
public:
	int get_roll();

public:
	std::random_device rd;
	std::uniform_int_distribution<int> dice_gen = std::uniform_int_distribution<int>(1, 6);
};

int Dice::get_roll()
{
	return this->dice_gen(this->rd);
}

int main()
{
	Dice d;
	std::printf("Your roll is %i", d.get_roll());
}