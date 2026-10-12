#include "Digimon.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>


enum StatType {
    ATK = 0,
    DEF = 1,
    INT = 2,
    SPD = 3
};

Digimon::Digimon(DigiLine line, std::map<std::string, DigiData>& database)
    : db(database) {
    //The constructor it bases itself on when the digimon is created.
    //The database information is in Database.cpp

    name = line.startName;

    //std::map<std::string, DigiData>::iterator it = db.find(name);
    auto it = db.find(name);

    if (it != db.end()) {
        stats = it->second.stats;
        stage = it->second.stage;
    }

    std::cout << "Egg hatched into " << name << "!\n";
}

// =====================================================

void Digimon::train() {
    int choice;
    std::cout << "1 ATK 2 DEF 3 INT 4 SPD\n";
    std::cin >> choice;

    int* stat = nullptr;
    std::string statName;

    switch (choice) {
    case 1: stat = &stats.atk; statName = "ATK"; break;
    case 2: stat = &stats.def; statName = "DEF"; break;
    case 3: stat = &stats.intel; statName = "INT"; break;
    case 4: stat = &stats.speed; statName = "SPD"; break;
    default:
        std::cout << "Invalid.\n";
        return;
    }

    int cap = (stage + 1) * STAT_CAP_PER_STAGE;
    //to make training more restrictive so you dont run around with absurd stats.
    //a Const StatCap is added that multiplies depenind on the stage.
    //For example, the max stat you can have for a ROOKIE is 40 and the max for a CHAMPION is 60

    if (*stat >= cap) {
        std::cout << statName << " is already at max for this stage!\n";
        return;
    }

    int gain = rollStatGain();

    int before = *stat;
    int actual = std::min(gain, cap - *stat);
    *stat += actual;

    std::cout << name << " trained " << statName << "!\n";
    std::cout << statName << ": " << before << " -> " << *stat
        << " (+" << actual << ")\n";
    //This is used to randomize the stat game. The random gain then adds to the current stat you have
    //based on the choice.

    training++;
    endTurn();
}

// =====================================================
std::string getRandomEnemy(
    Stage playerStage,
    std::map<std::string, DigiData>& db)
{
    std::vector<std::string> candidates;

    for (std::map<std::string, DigiData>::iterator it = db.begin();
        it != db.end();
        ++it)
    {
        if (it->second.stage == playerStage) {
            candidates.push_back(it->first);
        }
    }

    if (candidates.empty()) {
        return ""; // safety fallback if there is no digimon names for enemies to use.
    }

    std::uniform_int_distribution<> pick(0, candidates.size() - 1);
    return candidates[pick(rng())];
}
//In the Virtual Pet, Digimon are usually facing against Digimon that are of the same stage. (uless there is an arcade like system.)
//To implement the same system. The code accesses the Digimon Database and pulls out any digimon name equal to your digimon stage.
//ex. A Champion Digimon will always fight a Champion digimon.

void Digimon::battle() {
    // reset special usage per battle
    playerSpecialUsed = false;
    enemySpecialUsed = false;

    if (stage < ROOKIE) {
        std::cout << "Too young to battle.\n";
        return;
    }
    //Baby INTRAININGI and INTRAININGII digimon cannot fight. This checks the current stage.

    // =====================================================
    // get random enemy of same stage
    // =====================================================
    std::string enemyName = getRandomEnemy(stage, db);

    if (enemyName == "") {
        std::cout << "No enemies available.\n";
        return;
    }

    DigiData enemyData = db.find(enemyName)->second;

    StatBlock enemy = enemyData.stats;

    // =====================================================
    // SCALING (hybrid system: base + stage scaling + variance)
    // =====================================================

    /*
    INTRAININGI = 0
    INTRAININGII = 1
    ROOKIE = 2
    CHAMPION = 3
    ULTIMATE = 4
    MEGA = 5

    Scale math. Stage+1 *3 
    higher the stage the higher the boost.
    then a random variation tweak of stats*/

    //ex as Player is ROOKIE
    /*
    scale = (2 + 1) * 3 = 9
    random = +1

    enemy ATK = 20 + 9 + 1 = 30
    */
    int scale = (stage + 1) * 3;

    enemy.atk += scale + (rand() % 5 - 2);
    enemy.def += scale + (rand() % 5 - 2);
    enemy.intel += scale + (rand() % 5 - 2);
    enemy.speed += scale + (rand() % 5 - 2);
    //By scaling the enemy, the fights are less predicatable. Giving you incentive to train your digimon.

    enemy.hp = 100;

    // =====================================================
    // LOAD SPECIAL MOVES
    // =====================================================
    std::string playerSpecial = "";
    std::string enemySpecial = "";

    std::map<std::string, DigiData>::iterator playerIt = db.find(name);
    if (playerIt != db.end() && !playerIt->second.moves.empty()) {
        playerSpecial = playerIt->second.moves[0].name;
    }
    //First we find the digimon
    //otherwise it ends if not found.
    //it then checks the database to see if the digimon has a move. if its empty end and dont crash.
    //if its found it will acess the move in a vector list and find the first (and only) move and print it out.

    std::map<std::string, DigiData>::iterator enemyIt = db.find(enemyName);
    if (enemyIt != db.end() && !enemyIt->second.moves.empty()) {
        enemySpecial = enemyIt->second.moves[0].name;
    }

    // =====================================================
    // battle setup
    // =====================================================
    std::cout << "\nA wild " << enemyName << " appears!\n";


    int playerHP = 100;
    int enemyHP = 100;

    bool playerTurn = stats.speed >= enemy.speed;

    // =====================================================
    // BATTLE LOOP
    // =====================================================
    for (int turn = 1; turn <= 6 && playerHP > 0 && enemyHP > 0; turn++) {
        //the battle ends when six turns are reached or someone's hp reaches zero.

        std::cout << "\n--- Turn " << turn << " ---\n";

        // =================================================
        // PLAYER TURN
        // =================================================
        if (playerTurn) {

            int move;
            std::cout << "Choose move:\n";
            std::cout << "1) Attack\n";
            std::cout << "2) " << playerSpecial << "\n";
            std::cin >> move;
            //There is the basic attack and special attack. The special attack can only be used on one turn.

            int playerStat;

            if (stats.intel > stats.atk) {
                playerStat = stats.intel;
            }
            else {
                playerStat = stats.atk;
            }
            //Attack damage is based off atk-def or int-def depending on which is the higest stat.

            int damage = 0;

            if (move == 1) {

                damage = playerStat - enemy.def / 2;
                std::cout << name << " uses Attack!\n";
                //To make it more game like. we will have defense slightly reduced so its not taking the full stat.
                
            }
            else if (move == 2) {

                if (playerSpecialUsed) {
                    std::cout << "Special already used!\n";
                    damage = 0;
                }
                else {
                    std::cout << name << " uses " << playerSpecial << "!\n";

                    damage = (playerStat * 2) - enemy.def;
                    playerSpecialUsed = true;
                    //Specail attracks get a multiply bonus here but can only be used once.
                }
            }
            else {
                std::cout << "Invalid move, turn wasted!\n";
                damage = 0;
            }

            if (damage < 1) damage = 1;

            enemyHP -= damage;

            std::cout << "Enemy takes " << damage << " damage!\n";
        }

        // =================================================
        // ENEMY TURN
        // =================================================
        else {

            int enemyAttackStat = std::max(enemy.atk, enemy.intel);
            int damage = 0;

            bool useSpecial = (!enemySpecialUsed && (rand() % 3 == 0));

            if (useSpecial && enemySpecial != "") {

                std::cout << enemyName << " uses " << enemySpecial << "!\n";

                damage = (enemy.atk * 2) - stats.def;

                enemySpecialUsed = true;
            }
            else {

                std::cout << enemyName << " attacks!\n";

                damage = enemyAttackStat - stats.def / 2;
            }

            if (damage < 1) damage = 1;

            playerHP -= damage;

            std::cout << "Enemy deals " << damage << " damage!\n";
        }

        // toggle turn
        playerTurn = !playerTurn;

        std::cout << name << " HP: " << playerHP
            << " | Enemy HP: " << enemyHP << "\n";
    }

    // =====================================================
    // RESULT
    // =====================================================
    if (playerHP > enemyHP) {
        std::cout << "\nYou Win!\n";
        wins++;
    }
    else if (enemyHP > playerHP) {
        std::cout << "\nYou Lose!\n";
        losses++;
    }
    else {
        std::cout << "\nDraw!\n";
    }

    battles++;
    endTurn();
}

// =====================================================

void Digimon::evolve(std::map<std::string, std::vector<EvoRule>>& evoTable,
    std::map<std::string, DigiData>& db) {

    auto it = evoTable.find(name);
    if (it == evoTable.end()) return;
    //This reads the Evolution table based on the choosen egg/digimon it hatches into.
    //The Evolution.cpp contains the Tables data.

    std::vector<EvoRule> valid;

    for (auto& r : it->second)
    {
        bool statMatch = false;

        switch (r.requiredStat)
        {
        case 0: // ATK
            statMatch = (stats.atk >= stats.def &&
                stats.atk >= stats.intel &&
                stats.atk >= stats.speed);
            break;

        case 1: // DEF
            statMatch = (stats.def >= stats.atk &&
                stats.def >= stats.intel &&
                stats.def >= stats.speed);
            break;

        case 2: // INT
            statMatch = (stats.intel >= stats.atk &&
                stats.intel >= stats.def &&
                stats.intel >= stats.speed);
            break;

        case 3: // SPD
            statMatch = (stats.speed >= stats.atk &&
                stats.speed >= stats.def &&
                stats.speed >= stats.intel);
            break;

        default:
            statMatch = true; // no stat requirement
            break;
        }

        if (statMatch &&
            training >= r.requiredTraining &&
            battles >= r.requiredBattle)
        {
            valid.push_back(r);
        }
    }

    // fallback if no stat matched
    if (valid.empty()) {
        for (auto& r : it->second) {
            if (training >= r.requiredTraining &&
                battles >= r.requiredBattle)
            {
                valid.push_back(r);
            }
        }

        if (valid.empty()) {
            std::cout << "Cannot evolve.\n";
            return;
        }
    }

    std::uniform_int_distribution<> pick(0, valid.size() - 1);
    std::string next = valid[pick(rng())].nextName;
    //We dont want our players to feel that stats are super important.
    //The stats are there to help get a DESIRED digimon if it is trained a certain way (see the stats above)
    //If the stats are a tie, but the requirements are meant, it will still evolve but now at random (depending on what it evolves to)


    auto dbIt = db.find(next);
    if (dbIt == db.end()) return;

    animateText("D I G I E V O L U T I O N", 100);

    name = next;
    stats = dbIt->second.stats;
    stage = dbIt->second.stage;

    std::cout << "Evolved into " << name << "!\n";
}

// =====================================================

void Digimon::feed() {
    hunger = std::min(4, hunger + 1);
    showHunger();
}
//the digimon have a hunger system. fail to pay attention to it. and it will starve and die.
//four is the the "fullest" a digimon can get.
//Hunger is reduced when training and battle happens. if the hunger reaches -3 the digimon will die.

// =====================================================

void Digimon::show() const {
    std::cout << "\n" << name << " (" << stageNames[stage] << ")\n";
    std::cout << "HP " << stats.hp
        << " ATK " << stats.atk
        << " DEF " << stats.def
        << " INT " << stats.intel
        << " SPD " << stats.speed << "\n";

    std::cout << "\n--- Combat Stats ---\n";
    std::cout << "Battles: " << battles
        << " | Wins: " << wins
        << " | Losses: " << losses << "\n";

    std::cout << "\n--- Status ---\n";
    std::cout << "Hunger: " << hunger << " / 4\n";

    //Stat checker. You can check your digimons current stats, battle wins and losses, and hunger.

}

// =====================================================

void Digimon::saveToMFile() {
    std::ofstream out("death_log.txt", std::ios::app);

    out << "R.I.P " << name << "\n";

    out << name << "\n";
    out << stageNames[stage] << "\n";

    out << "Health: " << stats.hp << " "
        << "Attack: " << stats.atk << " "
        << "Defense: " << stats.def << " "
        << "Intelligence: " << stats.intel << " "
        << "Speed: " << stats.speed << "\n";

    out <<"Battles:"<< battles << " "
        <<"Wins: "<< wins << " "
        <<"Losses: "<< losses << " ";
       
    //When a digimon dies, the program will save it to a text file.
}

void Digimon::saveToFile() {
    std::ofstream out("game_save.txt");

    out << name << "\n";
    out << stageNames[stage] << "\n";

    out << "Health: " << stats.hp << " "
        << "Attack: " << stats.atk << " "
        << "Defense: " << stats.def << " "
        << "Intelligence: " << stats.intel << " "
        << "Speed: " << stats.speed << "\n";

    out <<"Training "<< training << " "
        <<"Battles"<< battles << " "
        <<"Wins"<< wins << " "
        <<"Losses "<<losses << " "
        <<"Hunger "<<hunger << "\n";

    return ;
    //when you select the save option, it will save the current digimon to a save file.
}

void Digimon::loadFromFile() {
    std::ifstream in("game_save.txt");

    if (!in.is_open()) {
        std::cout << "No save file found.\n";
        return;
    }

    int tempStage;
    in >> name;
    in >> tempStage;
    stage = static_cast<Stage>(tempStage);

    in >> stats.hp
        >> stats.atk
        >> stats.def
        >> stats.intel
        >> stats.speed;

    in >> training
        >> battles
        >> wins
        >> losses
        >> hunger;

    std::cout << "Save loaded: " << name << "\n";
    //when the program starts and you chose load. it will load the save file.
}

// =====================================================

void Digimon::endTurn() {
    hunger--;
    showHunger();
    checkDeath();
}

void Digimon::showHunger() const {
    if (hunger <= 0) { std::cout << "Starving!\n" << std::endl;; }
    else if (hunger == 4) { std::cout << name << " is full! \n" << std::endl; }
}

void Digimon::checkDeath() {
    if (hunger <= -3 || losses >= 3) {
        animateText(name, 100);
        animateText("has died...", 100);

        saveToMFile();

        std::exit(0);
    }
}