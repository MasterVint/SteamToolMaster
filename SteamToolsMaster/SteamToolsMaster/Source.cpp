#include <iostream>
#include "functions.h"
#include "DataClass.h"
#include "TradePrice.h"
#include "Kitmaker.h"
#include "SetKey.h"
#include "Funktion.h"
using namespace std;

void funkt(ToolSettings& Settings, int argc, const char* argv[]) {

}
int main(int argc, const char* argv[]) {

#ifdef _DEBUG
	argc++;
	argv[1] = "ktm";
#endif
	void (*funkt)(ToolSettings&, int&, const char* []);
	ToolSettings Settings;

	//Add functions
	const char* str = "tradeprice";
	funkt = TradePrice;
	Settings.AddFunktion(Funktion(str, funkt));
	funkt = KitMaker;
	Settings.AddFunktion(Funktion("kitmaker", funkt));
	funkt = SetKey;
	Settings.AddFunktion(Funktion("setkey", funkt));

	Settings.ParseToolSettings();

	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ] [ setkey | key ]\n\n");
		//printf("See \"stmtool [command] help\" for specific command help");
		return 0;
	}

	const char* parsedCommand = Settings.GetAliasMatch(argv[1]);

	#ifdef _DEBUG
		printf("parsedCommand: %s\n", parsedCommand);
	#endif
	Settings.ExecuteAliasMatch(_strdup(argv[1]), Settings, argc, argv);

	//This is temporary, in reality this should only be called when we do a change.
	//Settings.SerializeToolSettings();
	return 0;

}