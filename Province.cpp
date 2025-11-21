#include "Province.h"
#include <algorithm>

Province::Province(const std::string& name, const std::string& initialController, int income)
    : name(name), troops(100), controller(initialController), 
      income(income), fortificationLevel(0), stability(100) {
}

std::string Province::getName() const {
    return name;
}

int Province::getTroops() const {
    return troops;
}

std::string Province::getController() const {
    return controller;
}

int Province::getIncome() const {
    return income;
}

int Province::getFortificationLevel() const {
    return fortificationLevel;
}

int Province::getStability() const {
    return stability;
}

void Province::setTroops(int troops) {
    this->troops = troops;
}

void Province::setController(const std::string& controller) {
    this->controller = controller;
}

void Province::addTroops(int amount) {
    this->troops += amount;
}

void Province::setIncome(int income) {
    this->income = income;
}

void Province::upgradeFortification() {
    if (fortificationLevel < 5) {
        fortificationLevel++;
    }
}

void Province::setStability(int stability) {
    this->stability = std::max(0, std::min(100, stability));
}

void Province::adjustStability(int amount) {
    this->stability = std::max(0, std::min(100, this->stability + amount));
}
