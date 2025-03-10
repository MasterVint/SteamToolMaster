#ifndef SETKEY_H
#define SETKEY_H
#include <iostream>
#include "functions.h"
#include "DataClass.h"
void SetKey(ToolSettings &Settings) {
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
		char &indexchar = input[i];
		if (indexchar == NULL) {
			printf("here\n");
			if (metal_type_index < 4) {
				KeyPrice[metal_type_index] = parsePositiveNumber(input, MAX_SIZE, last_comma_index, i);
				printf("Metal %zu: %zu\n", (size_t)metal_type_index, (size_t)KeyPrice[metal_type_index]);
			}
			break;
		}
		
		if (indexchar == ',') {
			if (metal_type_index == 4) {
				printf("Too many metals! The extra ones were ignored! Please follow the follow either of these formats:\n");
				printf("60,1,1,1 (Refined, Reclaimed, Scrap, Weapon)\n");
				printf("60.33 (decimal of Refined, this would be 60 refined and 1 reclaimed)\n");
				return;
			}
			KeyPrice[metal_type_index] = parsePositiveNumber(input, MAX_SIZE, last_comma_index, i);
			printf("Metal %zu: %zu\n", (size_t)metal_type_index, (size_t)KeyPrice[metal_type_index]);
			last_comma_index = i + 1;
			metal_type_index++;
			
		}
		if (indexchar == '.') {
			KeyPrice[0] = parsePositiveNumber(input, MAX_SIZE, 0, i);
			#ifdef _DEBUG
				printf("keypriceref: %zu\n", KeyPrice[0]);
			#endif
			size_t afterdecimal = parsePositiveNumber(input, MAX_SIZE, i+1, i + 3);
			#ifdef _DEBUG
				printf("after decimal: %zu\n", afterdecimal);
			#endif
		}

	}
	Settings.SetMetal_KeyPrice(KeyPrice);
	Settings.SerializeToolSettings();
	printf("Key metal price set to %zu,%zu,%zu,%zu\n", KeyPrice[0], KeyPrice[1], KeyPrice[2], KeyPrice[3]);

	//different inputs
	// 60.33 (aka 60 refined, 1 reclaimed)
	// 60,1,1,1 (aka 60 refined, 1 reclaimed, 1 scrap)
	// 60,1,1 (we can omitt ofc)
	
	// What date relating to keys should we store?
	// char* MetalKeyPrice[4] = {60,2,2,0}; // Refined, Reclaimed, Scrap, Weapons
	// float MoneyKeyPrice = 1.78;
}

#endif