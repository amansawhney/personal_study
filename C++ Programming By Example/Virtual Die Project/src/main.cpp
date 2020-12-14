#include <iostream>
#include <random>

int main()
{
	std::random_device random_device;
	std::default_random_engine random_eng(random_device());
	std::uniform_int_distribution<int> dice_gen(1, 6);

	int random_int = dice_gen(random_eng);
	std::cout << random_int << std::endl;
}