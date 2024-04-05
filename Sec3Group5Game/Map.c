#include "constants.h"
#include <windows.h>
#include "Map.h"

// Create the map
MAP* initMap() {
	MAP* map = malloc(sizeof(MAP));
	if (map == NULL) {
		perror("Couldn't create map...\n");
		return NULL;
	}
	map->currentMap = 1;
	map->previousMap = 0;
	map->totalFights = 5;

	return map;
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
	printf("1) New Game\n");
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
int enterArea(MAP* map, PLAYER* player, LOOTPOOL* lootpool) {
	printf("\n\n\n\n\n");
	// Early exit if map is already selected or player wants to leave
	if (map->currentMap == map->previousMap || map->currentMap == EXITCODE)
		return;

	switch (map->currentMap) {
	// This is the starting case, allows the player to get into the game
	case 1:
		printf("The weary adventurer starts on their journey...\n");
		Sleep(2000);
		printf("Their name is: ");
		char name[NAMELENGTH];
		fgets(name, NAMELENGTH, stdin); // Removes the newline
		fgets(name, NAMELENGTH, stdin); // Actually gets the name

		// Return if name is 0
		if (strncmp(name, "0\n", NAMELENGTH) == 0)
			return EXITCODE;

		// Sets up the player name
		setName(name, player);
		player->playerName[strlen(player->playerName) - 1] = '\0';

		// Begin journey
		printf("%s happens upon a jungle...\n", player->playerName);
		Sleep(2000);

		// Rolls a random sword
		ITEM item = returnItem(lootpool);
		while (item.lootType != SWORD_TYPE) item = returnItem(lootpool);
		printf("%s stumbles upon a chest! Inside is a %s!\n", player->playerName, item.loot.sword.name);
		Sleep(2000);

		// Shows off the weapon and equips it
		printf("It has %d damage and %d critical hit chance!\n", item.loot.sword.dmg, item.loot.sword.crit);
		equipWeapon(item.loot.sword, player);
		Sleep(2000);

		break;

		// Entering next area
	case 2:
		printf("%s enters a strange and long forgotten ancient dungeon...\n", player->playerName);
		Sleep(2000);
		printf("The dungeon shows its age through the cracks and crumbling walls...\n");
		Sleep(2000);
		break;

		// Entering final area
	case 3:
		printf("%s starts to feel warmer...\n", player->playerName);
		Sleep(2000);
		printf("%s walks into a fiery cave of lava!\n", player->playerName);
		Sleep(2000);
		break;
		
		// Winning the game
	case 4:
		map->currentMap == WIN;
		return -1;
	default:
		perror("Couldn't load area...\n");
		return -1;
	}

	// Sets this as the previous map so it only says text once
	map->previousMap = map->currentMap;
	map->currentMap++;
	return 1;
}

// Choose left or right path, adds interactivity. Direction doesn't matter since its based on an arbitrary roll.
short choosePath(MAP* map, PLAYER* player, LOOTPOOL* lootpool) {
	printf("\n\n\n\n\n");
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
	if (pathWithItem <= 50) {
		printf("You found an item!\n");
		ITEM item = returnItem(lootpool);
		// Logic for printing out item information
		switch (item.lootType) {
		case SWORD_TYPE:
			printf("It's a %s with %d damage and +%d critical hit chance!\n", item.loot.sword.name, item.loot.sword.dmg, item.loot.sword.crit);
			break;
		case ARMOUR_TYPE:
			printf("It's a %s with %d defense!\n", item.loot.armour.name, item.loot.armour.def);
			break;
		case HEALTHPOT_TYPE:
			printf("It's a health potion that heals %d hp!\n", HEALTHPOTHEALING);
			break;
		default:
			item.lootType = SWORD_TYPE;
			item.loot.sword.dmg = 5 * map->currentMap;
			item.loot.sword.crit = 10;
			printf("It's a sword with %d damage and +%d critical hit chance.\n", item.loot.sword.dmg, item.loot.sword.crit);
		}

		// Accepting the item
		printf("Do you accept the item?\n");
		printf("1) Yes\n");
		printf("2) No\n");
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
				equipWeapon(item.loot.sword, player);
				printf("%s's damage increased by %d to %d!\n", player->playerName, item.loot.sword.dmg, player->damage);
				printf("%s's critical hit chance increased by %d to %d!\n", player->playerName, item.loot.sword.crit, player->critChance);
				break;
			case ARMOUR_TYPE:
				equipArmor(item.loot.armour, player);
				printf("%s's armour increased by %d to %d!\n", player->playerName, item.loot.armour.def, player->defence);
				break;
			case HEALTHPOT_TYPE:
				addHealthPot(player);
				printf("%s gained a health potion!\n", player->playerName);
				break;
			default:
				printf("The item randomly burst into a billion pieces?!\n");
				break;
			}
			break;
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
	printf("\n\n\n\n\n");
	printf("You've encountered an enemy!\n");
	ENEMY* enemy = malloc(sizeof(ENEMY));
	if (enemy == NULL)
		return ERRORS;
	*enemy = enemies[rand() % TOTALENEMIES];

	// Main loop for fighting
	short enemyOption = 0;
	short userinput;
	do {

		////////////////////////////////////////////////////////////////////////////////////
		// Determines players option
		short userDidSomethingProductive;
		do {
			printf("\n\n\n\n\n");
			// Print out menu options
			printf("The %s has %d health.\n", enemy->enemyName, enemy->health);
			printf("1) Attack\n");
			printf("2) Defend\n");
			printf("3) Heal\n");
			printf("4) Player stats\n");

			userinput = getIntInput(1, 4);

			userDidSomethingProductive = 0;
			switch (userinput) {
				// User wants to leave
			case EXITCODE:
				if (enemy != NULL) free(enemy);
				return EXITCODE;
				break;

				// Attacking
			case 1: { // Brackets for making MSVC stop complaining
				// Checks if the enemy is defending
				short keepOdd = player->damage % 2;
				if (enemyOption == 2)
					player->damage >>= 1;

				// Attack the enemt
				printf("You attack for %d damage\n", player->damage);
				enemyTakeDmg(playerDealDmg(player), enemy);

				// Reset player damage
				if (enemyOption == 2) {
					player->damage <<= 1;
					player->damage += keepOdd;
				}
				break;
			}

				  // Using health potion
			case 3:
				if (useHealthPot(player) == 1)
					printf("%s recovered %d health and now has %d health!\n", player->playerName, HEALTHPOTHEALING, player->health);
				else {
					printf("%s has no health pots to use...\n", player->playerName);
					userDidSomethingProductive = -1;
				}
				break;

				// Player stats
			case 4:
				printf("%s has %d health, %d damage, %d critical hit chance, %d defence, and %d health potions remaining.\n", 
				player->playerName, player->health, player->damage, player->critChance, player->defence, player->healthPots);
				userDidSomethingProductive = -1;
				break;

				// User defends, also default case
			case 2:
			default:
				printf("%s increases their defense!\n", player->playerName);
				userinput = 2;
				player->defence <<= 1;
				break;
			}
		} while (userDidSomethingProductive == -1);

		// Exit loop if enemy died
		if (enemy->health <= 0)
			break;

		Sleep(2000);
		////////////////////////////////////////////////////////////////////////////////////
		// Determines enemies option

		enemyOption = (rand() % 2) + 1;

		switch (enemyOption) {
		case 1:
			// Damages the player
			printf("The %s attacks!\n", enemy->enemyName);
			playerTakeDmg(enemyDealDmg(enemy), player);

			// Determines how much damage is taken
			int damageTaken = enemy->damage - player->defence;
			if (damageTaken <= 0)
				printf("%s takes no damage!\n", player->playerName);
			else
				printf("%s takes %d damage!\n", player->playerName, damageTaken);
			break;

		case 2:
		default:
			enemyOption = 2;
			printf("The %s bolsters is defence!\n", enemy->enemyName);
			break;
		}

		////////////////////////////////////////////////////////////////////////////////////

		// Reset player defence after enemy move
		if (userinput == 2)
			player->defence >>= 1;

	} while (enemy->health > 0 && player->health > 0);

	// If the player dies, print exit message
	if (player->health <= 0) {
		printf("\n\n\n\n\n");
		printf("%s has perished to a %s...\n", player->playerName, enemy->enemyName);
		Sleep(2000);
		printf("Their journey has come to an end...\n");
		Sleep(2000);
		printf("Long will %s be remembered...\n", player->playerName);
		return EXITCODE;
	}

	printf("%s has slain the %s!\n", player->playerName, enemy->enemyName);
	Sleep(1000);

	if (enemy != NULL) free(enemy);
	return 1;
}

// Free Map Memory
void destroyMap(MAP* map) {
	if (map != NULL) free(map);
}

