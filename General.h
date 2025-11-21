#ifndef GENERAL_H
#define GENERAL_H

#include <string>

class General {
private:
    std::string name;
    int combatPower;
    int cost;
    bool recruited;
    int provinceIndex;  // -1 if not assigned

public:
    General(const std::string& name, int combatPower, int cost);
    
    std::string getName() const;
    int getCombatPower() const;
    int getCost() const;
    bool isRecruited() const;
    int getProvinceIndex() const;
    
    void recruit();
    void assignToProvince(int index);
};

#endif
