#ifndef KITMAKER_H
#define KITMAKER_H
#include <iostream>
#include "functions.h"
#include "DataClass.h"
void KitMaker(ToolSettings &Settings, int &argc, const char* argv[]) {
	debugPrintf("[Kitmaker Start]\n");
	bool opened = openFile("./Kitmaker_input.txt");
	if (opened) {
		printf("Enter the fabricator inputs in the file, example provided.\n");
		printf("Press enter when you've pasted the input and saved Kitmaker_input.txt\n");
	}
	else {
		printf("./Kitmaker_input.txt could not be opened.\n");
		return;
	}
	//Wait for user to press any button
	std::cin.get();

	//Read File
	std::ifstream kitmakerinput("./Kitmaker_input.txt");
	char line[200];
	size_t total_weapons_price = 0;
	while (kitmakerinput.getline(line, sizeof(line))) {
		std::string lineString = line;
		size_t LocationOfx = lineString.find(" x ");

		std::string ItemName = lineString.substr(0, LocationOfx);
		int ItemAmount = atoi((lineString.substr(LocationOfx + 3, sizeof(lineString) - LocationOfx)).c_str());


		if (ItemName == "Unique Killstreak Item") {
			total_weapons_price += Settings.GetUnique_Killstreak_Item() * ItemAmount;
		}
		else if (ItemName == "Unique Specialized Killstreak Item") {
			total_weapons_price += Settings.GetUnique_Specialized_Killstreak_Item() * ItemAmount;
		}
		else if (ItemName == "Battle-Worn Robot KB-808") {
			total_weapons_price += Settings.GetBattle_Worn_Robot_KB_808() * ItemAmount;
		}
		else if (ItemName == "Battle-Worn Robot Taunt Processor") {
			total_weapons_price += Settings.GetBattle_Worn_Robot_Taunt_Processor() * ItemAmount;
		}
		else if (ItemName == "Battle-Worn Robot Money Furnace") {
			total_weapons_price += Settings.GetBattle_Worn_Robot_Money_Furnace() * ItemAmount;
		}
		else if (ItemName == "Reinforced Robot Emotion Detector") {
			total_weapons_price += Settings.GetReinforced_Robot_Emotion_detector() * ItemAmount;
		}
		else if (ItemName == "Reinforced Robot Humor Suppression Pump") {
			total_weapons_price += Settings.GetReinforced_Robot_Humor_Supression_Pump() * ItemAmount;
		}
		else if (ItemName == "Reinforced Robot Bomb Stabilizer") {
			total_weapons_price += Settings.GetReinforced_Robot_Bomb_Stabilizer() * ItemAmount;
		}
		else if (ItemName == "Pristine Robot Brainstorm Bulb") {
			total_weapons_price += Settings.GetPristine_Robot_Brainstorm_Bulb() * ItemAmount;
		}
		#ifdef _DEBUG
				std::cout << "\"" << ItemName << "\"\n";
		#endif
	}
	size_t MetalKeyPrice = ReturnKeyWeaponValue(Settings.GetMetal_KeyPrice());
	float key_floatvalue = round((float(total_weapons_price) / float(MetalKeyPrice)) * 100)/100;
	//float refined_floatvalue = round((float(total_weapons_price)/float(18)) * 100) / 100;
	size_t keys = 0, refined = 0, reclaimed = 0, scrap = 0, weapons = 0;;
	MetalHelper(total_weapons_price, keys, MetalKeyPrice);
	CleanValue(refined, reclaimed, scrap, total_weapons_price);
	printf("//// Total Crafting Cost ////\n");
	if (keys > 0) { printf("keys: %zu\n", keys); };
	if (refined > 0) { printf("refined: %zu\n", refined); };
	if (reclaimed > 0) { printf("reclaimed: %zu\n", reclaimed); };
	if (scrap > 0) { printf("scrap: %zu\n", scrap); };
	if (total_weapons_price > 0) { printf("weapons: %zu\n", total_weapons_price); };
	printf("%g keys\n", key_floatvalue);
	//printf("Or %g refined\n", refined_floatvalue);
	kitmakerinput.close();

	//Write File
	std::ofstream kitmakeroutput("./Kitmaker_input.txt");
	kitmakeroutput << "//Replace this files contents with the input items from your kit's steam inventory page, example given below:\n";
	kitmakeroutput << "Unique Specialized Killstreak Item x 2\n";
	kitmakeroutput << "Battle-Worn Robot KB-808 x 13\n";
	kitmakeroutput << "Battle-Worn Robot Taunt Processor x 3\n";
	kitmakeroutput << "Reinforced Robot Emotion Detector x 3\n";
	kitmakeroutput.close();

	
}
#endif
