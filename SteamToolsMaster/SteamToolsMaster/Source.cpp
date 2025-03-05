#include <iostream>
#include "functions.h"
#include "DataClass.h"
#include "TradePrice.h"
#include "Kitmaker.h"
using namespace std;

int main(int argc, const char* argv[]) {
	ToolSettings Settings;

	Settings.ParseToolSettings();
	Settings.SerializeToolSettings();
	//Todo: add parsing functionality to ToolSettings, use this in the meantime
	Settings.AddAlias("trp", "TradePriceAlias");
	Settings.AddAlias("trade", "TradePriceAlias");
	Settings.AddAlias("tradeprice", "TradePriceAlias");

	Settings.AddAlias("kitmaker", "KitMakerAlias");
	Settings.AddAlias("kitmkr", "KitMakerAlias");
	Settings.AddAlias("kit", "KitMakerAlias");

	//Test
	//argv[1] = "test";
	//argv[2] = "hello";
	//argc = 3;
	////Check for memory leak with this
	//for (size_t i = 0; i < 1000000000; i++) {
	//	Settings.AddAlias("trp", "TradePriceAlias");
	//	Settings.AddAlias("trade", "TradePriceAlias");
	//}
	//std::cout << "End of Test" << "\n";

	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ]\n\n");
		printf("See \"stmtool [command] help\" for specific command help");
		return 0;
	}



	const char* inputCommand = argv[1]; // = argv[1]
	const char* parsedCommand = Settings.CheckAgainstAlias(inputCommand);
	if (strcmp(parsedCommand, "none") == 0) {
		//non existant command/command
	}
	else if (strcmp(parsedCommand, "TradePriceAlias") == 0) {
		TradePrice();
	}
	else if (strcmp(parsedCommand, "KitMakerAlias") == 0) {
		KitMaker();
	}
	else if (strcmp(parsedCommand, "SetKeyAlias") == 0) {

	}
	return 0;

}