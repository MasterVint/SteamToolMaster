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
public:
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
            //we want to add a single item to TradePriceAlias
            if (InputCount > INITIAL_CAP) {
                TradePriceAlias = resizeArray(TradePriceAlias, TradePriceCount, InputCount);
                //this means that our array is too small for our new_value, thus we resize
            }
            TradePriceAlias[TradePriceCount] = _strdup(new_value);
            //std::cout << "added_alias: " << TradePriceCount << '\n';
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
        int is = i;
        while (src[i] != ',' && src[i] != '\0' && src[i] != '\n') {
            dest[i - is] = src[i];
           // std::cout << (i - is) << src[i] << std::endl;
            i++;
        }
        dest[i - is] = '\0';
        i++;
        return true;
    }

    //The most horrible filereader haha
    bool SerializeToolSettings() {
       // std::cout << "[SerializeToolSettings] Start" << '\n';
        //std::cout << "[SerializeToolSettings] TradePriceCount: " << TradePriceCount << '\n';
        std::ofstream SettingsCFG("./Settings.cfg");

        SettingsCFG << "#This .cfg file is used to store data such as key price, aliases and relevant settings." << '\n';
        SettingsCFG << "#Be wary of manually editing these values, spaces or ' ' are not trimmed." << '\n';
        SettingsCFG << "#alias,alias_category,aliasname1,aliasname2, ..." << '\n';
        SettingsCFG << "#keyprice,metal,refined,reclaimed,scrap,weapon" << '\n';
        SettingsCFG << "#keyprice,usd,price_in_cents ($1.70 == 170)" << '\n';

        //Seperate commented block from aliases
        SettingsCFG << '\n';

        //Write down aliases
        SettingsCFG << "\nalias,tradeprice";
        //std::cout << "count from serialized: " << TradePriceCount << '\n';
        for (size_t i = 0; i < TradePriceCount; i++) {
            //std::cout << "[SerializeToolSettings] Alias[" << i << "]: " << TradePriceAlias[i] << '\n';
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
       // std::cout << "[SerializeToolSettings] End" << '\n';
        return true;
    }
    bool ParseToolSettings() {
        //std::cout << "[ParseToolSettings] Start" << '\n';
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
                            //std::cout << "[ParseToolSettings] Adding alias: " << match << '\n';
                            AddAlias(match, "TradePriceAlias");
                            //std::cout << "Added tradeprice alias: " << match << std::endl;
                        }
                    } else if (strcmp("kitmaker", match) == 0) {
                        while (Line[needleIndex - 1] != '\0' && Line[needleIndex - 1] != '\n') {
                            ClearArray(match, match_size);
                            copyUntilComma(match, Line, needleIndex);
                           // std::cout << "[ParseToolSettings] Adding alias: " << match << '\n';
                            AddAlias(match, "KitMakerAlias");
                            //std::cout << "Added kitmaker alias: " << match << std::endl;
                        }
                    } else if (strcmp("setkey", match) == 0) {
                        while (Line[needleIndex - 1] != '\0' && Line[needleIndex - 1] != '\n') {
                            ClearArray(match, match_size);
                            copyUntilComma(match, Line, needleIndex);
                            //std::cout << "[ParseToolSettings] Adding alias: " << match << '\n';
                            AddAlias(match, "SetKeyAlias");
                            //std::cout << "Added setkey alias: " << match << std::endl;
                        }
                    }
                }
                else if (strcmp("keyprice", match) == 0) {
                    ClearArray(match, match_size);

                    copyUntilComma(match, Line, needleIndex);
                    //std::cout << match << std::endl;
                    if (strcmp("metal", match) == 0) {
                        size_t metalIndex = 0;
                        while(Line[needleIndex - 1] != '\0' && Line[needleIndex - 1] != '\n' && metalIndex < 4) {
                            ClearArray(match, match_size);
                            copyUntilComma(match, Line, needleIndex);
                            Metal_KeyPrice[metalIndex] = parsePositiveNumber(match, sizeof(match) / sizeof(match[0]));
                            CleanValue(Metal_KeyPrice[0], Metal_KeyPrice[1], Metal_KeyPrice[2], Metal_KeyPrice[3]);
                            //std::cout << Metal_KeyPrice[0] << '\n';
                            metalIndex++;
                           //std::cout <<  parsePositiveNumber(match, sizeof(match) / sizeof(match[0])) << '\n';
                        }
                    }
                    else if (strcmp("usd", match) == 0) {
                        ClearArray(match, match_size);
                        copyUntilComma(match, Line, needleIndex);
                        USD_KeyPrice = parsePositiveNumber(match, sizeof(match) / sizeof(match[0]));
                        //std::cout <<  parsePositiveNumber(match, sizeof(match) / sizeof(match[0])) << '\n';
                    }
                }
                //std::cout << "Processed Line: " << Line << '\n';
            }
           // std::cout << "Line: " << Line << '\n';
        }
        //// Close the file
        SettingsCFG.close();
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
