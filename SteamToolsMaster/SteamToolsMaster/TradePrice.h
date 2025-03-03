#ifndef TRADEPRICE_H
#define TRADEPRICE_H
#include <iostream>
#include "functions.h"
void TradePrice() {
	const size_t MAX_SIZE = 100;
	char input[MAX_SIZE];

	const size_t MAX_SIZE2 = 100;
	char input2[MAX_SIZE2];

	//size_t numbersize = 0;
	size_t AmountOfDiffItems = 0;
	size_t AmountOfItems = 0;

	size_t Keys = 0;
	size_t Refined = 0;
	size_t Reclaimed = 0;
	size_t Scrap = 0;
	size_t Weapons = 0;
	size_t total_value = 0;

	size_t TEST_KeyPrice[4] = { 60,2,2,2 };

	//Prompt 1: How many different items?
	printf("How many different items?\n");
	printf(">");
	AmountOfDiffItems = AskForPositiveNumber(input, MAX_SIZE);
	std::cout << AmountOfDiffItems << '\n';

	for (size_t i = 0; i < AmountOfDiffItems; i++) {
		//Prompt 2: How many of item [index]
		printf("How many of item ");
		printf(i + 1 + "?\n");
		printf(">");
		AmountOfItems = AskForPositiveNumber(input2, MAX_SIZE2);

		//Prompt 3: How much keys?
		Keys = AskForPositiveNumber(input, MAX_SIZE) * AmountOfItems;
		//Prompt 4: How much refined?
		Refined = AskForPositiveNumber(input, MAX_SIZE) * AmountOfItems;
		//Prompt 5: How much reclaimed?
		Reclaimed = AskForPositiveNumber(input, MAX_SIZE) * AmountOfItems;
		//Prompt 6: How much Scrap?
		Scrap = AskForPositiveNumber(input, MAX_SIZE) * AmountOfItems;
		//Prompt 7 How many weapons?
		Weapons = AskForPositiveNumber(input, MAX_SIZE) * AmountOfItems;

		total_value = Weapons + Scrap * 2 + Reclaimed * 6 + Refined * 18;
		size_t KeyWeaponValue = ReturnKeyWeaponValue(TEST_KeyPrice, Keys);
		MetalHelper(total_value, Keys, KeyWeaponValue);

		std::cout << Keys, Refined, Reclaimed, Scrap, Weapons;

		//Example Key Price
		//size_t KeyPrice[4] = { 60,2,2,2 };
		
	}
	
	//Prompt 1: How many different items?
	//foreach (answer of previous prompt) {
	//Prompt 2: How many of item [index]
	//Prompt 3: How much refined?
	//Prompt 4: How much reclaimed?
	//Prompt 5: How much Scrap?
	//Prompt 6 How many weapons?
	//}
}

//we might just have everything in the TradePrice() function
void TradePriceHelp() {

}
#endif
