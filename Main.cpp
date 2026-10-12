#include "Digimon.h"
#include "Database.h"
#include "Evolution.h"
#include <iostream>
#include <fstream>

int main() {

    int gameChoice;
    //game choice is for the big main menus before the game starts.
    //its for new game, load game, and egg choice.
    std::cout << "1 New Game  2 Load Game\n";
    std::cin >> gameChoice;
    //This is a choice you select when program runs.

    std::map<std::string, DigiData> db;
    createDigiDB(db);

    auto silver = createSilverTable();
    //the complier will use auto to figure out the type.
    //instead of writing whats below, it makes it shorter and faster to type out.
    //std::map<std::string, std::vector<EvoRule>> silver = createSilverTable();;
    auto purple = createPurpleTable();

    int choice;

    auto* evoTable = &silver;
    //Evotable is a pointer. auto* is to figure out what the type it points to.
    //&silver is the memory address of silver.
    //This is an address operator.  Im asking it to give me the memory address of Silver.
    Digimon* d = nullptr;
    //points to a digimon but not yet created. Its waiting for a digimon to be made/selected.

    DigiLine line;

    if (gameChoice == 1) {

        std::cout << "1 Silver 2 Purple\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            line.startName = "Choromon";
            evoTable = &silver;
            break;

        case 2:
            line.startName = "Kuramon";
            evoTable = &purple;
            break;

        default:
            std::cout << "Invalid choice, defaulting to Silver.\n";
            line.startName = "Choromon";
            evoTable = &silver;
            break;
        }

        //we will be able to add additional Digimon by using a switch case for choices.
        //When a choice is made, the evoTable will get the memory address of the name.
        //Invalid input will just make it Silver.

        d = new Digimon(line, db);
        //d points to a digimon. The code asks to make a Digimon and store it in d to be used later.
    }
    else {

        std::streambuf* old = std::cout.rdbuf();   // save output buffer
        std::cout.rdbuf(nullptr);                  // silence cout

        line.startName = "Choromon";               // safe placeholder
        //Placeholder is needed due to the constructor needing to be called
        //otherwise program will crash constantly
        d = new Digimon(line, db);                 // constructor runs silently

        std::cout.rdbuf(old);                      // restore output

        d->loadFromFile();                         // now safe output
       
        //Without this section of code, the program will crash or it will display
        //Egg hatched into ? while confirming the save loaded
        //Basically the Constructor kinda screwed me up here.
        //rdbuf a steam buffer, it handles where the output goes. Because I don't want the output.
        //I and silencing it, then restoring it as a new safe output so it doesnt print what I dont
        // want to print, this being the "Egg hatched into ?" line
    }

    while (true) {

        std::cout << "\n1 Train 2 Battle 3 Evolve 4 Show 5 Feed 6 Save\n";
        std::cin >> choice;

        if (choice == 1) d->train();
        else if (choice == 2) d->battle();
        else if (choice == 3) d->evolve(*evoTable, db);
        else if (choice == 4) d->show();
        else if (choice == 5) d->feed();
        else if (choice == 6) {
            d->saveToFile();
            std::exit(0);
            //basic main menu switch case.
        }
    }
}