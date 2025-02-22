#include <iostream>
#include "functions.h"
using namespace std;

int main(int argc, const char* argv[]) {
	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ]\n\n");
		printf("See \"stmtool [command] help\" for specific help");
		return 0;
	}
	if (CompareCharArray(argv[1], "tradeprice") || CompareCharArray(argv[1], "trp")) {
		if (argc <= 3 && CompareCharArray(argv[2], "help")) {
			printf("// A script made to confirm the price of items when buying in bulk");

			//howto guide since they asked for help
		}
		else {
			
			//how many different items are we buying?
			//Price for this item?
			//How many of this item?
		}

	}
	return 0;

}