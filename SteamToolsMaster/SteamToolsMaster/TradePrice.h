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

	size_t total_cost = 0;

	bool responseStatus = true;

	size_t TEST_KeyPrice[4] = { 60,2,0,0 };

	//Prompt 1: How many different items?
	printf("\nHow many different items? ");
	responseStatus = AskForPositiveNumber(AmountOfDiffItems, input, MAX_SIZE);
	if (!responseStatus) { 
		std::cout << "Invalid Input";
	return; 
	};

	for (size_t i = 0; i < AmountOfDiffItems; i++) {
		//Initialize values
		Keys = 0;
		Refined = 0;
		Reclaimed = 0;
		Scrap = 0;
		Weapons = 0;
		AmountOfItems = 0;

		std::cout << "\n//// Item " << (i + 1) << " ////" << "\n";
		//Prompt 2: How many of item [index]
		std::cout << "How many items " << "? ";
		responseStatus = AskForPositiveNumber(AmountOfItems, input2, MAX_SIZE2);
		if (!responseStatus) { std::cout << "Invalid Input"; return; };

		//Prompt 3: How much keys?
		std::cout << "How many keys " << "? ";
		responseStatus = AskForPositiveNumber(Keys, input, MAX_SIZE);
		if (!responseStatus) { std::cout << "Invalid Input"; return; };
		Keys *= AmountOfItems;

		//Prompt 4: How much refined?
		std::cout << "How many refined " << "? ";
		responseStatus = AskForPositiveNumber(Refined, input, MAX_SIZE);
		if (!responseStatus) { std::cout << "Invalid Input"; return; };

		//Prompt 5: How much reclaimed?
		std::cout << "How many reclaimed " << "? ";
		responseStatus = AskForPositiveNumber(Reclaimed, input, MAX_SIZE);
		if (!responseStatus) { std::cout << "Invalid Input"; return; };

		//Prompt 6: How much Scrap?
		std::cout << "How many scrap " << "? ";
		responseStatus = AskForPositiveNumber(Scrap, input, MAX_SIZE);
		if (!responseStatus) { std::cout << "Invalid Input"; return; };

		//Prompt 7 How many weapons?
		std::cout << "How many weapons " << "? ";
		responseStatus = AskForPositiveNumber(Weapons, input, MAX_SIZE);
		if (!responseStatus) { std::cout << "Invalid Input"; return; };

		Weapons += (Scrap * 2 + Reclaimed * 6 + Refined * 18) * AmountOfItems;
		total_cost += Weapons + Keys * ReturnKeyWeaponValue(TEST_KeyPrice);
		std::cout << Weapons << " : " << Keys << " : " << ReturnKeyWeaponValue(TEST_KeyPrice) << std::endl;
		MetalHelper(Weapons, Keys, ReturnKeyWeaponValue(TEST_KeyPrice));
		Scrap = 0;
		Reclaimed = 0;
		Refined = 0;
		CleanValue(Refined, Reclaimed, Scrap, Weapons);
		std::cout << "\n//// Item " << (i + 1) << " Cost ////\n";
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
	MetalHelper(total_cost, Keys, ReturnKeyWeaponValue(TEST_KeyPrice));
	CleanValue(Refined, Reclaimed, Scrap, total_cost);
	Weapons = total_cost;
	std::cout << "\n//// Total Cost ////\n";
	if (Keys > 0) { std::cout << "Keys: " << Keys << '\n'; };
	if (Refined > 0) { std::cout << "Refined: " << Refined << '\n'; };
	if (Reclaimed > 0) { std::cout << "Reclaimed: " << Reclaimed << '\n'; };
	if (Scrap > 0) { std::cout << "Scrap: " << Scrap << '\n'; };
	if (Weapons > 0) { std::cout << "Weapons: " << Weapons << '\n'; };


	//ru,tr,rd,tl
	
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
