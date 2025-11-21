#ifndef EVENT_H
#define EVENT_H

#include <string>

struct GameEvent {
    std::string title;
    std::string description;
    int stabilityEffect;
    int moneyEffect;
    int troopsEffect;
    
    GameEvent(const std::string& t, const std::string& d, int stab, int money, int troops)
        : title(t), description(d), stabilityEffect(stab), 
          moneyEffect(money), troopsEffect(troops) {}
};

#endif
