#include <iostream>
#include "functions.h"
#include "ToolSettings.h"
#include "TradePrice.h"
#include "Kitmaker.h"
#include "SetKey.h"
#include "Funktion.h"
using namespace std;

//This program is single-threaded
int main(int argc, const char* argv[]) {
	ToolSettings Settings;
	#ifdef _DEBUG
		argc++;
		argv[1] = "editalias";
	#endif
	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice ] [ kitmaker ] [ setkey ] [ editalias ]\n");
		//printf("See \"stmtool [command] help\" for specific command help");
		return 0;
	}
	//All functions have to follow this ruleset
	//In case you want to add stored data you could either create a custom file reading and writing solution in your function
	//Or edit/add values stored by ToolSettings
	//void (*pFunction)(ToolSettings&, int&, const char* []);

	//Add functions and corresponding true names
	Settings.AddFunktion(Funktion("TradePrice", TradePrice));
	Settings.AddFunktion(Funktion("KitMaker", KitMaker));
	Settings.AddFunktion(Funktion("SetKey", SetKey));

	Settings.AddFunktion(Funktion("EditAlias", EditAlias));

	//Settings.cfg is dependant on the Functions already being loaded
	Settings.ParseToolSettings();

	Settings.ExecuteAliasMatch(_strdup(argv[1]), Settings, argc, argv);

	Settings.SerializeToolSettings();
	return 0;

}