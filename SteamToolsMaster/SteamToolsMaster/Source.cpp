#include <iostream>
#include "functions.h"
#include "DataClass.h"
#include "TradePrice.h"
using namespace std;

int main(int argc, const char* argv[]) {
	ToolSettings Settings;

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

	Settings.AddAlias("trp", "TradePriceAlias");
	Settings.AddAlias("trade", "TradePriceAlias");
	Settings.AddAlias("tradeprice", "TradePriceAlias");

	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ]\n\n");
		printf("See \"stmtool [command] help\" for specific command help");
		//return 0;
	}
	std::cout << "end" << "\n";
	//Parse Settings.cfg


	const char* inputCommand = "tradeprice"; // = argv[1]
	const char* parsedCommand = Settings.CheckAgainstAlias("tradeprice");
	if (strcmp(parsedCommand, "none") == 0) {
		//non existant command/command
	}
	else if (strcmp(parsedCommand, "TradePriceAlias") == 0) {
		TradePrice();
	}
	else if (strcmp(parsedCommand, "KitMakerAlias") == 0) {

	}
	else if (strcmp(parsedCommand, "SetKeyAlias") == 0) {

	}
	if (argc <= 1) {
		return 0;
	}
	if (strcmp(argv[1], "tradeprice") == 0|| strcmp(argv[1], "trp") == 0) {
		if (argc <= 3 && strcmp(argv[2], "help")) {
			printf("// A script made to confirm the price of items when buying in bulk");

			//howto guide since they asked for help
		}
		else {
			
			//how many different items are we buying?
			//Price for this item?
			//How many of this item?
		}

	}
	std::cout << "end" << "\n";
	return 0;

}