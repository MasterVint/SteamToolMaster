#ifndef ToolSettings_H
#define ToolSettings_H
#include <iostream>
#include <fstream>
#include "functions.h"
#include <vector>
#include "Funktion.h"
//a class for the data such as settings, keyprice and command aliases
// 
class ToolSettings {
private:

    //key
    size_t Metal_KeyPrice[4] = { 60,0,0,0 }; // Refined, Reclaimed, Scrap, Weapons
    size_t USD_KeyPrice = 170; // Cents, divide by 100 for actual number

    // Dynamic arrays to store the aliases
    std::vector<Funktion> Functions;

    //Killstreak Kit Parts, Cost Denoted in weapons
    size_t Unique_Killstreak_Item = 270;
    size_t Unique_Specialized_Killstreak_Item = 900;
    size_t Battle_Worn_Robot_KB_808 = 20;
    size_t Battle_Worn_Robot_Taunt_Processor = 20;
    size_t Battle_Worn_Robot_Money_Furnace = 20;
    size_t Reinforced_Robot_Emotion_detector = 2;
    size_t Reinforced_Robot_Humor_Supression_Pump = 2;
    size_t Reinforced_Robot_Bomb_Stabilizer = 2;
    size_t Pristine_Robot_Brainstorm_Bulb = 50;

    //Visual flags
    bool DisplayMoneyPrice = false; //not used
    





public:


    std::vector<Funktion>& GetFunctions() { return Functions; }

    ToolSettings() {

    }

    ~ToolSettings() {
    }
    void AddFunktion(Funktion func) {
        Functions.push_back(func);
    }

    void SetMetal_KeyPrice(size_t* NewKeyPrice) {
        for (size_t i = 0; i < 4; i++) {
            Metal_KeyPrice[i] = NewKeyPrice[i];
        };
    };
    size_t* GetMetal_KeyPrice() { return Metal_KeyPrice; };
    //Returns "none" if no match was found
    const char* GetAliasMatch(const char* value) {
        for (Funktion& Func : Functions) {
            for (const char* Alias : Func.GetAliases()) {
                if (strcmp(Alias, value) == 0) {
                    return Func.GetAliasName();
                }
            }
        }
        return "none";
    }
    bool ExecuteAliasMatch(char* value, ToolSettings &Settings, int &argc, const char* argv[]) {
        ToLowerCase(value);
        for (Funktion& Func : Functions) {
            if (strcmp(ToLowerCase(Func.GetAliasName()), value) == 0) {
                Func.ExecuteFunction(Settings, argc, argv);
                return true;
            }
            for (const char* Alias : Func.GetAliases()) {
                debugPrintf("\"%s\" and \"%s\"\n", ToLowerCase(Alias), value);
                if (strcmp(ToLowerCase(Alias), value) == 0) {
                    Func.ExecuteFunction(Settings, argc, argv);
                    return true;
                }
            }
        }
        printf("No command or alias called \"%s\" exists.", value);
        return false;
    }
    bool RemoveAlias(char* needle) {
        bool success = false;
        debugPrintf("[Remove Alias] needle: \"%s\"\n", needle);
        for (Funktion& Func : Functions) {
            success = Func.RemoveAlias(needle);
        }
        return success;
    }
    bool RemoveAlias(const char* needle) {
        bool success = false;
        debugPrintf("[Remove Alias] needle: \"%s\"\n", needle);
        for (Funktion& Func : Functions) {
            success = Func.RemoveAlias(needle);
        }
        return success;
    }
    bool EditAlias(const char* oldAlias, const char* newAlias) {
        bool success = false;
        for (Funktion& Func : Functions) {
            if (Func.EditAlias(oldAlias, newAlias)) {
                success = true;
            }
        }
        return success;
    }
    bool AddAlias(char* new_value, const char* category) {
        char* lowerCaseCategory = ToLowerCase(category);
        size_t InputCount = 0;
        for (Funktion& Func : Functions) {
            debugPrintf("[AddAlias] truname: %s | %s\n", new_value, category);
            if (strcmp(ToLowerCase(Func.GetAliasName()), lowerCaseCategory) == 0) {
                debugPrintf("[AddAlias] Adding \"%s\"\n", new_value);
                Func.AddAlias(new_value);
                return true;
            }
        }
        return false;
    }

    size_t GetUnique_Killstreak_Item() { return Unique_Killstreak_Item; };
    size_t GetUnique_Specialized_Killstreak_Item() { return Unique_Specialized_Killstreak_Item; };
    size_t GetBattle_Worn_Robot_KB_808() { return Battle_Worn_Robot_KB_808; };
    size_t GetBattle_Worn_Robot_Taunt_Processor() { return Battle_Worn_Robot_Taunt_Processor; };
    size_t GetBattle_Worn_Robot_Money_Furnace() { return Battle_Worn_Robot_Money_Furnace; };
    size_t GetReinforced_Robot_Emotion_detector() { return Reinforced_Robot_Emotion_detector; };
    size_t GetReinforced_Robot_Humor_Supression_Pump() { return Reinforced_Robot_Humor_Supression_Pump; };
    size_t GetReinforced_Robot_Bomb_Stabilizer() { return Reinforced_Robot_Bomb_Stabilizer; };
    size_t GetPristine_Robot_Brainstorm_Bulb() { return Pristine_Robot_Brainstorm_Bulb; };
    void PrintToolSettings() {
        //Print all the aliases
        for (Funktion& Func : Functions) {
            printf("Aliases \"%s\": ", Func.GetAliasName());
            for (const char* Alias : Func.GetAliases()) {
                printf("%s, ", Alias);
            }
            printf("\n");

        }
    }

    bool SerializeToolSettings() {
        #ifdef _DEBUG
        printf("[SerializeToolSettings] Start\n");
        #endif
        std::ofstream SettingsCFG("./Settings.cfg");

        SettingsCFG << "#This .cfg file is used to store data such as key price, aliases and relevant settings." << '\n';
        SettingsCFG << "#Be wary of manually editing these values, spaces or ' ' are not trimmed." << '\n';
        SettingsCFG << "#alias,alias_category,aliasname1,aliasname2, ..." << '\n';
        SettingsCFG << "#keyprice,metal,refined,reclaimed,scrap,weapon" << '\n';
        SettingsCFG << "#keyprice,usd,price_in_cents ($1.70 == 170)" << '\n';

        //Write down aliases
        for (Funktion& Func : Functions) {
            SettingsCFG << "\n" << "alias," << Func.GetAliasName();
            for (const char* Alias : Func.GetAliases()) {
                SettingsCFG << "," << Alias;
            }
        }

        SettingsCFG << "\n\nkeyprice,metal";
        for (const size_t metal_price : Metal_KeyPrice) {
            SettingsCFG << ',' << metal_price;
        }
        SettingsCFG << "\nkeyprice,usd";
        SettingsCFG << ',' << USD_KeyPrice;
        #ifdef _DEBUG
                printf("[SerializeToolSettings] End\n");
        #endif
        return true;
    }
    bool ParseToolSettings() {
    #ifdef _DEBUG
            printf("[ParseToolSettings] Start\n");
    #endif
        char Line[100]; //hardcoded limits, nice

        const size_t match_size = 100;
        char match[match_size];

        size_t needleIndex = 0;

        std::ifstream SettingsCFG("./Settings.cfg");

        //Note: The below code, repeats it self multiple times, it's plausible to create functions for greater readability
        while (SettingsCFG.getline(Line, sizeof(Line))) {
            needleIndex = 0;
            if (Line[needleIndex] == '#' || Line[needleIndex] == '\n' || Line[needleIndex] == '\0') {
                //Is commented or empty or newline -> skip
            }
            else {
                copyUntilComma(match, Line, needleIndex);
                if (strcmp("alias", match) == 0) {
                    ClearArray(match, match_size);

                    copyUntilComma(match, Line, needleIndex);
                    const char* TrueName = _strdup(match);
                    //printf("TrueName: \"%s\"\n", TrueName);
                    while (Line[needleIndex - 1] != '\0' && Line[needleIndex - 1] != '\n') {
                        ClearArray(match, match_size);
                        copyUntilComma(match, Line, needleIndex);
                        #ifdef _DEBUG
                           printf("[ParseToolSettings] Adding %s: %s\n", TrueName, match);
                        #endif
                           if (!AddAlias(match, TrueName)) {
                               printf("Adding Alias Failed!\n");
                               debugPrintf("[ParseToolSettings] Adding Alias Failed, TrueName: %s, match: %s\n", TrueName, match);
                           }
                    }

                }
                else if (strcmp("keyprice", match) == 0) {
                    ClearArray(match, match_size);

                    copyUntilComma(match, Line, needleIndex);
                    if (strcmp("metal", match) == 0) {
                        size_t metalIndex = 0;
                        while(Line[needleIndex - 1] != '\0' && Line[needleIndex - 1] != '\n' && metalIndex < 4) {
                            ClearArray(match, match_size);
                            copyUntilComma(match, Line, needleIndex);
                            Metal_KeyPrice[metalIndex] = parsePositiveNumber(match, sizeof(match) / sizeof(match[0]));
                            CleanValue(Metal_KeyPrice[0], Metal_KeyPrice[1], Metal_KeyPrice[2], Metal_KeyPrice[3]);
                            //printf("metals: %zu\n",Metal_KeyPrice[0]);
                            metalIndex++;
                        }
                    }
                    else if (strcmp("usd", match) == 0) {
                        ClearArray(match, match_size);
                        copyUntilComma(match, Line, needleIndex);
                        USD_KeyPrice = parsePositiveNumber(match, sizeof(match) / sizeof(match[0]));
                        #ifdef _DEBUG
                        printf("[ParseToolSettings] USD_KeyPrice: %zu\n", USD_KeyPrice);
                        #endif
                    }
                }
                //std::cout << "Processed Line: " << Line << '\n';
            }
           // std::cout << "Line: " << Line << '\n';
        }
        //// Close the file
        SettingsCFG.close();
        #ifdef _DEBUG
                printf("[ParseToolSettings] End\n");
        #endif
        //std::cout << "[ParseToolSettings] End, TradePriceCount = " << TradePriceCount << '\n';
        return true;
    }
};

//Just AddAlias as a pure function is pretty bad
//Let's say we instead list all true names and their aliases like such:
/*
1. TradePrice
    1.1 trp
    1.2 tradeprice
2. kitmaker
    2.1 ktm
    3.2 kitmaker
3. setkey
    3.1 key
    3.2 setkey

Add, Remove, Edit Alias:
> Add 3                 // "Add yy.xxx" gets truncuated to "Add yy" since you can only select true names
> Enter alias to add: kit
> alias "kit" was added for "kitmaker"

> Remove 3              //Invalid can't remove, add or remove true names
> Remove 3.1            //Removed the alias 3.1 "key"

> Edit 3.1              //Change alias to the new user input




*/
void EditAlias(ToolSettings& Settings, int& argc, const char* argv[]) {
    debugPrintf("[AddAlias Start]\n");

    printf("Functions and their respective aliases: \n");

    size_t TrueNameIndex = 0;
    size_t AliasIndex = 0;
    for (Funktion& func : Settings.GetFunctions()) {
        TrueNameIndex++;
        printf("%zu. %s\n",TrueNameIndex,func.GetAliasName());
        AliasIndex = 0;
        for (const char* alias : func.GetAliases()) {
            AliasIndex++;
            printf("    %zu.%zu %s\n", TrueNameIndex, AliasIndex, alias);
        }
    }
    printf("\n// Either Add, Remove or Edit an alias //\n");
    printf("// Example: add 1\n");
    printf("// Example: remove 1.1\n");
    printf("// Example: edit 1.1\n");
    const size_t MAX_SIZE = 100;
    char input[MAX_SIZE];
    std::cin.clear();
    std::cin.get(input, MAX_SIZE);
    std::cin.ignore(1000, '\n');

    char MainCommand[50];
    char Argument[50];
    char SecondArgument[50] = {};
    size_t inputIndex = 0;
    bool success = copyUntilSpace(MainCommand, input, inputIndex, 50);
    if (!success) { return; };
    success = copyUntilSpace(Argument, input, inputIndex, 50);
    if (!success) { printf("Arguments missing\n"); return; };
    if (input[inputIndex-1] != NULL) {
        success = copyUntilSpace(SecondArgument, input, inputIndex, 50);
    }
    //Turn the commands into lowercase so the user can do "Add" "aDd" etc etc
    ToLowerCase(MainCommand);
    ToLowerCase(Argument);
    ToLowerCase(SecondArgument);

    const size_t needleCount = 3;
    char needles[needleCount] = { '.', '\n', '\0' };

    if (strcmp("add", MainCommand) == 0) {
        TrueNameIndex = 0;
        size_t i = 0;


        success = copyUntilChar(Argument, Argument, 50, needles, needleCount, i);
        //if (!success) { printf("Invalid alias index, please use \"add x.y\" when adding an alias.\n"); return; };
        debugPrintf("success: %d\n", success);
        debugPrintf("Argument: \"%s\"\n", Argument);
        for (Funktion& func : Settings.GetFunctions()) {
            TrueNameIndex++;


            size_t ParsedNumber = 0;
            bool success = parsePositiveNumber(Argument, 50, ParsedNumber);
            if (!success) { printf("An function can not be selected using letters, please use \"add x\" when adding an alias.\n"); return; };

            if (TrueNameIndex == ParsedNumber) {

                if (SecondArgument[0] != NULL) {
                    // We have a second argument
                    Settings.AddAlias(SecondArgument, func.GetAliasName());
                    printf("Added \"%s\" as an alias for \"%s\"\n", SecondArgument, func.GetAliasName());
                    return;
                }
                else {
                    // We don't have the second argument, so we need to ask for the alias to add
                    printf("Function \"%s\" selected.\nPlease enter the alias you would like to add or leave empty to cancel:\n>", func.GetAliasName());
                    char Aliasinput[MAX_SIZE];
                    std::cin.clear();
                    std::cin.get(Aliasinput, MAX_SIZE);
                    std::cin.ignore(1000, '\n');
                    if (Aliasinput[0] != NULL && Aliasinput[0] != '\n' && Aliasinput[0] != '\0') {
                        Settings.AddAlias(Aliasinput, func.GetAliasName());
                        printf("Added \"%s\" as an alias for \"%s\"\n", Aliasinput, func.GetAliasName());
                    }
                    else {
                        printf("Canceled. No alias was added.\n");
                    }
                    
                    return;
                }

            }
        }
        


    }
    else if (strcmp("remove", MainCommand) == 0) {
        TrueNameIndex = 0;
        AliasIndex = 0;
        size_t i = 0;
        success = copyUntilChar(Argument, Argument, 50, needles, needleCount, i);
        debugPrintf("success: %d\n", success);
        debugPrintf("Argument: \"%s\"\n", Argument);

        for (Funktion& func : Settings.GetFunctions()) {
            TrueNameIndex++;

            size_t ParsedNumber = 0;
            bool success = parsePositiveNumber(Argument, 50, ParsedNumber);
            if (!success) { printf("An alias can not be selected using letters, please use \"remove x.y\" when removing an alias.\n"); return; };
            if (TrueNameIndex == ParsedNumber) {
                success = copyUntilChar(Argument, Argument, 50, needles, needleCount, i);
                for (const char* alias : func.GetAliases()) {
                    AliasIndex++;

                    if (AliasIndex == parsePositiveNumber(Argument, 50)) {
                        Settings.RemoveAlias(alias);
                        printf("Removed alias \"%s\" from \"%s\"\n", alias, func.GetAliasName());
                        return;
                    }
                }



            }
        }
        printf("No matching alias index found.\n");
        return;
    }
    else if (strcmp("edit", MainCommand) == 0) {
        TrueNameIndex = 0;
        AliasIndex = 0;
        size_t i = 0;
        success = copyUntilChar(Argument, Argument, 50, needles, needleCount, i);
        debugPrintf("success: %d\n", success);
        debugPrintf("Argument: \"%s\"\n", Argument);

        for (Funktion& func : Settings.GetFunctions()) {
            TrueNameIndex++;

            size_t ParsedNumber = 0;
            bool success = parsePositiveNumber(Argument, 50, ParsedNumber);
            if (!success) { printf("An alias can not be selected using letters, please use \"edit x.y\" when editing an alias.\n"); return; };
            if (TrueNameIndex == ParsedNumber) {
                success = copyUntilChar(Argument, Argument, 50, needles, needleCount, i);
                for (const char* alias : func.GetAliases()) {
                    AliasIndex++;

                    if (AliasIndex == parsePositiveNumber(Argument, 50)) {

                        if (SecondArgument[0] != NULL) {
                            Settings.EditAlias(alias, SecondArgument);
                            printf("Replaced alias \"%s\" with \"%s\" for the function \"%s\"\n", alias, SecondArgument, func.GetAliasName());
                        }
                        else {
                            printf("alias \"%s\" for the function \"%s\" selected.\nPlease enter the alias you would like to replace it with:\n", alias, func.GetAliasName());
                            char Aliasinput[MAX_SIZE];
                            std::cin.clear();
                            std::cin.get(Aliasinput, MAX_SIZE);
                            std::cin.ignore(1000, '\n');
                            if (Aliasinput[0] != NULL && Aliasinput[0] != '\n' && Aliasinput[0] != '\0') {
                                Settings.EditAlias(alias, Aliasinput);
                                printf("Replaced alias \"%s\" with \"%s\" for the function \"%s\"\n", alias, Aliasinput, func.GetAliasName());
                            }
                            else {
                                printf("Canceled. No alias was added.\n");
                            }
                        }
                        return;
                    }
                }



            }
        }
        printf("No matching alias index found.\n");
        return;
    }
    if (input[0] != '\n' && input[0] != '\0') {
        printf("Invalid command.\n");
        return;
    }
    else {
        return;
    }
    debugPrintf("Main command: \"%s\"\n", MainCommand);
    debugPrintf("Arugment: \"%s\"\n", Argument);
    debugPrintf("SecondArgument: \"%s\"\n", SecondArgument);

}
#endif
