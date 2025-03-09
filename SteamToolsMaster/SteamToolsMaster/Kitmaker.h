#ifndef KITMAKER_H
#define KITMAKER_H
#include <iostream>
#include "functions.h"
void KitMaker(ToolSettings &Settings) {

	bool opened = openFile("./Kitmaker_input.txt");
	if (opened) {
		printf("Enter the fabricator inputs in the file, example provided.\n");

	}
	else {
		printf("./Kitmaker_input.txt could not be opened.\n");
		return;
	}

	std::ofstream kitmakerinput("./Kitmaker_input.txt");
	kitmakerinput << "//Just copy and paste the input items from your kit's steam inventory page, example given below:\n";
	printf("Press enter when you've pasted the input and saved Kitmaker_input.txt\n");
	char input[1];
	std::cin.get(input, 1);

	std::cout << input << std::endl;
	kitmakerinput.close();

	
}
#endif
