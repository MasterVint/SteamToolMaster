#ifndef SETKEY_H
#define SETKEY_H
#include <iostream>
#include "functions.h"
#include "DataClass.h"
// TODO
// Add support for inputing metal key price as decimal (e.g 60.33)
// Add support for inputting usd key price
void SetKey(ToolSettings& Settings, int& argc, const char* argv[]) {
	debugPrintf("[SetKey Start]\n");
	const size_t MAX_SIZE = 50;
	char input[MAX_SIZE];
	printf("set key: ");
	std::cin.clear();
	std::cin.get(input, MAX_SIZE);
	std::cin.ignore(1000, '\n');
	printf("\n");
	size_t last_comma_index = 0;
	size_t metal_type_index = 0;
	size_t KeyPrice[4] = { 0,0,0,0 };
	for (size_t i = 0; i < MAX_SIZE; i++) {
		char& indexchar = input[i];
		if (indexchar == NULL) {
			if (metal_type_index < 4) {
				KeyPrice[metal_type_index] = parsePositiveNumber(input, MAX_SIZE, last_comma_index, i);
			}
			break;
		}

		if (indexchar == ',') {
			if (metal_type_index == 4) {
				printf("Too many metals! The extra ones were ignored! Please follow the follow this format:\n");
				printf("60,1,1,1 (Refined, Reclaimed, Scrap, Weapon)\n");
				return;
			}
			KeyPrice[metal_type_index] = parsePositiveNumber(input, MAX_SIZE, last_comma_index, i);
			last_comma_index = i + 1;
			metal_type_index++;

		}
		if (indexchar == '.') {
			KeyPrice[0] = parsePositiveNumber(input, MAX_SIZE, 0, i);
			#ifdef _DEBUG
						printf("keypriceref: %zu\n", KeyPrice[0]);
			#endif
						size_t afterdecimal = parsePositiveNumber(input, MAX_SIZE, i + 1, i + 3);
			#ifdef _DEBUG
						printf("after decimal: %zu\n", afterdecimal);
			#endif
		}

	}
	if (KeyPrice[0] != 0) {
		Settings.SetMetal_KeyPrice(KeyPrice);
		Settings.SerializeToolSettings();
		printf("Key metal price set to %zu,%zu,%zu,%zu\n", KeyPrice[0], KeyPrice[1], KeyPrice[2], KeyPrice[3]);
	}
	else {

	};

};

#endif