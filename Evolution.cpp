#include "Evolution.h"

std::map<std::string, std::vector<EvoRule>> createSilverTable() {
    return {
        {"Choromon", 
        {EvoRule("Kapurimon",0,0,0)}},
        
        {"Kapurimon", {
            EvoRule("Hagurumon",1,5,0),
            EvoRule("ToyAgumon",0,5,0),
            EvoRule("Kokuwamon",2,5,0)
        }},

         {"Hagurumon", {
            EvoRule("Tankmon",0,0,5),
            EvoRule("Clockmon",1,0,5),
            EvoRule("Blimpmon",3,0,5)
        }},
         {"Kokuwamon", {
            EvoRule("Clockmon",1,0,5),
            EvoRule("Mekanorimon",0,0,5),
            EvoRule("Guardromon",1,0,5)
        }},
         {"ToyAgumon", {
            EvoRule("Tankmon",0,0,5),
            EvoRule("Clockmon",1,0,5),
            EvoRule("Blimpmon",3,0,5)
        }},


        {"Tankmon", {
            EvoRule("Tankdramon",1,0,5),
            EvoRule("DeathMeramon",0,0,5)
        }},
         {"Clockmon", {
            EvoRule("DeathMeramon",0,0,5),
            EvoRule("Andromon",2,0,5)
        }},
         {"Mekanorimon", {
            EvoRule("DeathMeramon",0,0,5),
            EvoRule("Andromon",2,0,5),
            EvoRule("Locomon",1,0,5)
        }},
           {"Guardromon", {
            EvoRule("Andromon",2,0,5),
            EvoRule("Locomon",1,0,5)
        }},
        {"Blimpmon", {
            EvoRule("Locomon",1,0,5),
            EvoRule("MasterBlimpmon",3,0,5)
        }},

         {"Tankdramon", {
            EvoRule("Darkdramon",2,0,5),
            EvoRule("Gundramon",0,0,5)
        }},
        {"DeathMeramon", {
            EvoRule("Darkdramon",2,0,5),
            EvoRule("Boltmon",0,0,5)
        }},
        {"Andromon", {
            EvoRule("HiAndromon",2,0,5),
            EvoRule("Boltmon",0,0,5)
        }},
        {"Locomon", {
            EvoRule("HiAndromon",2,0,5),
            EvoRule("GroundLocomon",1,0,5)
        }},
        {"MasterBlimpmon", {
            EvoRule("Gundramon",0,0,5),
            EvoRule("GroundLocomon",1,0,5)
        }},


    };
}

//stat/training/battle
std::map<std::string, std::vector<EvoRule>> createPurpleTable() {
    return {
         {"Kuramon",
        {EvoRule("Tsumemon",0,0,0),
        {EvoRule("Pagumon",1,0,0)}
        }},
        {"Tsumemon", {
            EvoRule("Keramon",0,5,0),
            EvoRule("Gazimon",3,5,0)
        }},
        {"Pagumon", {
            EvoRule("Impmon",2,5,0),
            EvoRule("Gazimon",3,5,0)
        }},

        {"Keramon", {
            EvoRule("Kurisarimon",0,0,5),
            EvoRule("Shademon",2,0,5)
        }},
        {"Gazimon", {
            EvoRule("Shademon",2,0,5),
            EvoRule("Dobermon",3,0,5),
            EvoRule("Sangloupmon",0,0,5)
        }},
        {"Impmon", {
            EvoRule("Sangloupmon",0,0,5),
            EvoRule("Devimon",2,0,5)
        }},

        {"Kurisarimon", {
            EvoRule("Infermon",0,0,5),
            EvoRule("Orochimon",1,0,5)
        }},
        {"Shademon", {
            EvoRule("Vamedemon",2,0,5),
            EvoRule("Orochimon",1,0,5)
        }},
        {"Dobermon", {
            EvoRule("Vamedemon",2,0,5),
            EvoRule("Orochimon",1,0,5),
            EvoRule("Astamon",0,0,5)
        }},
        {"Sangloupmon", {
            EvoRule("Vamdememon",2,0,5),
            EvoRule("Astamon",0,0,5)
        }},
        {"Devimon", {
            EvoRule("SkullSatamon",2,0,5),
            EvoRule("Astamon",0,0,5)
        }},

        {"Infermon", {
            EvoRule("Minervamon",0,0,5),
            EvoRule("Diablomon",2,0,5)
        }},
        {"Orochimon", {
            EvoRule("Minervamon",0,0,5),
            EvoRule("GrandDracumon",1,0,5)
        }},
        {"Vamdememon", {
            EvoRule("VenomVamdemon",2,0,5),
            EvoRule("GrandDracumon",1,0,5)
        }},
        {"Astamon", {
            EvoRule("VenomVamdemon",2,0,5),
            EvoRule("Beelzebumon",0,0,5)
        }},
        {"SkullSatamon", {
            EvoRule("Diablomon",2,0,5),
            EvoRule("Beelzebumon",0,0,5)
        }},

        {"Minervamon", {
            EvoRule("Mervamon",0,0,5)
        }},
        {"Beelzebumon", {
            EvoRule("BeelzebumonBM",0,0,5)
        }},
    
    };
}