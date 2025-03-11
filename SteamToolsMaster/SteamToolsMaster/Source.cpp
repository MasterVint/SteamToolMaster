#include <iostream>
#include "functions.h"
#include "DataClass.h"
#include "TradePrice.h"
#include "Kitmaker.h"
#include "SetKey.h"
using namespace std;

int main(int argc, const char* argv[]) {

#ifdef _DEBUG
	argc++;
	argv[1] = "trp";
#endif
	ToolSettings Settings;
	Settings.ParseToolSettings();

	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ] [ setkey | key ]\n\n");
		printf("See \"stmtool [command] help\" for specific command help");
		return 0;
	}
	const char* parsedCommand = Settings.CheckAgainstAlias(argv[1]);

	#ifdef _DEBUG
		printf("parsedCommand: %s\n", parsedCommand);
	#endif

	if (strcmp(parsedCommand, "none") == 0) {
		printf("No command or alias called \"%s\" exists.", argv[1]);
	}
	else if (strcmp(parsedCommand, "TradePriceAlias") == 0) {
		TradePrice(Settings);
	}
	else if (strcmp(parsedCommand, "KitMakerAlias") == 0) {
		KitMaker(Settings);
	}
	else if (strcmp(parsedCommand, "SetKeyAlias") == 0) {
		SetKey(Settings);
	}

	//This is temporary, in reality this should only be called when we do a change.
	Settings.SerializeToolSettings();
	return 0;

}