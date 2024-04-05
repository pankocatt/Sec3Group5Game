// Dina Makhdoom, Kyle Wager, Rhys Hunt Section 3 

#include <stdio.h>
#include "Map.h"
#include "main.h"
#include "constants.h"

int main(int argc, char* argv[]) {
    MAP* map = initMap();
    // Initialize the map
    if (map == NULL) {
        printf("Exiting due to no map...\n");
        return 1;
    }

    // Initialize all player data
    PLAYER* player = initPlayer();
    if (player == NULL) {
        if (map != NULL) free(map);
        return 1;
    }
    

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

            // Enters new area
            if (enterArea(map, player, lootpool, map->currentMap) == -1)
                break;

            // This is the loop for getting new items and fighting
            int totalFights = 0;
            while (userInput != EXITCODE && totalFights < map->totalFights) {
                // Lets player select a path for a chance at a new item
                userInput = choosePath(map, player, lootpool);
                if (userInput == EXITCODE)
                    break;

                // The fight menu for an encounter
                userInput = fightMenu(player, enemies);
                totalFights++;
            }
            if (enemies != NULL) free(enemies);
            if (lootpool != NULL) free(lootpool);
        }
    } while (userInput != EXITCODE && map->currentMap != WIN);

    // The win
    if (map->currentMap == WIN) {
        printf("%s escapes from the fiery cave...\n", player->playerName);
        Sleep(2000);
        printf("%s returns home.\n", player->playerName);
        Sleep(2000);
        printf("%s takes a well deserved rest...\n", player->playerName);
        Sleep(2000);
        printf("You win!\n");
        printf("Final Stats:\n");
        printf("%s had %d health, %d damage, %d critical hit chance, %d defence, and %d health potions remaining.\n",
        player->playerName, player->health, player->damage, player->critChance, player->defence, player->healthPots);
        Sleep(2000);
        printf("Thank you for playing!\n");
    }

    if (player != NULL) { free(player->playerName); free(player); }
    destroyMap(map);

    return 0;
}