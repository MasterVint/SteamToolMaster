#ifndef TRADEPRICE_H
#define TRADEPRICE_H
#include <iostream>
#include "functions.h"
#include "ToolSettings.h"

bool PromptItemCount(const char* messageItem, size_t& returnValue, char* input, const size_t& MAX_SIZE) {
	printf("How many %s ? ", messageItem);
	return AskForPositiveNumber(returnValue, input, MAX_SIZE);
}



// WIP Other way to ask for price
/*
Questions:
How many different items? 3
How many items of item [1]? 27
The cost of one such item? 1 60.77 // One way
// [Keys] [Metal]

How many items of item [2]? 7
The cost of one such item? 0 20 // second way
// [Keys] [Metal]

How many items of item [3]? 3
The cost of one such item? 6 60,2,1,3 // third way
// [Keys] [refined,reclaimed,scrap,weapons]







*/
//Calculate the cost of items in a trade
void TradePrice(ToolSettings &Settings, int &argc, const char* argv[]) {
	debugPrintf("[TradePrice Start]\n");

	//Get Current Key Price
	size_t CurrentKeyPriceSides[2];
	Metal_KeyPriceSides(Settings.GetMetal_KeyPrice(), CurrentKeyPriceSides);
	printf("Current Key price is %zu.%zu Refined\n", CurrentKeyPriceSides[0], CurrentKeyPriceSides[1]);
	const size_t MAX_SIZE = 100;
	char input[MAX_SIZE];

	size_t AmountOfDifferentItems = 0;
	size_t AmountOfItems = 0;
	size_t total_cost = 0;

	size_t Key_metal_value = ReturnKeyWeaponValue(Settings.GetMetal_KeyPrice());
	size_t Keys = 0, Refined = 0, Reclaimed = 0, Scrap = 0, Weapons = 0;
	bool responseStatus = true;

	//Prompt 1: How many different items?
	PromptItemCount("different items", AmountOfDifferentItems, input, MAX_SIZE);

	for (size_t i = 1; i <= AmountOfDifferentItems; i++) {
		std::cout << "\n//// Item " << i << " ////" << "\n";

		// How many of item [index]
		if (!PromptItemCount("items", AmountOfItems, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };

		//Ask for item [index] price
		if (!PromptItemCount("keys", Keys, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		if (!PromptItemCount("refined", Refined, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		if (!PromptItemCount("reclaimed", Reclaimed, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		if (!PromptItemCount("scrap", Scrap, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		if (!PromptItemCount("weapons", Weapons, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };

		//Add to total cost and zero values
		total_cost += (Keys * Key_metal_value + Scrap * 2 + Reclaimed * 6 + Refined * 18 + Weapons) * AmountOfItems;
		Keys = 0; Refined = 0; Reclaimed = 0; Scrap = 0; Weapons = 0; AmountOfItems = 0;
	}

	CleanValue(Key_metal_value, Keys, Refined, Reclaimed, Scrap, total_cost);
	Weapons = total_cost;
	std::cout << "\n//// Total Cost ////\n";
	if (Keys > 0) { std::cout << "Keys: " << Keys << '\n'; };
	if (Refined > 0) { std::cout << "Refined: " << Refined << '\n'; };
	if (Reclaimed > 0) { std::cout << "Reclaimed: " << Reclaimed << '\n'; };
	if (Scrap > 0) { std::cout << "Scrap: " << Scrap << '\n'; };
	if (Weapons > 0) { std::cout << "Weapons: " << Weapons << '\n'; };
	return;
}
#endif
