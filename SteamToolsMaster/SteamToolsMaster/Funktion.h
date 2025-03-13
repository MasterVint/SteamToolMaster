#ifndef FUNKTION_H
#define FUNKTION_H
#include "DataClass.h"
class ToolSettings;
class Funktion {
private:
    const char* AliasName;
    std::vector<const char*> Aliases;
    void (*func)(ToolSettings&, int&, const char* []);

public:
    const char* GetAliasName() const {
        return AliasName;
    }
     std::vector<const char*> GetAliases()  {
        return Aliases;
    }
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
