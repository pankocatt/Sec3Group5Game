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
	PLAYER* player = { 0 };
	LOOTPOOL* lootpool = { 0 };

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
			if (enterArea(player, lootpool, map->currentMap) == EXITCODE)
				break;

			// Chooses encounter
		}
		

	} while (userInput != EXITCODE);

	destroyMap(map);

	return 0;
}