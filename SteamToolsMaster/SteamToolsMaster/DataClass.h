#ifndef DATACLASS_H
#define DATACLASS_H
#include <iostream>
#include <fstream>
#include "functions.h"
//a class for the data such as settings, keyprice and command aliases
// 
class ToolSettings {
private:
    size_t Metal_KeyPrice[4] = { 60,0,0,0 }; // Refined, Reclaimed, Scrap, Weapons
    size_t USD_KeyPrice = 170; // Cents, divide by 100 for actual number

    // Dynamic arrays to store the aliases
	const char** TradePriceAlias;
    const char** KitMakerAlias;
    const char** SetKeyAlias;

    // Track the size of each array
    size_t TradePriceCount = 0;
    size_t KitMakerCount = 0;	
    size_t SetKeyCount = 0;

    size_t INITIAL_CAP = 1;

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
    size_t* SetMetal_KeyPrice(size_t* NewKeyPrice) {
        for (size_t i = 0; i < 4; i++) {
            Metal_KeyPrice[i] = NewKeyPrice[i];
        };
    };
    size_t* GetMetal_KeyPrice() { return Metal_KeyPrice; };
    size_t GetUnique_Killstreak_Item() { return Unique_Killstreak_Item; };
    size_t GetUnique_Specialized_Killstreak_Item() { return Unique_Specialized_Killstreak_Item; };
    size_t GetBattle_Worn_Robot_KB_808() { return Battle_Worn_Robot_KB_808; };
    size_t GetBattle_Worn_Robot_Taunt_Processor() { return Battle_Worn_Robot_Taunt_Processor; };
    size_t GetBattle_Worn_Robot_Money_Furnace() { return Battle_Worn_Robot_Money_Furnace; };
    size_t GetReinforced_Robot_Emotion_detector() { return Reinforced_Robot_Emotion_detector; };
    size_t GetReinforced_Robot_Humor_Supression_Pump() { return Reinforced_Robot_Humor_Supression_Pump; };
    size_t GetReinforced_Robot_Bomb_Stabilizer() { return Reinforced_Robot_Bomb_Stabilizer; };
    size_t GetPristine_Robot_Brainstorm_Bulb() { return Pristine_Robot_Brainstorm_Bulb; };
    //This function is designed to only work when newsize is bigger than oldsize aka we make a bigger array than the input array.
    const char** resizeArray(const char** old_array, size_t& oldsize, size_t& newsize) {
        const char** new_array = new const char* [newsize];
        for (size_t i = 0; i < oldsize; i++) {
            new_array[i] = old_array[i];
        }
        delete[] old_array;
        return new_array;
    }
    const char* CheckAgainstAlias(const char* value) {
        #ifdef _DEBUG
            printf("TradePriceCount: %zu\n", TradePriceCount);
            printf("KitMakerCount: %zu\n", KitMakerCount);
            printf("SetKeyCount: %zu\n", SetKeyCount);
        #endif
        for (size_t i = 0; i < TradePriceCount; i++) {
            if (strcmp(value, TradePriceAlias[i]) == 0) {
                return "TradePriceAlias";
            }
        }
        for (size_t i = 0; i < KitMakerCount; i++) {
            if (strcmp(value, KitMakerAlias[i]) == 0) {
                return "KitMakerAlias";
            }
        }
        for (size_t i = 0; i < SetKeyCount; i++) {
            if (strcmp(value, SetKeyAlias[i]) == 0) {
                return "SetKeyAlias";
            }
        }
        return "none";
    }
    void AddAlias(const char* new_value, const char* category) {
        size_t InputCount = 0;
        if (strcmp(category, "TradePriceAlias") == 0) {
            InputCount = TradePriceCount + 1;
            //we add a single item to TradePriceAlias
            if (InputCount > INITIAL_CAP) {
                TradePriceAlias = resizeArray(TradePriceAlias, TradePriceCount, InputCount);
                //this means that our array is too small for our new_value, thus we resize
            }
            TradePriceAlias[TradePriceCount] = _strdup(new_value);
            TradePriceCount++;
        }
        else if (strcmp(category, "KitMakerAlias") == 0) {
            InputCount = KitMakerCount + 1;
            if (InputCount > INITIAL_CAP) {
                KitMakerAlias = resizeArray(KitMakerAlias, KitMakerCount, InputCount);
            }
            KitMakerAlias[KitMakerCount] = _strdup(new_value);;
            KitMakerCount++;
        }
        else if (strcmp(category, "SetKeyAlias") == 0) {
            InputCount = SetKeyCount + 1;
            if (InputCount > INITIAL_CAP) {
                SetKeyAlias = resizeArray(SetKeyAlias, SetKeyCount, InputCount);
            }
            SetKeyAlias[SetKeyCount] = _strdup(new_value);;
            SetKeyCount++;
        }
        return;
    }

    void ClearArray(char* array, const size_t len) {
        for (size_t i = 0; i < len; i++) {
            array[i] = NULL;
        }
    }
    bool copyUntilComma(char* dest, const char* src, size_t &i) {
        size_t is = i;
        while (src[i] != ',' && src[i] != '\0' && src[i] != '\n') {
            dest[i - is] = src[i];
           // std::cout << (i - is) << src[i] << std::endl;
            i++;
        }
        dest[i - is] = '\0';
        i++;
        return true;
    }

    void PrintToolSettings() {
        //Print all the aliases
        for (size_t i = 0; i < TradePriceCount; i++) {
            
            printf(TradePriceAlias[i]);
        }
        for (size_t i = 0; i < KitMakerCount; i++) {
            printf(TradePriceAlias[i]);
        }
        for (size_t i = 0; i < SetKeyCount; i++) {
            printf(TradePriceAlias[i]);
        }
    }

    //The most horrible filereader haha
    bool SerializeToolSettings() {
        #ifdef _DEBUG
        printf("[SerializeToolSettings] Start\n");
        printf("[SerializeToolSettings] TradePriceCount: %zu\n", TradePriceCount);
        #endif
        std::ofstream SettingsCFG("./Settings.cfg");

        SettingsCFG << "#This .cfg file is used to store data such as key price, aliases and relevant settings." << '\n';
        SettingsCFG << "#Be wary of manually editing these values, spaces or ' ' are not trimmed." << '\n';
        SettingsCFG << "#alias,alias_category,aliasname1,aliasname2, ..." << '\n';
        SettingsCFG << "#keyprice,metal,refined,reclaimed,scrap,weapon" << '\n';
        SettingsCFG << "#keyprice,usd,price_in_cents ($1.70 == 170)" << '\n';

        //Write down aliases
        SettingsCFG << "\nalias,tradeprice";
        for (size_t i = 0; i < TradePriceCount; i++) {
            SettingsCFG << "," << TradePriceAlias[i];
        }
        SettingsCFG << "\nalias,kitmaker";
        for (size_t i = 0; i < KitMakerCount; i++) {
            SettingsCFG << "," << KitMakerAlias[i];
        }
        SettingsCFG << "\nalias,setkey";
        for (size_t i = 0; i < SetKeyCount; i++) {
            SettingsCFG << "," << SetKeyAlias[i];
        }

        //Seperate aliases from keyprice
        SettingsCFG << '\n';

        SettingsCFG << "\nkeyprice,metal";
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
            printf("[ParseToolSettings] TradePriceCount: %zu\n", TradePriceCount);
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
                    if (strcmp("tradeprice", match) == 0) {
                        while (Line[needleIndex - 1] != '\0' && Line[needleIndex - 1] != '\n') {
                            ClearArray(match, match_size);
                            copyUntilComma(match, Line, needleIndex);
                            #ifdef _DEBUG
                                printf("[ParseToolSettings] Adding TradePriceAlias: %s\n", match);
                            #endif
                            AddAlias(match, "TradePriceAlias");
                        }
                    } else if (strcmp("kitmaker", match) == 0) {
                        while (Line[needleIndex - 1] != '\0' && Line[needleIndex - 1] != '\n') {
                            ClearArray(match, match_size);
                            copyUntilComma(match, Line, needleIndex);
                            #ifdef _DEBUG
                                printf("[ParseToolSettings] Adding KitMakerAlias: %s\n", match);
                            #endif
                            AddAlias(match, "KitMakerAlias");
                        }
                    } else if (strcmp("setkey", match) == 0) {
                        while (Line[needleIndex - 1] != '\0' && Line[needleIndex - 1] != '\n') {
                            ClearArray(match, match_size);
                            copyUntilComma(match, Line, needleIndex);
                            #ifdef _DEBUG
                                printf("[ParseToolSettings] Adding SetKeyAlias: %s\n", match);
                            #endif
                            AddAlias(match, "SetKeyAlias");
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
                printf("[ParseToolSettings] End, TradePriceCount: %zu\n", TradePriceCount);
        #endif
        //std::cout << "[ParseToolSettings] End, TradePriceCount = " << TradePriceCount << '\n';
        return true;
    }
    ToolSettings() {
        TradePriceAlias = new const char* [INITIAL_CAP];
        KitMakerAlias = new const char* [INITIAL_CAP];
        SetKeyAlias = new const char* [INITIAL_CAP];
        TradePriceCount = 0;
        KitMakerCount = 0;
        SetKeyCount = 0;

        for (size_t i = 0; i < INITIAL_CAP; i++) {
            TradePriceAlias[i] = nullptr;
            KitMakerAlias[i] = nullptr;
            SetKeyAlias[i] = nullptr;
        }
    }

    ~ToolSettings() {

        delete[] TradePriceAlias;
        delete[] KitMakerAlias;
        delete[] SetKeyAlias;
    }

    

    const char** GetTradePriceAlias() { return TradePriceAlias; };
    const char** GetKitMakerAlias() { return KitMakerAlias; };
    const char** GetSetKeyAlias() { return SetKeyAlias; };

    size_t GetTradePriceCount() const { return TradePriceCount; };
    size_t GetKitMakerCount() const { return KitMakerCount; };
    size_t GetSetKeyCount() const { return SetKeyCount; };
};
#endif
