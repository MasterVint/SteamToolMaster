#include <iostream>
#include "functions.h"
#include "DataClass.h"
#include "TradePrice.h"
#include "Kitmaker.h"
#include "SetKey.h"
#include "Funktion.h"
using namespace std;

int main(int argc, const char* argv[]) {

	#ifdef _DEBUG
		argc++;
		argv[1] = "ktm";
	#endif
	if (argc <= 1) {
		printf("usage: stmtool [ tradeprice | trp ] [ kitmaker | ktm ] [ setkey | key ]\n\n");
		//printf("See \"stmtool [command] help\" for specific command help");
		return 0;
	}
	void (*pFunction)(ToolSettings&, int&, const char* []);
	ToolSettings Settings;

	//Add functions
	pFunction = TradePrice;
	Settings.AddFunktion(Funktion("tradeprice", pFunction));
	pFunction = KitMaker;
	Settings.AddFunktion(Funktion("kitmaker", pFunction));
	pFunction = SetKey;
	Settings.AddFunktion(Funktion("setkey", pFunction));

	//Settings.cfg is dependant on the Functions already being loaded
	Settings.ParseToolSettings();

	Settings.ExecuteAliasMatch(_strdup(argv[1]), Settings, argc, argv);
	return 0;

}