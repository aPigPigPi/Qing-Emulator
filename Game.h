#ifndef GAME_H
#define GAME_H

#include "Province.h"
#include "Technology.h"
#include "General.h"
#include "Event.h"
#include <vector>
#include <string>
#include <memory>
#include <map>

class Game {
private:
    std::vector<std::unique_ptr<Province>> provinces;
    std::vector<std::string> foreignPowers;
    std::vector<Technology> technologies;
    std::vector<General> generals;
    std::map<std::string, int> diplomacy;  // Relationship with each power (-100 to 100)
    
    int turn;
    bool gameOver;
    bool victory;
    int treasury;          // Money for Qing
    int reformLevel;       // Overall reform progress (0-100)
    int militaryTech;      // Military technology level
    int spyNetwork;        // Intelligence network level (0-5)

    void initProvinces();
    void initTechnologies();
    void initGenerals();
    void initDiplomacy();
    
    void foreignPowersAction();
    void checkGameOver();
    void displayProvinces() const;
    void displayStatus() const;
    void collectIncome();
    void randomEvent();
    
    // Player actions
    void stationTroops(int provinceIndex, int troops);
    void recruitTroops(int amount);
    void researchTechnology();
    void recruitGeneral();
    void performDiplomacy();
    void conductEspionage();
    void buildFortification(int provinceIndex);
    void enactReforms();
    
public:
    Game();
    void run();
    bool isGameOver() const;
    bool isVictory() const;
    int getQingProvinceCount() const;
};

#endif
