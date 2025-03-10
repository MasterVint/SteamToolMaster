#include <iostream>
#include "functions.h"
#include "DataClass.h"
#include "TradePrice.h"
#include "Kitmaker.h"
#include "SetKey.h"
using namespace std;

int main(int argc, const char* argv[]) {
	ToolSettings Settings;

	#ifdef _DEBUG
		argc++;
		argv[1] = "key";
	#endif
	#ifdef _DEBUG
		printf("[Main Parse Start]\n");
	#endif
	Settings.ParseToolSettings();
	#ifdef _DEBUG
		printf("[Main Parse End]\n");
	#endif

	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ]\n\n");
		printf("See \"stmtool [command] help\" for specific command help");
		return 0;
	}


	#ifdef _DEBUG
		printf("[Main CheckAgainstAlias Start]\n");
	#endif
	const char* parsedCommand = Settings.CheckAgainstAlias(argv[1]);

	#ifdef _DEBUG
	printf("[Main CheckAgainstAlias End]\n");
	printf("argv[1]: %s\n", argv[1]);
	printf("parsedCommand: %s\n", parsedCommand);
	#endif
	if (strcmp(parsedCommand, "none") == 0) {
		printf("No command or alias called \"%s\" exists.", argv[1]);
		//inputCommand is not an existant command
	}
	else if (strcmp(parsedCommand, "TradePriceAlias") == 0) {
		#ifdef _DEBUG
				printf("[Main TradePrice() Start]\n");
		#endif
		TradePrice(Settings);
		#ifdef _DEBUG
				printf("[Main TradePrice() End]\n");
		#endif
	}
	else if (strcmp(parsedCommand, "KitMakerAlias") == 0) {
		#ifdef _DEBUG
				printf("[Main KitMaker() Start]\n");
		#endif
		KitMaker(Settings);
		#ifdef _DEBUG
				printf("[Main KitMaker() End]\n");
		#endif
	}
	else if (strcmp(parsedCommand, "SetKeyAlias") == 0) {
		SetKey(Settings);
	}

	//This is temporary, in reality this should only be called when we do a change.
	#ifdef _DEBUG
		printf("[Main Serializer Start]\n");
	#endif
	Settings.SerializeToolSettings();
	#ifdef _DEBUG
		printf("[Main Serializer End]\n");
	#endif
	return 0;

}