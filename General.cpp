#include "General.h"

General::General(const std::string& name, int combatPower, int cost)
    : name(name), combatPower(combatPower), cost(cost), 
      recruited(false), provinceIndex(-1) {
}

std::string General::getName() const {
    return name;
}

int General::getCombatPower() const {
    return combatPower;
}

int General::getCost() const {
    return cost;
}

bool General::isRecruited() const {
    return recruited;
}

int General::getProvinceIndex() const {
    return provinceIndex;
}

void General::recruit() {
    recruited = true;
}

void General::assignToProvince(int index) {
    provinceIndex = index;
}
