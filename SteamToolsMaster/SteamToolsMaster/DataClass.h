#ifndef DATACLASS_H
#define DATACLASS_H
#include <iostream>
//a class for the data such as settings, keyprice and command aliases
class ToolSettings {
private:
    // Dynamic arrays to store the aliases
    const char** TradePriceAlias;
    const char** KitMakerAlias;
    const char** SetKeyAlias;

    // Track the size of each array
    size_t TradePriceCount;
    size_t KitMakerCount;
    size_t SetKeyCount;

    size_t current_cap = 1;

    size_t metal_keyprice[4] = {60,2,2,1}; // Refined, Reclaimed, Scrap, Weapons
    size_t USD_keyprice = 178; // divide by 100 for actual price
public:
    Settings() {
        TradePriceAlias = new const char* [current_cap];
        KitMakerAlias = new const char* [current_cap];
        SetKeyAlias = new const char* [current_cap];
        TradePriceCount = 0;
        KitMakerCount = 0;
        SetKeyCount = 0;

        for (size_t i = 0; i < current_cap; i++) {
            TradePriceAlias[i] = nullptr;
            KitMakerAlias[i] = nullptr;
            SetKeyAlias[i] = nullptr;
        }
    }

    ~Settings() {
        // Clean up dynamically allocated memory
        for (size_t i = 0; i < TradePriceCount; i++) {
            delete[] TradePriceAlias[i];
        }
        delete[] TradePriceAlias;

        for (size_t i = 0; i < KitMakerCount; i++) {
            delete[] KitMakerAlias[i];
        }
        delete[] KitMakerAlias;

        for (size_t i = 0; i < SetKeyCount; i++) {
            delete[] SetKeyAlias[i];
        }
        delete[] SetKeyAlias;
    }

    const char** resizeArray(const char** arr, size_t& count, size_t& new_capacity) {
        const char** temp = new const char* [new_capacity];
        for (size_t i = 0; i < count; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        return temp;
    }

    void AddTradeAlias(const char* value) {
        size_t newsize = 0;
        const char** targetArray = nullptr;
        size_t count = 0;

        targetArray = TradePriceAlias;
        count = TradePriceCount;
        newsize = TradePriceCount + 1;

        if (newsize > current_cap) {
            TradePriceAlias = resizeArray(TradePriceAlias, count, newsize);
        }

        size_t valueLen = strlen(value) + 1;
        targetArray[count] = new char[valueLen];
        strcpy((char*)targetArray[count], value);
        count++;

    }

    const char** GetTradePriceAlias() { return TradePriceAlias; };
    const char** GetKitMakerAlias() { return KitMakerAlias; };
    const char** GetSetKeyAlias() { return SetKeyAlias; };

    size_t GetTradePriceCount() const { return TradePriceCount; };
    size_t GetKitMakerCount() const { return KitMakerCount; };
    size_t GetSetKeyCount() const { return SetKeyCount; };
};
#endif
