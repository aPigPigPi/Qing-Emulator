#include "Game.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Game::Game() : turn(0), gameOver(false), victory(false), 
               treasury(1000), reformLevel(0), militaryTech(0), spyNetwork(0),
               gameEnded(false), currentSaveFile("") {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // 扩展列强 - 所有八国联军成员国及其他势力
    foreignPowers.push_back("英国");      // Britain
    foreignPowers.push_back("法国");      // France
    foreignPowers.push_back("俄国");      // Russia
    foreignPowers.push_back("日本");      // Japan
    foreignPowers.push_back("德国");      // Germany
    foreignPowers.push_back("美国");      // USA
    foreignPowers.push_back("意大利");    // Italy
    foreignPowers.push_back("奥匈帝国");  // Austria-Hungary
    foreignPowers.push_back("荷兰");      // Netherlands
    foreignPowers.push_back("葡萄牙");    // Portugal
    
    initProvinces();
    initTechnologies();
    initGenerals();
    initDiplomacy();
}

void Game::initProvinces() {
    // 中国地区（34个省级行政区）
    // 华北地区
    provinces.push_back(std::unique_ptr<Province>(new Province("北京", "清国", 180)));      // Capital
    provinces.push_back(std::unique_ptr<Province>(new Province("天津", "清国", 160)));
    provinces.push_back(std::unique_ptr<Province>(new Province("河北", "清国", 140)));
    provinces.push_back(std::unique_ptr<Province>(new Province("山西", "清国", 90)));
    provinces.push_back(std::unique_ptr<Province>(new Province("内蒙古", "清国", 70)));
    
    // 东北地区
    provinces.push_back(std::unique_ptr<Province>(new Province("辽宁", "清国", 120)));
    provinces.push_back(std::unique_ptr<Province>(new Province("吉林", "清国", 80)));
    provinces.push_back(std::unique_ptr<Province>(new Province("黑龙江", "清国", 70)));
    
    // 华东地区
    provinces.push_back(std::unique_ptr<Province>(new Province("上海", "清国", 250)));      // Very rich
    provinces.push_back(std::unique_ptr<Province>(new Province("江苏", "清国", 200)));
    provinces.push_back(std::unique_ptr<Province>(new Province("浙江", "清国", 190)));
    provinces.push_back(std::unique_ptr<Province>(new Province("安徽", "清国", 100)));
    provinces.push_back(std::unique_ptr<Province>(new Province("福建", "清国", 130)));
    provinces.push_back(std::unique_ptr<Province>(new Province("江西", "清国", 95)));
    provinces.push_back(std::unique_ptr<Province>(new Province("山东", "清国", 150)));
    
    // 中南地区
    provinces.push_back(std::unique_ptr<Province>(new Province("河南", "清国", 110)));
    provinces.push_back(std::unique_ptr<Province>(new Province("湖北", "清国", 120)));
    provinces.push_back(std::unique_ptr<Province>(new Province("湖南", "清国", 110)));
    provinces.push_back(std::unique_ptr<Province>(new Province("广东", "清国", 230)));      // Very rich
    provinces.push_back(std::unique_ptr<Province>(new Province("广西", "清国", 85)));
    provinces.push_back(std::unique_ptr<Province>(new Province("海南", "清国", 60)));
    
    // 西南地区
    provinces.push_back(std::unique_ptr<Province>(new Province("重庆", "清国", 100)));
    provinces.push_back(std::unique_ptr<Province>(new Province("四川", "清国", 140)));
    provinces.push_back(std::unique_ptr<Province>(new Province("贵州", "清国", 70)));
    provinces.push_back(std::unique_ptr<Province>(new Province("云南", "清国", 90)));
    provinces.push_back(std::unique_ptr<Province>(new Province("西藏", "清国", 40)));
    
    // 西北地区
    provinces.push_back(std::unique_ptr<Province>(new Province("陕西", "清国", 100)));
    provinces.push_back(std::unique_ptr<Province>(new Province("甘肃", "清国", 65)));
    provinces.push_back(std::unique_ptr<Province>(new Province("青海", "清国", 45)));
    provinces.push_back(std::unique_ptr<Province>(new Province("宁夏", "清国", 50)));
    provinces.push_back(std::unique_ptr<Province>(new Province("新疆", "清国", 60)));
    
    // 港澳台
    provinces.push_back(std::unique_ptr<Province>(new Province("香港", "英国", 200)));      // British
    provinces.push_back(std::unique_ptr<Province>(new Province("澳门", "葡萄牙", 80)));     // Portuguese
    provinces.push_back(std::unique_ptr<Province>(new Province("台湾", "日本", 150)));      // Japanese
    
    // 日本地区
    provinces.push_back(std::unique_ptr<Province>(new Province("东京", "日本", 220)));
    provinces.push_back(std::unique_ptr<Province>(new Province("大阪", "日本", 180)));
    provinces.push_back(std::unique_ptr<Province>(new Province("北海道", "日本", 100)));
    provinces.push_back(std::unique_ptr<Province>(new Province("九州", "日本", 120)));
    
    // 俄国远东地区
    provinces.push_back(std::unique_ptr<Province>(new Province("海参崴", "俄国", 140)));
    provinces.push_back(std::unique_ptr<Province>(new Province("西伯利亚", "俄国", 90)));
    provinces.push_back(std::unique_ptr<Province>(new Province("蒙古", "俄国", 70)));
    provinces.push_back(std::unique_ptr<Province>(new Province("中亚", "俄国", 80)));
    
    // 英国殖民地
    provinces.push_back(std::unique_ptr<Province>(new Province("缅甸", "英国", 110)));
    provinces.push_back(std::unique_ptr<Province>(new Province("马来亚", "英国", 130)));
    provinces.push_back(std::unique_ptr<Province>(new Province("新加坡", "英国", 160)));
    provinces.push_back(std::unique_ptr<Province>(new Province("印度", "英国", 200)));
    
    // 法国殖民地
    provinces.push_back(std::unique_ptr<Province>(new Province("越南", "法国", 120)));
    provinces.push_back(std::unique_ptr<Province>(new Province("柬埔寨", "法国", 90)));
    provinces.push_back(std::unique_ptr<Province>(new Province("老挝", "法国", 70)));
    
    // 德国殖民地
    provinces.push_back(std::unique_ptr<Province>(new Province("青岛", "德国", 140)));
    provinces.push_back(std::unique_ptr<Province>(new Province("太平洋岛", "德国", 60)));
    
    // 美国势力范围
    provinces.push_back(std::unique_ptr<Province>(new Province("菲律宾", "美国", 130)));
    provinces.push_back(std::unique_ptr<Province>(new Province("关岛", "美国", 80)));
    
    // 荷兰殖民地
    provinces.push_back(std::unique_ptr<Province>(new Province("印尼", "荷兰", 150)));
    
    // 意大利租界
    provinces.push_back(std::unique_ptr<Province>(new Province("天津租界", "意大利", 90)));
    
    // 奥匈帝国势力
    provinces.push_back(std::unique_ptr<Province>(new Province("东欧据点", "奥匈帝国", 100)));
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
    std::cout << std::left << std::setw(5) << "编号" 
              << std::setw(10) << "省份" 
              << std::setw(10) << "控制者" 
              << std::setw(8) << "驻军"
              << std::setw(8) << "收入"
              << std::setw(8) << "防御"
              << std::setw(8) << "稳定" << "\n";
    std::cout << "----------------------------------------\n";
    
    for (size_t i = 0; i < provinces.size(); i++) {
        std::cout << std::left << std::setw(5) << i
                  << std::setw(10) << provinces[i]->getName()
                  << std::setw(10) << provinces[i]->getController()
                  << std::setw(8) << provinces[i]->getTroops()
                  << std::setw(8) << provinces[i]->getIncome()
                  << std::setw(8) << provinces[i]->getFortificationLevel()
                  << std::setw(8) << provinces[i]->getStability() << "\n";
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
    const int EVENT_CHANCE = 15;  // 15% chance for an event per turn
    const int EVENT_TYPES = 5;    // Total number of different event types
    
    int chance = std::rand() % 100;
    
    if (chance < EVENT_CHANCE) {
        int eventType = std::rand() % EVENT_TYPES;
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
            std::cout << "\n--- 派遣驻军 ---\n";
            std::cout << "目标省份: " << provinces[provinceIndex]->getName() << "\n";
            std::cout << "派遣兵力: " << troops << " 人\n";
            std::cout << "需要花费: " << cost << " 银两\n";
            std::cout << "当前国库: " << treasury << " 银两\n";
            
            if (treasury >= cost) {
                provinces[provinceIndex]->addTroops(troops);
                treasury -= cost;
                std::cout << "\n✓ 成功派遣！\n";
                std::cout << "剩余国库: " << treasury << " 银两\n";
                std::cout << provinces[provinceIndex]->getName() 
                          << " 现有驻军: " << provinces[provinceIndex]->getTroops() << " 人\n";
            } else {
                std::cout << "\n✗ 国库不足！还需要 " << (cost - treasury) << " 银两\n";
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
    std::cout << "\n--- 招募士兵 ---\n";
    std::cout << "招募数量: " << amount << " 人\n";
    std::cout << "需要花费: " << cost << " 银两 (每人2银两)\n";
    std::cout << "当前国库: " << treasury << " 银两\n";
    
    if (treasury >= cost) {
        treasury -= cost;
        provinces[0]->addTroops(amount);
        std::cout << "\n✓ 在直隶成功招募 " << amount << " 名士兵！\n";
        std::cout << "剩余国库: " << treasury << " 银两\n";
        std::cout << "直隶驻军: " << provinces[0]->getTroops() << " 人\n";
    } else {
        std::cout << "\n✗ 国库不足！还需要 " << (cost - treasury) << " 银两\n";
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
            std::cout << "【花费：400银两】\n";
        } else if (reformLevel >= 100) {
            std::cout << "改革已完成！\n";
        } else {
            std::cout << "国库不足！需要 400 银两，当前: " << treasury << " 银两\n";
        }
    }
}

void Game::attackProvince() {
    std::cout << "\n=== 进攻敌方省份 ===\n";
    
    // List enemy provinces
    std::vector<int> enemyProvinces;
    for (size_t i = 0; i < provinces.size(); i++) {
        if (provinces[i]->getController() != "清国") {
            enemyProvinces.push_back(i);
            std::cout << i << ". " << provinces[i]->getName() 
                      << " (控制: " << provinces[i]->getController()
                      << ", 驻军: " << provinces[i]->getTroops() << ")\n";
        }
    }
    
    if (enemyProvinces.empty()) {
        std::cout << "没有敌方省份可以进攻！\n";
        return;
    }
    
    std::cout << "\n选择要进攻的省份编号 (-1取消): ";
    int targetIndex;
    std::cin >> targetIndex;
    
    if (targetIndex == -1) return;
    
    if (targetIndex < 0 || targetIndex >= static_cast<int>(provinces.size()) ||
        provinces[targetIndex]->getController() == "清国") {
        std::cout << "无效的目标！\n";
        return;
    }
    
    std::cout << "请输入派遣进攻的兵力: ";
    int attackForce;
    std::cin >> attackForce;
    
    if (attackForce <= 0) {
        std::cout << "兵力必须大于0！\n";
        return;
    }
    
    // Check if we have enough troops (from all our provinces)
    int totalTroops = 0;
    for (const auto& prov : provinces) {
        if (prov->getController() == "清国") {
            totalTroops += prov->getTroops();
        }
    }
    
    if (attackForce > totalTroops) {
        std::cout << "兵力不足！当前总兵力: " << totalTroops << "\n";
        return;
    }
    
    // Calculate combat
    int attackPower = attackForce + militaryTech;
    
    // Add general bonus if available
    for (const auto& general : generals) {
        if (general.isRecruited()) {
            attackPower += general.getCombatPower() / 2;  // Half bonus for attack
            break;  // Only one general per attack
        }
    }
    
    int defense = provinces[targetIndex]->getTroops() + 
                  provinces[targetIndex]->getFortificationLevel() * 20;
    
    std::cout << "\n--- 战斗 ---\n";
    std::cout << "我方攻击力: " << attackPower << " (兵力: " << attackForce 
              << " + 科技: " << militaryTech << ")\n";
    std::cout << "敌方防御力: " << defense << " (驻军: " << provinces[targetIndex]->getTroops()
              << " + 工事: " << provinces[targetIndex]->getFortificationLevel() * 20 << ")\n\n";
    
    if (attackPower > defense) {
        std::cout << "*** 胜利！成功攻占 " << provinces[targetIndex]->getName() << "！***\n";
        provinces[targetIndex]->setController("清国");
        int casualties = defense / 2;
        provinces[targetIndex]->setTroops(attackForce - casualties);
        std::cout << "我军伤亡: " << casualties << " 人\n";
        std::cout << "占领后驻军: " << provinces[targetIndex]->getTroops() << " 人\n";
        
        // Worsen relations with the defeated power
        std::string enemy = provinces[targetIndex]->getController();
        if (diplomacy.find(enemy) != diplomacy.end()) {
            diplomacy[enemy] -= 20;
        }
    } else {
        std::cout << "*** 战败！进攻失败 ***\n";
        int casualties = attackForce / 2;
        std::cout << "我军伤亡: " << casualties << " 人\n";
        provinces[targetIndex]->setTroops(defense - attackPower / 2);
    }
}

void Game::saveGame(const std::string& filename) const {
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "无法创建存档文件！\n";
        return;
    }
    
    // Save game state
    file << turn << "\n";
    file << treasury << "\n";
    file << reformLevel << "\n";
    file << militaryTech << "\n";
    file << spyNetwork << "\n";
    file << gameEnded << "\n";  // Save game ended status
    
    // Save provinces
    file << provinces.size() << "\n";
    for (size_t i = 0; i < provinces.size(); i++) {
        file << provinces[i]->getName() << "\n";
        file << provinces[i]->getController() << "\n";
        file << provinces[i]->getTroops() << "\n";
        file << provinces[i]->getIncome() << "\n";
        file << provinces[i]->getFortificationLevel() << "\n";
        file << provinces[i]->getStability() << "\n";
    }
    
    // Save technologies
    file << technologies.size() << "\n";
    for (size_t i = 0; i < technologies.size(); i++) {
        file << technologies[i].researched << "\n";
    }
    
    // Save generals
    file << generals.size() << "\n";
    for (size_t i = 0; i < generals.size(); i++) {
        file << generals[i].isRecruited() << "\n";
    }
    
    // Save diplomacy
    file << diplomacy.size() << "\n";
    for (std::map<std::string, int>::const_iterator it = diplomacy.begin(); 
         it != diplomacy.end(); ++it) {
        file << it->first << "\n";
        file << it->second << "\n";
    }
    
    file.close();
    std::cout << "游戏已保存到: " << filename << "\n";
}

bool Game::loadGame(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        return false;
    }
    
    // Load game state
    file >> turn;
    file >> treasury;
    file >> reformLevel;
    file >> militaryTech;
    file >> spyNetwork;
    file >> gameEnded;  // Load game ended status
    
    // Load provinces
    size_t provinceCount;
    file >> provinceCount;
    file.ignore();  // Ignore newline
    
    for (size_t i = 0; i < provinceCount && i < provinces.size(); i++) {
        std::string name, controller;
        int troops, income, fortLevel, stability;
        
        std::getline(file, name);
        std::getline(file, controller);
        file >> troops >> income >> fortLevel >> stability;
        file.ignore();
        
        provinces[i]->setController(controller);
        provinces[i]->setTroops(troops);
        provinces[i]->setIncome(income);
        for (int j = 0; j < fortLevel; j++) {
            provinces[i]->upgradeFortification();
        }
        provinces[i]->setStability(stability);
    }
    
    // Load technologies
    size_t techCount;
    file >> techCount;
    for (size_t i = 0; i < techCount && i < technologies.size(); i++) {
        bool researched;
        file >> researched;
        technologies[i].researched = researched;
    }
    
    // Load generals
    size_t genCount;
    file >> genCount;
    for (size_t i = 0; i < genCount && i < generals.size(); i++) {
        bool recruited;
        file >> recruited;
        if (recruited) {
            generals[i].recruit();
        }
    }
    
    // Load diplomacy
    size_t dipCount;
    file >> dipCount;
    file.ignore();
    diplomacy.clear();
    for (size_t i = 0; i < dipCount; i++) {
        std::string power;
        int relation;
        std::getline(file, power);
        file >> relation;
        file.ignore();
        diplomacy[power] = relation;
    }
    
    file.close();
    
    // If game has ended, show report and exit
    if (gameEnded) {
        std::cout << "\n这是一个已结束的存档！\n";
        displayFinalReport();
        return true;
    }
    
    return true;
}

void Game::displayFinalReport() const {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════╗\n";
    std::cout << "║                                            ║\n";
    std::cout << "║         游戏结束 - 最终成果报告           ║\n";
    std::cout << "║                                            ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    std::cout << "║                                            ║\n";
    
    int qingProvinces = getQingProvinceCount();
    int totalProvinces = provinces.size();
    double controlPercent = (qingProvinces * 100.0) / totalProvinces;
    
    std::cout << "║ 游戏回合: " << std::setw(28) << std::left << turn << "║\n";
    std::cout << "║ 控制省份: " << qingProvinces << "/" << totalProvinces 
              << " (" << std::fixed << std::setprecision(1) << controlPercent << "%)";
    for (int i = 0; i < 20; i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "║ 国库余额: " << std::setw(28) << std::left << treasury << "║\n";
    std::cout << "║ 改革进度: " << std::setw(28) << std::left << reformLevel << "║\n";
    std::cout << "║ 军事科技: " << std::setw(28) << std::left << militaryTech << "║\n";
    std::cout << "║                                            ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    std::cout << "║ 省份控制详情:                             ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    
    // Count provinces by controller
    std::map<std::string, int> controlCount;
    for (const auto& prov : provinces) {
        controlCount[prov->getController()]++;
    }
    
    for (const auto& pair : controlCount) {
        std::cout << "║ " << std::setw(12) << std::left << pair.first 
                  << ": " << std::setw(27) << std::left << pair.second + "个省份" << "║\n";
    }
    
    std::cout << "║                                            ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    
    // Evaluation
    if (controlPercent >= 90) {
        std::cout << "║ 评价: 大清中兴，功在千秋！                ║\n";
    } else if (controlPercent >= 70) {
        std::cout << "║ 评价: 成功守土，保住基业                  ║\n";
    } else if (controlPercent >= 50) {
        std::cout << "║ 评价: 勉强维持，前路坎坷                  ║\n";
    } else if (controlPercent >= 30) {
        std::cout << "║ 评价: 江河日下，国势危急                  ║\n";
    } else {
        std::cout << "║ 评价: 大厦将倾，回天乏术                  ║\n";
    }
    
    std::cout << "║                                            ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n\n";
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
    // 移除自动胜负判定，改为提示
    int qingProvinces = getQingProvinceCount();
    
    if (qingProvinces < 8) {
        std::cout << "\n!!! 警告：清国仅剩 " << qingProvinces << " 个省份，形势危急！\n";
    } else if (qingProvinces == static_cast<int>(provinces.size())) {
        std::cout << "\n*** 恭喜：清国已收复所有失地！***\n";
    }
}

void Game::run() {
    std::cout << "========================================\n";
    std::cout << "     欢迎来到大清模拟器！\n";
    std::cout << "========================================\n";
    
    // 让玩家选择存档文件名
    std::cout << "\n请输入存档文件名 (不含扩展名，如: save1): ";
    std::cin >> currentSaveFile;
    currentSaveFile += ".dat";
    
    std::cout << "\n检查存档: " << currentSaveFile << "\n";
    
    // 尝试加载存档
    if (loadGame(currentSaveFile)) {
        if (gameEnded) {
            // 已结束的存档，显示报告后退出
            std::cout << "\n按任意键继续...\n";
            std::cin.ignore();
            std::cin.get();
            return;
        }
        std::cout << "✓ 找到存档！存档已加载，继续游戏...\n";
    } else {
        std::cout << "未找到存档文件，将创建新存档。\n";
        std::cout << "游戏时可随时保存到: " << currentSaveFile << "\n";
    }
    
    std::cout << "\n目标: 尽可能扩大清国领土！\n";
    std::cout << "提示: 您可以随时保存游戏或选择退出并查看最终成果\n";
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
            std::cout << "║ 9. 进攻敌方省份  [新]              ║\n";
            std::cout << "║ 10. 保存游戏                       ║\n";
            std::cout << "║ 11. 结束回合                       ║\n";
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
                std::cout << "确认退出? (1=是, 0=否): ";
                int confirm;
                std::cin >> confirm;
                if (confirm == 1) {
                    std::cout << "正在保存游戏并退出...\n";
                    gameEnded = true;  // Mark game as ended
                    saveGame(currentSaveFile);
                    displayFinalReport();
                    gameOver = true;
                }
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
                attackProvince();
            } else if (choice == 10) {
                saveGame(currentSaveFile);
            } else if (choice == 11) {
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
