#ifndef DATACLASS_H
#define DATACLASS_H
#include <iostream>
//a class for the data such as settings, keyprice and command aliases
// 
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

    size_t INITIAL_CAP = 1;
public:
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

    //This function is designed to only work when newsize is bigger than oldsize aka we make a bigger array than the input array.
    const char** resizeArray(const char** old_array, size_t &oldsize, size_t &newsize) {
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
            TradePriceAlias[TradePriceCount] = new_value;
            TradePriceCount++;
        } else if (strcmp(category, "KitMakerAlias") == 0) {
            InputCount = KitMakerCount + 1;
            if (InputCount > INITIAL_CAP) {
                KitMakerAlias = resizeArray(KitMakerAlias, KitMakerCount, InputCount);
            }
            KitMakerAlias[KitMakerCount] = new_value;
            KitMakerCount++;
        } else if (strcmp(category, "SetKeyAlias") == 0) {
            InputCount = SetKeyCount + 1;
            if (InputCount > INITIAL_CAP) {
                SetKeyAlias = resizeArray(SetKeyAlias, SetKeyCount, InputCount);
            }
            SetKeyAlias[SetKeyCount] = new_value;
            SetKeyCount++;
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
