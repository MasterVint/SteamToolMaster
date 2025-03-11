#ifndef TRADEPRICE_H
#define TRADEPRICE_H
#include <iostream>
#include "functions.h"
#include "DataClass.h"

//std::cout << "How many items " << "? ";
//responseStatus = AskForPositiveNumber(AmountOfItems, input, MAX_SIZE);
//if (!responseStatus) { std::cout << "Invalid Input"; return; };

bool PromptItemCount(const char* messageItem, size_t& returnValue, char* input, const size_t& MAX_SIZE) {
	printf("How many %s ? ", messageItem);
	return AskForPositiveNumber(returnValue, input, MAX_SIZE);
}
void TradePrice(ToolSettings& Settings) {
	debugPrintf("[TradePrice Start]\n");
	const size_t MAX_SIZE = 100;
	char input[MAX_SIZE];

	//size_t numbersize = 0;
	size_t AmountOfDiffItems = 0;
	size_t AmountOfItems = 0;

	size_t Keys = 0;
	size_t Refined = 0;
	size_t Reclaimed = 0;
	size_t Scrap = 0;
	size_t Weapons = 0;

	size_t total_cost = 0;

	bool responseStatus = true;


	//Prompt 1: How many different items?
	printf("\nHow many different items? ");
	responseStatus = AskForPositiveNumber(AmountOfDiffItems, input, MAX_SIZE);
	if (!responseStatus) { 
		std::cout << "Invalid Input";
	return; 
	};

	for (size_t i = 1; i <= AmountOfDiffItems; i++) {
		//Initialize values
		Keys = 0;
		Refined = 0;
		Reclaimed = 0;
		Scrap = 0;
		Weapons = 0;
		AmountOfItems = 0;

		std::cout << "\n//// Item " << i << " ////" << "\n";
		//Test Prompt

		//Prompt 2: How many of item [index]
		if (!PromptItemCount("items", AmountOfItems, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };

		//Ask for item [index] price
		if (!PromptItemCount("keys", Keys, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		if (!PromptItemCount("refined", Refined, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		if (!PromptItemCount("reclaimed", Reclaimed, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		if (!PromptItemCount("scrap", Scrap, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		if (!PromptItemCount("weapons", Weapons, input, MAX_SIZE)) { std::cout << "Invalid Input"; return; };
		Keys *= AmountOfItems;

		//This is really confusing
		Weapons += (Scrap * 2 + Reclaimed * 6 + Refined * 18) * AmountOfItems;
		total_cost += Weapons + Keys * ReturnKeyWeaponValue(Settings.GetMetal_KeyPrice());
		std::cout << Weapons << " : " << Keys << " : " << ReturnKeyWeaponValue(Settings.GetMetal_KeyPrice()) << std::endl;
		MetalHelper(Weapons, Keys, ReturnKeyWeaponValue(Settings.GetMetal_KeyPrice()));
		Scrap = 0;
		Reclaimed = 0;
		Refined = 0;
		CleanValue(Refined, Reclaimed, Scrap, Weapons);
		std::cout << "\n//// Item " << i << " Cost ////\n";
		if (Keys > 0) { std::cout << "Keys: " << Keys << '\n'; };
		if (Refined > 0) { std::cout << "Refined: " << Refined << '\n'; };
		if (Reclaimed > 0) { std::cout << "Reclaimed: " << Reclaimed << '\n'; };
		if (Scrap > 0) { std::cout << "Scrap: " << Scrap << '\n'; };
		if (Weapons > 0) { std::cout << "Weapons: " << Weapons << '\n'; };
		
	}
	Keys = 0;
	Refined = 0;
	Reclaimed = 0;
	Scrap = 0;
	Weapons = 0;
	MetalHelper(total_cost, Keys, ReturnKeyWeaponValue(Settings.GetMetal_KeyPrice()));
	CleanValue(Refined, Reclaimed, Scrap, total_cost);
	Weapons = total_cost;
	std::cout << "\n//// Total Cost ////\n";
	if (Keys > 0) { std::cout << "Keys: " << Keys << '\n'; };
	if (Refined > 0) { std::cout << "Refined: " << Refined << '\n'; };
	if (Reclaimed > 0) { std::cout << "Reclaimed: " << Reclaimed << '\n'; };
	if (Scrap > 0) { std::cout << "Scrap: " << Scrap << '\n'; };
	if (Weapons > 0) { std::cout << "Weapons: " << Weapons << '\n'; };


	//ru,tr,rd,tl
}

//we might just have everything in the TradePrice() function
void TradePriceHelp() {

}
#endif
