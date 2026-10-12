#pragma once
#include <string>
#include <vector>
#include <map>

struct EvoRule {
    std::string nextName;
    int requiredStat;
    int requiredTraining;
    int requiredBattle;
    //This struct stores the information needed to digievolve.
    //it stores the stat,training and battle requirments.

    //EvoRule("Tankmon",0,0,5)
    //Nextname is what the digimon evolves to, the first number is for stat, the second is training, the thrid is battles.
    //Tankmon needs highest atk, no training, and 5 battles to evolve


    EvoRule(std::string n, int rs, int rt, int rb)
        : nextName(n), requiredStat(rs), requiredTraining(rt), requiredBattle(rb) {
    }
};

std::map<std::string, std::vector<EvoRule>> createSilverTable();
std::map<std::string, std::vector<EvoRule>> createPurpleTable();

//These tables store how Digimon evolve. (See evolution cpp) used for organization because
//each digimon evolves differently.