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
    ToolSettings() {
        TradePriceAlias = new const char* [current_cap];
        KitMakerAlias = new const char* [current_cap];
        SetKeyAlias = new const char* [current_cap];
        TradePriceCount = 1;
        KitMakerCount = 1;
        SetKeyCount = 1;

        for (size_t i = 0; i < current_cap; i++) {
            TradePriceAlias[i] = nullptr;
            KitMakerAlias[i] = nullptr;
            SetKeyAlias[i] = nullptr;
        }
    }

    ~ToolSettings() {
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

    void AddAlias(const char* value, const char* category) {
        size_t newsize = 0;
        const char** targetArray;
        size_t count = 0;

        if (strcmp(category, "TradePriceAlias") == 0) {
            //sgiam
            std::cout << "!iim here" << "\n";
            targetArray = TradePriceAlias;
            count = TradePriceCount;
            TradePriceCount += 1;
            newsize = TradePriceCount;
            if (newsize > current_cap) {
                TradePriceAlias = resizeArray(TradePriceAlias, count, newsize);
            }
        }
        else if (strcmp(category, "KitMakerAlias") == 0) {
            targetArray = KitMakerAlias;
            count = KitMakerCount;
            KitMakerCount += 1;
            newsize = KitMakerCount;
            if (newsize > current_cap) {
                KitMakerAlias = resizeArray(KitMakerAlias, count, newsize);
            }
        }
        else if (strcmp(category, "SetKeyAlias") == 0) {
            targetArray = SetKeyAlias;
            count = SetKeyCount;
            SetKeyCount += 1;
            newsize = SetKeyCount;
            if (newsize > current_cap) {
                SetKeyAlias = resizeArray(SetKeyAlias, count, newsize);
            }
        }
        else {
            return;
        }

        size_t valueLen = strlen(value) + 1;
        targetArray[count] = new char[valueLen];
       // strcpy();
       // strcpy((char*)targetArray[count],,value);
        strcpy_s((char*)targetArray[count], sizeof(targetArray[count]), value);
        count++;
        for (size_t i = 0; i < count; i++) {
            std::cout << targetArray[i] << '\n';
        }

    }

    const char** GetTradePriceAlias() { return TradePriceAlias; };
    const char** GetKitMakerAlias() { return KitMakerAlias; };
    const char** GetSetKeyAlias() { return SetKeyAlias; };

    size_t GetTradePriceCount() const { return TradePriceCount; };
    size_t GetKitMakerCount() const { return KitMakerCount; };
    size_t GetSetKeyCount() const { return SetKeyCount; };
};
#endif
