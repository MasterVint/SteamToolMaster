#ifndef SETKEY_H
#define SETKEY_H
#include <iostream>
#include "functions.h"
#include "ToolSettings.h"
// TODO
// Add support for inputing metal key price as decimal (e.g 60.33)
// Add support for inputting usd key price
void SetKey(ToolSettings& Settings, int& argc, const char* argv[]) {
	
	debugPrintf("[SetKey Start]\n");

	//Get Current Key Price
	size_t CurrentKeyPriceSides[2];
	Metal_KeyPriceSides(Settings.GetMetal_KeyPrice(), CurrentKeyPriceSides);
	printf("Current Key price is %zu.%zu Refined\n", CurrentKeyPriceSides[0], CurrentKeyPriceSides[1]);

	const size_t MAX_SIZE = 50;
	char input[MAX_SIZE];
	printf("set key: ");
	std::cin.clear();
	std::cin.get(input, MAX_SIZE);
	std::cin.ignore(1000, '\n');
	printf("\n");

	//Here "index" refers to two different things, consider giving them more clarifying names
	size_t last_comma_index = 0;
	size_t metal_type_index = 0;

	size_t KeyPrice[4] = { 0,0,0,0 };
	bool OnlyNumbersInString = true;
	for (size_t i = 0; i < MAX_SIZE; i++) {
		if (input[i] == NULL) {
			break;
		}
		//Check if char is a number or not
		if ((input[i] >= 48 && input[i] <= 57) || input[i] == ',' || input[i] == '.') {

		}
		else {

			debugPrintf("[SetKey] Letter Detected\n");
			OnlyNumbersInString = false;
			break;
		}
	}
	for (size_t i = 0; i < MAX_SIZE; i++) {
		if (!OnlyNumbersInString) {
			break;
		}
		char& indexchar = input[i];

		if (indexchar == NULL) {
			if (metal_type_index < 4) {
				KeyPrice[metal_type_index] = parsePositiveNumber(input, MAX_SIZE, last_comma_index, i);
			}
			break;
		}



		if (indexchar == ',') {
			if (metal_type_index == 4) {
				printf("Too many metals! The extra ones were ignored! Please follow this format in the future:\n");
				printf("60,1,1,1 (Refined, Reclaimed, Scrap, Weapon)\n");
				printf("There is no need to include all the metal, 60,1,1 (Refined, Reclaimed, Scrap) would be a valid input.\n");
				return;
			}
			KeyPrice[metal_type_index] = parsePositiveNumber(input, MAX_SIZE, last_comma_index, i);
			last_comma_index = i + 1;
			metal_type_index++;
			continue;
		}
		if (indexchar == '.') {
			KeyPrice[0] = parsePositiveNumber(input, MAX_SIZE, 0, i);
			
			#ifdef _DEBUG
						printf("[SetKey] keypriceref: %zu\n", KeyPrice[0]);
			#endif
						size_t afterdecimal = parsePositiveNumber(input, MAX_SIZE, i + 1, i + 3);
			#ifdef _DEBUG
						printf("[SetKey] after decimal: %zu\n", afterdecimal);
			#endif
						MetalHelper(afterdecimal, KeyPrice[1], 33);
						MetalHelper(afterdecimal, KeyPrice[2], 11);
						MetalHelper(afterdecimal, KeyPrice[3], 5);
			break;
		}



	}
	if (KeyPrice[0] != 0 && OnlyNumbersInString) {
		Settings.SetMetal_KeyPrice(KeyPrice);
		Metal_KeyPriceSides(KeyPrice, CurrentKeyPriceSides);
		Settings.SerializeToolSettings();
		//printf("Key metal price was set to %zu,%zu,%zu,%zu\n", KeyPrice[0], KeyPrice[1], KeyPrice[2], KeyPrice[3]);
		printf("New key price is %zu.%zu Refined\n", CurrentKeyPriceSides[0], CurrentKeyPriceSides[1]);
	}
	else if (input[0] == NULL) {
		printf("The metal key price was not changed.\n");
	}
	else if (!OnlyNumbersInString) {
		printf("The value of keys cannot be measured with letters. The metal key price was not changed.\n");
	}
	else if (input[0] == '0' || KeyPrice[0] == 0) {
		printf("The metal key price can not be set to 0. The metal key price was not changed.\n");
	}
	else {
		//We do not know this error
		printf("Unknown error, please make a report. The metal key price was not changed.\n");
	};

};

#endif