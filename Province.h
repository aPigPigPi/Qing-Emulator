#ifndef PROVINCE_H
#define PROVINCE_H

#include <string>

class Province {
private:
    std::string name;
    int troops;
    std::string controller;  // Which power controls this province
    int income;              // Economic value of this province
    int fortificationLevel;  // Defense level (0-5)
    int stability;           // Province stability (0-100)

public:
    Province(const std::string& name, const std::string& initialController, int income = 100);
    
    std::string getName() const;
    int getTroops() const;
    std::string getController() const;
    int getIncome() const;
    int getFortificationLevel() const;
    int getStability() const;
    
    void setTroops(int troops);
    void setController(const std::string& controller);
    void addTroops(int amount);
    void setIncome(int income);
    void upgradeFortification();
    void setStability(int stability);
    void adjustStability(int amount);
};

#endif
