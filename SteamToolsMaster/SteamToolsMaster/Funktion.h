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

    void AddAlias(const char* newAlias) {
        Aliases.push_back(newAlias);
    }
    Funktion(const char* aliasName, void (*f)(ToolSettings&, int&, const char* [])) {
        func = f;
        AliasName = aliasName;
    }
    ~Funktion() {
    }
};
#endif
