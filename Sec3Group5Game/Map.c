#include "constants.h"
#include <windows.h>
#include "Map.h"

// Create the map
bool initMap() {
	map = malloc(sizeof(MAP));
	if (map == NULL) {
		perror("Couldn't create map...\n");
		return false;
	}
	map->currentMap = 1;
	return true;
}

// Enter game
void mainMenu() {
	printf("_________                            .__           ____________________  ________			\n");
	printf("\\_   ___ \\  ____   ____   __________ |  |   ____   \\______   \\______   \\/  _____/		\n");
	printf("/    \\  \\/ /  _ \\ /    \\ /  ___/  _ \\|  | _/ __ \\   |       _/|     ___/   \\  ___	\n");
	printf("\\     \\___(  <_> )   |  \\\\___ (  <_> )  |_\\  ___/   |    |   \\|    |   \\    \\_\\  \\\n");
	printf(" \\______  /\\____/|___|  /____  >____/|____/\\___  >  |____|_  /|____|    \\______  /		\n");
	printf("        \\/            \\/     \\/                \\/          \\/                  \\/		\n");
	printf("\n\n");
	printf("1. New Game\n");
	//printf("2. Load Game\n");
	printf("Enter '%d' at any point to exit/return to main menu.\n", EXITCODE);
}

// Gets user int input
int getIntInput(int min, int max) {
	printf("Please select one of the options.\n");
	int input;
	// Loops until valid input is entered
	while ((scanf("%d", &input) != 1 || max < input || input < min ) && input != EXITCODE) {
		printf("Please select one of the options.\n");
		char removeNewline;
		scanf("%c", &removeNewline);
	}
	return input;
}

// Used when you first enter a new area
int enterArea(PLAYER* player, LOOTPOOL* lootpool, short areaNum) {
	// Early exit if map is already selected or player wants to leave
	if (areaNum == map->previousMap || areaNum == EXITCODE)
		return;

	switch (areaNum) {
	// This is the starting case, allows the player to get into the game
	case 1:
		printf("\n\n\n\n\nThe weary adventurer starts on their journey...\n");
		Sleep(2000);
		printf("Their name is: ");
		char name[NAMELENGTH];
		fgets(name, NAMELENGTH, stdin); // Removes the newline
		fgets(name, NAMELENGTH, stdin); // Actually gets the name
		name[strlen(name) - 1] = '\0';

		// Return if name is 0
		if (strncmp(name, "0\0", NAMELENGTH) == 0)
			return EXITCODE;

		setName(player, name);
		printf("%s happens upon a jungle...\n", player->playerName);
		Sleep(2000);
		printf("%s stumbles upon a chest! Inside is a sword!\n", player->playerName);

		// Rolls a random sword
		ITEM item = returnItem(lootpool);
		while (item.lootType != SWORD_TYPE) { item = returnItem(lootpool); }

		// Shows off the sword weapon
		SWORD sword = item.loot.sword;
		printf("It has %d damage", sword.dmg);

		break;

	case 2:
		printf("%s enters a strange and long forgotten ancient dungeon...\n", player->playerName);
		Sleep(2000);
		printf("The dungeon shows its age through the cracks and crumbling walls...\n");
		Sleep(2000);
		break;

	case 3:
		printf("%s starts to feel warmer...\n", player->playerName);
		Sleep(2000);
		printf("%s walks into a fiery cave of lava!\n", player->playerName);
		Sleep(2000);
		break;
	default:
		perror("Couldn't load area...\n");
		return -1;
	}

	// Sets this as the previous map so it only says text once
	map->previousMap = areaNum;
	return 1;
}

// Choose left or right path, adds interactivity but changes nothing at the moment
short choosePath(PLAYER* player, LOOTPOOL* lootpool) {
	printf("%s comes to a fork in the path...\n", player->playerName);
	printf("Which direction do they choose to go?\n");
	printf("1. Left\n");
	printf("2. Right\n");
	short input = getIntInput(1, 2);
	if (input == EXITCODE)
		return EXITCODE;

	short pathWithItem = rand() % 100 + 1;

	// Left path
	if (input == 1) {
		printf("%s walks down the left path...\n", player->playerName);
	}

	// Right path
	else {
		printf("%s walks down the right path...\n", player->playerName);
	}

	// % chance of finding an item
	if (pathWithItem > 50) {
		printf("You found an item!\n");
		ITEM item = returnItem(lootpool);
		// Logic for printing out item information
		switch (item.lootType) {
		case SWORD_TYPE:
			printf("It's a sword with %d damage.\n", item.loot.sword.dmg);
			break;
		case ARMOUR_TYPE:
			printf("It's some armour with %d defense.\n", item.loot.armour.def);
			break;
		case HEALTHPOT_TYPE:
			printf("It's a healthpot that heals %d hp.\n", item.loot.healthpot.health);
			break;
		default:
			item.lootType = SWORD_TYPE;
			item.loot.sword.dmg = 5 * map->currentMap;
			printf("It's a sword with %d damage.\n", item.loot.sword.dmg);
		}

		// Accepting the item
		printf("Do you accept the item?\n");
		printf("1) Yes\n2) No\n");
		input = getIntInput(1, 2);
		
		switch (input) {
		// Early exit
		case EXITCODE:
			return EXITCODE;
			break;
		// Player chooses to keep item
		case 1:
			printf("You received the item!\n");
			switch (item.lootType) {
			case SWORD_TYPE:
				equipWeapon(item.loot.sword.dmg, player);
				break;
			case ARMOUR_TYPE:
				equipArmor(item.loot.armour.def, player);
				break;
			case HEALTHPOT_TYPE:
				addHealthPot(item.loot.healthpot.health, player);
				break;
			default:
				break;
			}
		// Player refuses item
		case 2:
			printf("You put the item down.\n");
			break;
		default:
			printf("Something went wrong...\n");
			break;
		}
	}
}

short fightMenu(PLAYER* player, ENEMY* enemies) {
	printf("You've encountered an enemy!\n");
	short enemyNumber = rand() % 5;
	ENEMY* enemy = malloc(sizeof(ENEMY));
	if (enemy == NULL)
		return ERRORS;
	*enemy = enemies[enemyNumber];

	// Main loop for fighting
	do {
		// Print out menu options
		printf("The %s has %d health.\n", enemy->enemyName, enemy->health);
		printf("1) Attack\n");
		printf("2) Defend\n");
		printf("3) Heal\n");

		short userinput = getIntInput(1, 3);

		// Determines players option
		switch (userinput) {
		case EXITCODE:
			if (enemy != NULL) free(enemy);
			return EXITCODE;
			break;
		case 1:
			enemyTakeDmg(player->damage, enemy);
			break;
		}
	} while (enemy->health > 0 && player->health > 0);

	if (player->health <= 0) {
		printf("%s has perished to a %s...\n", player->playerName, enemy->enemyName);
		return EXITCODE;
	}

	if (enemy != NULL) free(enemy);
	return 1;
}

// Free Map Memory
void destroyMap() {
	if (map != NULL) free(map);
}

