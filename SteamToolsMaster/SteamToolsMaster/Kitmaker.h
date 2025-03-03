#ifndef KITMAKER_H
#define KITMAKER_H
#include <iostream>
void KitMaker() {
	const size_t MAX_SIZE = 100;
	char input[MAX_SIZE];
	std::cin.get(input, MAX_SIZE);

	std::cout << input << std::endl;
}
#endif
