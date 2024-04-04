// Dina Makhdoom, Kyle Wager, Rhys Hunt Section 3 

#include <stdio.h>
#include "Map.h"
#include "main.h"
#include "constants.h"

int main(int argc, char* argv[]) {
    // Initialize the map
    if (!initMap()) {
        printf("Exiting due to no map...\n");
        return 1;
    }
    PLAYER* player = malloc(sizeof(PLAYER));
    if (player == NULL) {
        if (map != NULL) free(map);
        return 1;
    }
    LOOTPOOL* lootpool = setUpLootPool(argv);

    int userInput;
    // Main program loop
    do {
        mainMenu();
        userInput = getIntInput(1, 1); // Have user enter main menu option

        // Choose what to do based on user input
        if (userInput == 2)
            printf("File loading not added yet.\n");

        while (userInput != EXITCODE) {
            // Enters next area
            enterArea(player, lootpool, map->currentMap);
            ENEMYLIST* enemies = readEnemyFromFile(argv[map->currentMap]);

            // This is the loop for getting new items and 
            while (userInput != EXITCODE) {
                // Lets player select a path for a chance at a new item
                userInput = choosePath(player, lootpool);
                if (userInput == EXITCODE)
                    break;

                // The fight menu for an encounter
                userInput = fightMenu(player, enemies);
            }
            if (enemies != NULL) free(enemies);
        }
    } while (userInput != EXITCODE);

    if (player != NULL) free(player);
    destroyMap();

    return 0;
}