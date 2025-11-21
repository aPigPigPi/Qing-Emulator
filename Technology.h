#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H

#include <string>
#include <vector>

struct Technology {
    std::string name;
    std::string description;
    int cost;
    bool researched;
    int militaryBonus;    // Bonus to military power
    int economicBonus;    // Bonus to income
    
    Technology(const std::string& n, const std::string& desc, int c, int milBonus, int ecoBonus)
        : name(n), description(desc), cost(c), researched(false), 
          militaryBonus(milBonus), economicBonus(ecoBonus) {}
};

#endif
