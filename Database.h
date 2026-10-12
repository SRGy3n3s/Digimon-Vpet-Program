#pragma once
#include <string>
#include <vector>
#include <map>

enum Stage {
    INTRAININGI,
    INTRAININGII,
    ROOKIE,
    CHAMPION,
    ULTIMATE,
    MEGA
};
//use enum to define growth levels
//Enum is a group of constants.

extern std::string stageNames[];
//extern in summary, tells the program what you need isnt here. it is elsewhere, go find it.
//if we did not have it every .cpp file that has it would attempt to make its own copy
//resulting in error due to multiple definitions.

struct StatBlock {
    int hp{};
    int atk{};
    int def{};
    int intel{};
    int speed{};
};
//strut used to group variables under a single name.
//this strut holds the Digimon stats.

struct Move {
    std::string name;
};
//Each digimon has special attacks. This is a name place holder strut

struct DigiData {
    StatBlock stats;
    Stage stage;
    std::vector<Move> moves;
};
//this struct is the complete progile, containing statblock,stage,and moves

struct DigiLine {
    std::string startName;
};


void createDigiDB(std::map<std::string, DigiData>& db);
//this is a map. A data container that stores the information in key value pairs.
//for example
//db["Hagurumon"] = { {100,12,26,17,17}, ROOKIE, { {"Cog Crusher"} }
//it accesses the digimon database.cpp to read digimon name, stats, stage, and special move.