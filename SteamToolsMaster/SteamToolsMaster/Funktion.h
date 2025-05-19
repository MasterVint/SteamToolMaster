#ifndef FUNKTION_H
#define FUNKTION_H
#include "ToolSettings.h"
class ToolSettings;
class Funktion {
private:
    const char* AliasName; //This is the true name of the function
    std::vector<const char*> Aliases; //All of these names refer to this function
    void (*func)(ToolSettings&, int&, const char* []);

public:
    const char* GetAliasName() const {return AliasName;}
     std::vector<const char*> GetAliases()  {return Aliases;}
    void ExecuteFunction(ToolSettings &Settings, int &argc, const char* argv[]) {
        func(Settings, argc, argv);
    }

    bool EditAlias(const char* oldAlias, const char* newAlias) {
        bool success = false;
        for (size_t i = 0; i < Aliases.size(); i++) {
            debugPrintf(" \"%s\" and \"%s\"\n", oldAlias, Aliases[i]);
            if (strcmp(Aliases[i], oldAlias) == 0) {
                debugPrintf("[EditAlias] replaced \"%s\" with \"%s\"\n", oldAlias, newAlias);
                Aliases[i] = _strdup(newAlias);
                success = true;
            
            }

        }
        return success;
    }
    bool RemoveAlias(char* needle) {
        bool success = false;
        for (size_t i = 0; i < Aliases.size(); i++) {
            if (strcmp(Aliases[i], needle) == 0) {
                Aliases.erase(Aliases.begin() + i);
                Aliases.shrink_to_fit();
                debugPrintf("Erased %s\n", needle);
                success = true;
            }
        }
        return success;
    }
    bool RemoveAlias(const char* needle) {
        bool success = false;
        for (size_t i = 0; i < Aliases.size(); i++) {
            if (strcmp(Aliases[i], needle) == 0) {
                Aliases.erase(Aliases.begin() + i);
                Aliases.shrink_to_fit();
                debugPrintf("Erased %s\n", needle);
                success = true;
            }
        }
        return success;
    }
    void AddAlias(const char* newAlias) {
        Aliases.push_back(_strdup(newAlias));
    }
    Funktion(const char* aliasName, void (*f)(ToolSettings&, int&, const char* [])) {
        func = f;
        AliasName = aliasName;
    }
    ~Funktion() {
    }
};
#endif
