#pragma once
#include "Database.h"
#include "Evolution.h"
#include <map>

class Digimon {
private:
    std::string name;
    Stage stage;
    StatBlock stats;

    int training = 0;
    int battles = 0;
    int losses = 0;
    int hunger = 4;
    int wins = 0;

    std::map<std::string, DigiData>& db;

    bool playerSpecialUsed = false;
    bool enemySpecialUsed = false;
    //track the special move usage.

public:
    Digimon(DigiLine line, std::map<std::string, DigiData>& db);
    //reference for database.

    void train();
    void battle();
    void evolve(std::map<std::string, std::vector<EvoRule>>& evoTable,
        std::map<std::string, DigiData>& db);
    //reference for evolutions.

    void feed();
    void show() const;
    void saveToMFile();
    void saveToFile();
    void loadFromFile();



private:
    void endTurn();
    void showHunger() const;
    void checkDeath();
};
//Digimon character sheet.