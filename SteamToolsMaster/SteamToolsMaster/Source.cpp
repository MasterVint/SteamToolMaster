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
		argv[1] = "trp";
	#endif
	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ] [ setkey | key ]\n\n");
		//printf("See \"stmtool [command] help\" for specific command help");
		return 0;
	}
	//All functions have to follow this ruleset
	//In case you want to add stored data you could either create a custom file reading and writing solution in your function
	//Or edit/add values stored by ToolSettings
	//void (*pFunction)(ToolSettings&, int&, const char* []);

	//Add functions and corresponding true names
	Settings.AddFunktion(Funktion("tradeprice", TradePrice));
	Settings.AddFunktion(Funktion("kitmaker", KitMaker));
	Settings.AddFunktion(Funktion("setkey", SetKey));

	//Settings.cfg is dependant on the Functions already being loaded
	Settings.ParseToolSettings();

	Settings.ExecuteAliasMatch(_strdup(argv[1]), Settings, argc, argv);

	Settings.SerializeToolSettings();
	return 0;

}