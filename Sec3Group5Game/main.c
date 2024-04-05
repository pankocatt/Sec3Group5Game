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

    // Initialize all player data
    PLAYER* player = malloc(sizeof(PLAYER));
    if (player == NULL) {
        if (map != NULL) free(map);
        return 1;
    }
    initPlayer(player);

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
            ENEMYLIST* enemies = readEnemyFromFile(argv[map->currentMap]);
            LOOTPOOL* lootpool = setUpLootPool(argv[map->currentMap + 3]);
            enterArea(player, lootpool, map->currentMap);

            // This is the loop for getting new items and fighting
            int totalFights = 0;
            while (userInput != EXITCODE && totalFights < 5) {
                // Lets player select a path for a chance at a new item
                userInput = choosePath(player, lootpool);
                if (userInput == EXITCODE)
                    break;

                // The fight menu for an encounter
                userInput = fightMenu(player, enemies);
                totalFights++;
            }
            if (enemies != NULL) free(enemies);
            if (lootpool != NULL) free(lootpool);
        }
    } while (userInput != EXITCODE);

    if (player != NULL) free(player);
    destroyMap();

    return 0;
}