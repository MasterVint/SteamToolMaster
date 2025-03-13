#ifndef DATACLASS_H
#define DATACLASS_H
#include <iostream>
#include <fstream>
#include "functions.h"
#include <vector>
#include "Funktion.h"
//a class for the data such as settings, keyprice and command aliases
// 
class ToolSettings {
private:
    size_t Metal_KeyPrice[4] = { 60,0,0,0 }; // Refined, Reclaimed, Scrap, Weapons
    size_t USD_KeyPrice = 170; // Cents, divide by 100 for actual number
    // Dynamic arrays to store the aliases
    std::vector<Funktion> Functions;

    size_t Unique_Killstreak_Item = 292;
    size_t Unique_Specialized_Killstreak_Item = 900;
    size_t Battle_Worn_Robot_KB_808 = 20;
    size_t Battle_Worn_Robot_Taunt_Processor = 20;
    size_t Battle_Worn_Robot_Money_Furnace = 20;
    size_t Reinforced_Robot_Emotion_detector = 2;
    size_t Reinforced_Robot_Humor_Supression_Pump = 2;
    size_t Reinforced_Robot_Bomb_Stabilizer = 2;
    size_t Pristine_Robot_Brainstorm_Bulb = 50;





public:
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
    void ExecuteAliasMatch(char* value, ToolSettings &Settings, int &argc, const char* argv[]) {
        for (Funktion& Func : Functions) {
            for (const char* Alias : Func.GetAliases()) {
                //printf("Alias: %s, Value: %s, %s\n", Alias, value, Func.GetAliasName());
                if (strcmp(Alias, value) == 0) {
                    Func.ExecuteFunction(Settings, argc, argv);
                    return;
                }
            }
        }
        printf("No command or alias called \"%s\" exists.", value);
    }
    bool AddAlias(char* new_value, const char* category) {
        size_t InputCount = 0;
        for (Funktion& Func : Functions) {
            if (strcmp(Func.GetAliasName(), category) == 0) {
                Func.AddAlias(_strdup(new_value));
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

    //The most horrible filereader haha
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
        SettingsCFG << "\nalias,tradeprice";
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
                            printf("metals: %zu\n",Metal_KeyPrice[0]);
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
#endif
