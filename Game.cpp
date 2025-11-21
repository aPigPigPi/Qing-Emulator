#include "Game.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Game::Game() : turn(0), gameOver(false), victory(false), 
               treasury(1000), reformLevel(0), militaryTech(0), spyNetwork(0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initProvinces();
    initTechnologies();
    initGenerals();
    initDiplomacy();
    
    foreignPowers.push_back("英国");  // Britain
    foreignPowers.push_back("法国");  // France
    foreignPowers.push_back("俄国");  // Russia
    foreignPowers.push_back("日本");  // Japan
    foreignPowers.push_back("德国");  // Germany
}

void Game::initProvinces() {
    // Initialize 18 provinces with varying income levels
    provinces.push_back(std::make_unique<Province>("直隶", "清国", 150));   // Zhili - Capital region
    provinces.push_back(std::make_unique<Province>("山东", "清国", 120));
    provinces.push_back(std::make_unique<Province>("山西", "清国", 80));
    provinces.push_back(std::make_unique<Province>("河南", "清国", 100));
    provinces.push_back(std::make_unique<Province>("江苏", "清国", 200));   // Rich region
    provinces.push_back(std::make_unique<Province>("安徽", "清国", 90));
    provinces.push_back(std::make_unique<Province>("江西", "清国", 85));
    provinces.push_back(std::make_unique<Province>("浙江", "清国", 180));   // Rich coastal
    provinces.push_back(std::make_unique<Province>("福建", "清国", 110));
    provinces.push_back(std::make_unique<Province>("湖北", "清国", 100));
    provinces.push_back(std::make_unique<Province>("湖南", "清国", 95));
    provinces.push_back(std::make_unique<Province>("广东", "清国", 220));   // Very rich
    provinces.push_back(std::make_unique<Province>("广西", "清国", 70));
    provinces.push_back(std::make_unique<Province>("四川", "清国", 130));
    provinces.push_back(std::make_unique<Province>("陕西", "清国", 75));
    provinces.push_back(std::make_unique<Province>("甘肃", "清国", 60));
    provinces.push_back(std::make_unique<Province>("云南", "清国", 80));
    provinces.push_back(std::make_unique<Province>("贵州", "清国", 65));
}

void Game::initTechnologies() {
    technologies.push_back(Technology("洋务运动", "学习西方技术，提升工业能力", 500, 20, 50));
    technologies.push_back(Technology("新式陆军", "建立现代化陆军", 800, 50, 0));
    technologies.push_back(Technology("北洋水师", "建立现代海军", 1000, 40, 0));
    technologies.push_back(Technology("铁路建设", "修建铁路网络", 600, 10, 80));
    technologies.push_back(Technology("电报系统", "建立通讯网络", 400, 15, 30));
    technologies.push_back(Technology("维新变法", "进行政治改革", 700, 25, 60));
}

void Game::initGenerals() {
    generals.push_back(General("左宗棠", 85, 300));
    generals.push_back(General("李鸿章", 75, 250));
    generals.push_back(General("曾国藩", 80, 280));
    generals.push_back(General("袁世凯", 70, 200));
    generals.push_back(General("刘永福", 65, 180));
}

void Game::initDiplomacy() {
    for (const auto& power : foreignPowers) {
        diplomacy[power] = -50;  // Start with negative relations
    }
}

void Game::displayProvinces() const {
    std::cout << "\n========================================\n";
    std::cout << "          第 " << turn << " 回合 - 省份状况\n";
    std::cout << "========================================\n";
    std::cout << std::left << std::setw(10) << "省份" 
              << std::setw(10) << "控制者" 
              << std::setw(8) << "驻军"
              << std::setw(8) << "收入"
              << std::setw(8) << "防御"
              << std::setw(8) << "稳定" << "\n";
    std::cout << "----------------------------------------\n";
    
    for (const auto& province : provinces) {
        std::cout << std::left << std::setw(10) << province->getName()
                  << std::setw(10) << province->getController()
                  << std::setw(8) << province->getTroops()
                  << std::setw(8) << province->getIncome()
                  << std::setw(8) << province->getFortificationLevel()
                  << std::setw(8) << province->getStability() << "\n";
    }
    
    std::cout << "========================================\n";
    std::cout << "清国控制省份数: " << getQingProvinceCount() << "/" << provinces.size() << "\n";
    std::cout << "========================================\n\n";
}

void Game::displayStatus() const {
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║       大清帝国 - 国家状况          ║\n";
    std::cout << "╠════════════════════════════════════╣\n";
    std::cout << "║ 回合: " << std::setw(28) << std::left << turn << "║\n";
    std::cout << "║ 国库: " << std::setw(28) << std::left << treasury << "║\n";
    std::cout << "║ 改革进度: " << std::setw(24) << std::left << reformLevel << "║\n";
    std::cout << "║ 军事科技: " << std::setw(24) << std::left << militaryTech << "║\n";
    std::cout << "║ 谍报等级: " << std::setw(24) << std::left << spyNetwork << "║\n";
    std::cout << "╠════════════════════════════════════╣\n";
    std::cout << "║ 外交关系:                          ║\n";
    for (const auto& pair : diplomacy) {
        std::string status;
        if (pair.second >= 50) status = "友好";
        else if (pair.second >= 0) status = "中立";
        else if (pair.second >= -50) status = "冷淡";
        else status = "敌对";
        std::cout << "║   " << std::setw(8) << pair.first 
                  << std::setw(24) << std::left << status << "║\n";
    }
    std::cout << "╚════════════════════════════════════╝\n\n";
}

void Game::collectIncome() {
    int income = 0;
    for (const auto& province : provinces) {
        if (province->getController() == "清国") {
            int provinceIncome = province->getIncome();
            // Apply technology bonuses
            for (const auto& tech : technologies) {
                if (tech.researched) {
                    provinceIncome += tech.economicBonus / 10;
                }
            }
            income += provinceIncome;
        }
    }
    treasury += income;
    std::cout << "本回合收入: " << income << " 银两\n";
}

void Game::randomEvent() {
    int chance = std::rand() % 100;
    
    if (chance < 15) {  // 15% chance for an event
        int eventType = std::rand() % 5;
        GameEvent event("", "", 0, 0, 0);
        
        switch (eventType) {
            case 0:
                event = GameEvent("太平天国起义", 
                    "农民起义爆发，多个省份陷入动乱", 
                    -20, -300, -500);
                break;
            case 1:
                event = GameEvent("义和团运动", 
                    "排外运动兴起，列强不满", 
                    -15, -200, 0);
                for (auto& pair : diplomacy) {
                    pair.second -= 10;
                }
                break;
            case 2:
                event = GameEvent("洋务运动成果", 
                    "工厂建设取得进展", 
                    10, 500, 0);
                break;
            case 3:
                event = GameEvent("丰收之年", 
                    "风调雨顺，农业丰收", 
                    15, 400, 0);
                break;
            case 4:
                event = GameEvent("天灾", 
                    "水旱灾害影响多个省份", 
                    -10, -250, 0);
                break;
        }
        
        std::cout << "\n╔════════════════════════════════════╗\n";
        std::cout << "║ ★ 事件: " << std::setw(26) << std::left << event.title << "║\n";
        std::cout << "╠════════════════════════════════════╣\n";
        std::cout << "║ " << std::setw(35) << std::left << event.description << "║\n";
        std::cout << "╚════════════════════════════════════╝\n\n";
        
        treasury += event.moneyEffect;
        
        if (event.stabilityEffect != 0) {
            for (auto& province : provinces) {
                if (province->getController() == "清国") {
                    province->adjustStability(event.stabilityEffect);
                }
            }
        }
    }
}

void Game::stationTroops(int provinceIndex, int troops) {
    if (provinceIndex >= 0 && provinceIndex < static_cast<int>(provinces.size())) {
        if (provinces[provinceIndex]->getController() == "清国") {
            int cost = troops * 2;  // Each troop costs 2 silver
            if (treasury >= cost) {
                provinces[provinceIndex]->addTroops(troops);
                treasury -= cost;
                std::cout << "已在 " << provinces[provinceIndex]->getName() 
                          << " 增派 " << troops << " 名士兵 (花费: " << cost << ")\n";
            } else {
                std::cout << "国库不足！需要 " << cost << " 银两\n";
            }
        } else {
            std::cout << "该省份不在清国控制之下！\n";
        }
    } else {
        std::cout << "无效的省份编号！\n";
    }
}

void Game::recruitTroops(int amount) {
    int cost = amount * 2;
    if (treasury >= cost) {
        treasury -= cost;
        // Add troops to capital (index 0)
        provinces[0]->addTroops(amount);
        std::cout << "在直隶招募了 " << amount << " 名士兵 (花费: " << cost << ")\n";
    } else {
        std::cout << "国库不足！需要 " << cost << " 银两\n";
    }
}

void Game::researchTechnology() {
    std::cout << "\n=== 可研究科技 ===\n";
    bool hasAvailable = false;
    for (size_t i = 0; i < technologies.size(); i++) {
        if (!technologies[i].researched) {
            hasAvailable = true;
            std::cout << i << ". " << technologies[i].name 
                      << " - " << technologies[i].description
                      << " (花费: " << technologies[i].cost << ")\n";
            std::cout << "   效果: 军事+" << technologies[i].militaryBonus 
                      << " 经济+" << technologies[i].economicBonus << "\n";
        }
    }
    
    if (!hasAvailable) {
        std::cout << "所有科技已研究完毕！\n";
        return;
    }
    
    std::cout << "\n输入科技编号 (-1取消): ";
    int choice;
    std::cin >> choice;
    
    if (choice >= 0 && choice < static_cast<int>(technologies.size()) && 
        !technologies[choice].researched) {
        if (treasury >= technologies[choice].cost) {
            treasury -= technologies[choice].cost;
            technologies[choice].researched = true;
            militaryTech += technologies[choice].militaryBonus;
            std::cout << "成功研究 " << technologies[choice].name << "！\n";
        } else {
            std::cout << "国库不足！\n";
        }
    }
}

void Game::recruitGeneral() {
    std::cout << "\n=== 可招募将领 ===\n";
    bool hasAvailable = false;
    for (size_t i = 0; i < generals.size(); i++) {
        if (!generals[i].isRecruited()) {
            hasAvailable = true;
            std::cout << i << ". " << generals[i].getName()
                      << " (战力: " << generals[i].getCombatPower()
                      << ", 花费: " << generals[i].getCost() << ")\n";
        }
    }
    
    if (!hasAvailable) {
        std::cout << "所有将领已招募！\n";
        return;
    }
    
    std::cout << "\n输入将领编号 (-1取消): ";
    int choice;
    std::cin >> choice;
    
    if (choice >= 0 && choice < static_cast<int>(generals.size()) && 
        !generals[choice].isRecruited()) {
        if (treasury >= generals[choice].getCost()) {
            treasury -= generals[choice].getCost();
            generals[choice].recruit();
            std::cout << "成功招募 " << generals[choice].getName() << "！\n";
        } else {
            std::cout << "国库不足！\n";
        }
    }
}

void Game::performDiplomacy() {
    std::cout << "\n=== 外交行动 ===\n";
    std::cout << "1. 贿赂列强 (提升关系)\n";
    std::cout << "2. 签订条约 (避免战争)\n";
    std::cout << "0. 取消\n";
    std::cout << "选择: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 1) {
        std::cout << "选择国家:\n";
        for (size_t i = 0; i < foreignPowers.size(); i++) {
            std::cout << i << ". " << foreignPowers[i] << " (关系: " 
                      << diplomacy[foreignPowers[i]] << ")\n";
        }
        std::cout << "输入编号: ";
        int powerIdx;
        std::cin >> powerIdx;
        
        if (powerIdx >= 0 && powerIdx < static_cast<int>(foreignPowers.size())) {
            int cost = 300;
            if (treasury >= cost) {
                treasury -= cost;
                diplomacy[foreignPowers[powerIdx]] += 20;
                if (diplomacy[foreignPowers[powerIdx]] > 100) {
                    diplomacy[foreignPowers[powerIdx]] = 100;
                }
                std::cout << "成功改善与 " << foreignPowers[powerIdx] << " 的关系！\n";
            } else {
                std::cout << "国库不足！需要 " << cost << " 银两\n";
            }
        }
    } else if (choice == 2) {
        int cost = 500;
        if (treasury >= cost) {
            treasury -= cost;
            for (auto& pair : diplomacy) {
                pair.second += 10;
                if (pair.second > 100) pair.second = 100;
            }
            std::cout << "与列强签订和平条约，关系普遍改善！\n";
        } else {
            std::cout << "国库不足！需要 " << cost << " 银两\n";
        }
    }
}

void Game::conductEspionage() {
    std::cout << "\n=== 谍报行动 ===\n";
    std::cout << "当前谍报等级: " << spyNetwork << "/5\n";
    std::cout << "1. 升级谍报网络 (花费: " << (spyNetwork + 1) * 200 << ")\n";
    std::cout << "2. 刺探敌情\n";
    std::cout << "3. 破坏敌方省份\n";
    std::cout << "0. 取消\n";
    std::cout << "选择: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 1) {
        if (spyNetwork < 5) {
            int cost = (spyNetwork + 1) * 200;
            if (treasury >= cost) {
                treasury -= cost;
                spyNetwork++;
                std::cout << "谍报网络升级至等级 " << spyNetwork << "！\n";
            } else {
                std::cout << "国库不足！\n";
            }
        } else {
            std::cout << "谍报网络已达最高等级！\n";
        }
    } else if (choice == 2) {
        if (spyNetwork > 0) {
            std::cout << "\n=== 敌方情报 ===\n";
            for (const auto& province : provinces) {
                if (province->getController() != "清国") {
                    std::cout << province->getName() << " (" << province->getController() 
                              << ") - 驻军: " << province->getTroops() << "\n";
                }
            }
        } else {
            std::cout << "需要先建立谍报网络！\n";
        }
    } else if (choice == 3) {
        if (spyNetwork >= 2) {
            std::vector<int> enemyProvinces;
            for (size_t i = 0; i < provinces.size(); i++) {
                if (provinces[i]->getController() != "清国") {
                    enemyProvinces.push_back(i);
                }
            }
            
            if (!enemyProvinces.empty()) {
                int target = enemyProvinces[std::rand() % enemyProvinces.size()];
                int damage = 30 + std::rand() % 50;
                provinces[target]->setTroops(
                    std::max(0, provinces[target]->getTroops() - damage)
                );
                std::cout << "成功破坏 " << provinces[target]->getName() 
                          << "，削弱敌军 " << damage << " 人！\n";
            } else {
                std::cout << "没有可破坏的敌方省份！\n";
            }
        } else {
            std::cout << "谍报等级不足！需要等级2以上\n";
        }
    }
}

void Game::buildFortification(int provinceIndex) {
    if (provinceIndex >= 0 && provinceIndex < static_cast<int>(provinces.size())) {
        if (provinces[provinceIndex]->getController() == "清国") {
            int cost = (provinces[provinceIndex]->getFortificationLevel() + 1) * 150;
            if (treasury >= cost && provinces[provinceIndex]->getFortificationLevel() < 5) {
                treasury -= cost;
                provinces[provinceIndex]->upgradeFortification();
                std::cout << "在 " << provinces[provinceIndex]->getName() 
                          << " 建造防御工事！当前等级: " 
                          << provinces[provinceIndex]->getFortificationLevel() << "\n";
            } else if (provinces[provinceIndex]->getFortificationLevel() >= 5) {
                std::cout << "该省份防御工事已达最高等级！\n";
            } else {
                std::cout << "国库不足！需要 " << cost << " 银两\n";
            }
        } else {
            std::cout << "该省份不在清国控制之下！\n";
        }
    } else {
        std::cout << "无效的省份编号！\n";
    }
}

void Game::enactReforms() {
    std::cout << "\n=== 进行改革 ===\n";
    std::cout << "当前改革进度: " << reformLevel << "/100\n";
    std::cout << "推进改革需要 400 银两\n";
    std::cout << "确认推进改革? (1=是, 0=否): ";
    
    int confirm;
    std::cin >> confirm;
    
    if (confirm == 1) {
        int cost = 400;
        if (treasury >= cost && reformLevel < 100) {
            treasury -= cost;
            reformLevel += 10;
            militaryTech += 5;
            
            // Improve stability in all Qing provinces
            for (auto& province : provinces) {
                if (province->getController() == "清国") {
                    province->adjustStability(5);
                }
            }
            
            std::cout << "改革成功推进！改革进度: " << reformLevel << "/100\n";
            std::cout << "全国稳定度提升，军事科技提升！\n";
        } else if (reformLevel >= 100) {
            std::cout << "改革已完成！\n";
        } else {
            std::cout << "国库不足！\n";
        }
    }
}

void Game::foreignPowersAction() {
    std::cout << "\n--- 列强行动 ---\n";
    
    for (const auto& power : foreignPowers) {
        // Diplomatic status affects aggressiveness
        int relationship = diplomacy[power];
        int actionChance = std::rand() % 100;
        
        // Better relations reduce attack chance
        if (relationship > 0 && actionChance < relationship / 2) {
            std::cout << power << " 保持和平态度\n";
            continue;
        }
        
        int action = std::rand() % 4;
        
        if (action == 0 || action == 1) {
            // Try to attack a Qing province
            std::vector<int> qingProvinces;
            for (size_t i = 0; i < provinces.size(); i++) {
                if (provinces[i]->getController() == "清国") {
                    qingProvinces.push_back(i);
                }
            }
            
            if (!qingProvinces.empty()) {
                int targetIndex = qingProvinces[std::rand() % qingProvinces.size()];
                int attackPower = 50 + std::rand() % 100;
                int defense = provinces[targetIndex]->getTroops() + 
                             provinces[targetIndex]->getFortificationLevel() * 20;
                
                // Check if general is defending
                for (const auto& general : generals) {
                    if (general.isRecruited() && 
                        general.getProvinceIndex() == targetIndex) {
                        defense += general.getCombatPower();
                    }
                }
                
                defense += militaryTech;  // Add tech bonus
                
                if (attackPower > defense) {
                    std::cout << power << " 攻占了 " << provinces[targetIndex]->getName() << "！\n";
                    provinces[targetIndex]->setController(power);
                    provinces[targetIndex]->setTroops(attackPower - defense);
                    provinces[targetIndex]->setStability(50);
                    diplomacy[power] -= 10;  // Worsen relations
                } else {
                    std::cout << power << " 进攻 " << provinces[targetIndex]->getName() 
                              << " 失败\n";
                    provinces[targetIndex]->setTroops(defense - attackPower / 2);
                }
            }
        } else if (action == 2) {
            // Reinforce a province they control
            std::vector<int> controlledProvinces;
            for (size_t i = 0; i < provinces.size(); i++) {
                if (provinces[i]->getController() == power) {
                    controlledProvinces.push_back(i);
                }
            }
            
            if (!controlledProvinces.empty()) {
                int targetIndex = controlledProvinces[std::rand() % controlledProvinces.size()];
                int reinforcement = 30 + std::rand() % 50;
                provinces[targetIndex]->addTroops(reinforcement);
                std::cout << power << " 在 " << provinces[targetIndex]->getName() 
                          << " 增兵 " << reinforcement << "\n";
            }
        }
        // else: diplomatic action or nothing
    }
    std::cout << "\n";
}

int Game::getQingProvinceCount() const {
    int count = 0;
    for (const auto& province : provinces) {
        if (province->getController() == "清国") {
            count++;
        }
    }
    return count;
}

void Game::checkGameOver() {
    int qingProvinces = getQingProvinceCount();
    
    if (qingProvinces < 8) {
        gameOver = true;
        victory = false;
        std::cout << "\n**************************************\n";
        std::cout << "  游戏结束！清国失去了太多领土...\n";
        std::cout << "  清国仅剩 " << qingProvinces << " 个省份\n";
        std::cout << "**************************************\n";
    } else if (qingProvinces == static_cast<int>(provinces.size())) {
        gameOver = true;
        victory = true;
        std::cout << "\n**************************************\n";
        std::cout << "  胜利！清国收复了所有失地！\n";
        std::cout << "**************************************\n";
    }
}

void Game::run() {
    std::cout << "========================================\n";
    std::cout << "     欢迎来到大清模拟器！\n";
    std::cout << "========================================\n";
    std::cout << "目标: 保卫清国领土，击退列强！\n";
    std::cout << "胜利条件: 收复所有省份\n";
    std::cout << "失败条件: 省份少于8个\n";
    std::cout << "========================================\n\n";
    
    while (!gameOver) {
        turn++;
        displayStatus();
        displayProvinces();
        
        // Collect income at start of turn
        collectIncome();
        
        // Random events
        randomEvent();
        
        bool endTurn = false;
        while (!endTurn && !gameOver) {
            std::cout << "\n╔════════════════════════════════════╗\n";
            std::cout << "║        请选择行动:                 ║\n";
            std::cout << "╠════════════════════════════════════╣\n";
            std::cout << "║ 1. 派遣驻军                        ║\n";
            std::cout << "║ 2. 招募士兵                        ║\n";
            std::cout << "║ 3. 研究科技                        ║\n";
            std::cout << "║ 4. 招募将领                        ║\n";
            std::cout << "║ 5. 外交行动                        ║\n";
            std::cout << "║ 6. 谍报活动                        ║\n";
            std::cout << "║ 7. 建造防御工事                    ║\n";
            std::cout << "║ 8. 推进改革                        ║\n";
            std::cout << "║ 9. 结束回合                        ║\n";
            std::cout << "║ 0. 退出游戏                        ║\n";
            std::cout << "╚════════════════════════════════════╝\n";
            std::cout << "选择: ";
            
            int choice;
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "无效输入！\n";
                continue;
            }
            
            if (choice == 0) {
                std::cout << "退出游戏...\n";
                gameOver = true;
                break;
            } else if (choice == 1) {
                std::cout << "\n请输入省份编号 (0-" << provinces.size() - 1 << "): ";
                int provinceIndex;
                std::cin >> provinceIndex;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "无效输入！\n";
                    continue;
                }
                
                std::cout << "请输入增派士兵数量: ";
                int troops;
                std::cin >> troops;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "无效输入！\n";
                    continue;
                }
                
                stationTroops(provinceIndex, troops);
            } else if (choice == 2) {
                std::cout << "请输入招募数量: ";
                int amount;
                std::cin >> amount;
                recruitTroops(amount);
            } else if (choice == 3) {
                researchTechnology();
            } else if (choice == 4) {
                recruitGeneral();
            } else if (choice == 5) {
                performDiplomacy();
            } else if (choice == 6) {
                conductEspionage();
            } else if (choice == 7) {
                std::cout << "\n请输入省份编号 (0-" << provinces.size() - 1 << "): ";
                int provinceIndex;
                std::cin >> provinceIndex;
                buildFortification(provinceIndex);
            } else if (choice == 8) {
                enactReforms();
            } else if (choice == 9) {
                // End turn
                std::cout << "回合结束...\n";
                endTurn = true;
            } else {
                std::cout << "无效选择！\n";
                continue;
            }
        }
        
        if (!gameOver) {
            // Foreign powers take their turn
            foreignPowersAction();
            
            // Check win/lose conditions
            checkGameOver();
        }
    }
    
    if (gameOver && !victory) {
        displayProvinces();
    }
}

bool Game::isGameOver() const {
    return gameOver;
}

bool Game::isVictory() const {
    return victory;
}
