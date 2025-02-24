#include <iostream>
#include "functions.h"
#include "DataClass.h"
using namespace std;

int main(int argc, const char* argv[]) {
	//Test
	argv[1] = "test";
	argv[2] = "hello";
	argc = 3;
	//Check for memory leak with this
	for (size_t i = 0; i < 1000000000; i++) {
		ToolSettings Settings;
		Settings.AddAlias("sigma", "TradePriceAlias");
		//std::cout << "sigma" << std::endl;
	}
	std::cout << "end" << "\n";
	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ]\n\n");
		printf("See \"stmtool [command] help\" for specific help");
		return 0;
	}
	std::cout << "end" << "\n";
	//Parse Settings.cfg
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