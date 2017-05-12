
#include <stdio.h>
#include <stdlib.h> // strtol
#include <string.h> // strlen, memmove
#include <ctype.h> // isspace

#include "caverna.h"


int get_line(char *buffer, int size) {
	fgets(buffer, size, stdin);
	int len = strlen(buffer);
	// strip trailing newline
	buffer[--len] = '\0';
	return len;
}

int trim_trailing(char *buffer, int len) {
	while ((len > 0) && (isspace(buffer[len-1]))) len--;
	buffer[len] = '\0';
	return len;
}

int trim_leading(char *buffer, int len) {
	int i = 0;
	while ( (i < len) && (isspace(buffer[i])) ) i++;
	// i is now first non-space char
	len -=  i; // len after memmove
	memmove(&buffer[0], &buffer[i], len+1);
	return len;
}

int trim(char *buffer, int len) {
	len = trim_trailing(buffer, len);
	len = trim_leading(buffer, len);
	return len;
}

int starts_with(const char *s, const char *prefix) {
	int len = strlen(prefix);
	for (int i = 0; i < len; i++) {
		char c1 = prefix[i];
		char c2 = s[i];
		// NOTE: if s is shorther than prefix,
		// it will have '\0' before the prefix.
		// Consequently, the following test will fail.
		if (c1 != c2) return 0;
	}
	return 1;
}

int to_int(char *buffer, int *value) {
	int success = 0;
	int len = trim_trailing(buffer, strlen(buffer));
	char *endptr = NULL;
	*value = strtol(buffer, &endptr, 10);
	if ((len > 0) && (*endptr == '\0')) {
		success = 1;
	}
	return success;
}

int get_number(int *value) {
	char buffer[0x100];
	get_line(buffer, sizeof(buffer));
	return to_int(buffer, value);
}

int get_number_between(int *value, int min_value, int max_value) {
	char buffer[0x100];
	int success = 0;

	do {
		printf(
		    "Enter a number between %d-%d or \".\" to abort:\n",
		    min_value, max_value
		);
		get_line(buffer, sizeof(buffer));
		if (strcmp(buffer, ".") == 0) {
			printf("Aborting\n");
			return 0;
		}

		success = to_int(buffer, value);
		if (!success) {
			printf("Error: not a number.\n");
			continue;
		}
		success = (min_value <= *value) && (*value <= max_value);
		if (!success) {
			printf("Error: value not between %d-%d\n",
			    min_value, max_value);
			continue;
		}

	} while (!success);

	return 1;
}


int get_yesno(void) {
	char buffer[0x100];
	do {
		get_line(buffer, sizeof(buffer));
		if (strcmp(buffer, "y") == 0) return 1;
		if (strcmp(buffer, "yes") == 0) return 1;
		if (buffer[0] == '\0') return 1;
		if (strcmp(buffer, "n") == 0) return 0;
		if (strcmp(buffer, "no") == 0) return 0;
		printf("Error: invalid response\n");
	} while (1);
	return 0;
}

int get_choice(const char *question, int choices) {
	int min_c = 'a';
	int max_c = min_c + choices;
	do {
		char buffer[0x100];
		printf(question);
		int len = get_line(buffer, sizeof(buffer));
		len = trim(buffer, len);
		if (len == 1) {
			char c = buffer[0];
			if (c == '-') {
				break;
			}
			if ((min_c <= c) && (c <= max_c)) {
				return c-min_c;
			}
		}
		printf("Error: you must choose %c-%c, or \'-\' to abort.\n",
		    min_c, max_c);
	} while (1);

	return -1;
}

static int get_builder_effect(const player_state *player) {
	int effect = BUILDER_REPLACE_NONE;

	if (!caverna_has_player_tile(player, TILE_BUILDER)) return effect;

	printf("[Builder] Replace 1 Wood with 1 Ore?\n");
	if (get_yesno()) {
		effect |= BUILDER_REPLACE_WOOD;
	}
	printf("[Builder] Replace 1 Stone with 1 Ore?\n");
	if (get_yesno()) {
		effect |= BUILDER_REPLACE_STONE;
	}
	return effect;
}

static void swap_int(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int parse_coordinates(int *xptr, int *yptr, const char *buffer) {
	int c1, c2;
	int x, y;
	int success = 0;
	do {
		int len = strlen(buffer);
		if (len < 2) break;

		c1 = buffer[0];
		c2 = buffer[1];

		if (!isalpha(c1)) break;
		if (!isdigit(c2)) break;

		y = toupper(c1) - 'A';
		x = c2 - '0';

		success = 1;
	} while (0);

	if (success) {
		*xptr = x-1;
		*yptr = y;
	}
	return success;
}

int parse_int_between(int *value, char *buffer, int min_value, int max_value) {
	int success;
	success = to_int(buffer, value);
	if (!success) return 0;

	success = (min_value <= *value) && (*value <= max_value);
	if (!success) return 0;

	return 1;
}




int get_coordinates(int *xptr, int *yptr) {
	char buffer[0x100];
	int len = get_line(buffer, sizeof(buffer));
	len = trim(buffer, len);
	return parse_coordinates(xptr, yptr, buffer);
}

int get_tile_placement1(tile_placement *placement) {
	placement->dir = DIRECTION_NONE;
	return get_coordinates(&placement->x, &placement->y);
}

int get_tile_placement(tile_placement *placement) {
	int success = 0;
	int x1, y1, x2, y2;
	int dir;
	int c1, c2, c3;
	do {
		char buffer[0x100];
		int len = get_line(buffer, sizeof(buffer));
		len = trim(buffer, len);
		if (len < 3) break;

		c1 = buffer[0];
		c2 = buffer[1];
		c3 = buffer[2];

		if (!isalpha(c1)) break;
		if (!isdigit(c3)) break;

		y1 = toupper(c1) - 'A';
		if (isalpha(c2)) {
			y2 = toupper(c2) - 'A';
			if (y2 == y1) break;
			x1 = c3 - '0';
			x2 = x1;
		} else if (isdigit(c2)) {
			y2 = y1;
			x1 = c2 - '0';
			x2 = c3 - '0';
			if (x2 == x1) break;
		} else {
			break;
		}

		if ((len >= 5) && (buffer[4] == 'r')) {
			// reverse direction. Swap coordinates.
			swap_int(&x1, &x2);
			swap_int(&y1, &y2);
		}

		if (x2 > x1) {
			dir = DIRECTION_RIGHT;
		} else if (x2 < x1) {
			dir = DIRECTION_LEFT;
		} else if (y2 > y1) {
			dir = DIRECTION_DOWN;
		} else if (y2 < y1) {
			dir = DIRECTION_UP;
		} else {
			break;
		}

		success = 1;
	} while (0);
	if (success) {
		placement->x = x1-1;
		placement->y = y1;
		placement->dir = dir;
	}
	return success;
}

static void get_next_dwarf(
    const player_state *player,
    int *next_dwarf,
    int *next_armed
) {
	*next_dwarf = -1;
	*next_armed = -1;
	int num_armed = 0;
	for (int i = 0; i < player->dwarfs; i++) {
		// Skip, if employed
		if (player->locations[i] != ACTION_NONE) continue;
		if (*next_dwarf == -1) {
			 *next_dwarf = i;
		}
		if (player->weapons[i] > 0) {
			num_armed++;
			if (*next_armed == -1) {
				*next_armed = i;
			}
		}
	}
}

int get_sow(
    crop_placement* sow,
    const player_state *player,
    tile_placement* new_twin_tile
) {
	const tile_state *board = player->board;
	// Clear sow
	for (int i = 0; i < 4; i++) {
		sow[i].x = 0;
		sow[i].y = 0;
		sow[i].type = RESOURCE_NONE;
	}

	int empty_fields = 0;
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			const tile_state *top
			    = caverna_get_top_tile(board, x, y);
			// Skip if not a field.
			if (top->type != TILE_FIELD) continue;
			if ((top->grain == 0) && (top->vegetable == 0)) {
				empty_fields++;
			}
		}
	}
	// Remember to account for the new Meadow/Field twin-tile, if any.
	int x1, y1, x2, y2;
	if (new_twin_tile != NULL) {
		empty_fields++;
		caverna_get_both_coordinates(
		    new_twin_tile, &x1, &y1, &x2, &y2);
	}
	if (empty_fields == 0) {
		printf("No empty fields. Cannot sow.\n");
		return 0;
	}

	int grain = player->grain;
	int vegetable = player->vegetable;

	if ((grain == 0) && (vegetable == 0)) {
		printf(
		    "No Grain nor Vegetable in your personal supply. "
		    "Cannot sow.\n"
		);
		return 0;
	}

	int max_entries = 0;

	if (grain > 2) {
		max_entries += 2;
	} else {
		max_entries += grain;
	}
	if (vegetable > 2) {
		max_entries += 2;
	} else {
		max_entries += vegetable;
	}
	if (empty_fields < max_entries) {
		max_entries = empty_fields;
	}

	int sown_vegetable = 0;
	int sown_grain = 0;

	for (int i = 0; i < max_entries; i++) {
		int finish = 0;
		printf(
		    "There are %d Grain and %d Vegetable left "
		    "in your personal supply.\n",
		    grain - sown_grain,
		    vegetable - sown_vegetable
		);
		printf(
		   "You have already sown %d Grain and %d Vegetable.\n",
		   sown_grain, sown_vegetable
		);
		printf("There is %d empty field(s) left\n", empty_fields-i);

		int may_grain
		    = ((grain-sown_grain) > 0)
		    && (sown_grain < 2);
		int may_vegetable
		    = ((vegetable - sown_vegetable) > 0)
		    && (sown_vegetable < 2);

		if (may_grain && may_vegetable) {
			printf("It is possible to sow both Grain and Vegetable.\n");
		} else if (may_grain) {
			printf("It is possible to sow only Grain.\n");
		} else if (may_vegetable) {
			printf("It is possible to sow only Vegetable.\n");
		} else {
			printf("It is not possible to sow more.\n");
			return i;
		}

		do {
			int success;
			char buffer[0x100];
			int x, y, type;

			printf("Enter field coordinates or \".\" to finish.\n");
			get_line(buffer, sizeof(buffer));
			if (strcmp(buffer, ".") == 0) {
				finish = 1;
				break;
			}
			success = parse_coordinates(&x, &y, buffer);
			if (!success) {
				printf("Error: invalid coordinates\n");
				continue;
			}

			// Validate the location
			const tile_state *top
			    = caverna_get_top_tile(board, x, y);

			if (top == NULL) {
				printf("Error: coordinates are out of boundaries\n");
				continue;
			}
			if ( (new_twin_tile != NULL)
			    && (x == x2) && (y == y2) )
			{
				// crop_placement ok
			} else if (top->type == TILE_FIELD) {
				// crop_placement ok
			} else {
				printf(
				    "Error: at coordinates %c%d there "
				    "is not a Field tile, "
				    "but %s tile instead.\n",
				    'A'+y, x+1,
				    caverna_get_tile_name(top->type)
				);
				continue;
			}
			if ((top->grain != 0) || (top->vegetable != 0)) {
				printf(
				    "Error: at coordiantes %c%d the field "
				    "is not empty.\n",
				    'A'+y, x+1
				);
				continue;
			}

			int abort = 0;
			do {
				printf(
				    "Enter \"g\" to sow Grain, "
				    "\"v\" to sow Vegetable, \".\" to abort.\n"
				);
				int len = get_line(buffer, sizeof(buffer));
				if (len < 1) continue;
				int c = buffer[0];
				if (c == '.') {
					abort = 1;
				} else if (c == 'v') {
					type = RESOURCE_VEGETABLE;
				} else if (c == 'g') {
					type = RESOURCE_GRAIN;
				} else {
					printf("Invalid answer\n");
					continue;
				}
				if ( (type == RESOURCE_GRAIN)
				    && (!may_grain) )
				{
				    printf("Error: not possible to sow Grain.\n");
				    continue;
				}
				if ( (type == RESOURCE_VEGETABLE)
				    && (!may_vegetable) )
				{
				    printf("Error: not possible to sow Vegetable.\n");
				    continue;
				}
				// Success!
				break;
			} while (1);
			if (abort) {
				printf("Crop selection aborted\n");
				continue;
			}
			// Success
			sow[i].x = x;
			sow[i].y = y;
			sow[i].type = type;
			if (type == RESOURCE_VEGETABLE) {
				sown_vegetable++;
			} else if (type == RESOURCE_GRAIN) {
				sown_grain++;
			}
			break;
		} while (1); // single sow action repetion
		if (finish) {
			return i;
		}
	} // for

	return max_entries;
}

void list_furnishing_tiles(
	const int *types,
	int num_types,
	const player_state *player,
	const game_state *gs
) {
	for (int i = 0; i < num_types; i++) {
		int type = types[i];
		int owner = caverna_get_furnishing_owner(gs, type);
		int can_furnish = caverna_can_furnish(player, type);

		printf("%d. %s",
		    i+1,
		    caverna_get_tile_name(type)
		);
		if (owner != -1) {
			printf(" (taken by player %d)", owner);
		} else {
			// Price is shown
			const int *price = caverna_get_furnishing_price(type);

			printf(" (");
			for (int i = 0; i < 3; i++) {
				if (price[i*2] == RESOURCE_NONE) break;
				if (i > 0) {
					printf(" + ");
				}
				printf("%d %s",
				    price[i*2+1],
				    caverna_get_resource_name(price[i*2])
				);
			}
			if (price[0] == RESOURCE_NONE) {
				printf("Free");
			}
			printf(")");
			if (!can_furnish) {
				printf(" [unaffordable]");
			}
		}
		printf("\n");
	}
}

int get_furnishing_selection(
    const game_state *gs,
    const player_state *player,
    int *type,
    tile_placement *placement,
    int *builder_effect
) {
	int num_types = 0;
	const int *types
	    = caverna_get_all_furnishing_types(gs, &num_types);

	list_furnishing_tiles(types, num_types, player, gs);

	do {
		int number;
		int success = get_number_between(&number, 1, num_types);
		if (!success) return 0; // Abort

		// Take the corresponding type
		*type = types[number-1];

		int owner = caverna_get_furnishing_owner(gs, *type);
		if (owner != -1) {
			printf(
			    "Error: the Furnishing tile has already "
			    "been taken by the player #%d.\n",
			    owner
			);
			*type = TILE_NONE;
			continue;
		}

		int can_furnish = caverna_can_furnish(player, *type);
		if (!can_furnish) {
			printf(
			    "Warning: there may not be enough resources "
			    "to pay for the Furnishing tile \"%s\".\n",
			    caverna_get_tile_name(*type)
			);
		}

		// The player is able to acquire the Furnishing tile.
		// Ask Builder effect, if any.
		*builder_effect = get_builder_effect(player);

		// Ask tile placement
		printf("Enter coordinates for the Furnishing tile: %s\n",
		    caverna_get_tile_name(*type));
		success = get_tile_placement1(placement);
		if (!success) {
			//if (get_abort()) return 0;
			printf("Error: Invalid coordinates\n");
			continue;
		}
		break;
	} while (1);

	return 1;
}

/** game_state is required for Furnishing tiles information. */
int get_loot(
    const game_state *gs,
    const player_state *player,
    loot_selection *loots,
    int index,
    int weapon
) {
	loot_selection *loot = &loots[index];
	do {
		int num_items;
		const int *loot_types = caverna_get_loot_items_upto(
		    weapon, &num_items);

		printf("Dwarf with strength %d Weapon can choose:\n",
		    weapon);
		for (int i = 0; i < num_items; i++) {
			int loot_type = loot_types[i];
			if (loot_type == LOOT_NONE) continue;
			printf(
			    "%d. %s\n",
			    i, caverna_get_loot_name(loot_type)
			);
		}
		printf("Enter a number (loot #%d):\n", index+1);
		int loot_num = -1;
		int success = get_number(&loot_num);
		if (!success) {
			printf("Not a number\n");
			continue;
		}
		if ((loot_num < 0) || (loot_num >= num_items)) {
			printf("Please enter a number between: 1-%d\n", num_items);
			continue;
		}
		int loot_type = loot_types[loot_num];
		if (loot_type == LOOT_NONE) {
			printf("Invalid choice: %d\n", loot_num);
			continue;
		}

		// Cross check with previous loot
		for (int i = 0; i < index; i++) {
			if (loots[i].type == loot_type) {
				printf("This loot has already been chosen\n");
				success = 0;
				break;
			}
		}
		if (!success) continue;

		loot->type = loot_type;

		// TODO. Depending on the loot, ask for specific additional params.

		switch(loot_type) {
		case LOOT_FURNISH:
			success = get_furnishing_selection(
			    gs, player,
			    &loot->tile_type,
			    &loot->placement,
			    &loot->builder_effect
			);
			break;
		case LOOT_STABLE:
		case LOOT_TUNNEL:
		case LOOT_MEADOW:
		case LOOT_FIELD:
		case LOOT_CAVERN:
			// Single-tile coordinates
			do {
				printf("Looting \"%s\"...\n",
				    caverna_get_loot_name(loot_num));
				printf("Single-tile coordinates?\n");
			} while (!get_tile_placement1(&loot->placement));
			break;
		case LOOT_SMALL_PASTURE:
			// TODO: Check price (1 Wood)
			// Single-tile coordinates
			do {
				printf("Looting \"%s\"...\n",
				    caverna_get_loot_name(loot_num));
				printf("Single-tile coordinates?\n");
			} while (!get_tile_placement1(&loot->placement));
			break;
		case LOOT_LARGE_PASTURE:
			// TODO: Check price (2 Wood)
			// Twin-tile coordinates
			do {
				printf("Looting \"%s\"...\n",
				    caverna_get_loot_name(loot_num));
				printf("Twin-tile coordinates?\n");
			} while (!get_tile_placement(&loot->placement));
			break;
		case LOOT_DWELLING:
			// TODO: Check price (2 Wood + 2 Stone)
			do {
				printf("Looting \"%s\"...\n",
				    caverna_get_loot_name(loot_num));
				printf("Single-tile coordinates?\n");
			} while (!get_tile_placement1(&loot->placement));
			break;
		case LOOT_SOW:
			success = get_sow(
			    loot->sow,
			    player,
			    NULL
			);
			break;
		case LOOT_BREED2:
			printf("Looting breed up to 2 Farm animals.\n");
			break;
		default:
			// No additional parameters
			break;
		}
		break;
	} while(1);
	return 1;
}

/** game_state is required for furnishing tiles list and states. */
int get_expedition(
    const game_state *gs,
    const player_state *player,
    int weapon,
    loot_selection *loot,
    int level
) {
	int success = 1;
	for (int i = 0; i < level; i++) {
		do {
			int success = get_loot(gs, player, loot, i, weapon);
			if (success) break;
		} while(1);
		if (!success) return 0;
	}
	return 1;
}

int get_furnishing_type(
    const int *types,
    int num_types,
    const player_state *player,
    const game_state *gs
) {
	int type_num = 0;
	do {
		printf("Furnishing tile number?\n");
		int success = get_number(&type_num);
		if (!success) {
			type_num = 0;
			printf("Error: not a number\n");
			continue;
		}
		if ((type_num < 1) || (type_num > num_types)) {
			type_num = 0;
			printf("Error: value must be within 1-%d\n",
			    num_types);
			continue;
		}

		int type = types[type_num-1];

		// Verify that the tile is not yet taken by anyone
		int owner = caverna_get_furnishing_owner(gs, type);
		if (owner != -1) {
			type_num = 0;
			printf(
			    "Error: the Furnishing tile has already "
			    "been taken by a player.\n"
			);
			continue;
		}

		int can_furnish = caverna_can_furnish(player, type);
		if (!can_furnish) {
			type_num = 0;
			printf("Error: Not enough resources to pay "
			    "for the Furnishing tile.\n");
			// TODO: Show price and what's missing.
			continue;
		}
	} while (type_num == 0);
	return types[type_num-1];
}

int furnish_dwelling(
    const player_state *player,
    const game_state *gs,
    furnishing_selection *selection
) {
	static const int dwelling_types[] = {
		// TILE_INITIAL_DWELLING, // Cannot be furnished
		TILE_DWELLING,
		TILE_SIMPLE_DWELLING_1,
		TILE_SIMPLE_DWELLING_2,
		TILE_MIXED_DWELLING,
		TILE_COUPLE_DWELLING,
		TILE_ADDITIONAL_DWELLING
	};
	int entries = sizeof(dwelling_types) / sizeof(dwelling_types[0]);
	do {
		list_furnishing_tiles(dwelling_types, entries, player, gs);

		selection->type = get_furnishing_type(
		    dwelling_types, entries, player, gs);
		selection->builder_effect = get_builder_effect(player);

		// TODO: Print board here
		// TODO: Enumerate possible locations
		do {
			printf("Coordinates for the Furnishing tile \"%s\"?\n",
			    caverna_get_tile_name(selection->type));
		} while (!get_tile_placement1(&selection->placement));
		// TODO: Validate the underlying tile.
		break;
	} while(1);
	return 1;
}

int affords_to_furnish_dwelling(
    const player_state *player,
    const game_state *gs
) {
	static const int dwelling_types[] = {
		// TILE_INITIAL_DWELLING, // Cannot be furnished
		TILE_DWELLING,
		TILE_SIMPLE_DWELLING_1,
		TILE_SIMPLE_DWELLING_2,
		TILE_MIXED_DWELLING,
		TILE_COUPLE_DWELLING
		// TILE_ADDITIONAL_DWELLING // Handled separately
	};
	int entries = sizeof(dwelling_types) / sizeof(dwelling_types[0]);
	for (int i = 0; i < entries; i++) {
		int type = dwelling_types[i];
		int taken_by = caverna_get_furnishing_owner(gs, type);
		if (taken_by != -1) {
			// Skip, because the furnishing tile has
			// already been bought.
			// NOTE: The basic Dwelling is infinite,
			// and will always have taken_by == -1.
			continue;
		}
		if (caverna_can_furnish(player, type)) {
			return 1;
		}
	}
	return 0;
}

int get_forge_weapon(
    const player_state *player,
    int dwarf_num,
    int *do_forging,
    int *weapon
) {
	int can_forge = 1;
	int must_forge = 0;

	// No forging by default
	*do_forging = 0;

	if (player->weapons[dwarf_num] > 0) {
		// Playing an armed Dwarf, cannot forge.
		printf("The Dwarf has a strength %d Weapon already, "
		    "so no forging takes place.\n",
		    player->weapons[dwarf_num]
		);
		return 1;
	} else {
		// Playing an unarmed Dwarf, must forge.
		must_forge = 1;
	}

	// Get Ore and handle Blacksmith discount
	int ore = player->ore;
	int has_blacksmith
	    = caverna_has_player_tile(player, TILE_BLACKSMITH);
	if (has_blacksmith) ore += 2;

	if ((can_forge) && (ore == 0)) {
		printf("Player has no Ore, so a Weapon cannot be forged.\n");
		return 0;
	}

	if (can_forge) {
		printf("A Weapon must be forged.\n");
		*do_forging = 1;
	} else if (must_forge) {
		printf(
		    "The Dwarf %d has no Weapon, so a Weapon must be forged, "
		    "but the player has no Ore to forge a Weapon. "
		    "Cannot take this action.\n",
		    dwarf_num
		);
		return 0;
	}

	if (*do_forging) {
		int ore = player->ore;

		int max_strength = MAX_WEAPON_STRENGTH;
		if (ore < max_strength) max_strength = ore;

		do {
			printf(
			    "You have %d ore. "
			    "Strength for the Weapon (max. %d)?\n",
			    ore,
			    max_strength
			);
			int strength;
			int success = get_number(&strength);
			if (!success) {
				printf("Please enter a number.\n");
				continue;
			}
			if ((strength < 1) || (strength > max_strength)) {
				printf(
				    "Please enter a number between 1-%d.\n",
				    max_strength
				);
				continue;
			}
			*weapon = strength;
			break;
		} while(1);
	}
	return 1;
}


void print_actions(const game_state *gs) {
	int num_actions = gs->num_actions;
	char buffer[0x100];

	printf("Actions: %d (%d+%d)\n", num_actions, gs->num_actions-gs->cur_round, gs->cur_round);
	for (int i = 0; i < num_actions; i++) {
		// For convenience
		const action_space *action = &gs->actions[i];
		int type = action->type;
		int taken_by = action->taken_by;

		if (type == ACTION_NONE) {
			continue;
		}
		const char *name = caverna_get_action_name(type);
		if (name == NULL) {
			sprintf(buffer, "(No description, type: %d)", type);
			name = buffer;
		}
		printf("%d. %s", i+1, name);
		if (action->counter != 0) {
			const char *resource_name = NULL;
			if (action->type == ACTION_ORE_DELIVERY) {
				resource_name = "Ore and Stone";
			} else {
				resource_name = caverna_get_resource_name(
				    caverna_get_action_resource(type)
				);
			}

			printf(" (%d %s)", action->counter, resource_name);
			if ((gs->num_players == 1)
			    && (action->counter >= 6))
			{
				if (action->has_ruby) {
					printf(" [has Ruby]");
				} else {
					printf(" [will reset]");
				}
			}

		}
		if (taken_by != -1) {
			printf(" (taken by player #%d)", taken_by);
		}
		printf("\n");
	}
}

void setc(char *screen, int x, int y, char c) {
	screen[(y*80)+x] = c;
}
void setstr(char *screen, int x, int y, const char *s) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		setc(screen, x+i, y, s[i]);
	}
}

void render_forest(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Forest ");
	setstr(screen, sx, sy+1, ". . . .");
	setstr(screen, sx, sy+2, ". . . .");
	setstr(screen, sx, sy+3, ". . . .");
}

void render_mountain(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Mountn ");
	setstr(screen, sx, sy+1, "#######");
	setstr(screen, sx, sy+2, "#######");
	setstr(screen, sx, sy+3, "#######");
}

void render_cavern(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Cavern ");
	setstr(screen, sx, sy+1, "/^^ ^^\\");
	setstr(screen, sx, sy+2, "       ");
	setstr(screen, sx, sy+3, "\\__ __/");
}

void render_tunnel(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Tunnel ");
	setstr(screen, sx, sy+1, "   |   ");
	setstr(screen, sx, sy+2, "---+---");
	setstr(screen, sx, sy+3, "   |   ");
}

void render_deep_tunnel(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Deep Tn");
	setstr(screen, sx, sy+1, "## | ##");
	setstr(screen, sx, sy+2, "---+---");
	setstr(screen, sx, sy+3, "## | ##");
}

void render_ore_mine(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Ore Mn ");
	setstr(screen, sx, sy+1, "/  .  \\");
	setstr(screen, sx, sy+2, " .   . ");
	setstr(screen, sx, sy+1, "\\  .  /");
}

void render_ruby_mine(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Ore Mn ");
	setstr(screen, sx, sy+1, "/  *  \\");
	setstr(screen, sx, sy+2, " *   * ");
	setstr(screen, sx, sy+3, "\\  *  /");
}

void render_animals(
    char *screen,
    int sx, int sy,
    const tile_state *tile
) {
	char s[10];

	// Mark the stable
	if (tile->stable > 0) {
		setstr(screen, sx+6, sy+1, "%");
	}

	// Mark the dogs, if any
	if (tile->dog > 0) {
		sprintf(s, "Dg%d", tile->dog);
		setstr(screen, sx+1, sy+1, s);
	}

	// Print the animal type
	const char *fmt = NULL;
	int count;
	if (tile->sheep) {
		count = tile->sheep;
		fmt = "Shp%d";
	} else if (tile->donkey) {
		count = tile->donkey;
		fmt = "Dnk%d";
	} else if (tile->boar) {
		count = tile->boar;
		fmt = "Bo%d";
	} else if (tile->cattle) {
		count = tile->cattle;
		fmt = "Ca%d";
	}

	if (fmt != NULL) {
		sprintf(s, fmt, count);
		setstr(screen, sx+1, sy+2, s);
	}
}

void render_large_pasture_left(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "------/");
	setstr(screen, sx, sy+1, "      |");
	setstr(screen, sx, sy+2, "      |");
	setstr(screen, sx, sy+3, "------\\");
}

void render_large_pasture_right(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "\\-Pstr--");
	setstr(screen, sx, sy+1, "|       ");
	setstr(screen, sx, sy+2, "|       ");
	setstr(screen, sx, sy+3, "/-------");
}

void render_large_pasture_down(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "|      |");
	setstr(screen, sx, sy+1, "|      |");
	setstr(screen, sx, sy+2, "|      |");
	setstr(screen, sx, sy+3, "/------\\");
}

void render_large_pasture_up(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "\\-Pstr-/");
	setstr(screen, sx, sy+1, "|      |");
	setstr(screen, sx, sy+2, "|      |");
	setstr(screen, sx, sy+3, "|      |");
}

void render_large_pasture(
    char *screen,
    int sx, int sy,
    const tile_state *board,
    int x, int y
) {
	const tile_state *tile = caverna_get_top_tile(board, x, y);

	int show_cap = 0;
	switch(tile->dir) {
	case DIRECTION_UP:
		render_large_pasture_up(screen, sx, sy, tile);
		break;
	case DIRECTION_RIGHT:
		render_large_pasture_right(screen, sx, sy, tile);
		show_cap = 1;
		break;
	case DIRECTION_DOWN:
		render_large_pasture_down(screen, sx, sy, tile);
		show_cap = 1;
		break;
	case DIRECTION_LEFT:
		render_large_pasture_left(screen, sx, sy, tile);
		break;
	}

	render_animals(screen, sx, sy, tile);

	if (show_cap) {
		tile_placement p;
		int x2, y2;
		p.x = x;
		p.y = y;
		p.dir = tile->dir;
		caverna_get_both_coordinates(&p, &p.x, &p.y, &x2, &y2);

		const tile_state *other = caverna_get_top_tile(board, x2, y2);

		int cap = 4;
		if (tile->stable) cap *= 2;
		if (other->stable) cap *= 2;

		char s[10];
		sprintf(s, "(%d)", cap);
		setstr(screen, sx+2, sy+3, s);
	}
}


void render_small_pasture(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "\\-Pstr-/");
	setstr(screen, sx, sy+1, "|      |");
	setstr(screen, sx, sy+2, "|      |");
	setstr(screen, sx, sy+3, "/------\\");

	int cap;
	if (tile->dog) {
		cap = tile->dog + 1;
	} else {
		cap = tile->stable ? 4 : 2;
	}

	// Print the capacity
	char s[10];
	sprintf(s, "(%d)", cap);
	setstr(screen, sx+2, sy+3, s);

	render_animals(screen, sx, sy, tile);
}

void render_field(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Field   ");
	setstr(screen, sx, sy+1, "~~~~~~~");
	setstr(screen, sx, sy+2, "~~~~~~~");
	setstr(screen, sx, sy+3, "~~~~~~~");

	int count = 0;
	char c = '\0';
	if (tile->vegetable) {
		count = tile->vegetable;
		c = 'V';
	} else if (tile->grain) {
		count = tile->grain;
		c = 'G';
	}

	setstr(screen, sx, sy+0, "Field  ");
	setstr(screen, sx, sy+1, "~~~~~~~");
	setstr(screen, sx, sy+2, "~~~~~~~");
	setstr(screen, sx, sy+3, "~~~~~~~");
	if (count > 0) {
		char s[10];

		for (int i = 0; i < count; i++) {
			s[i] = c;
		}
		s[count] = '\0';

		//sprintf(s, fmt, count);
		setstr(screen, sx+2, sy+2, s);
	}
}

void render_meadow(char *screen, int sx, int sy, const tile_state *tile) {
	setstr(screen, sx, sy+0, "Meadow ");
	setstr(screen, sx, sy+1, "       ");
	setstr(screen, sx, sy+2, "       ");
	setstr(screen, sx, sy+3, "       ");

	if ((tile->dog) || (tile->stable)) {
		char s[10];
		int cap = tile->dog + 1;
		// Print the capacity
		sprintf(s, "(%d)", cap);
		setstr(screen, sx+2, sy+3, s);
		render_animals(screen, sx, sy, tile);
	}
}

void render_entry_level_dwelling(
    char *screen, int sx, int sy,
    const tile_state *tile
) {
	setstr(screen, sx, sy+0, "EntryDw");
	setstr(screen, sx, sy+1, "/     \\");
	setstr(screen, sx, sy+2, "       ");
	setstr(screen, sx, sy+3, "\\     /");
	render_animals(screen, sx, sy, tile);
}

void render_blocked(
    char *screen, int sx, int sy,
    const tile_state *tile
) {
	setstr(screen, sx, sy+0, "/     \\");
	setstr(screen, sx, sy+1, "|     |");
	setstr(screen, sx, sy+2, "\\-----/");
}

void render_furnishing(
    char *screen, int sx, int sy,
    const tile_state *tile
) {
	const char *name = caverna_get_tile_name(tile->type);
	char s[10];
	int j = 0;
	for (int i = 0; i < 7; i++) {
		/*
		char c = tolower(name[i]);
		if (c == 'a')
		    || (c == 'e')
		    || (c == 'i');
		*/
		char c = name[i];
		if (c == '\0') break;

		s[j++] = c;
	}
	s[j++] = '\0';

	setstr(screen, sx, sy+0, s);
	setstr(screen, sx, sy+1, "/     \\");
	setstr(screen, sx, sy+2, "       ");
	setstr(screen, sx, sy+3, "\\     /");
	render_animals(screen, sx, sy, tile);

}




void render_tile(
    char *screen,
    int sx, int sy,
    const tile_state *board,
    int x, int y
) {
	const tile_state *tile = caverna_get_top_tile(board, x, y);

	if ((x == 0) || (x == BOARD_WIDTH-1)
	    || (y == 0) || (y == BOARD_HEIGHT-1))
	{
		if ((tile->type == TILE_FOREST)
		    || (tile->type == TILE_MOUNTAIN))
		{
			// TODO: render_overhung?
			//return;
		}
	}

	switch(tile->type) {
	case TILE_FOREST:
		render_forest(screen, sx, sy, tile);
		break;
	case TILE_MOUNTAIN:
		render_mountain(screen, sx, sy, tile);
		break;
	case TILE_CAVERN:
		render_cavern(screen, sx, sy, tile);
		break;
	case TILE_INITIAL_DWELLING:
		render_entry_level_dwelling(screen, sx, sy, tile);
		break;
	case TILE_BLOCKED:
		render_blocked(screen, sx, sy, tile);
		break;
	case TILE_SMALL_PASTURE:
		render_small_pasture(screen, sx, sy, tile);
		break;
	case TILE_LARGE_PASTURE:
		render_large_pasture(
		    screen, sx, sy,
		    board, x, y
		);
		break;
	case TILE_FIELD:
		render_field(screen, sx, sy, tile);
		break;
	case TILE_MEADOW:
		render_meadow(screen, sx, sy, tile);
		break;
	default:
		render_furnishing(screen, sx, sy, tile);
		break;
	}
	//setc(screen, sx, sy)
}

void render_board(const player_state *player) {
	// For convenience
	const tile_state *board = player->board;
	int has_office = caverna_has_player_tile(player, TILE_OFFICE_ROOM);

	int border = has_office ? 0 : 1;
	//border=0;
	int xmin = 0+border;
	int ymin = 0+border;
	int xmax = (BOARD_WIDTH-1)-border;
	int ymax = (BOARD_HEIGHT-1)-border;

	char screen[50*80];
	memset(screen, 0, sizeof(screen));

	for (int x = xmin; x <= xmax; x++) {
		char coords[4];
		sprintf(coords, "%d", x+1);
		setstr(screen, ((x-xmin)*8)+2+2, 0, coords);
	}
	for (int y = ymin; y <= ymax; y++) {
		char coords[4];
		sprintf(coords, "%c", 'A'+y);
		setstr(screen, 0, ((y-ymin)*4)+1+2, coords);
	}


	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {

			// Compute screen coordinates
			int sx = 2+ ((x-xmin)*8);
			int sy = 1+ ((y-ymin)*4);

			// Build and display logical coordinates
			//setstr(screen, sx+2, sy+4, coords);
			// Render tile
			render_tile(screen, sx, sy, board, x, y);
		}
	}

	ymax = 1 + ((ymax+1-ymin)*4);
	xmax = 2 + ((xmax+1-ymin)*8);

	for (int y = 0; y < ymax; y++) {
		int offset = y*80;
		for (int x = 0; x < xmax; x++) {
			char c = screen[offset++];
			if (c == '\0') c = ' ';
			printf("%c", c);
		}
		printf("\n");
	}
}

void print_board(const tile_state *board) {

	printf("   ");
	for (int x = 0; x < BOARD_WIDTH; x++) {
		printf("   %d", x+1);
	}
	printf("\n");

	for (int y = 0; y < BOARD_HEIGHT; y++) {
		printf("  %c", 'A'+y);
		int tile_dir[BOARD_WIDTH];
		for (int x = 0; x < BOARD_WIDTH; x++) {
			char c;
			const tile_state *tile
			    = caverna_get_top_tile(board, x, y);
			// NULL if no prev
			const tile_state *prev
			    = caverna_get_top_tile(board, x-1, y);
			tile_dir[x] = tile->dir;
			switch(tile->type) {
			case TILE_FOREST:
				c = 'O';
				break;
			case TILE_MOUNTAIN:
				c = 'X';
				break;
			case TILE_CAVERN:
				c = '#';
				break;
			case TILE_TUNNEL:
				c = '+';
				break;
			case TILE_DEEP_TUNNEL:
				c = '%';
				break;
			case TILE_ORE_MINE:
				c = '~';
				break;
			case TILE_INITIAL_DWELLING:
				c = '*';
				break;
			case TILE_MEADOW:
				c = '_';
				break;
			case TILE_FIELD:
				// TODO: Should depend on the whether the field is empty.
				c = '&';
				if (tile->vegetable == 2) {
					c = 'V';
				} else if (tile->vegetable == 1) {
					c = 'v';
				} else if (tile->grain == 3) {
					c = ':';
				} else if (tile->grain == 2) {
					c = 'G';
				} else if (tile->grain == 1) {
					c = 'g';
				}
				break;
			case TILE_BLOCKED:
				c = '"';
				break;
			default:
				// Some furnishing tile
				c = 'R';
				break;
			}

			if ((tile->type == TILE_FOREST) ||
			    (tile->type == TILE_MOUNTAIN))
			{
				if ((x == 0) || (x == BOARD_WIDTH-1)
				    || (y == 0) || (y == BOARD_HEIGHT-1))
				{
					c = ','; // outside
				}
			}
			char connector = ' ';
			if (( tile->dir == DIRECTION_LEFT)
			    && (prev != NULL)
			    && (prev->dir == DIRECTION_RIGHT) )
			{
				connector = '-';
			}
		    	printf(" %c %c", connector, c);
		} // for
		printf("\n");
		printf("   ");
		for (int x = 0; x < BOARD_WIDTH; x++) {
			const tile_state *down
			    = caverna_get_top_tile(board, x, y+1);
			char connector = ' ';
			if ( (tile_dir[x] == DIRECTION_DOWN)
			    && (down != NULL)
			    && (down->dir == DIRECTION_UP) )
			{
				connector = '|';
			}
		    	printf("   %c", connector);
		}
		printf("\n");
	}
}

void print_newborns(const player_state *player) {
	int i = 0;
	printf("(Newborns: ");
	if (player->newborn_sheep) {
		printf("Sheep");
		i++;
	}
	if (player->newborn_donkey) {
		printf("%sDonkey", i > 0 ? ", " : "");
		i++;
	}
	if (player->newborn_boar) {
		printf("%sBoar", i > 0 ? ", " : "");
		i++;
	}
	if (player->newborn_cattle > 0) {
		printf("%sCattle", i > 0 ? ", " : "");
		i++;
	}
	if (i == 0) {
		printf("none");
	}
	printf(")\n");
}

void print_unplaced(const player_state *player) {
	// Show unplaced animal status, if any.

	int unplaced_sheep = player->sheep - player->placed_sheep;
	int unplaced_donkey = player->donkey - player->placed_donkey;
	int unplaced_boar = player->boar - player->placed_boar;
	int unplaced_cattle = player->cattle - player->placed_cattle;
	int num_unplaced = unplaced_sheep + unplaced_donkey
	    + unplaced_boar + unplaced_cattle;

	if (num_unplaced > 0) {
		int i = 0;
		printf("(Unplaced animals: ");
		if (unplaced_sheep > 0) {
			printf("%d Sheep", unplaced_sheep);
			i++;
		}
		if (unplaced_donkey > 0) {
			printf("%s%d Donkey",
			    i > 0 ? ", " : "",
			    unplaced_donkey
			);
			i++;
		}
		if (unplaced_boar > 0) {
			printf("%s%d Boar",
			    i > 0 ? ", " : "",
			    unplaced_boar
			);
			i++;
		}
		if (unplaced_cattle > 0) {
			printf("%s%d Cattle",
			    i > 0 ? ", " : "",
			    unplaced_cattle
			);
			i++;
		}
		printf(")\n");
	}
}


void print_status(const player_state *player) {
	printf("------------------------------------------------------\n");
	printf("| %2d Food  | %2d Veggie | %2d Grain | %2d Begging       |\n",
	    player->food,
	    player->vegetable,
	    player->grain,
	    player->beggar
	);
	printf("| %2d Gold  | %2d Stone  | %2d Wood  | %2d Ruby | %2d Ore |\n",
	    player->gold,
	    player->stone,
	    player->wood,
	    player->ruby,
	    player->ore
	);
	printf("| %2d Sheep | %2d Donkey | %2d Boar  | %2d Cow  | %2d Dog |\n",
	    player->sheep,
	    player->donkey,
	    player->boar,
	    player->cattle,
	    player->dog
	);
	printf("------------------------------------------------------\n");

	print_unplaced(player);

	score_state score;
	printf("(Score: %d points)\n", caverna_get_score(&score, player));


}

void print_dwarfs(const player_state *player) {
        int next_dwarf = -1; // Next unemployed dwarf
        for (int i = 0; i < player->dwarfs; i++) {
                // Skip, if employed
                if (player->locations[i] != ACTION_NONE) continue;
                if (next_dwarf == -1) {
                        next_dwarf = i;
			break;
                }
        }

	printf("Dwarfs:\n");
	for (int i = 0; i < player->dwarfs; i++) {
		int location = player->locations[i];
		int occupied = location != ACTION_NONE;
		int weapon = player->weapons[i];
		int is_next = next_dwarf == i;
		if (occupied) {
			if (weapon == 0) {
				printf(
				    "%d. (at %s)\n",
				    i+1, caverna_get_action_name(location)
				);
			} else {
				printf(
				    "%d. (at %s, strength %d Weapon)\n",
				    i+1, caverna_get_action_name(location),
				    weapon
				);
			}
		} else if (weapon == 0) {
			printf(
			    "%d. Free, no Weapon%s.\n",
			    i+1,
			    is_next ? " (next in order)" : ""
			);
		} else {
			printf(
			    "%d. Free, strength %d Weapon%s.\n",
			    i+1, weapon,
			    is_next ? " (next in order)" : ""
			);
		}
	}
	printf("Press enter to continue\n");
	get_yesno();
}

action_orders *take_drift_mining(const game_state* gs, int dwarf_num) {

	//const player_state *player = caverna_get_player(gs, gs->cur_player);

	action_orders *ao = caverna_malloc_orders(ACTION_DRIFT_MINING);
	if (ao == NULL) {
		perror("malloc");
		exit(1);
	}

	drift_mining_orders *orders = (void *) &ao->orders;
	printf("Taking stone.\n");
	orders->take_stone = 1;

	printf("Do mining?\n");
	orders->do_mining = get_yesno();
	if (orders->do_mining) {
		do {
			printf("Coordinates for twin-tile: Cavern/Tunnel\n");
		} while (!get_tile_placement(&orders->placement));
	}
	// 1) pick stone?
	// 2) do mining?
	// 3) if mining, do tile placement
	return ao;
}

action_orders *take_logging(const game_state* gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_LOGGING);
	if (ao == NULL) {
		perror("malloc");
		exit(1);
	}
	logging_orders *orders = (void *) ao->orders;
	printf("Taking wood.\n");
	orders->take_wood = 1;

	const player_state *player
	    = caverna_get_player(gs, gs->cur_player);

	// For convenience
	int weapon = player->weapons[dwarf_num];

	if (weapon > 0) {
		orders->do_looting = 1;
		int success = 1;
		do {
			success = get_expedition(
			    gs, player, weapon, orders->loot, 1);
			if (!success) {
				printf("Error during get_expedition()\n");
				continue;
			}
		} while (!success);
	}

	return ao;
}

action_orders *take_housework(const game_state* gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_HOUSEWORK);
	if (ao == NULL) {
		perror("malloc");
		exit(1);
	}
	housework_orders *orders = (void *) ao->orders;

	printf("Take the dog?\n");
	orders->take_dog = get_yesno();

	printf("Furnish a cavern?\n");
	orders->do_furnish = get_yesno();

	const player_state *player
	    = caverna_get_player(gs, gs->cur_player);

	if (orders->do_furnish) {
		int success = get_furnishing_selection(
		    gs, player,
		    &orders->tile_type,
		    &orders->placement,
		    &orders->builder_flags
		);
		if (!success) {
			free(ao);
			ao = NULL;
		}
	}

	// For convenience
	return ao;
}

action_orders *take_wood_gathering(const game_state* gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_WOOD_GATHERING);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	wood_gathering_orders *orders = (void *) ao->orders;
	printf("Taking Wood.\n");
	orders->take_wood = 1;
	return ao;
}

action_orders *take_excavation(const game_state* gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_EXCAVATION);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	excavation_orders *orders = (void *) ao->orders;
	printf("Taking Stone\n");
	orders->take_stone = 1;

	printf("Do mining?\n");
	orders->do_mining = get_yesno();
	if (orders->do_mining) {
		printf("Place Cavern/Cavern tile instead of Cavern/Tunnel?\n");
		orders->cc = get_yesno();
		do {
			printf("Coordinates for twin-tile: Cavern/%s\n",
			    orders->cc ? "Cavern" : "Tunnel");
		} while (!get_tile_placement(&orders->placement));
	}

	return ao;
}

action_orders *take_ore_mining(const game_state* gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_ORE_MINING);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	ore_mining_orders *orders = (void *) ao->orders;
	printf("Taking Ore.\n");
	orders->take_ore = 1;
	return ao;
}

action_orders *take_sustenance(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_SUSTENANCE);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	sustenance_orders *orders = (void *) ao->orders;

	printf("Taking Food.\n");
	orders->take_food = 1;

	printf("Do clearing?\n");
	orders->do_clearing = get_yesno();

	if (orders->do_clearing) {
		do {
			printf("Coordinates for twin-tile: Meadow/Field?\n");
		} while (!get_tile_placement(&orders->placement));
	}

	return ao;
}

action_orders *take_ruby_mining(const game_state* gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_RUBY_MINING);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	ruby_mining_orders *orders = (void *) ao->orders;
	printf("Taking Ruby.\n");
	orders->take_ruby = 1;
	return ao;
}

// TODO: housework should be here

action_orders *take_slash_and_burn(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_SLASH_AND_BURN);
	slash_and_burn_orders *orders = (void *) ao->orders;

	const player_state *player
	    = caverna_get_player(gs, gs->cur_player);

	printf("Do clearing?\n");
	orders->do_clearing = get_yesno();

	if (orders->do_clearing) {
		do {
			printf("Coordinates for twin-tile: Meadow/Field?\n");
		} while (!get_tile_placement(&orders->placement));
	}

	printf("Do sowing?\n");
	int do_sow = get_yesno();
	if (do_sow) {
		get_sow(
		    orders->sow, player,
		    &orders->placement
		);
	}

	return ao;
}

action_orders *take_blacksmithing(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_BLACKSMITHING);
	blacksmithing_orders *orders = (void *) ao->orders;

	const player_state *player
	    = caverna_get_player(gs, gs->cur_player);

	int success = get_forge_weapon(
	    player,
	    dwarf_num,
	    &orders->do_forging,
	    &orders->weapon
	);

	if (!success) {
		// Cannot forge a weapon to an unarmed Dwarf.
		free(ao);
		return NULL;
	}

	orders->do_looting = 1;
	printf("Level 3 Quest is always performed.\n");

	int weapon = 0;
	if (orders->do_forging) {
		weapon = orders->weapon;
	} else {
		weapon = player->weapons[dwarf_num];
	}

	success = 1;
	do {
		success = get_expedition(
		    gs, player, weapon, orders->loot, 3);
		if (!success) {
			printf("Error during get_expedition()\n");
			continue;
		}
	} while (!success);

	return ao;
}

action_orders *take_animal_farming(const game_state *gs, int dwarf_num, int action) {
	action_orders *ao = caverna_malloc_orders(action);
	sheep_farming_orders *orders = (void *) ao->orders;

	const player_state *player
	    = caverna_get_player(gs, gs->cur_player);

	int wood_left = player->wood;
	int price_small = 2;
	int price_large = 4;
	int price_stable = 1;

	// Account for Discount effects
	if (caverna_has_player_tile(player, TILE_CARPENTER)) {
		price_small -= 1;
		price_large -= 1;
	}
	if (caverna_has_player_tile(player, TILE_STONE_CARVER)) {
		price_stable -= 1;
	}

	if (wood_left >= price_small) {
		printf("Build Small pasture for %d Wood?\n", price_small);
		orders->build_small = get_yesno();
	} else {
		printf("Not enough Wood left for a Small pasture.\n");
		orders->build_small = 0;
	}

	if (orders->build_small) {
		do {
			printf("Coordinates for Small pasture?\n");
		} while (!get_tile_placement1(&orders->small_placement));
		wood_left -= price_small; // Account discounts.
	}

	if (wood_left >= price_large) {
		printf("Build Large pasture for %d Wood?\n", price_large);
		orders->build_large = get_yesno();
	} else {
		printf("Not enough Wood left for a Large pasture.\n");
		orders->build_large = 0;
	}

	if (orders->build_large) {
		do {
			printf("Twin-tile coordinates for Large pasture?\n");
		} while (!get_tile_placement(&orders->large_placement));
	}

	if (player->stone >= price_stable) {
		printf("Build Stable for 1 Stone?\n");
		orders->build_stable = get_yesno();
	} else {
		printf("Not enough Stone left for a Stable.\n");
		orders->build_stable = 0;
	}

	if (orders->build_stable) {
		do {
			printf("Coordinates for Stable?\n");
		} while (!get_tile_placement1(&orders->stable_placement));
	}

	const char *animal_name = "(?)";
	switch(action) {
	case ACTION_SHEEP_FARMING:
		animal_name = caverna_get_resource_name(RESOURCE_SHEEP);
		break;
	case ACTION_DONKEY_FARMING:
		animal_name = caverna_get_resource_name(RESOURCE_DONKEY);
		break;
	}

	printf("Taking %s.\n", animal_name);
	orders->take_animals = 1;

	return ao;
}

action_orders *take_sheep_farming(const game_state *gs, int dwarf_num) {
	return take_animal_farming(gs, dwarf_num, ACTION_SHEEP_FARMING);
}

action_orders *take_ore_mine_construction(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_ORE_MINE_CONSTRUCTION);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	ore_mine_construction_orders *orders = (void *) ao->orders;

	// For convenience
	const player_state *player = &gs->players[gs->cur_player];
	int weapon = player->weapons[dwarf_num];

	orders->do_looting = weapon > 0;

	if (orders->do_looting) {
		// May choose NOT to construct an ore mine.
		printf("Construct an ore mine?\n");
		orders->do_construction = get_yesno();
	} else {
		// Must construct an ore mine.
		orders->do_construction = 1;
	}

	if (orders->do_construction) {
		do {
			printf("Coordinates for twin-tile: Ore mine/Deep Tunnel?\n");
		} while (!get_tile_placement(&orders->placement));
	}

	if (orders->do_looting) {
		int success = 1;
		do {
			success = get_expedition(
			    gs, player, weapon, orders->loot, 2);
			if (!success) {
				printf("Error during get_expedition()\n");
				continue;
			}
		} while (!success);
	}

	return ao;

}

action_orders *take_wish_for_children(const game_state *gs, int dwarf_num, int is_urgent) {
	action_orders *ao = NULL;
	if (!is_urgent) {
		ao = caverna_malloc_orders(ACTION_WISH_FOR_CHILDREN);
	} else {
		ao = caverna_malloc_orders(ACTION_URGENT_WISH_FOR_CHILDREN);
	}

	wish_for_children_orders *orders = (void *) ao->orders;

	// Get current player
	const player_state *player
	    = caverna_get_player(gs, gs->cur_player);

	int has_guest_room
	    = caverna_has_player_tile(player, TILE_GUEST_ROOM);

	int additional_owner
	    = caverna_get_furnishing_owner(gs, TILE_ADDITIONAL_DWELLING);

	int has_additional_dwelling = additional_owner == gs->cur_player;

	int capacity = caverna_num_rooms_in_dwellings(player);

	int num_occupied = player->dwarfs + player->children;

	// Additional dwelling counts only if the player has 5 Dwarfs already.
	if ((num_occupied == 5) && (has_additional_dwelling)) {
		capacity++;
	}

	int can_furnish_additional = caverna_can_furnish(
	    player, TILE_ADDITIONAL_DWELLING);

	int can_family_growth = 1;
	int can_furnish_dwelling = 1;

	if (caverna_num_caverns(player) == 0) {
		// TODO: May use Rubies, if there are still Mountain tiles?
		printf("There are no empty Caverns in the Mountain, "
		    "so it is impossible to Furnish a Dwelling.\n");
		can_furnish_dwelling = 0;
	}

	if ( (can_furnish_dwelling)
	    && (!affords_to_furnish_dwelling(player, gs))
	    && (!can_furnish_additional) )
	{
		printf("The player does not have enough resources for "
		    "any kind of Dwelling, so it is impossible "
		    "to Furnish a Dwelling.\n");
		can_furnish_dwelling = 0;
	}

	if (num_occupied == 6) {
		printf("The player has already six Dwarfs, so further"
		    "Family growth is impossible.\n");
		can_family_growth = 0;
	} else if (num_occupied == 5) {
		// Regardless of the capacity (the player may have
		// extra Dwellings just for the points), Family growth
		// is possible only by having the Additional dwelling.

		// Therefore, the player must either (i) have the Additional
		// dwelling, or (ii) have the Guest Room and afford to
		// Furnish the Additional dwelling.
		if (has_additional_dwelling) {
			// possible
		} else if (!has_guest_room) {
			printf("The player has five Dwarfs, and no "
			    "Additional dwelling for the sixth Dwarf, "
			    "so Family growth is not possible.\n");
			can_family_growth = 0;
		} else if (additional_owner != -1) {
			printf("The player has five Dwarfs, but the "
			    "Additional dwelling for the sixth Dwarf is "
			    "already on another player\'s (%d) Home board, "
			    "so further Family growth is not possible.\n",
			    additional_owner
			);
			can_family_growth = 0;
		} else if (!can_furnish_additional) {
			printf("The player has five Dwarfs, and cannot "
			    "afford to Furnish the Additional dwelling "
			    "for the sixth Dwarf, so Family growth is "
			    "not possible.\n"
			);
			can_family_growth = 0;
		}
	} else if (num_occupied == capacity) { // num_occupied <= 4
		// Family growth is possible iff a new Dwelling for
		// the Dwarf baby is furnished at the same time.

		// To do this, the player must (i) have Guest room,
		// and (ii) be able to furnish a Dwelling.

		// The new Dwelling must not be the Additional dwelling.

		if (!has_guest_room) {
			printf("The player has no vacant room in any "
			    "Dwelling for the baby Dwarf, so Family growth "
			    "is not possible.\n"
			);
			can_family_growth = 0;
		} else if (!can_furnish_dwelling) {
			printf("The player has no vacant room in any "
			    "Dwelling for the baby Dwarf, and cannot afford "
			    "to Furnish a Dwelling, so Family growth "
			    "is not possible.\n"
			);
			can_family_growth = 0;
		}
	} else {
		// num_occupied <= 4 AND num_occupied < capacity
		// Family growth IS possible.
	}

	if (!is_urgent) {
		int can_both = can_family_growth && can_furnish_dwelling;
		if ((!can_family_growth) && (!can_furnish_dwelling)) {
			printf("Both actions are impossible.\n");
			free(ao);
			return NULL;
		}

		printf("Possible actions:\n");
		printf("(a) Family growth%s\n",
		    can_family_growth ? "" : " (impossible)");
		printf("(b) Furnish a Dwelling%s\n",
		    can_furnish_dwelling ? "" : " (impossible)");
		int choice = -1;
		if (has_guest_room && can_both) {
			printf("(c) Both\n");
			choice = get_choice("Which action to play?\n", 3);
		} else {
			choice = get_choice("Which action to play?\n", 2);
		}
		if (choice == -1) {
			free(ao);
			return NULL;
		}
		orders->do_family_growth = 0;
		orders->furnish_dwelling = 0;
		if ((choice == 0) || (choice == 2)) {
			if (!can_family_growth) {
				printf("That action is impossible\n");
				free(ao);
				return NULL;
			}
			orders->do_family_growth = 1;
		}
		if ((choice == 1) || (choice == 2)) {
			if (!can_furnish_dwelling) {
				printf("That action is impossible\n");
				free(ao);
				return NULL;
			}
			orders->furnish_dwelling = 1;
		}
	} else {
		printf("Possible actions:\n");
		printf("(a) Furnish a Dwelling%s,\n",
		    can_furnish_dwelling ? "" : " (impossible)");
		printf("    followed optionally by Family growth%s\n",
		    can_family_growth ? "" : " (impossible)");
		printf("(b) Take +3 Gold\n");
		int choice = -1;
		if (has_guest_room && can_furnish_dwelling) {
			printf("(c) Both\n");
			choice = get_choice("Which action to play?\n", 3);
		} else {
			choice = get_choice("Which action to play?\n", 2);
		}
		if ((choice == 0) || (choice == 2)) {
			if (!can_furnish_dwelling) {
				printf("That action is impossible\n");
				free(ao);
				return NULL;
			}
			orders->furnish_dwelling = 1;
		}
		if ((choice == 1) || (choice == 2)) {
			orders->take_gold = 1;
		}
	}

	if (orders->furnish_dwelling) {
		furnishing_selection selection;
		furnish_dwelling(player, gs, &selection);

		// TODO: This is temporary transport..
		orders->type = selection.type;
		orders->placement = selection.placement;
		orders->builder_effect = selection.builder_effect;

		if ((is_urgent) && (can_family_growth)) {
			printf("Do the Family growth also?\n");
			orders->do_family_growth = get_yesno();
		}
	}


	return ao;
}

action_orders *take_donkey_farming(const game_state *gs, int dwarf_num) {
	return take_animal_farming(gs, dwarf_num, ACTION_DONKEY_FARMING);
}

action_orders *take_ruby_mine_construction(const game_state *gs, int dwarf_num) {
	action_orders *ao
	    = caverna_malloc_orders(ACTION_RUBY_MINE_CONSTRUCTION);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	ruby_mine_construction_orders *orders = (void *) ao->orders;

	// Get current player
	const player_state *player
	    = caverna_get_player(gs, gs->cur_player);

	// At least one ruby mine must be constructed when taking this action.
	tile_placement placement;

	int type = TILE_NONE;
	int other = TILE_NONE;
	do {
		do {
			printf("Coordinates for Ruby mine?\n");
		} while (!get_tile_placement1(&placement));

		const tile_state *tile = caverna_get_top_tile(
		    player->board,
		    placement.x, placement.y
		);

		if (tile == NULL) {
			printf("Error: invalid coordinates\n");
			continue;
		}

		if (tile->type == TILE_TUNNEL) {
			type = TILE_TUNNEL;
			other = TILE_DEEP_TUNNEL;
		} else if (tile->type == TILE_DEEP_TUNNEL) {
			type = TILE_DEEP_TUNNEL;
			other = TILE_TUNNEL;
		} else {
			printf(
			    "Error: the tile at %c%d is %s tile. "
			    "Either Tunnel nor Deep Tunnel expected",
			    'A'+placement.y, placement.x+1,
			    caverna_get_tile_name(tile->type)
			);
			continue;
		}
		break;
	} while (1);

	if (type == TILE_TUNNEL) {
		orders->do_construction1 = 1;
		orders->do_construction2 = 0;
		orders->placement1 = placement;
	} else { // type == TILE_DEEP_TUNNEL
		orders->do_construction1 = 0;
		orders->do_construction2 = 1;
		orders->placement2 = placement;
	}

	int do_other = 0;
	if (caverna_has_player_tile(player, TILE_GUEST_ROOM)) {
		printf("Construct a Ruby mine on %s tile as well?\n",
		    caverna_get_tile_name(other)
		);
		do_other = get_yesno();
	}

	if (do_other) {
		do {
			printf("Coordinates for Ruby mine?\n");
			int success = get_tile_placement1(&placement);
			if (!success) continue;

			const tile_state *tile = caverna_get_top_tile(
			    player->board,
			    placement.x, placement.y
			);
			if (tile == NULL) {
				printf("Error: invalid coordinates\n");
				continue;
			}
			if (tile->type != other) {
				printf(
				    "Error: the tile at %c%d is %s tile. "
				    "Expected %s tile.",
				    'A'+placement.y, placement.x+1,
				    caverna_get_tile_name(tile->type),
				    caverna_get_tile_name(other)
				);
				continue;
			}
			break;
		} while (1);

		if (other == TILE_TUNNEL) {
			orders->do_construction1 = 1;
			orders->placement1 = placement;
		} else { // other == TILE_DEEP_TUNNEL
			orders->do_construction2 = 1;
			orders->placement2 = placement;
		}

	}

	return ao;
}

action_orders *take_ore_delivery(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_ORE_DELIVERY);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	ore_delivery_orders *orders = (void *) ao->orders;
	printf("Taking Stone and Ore\n");
	orders->take_stone_and_ore = 1;
	return ao;
}

action_orders *take_family_life(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_FAMILY_LIFE);
	family_life_orders *orders = (void *) ao->orders;

	// Get current player
	const player_state *player
	    = caverna_get_player(gs, gs->cur_player);

	int has_additional_dwelling
	    = caverna_has_player_tile(player, TILE_ADDITIONAL_DWELLING);

	int capacity = caverna_num_rooms_in_dwellings(player);

	int num_occupied = player->dwarfs + player->children;

	// Additional dwelling counts iff the player has 5 Dwarfs already.
	if ((num_occupied == 5) && (has_additional_dwelling)) {
		capacity++;
	}

	int can_family_growth = 1;

	if (num_occupied == 6) {
		printf("The player has already six Dwarfs, so further"
		    "Family growth is impossible.\n");
		can_family_growth = 0;
	} else if (num_occupied == 5) {
		// Regardless of the capacity (the player may have
		// extra Dwellings just for the points), Family growth
		// is possible only by having the Additional dwelling.

		if (!has_additional_dwelling) {
			printf("The player has five Dwarfs, and no "
			    "Additional dwelling for the sixth Dwarf, "
			    "so Family growth is not possible.\n");
			can_family_growth = 0;
		}
	} else if (num_occupied == capacity) { // num_occupied <= 4
		printf("The player has no vacant room in any "
		    "Dwelling for the baby Dwarf, so Family growth "
		    "is not possible.\n"
		);
		can_family_growth = 0;
	} else {
		// num_occupied <= 4 AND num_occupied < capacity
		// Family growth IS possible.
	}


	if (can_family_growth) {
		printf("Do family growth?\n");
		orders->do_family_growth = get_yesno();
	} else {
		orders->do_family_growth = 0;
	}

	printf("Do sowing?\n");
	int do_sow = get_yesno();
	if (do_sow) {
		int sown = get_sow(orders->sow, player, NULL);
		if (sown == 0) do_sow = 0;
	}

	if ((!orders->do_family_growth) && (!do_sow)) {
		printf("Error: You must either do Family growth or Sow\n");
		free(ao);
		return NULL;
	}


	return ao;
}

action_orders *take_ore_trading(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_ORE_TRADING);
	ore_trading_orders *orders = (void *) ao->orders;

	const player_state *player = caverna_get_player(gs, gs->cur_player);

	int max_count = player->ore / 2;
	if (max_count < 1) {
		printf(
		    "Error: You do not have enough Ore for exchange "
		    "(have %d, needed at least %d)\n",
		    player->ore, 2
		);
		free(ao);
		return NULL;
	}
	if (max_count > 3) max_count = 3;

	printf("You have %d Ore\n", player->ore);
	printf(
	    "Exchange 2 Ore for 2 Gold + 1 Food. "
	    "How many times (%d-%d)?\n",
	    1, max_count
	);
	int success = get_number_between(&orders->count, 1, max_count);
	if (!success) {
		free(ao);
		return NULL;
	}

	return ao;
}


action_orders *take_adventure(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_ADVENTURE);
	adventure_orders *orders = (void *) ao->orders;

	const player_state *player = caverna_get_player(gs, gs->cur_player);

	int success = get_forge_weapon(
	    player,
	    dwarf_num,
	    &orders->do_forging,
	    &orders->weapon
	);
	if (!success) {
		// Cannot forge a weapon to an unarmed Dwarf.
		free(ao);
		return NULL;
	}

	orders->do_looting = 1;
	printf("2x Level 1 Quests are always performed.\n");

	int weapon = 0;
	if (orders->do_forging) {
		weapon = orders->weapon;
	} else {
		weapon = player->weapons[dwarf_num];
	}

	success = 1;
	do {
		success = get_expedition(
		    gs, player, weapon, orders->loot1, 1);
		if (!success) {
			printf("Error during get_expedition()\n");
			continue;
		}
	} while (!success);

	// Account for weapon strength increment, and saturate.
	if (orders->loot1[0].type == LOOT_INCREASE_WEAPONS) {
		weapon++;
	}
	weapon++;
	if (weapon > MAX_WEAPON_STRENGTH) {
		weapon = MAX_WEAPON_STRENGTH;
	}

	success = 1;
	do {
		success = get_expedition(
		    gs, player, weapon, orders->loot2, 1);
		if (!success) {
			printf("Error during get_expedition()\n");
			continue;
		}
	} while (!success);

	return ao;
}

action_orders *take_ruby_delivery(const game_state *gs, int dwarf_num) {
	action_orders *ao = caverna_malloc_orders(ACTION_RUBY_DELIVERY);
	// TODO: assume success... make it into a function to handle
	// the out of memory condition.
	ruby_delivery_orders *orders = (void *) ao->orders;
	printf("Taking Ruby\n");
	orders->take_ruby = 1;
	return ao;
}

const action_orders *plan_action(const game_state *gs, int dwarf_num, int action_num) {
	const action_space *action = &gs->actions[action_num];
	int type = action->type;
	action_orders *ao = NULL;

	// Different flow based on the action type
	switch(type) {
	case ACTION_DRIFT_MINING:
		ao = take_drift_mining(gs, dwarf_num);
		break;
	case ACTION_LOGGING:
		ao = take_logging(gs, dwarf_num);
		break;
	case ACTION_WOOD_GATHERING:
		ao = take_wood_gathering(gs, dwarf_num);
		break;
	case ACTION_EXCAVATION:
		ao = take_excavation(gs, dwarf_num);
		break;
	//case ACTION_SUPPLIES:
	//case ACTION_CLEARING:
	//case ACTION_STARTING_PLAYER:
	case ACTION_ORE_MINING:
		ao = take_ore_mining(gs, dwarf_num);
		break;
	case ACTION_SUSTENANCE:
		ao = take_sustenance(gs, dwarf_num);
		break;
	case ACTION_RUBY_MINING:
		ao = take_ruby_mining(gs, dwarf_num);
		break;
	case ACTION_HOUSEWORK:
		ao = take_housework(gs, dwarf_num);
		break;
	case ACTION_SLASH_AND_BURN:
		ao = take_slash_and_burn(gs, dwarf_num);
		break;
	case ACTION_BLACKSMITHING:
		ao = take_blacksmithing(gs, dwarf_num);
		break;
	case ACTION_SHEEP_FARMING:
		ao = take_sheep_farming(gs, dwarf_num);
		break;
	case ACTION_ORE_MINE_CONSTRUCTION:
		ao = take_ore_mine_construction(gs, dwarf_num);
		break;
	case ACTION_WISH_FOR_CHILDREN:
		ao = take_wish_for_children(gs, dwarf_num, 0);
		break;
	case ACTION_URGENT_WISH_FOR_CHILDREN:
		ao = take_wish_for_children(gs, dwarf_num, 1);
		break;
	case ACTION_DONKEY_FARMING:
		ao = take_donkey_farming(gs, dwarf_num);
		break;
	case ACTION_RUBY_MINE_CONSTRUCTION:
		ao = take_ruby_mine_construction(gs, dwarf_num);
		break;
	case ACTION_ORE_DELIVERY:
		ao = take_ore_delivery(gs, dwarf_num);
		break;
	case ACTION_FAMILY_LIFE:
		ao = take_family_life(gs, dwarf_num);
		break;
	case ACTION_ORE_TRADING:
		ao = take_ore_trading(gs, dwarf_num);
		break;
	case ACTION_ADVENTURE:
		ao = take_adventure(gs, dwarf_num);
		break;
	case ACTION_RUBY_DELIVERY:
		ao = take_ruby_delivery(gs, dwarf_num);
		break;
	default:
		printf("Error: user interface for the action not implemented\n");
	}
	return ao;
}

void rollback_to(game_state *gs, const command_record *cmd) {
	printf("rolling back to %p\n", cmd);
	printf("tail is now: %p\n", gs->log.tail);
	while (gs->log.tail != cmd) {
		printf("calling caverna_rollback...\n");
		caverna_rollback(gs);
	}
}

void crash(game_state *gs) {
	printf("ERROR: %s\n", caverna_strerror(gs));
	exit(1);
}

static void show_tile_details(const player_state *player, int x, int y) {
	const tile_state *top = caverna_get_top_tile(player->board, x, y);

	printf("Details for the top tile at coordinates %c%d:\n", 'A'+y, x+1);
	printf("    Type:       %s (%d)\n",
	    caverna_get_tile_name(top->type),
	    top->type
	);
	printf("    Direction:  %d\n", top->dir);
	printf("    Rounds:     %d\n", top->rounds);
	printf("\n");
	printf("Show tile contents?\n");
	if (!get_yesno()) return;
	printf("Tile contents:\n");
	printf("    Stables:    %d\n", top->stable);
	printf("    Dog:        %d\n", top->dog);
	printf("    Sheep:      %d\n", top->sheep);
	printf("    Donkey:     %d\n", top->donkey);
	printf("    Boar:       %d\n", top->boar);
	printf("    Cattle:     %d\n", top->cattle);
	printf("    Grain:      %d\n", top->grain);
	printf("    Vegetable:  %d\n", top->vegetable);
	if (top->reward[0] != RESOURCE_NONE) {
		printf("    REWARD:     %d %s\n",
		    top->reward[1],
		    caverna_get_resource_name(top->reward[0])
		);
	}
	printf("\n");
	printf("Press enter to continue\n");
	get_yesno();
}

int get_dwarf_num(const player_state *player, int action_type) {
        int next_dwarf = -1; // Next unemployed dwarf
        int next_armed = -1; // Next unemployed, but armed dwarf
	int num_armed = 0;
        for (int i = 0; i < player->dwarfs; i++) {
                // Skip, if employed
                if (player->locations[i] != ACTION_NONE) continue;

                if (next_dwarf == -1) {
                        next_dwarf = i;
                }
                if (player->weapons[i] > 0) {
			num_armed++;
			if (next_armed == -1) {
	                        next_armed = i;
        	        }
		}
        }

	int ask_order = 0;
	switch(action_type) {
	case ACTION_LOGGING:
	case ACTION_ORE_MINE_CONSTRUCTION:
	case ACTION_BLACKSMITHING:
	case ACTION_ADVENTURE:
		ask_order = 1;
		break;
	default:
		break;
	}
	printf("Asking order: %d\n", ask_order);

	if (ask_order) {
		if (next_armed == -1) {
			printf(
			    "Player has no armed Dwarfs, so playing "
			    "a Dwarf out of order has no effect.\n"
			);
			ask_order = 0;
		}
		if (player->ruby == 0) {
			printf(
			    "Player has no Rubies, so cannot play "
			    "an armed Dwarf out of order.\n"
			);
			ask_order = 0;
		}
		if ((next_dwarf == next_armed) && (num_armed == 1)) {
			// This is practically the last Dwarf left,
			// so no point in asking.
			printf(
			    "Player has 1 Dwarf left, so it is "
			    "impossible to play a Dwarf out of order.\n"
			);
			ask_order = 0;
		}
	}

	if (ask_order) {
		printf("Play an armed Dwarf out of order?\n");
		ask_order = get_yesno();
	}

	while (ask_order) {
		printf("Dwarfs:\n");
		for (int i = 0; i < player->dwarfs; i++) {
			int location = player->locations[i];
			int occupied = location != ACTION_NONE;
			int weapon = player->weapons[i];
			int is_next = next_dwarf == i;
			if ((occupied) && (weapon == 0)) {
				printf(
				    "%d. (at %s)\n",
				    i+1, caverna_get_action_name(location)
				);
			} else if (occupied) {
				printf(
				    "%d. (at %s, strength %d Weapon)\n",
				    i+1, caverna_get_action_name(location),
				    weapon
				);
			} else if (weapon == 0) {
				printf(
				    "%d. Free, no Weapon%s.\n",
				    i+1,
				    is_next ? " (next in order)" : ""
				);
			} else {
				printf(
				    "%d. Free, strength %d Weapon%s.\n",
				    i+1, weapon,
				    is_next ? " (next in order)" : ""
				);
			}
		}
		int dwarf_num = -1;
		int success = get_number(&dwarf_num);

		if (!success) {
			printf("Please enter a number\n");
			continue;
		}
		dwarf_num--; // Make it zero-based.

		if ((dwarf_num < 0) || (dwarf_num >= player->dwarfs)) {
			printf(
			    "Please enter a number between 1-%d.\n",
			    player->dwarfs
			);
			continue;
		}

		if (player->locations[dwarf_num] != ACTION_NONE) {
			printf("That Dwarf is already occupied.\n");
			continue;
		}
		next_dwarf = dwarf_num;
		ask_order = 0;
	}

	return next_dwarf;
}

static void list_conversions(const player_state *player, const int *types, int num_types) {
	printf("%-25s       %-25s\n",
		"Input", "Output"
	);
	for (int i = 0; i < num_types; i++) {
		int type = types[i];

		const char *input_desc = NULL;
		const char *output_desc = NULL;
		int can_convert = caverna_can_convert(player, type, 1);
		caverna_get_conversion_description(type, &input_desc, &output_desc);
		printf("%2d:  %-24s   %2d:  %-24s%s\n",
		    i+1, input_desc, i+1, output_desc,
		    can_convert ? "" : " [unavailable]"
		);
	}
}

static void convert_resources(game_state *gs, const player_state *player) {
	int num_types;
	const int *types = caverna_get_all_conversion_types(&num_types);

	// 1. Print available conversions
	list_conversions(player, types, num_types);
	do {
		print_status(player);

		printf("Enter a conversion number, \".\" to finish, or \"l\" to re-list.\n");
		char buffer[0x100];
		int len = get_line(buffer, sizeof(buffer));
		len = trim(buffer, len);
		if (len == 0) continue;

		if (strcmp(buffer, ".") == 0) {
			break;
		} else if (strcmp(buffer, "l") == 0) {
			list_conversions(player, types, num_types);
			continue;
		}
		// Otherwise expect a conversion number
		int type_num = -1;
		int success = parse_int_between(&type_num, buffer, 1, num_types);
		if (!success) {
			printf(
			    "Error: not a number, or not between %d-%d\n",
			    1, num_types
			);
			continue;
		}
		// Get the conversion type
		int type = types[type_num-1];

		// Check it can be done
		if (!caverna_can_convert(player, type, 1)) {
			printf("Error: that conversion is not possible\n");
			continue;
		}

		// If a Ruby-to-Tile conversion, ask placement
		if (caverna_is_ruby2tile_conversion(type)) {
			print_board(player->board);
			tile_placement placement;
			printf("Enter coordinates for the single-tile:\n");
        	        success = get_tile_placement1(&placement);
	                if (!success) {
	                        //if (get_abort()) return 0;
        	                printf("Error: Invalid coordinates\n");
                	        continue;
			}
			success = caverna_convert_ruby_to_tile(
			    gs, type, &placement);
                } else {
			// Ordinary resource conversion
			success = caverna_convert_resources(gs, type, 1);
		}
		if (!success) {
			printf("Error: %s\n", caverna_strerror(gs));
		}

	} while(1);
}

void list_resetting_actions(const game_state *gs) {
	printf("Actions which will be reset at the beginning of the next round:\n");
	for (int i = 0; i < gs->num_actions; i++) {
		// For convenience
		const action_space *aspace = &gs->actions[i];
		if (aspace->counter >= 6) {
			printf("%d. %s (counter: %d)%s\n",
			    i+1,
			    caverna_get_action_name(aspace->type),
			    aspace->counter,
			    aspace->has_ruby ? " [has Ruby]" : ""
			);
		}
	}
}

void retain_resources(game_state *gs, const player_state *player) {
	do {
		list_resetting_actions(gs);
		int number;
		int success = get_number_between(&number, 1, gs->num_actions);
                if (!success) break;

		const action_space *aspace = &gs->actions[number-1];
		if (aspace->counter < 6) {
			printf("ERROR: That action will not reset.\n");
			continue;
		}
		if (aspace->has_ruby) {
			printf("ERROR: That action has a Ruby already.\n");
			continue;
		}
		success = caverna_put_ruby_on_action(gs, aspace->type);
		if (!success) {
			printf("ERROR: %s\n", caverna_strerror(gs));
			continue;
		}
	} while(1);
}


void do_feeding(game_state *gs) {
	while (gs->phase == PHASE_FEED) {
		// For convenience
		int cur_player = gs->cur_player;
		const player_state *player = &gs->players[cur_player];

		// Reset family_feeding struct
		family_feeding feeding;
		feeding.food = 0;
		feeding.working_cave_effect = 0;

		printf("Feeding phase: player %d turn.\n", cur_player);

		// Compute feeding costs

		int dwarf_cost = 0;
		if (gs->harvest == HARVEST_NONE_FEED_1FOOD) {
			dwarf_cost = 1;
		} else {
			dwarf_cost = 2;
		}
		int cost = (player->dwarfs*dwarf_cost)
		    + (player->children*1);

		// Apply tile effects
		int has_mining_cave
		    = caverna_has_player_tile(player, TILE_MINING_CAVE);

		int has_working_cave
		    = caverna_has_player_tile(player, TILE_WORKING_CAVE);

		// Mining cave effect
		if (has_mining_cave) {
			cost -= caverna_num_donkeys_in_ore_mines(player);
		}

		// Working cave effect
		if (has_working_cave) {
			if ( (player->wood >= 1)
			    || (player->stone >= 1)
			    || (player->ore >= 2) )
			{
				printf("Feeding costs: %d-%d Food\n",
				    cost-dwarf_cost, cost);

				int choice = get_choice(
				    "You have Working cave. Feed exactly 1 Dwarf "
				    "with (a) 1 Wood, (b) 1 Stone, or with (c) 2 Ore?",
				    3
				);
				int effect = 0;
				switch(choice) {
				case 0:
					effect = WORKING_CAVE_FEED_1WOOD;
					break;
				case 1:
					effect = WORKING_CAVE_FEED_1STONE;
					break;
				case 2:
					effect = WORKING_CAVE_FEED_2ORE;
					break;
				}
				feeding.working_cave_effect = effect;
				if (effect) {
					cost -= dwarf_cost;
				}
			} else {
				printf(
				    "Cannot use Working cave: not enough "
				    "Wood, Stone, or Ore\n"
				);
			}
		} else {
			printf("Feeding costs: %d Food\n", cost);
		}

		// Allow the player to convert resources first.
		convert_resources(gs, player);

		printf("You have %d Food. How many is used to feed your family?\n",
		    player->food);
		int success = get_number(&feeding.food);
		if (!success) {
			printf("Error: not an integer\n");
			continue;
		}
		if (feeding.food < 0) {
			printf("Error: invalid number (negative integer)\n");
			continue;
		}
		if (feeding.food > player->food) {
			printf("Error: You do not have that much Food!\n");
			continue;
		}
		if (feeding.food > cost) {
			printf("Error: too much Food\n");
			continue;
		}
		if (feeding.food < cost) {
			printf(
			    "This will result in %d begging markers. "
			    "Are you sure to continue?\n",
			    cost-feeding.food
			);
			if (!get_yesno()) continue;
		}

		// All good. Execute feeding
		success = caverna_feed(gs, &feeding);
		if (!success) {
			printf("Feeding failed. Error message:\n");
			printf("%s\n", caverna_strerror(gs));
		}
	}
}

void list_breedable(const player_state *player) {
	if (player->sheep >= 2) {
		printf("1. Sheep (%s)\n",
		    player->newborn_sheep ? "already bred" : "breedable");
	} else {
		printf("1. Sheep (unbreedable)\n");
	}

	if (player->donkey >= 2) {
		printf("2. Donkey (%s)\n",
		    player->newborn_donkey ? "already bred" : "breedable");
	} else {
		printf("2. Donkey (unbreedable)\n");
	}

	if (player->boar >= 2) {
		printf("3. Boar (%s)\n",
		    player->newborn_boar ? "already bred" : "breedable");
	} else {
		printf("3. Boar (unbreedable)\n");
	}

	if (player->cattle >= 2) {
		printf("4. Cattle (%s)\n",
		    player->newborn_cattle ? "already bred" : "breedable");
	} else {
		printf("4. Cattle (unbreedable)\n");
	}
}

int parse_animal_name(const char *name) {
	if (strcmp(name, "sheep") == 0) return RESOURCE_SHEEP;
	else if (strcmp(name, "donkey") == 0) return RESOURCE_DONKEY;
	else if (strcmp(name, "boar") == 0) return RESOURCE_BOAR;
	else if (strcmp(name, "cattle") == 0) return RESOURCE_CATTLE;
	return RESOURCE_NONE;
}

int get_animal_type(int *type) {
	static int animal_types[4] = {
		RESOURCE_SHEEP,
		RESOURCE_DONKEY,
		RESOURCE_BOAR,
		RESOURCE_CATTLE
	};

	int number;
	printf("Enter a number between 1-4: ");
	int success = get_number_between(&number, 1, 4);
	if (!success) return 0;

	*type = animal_types[number-1];
	return 1;
}

int breed_animal(game_state *gs, const player_state *player) {
	list_breedable(player);
	int type;
	int success = get_animal_type(&type);
	if (!success) return 0;

	success = caverna_breed(gs, type);
	if (!success) {
		printf("ERROR: %s\n", caverna_strerror(gs));
		return 0;
	}

	return 1;
}

int unbreed_animal(game_state *gs, const player_state *player) {
	list_breedable(player);
	int type;
	int success = get_animal_type(&type);
	if (!success) return 0;

	success = caverna_unbreed(gs, type);
	if (!success) {
		printf("ERROR: %s\n", caverna_strerror(gs));
		return 0;
	}

	return 1;
}


void do_breeding(game_state *gs) {
	while (gs->phase == PHASE_BREED) {
		// For convenience
		int cur_player = gs->cur_player;
		const player_state *player = &gs->players[cur_player];

		print_board(player->board);
		print_status(player);
		print_newborns(player);

		printf("Round %-2d | Player #%d turn | Breeding phase\n",
		    gs->cur_round, cur_player);

		printf("Enter command\n");
		char buffer[0x100];
		int len = get_line(buffer, sizeof(buffer));
		len = trim(buffer, len);
		if (len == 0) continue;

		int x, y;
		int is_coordinates = parse_coordinates(&x, &y, buffer);

		if ((strcmp(buffer, "re") == 0)
		    || (strcmp(buffer, "rearrange") == 0))
		{
			// Rearrange animals
			printf("Rearranging animals...\n");
			int result = caverna_rearrange_animals(
			    (player_state *) player);
			printf("Rearranging %s.\n",
			    result ? "succeeded" : "failed");
			if (!result)
				printf("ERROR: %s\n", caverna_strerror(gs));
		}
		else if (strcmp(buffer, "place") == 0) {
			printf("Placing animals...\n");
			int result = caverna_place_animals(gs);
			printf("Animal placement %s.\n",
			    result ? "succeeded" : "failed");
			if (!result)
				printf("ERROR: %s\n", caverna_strerror(gs));
		}
		else if ((strcmp(buffer, "convert") == 0)
		    || (strcmp(buffer, "c") == 0))
		{
			convert_resources(gs, player);
		}
		else if (strcmp(buffer, "l") == 0) {
			list_breedable(player);
		}
		else if (strcmp(buffer, "breed") == 0) {
			breed_animal(gs, player);
		}
		else if (strcmp(buffer, "unbreed") == 0) {
			unbreed_animal(gs, player);
		}
		else if ((buffer[0] == '+') || (buffer[0] == '-')) {
			int sign = buffer[0];
			int type = parse_animal_name(&buffer[1]);
			if (type == RESOURCE_NONE) {
				printf("ERROR: invalid animal name: %s\n",
				    &buffer[1]);
				continue;
			}
			int success;
			if (sign == '+') {
				success = caverna_breed(gs, type);
			} else {
				success = caverna_unbreed(gs, type);
			}
			if (!success) {
				printf("ERROR: %s\n", caverna_strerror(gs));
				continue;
			}
		}
		else if (strcmp(buffer, "done") == 0) {
			int success = caverna_commit_breeding(gs);
			if (!success) {
				printf("ERROR: %s\n", caverna_strerror(gs));
				continue;
			}
		}
		else if (is_coordinates) {
			show_tile_details(player, x, y);
		}
		else {
			printf("ERROR: unknown command: %s\n", buffer);
			continue;
		}
	}
}



static void set_tile(player_state *player, int x, int y, int z, int type, int dir) {
	tile_state *tile = &player->board[(z*BOARD_LEVEL_SIZE)+(y*BOARD_WIDTH)+x];
	tile->type = type;
	tile->dir = dir;
}

static tile_state *get_tile(player_state *player, int x, int y, int z) {
	return &player->board[(z*BOARD_LEVEL_SIZE)+(y*BOARD_WIDTH)+x];
}

static void show_score(const player_state *player) {
	score_state score;
	caverna_get_score(&score, player);
	printf("Victory point distribution:\n");
	printf("   1 VP per Farm animal and Dog      %3d VP\n", score.animals);
	printf("   1 VP per Ruby                     %3d VP\n", score.ruby);
	printf("   1 VP per Dwarf                    %3d VP\n", score.dwarfs);
	printf("   1 VP per Gold                     %3d VP\n", score.gold);
	printf("  -2 VP per missing Farm animal:     % 3d VP\n", -score.missing_farm_animals);
	printf(" 1/2 VP per Grain                    %3d VP\n", score.grain);
        printf("   1 VP per Vegetable                %3d VP\n", score.vegetable);
        printf("  -1 VP per Unused space             % 3d VP\n", -score.unused_spaces);
        printf("  -3 VP per Begging marker           % 3d VP\n", -score.begging);
	printf("     VP for Furnishing tiles         %3d VP\n", score.furnishings);
	printf("     VP for Pastures                 %3d VP\n", score.pastures);
	printf("     VP for Mines                    %3d VP\n", score.mines);
	printf("     Furnishing tile bonuses         %3d VP\n", score.bonus);
	if (score.acquittance > 0) {
		printf("     Maximum acquittance             %3d VP\n", score.acquittance);
	}
	printf("-------------------------------------------------\n");
	printf("     Score                           %3d VP\n", score.total);
	printf("     Penalty                         % 3d VP\n", -score.penalty);
	printf("-------------------------------------------------\n");
	printf("     Total:                          %3d VP\n", score.total - score.penalty);
	printf("\n");
	printf("Press enter to continue\n");
	get_yesno();

}


static void setup_test(game_state *gs) {
	player_state *player = &gs->players[0];

	player->ruby = 3;
	player->ore = 8;
	player->stone = 8;
	player->wood = 8;
	player->weapons[1] = 14;
	player->boar = 0;
	player->cattle = 3;
	player->sheep = 3;

	player->dog = 4;

	gs->cur_round = 10;
	gs->num_actions += gs->cur_round;

	set_tile(player, 2, 2, 0, TILE_LARGE_PASTURE, DIRECTION_DOWN);
	set_tile(player, 2, 3, 0, TILE_LARGE_PASTURE, DIRECTION_UP);

	set_tile(player, 2, 4, 0, TILE_MEADOW, DIRECTION_NONE);
	get_tile(player, 2, 4, 0)->stable = 1;

	/*
	set_tile(player, 1, 4, 0, TILE_MEADOW, DIRECTION_NONE);
	get_tile(player, 1, 4, 0)->stable = 1;
	*/

	// Large pasture: capacity 4
	// Meadow with Stable: capacity 1
	// Meadow with Stable: capacity 1
	// Entry-level Dwelling: capacity 2
	// Total capacity without dogs: 8
	// Dogs: 2 -> capacity increment: 1 or 2
}

int main(void) {
	char buffer[0x100];
	printf("Caverna: The Cave Farmers.\n");
	printf("Digital conversion by Jani Hautamaki <jani.hautamaki@hotmail.com>\n");

	game_state *gs = NULL;
	gs = caverna_create();

	int num_players = 0;
	do {
		printf("Number of players?\n");
		int success = get_number(&num_players);
		if (!success) {
			num_players = 0;
			printf("Error: not a number\n");
			continue;
		}
		if ((num_players < 1) || (num_players > MAX_PLAYERS)) {
			num_players = 0;
			printf("Error: value must be within 1-7.\n");
			continue;
		}
	} while (num_players == 0);

	printf("Starting the game with %d players\n", num_players);
	caverna_start(gs, num_players);

	// TODO: This is temporary. Remove
	//setup_test(gs);

	command_record *previous_cmd = gs->log.tail;
	printf("previous_cmd set to log.tail: %p\n", gs->log.tail);

	while (1) {
		int success;
		if (caverna_beginning_of_round(gs)) {
			printf("Beginning a new round.\n");
			success = caverna_begin_round(gs);
			if (!success) crash(gs);
		}
		if (gs->phase == PHASE_FINISH_TURN) {
			printf("There are unplaced animals "
			    "or the arrangement is illegal\n");
			//exit(1);
		} else if (gs->phase == PHASE_BREED) {
			printf("Do breeding. Cannot take actions\n");
		} else if (gs->phase == PHASE_GAME_OVER) {
			printf("NOTE: The game has finished.\n");
		} else if (gs->phase != PHASE_WORK) {
			fprintf(stderr,
			    "Unexpected game phase: %d\n", gs->phase);
			exit(1);
		}

		// print available actions
		print_actions(gs);
		int player_num = caverna_get_cur_player(gs);
		if (player_num == -1) {
			printf("Which player to examine?\n");
			int success;
			do {
				printf("Enter a number between 0-%d\n",
				    gs->num_players-1);
				success = get_number_between(
				    &player_num, 0, gs->num_players-1);
			} while (!success);
		}
		int round_num = caverna_get_cur_round(gs);
		const player_state *player
		    = caverna_get_player(gs, player_num);

		render_board(player);
		//print_board(player->board);
		print_status(player);

		if (player->children > 0) {
			printf("(%d %s)\n",
			    player->children,
			    player->children == 1 ? "child" : "children"
			);
		}

		int next_dwarf = -1;
		int next_armed = -1; // nuissance
		get_next_dwarf(player, &next_dwarf, &next_armed);
		int next_weapon = player->weapons[next_dwarf];

		printf("Round %-2d | Player #%d turn | ",
		    round_num, player_num);

		if (gs->phase == PHASE_WORK) {
			printf("Dwarf %d/%d",
			    player->workers+1,
			    player->dwarfs
			);
			if (next_weapon > 0) {
				printf(" (with strength %d Weapon)", next_weapon);
			}
		} else {
			printf("Dwarf %d/%d [turn unfinished]",
			    player->workers,
			    player->dwarfs
			);
		}
		printf("\n");

		printf("Enter command\n");
		int len = get_line(buffer, sizeof(buffer));
		len = trim(buffer, len);
		if (len == 0) continue;

		int action_num;
		int is_number = to_int(buffer, &action_num);

		int x, y;
		int is_coordinates = parse_coordinates(&x, &y, buffer);

		if (starts_with(buffer, "//")) {
			// A Comment. Ignore.
			printf("Ignoring a comment.\n");
		} else if (strcmp(buffer, "q") == 0) {
			printf("Aborting game.\n");
			break;
		} else if (strcmp(buffer, "undo") == 0) {
			printf("Undoing the previous action\n");
			rollback_to(gs, previous_cmd);
		} else if ((strcmp(buffer, "dwarf") == 0)
		    || (strcmp(buffer, "l") == 0))
		{
			print_dwarfs(player);
		} else if ((strcmp(buffer, "convert") == 0)
		    || (strcmp(buffer, "c") == 0))
		{
			convert_resources(gs, player);
		} else if (strcmp(buffer, "place") == 0) {
			int result = caverna_place_animals(gs);
			printf("Animal placement %s.\n",
			    result ? "succeeded" : "failed");
		} else if ((strcmp(buffer, "rearrange") == 0)
		    || (strcmp(buffer, "re") == 0))
		{
			printf("Rearranging animals...");
			// TODO: needs non-const pointer!
			int result = caverna_rearrange_animals((player_state *) player);
			printf("Rearranging %s.\n",
			    result ? "succeeded" : "failed");
		} else if (strcmp(buffer, "retain") == 0) {
			retain_resources(gs, player);
		} else if (strcmp(buffer, "finish") == 0) {
			// Attempt to re-finish turn
			int success = caverna_finish_turn(gs);
			if (!success) {
				printf("ERROR: %s\n", caverna_strerror(gs));
			}
		} else if (strcmp(buffer, "score") == 0) {
			show_score(player);
		} else if (strcmp(buffer, "verify") == 0) {
			int success = caverna_verify_animal_arrangement(
			    gs, player);
			if (!success) {
				printf("ERROR: %s\n", caverna_strerror(gs));
			} else {
				printf("SUCCESS: Animal arrangement is "
				    "allowed by the rules.\n");
			}
		} else if (is_coordinates) {
			show_tile_details(player, x, y);
		} else if (is_number) {
			action_num--;
			if ((action_num < 0)
			    || (action_num >= gs->num_actions))
			{
				printf("Number outside of valid range\n");
				continue;
			}
			// Otherwise carry out the chosen action
			printf("Taking action #%d\n", action_num);
			const action_space *action = &gs->actions[action_num];
			int action_type = action->type;

			int dwarf_num
			    = get_dwarf_num(player, action_type);
			const action_orders *ao
			    = plan_action(gs, dwarf_num, action_num);
			if (ao == NULL) {
				printf("Failed to set parameters for the action\n");
				continue;
			}
			command_record *cmd = gs->log.tail;
			//int dwarf_num = player->workers; // TODO: kludge workaround
			if (!caverna_take_action(gs, dwarf_num, ao)) {
				free((void *) ao); // discard const qualifier
				printf("Failed to execute the action\n");
				printf("Error: %s\n", caverna_strerror(gs));
				continue;
			}
			free((void *) ao); // discard const qualifier
			printf("Execution action succeeded!\n");
			// Action succeeded. See if a new round needs starting
			previous_cmd = cmd;

			// This signals the next player, and checks
			// the animal arrangement. If there is excess
			// animals, false is returned
			printf("Player %d turn finished.\n", player_num);

			int success = caverna_finish_turn(gs);
			if (!success) {
				printf("ERROR: %s\n", caverna_strerror(gs));
			}


		} else {
			printf("Error: unknown command\n");
		}


		if (caverna_end_of_round(gs)) {
			printf("End of Round %d.\n", round_num);
			success = caverna_finish_round(gs);
			if (!success) crash(gs);
			switch(gs->harvest) {
			case HARVEST_NONE:
				printf("No harvest.\n");
				break;
			case HARVEST_NORMAL:
				printf("Normal harvest.\n");
				break;
			case HARVEST_NONE_FEED_1FOOD:
				printf("Pay 1 Food per Dwarf.\n");
				break;
			case HARVEST_WITH_PHASE_SKIP:
				printf(
				    "Harvest with either Field or Breeding "
				    "sub-phase skipped individually.\n");
				break;
			}
		}

		if (gs->phase == PHASE_HARVEST) {
			printf("Field sub-phase.\n");
			caverna_harvest(gs);
		}
		if (gs->phase == PHASE_FEED) {
			printf("Feeding sub-phase.\n");
			// run through all players
			do_feeding(gs);
		}
		if (gs->phase == PHASE_BREED) {
			printf("Breeding sub-phase.\n");
			do_breeding(gs);
		}

		if (gs->phase == PHASE_GROW) {
			printf("Growing up phase.\n");
			success = caverna_grow(gs);
			if (!success) crash(gs);

		}
		if (caverna_end_of_game(gs)) {
			printf("End of Game.\n");
			success = caverna_finish_game(gs);
			if (!success) crash(gs);
			printf("You may still explore your Home board.\n");
		}

	} // while
	// TODO: print scoring
	if (gs->num_players == 1) {
		show_score(&gs->players[0]);
	}

	printf("Game over.\n");
	// Compute final scores and declare winner

	caverna_free(gs);

	return 0;
}
