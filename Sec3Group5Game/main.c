// Dina Makhdoom, Kyle Wager, Rhys Hunt Section 3 

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "main.h"
#include "constants.h"

int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    // Check that there are enough command line arguments
    if (argc < 6) {
        perror("Not enough arguments...\n");
        return 1;
    }

    MAP* map = initMap();
    // Initialize the map
    if (map == NULL) {
        printf("Exiting due to no map...\n");
        return 1;
    }

    // Initialize all player data
    PLAYER* player = initPlayer();
    if (player == NULL) {
        free(map);
        return 1;
    }

    int userInput;
    int returnedValues = GOODCODE;
    // Main program loop
    do {
        mainMenu();
        userInput = getIntInput(1, 1); // Have user enter main menu option

        while (userInput != EXITCODE && returnedValues != EXITCODE && returnedValues != WIN && map->currentMap != WIN) {
            // Enters next area
            ENEMYLIST* enemies = readEnemyFromFile(argv[map->currentMap]);
            LOOTPOOL* lootpool = readLootPoolFromFile(argv[map->currentMap + 3]);
            if (enemies == NULL || lootpool == NULL) {
                perror("Couldn't correctly read files...\n");
                free(enemies);
                free(lootpool);
                break;
            }

            // Enters new area
            returnedValues = enterArea(map, player, lootpool);
            if (returnedValues == EXITCODE || returnedValues == ERRORCODE) {
                free(enemies);
                free(lootpool);
                break;
            }

                // This is the loop for getting new items and fighting
            int totalFights = 0;
            while (returnedValues != EXITCODE && totalFights < map->totalFights) {
                // Lets player select a path for a chance at a new item
                returnedValues = choosePath(map, player, lootpool);
                if (returnedValues == EXITCODE)
                    break;

                // The fight menu for an encounter
                returnedValues = fightMenu(map, player, enemies);
                totalFights++;
            }
            

            // Lets player move to next map if they are still alive
            map->currentMap++;

            // Beat game
            if (map->currentMap == 4)
                returnedValues = enterArea(map, player, lootpool);

            free(enemies);
            free(lootpool);
        }
    } while (userInput != EXITCODE && returnedValues != EXITCODE && returnedValues != ERRORCODE && returnedValues != WIN && map->currentMap != WIN);

    // The win

    if (map->currentMap == WIN) {
        printf("%s escapes from the fiery cave...\n", player->playerName);
        SLEEP;
        printf("%s returns home.\n", player->playerName);
        Sleep(2000);
        printf("%s takes a well deserved rest...\n", player->playerName);
        SLEEP;
        printf("You win!\n");
        printf("Final Stats:\n");
        printf("%s had %d health, %d damage, %d critical hit chance, %d defence, and %d health potions remaining.\n",
        player->playerName, player->health, player->damage, player->critChance, player->defence, player->healthPots);
        SLEEP;
        
    }

    printf("Thank you for playing!\n");

    free(player->playerName);
    free(player);
    destroyMap(map);

    return 0;
}