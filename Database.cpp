#include "Database.h"

std::string stageNames[] = {
    "In-Training I", "In-Training II", "Rookie",
    "Champion", "Ultimate", "Mega"
    //extern is using this in the Database.h file.
};

void createDigiDB(std::map<std::string, DigiData>& db) {
    //This database is organized by
    //Name, hp, atk,def,int,sped,Stage, and special move
    //INTRAININGI and INTAININGII cannot battle, so they do not need a special move.

    db["Choromon"] = { {100,1,1,1,1}, INTRAININGI, {} };
    db["Kapurimon"] = { {100,5,5,5,5}, INTRAININGII, {} };

    db["Hagurumon"] = { {100,12,26,17,17}, ROOKIE, { {"Cog Crusher"} } };
    db["ToyAgumon"] = { {100,15,27,13,17}, ROOKIE, { {"Plastic Blaze"} } };
    db["Kokuwamon"] = { {100,24,20,25,20}, ROOKIE, { {"Mini Scissor Claw"} } };

    db["Tankmon"] = { {100,30,39,28,21}, CHAMPION, { {"Hyper Cannon"} } };
    db["Clockmon"] = { {100,17,26,44,24}, CHAMPION, { {"Chrono Breaker"} } };
    db["Mekanorimon"] = { {100,31,43,27,14}, CHAMPION, { {"Twinkle Beam"} } };
    db["Guardromon"] = { {100,27,37,31,20}, CHAMPION, { {"Destruction Grenade"} } };
    db["Blimpmon"] = { {100,17,29,27,21}, CHAMPION, { {"Zeppelin Explosion"} } };

    db["Tankdramon"] = { {100,27,28,13,33}, ULTIMATE, {{"Striver Cannon"}} };
    db["DeathMeramon"] = { {100,30,25,25,31}, ULTIMATE, {{"Heavy Metal Fire"}} };
    db["Andromon"] = { {100,28,26,42,28}, ULTIMATE, {{"Spiral Sword"}} };
    db["Locomon"] = { {100,24,31,24,23}, ULTIMATE, {{"Wheel Grinder"}} };
    db["MasterBlimpmon"] = { {100,20,27,24,38}, ULTIMATE, {{"Daredevil Break"}} };

    db["Darkdramon"] = { {100,44,34,45,31}, MEGA, {{"Dark Roar"}} };
    db["Boltmon"] = { {100,37,40,30,35}, MEGA, {{"Tomahawk Stinger"}} };
    db["HiAndromon"] = { {100,32,45,43,36}, MEGA, {{"Atomic Ray"}} };
    db["GroundLocomon"] = { {100,37,46,33,37}, MEGA, {{"Destruction Crush"}} };
    db["Gundramon"] = { {100,50,42,30,27}, MEGA, {{"Gewalt Schwärmer"}} };

    //purple evolution table
    db["Kuramon"] = { {100,1,1,1,1}, INTRAININGI, {} };
    db["Tsumemon"] = { {100,7,5,5,5}, INTRAININGII, {} };
    db["Pagumon"] = { {100,5,7,5,5}, INTRAININGII, {} };

    db["Keramon"] = { {100,33,14,15,24}, ROOKIE, {{"Crazy Giggle"}}};
    db["Gazimon"] = { {100,24,22,14,27}, ROOKIE, {{"Electric Stun Blast"}}};
    db["Impmon"] = { {100,12,11,35,24}, ROOKIE, {{"Summon"}}};

    db["Kurisarimon"] = { {100,45,17,15,27}, CHAMPION, {{"Data Crusher"}}};
    db["Shademon"] = { {100,10,20,45,33}, CHAMPION, {{"Free Death Fall"}}};
    db["Dobermon"] = { {100,42,23,27,39}, CHAMPION, {{"Grau Lärm"}}};
    db["Sangloupmon"] = { {100,35,19,25,30}, CHAMPION, {{"Sticker Blade"}}};
    db["Devimon"] = { {100,27,20,42,24}, CHAMPION, {{"Death Claw"}}};

    db["Infermon"] = { {100,50,25,15,35}, ULTIMATE, {{"Spider Shooter"}}};
    db["Orochimon"] = { {100,35,30,30,25}, ULTIMATE, {{"Ame no Murakumo"}}};
    db["Vamdememon"] = { {100,37,20,46,27}, ULTIMATE, {{"Night Raid"}}};
    db["Astamon"] = { {100,40,30,27,28}, ULTIMATE, {{"Mad Dog Fire"}} };
    db["SkullSatamon"] = { {100,23,20,50,30}, ULTIMATE, {{"Nail Bone"}}};

    db["Diablomon"] = { {100,60,30,30,37}, MEGA, {{"Catastrophe Cannon"}}};
    db["Minervamon"] = { {100,40,40,29,41}, MEGA, {{"Strike Roll"}}};
    db["GrandDracumon"] = { {100,30,47,30,32}, MEGA, {{"Eye Of The Gorgon"}}};
    db["VenomVamdemon"] = { {100,40,30,41,35}, MEGA, {{"Venom Infusion"}}};
    db["Beelzebumon"] = { {100,45,32,26,45}, MEGA, {{"Double Impact"}} };

    db["Mervamon"] = { {100,50,50,50,55}, MEGA, {{"Love Poison"}}};
    db["BeelzebumonBM"] = { {100,55,42,44,55}, MEGA, {{"Death Slinger"}}};
    
}