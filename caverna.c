#include <stdlib.h> // malloc, free
#include <stdio.h> // vsnprintf
#include <stdarg.h> // va_list, va_start, va_arg, va_end
#include <string.h> // memcpy

#include "caverna.h"

struct action_config {
	int type;
	const char *name;
	size_t orders_size;
};

typedef struct action_config action_config;

const action_config ACTIONS_CONFIG[] = {

	{ ACTION_DRIFT_MINING, "Drift mining", sizeof(drift_mining_orders) },
	{ ACTION_LOGGING, "Logging", sizeof(logging_orders) },
	{ ACTION_WOOD_GATHERING, "Wood gathering", sizeof(wood_gathering_orders) },

	{ ACTION_EXCAVATION, "Excavation", sizeof(excavation_orders) },
	{ ACTION_SUPPLIES, "Supplies", 0 }, // TODO
	{ ACTION_CLEARING, "Clearing", 0 }, // TODO

	{ ACTION_STARTING_PLAYER, "Starting player", 0 }, // TODO
	{ ACTION_ORE_MINING, "Ore mining", sizeof(ore_mining_orders), },
	{ ACTION_SUSTENANCE, "Sustenance", sizeof(sustenance_orders), },

	{ ACTION_RUBY_MINING, "Ruby mining", sizeof(ruby_mining_orders) },
	{ ACTION_HOUSEWORK, "Housework", sizeof(housework_orders) },
	{ ACTION_SLASH_AND_BURN, "Slash and burn",
	    sizeof(slash_and_burn_orders) },

	// In order of solo play action spaces
	{ ACTION_BLACKSMITHING, "Blacksmithing",
	    sizeof(blacksmithing_orders) },
	{ ACTION_SHEEP_FARMING, "Sheep farming",
	    sizeof(sheep_farming_orders) },
	{ ACTION_ORE_MINE_CONSTRUCTION, "Ore mine construction",
	    sizeof(ore_mine_construction_orders) },

	{ ACTION_WISH_FOR_CHILDREN, "Wish for children",
	    sizeof(wish_for_children_orders) },
	{ ACTION_DONKEY_FARMING, "Donkey farming",
	    sizeof(donkey_farming_orders) },
	{ ACTION_RUBY_MINE_CONSTRUCTION, "Ruby mine construction",
	    sizeof(ruby_mine_construction_orders) },

	{ ACTION_ORE_DELIVERY, "Ore delivery", sizeof(ore_delivery_orders) },
	{ ACTION_FAMILY_LIFE, "Family life", sizeof(family_life_orders) },
	{ ACTION_URGENT_WISH_FOR_CHILDREN, "Urgent wish for children",
	    sizeof(wish_for_children_orders) },

	{ ACTION_ORE_TRADING, "Ore trading", sizeof(ore_trading_orders) },
	{ ACTION_ADVENTURE, "Adventure", sizeof(adventure_orders) },
	{ ACTION_RUBY_DELIVERY, "Ruby delivery",
	    sizeof(ruby_delivery_orders) },

	{ ACTION_NONE, "Not available", 0 }
}; // const action_config[]

struct dwelling_tile_config {
	/** Dwelling tile type. */
	int type;
	/** Capacity for dwarfs (either 1 or 2). */
	int dwarf;
	/** Capacity for animals (either 0 or 2). */
	int animal;
};
typedef struct dwelling_tile_config dwelling_tile_config;

struct name_config {
	int id;
	const char *name;
};
typedef struct name_config name_config;

const name_config TILE_NAMES_CONFIG[] = {
	// Pseudo-tiles
	{ TILE_FOREST, "Forest" },
	{ TILE_MOUNTAIN, "Mountain" },
	{ TILE_INITIAL_DWELLING, "Entry-level dwelling" },
	{ TILE_BLOCKED, "Entry-level dwelling" },
	// Terraforming tiles
	{ TILE_CAVERN, "Cavern" },
	{ TILE_TUNNEL, "Tunnel" },
	{ TILE_FIELD, "Field" },
	{ TILE_MEADOW, "Meadow" },
	{ TILE_ORE_MINE, "Ore mine" },
	{ TILE_RUBY_MINE, "Ruby mine" },
	{ TILE_DEEP_TUNNEL, "Deep Tunnel" },
	{ TILE_SMALL_PASTURE, "Small Pasture" },
	{ TILE_LARGE_PASTURE, "Large Pasture" },

	// Furnishing tiles

	// Dwelling tiles
	{ TILE_DWELLING, "Dwelling" },
	{ TILE_SIMPLE_DWELLING_1, "Simple dwelling" },
	{ TILE_SIMPLE_DWELLING_2, "Simple dwelling" },
	{ TILE_MIXED_DWELLING, "Mixed dwelling" },
	{ TILE_COUPLE_DWELLING, "Couple dwelling" },
	{ TILE_ADDITIONAL_DWELLING, "Additional dwelling" },

	{ TILE_CUDDLE_ROOM, "Cuddle room" },
	{ TILE_BREAKFAST_ROOM, "Breakfast room" },
	{ TILE_STUBBLE_ROOM, "Stubble room" },
	{ TILE_WORK_ROOM, "Work room" },
	{ TILE_GUEST_ROOM, "Guest room" },
	{ TILE_OFFICE_ROOM, "Office room" },
	// Building materials rooms 1a
	{ TILE_CARPENTER, "Carpenter" },
	{ TILE_STONE_CARVER, "Stone carver" },
	{ TILE_BLACKSMITH, "Blacksmith" },
	{ TILE_MINER, "Miner" },
	{ TILE_BUILDER, "Builder" },
	{ TILE_TRADER, "Trader" },
	// Building materials rooms 1b
	{ TILE_WOOD_SUPPLIER, "Wood supplier" },
	{ TILE_STONE_SUPPLIER, "Stone supplier" },
	{ TILE_RUBY_SUPPLIER, "Ruby supplier" },
	{ TILE_DOG_SCHOOL, "Dog school" },
	{ TILE_QUARRY, "Quarry" },
	{ TILE_SEAM, "Seam" },
	// Building materials rooms 2
	{ TILE_SLAUGHTERING_CAVE, "Slaughtering cave" },
	{ TILE_COOKING_CAVE, "Cooking cave" },
	{ TILE_WORKING_CAVE, "Working cave" },
	{ TILE_MINING_CAVE, "Mining cave" },
	{ TILE_BREEDING_CAVE, "Breeding cave" },
	{ TILE_PEACEFUL_CAVE, "Peaceful cave" },
	// Parlors
	{ TILE_WEAVING_PARLOR, "Weaving parlor" },
	{ TILE_MILKING_PARLOR, "Milking parlor" },
	{ TILE_STATE_PARLOR, "State parlor" },
	{ TILE_HUNTING_PARLOR, "Hunting parlor" },
	{ TILE_BEER_PARLOR, "Beer parlor" },
	{ TILE_BLACKSMITHING_PARLOR, "Blacksmithing parlor" },
	// Storages
	{ TILE_STONE_STORAGE, "Stone storage" },
	{ TILE_ORE_STORAGE, "Ore storage" },
	{ TILE_SPARE_PART_STORAGE, "Spare part storage" },
	{ TILE_MAIN_STORAGE, "Main storage" },
	{ TILE_WEAPON_STORAGE, "Weapon storage" },
	{ TILE_SUPPLIES_STORAGE, "Supplies storage" },
	// Chambers
	{ TILE_BROOM_CHAMBER, "Broom chamber" },
	{ TILE_TREASURE_CHAMBER, "Treasure chamber" },
	{ TILE_FOOD_CHAMBER, "Food chamber" },
	{ TILE_PRAYER_CHAMBER, "Player chamber" },
	{ TILE_WRITING_CHAMBER, "Writing chamber" },
	{ TILE_FODDER_CHAMBER, "Fodder chamber" },
	// No tile
	{ TILE_NONE, "(No tile)"}
};

const name_config RESOURCE_NAMES_CONFIG[] = {
	{ RESOURCE_GRAIN, "Grain" },
	{ RESOURCE_VEGETABLE, "Vegetable" },
	{ RESOURCE_FOOD, "Food" },
	{ RESOURCE_GOLD, "Gold" },
	{ RESOURCE_STONE, "Stone" },
	{ RESOURCE_WOOD, "Wood" },
	{ RESOURCE_RUBY, "Ruby" },
	{ RESOURCE_ORE, "Ore" },
	{ RESOURCE_DOG, "Dog" },
	{ RESOURCE_SHEEP, "Sheep" },
	{ RESOURCE_BOAR, "Boar" },
	{ RESOURCE_DONKEY, "Donkey" },
	{ RESOURCE_CATTLE, "Cattle" },
	{ RESOURCE_NONE, "(None)" }
};

const int FARM_ANIMAL_TYPES[] = {
	RESOURCE_SHEEP,
	RESOURCE_DONKEY,
	RESOURCE_BOAR,
	RESOURCE_CATTLE
};

const name_config LOOT_NAMES_CONFIG[] = {
	// Level 1
	{ LOOT_INCREASE_WEAPONS, "Increase all weapons +1 after the Expedition" },
	{ LOOT_WOOD, "+1 Wood" },
	{ LOOT_DOG, "+1 Dog" },
	// Level 2
	{ LOOT_GRAIN, "+1 Grain" },
	{ LOOT_SHEEP, "+1 Sheep" },
	// Level 3
	{ LOOT_STONE, "+1 Stone" },
	{ LOOT_DONKEY, "+1 Donkey" },
	// Level 4
	{ LOOT_VEGETABLE, "+1 Vegetable" },
	{ LOOT_2ORE, "+2 Ore" },
	// Level 5
	{ LOOT_BOAR, "+1 Boar" },
	// Level 6
	{ LOOT_2GOLD, "+2 Gold" },
	// Level 7
	{ LOOT_FURNISH, "Furnish Cavern" },
	// Level 8
	{ LOOT_STABLE, "Build Stable" },
	// Level 9
	{ LOOT_TUNNEL, "Build Tunnel" },
	{ LOOT_SMALL_PASTURE, "Build Small Pasture" },
	// Level 10
	{ LOOT_CATTLE, "+1 Cattle" },
	{ LOOT_LARGE_PASTURE, "Build Large Pasture" },
	// Level 11
	{ LOOT_MEADOW, "Build a single-tile Meadow" },
	{ LOOT_DWELLING, "Furnish Dwelling" },
	// Level 12
	{ LOOT_FIELD, "Build a single-tile Field" },
	{ LOOT_SOW, "Sow" },
	// Level 13
	// (Nothing)
	// Level 14
	{ LOOT_CAVERN, "Build a single-tile Cavern" },
	{ LOOT_BREED2, "Breed up to 2 Farm animals" },

	{ LOOT_NONE, "(None)" }
};

const int LOOT_ITEMS[] = {
	LOOT_NONE,      // 0
	// Level 1
	LOOT_INCREASE_WEAPONS, // 1
	LOOT_WOOD,      // 2
	LOOT_DOG,       // 3
	// Level 2
	LOOT_GRAIN,     // 4
	LOOT_SHEEP,     // 5
	// Level 3
	LOOT_STONE,     // 6
	LOOT_DONKEY,    // 7
	// Level 4
	LOOT_VEGETABLE, // 8
	LOOT_2ORE,      // 9
	// Level 5
	LOOT_BOAR,      // 10
	 // Level 6
	LOOT_2GOLD,     // 11
	// Level 7
	LOOT_FURNISH,   // 12
	// Level 8
	LOOT_STABLE,    // 13
	// Level 9
	LOOT_TUNNEL,    // 14
	LOOT_SMALL_PASTURE, // 15
	// Level 10
	LOOT_CATTLE,    // 17
	LOOT_LARGE_PASTURE, // 18
	// Level 11
	LOOT_MEADOW,    // 19
	LOOT_DWELLING,  // 19
	// Level 12
	LOOT_FIELD,     // 20
	LOOT_SOW,       // 21
	// Level 13
	// (Nothing)
	// Level 14
	LOOT_CAVERN,    // 22
	LOOT_BREED2     // 23
};

/** Maximum index of LOOT_ITEMS array by Weapon strength. */
const int LOOT_UPTO[] = {
	0,  // Strength 0
	3,  // Strength 1
	5,  // Strength 2
	7,  // Strength 3
	9,  // Strength 4
	10, // Strength 5
	11, // Strength 6
	12, // Strength 7
	13, // Strength 8
	15, // Strength 9
	17, // Strength 10
	19, // Strength 11
	21, // Strength 12
	21, // Strength 13
	23  // Strength 14
};

struct furnishing_config {
	/** Tile type */
	int type;

	/** Victory points, if static. */
	int vp;

	/** Price, expressed as pairs (resource_type, cost). */
	int price[3*2];

	/** Text description of the tile. */
	const char *description;
};
typedef struct furnishing_config furnishing_config;

// Breaking indentation rules here a bit for brewity..
const furnishing_config FURNISHINGS_CONFIG[] = {
// Dwellings
{
	TILE_DWELLING,
	3,
	{ RESOURCE_WOOD, 4, RESOURCE_STONE, 3 },
	"Room for 1 Dwarf"
}, {
	TILE_SIMPLE_DWELLING_1,
	0,
	{ RESOURCE_WOOD, 4, RESOURCE_STONE, 2 },
	"Room for 1 Dwarf"
}, {
	TILE_SIMPLE_DWELLING_2,
	0,
	{ RESOURCE_WOOD, 3, RESOURCE_STONE, 3 },
	"Room for 1 Dwarf"
}, {
	TILE_MIXED_DWELLING,
	4,
	{ RESOURCE_WOOD, 5, RESOURCE_STONE, 4 },
	"Roomf or 1 Dwarf and 1 pair of animals"
}, {
	TILE_COUPLE_DWELLING,
	5,
	{ RESOURCE_WOOD, 8, RESOURCE_STONE, 5 },
	"Room for 2 Dwarfs",
}, {
	TILE_ADDITIONAL_DWELLING,
	5,
	{ RESOURCE_WOOD, 4, RESOURCE_STONE, 3 },
	"Room for the sixth Dwarf only"
},
// Rooms
{
	TILE_CUDDLE_ROOM,
	2,
	{ RESOURCE_WOOD, 2 },
	"Room for as many Sheeps as you have Dwarfs"
}, {
	TILE_BREAKFAST_ROOM,
	0,
	{ RESOURCE_WOOD, 1 },
	"Room for up to 3 Cows"
}, {
	TILE_STUBBLE_ROOM,
	1,
	{ RESOURCE_WOOD, 1, RESOURCE_ORE, 1 },
	"you may keep 1 Farm animal on each empty Field"
}, {
	TILE_WORK_ROOM,
	2,
	{ RESOURCE_STONE, 1 },
	"you may furnish Tunnel and Deep Tunnel"
}, {
	TILE_GUEST_ROOM,
	0,
	{ RESOURCE_WOOD, 1, RESOURCE_STONE, 1 },
	"\"either ... or\" becomes \"and/or\" for you"
}, {
	TILE_OFFICE_ROOM,
	0,
	{ RESOURCE_STONE, 1 },
	"twin tiles may overhang; every time you do so: +2 Gold"
},
// Building Materials Rooms 1
{
	TILE_CARPENTER,
	0,
	{ RESOURCE_STONE, 1 },
	"every time you furnish a Cavern or build Fences, "
	"you receive a discount of 1 Wood"
}, {
	TILE_STONE_CARVER,
	1,
	{ RESOURCE_WOOD, 1 },
	"(immediately +2 Stone) every time you furnish a Cavern "
	"or build a Stable, you receive a discount of 1 Stone"
}, {
	TILE_BLACKSMITH,
	3,
	{ RESOURCE_WOOD, 1, RESOURCE_STONE, 2 },
	"(immediately +2 Ore) every time you forge a Weapon, "
	"you receive a discount of 2 Ore"
}, {
	TILE_MINER,
	3,
	{ RESOURCE_WOOD, 1, RESOURCE_STONE, 1 },
	"at the beginning of each round: +1 Ore per Donkey in an Ore mine"
}, {
	TILE_BUILDER,
	2,
	{ RESOURCE_STONE, 1 },
	"you may replace 1 Wood with 1 Ore and/or 1 Stone with 1 Ore "
	"when paying for a Furnishing tile"
}, {
	TILE_TRADER,
	2,
	{ RESOURCE_WOOD, 1 },
	"at any time before scoring: 2 Gold -> 1 Wood, 1 Ore, and 1 Stone"
},
// Building Materials rooms 2
{	TILE_WOOD_SUPPLIER,
	2,
	{ RESOURCE_STONE, 1 },
	"at the beginning of the next 7 rounds: +1 Wood"
}, {
	TILE_STONE_SUPPLIER,
	1,
	{ RESOURCE_WOOD, 1 },
	"at the beginning of the next 5 rounds: +1 Stone"
}, {
	TILE_RUBY_SUPPLIER,
	2,
	{ RESOURCE_WOOD, 2, RESOURCE_STONE, 2 },
	"at the beginning of he next 4 rounds: +1 Ruby"
}, {
	TILE_DOG_SCHOOL,
	0,
	{ RESOURCE_NONE, 0 },
	"for each new Dog: +1 Wood"
}, {
	TILE_QUARRY,
	2,
	{ RESOURCE_WOOD, 1 },
	"for each newborn Sheep: +1 Stone"
}, {
	TILE_SEAM,
	1,
	{ RESOURCE_WOOD, 2 },
	"for each new Stone: +1 Ore"
},
// Food furnishings
{
	TILE_SLAUGHTERING_CAVE,
	2,
	{ RESOURCE_WOOD, 2, RESOURCE_STONE, 2 },
	"for each Farm animal that you convert into Food: +1 Food"
}, {
	TILE_COOKING_CAVE,
	2,
	{ RESOURCE_STONE, 1 },
	"at any time: 1 Vegetable and 1 Grain -> +5 Food"
}, {
	TILE_WORKING_CAVE,
	2,
	{ RESOURCE_WOOD, 1, RESOURCE_STONE, 1 },
	"you may feed exactly 1 Dwarf with 1 Wood / 1 Stone / 2 Ore"
}, {
	TILE_MINING_CAVE,
	2,
	{ RESOURCE_WOOD, 3, RESOURCE_STONE, 2 },
	"reduce feeding costs by 1 Food per Donkey in a Mine"
}, {
	TILE_BREEDING_CAVE,
	2,
	{ RESOURCE_GRAIN, 1, RESOURCE_STONE, 1 },
	"for 1/2/3/4 newborn animals: +1/2/3/5 Food"
}, {
	TILE_PEACEFUL_CAVE,
	2,
	{ RESOURCE_WOOD, 2, RESOURCE_STONE, 2 },
	"you may trade your Weapons for Food at a 1:1 ratio "
	"according to their strength",
},
// Parlols
{
	TILE_WEAVING_PARLOR,
	0,
	{ RESOURCE_WOOD, 2, RESOURCE_STONE, 1 },
	"(immediately +1 Food per Sheep) scoring: +1 VP per 2 Sheep"
}, {
	TILE_MILKING_PARLOR,
	0,
	{ RESOURCE_WOOD, 2, RESOURCE_STONE, 2 },
	"(immediately +1 Food per Cow) scoring: +1 VP per Cow"
}, {
	TILE_STATE_PARLOR,
	0,
	{ RESOURCE_STONE, 3, RESOURCE_GOLD, 5 },
	"for each adjacent Dwelling, receive: (i) now +2 Food, (ii) when scoring +4 VP"
}, {
	TILE_HUNTING_PARLOR,
	1,
	{ RESOURCE_ORE, 2 },
	"at any time before scoring: 2 Cow -> +2 Gold, +2 Food"
}, {
	TILE_BEER_PARLOR,
	3,
	{ RESOURCE_WOOD, 2 },
	"at any time before scoring: 2 Grain -> +3 Gold / +4 Food"
}, {
	TILE_BLACKSMITHING_PARLOR,
	2,
	{ RESOURCE_ORE, 3 },
	"at any time before scoring: 1 Ruby and 1 Ore -> +2 Gold, +1 Food"
},
// Victory point rooms
{
	TILE_STONE_STORAGE,
	0,
	{ RESOURCE_WOOD, 1, RESOURCE_ORE, 1 },
	"scoring: +1 VP per 1 Stone"
}, {
	TILE_ORE_STORAGE,
	0,
	{ RESOURCE_WOOD, 1, RESOURCE_STONE, 2 },
	"scoring: +1 VP per 2 Ore"
}, {
	TILE_SPARE_PART_STORAGE,
	0,
	{ RESOURCE_WOOD, 2 },
	"at any time before scoring: 1 Wood, 1 Stone, and 1 Ore -> +2 Gold"
}, {
	TILE_MAIN_STORAGE,
	0,
	{ RESOURCE_WOOD, 2, RESOURCE_STONE, 1 },
	"scoring: +2 VP per scoring furnishing tile"
}, {
	TILE_WEAPON_STORAGE,
	0,
	{ RESOURCE_WOOD, 3, RESOURCE_STONE, 2 },
	"scoring: +3 VP per Dwarf with a Weapon"
}, {
	TILE_SUPPLIES_STORAGE,
	0,
	{ RESOURCE_FOOD, 3, RESOURCE_WOOD, 1 },
	"scoring: +8 VP if all your Dwarfs that are in play have a Weapon"
},
// Chambers
{
	TILE_BROOM_CHAMBER,
	0,
	{ RESOURCE_WOOD, 1 },
	"scoring: +5 VP for 5 Dwarfs, or +10 VP for 6 Dwarfs"
}, {
	TILE_TREASURE_CHAMBER,
	0,
	{ RESOURCE_WOOD, 1, RESOURCE_STONE, 1 },
	"scoring: +1 VP per Ore"
}, {
	TILE_FOOD_CHAMBER,
	0,
	{ RESOURCE_WOOD, 2, RESOURCE_VEGETABLE, 2 },
	"scoring: +2 VP per 1 Vegetable and 1 Grain"
}, {
	TILE_PRAYER_CHAMBER,
	0,
	{ RESOURCE_WOOD, 2 },
	"scoring: +8 VP if none of your Dwarfs has a Weapon when scoring this tile"
},{
	TILE_WRITING_CHAMBER,
	0,
	{ RESOURCE_STONE, 2 },
	"prevents up to 7 negative points"
}, {
	TILE_FODDER_CHAMBER,
	0,
	{ RESOURCE_GRAIN, 2, RESOURCE_STONE, 1 },
	"scoring: +1 VP per 3 Farm animals"
}
// End furnishing tiles
};

/** All funrishing tiles used in the Full game. */
const int FURNISHING_TILES[] = {
	// Dwellings
	TILE_DWELLING,
	TILE_SIMPLE_DWELLING_1,
	TILE_SIMPLE_DWELLING_2,
	TILE_MIXED_DWELLING,
	TILE_COUPLE_DWELLING,
	TILE_ADDITIONAL_DWELLING,
	// Special rooms
	TILE_CUDDLE_ROOM,
	TILE_BREAKFAST_ROOM,
	TILE_STUBBLE_ROOM,
	TILE_WORK_ROOM,
	TILE_GUEST_ROOM,
	TILE_OFFICE_ROOM,
	// Building materials rooms 1a
	TILE_CARPENTER,
	TILE_STONE_CARVER,
	TILE_BLACKSMITH,
	TILE_MINER,
	TILE_BUILDER,
	TILE_TRADER,
	// Building materials rooms 1b
	TILE_WOOD_SUPPLIER,
	TILE_STONE_SUPPLIER,
	TILE_RUBY_SUPPLIER,
	TILE_DOG_SCHOOL,
	TILE_QUARRY,
	TILE_SEAM,
	// Building materials rooms 2
	TILE_SLAUGHTERING_CAVE,
	TILE_COOKING_CAVE,
	TILE_WORKING_CAVE,
	TILE_MINING_CAVE,
	TILE_BREEDING_CAVE,
	TILE_PEACEFUL_CAVE,
	// Parlors
	TILE_WEAVING_PARLOR,
	TILE_MILKING_PARLOR,
	TILE_STATE_PARLOR,
	TILE_HUNTING_PARLOR,
	TILE_BEER_PARLOR,
	TILE_BLACKSMITHING_PARLOR,
	// Storages
	TILE_STONE_STORAGE,
	TILE_ORE_STORAGE,
	TILE_SPARE_PART_STORAGE,
	TILE_MAIN_STORAGE,
	TILE_WEAPON_STORAGE,
	TILE_SUPPLIES_STORAGE,
	// Chambers
	TILE_BROOM_CHAMBER,
	TILE_TREASURE_CHAMBER,
	TILE_FOOD_CHAMBER,
	TILE_PRAYER_CHAMBER,
	TILE_WRITING_CHAMBER,
	TILE_FODDER_CHAMBER
};

const int FURNISHING_TILES_INTRO[] = {
	// Dwellings
	TILE_DWELLING,
	TILE_SIMPLE_DWELLING_1,
	TILE_SIMPLE_DWELLING_2,
	// Special rooms
	TILE_CUDDLE_ROOM,
	TILE_BREAKFAST_ROOM,
	TILE_STUBBLE_ROOM,
	// Building materials rooms 1a
	TILE_CARPENTER,
	TILE_STONE_CARVER,
	TILE_BLACKSMITH,
	// Building materials rooms 1n
	TILE_WOOD_SUPPLIER,
	TILE_STONE_SUPPLIER,
	TILE_RUBY_SUPPLIER,
	// Building materials rooms 2
	TILE_SLAUGHTERING_CAVE,
	TILE_COOKING_CAVE,
	TILE_WORKING_CAVE,
	// Parlors
	TILE_WEAVING_PARLOR,
	TILE_MILKING_PARLOR,
	TILE_HUNTING_PARLOR,
	TILE_BEER_PARLOR,
	// Storages
	TILE_STONE_STORAGE,
	TILE_ORE_STORAGE,
	TILE_MAIN_STORAGE,
	TILE_WEAPON_STORAGE,
	// Chambers
	TILE_TREASURE_CHAMBER,
	TILE_FOOD_CHAMBER,
	TILE_WRITING_CHAMBER,
	TILE_FODDER_CHAMBER
};

struct conversion_config {
	/** Conversion type */
	int type;

	/** Whether the conversion is special */
	int is_special;

	/** Description of required resources, if non-common conversion. */
	const char *input_desc;

	/** Description of produced resources, if non-common conversion. */
	const char *output_desc;

	/** Requires resources */
	int input[3*2];

	/** Produced resoures */
	int output[3*2];

	/** Required Furnishing tile, or TILE_NONE. */
	int tile_type;
};
typedef struct conversion_config conversion_config;

const conversion_config CONVERSIONS_CONFIG[] = {
{
	CONV_SHEEP_TO_FOOD, 0,
	"1 Sheep", "1 Food",
	{RESOURCE_SHEEP, 1}, {RESOURCE_FOOD, 1}
}, {
	CONV_GRAIN_TO_FOOD, 0,
	"1 Grain", "1 Food",
	{RESOURCE_GRAIN, 1}, {RESOURCE_FOOD, 1}
}, {
	CONV_DONKEY_TO_FOOD, 1,
	"1 Donkey", "1.5 Food (rounded down)",
	{RESOURCE_NONE, 0}, {RESOURCE_NONE, 0}
}, {
	CONV_BOAR_TO_FOOD, 0,
	"1 Boar", "2 Food",
	{RESOURCE_BOAR, 1}, {RESOURCE_FOOD, 2}
}, {
	CONV_VEGETABLE_TO_FOOD, 0,
	"1 Vegetable", "2 Food",
	{RESOURCE_VEGETABLE, 1}, {RESOURCE_FOOD, 2}
}, {
	CONV_RUBY_TO_FOOD, 0,
	"1 Ruby", "2 Food",
	{RESOURCE_RUBY, 1}, {RESOURCE_FOOD, 2}
}, {
	CONV_CATTLE_TO_FOOD, 0,
	"1 Cattle", "3 Food",
	{RESOURCE_CATTLE, 1}, {RESOURCE_FOOD, 3}
}, {
	CONV_GOLD_TO_FOOD, 1,
	"N+1 Gold", "N Food",
	{RESOURCE_NONE, 0}, {RESOURCE_NONE, 0}
},
	// ruby-to-yyyy conversions
{
	CONV_RUBY_TO_DOG, 0,
	"1 Ruby", "1 Dog",
	{RESOURCE_RUBY, 1}, {RESOURCE_DOG, 1}
}, {
	CONV_RUBY_TO_GRAIN, 0,
	"1 Ruby", "1 Grain",
	{RESOURCE_RUBY, 1}, {RESOURCE_GRAIN, 1}
}, {
	CONV_RUBY_TO_VEGETABLE, 0,
	"1 Ruby", "1 Vegetable",
	{RESOURCE_RUBY, 1}, {RESOURCE_VEGETABLE, 1}
}, {
	CONV_RUBY_TO_SHEEP, 0,
	"1 Ruby", "1 Sheep",
	{RESOURCE_RUBY, 1}, {RESOURCE_SHEEP, 1}
}, {
	CONV_RUBY_TO_WOOD, 0,
	"1 Ruby", "1 Wood",
	{RESOURCE_RUBY, 1}, {RESOURCE_WOOD, 1}
}, {
	CONV_RUBY_TO_DONKEY, 0,
	"1 Ruby", "1 Donkey",
	{RESOURCE_RUBY, 1}, {RESOURCE_DONKEY, 1}
}, {
	CONV_RUBY_TO_STONE, 0,
	"1 Ruby", "1 Stone",
	{RESOURCE_RUBY, 1}, {RESOURCE_STONE, 1}
}, {
	CONV_RUBY_TO_BOAR, 0,
	"1 Ruby", "1 Boar",
	{RESOURCE_RUBY, 1}, {RESOURCE_BOAR, 1}
}, {
	CONV_RUBY_TO_ORE, 0,
	"1 Ruby", "1 Ore",
	{RESOURCE_RUBY, 1}, {RESOURCE_ORE, 1},
},
	// Special cost Ruby conversion
{
	CONV_RUBY_TO_CATTLE, 0,
	"1 Ruby + 1 Food", "1 Cattle",
	{RESOURCE_RUBY, 1, RESOURCE_FOOD, 1}, {RESOURCE_CATTLE, 1}
},
	// Ruby-to-tile conversions
{
	CONV_RUBY_TO_MEADOW, 1,
	"1 Ruby", "1 Meadow tile",
	{RESOURCE_NONE, 0}, {RESOURCE_NONE, 0}
}, {
	CONV_RUBY_TO_FIELD, 1,
	"1 Ruby", "1 Field tile",
	{RESOURCE_NONE, 0}, {RESOURCE_NONE, 0}
}, {
	CONV_RUBY_TO_TUNNEL, 1,
	"1 Ruby", "1 Tunnel tile",
	{RESOURCE_NONE, 0}, {RESOURCE_NONE, 0}
}, {
	CONV_RUBY_TO_CAVERN, 1,
	"2 Ruby", "1 Cavern tile",
	{RESOURCE_NONE, 0}, {RESOURCE_NONE, 0}
},
	// Conversions provided by Furnishing tiles
{
	CONV_COOKING_CAVE, 0,
	"1 Grain + 1 Vegetable", "5 Food",
	{RESOURCE_GRAIN, 1, RESOURCE_VEGETABLE, 1}, {RESOURCE_FOOD, 5},
	TILE_COOKING_CAVE
}, {
	CONV_PEACEFUL_CAVE, 1,
	"Weapons", "Food",
	{RESOURCE_NONE, 0}, {RESOURCE_NONE, 0},
	TILE_PEACEFUL_CAVE
}, {
	CONV_HUNTING_PARLOR, 0,
	"2 Boar", "2 Gold + 2 Food",
	{RESOURCE_BOAR, 2}, {RESOURCE_GOLD, 2, RESOURCE_FOOD, 2},
	TILE_HUNTING_PARLOR
}, {
	CONV_BEER_PARLOR_FOOD, 0,
	"2 Grain", "4 Food",
	{RESOURCE_GRAIN, 2}, {RESOURCE_FOOD, 4},
	TILE_BEER_PARLOR
}, {
	CONV_BLACKSMITHING_PARLOR, 0,
	"1 Ore + 1 Ruby", "2 Gold + 1 Food",
	{RESOURCE_ORE, 1, RESOURCE_RUBY, 1},
	{RESOURCE_GOLD, 2, RESOURCE_FOOD, 1},
	TILE_BLACKSMITHING_PARLOR
}, {
	CONV_TRADER, 0,
	"2 Gold", "1 Wood + 1 Stone + 1 Ore",
	{RESOURCE_GOLD, 2},
	{RESOURCE_WOOD, 1, RESOURCE_STONE, 1, RESOURCE_ORE, 1},
	TILE_TRADER
}, {
	CONV_BEER_PARLOR_GOLD, 0,
	"2 Grain", "3 Gold",
	{RESOURCE_GRAIN, 2}, {RESOURCE_GOLD, 3},
	TILE_BEER_PARLOR
}, {
	CONV_SPARE_PART_STORAGE, 0,
	"1 Wood + 1 Stone + 1 Ore", "2 Gold",
	{RESOURCE_WOOD, 1, RESOURCE_STONE, 1, RESOURCE_ORE, 1},
	{RESOURCE_GOLD, 2},
	TILE_SPARE_PART_STORAGE
}, {
	CONV_NONE, 1,
	"(Nothing)", "(Nothing)",
	{RESOURCE_NONE, 0}, {RESOURCE_NONE, 0},
	TILE_NONE
}
// End conversion configs
};

const int CONVERSION_TYPES[] = {
	// ordinary xxxx-to-food conversion
	CONV_SHEEP_TO_FOOD,
	CONV_GRAIN_TO_FOOD,
	CONV_DONKEY_TO_FOOD,
	CONV_BOAR_TO_FOOD,
	CONV_VEGETABLE_TO_FOOD,
	CONV_RUBY_TO_FOOD,
	CONV_CATTLE_TO_FOOD,
	CONV_GOLD_TO_FOOD,
	// ruby-to-yyyy conversions
	CONV_RUBY_TO_DOG,
	CONV_RUBY_TO_GRAIN,
	CONV_RUBY_TO_VEGETABLE,
	CONV_RUBY_TO_SHEEP,
	CONV_RUBY_TO_WOOD,
	CONV_RUBY_TO_DONKEY,
	CONV_RUBY_TO_STONE,
	CONV_RUBY_TO_BOAR,
	CONV_RUBY_TO_ORE,
	CONV_RUBY_TO_CATTLE,
	// Furnishing tile conversions
	CONV_COOKING_CAVE,
	CONV_PEACEFUL_CAVE,
	CONV_HUNTING_PARLOR,
	CONV_BEER_PARLOR_FOOD,
	CONV_BLACKSMITHING_PARLOR,
	CONV_TRADER,
	CONV_BEER_PARLOR_GOLD,
	CONV_SPARE_PART_STORAGE,
	// Ruby-to-Tile conversions
	CONV_RUBY_TO_MEADOW,
	CONV_RUBY_TO_FIELD,
	CONV_RUBY_TO_TUNNEL,
	CONV_RUBY_TO_CAVERN
};

const int RUBY_TO_TILE_CONVERSIONS[] = {
	CONV_RUBY_TO_MEADOW,
	CONV_RUBY_TO_FIELD,
	CONV_RUBY_TO_TUNNEL,
	CONV_RUBY_TO_CAVERN
};



// FORWARD DECLARATIONS
//======================

static void trigger_resource_effect(player_state *player, int type, int value);





static const char *get_name(
    int id,
    const name_config *config,
    size_t size
) {
	int entries = size / sizeof(name_config);
	for (int i = 0; i < entries; i++) {
		const name_config *entry = &config[i];
		if (entry->id == id) {
			return entry->name;
		}
	}
	return "(Unknown)";
}

static const char *get_tile_name(int type) {
	return get_name(
	    type,
	    TILE_NAMES_CONFIG,
	    sizeof(TILE_NAMES_CONFIG)
	);
}

static const char *get_resource_name(int type) {
	return get_name(
	    type,
	    RESOURCE_NAMES_CONFIG,
	    sizeof(RESOURCE_NAMES_CONFIG)
	);
}

static const char *get_loot_name(int type) {
	return get_name(
	    type,
	    LOOT_NAMES_CONFIG,
	    sizeof(LOOT_NAMES_CONFIG)
	);
}


const char *caverna_get_resource_name(int type) {
	return get_resource_name(type);
}

const char *caverna_get_tile_name(int type) {
	return get_tile_name(type);
}

const char *caverna_get_loot_name(int type) {
	return get_loot_name(type);
}


static const action_config *get_action_config(int type) {
	int entries = sizeof(ACTIONS_CONFIG) / sizeof(ACTIONS_CONFIG[0]);

	for (int i = 0; i < entries; i++) {
		// For convenience
		const action_config *ac = &ACTIONS_CONFIG[i];
		if (ac->type == type) {
			return ac;
		}
	}
	return NULL;
}

static action_space *get_action_space(game_state *gs, int type) {
	for (int i = 0; i < MAX_ACTIONS; i++) {
		action_space *action = &gs->actions[i];
		if (action->type == type) {
			return action;
		}
	}
	return NULL;
}

static const furnishing_config *get_furnishing_config(int type) {
	int entries = sizeof(FURNISHINGS_CONFIG)
	    / sizeof(FURNISHINGS_CONFIG[0]);

	for (int i = 0; i < entries; i++) {
		// For convenience
		const furnishing_config *fc = &FURNISHINGS_CONFIG[i];
		if (fc->type == type) {
			return fc;
		}
	}
	return NULL;
}

static const conversion_config *get_conversion_config(int type) {
	int entries = sizeof(CONVERSIONS_CONFIG)
	    / sizeof(CONVERSIONS_CONFIG[0]);

	for (int i = 0; i < entries; i++) {
		// For convenience
		const conversion_config *cc = &CONVERSIONS_CONFIG[i];
		if (cc->type == type) {
			return cc;
		}
	}
	return NULL;
}
/*
static const int *get_loot_items_all(int *num_items) {
	*num_items = sizeof(LOOT_ITEMS) / sizeof(LOOT_ITEMS[0]);
	return LOOT_ITEMS;
}
*/

static const int *get_farm_animal_types(int *num_types) {
	*num_types = sizeof(FARM_ANIMAL_TYPES)
	    / sizeof(FARM_ANIMAL_TYPES[0]);
	return FARM_ANIMAL_TYPES;
}

static int is_farm_animal_type(int type) {
	int num_types = 0;
	const int *types = get_farm_animal_types(&num_types);
	for (int i = 0; i < num_types; i++) {
		if (types[i] == type) return 1;
	}
	return 0;
}

static const int *get_loot_items_upto(int strength, int *num_items) {
	static const int max_strength
	     = (sizeof(LOOT_UPTO) / sizeof(LOOT_UPTO[0])) - 1;

	if ((strength < 0) || (strength > max_strength)) {
		fprintf(stderr,
		    "(get_loot_items_upto) strength out of bounds: %d\n",
		    strength);
		//exit(1);
		return NULL;
	}

	*num_items = LOOT_UPTO[strength] + 1;
	return LOOT_ITEMS;
}

const int *caverna_get_loot_items_upto(int strength, int *num_items) {
	return get_loot_items_upto(strength, num_items);
}

static const int *get_all_furnishing_types(
    const game_state *gs,
    int *num_types
) {
	const int *all_furnishings = NULL;
	int entries = 0;

	// Full game
	all_furnishings = FURNISHING_TILES;
	entries = sizeof(FURNISHING_TILES) / sizeof(FURNISHING_TILES[0]);

	// Return
	*num_types = entries;
	return all_furnishings;
}

const int *caverna_get_all_furnishing_types(
    const game_state *gs,
    int *num_types
) {
	return get_all_furnishing_types(gs, num_types);
}

static const int *get_all_conversion_types(int *num_types) {
	*num_types = sizeof(CONVERSION_TYPES)
	    / sizeof(CONVERSION_TYPES[0]);
	return CONVERSION_TYPES;
}

const int *caverna_get_all_conversion_types(int *num_types) {
	return get_all_conversion_types(num_types);
}

static const int *get_ruby2tile_conversion_types(int *num_types) {
	*num_types = sizeof(RUBY_TO_TILE_CONVERSIONS)
	    / sizeof(RUBY_TO_TILE_CONVERSIONS[0]);
	return RUBY_TO_TILE_CONVERSIONS;
}

const int *caverna_get_ruby2tile_conversion_types(int *num_types) {
	return get_ruby2tile_conversion_types(num_types);
}

static int is_ruby2tile_conversion(int type) {
	int entries = sizeof(RUBY_TO_TILE_CONVERSIONS)
	    / sizeof(RUBY_TO_TILE_CONVERSIONS[0]);
	for (int i = 0; i < entries; i++) {
		if (RUBY_TO_TILE_CONVERSIONS[i] == type) {
			return 1;
		}
	}
	return 0;
}

int caverna_is_ruby2tile_conversion(int type) {
	return is_ruby2tile_conversion(type);
}

int get_conversion_description(
    int type,
    const char **input_desc,
    const char **output_desc
) {
	const conversion_config *cc = get_conversion_config(type);
	if (cc == NULL) return 0;
	*input_desc = cc->input_desc;
	*output_desc = cc->output_desc;
	return 1;
}

int caverna_get_conversion_description(
    int type,
    const char **input_desc,
    const char **output_desc
) {
	return get_conversion_description(type, input_desc, output_desc);
}



static void clear_tile(tile_state *tile) {
	tile->type = TILE_NONE;
	tile->dir = DIRECTION_NONE;
	tile->rounds = 0;
	tile->stable = 0;
	tile->dog = 0;
	tile->sheep = 0;
	tile->donkey = 0;
	tile->boar = 0;
	tile->cattle = 0;
	tile->grain = 0;
	tile->vegetable = 0;

	tile->reward[0] = RESOURCE_NONE;
	tile->reward[1] = 0;
}

static void clear_log(command_log *log) {
	log->head = NULL;
	log->tail = NULL;
}

static void deinit_command_log(command_log *log) {
	if (log == NULL) return;
	// traverse and free all nodes
	command_record *record = log->head;
	while (record != NULL) {
		command_record *next = record->next;
		// Reset pointers
		record->prev = NULL;
		record->next = NULL;
		// Free the node
		free(record);
		// Iterate forward
		record = next;
	} // while
	log->head = NULL;
	log->tail = NULL;
}

static int init_command_log(command_log *log) {
	int success = 0;
	do {
		log->head = NULL;
		log->tail = NULL;
		success = 1;
	} while(0);
	return success;
}

static int log_command6(
    command_log *log,
    int type,
    int value1,
    int value2,
    int value3,
    int value4,
    int value5,
    int value6
) {
	command_record *record = malloc(sizeof(command_record));
	if (record == NULL) return 0;

	record->prev = NULL;
	record->next = NULL;
	record->type = type;
	record->player_num = -1;
	record->value[0] = value1;
	record->value[1] = value2;
	record->value[2] = value3;
	record->value[3] = value4;
	record->value[4] = value5;
	record->value[5] = value6;

	// Append the record to the tail
	if (log->tail != NULL) {
		log->tail->next = record;
		record->prev = log->tail;
	} else {
		log->head = record;
	}
	log->tail = record;

	return 1;
}

static int log_command5(
    command_log *log,
    int type,
    int value1,
    int value2,
    int value3,
    int value4,
    int value5
) {
	return log_command6(log, type,
	    value1, value2, value3, value4, value5, 0);
}

static int log_command2(
    command_log *log,
    int type,
    int value1,
    int value2
) {
	return log_command5(log, type, value1, value2, 0, 0, 0);
}

static int log_command1(
    command_log *log,
    int type,
    int value1
) {
	return log_command5(log, type, value1, 0, 0, 0, 0);
}


static void reset_player(player_state *player) {
	// Unload the command log, if any
	deinit_command_log(&player->log);

	player->dwarfs = 0;
	player->children = 0;

	for (int i = 0; i < MAX_DWARFS; i++) {
		player->weapons[i] = 0;
		player->locations[i] = ACTION_NONE;
	}

	player->beggar = 0;

	player->stable = 0;

	player->grain = 0;
	player->vegetable = 0;

	player->food = 0;
	player->gold = 0;
	player->stone = 0;
	player->wood = 0;
	player->ruby = 0;
	player->ore = 0;

	player->dog = 0;
	player->sheep = 0;
	player->boar = 0;
	player->donkey = 0;
	player->cattle = 0;

	player->placed_dog = 0;
	player->placed_sheep = 0;
	player->placed_donkey = 0;
	player->placed_boar = 0;
	player->placed_cattle = 0;

	player->newborn_sheep = 0;
	player->newborn_donkey = 0;
	player->newborn_boar = 0;
	player->newborn_cattle = 0;

}


static void clear_player(player_state *player) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		clear_tile(&player->board[i]);
	}
	clear_log(&player->log);
	reset_player(player);
}

static void init_action(action_space *action, int type) {
	action->type = type;
	action->counter = 0;
	action->has_ruby = 0;
	action->taken_by = -1;
}

static void setup_actions_solo(action_space *actions, int *num_actions) {
	static const int solo_actions[] = {
		// Board: 1-7 players
		ACTION_NONE, // n/a in solo: Drift mining
		ACTION_LOGGING,
		ACTION_WOOD_GATHERING,

		ACTION_EXCAVATION,
		ACTION_NONE, // n/a in solo: Supplies
		ACTION_NONE, // n/a in solo: Clearing

		ACTION_NONE, // n/a in solo: Starting player
		ACTION_ORE_MINING,
		ACTION_SUSTENANCE,

		ACTION_RUBY_MINING,
		ACTION_HOUSEWORK,
		ACTION_SLASH_AND_BURN,

		// setup for appearing actions.
		ACTION_BLACKSMITHING,
		ACTION_SHEEP_FARMING,
		ACTION_ORE_MINE_CONSTRUCTION,

		ACTION_WISH_FOR_CHILDREN,
		ACTION_DONKEY_FARMING,
		ACTION_RUBY_MINE_CONSTRUCTION,

		ACTION_ORE_DELIVERY,
		ACTION_FAMILY_LIFE,
		ACTION_NONE, // Round 9 is skipped

		ACTION_ORE_TRADING,
		ACTION_ADVENTURE,
		ACTION_RUBY_DELIVERY
	};

	int entries = sizeof(solo_actions) / sizeof(solo_actions[0]);
	for (int i = 0; i < entries; i++) {
		init_action(&actions[i], solo_actions[i]);
	}
	*num_actions = entries - 12;
}

static int init_furnishing(furnishing_state *furnishing, int type) {
	int success = 0;
	do {
		furnishing->type = type;
		furnishing->taken_by = -1;

		success = 1;
	} while (0);
	return success;
}

static void setup_all_furnishings(
    furnishing_state *furnishings,
    int *num_furnishings
) {
	// TODO: Full game or Introductory game?

	const int *all_furnishings = NULL;
	int entries = 0;

	// Full game
	all_furnishings = FURNISHING_TILES;
	entries = sizeof(FURNISHING_TILES) / sizeof(FURNISHING_TILES[0]);

	for (int i = 0; i < entries; i++) {
		init_furnishing(&furnishings[i], all_furnishings[i]);
	}
	*num_furnishings = entries;
}

static furnishing_state *get_furnishing(const game_state *gs, int type) {
	for (int i = 0; i < gs->num_furnishings; i++) {
		const furnishing_state *furnishing = &gs->furnishings[i];
		if (furnishing->type == type) {
			// Discard const qualifier
			return (furnishing_state *) furnishing;
		}
	}
	return NULL;
}

static int get_depth_by_offset(const tile_state *board, int offset) {
	int z;
	for (z = 0; z < BOARD_DEPTH; z++) {
		const tile_state *t = &board[offset+(z*BOARD_LEVEL_SIZE)];
		if (t->type == TILE_NONE) break;
	} // for
	return z;
}

static int get_depth(const tile_state *board, int x, int y) {
	return get_depth_by_offset(board, (y*BOARD_WIDTH)+x);
}

static int are_coordinates_valid(int x, int y, int z) {
	if ( (x < 0) || (x >= BOARD_WIDTH)
	    || (y < 0) || (y >= BOARD_HEIGHT)
	    || (z < 0) || (z >= BOARD_DEPTH) )
	{
		return 0;
	}
	return 1;
}

/**
 * Returns NULL if the coordinates are not within the board limits.
 */
static tile_state *get_tile(
    const tile_state *board,
    int x,
    int y,
    int z
) {
	if (!are_coordinates_valid(x, y, z)) {
		return NULL;
	}
	// Strip away const
	return (tile_state *) &board[(z*BOARD_LEVEL_SIZE)+(y*BOARD_WIDTH)+x];
}

static void set_tile_reward(
    const tile_state *board,
    int x, int y, int z,
    int type, int qty
) {
	tile_state *t = get_tile(board, x, y, z);
	if (t == NULL) {
		fprintf(stderr,
		    "(set_tile_reward) invalid tile coordinates: "
		    "x=%d, y=%d, z=%d\n",
		    x, y, z
		);
		exit(1);
	}
	t->reward[0] = type;
	t->reward[1] = qty;
}

static void setup_board(tile_state *board) {
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			int type = TILE_NONE;
			// For convenience
			tile_state *tile = &board[(y*BOARD_WIDTH)+x];
			if (x < BOARD_MOUNTAIN_X) {
				type = TILE_FOREST;
			} else {
				type = TILE_MOUNTAIN;
			}
			// set type
			tile->type = type;
		}
	}
	// Set reward foods inside the Mountain and the Mountain lake.
	set_tile_reward(board, 5, 4, 0, RESOURCE_FOOD, 1);
	set_tile_reward(board, 6, 1, 0, RESOURCE_FOOD, 2);
	// Set reward foods in the Forest river
	set_tile_reward(board, 2, 4, 0, RESOURCE_FOOD, 1);
	// Set reward boars in the Forest
	set_tile_reward(board, 1, 3, 0, RESOURCE_BOAR, 1);
	set_tile_reward(board, 3, 1, 0, RESOURCE_BOAR, 1);

	// Set Entry-level Dwelling and block single Mountain space.
	get_tile(board, 4, 3, 0)->type = TILE_CAVERN;
	get_tile(board, 4, 4, 0)->type = TILE_INITIAL_DWELLING;
	get_tile(board, 4, 5, 0)->type = TILE_BLOCKED;
}


static void deinit_player(player_state *player) {
	if (player == NULL) return;
	deinit_command_log(&player->log);
}

static int init_player(player_state *player) {
	int success = 0;
	do {
		success = init_command_log(&player->log);
		if (!success) break;
		success = 1;
	} while (0);

	if (!success) {
		deinit_player(player);
	}
	return success;
}

static int error(game_state *gs, int errnum, const char *fmt, ...) {
	// Set errno
	gs->errno = errnum;
	// Format error message
	va_list args;
	va_start(args, fmt);
	int result = vsnprintf(
	    gs->strerror, sizeof(gs->strerror), fmt, args);
	va_end(args);
	return result;
}

int caverna_init(game_state *gs) {
	int success = 0;
	do {
		gs->cur_round = 0; // 1-based, so zero is invalid
		gs->cur_player = -1;
		gs->num_players = 0;
		gs->phase = PHASE_NONE;
		gs->harvest = HARVEST_NONE;
		gs->breed = BREED_NONE;

		gs->errno = E_OK;
		gs->strerror[0] = '\0';

		for (int i = 0; i < MAX_PLAYERS; i++) {
			clear_player(&gs->players[i]);
		}
		for (int i = 0; i < MAX_ACTIONS; i++) {
			init_action(&gs->actions[i], ACTION_NONE);
		}
		for (int i = 0; i < MAX_PLAYERS; i++) {
			success = init_player(&gs->players[i]);
			if (!success) break;
		}
		for (int i = 0; i < MAX_FURNISHINGS; i++) {
			success = init_furnishing(
			    &gs->furnishings[i], TILE_NONE);
			if (!success) break;
		}
		// NOTE: Action spaces are setup at game start,
		// since their configuration depends on the number
		// of players.
		if (!success) break;

		gs->last_command = NULL;
		success = init_command_log(&gs->log);
		if (!success) break;

	} while (0);

	if (!success) {
		// deinit game_state
		caverna_deinit(gs);
	}
	return success;
}

void caverna_deinit(game_state *gs) {
	if (gs == NULL) return;

	deinit_command_log(&gs->log);
	for (int i = 0; i < MAX_PLAYERS; i++) {
		deinit_player(&gs->players[i]);
	}
}

game_state *caverna_create(void) {
	int success = 0;
	game_state *gs = NULL;
	do {
		gs = malloc(sizeof(game_state));
		if (gs == NULL) break;
		success = caverna_init(gs);
	} while (0);

	if (!success) {
		free(gs);
	}
	return gs;
}

void caverna_free(game_state *gs) {
	caverna_deinit(gs);
	free(gs);
}

static int get_player_num(const game_state *gs, const player_state *player) {
	int player_num = -1;
	for (int i = 0; i < gs->num_players; i++) {
		if (&gs->players[i] == player) {
			player_num = i;
			break;
		}
	}
	return player_num;
}

const char *caverna_get_action_name(int type) {
	const action_config *ac = get_action_config(type);
	if (ac == NULL) {
		return NULL;
	}
	return ac->name;
}

int caverna_get_action_resource(int type) {
	int res = RESOURCE_NONE;

	switch(type) {
	case ACTION_DRIFT_MINING:
		res = RESOURCE_STONE;
		break;
	case ACTION_LOGGING:
		res = RESOURCE_WOOD;
		break;
	case ACTION_WOOD_GATHERING:
		res = RESOURCE_WOOD;
		break;
	case ACTION_EXCAVATION:
		res = RESOURCE_STONE;
		break;
	case ACTION_SUPPLIES:
		break;
	//case ACTION_CLEARING: // TODO
	//case ACTION_STARTING_PLAYER: // TODO
	case ACTION_ORE_MINING:
		res = RESOURCE_ORE;
		break;
	case ACTION_SUSTENANCE:
		res = RESOURCE_FOOD;
		break;
	case ACTION_RUBY_MINING:
		res = RESOURCE_RUBY;
		break;
	case ACTION_HOUSEWORK:
		break;
	case ACTION_SLASH_AND_BURN:
		break;
	case ACTION_BLACKSMITHING:
		break;
	case ACTION_SHEEP_FARMING:
		res = RESOURCE_SHEEP;
		break;
	case ACTION_ORE_MINE_CONSTRUCTION:
		break;
	case ACTION_WISH_FOR_CHILDREN:
		break;
	case ACTION_URGENT_WISH_FOR_CHILDREN:
		break;
	case ACTION_DONKEY_FARMING:
		res = RESOURCE_DONKEY;
		break;
	case ACTION_ORE_DELIVERY:
		// NOTE: Handled by the caller
		break;
	case ACTION_ADVENTURE:
		break;
	case ACTION_RUBY_DELIVERY:
		res = RESOURCE_RUBY;
		break;
	default:
		// TODO: This needs to be soft, as this is exported.
		fprintf(stderr,
		    "(caverna_get_action_resource) "
		    "unhandled action_type: %d\n", type
		);
		exit(1);
	}
	return res;
}

const int *caverna_get_furnishing_price(int type) {
	const furnishing_config *fc = get_furnishing_config(type);
	if (fc == NULL) {
		// TODO: This needs to be soft, as this is exported.
		fprintf(stderr,
		    "(caverna_get_furnishing_price) "
		    "unknown Furnishing tile type: %d\n",
		    type
		);
		exit(1);
	}
	return fc->price;
}



void *caverna_malloc_orders(int type) {
	size_t extra = 0;
	const action_config *ac = get_action_config(type);
	if (ac != NULL) {
		extra = ac->orders_size;
	}
	size_t size = sizeof(action_orders) + extra;
	action_orders *ao = malloc(size);
	ao->type = type;
	return ao;
}

static void move_coordinates(int *x, int *y, int dir) {
	switch(dir) {
	case DIRECTION_UP:
		(*y)--;
		break;
	case DIRECTION_RIGHT:
		(*x)++;
		break;
	case DIRECTION_DOWN:
		(*y)++;
		break;
	case DIRECTION_LEFT:
		(*x)--;
		break;
	case DIRECTION_NONE:
		break;
	default:
		fprintf(stderr,
		    "(move_coordinates) unexpected direction: %d\n",
		    dir
		);
		exit(1); // Abort
		break;
	}
}

static void get_both_coordinates(
    const tile_placement *placement,
    int *x1,
    int *y1,
    int *x2,
    int *y2
) {
	*x1 = placement->x;
	*y1 = placement->y;

	*x2 = placement->x;
	*y2 = placement->y;

	move_coordinates(x2, y2, placement->dir);
}

void caverna_get_both_coordinates(
    const tile_placement *placement,
    int *x1, int *y1, int *x2, int *y2
) {
	get_both_coordinates(placement, x1, y1, x2, y2);
}


static int get_opposite_direction(int dir) {
	int opposite = DIRECTION_NONE;
	switch(dir) {
	case DIRECTION_UP:
		opposite = DIRECTION_DOWN;
		break;
	case DIRECTION_RIGHT:
		opposite = DIRECTION_LEFT;
		break;
	case DIRECTION_DOWN:
		opposite = DIRECTION_UP;
		break;
	case DIRECTION_LEFT:
		opposite = DIRECTION_LEFT;
		break;
	case DIRECTION_NONE:
		opposite = DIRECTION_NONE;
		break;
	default:
		fprintf(stderr,
		    "(get_opposite_direction) unexpected direction: %d\n",
		    dir
		);
		exit(1); // Abort
		break;
	}
	return opposite;
}


/**
 * Returns NULL if the coordinates (x,y) are not within the board limits.
 */
static tile_state *get_top_tile(
    const tile_state *board,
    int x,
    int y,
    int *z
) {
	if (!are_coordinates_valid(x, y, 0)) {
		return NULL;
	}
	*z = get_depth(board, x, y) - 1;
	if (*z == -1) {
		return NULL;
	}
	return get_tile(board, x, y, *z);
}

tile_state *caverna_get_top_tile(const tile_state *board, int x, int y) {
	int z;
	return get_top_tile(board, x, y, &z);
}

tile_state *get_other_tile(const tile_state *board, int x, int y, int dir) {
	int z;
	move_coordinates(&x, &y, dir);
	const tile_state *other = get_top_tile(board, x, y, &z);
	// Discard const-qualifier
	return (tile_state *) other;
}

static int get_tile_coordinates(
    const player_state *player,
    int type,
    int *x,
    int *y,
    int *z
) {
	const tile_state *board = player->board;
	for (int iy = 0; iy < BOARD_HEIGHT; iy++) {
		for (int ix = 0; ix < BOARD_WIDTH; ix++) {
			int iz = get_depth(board, ix, iy) - 1;
			if (iz == -1) {
				// No top tile. Skip
				continue;
			}
			const tile_state *top = get_tile(board, ix, iy, iz);
			if (top->type == type) {
				*x = ix;
				*y = iy;
				*z = iz;
				return 1;
			}
		}
	}
	return 0;
}

static tile_state *get_furnishing_tile(
    const tile_state *board,
    int type
) {
	for (int iy = 0; iy < BOARD_HEIGHT; iy++) {
		for (int ix = 0; ix < BOARD_WIDTH; ix++) {
			int iz;
			tile_state *top = get_top_tile(board, ix, iy, &iz);
			if (top == NULL) continue;
			if (top->type == type) {
				// Discard const qualifier
				return (tile_state *) top;
			}
		}
	}
	return NULL;
}



static int has_tile(const player_state *player, int type) {
	int x, y, z;
	return get_tile_coordinates(player, type, &x, &y, &z);
}

int caverna_has_player_tile(const player_state *player, int type) {
	return has_tile(player, type);
}

static int is_overhung(int x, int y) {
	if ((x == 0) || (x == BOARD_WIDTH-1)) {
		return 1;
	}
	if ((y == 0) || (y == BOARD_HEIGHT-1)) {
		return 1;
	}
	return 0;
}

static void get_board_limits(int *xmin, int *ymin, int *xmax, int *ymax) {
	*xmin = 0;
	*ymin = 0;
	*xmax = BOARD_WIDTH-1;
	*ymax = BOARD_HEIGHT-1;
}

static void get_mountain_limits(
    const player_state *player,
    int *xmin,
    int *ymin,
    int *xmax,
    int *ymax
) {
	int has_office_room = has_tile(player, TILE_OFFICE_ROOM);
	int border = has_office_room ? 0 : 1;

	*xmin = BOARD_MOUNTAIN_X;
	*xmax = BOARD_WIDTH-1-border;
	*ymin = border;
	*ymax = BOARD_HEIGHT-1-border;
}

void caverna_get_mountain_limits(
    const player_state *player,
    int *xmin,
    int *ymin,
    int *xmax,
    int *ymax
) {
	return get_mountain_limits(player, xmin, ymin, xmax, ymax);
}

static void get_forest_limits(
    const player_state *player,
    int *xmin,
    int *ymin,
    int *xmax,
    int *ymax
) {
	int has_office_room = has_tile(player, TILE_OFFICE_ROOM);
	int border = has_office_room ? 0 : 1;

	*xmin = border;
	*xmax = BOARD_MOUNTAIN_X-1;
	*ymin = border;
	*ymax = BOARD_HEIGHT-1-border;
}

void caverna_get_forest_limits(
    const player_state *player,
    int *xmin,
    int *ymin,
    int *xmax,
    int *ymax
) {
	return get_forest_limits(player, xmin, ymin, xmax, ymax);
}

static int are_coordinates_within(
    int x,
    int y,
    int xmin,
    int ymin,
    int xmax,
    int ymax
) {
	if ((x < xmin) || (x > xmax) || (y < ymin) || (y > ymax)) {
		return 0;
	}
	return 1;
}

static int has_adjacent_other_than(
    const tile_state* board,
    int x,
    int y,
    int type
) {
	int xmin, ymin;
	int xmax, ymax;
	int z; // nuissance
	const tile_state* adjacent[4];

	if (type == TILE_FOREST) {
		xmin = 0;
		xmax = BOARD_MOUNTAIN_X-1;
	} else if (type == TILE_MOUNTAIN) {
		xmin = BOARD_MOUNTAIN_X;
		xmax = BOARD_WIDTH-1;
	} else {
		fprintf(stderr,
		    "(has_adjacent_other_than) unexpected type: %d\n",
		    type
		);
		exit(1);
	}

	ymin = 0;
	ymax = BOARD_HEIGHT-1;

	for (int i = 0; i < 4; i++) {
		adjacent[i] = NULL;
	}

	if ((x < xmin) || (x > xmax)
	    || (y < ymin) || (y > ymax))
	{
		// Out of boundaries
		return 0;
	}

	if (y > ymin) {
		// up tile
		adjacent[0] = get_top_tile(board, x, y-1, &z);
	}
	if (x < xmax) {
		// right tile
		adjacent[1] = get_top_tile(board, x+1, y, &z);
	}
	if (y < ymax) {
		// down tile
		adjacent[2] = get_top_tile(board, x, y+1, &z);
	}
	if (x > xmin) {
		// left tile
		adjacent[3] = get_top_tile(board, x-1, y, &z);
	}

	for (int i = 0; i < 4; i++) {
		if (adjacent[i] == NULL) continue;
		if (adjacent[i]->type != type) {
			return 1;
		}
	}

	// If on the forest side, one additional
	// test is allowed, since it is impossible to populate
	// forest otherwise.
	if ((type == TILE_FOREST)
	    && (y == BOARD_FOREST_ENTRY_Y)
	    && (x == BOARD_FOREST_ENTRY_X))
	{
		// Adjacent to a non-forest tile at right (mountain entry).
		return 1;
	}

	return 0;
}

int caverna_has_adjacent_other_than(
    const tile_state *board,
    int x,
    int y,
    int type
) {
	return has_adjacent_other_than(board, x, y, type);
}

static int is_dwelling(int type) {
	static const int dwelling_types[] = {
		TILE_INITIAL_DWELLING,
		TILE_DWELLING,
		TILE_SIMPLE_DWELLING_1,
		TILE_SIMPLE_DWELLING_2,
		TILE_MIXED_DWELLING,
		TILE_COUPLE_DWELLING,
		TILE_ADDITIONAL_DWELLING
	};
	int entries = sizeof(dwelling_types) / sizeof(dwelling_types[0]);
	for (int i = 0; i < entries; i++) {
		if (type == dwelling_types[i]) {
			return 1;
		}
	}
	return 0;
}

static int get_dwelling_capacity(int type) {
	int capacity = 0;
	switch(type) {
	case TILE_DWELLING:
	case TILE_SIMPLE_DWELLING_1:
	case TILE_SIMPLE_DWELLING_2:
	case TILE_MIXED_DWELLING:
		capacity = 1;
		break;
	case TILE_INITIAL_DWELLING:
	case TILE_COUPLE_DWELLING:
		capacity = 2;
		break;
	case TILE_ADDITIONAL_DWELLING:
		// As this is for the sixth Dwarf only,
		// it is handled a bit differently.
		capacity = 0;
		// (Its capacity depends on the number of Dwarfs
		// the player has. If less than five, capacity is zero).
		break;
	default:
		break;
	}
	return capacity;
}

static int num_adjacent_dwellings(
    const tile_state* board,
    int x,
    int y
) {
	int xmin, ymin;
	int xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);
	const tile_state* adjacent[4];

	int z; // nuissance
	adjacent[0] = get_top_tile(board, x, y-1, &z);
	adjacent[1] = get_top_tile(board, x+1, y, &z);
	adjacent[2] = get_top_tile(board, x, y+1, &z);
	adjacent[3] = get_top_tile(board, x-1, y, &z);

	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (adjacent[i] == NULL) continue;
		if (is_dwelling(adjacent[i]->type)) {
			count++;
		}
	}
	return count;
}

static int num_tiles(const tile_state* board, int type) {
	int xmin, ymin;
	int xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	int count = 0;
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			tile_state *tile = get_top_tile(board, x, y, &z);
			if (tile->type == type) {
				count++;
			}
		}
	}
	return count;
}

static int num_donkeys_in_ore_mines(const tile_state* board) {
	int xmin, ymin;
	int xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	int count = 0;
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			tile_state *tile = get_top_tile(board, x, y, &z);
			if ((tile->type == TILE_ORE_MINE)
			    && (tile->donkey > 0))
			{
				count++;
			}
		}
	}
	return count;
}

static int num_donkeys_in_mines(const tile_state* board) {
	int xmin, ymin;
	int xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	int count = 0;
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			tile_state *tile = get_top_tile(board, x, y, &z);
			int is_mine = (tile->type == TILE_ORE_MINE)
			    || (tile->type == TILE_RUBY_MINE);
			if ((is_mine) && (tile->donkey > 0)) {
				count++;
			}
		}
	}
	return count;
}

static int num_rooms_in_dwellings(const tile_state* board) {
	int xmin, ymin;
	int xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	int count = 0;
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			tile_state *tile = get_top_tile(board, x, y, &z);
			count += get_dwelling_capacity(tile->type);
		}
	}
	return count;
}

static int num_caverns(const tile_state *board) {
	return num_tiles(board, TILE_CAVERN);
}

static int is_scoring_tile(int type) {
	static const int SCORING_TILES[] = {
		// Scoring tiles 1 (parlors)
		TILE_WEAVING_PARLOR,
		TILE_MILKING_PARLOR,
		TILE_STATE_PARLOR,
		TILE_HUNTING_PARLOR,
		TILE_BEER_PARLOR,
		TILE_BLACKSMITHING_PARLOR,
		// Scoring tiles 2a (storages)
		TILE_STONE_STORAGE,
		TILE_ORE_STORAGE,
		TILE_SPARE_PART_STORAGE,
		TILE_MAIN_STORAGE,
		TILE_WEAPON_STORAGE,
		TILE_SUPPLIES_STORAGE,
		// Scoring tiles 2b (chambers)
		TILE_BROOM_CHAMBER,
		TILE_TREASURE_CHAMBER,
		TILE_FOOD_CHAMBER,
		TILE_PRAYER_CHAMBER,
		TILE_WRITING_CHAMBER,
		TILE_FODDER_CHAMBER
	};
	int entries = sizeof(SCORING_TILES) / sizeof(SCORING_TILES[0]);

	for (int i = 0; i < entries; i++) {
		if (type == SCORING_TILES[i]) return 1;
	}
	return 0;
}

static int num_scoring_tiles(const tile_state *board) {
	int xmin, ymin;
	int xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	int count = 0;
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			tile_state *tile = get_top_tile(board, x, y, &z);
			count += is_scoring_tile(tile->type);
		}
	}
	return count;
}

static int get_furnishing_owner(const game_state *gs, int type) {
	const furnishing_state *furnishing = get_furnishing(gs, type);
	if (furnishing == NULL) {
		return -1;
	}
	return furnishing->taken_by;
}

int caverna_num_donkeys_in_ore_mines(const player_state *player) {
	return num_donkeys_in_mines(player->board);
}

int caverna_num_rooms_in_dwellings(const player_state *player) {
	return num_rooms_in_dwellings(player->board);
}

int caverna_num_caverns(const player_state *player) {
	return num_caverns(player->board);
}

int caverna_get_furnishing_owner(const game_state *gs, int type) {
	return get_furnishing_owner(gs, type);
}

static int is_animal_resource(int type) {
	switch(type) {
	case RESOURCE_DOG:
	case RESOURCE_SHEEP:
	case RESOURCE_DONKEY:
	case RESOURCE_BOAR:
	case RESOURCE_CATTLE:
		return 1;
	}
	return 0;
}

static int *get_newborn_animal(const player_state *player, int type) {
	const int *counter = NULL;
	switch(type) {
	case RESOURCE_SHEEP:
		counter = &player->newborn_sheep;
		break;
	case RESOURCE_DONKEY:
		counter = &player->newborn_donkey;
		break;
	case RESOURCE_BOAR:
		counter = &player->newborn_boar;
		break;
	case RESOURCE_CATTLE:
		counter = &player->newborn_cattle;
		break;
	default:
		fprintf(stderr,
		    "(get_newborn_animal) not a newborn animal type: %d\n",
		    type
		);
		exit(1);
	}
	// Discard const-qualifier.
	return (int *) counter;
}


static int *get_placed_animal(const player_state *player, int type) {
	const int *counter = NULL;
	switch(type) {
	case RESOURCE_DOG:
		counter = &player->placed_dog;
		break;
	case RESOURCE_SHEEP:
		counter = &player->placed_sheep;
		break;
	case RESOURCE_DONKEY:
		counter = &player->placed_donkey;
		break;
	case RESOURCE_BOAR:
		counter = &player->placed_boar;
		break;
	case RESOURCE_CATTLE:
		counter = &player->placed_cattle;
		break;
	default:
		fprintf(stderr,
		    "(get_placed_animal) not animal resource type: %d\n",
		    type
		);
		exit(1);
	}
	// Discard const-qualifier.
	return (int *) counter;
}

static int *get_animal(const player_state *player, int type) {
	const int *counter = NULL;
	switch(type) {
	case RESOURCE_DOG:
		counter = &player->dog;
		break;
	case RESOURCE_SHEEP:
		counter = &player->sheep;
		break;
	case RESOURCE_BOAR:
		counter = &player->boar;
		break;
	case RESOURCE_DONKEY:
		counter = &player->donkey;
		break;
	case RESOURCE_CATTLE:
		counter = &player->cattle;
		break;
	default:
		fprintf(stderr,
		    "(get_animal) not animal resource type: %d\n",
		    type
		);
		exit(1);
	}
	// Discard const-qualifier.
	return (int *) counter;
}

static int *get_resource(const player_state *player, int type) {
	const int *counter = NULL;
	switch(type) {
	case RESOURCE_NONE:
		break;
	case RESOURCE_GRAIN:
		counter = &player->grain;
		break;
	case RESOURCE_VEGETABLE:
		counter = &player->vegetable;
		break;
	case RESOURCE_FOOD:
		counter = &player->food;
		break;
	case RESOURCE_GOLD:
		counter = &player->gold;
		break;
	case RESOURCE_STONE:
		counter = &player->stone;
		break;
	case RESOURCE_WOOD:
		counter = &player->wood;
		break;
	case RESOURCE_RUBY:
		counter = &player->ruby;
		break;
	case RESOURCE_ORE:
		counter = &player->ore;
		break;

	// Animals (total)
	case RESOURCE_DOG:
		counter = &player->dog;
		break;
	case RESOURCE_SHEEP:
		counter = &player->sheep;
		break;
	case RESOURCE_BOAR:
		counter = &player->boar;
		break;
	case RESOURCE_DONKEY:
		counter = &player->donkey;
		break;
	case RESOURCE_CATTLE:
		counter = &player->cattle;
		break;
	default:
		fprintf(stderr,
		    "(get_resource) not resource type: %d\n",
		    type
		);
		exit(1);
	}
	// Remove const
	return (int *) counter;
}

int *caverna_get_resource(const player_state *player, int type) {
	// TODO: Should return NULL instead of crashing if no such type.
	return get_resource(player, type);
}


static void add_resource(player_state *player, int type, int value) {
	if (value == 0) return;
	if (value < 0) {
		fprintf(stderr,
		    "(add_resource) value is negative: %d\n",
		    value
		);
		exit(1);
	}

	int *counter = get_resource(player, type);
	(*counter) += value;

	// Examine triggers
	trigger_resource_effect(player, type, value);
}

static void sub_resource(player_state *player, int type, int value) {
	if (value == 0) return;
	if (value < 0) {
		fprintf(stderr,
		    "(sub_resource) value is negative: %d\n",
		    value
		);
		exit(1);
	}

	int *counter = get_resource(player, type);

	if (is_animal_resource(type)) {
		int *placed = get_placed_animal(player, type);
		int unplaced = (*counter) - (*placed);
		if (unplaced < value) {
			fprintf(stderr,
			    "(sub_resource) need to unplace resource first: %d %s\n",
			    value, get_resource_name(type)
			);
			exit(1);
		}
	}

	(*counter) -= value;
}

/** Return the first Farm animal type seen on the tile. */
static int get_tile_animal_type(const tile_state *tile) {
	if (tile->sheep > 0) return RESOURCE_SHEEP;
	else if (tile->donkey > 0) return RESOURCE_DONKEY;
	else if (tile->boar > 0) return RESOURCE_BOAR;
	else if (tile->cattle > 0) return RESOURCE_CATTLE;
	return RESOURCE_NONE;
}

static int *get_tile_resource(const tile_state *tile, int type) {
	const int *counter = NULL;
	switch(type) {
	case RESOURCE_NONE:
		break;
	case RESOURCE_GRAIN:
		counter = &tile->grain;
		break;
	case RESOURCE_VEGETABLE:
		counter = &tile->vegetable;
		break;
	// no food
	// no gold
	// no stone
	// no wood
	// no ruby
	// no ore
	case RESOURCE_DOG:
		counter = &tile->dog;
		break;
	case RESOURCE_SHEEP:
		counter = &tile->sheep;
		break;
	case RESOURCE_BOAR:
		counter = &tile->boar;
		break;
	case RESOURCE_DONKEY:
		counter = &tile->donkey;
		break;
	case RESOURCE_CATTLE:
		counter = &tile->cattle;
		break;
	default:
		fprintf(stderr,
		    "(get_tile_resource) no such resource type: %d",
		    type
		);
		exit(1);
	}
	// Remove const
	return (int *) counter;
}


static int *get_price_resource(const int *price, int type) {
	for (int i = 0; i < 3; i++) {
		if (price[i*2+0] == type) {
			// discard const-qualifier
			return (int *) &price[(i*2)+1];
		}
	}
	return NULL;
}

static int *set_price_resource(int *price, int type, int cost) {
	for (int i = 0; i < 3; i++) {
		int cost_type = price[i*2];
		if ((cost_type == RESOURCE_NONE)
		    || (cost_type == type))
		{
			price[(i*2)+0] = type;
			int *counter = &price[(i*2)+1];
			*counter = cost;
			return counter;
		}
	}
	fprintf(stderr,
	    "(set_price_resource) not enough slots in a price\n"
	);
	exit(1); // Abort
	return NULL;
}

static void set_price(int *price, int num_resources, ...) {
	va_list ap;
	va_start(ap, num_resources);
	for (int i = 0; i < 3; i++) {
		int has_arg = i < num_resources;
		price[(i*2)+0] = has_arg ? va_arg(ap, int) : RESOURCE_NONE;
		price[(i*2)+1] = has_arg ? va_arg(ap, int) : 0;
	}
	va_end(ap);
}

static void set_price1(int *price, int type1, int cost1) {
	set_price(price, 1, type1, cost1);
}

static void set_price2(int *price, int type1, int cost1, int type2, int cost2) {
	set_price(price, 2, type1, cost1, type2, cost2);
}

static void set_price3(
    int *price,
    int type1, int cost1,
    int type2, int cost2,
    int type3, int cost3
) {
	set_price(price, 3, type1, cost1, type2, cost2, type3, cost3);
}

static int check_price(const int *price, const player_state *player) {
	for (int i = 0; i < 3; i++) {
		int type = price[i*2+0];
		int cost = price[(i*2)+1];
		if (type == RESOURCE_NONE) {
			// All costs checked.
			break;
		}
		const int *counter = get_resource(player, type);
		if (*counter < cost) {
			// Not enough this resource.
			return 0;
		}
	}
	return 1;
}

static int get_resource_conversion(
    const conversion_config *cc,
    int count,
    int *input, int *output
) {
	if (!cc->is_special) {
		memcpy(input, cc->input, sizeof(cc->input));
		memcpy(output, cc->output, sizeof(cc->input));
		// Apply count
		for (int i = 0; i < 3; i++) {
			if (input[(i*2)+0] == RESOURCE_NONE) break;
			input[(i*2)+1] *= count;
		}
		for (int i = 0; i < 3; i++) {
			if (output[(i*2)+0] == RESOURCE_NONE) break;
			output[(i*2)+1] *= count;
		}
	} else if (cc->type == CONV_DONKEY_TO_FOOD) {
		set_price1(input, RESOURCE_DONKEY, count);
		set_price1(output, RESOURCE_FOOD, (count*3)/2);
	} else if (cc->type == CONV_GOLD_TO_FOOD) {
		set_price1(input, RESOURCE_GOLD, count);
		set_price1(output, RESOURCE_FOOD, count-1);
	} else {
		// CONV_PEACEFUL_CAVE and Ruby-to-Tile conversions
		// are not handled here.
		return 0;
	}
	return 1;
}

static int get_ruby_to_tile_conversion(
    int conversion,
    int *cost_ruby, int *underneath, int *type
) {
	switch(conversion) {
	case CONV_RUBY_TO_MEADOW:
		*cost_ruby = 1;
		*type = TILE_MEADOW;
		*underneath = TILE_FOREST;
		break;
	case CONV_RUBY_TO_FIELD:
		*cost_ruby = 1;
		*type = TILE_FIELD;
		*underneath = TILE_FOREST;
		break;
	case CONV_RUBY_TO_TUNNEL:
		*cost_ruby = 1;
		*type = TILE_TUNNEL;
		*underneath = TILE_MOUNTAIN;
		break;
	case CONV_RUBY_TO_CAVERN:
		// Cost 2 Ruby
		*cost_ruby = 2;
		*type = TILE_CAVERN;
		*underneath = TILE_MOUNTAIN;
		break;
	default:
		return 0;
	}

	return 1;
}

/**
 * The player's personal supply gains a resource from the general supply.
 * This is used when? TODO.
 */
static void gain_resource(player_state *player, int type, int value) {
	log_command2(
	    &player->log,
	    CMD_GAIN_RESOURCE,
	    type, value
	);
	// Execute gain
	add_resource(player, type, value);
}

/**
 * The player pays resources from the personal supply to the general supply.
 * This is used when player pays for a Furnishing tile, TODO.
 *
 * NOTE: game_state needed only for error messaging.
 */
static int pay_resource(
    game_state *gs,
    player_state *player,
    int type,
    int cost
) {
	int *counter = get_resource(player, type);
	if (*counter < cost) {
		error(gs, E_ORDERS,
		    "Player has not enough %s to pay "
		    "(have %d, needed %d)",
		    get_resource_name(type),
		    *counter, cost
		);
		return 0;
	}

	// Log action and execute
	log_command2(
	    &player->log,
	    CMD_PAY_RESOURCE,
	    type, cost
	);

	sub_resource(player, type, cost);

	return 1;
}

static void take_animal_from_tile(
    player_state *player,
    int x,
    int y,
    int z,
    int type,
    int quantity
) {
	if (!is_animal_resource(type)) {
		fprintf(stderr,
		    "(take_animal_from_tile) this method cannot "
		    "be used for non-animal resource types.\n"
		);
		exit(1);
	}

	// Get the tile
	tile_state *tile = get_tile(player->board, x, y, z);

	// Get the counter for the animal resource on the tile
	int *on_tile = get_tile_resource(tile, type);

	// Assert the the player is not attempting to more
	// animals from the tile than there is.
	if (*on_tile < quantity) {
		const char *name = get_resource_name(type);
		fprintf(stderr,
		    "(take_animal_from_tile) cannot take %d %s from "
		    "tile %c%d, because the tile has only %d %s",
		    quantity, name, 'A'+y, x+1, *on_tile, name
		);
		exit(1);
	}

	// Integrity check: the player should have placed resources
	// more than or equal to number of resources on the tile.
	int *placed = get_placed_animal(player, type);
	if (*placed < quantity) {
		const char *name = get_resource_name(type);
		fprintf(stderr,
		    "(take_animal_from_tile) integrity failure: tile %c%d "
		    "has %d %s, but the player has only %d %s placed\n",
		    'A'+y, x+1, *on_tile, name, *placed, name
		);
		exit(1);
	}

	// Log command and execute
	log_command5(
	    &player->log,
	    CMD_TAKE_TILE_ANIMAL,
	    type, quantity,
	    x, y, z
	);

	// Remove from tile
	*on_tile -= quantity;

	// Remove from being placed
	*placed -= quantity;
}


static void drop_animal_to_tile(
    player_state *player,
    int x,
    int y,
    int z,
    int type,
    int quantity
) {
	if (!is_animal_resource(type)) {
		fprintf(stderr,
		    "(drop_animal_to_tile) this method cannot "
		    "be used for non-animal resource types.\n"
		);
		exit(1);
	}

	// Get the tile
	tile_state *tile = get_tile(player->board, x, y, z);

	// Get the counter for the animal resource on the tile
	int *on_tile = get_tile_resource(tile, type);

	int *total = get_animal(player, type);
	int *placed = get_placed_animal(player, type);
	int unplaced = (*total) - (*placed);

	// Assert the the player is not attempting to drop more
	// animals to the tile than there unplaced in his/her possession.
	if (unplaced < quantity) {
		const char *name = get_resource_name(type);
		fprintf(stderr,
		    "(drop_animal_to_tile) cannot drop %d %s to "
		    "tile %c%d, because there are only %d %s unplaced.\n",
		    quantity, name, 'A'+y, x+1, unplaced, name
		);
		exit(1);
	}

	// Log command and execute
	log_command5(
	    &player->log,
	    CMD_DROP_TILE_ANIMAL,
	    type, quantity,
	    x, y, z
	);

	// Drop to the tile
	*on_tile += quantity;

	// Mark as placed
	*placed += quantity;
}



static void take_resource_from_tile(
    player_state *player,
    int x,
    int y,
    int z,
    int type,
    int quantity
) {
	tile_state *tile = get_tile(player->board, x, y, z);
	int *on_tile = get_tile_resource(tile, type);

	if (is_animal_resource(type)) {
		fprintf(stderr,
		    "(take_resource_from_tile) this method cannot "
		    "be used for animal resource types.\n"
		);
		exit(1);
	}

	if (*on_tile < quantity) {
		const char *name = get_resource_name(type);
		fprintf(stderr,
		    "(take_resource_from_tile) "
		    "cannot take %d %s from tile %c%d, "
		    "because the tile has only %d %s",
		    quantity, name, 'A'+y, x+1, *on_tile, name
		);
		exit(1);
	}

	// Log command and execute
	log_command5(
	    &player->log,
	    CMD_TAKE_TILE_RESOURCE,
	    type, quantity,
	    x, y, z
	);

	// Remove from tile
	*on_tile -= quantity;

	// Add to player's supply
	add_resource(player, type, quantity);
}

static void drop_resource_to_tile(
    player_state *player,
    int x,
    int y,
    int z,
    int type,
    int quantity
) {
	tile_state *tile = get_tile(player->board, x, y, z);
	int *on_tile = get_tile_resource(tile, type);
	int *counter = get_resource(player, type);

	if (is_animal_resource(type)) {
		fprintf(stderr,
		    "(drop_resource_to_tile) this method cannot "
		    "be used for animal resource types.\n"
		);
		exit(1);
	}

	if (*counter < quantity) {
		const char *name = get_resource_name(type);
		fprintf(stderr,
		    "(drop_resource_to_tile) "
		    "cannot drop %d %s to tile %c%d, "
		    "because the personal supply has only %d %s",
		    quantity, name, 'A'+y, x+1, *on_tile, name
		);
		exit(1);
	}

	// If the tile is a Field and the player has Stubble room,
	// it is then possible that there is a single animal on
	// the tile. It needs to be picked up first.
	int animal_type = get_tile_animal_type(tile);
	if (animal_type != RESOURCE_NONE) {
		int num_animals = *get_tile_resource(tile, animal_type);
		take_animal_from_tile(
		    player, x, y, z,
		    animal_type, num_animals
		);
	}

	// Log command and execute
	log_command5(
	    &player->log,
	    CMD_DROP_TILE_RESOURCE,
	    type, quantity,
	    x, y, z
	);

	// Remove from player's supply
	sub_resource(player, type, quantity);

	// Drop to the tile.
	*on_tile += quantity;
}

static void take_tile_rewards(
    player_state *player,
    int x,
    int y,
    int z
) {
	tile_state *tile = get_tile(player->board, x, y, z);
	int type = tile->reward[0];
	int qty = tile->reward[1];

	if (type != RESOURCE_NONE) {
		gain_resource(player, type, qty);
	}
}

/**
 * Add resource to tile from the general supply.
 * This is needed when sowing fields. That is, the additional
 * Vegetable/Grain comes from the general supply.
 */
static void add_tile_resource(
    player_state *player,
    int x,
    int y,
    int z,
    int type,
    int delta
) {
	tile_state *tile = get_tile(player->board, x, y, z);
	int *counter = get_tile_resource(tile, type);

	log_command5(
	    &player->log,
	    CMD_ADD_TILE_RESOURCE,
	    type, delta,
	    x, y, z
	);

	// Execute the action
	*counter += delta;
}


static void take_action_resources(player_state *player, action_space *aspace) {
	// For convenience
	int counter = aspace->counter;
	// if the counter is zero, then this action space
	// does not accumulate any resources.
	if (counter == 0) return;

	log_command2(
	    &player->log,
	    CMD_TAKE_ACTION_RESOURCE,
	    aspace->type,
	    aspace->counter
	);

	// Take the resources on the action space.
	// At this point the action space in question
	// must be one that accumulates resources.
	switch(aspace->type) {
	case ACTION_DRIFT_MINING:
		add_resource(player, RESOURCE_STONE, counter);
		break;

	case ACTION_LOGGING:
		add_resource(player, RESOURCE_WOOD, counter);
		break;

	case ACTION_WOOD_GATHERING:
		add_resource(player, RESOURCE_WOOD, counter);
		break;

	case ACTION_EXCAVATION:
		add_resource(player, RESOURCE_STONE, counter);
		break;
	//case ACTION_CLEARING: // TODO

	//case ACTION_STARTING_PLAYER: // TODO
	case ACTION_ORE_MINING:
		add_resource(player, RESOURCE_ORE, counter);
		break;

	case ACTION_SUSTENANCE:
		add_resource(player, RESOURCE_FOOD, counter);
		break;

	case ACTION_RUBY_MINING:
		add_resource(player, RESOURCE_RUBY, counter);
		break;

	case ACTION_SHEEP_FARMING:
		add_resource(player, RESOURCE_SHEEP, counter);
		break;

	case ACTION_DONKEY_FARMING:
		add_resource(player, RESOURCE_DONKEY, counter);
		break;

	case ACTION_ORE_DELIVERY:
		add_resource(player, RESOURCE_STONE, counter);
		add_resource(player, RESOURCE_ORE, counter);
		break;

	case ACTION_RUBY_DELIVERY:
		add_resource(player, RESOURCE_RUBY, counter);
		break;
	default:
		fprintf(stderr,
		    "(take_action_resources) unhandled aspace->type: %d\n",
		    aspace->type
		);
		exit(1);
	}
	// Reset counter
	aspace->counter = 0;
}

/** game_state is used for error messaging AND discovering the action space. */
static int put_ruby_on_action(
    game_state *gs,
    player_state *player,
    int action_type
) {

	if (player->ruby == 0) {
		error(gs, E_RULES,
		    "Cannot pay a Ruby: the player has no Rubies left."
		);
		return 0;
	}

	action_space *aspace = get_action_space(gs, action_type);

	if (aspace == NULL) {
		error(gs, E_RULES,
		    "No such action space type: %d",
		    action_type
		);
		return 0;
	}

	if (aspace->counter < 6) {
		error(gs, E_RULES,
		    "The action space \"%s\" will not be reset "
		    "at the beginning of the next round.",
		    caverna_get_action_name(action_type)
		);
		return 0;
	}

	if (aspace->has_ruby) {
		error(gs, E_RULES,
		    "The action space \"%s\" has already a Ruby on it",
		    caverna_get_action_name(action_type)
		);
		return 0;
	}


	log_command2(
	    &player->log,
	    CMD_PUT_RUBY_ON_ACTION,
	    action_type, 0
	);
	sub_resource(player, RESOURCE_RUBY, 1);
	aspace->has_ruby = 1;

	return 1;
}

/**
 * Triggers always when a resource is gained.
 * type is the resource type gained, and count is a positive
 * number how much the resource were gained.
 */
static void trigger_resource_effect(
    player_state *player,
    int type,
    int value
) {
	switch(type) {
	case RESOURCE_DOG:
		if (has_tile(player, TILE_DOG_SCHOOL)) {
			// Gain +1 Wood for every new Dog.
			gain_resource(player, RESOURCE_WOOD, value*1);
		}
		break;
	case RESOURCE_STONE:
		if (has_tile(player, TILE_SEAM)) {
			// Gain +1 Ore for each new Stone
			gain_resource(player, RESOURCE_ORE, value*1);
		}
		break;
	default:
		// No effect
		break;
	}
}

/**
 * Triggered always when a resource conversion takes place
 * type is the conversion type.
 */
static void trigger_conversion_effect(
    player_state *player,
    int conversion,
    int count
) {
	switch(conversion) {
	case CONV_SHEEP_TO_FOOD:
	case CONV_DONKEY_TO_FOOD:
	case CONV_BOAR_TO_FOOD:
	case CONV_CATTLE_TO_FOOD:
		if (has_tile(player, TILE_SLAUGHTERING_CAVE)) {
			// Gain +1 Food for each farm animal
			// converted into Food.
			add_resource(player, RESOURCE_FOOD, count*1);
		}
		break;
	}
}


static void trigger_newborn_effects(player_state *player) {
	if (has_tile(player, TILE_QUARRY)) {
		if (player->newborn_sheep) {
			gain_resource(
			    player,
			    RESOURCE_STONE, player->newborn_sheep
			);
		}
	}
	if (has_tile(player, TILE_BREEDING_CAVE)) {
		int types = (player->newborn_sheep > 0)
		    + (player->newborn_donkey > 0)
		    + (player->newborn_boar > 0)
		    + (player->newborn_cattle > 0);

		int food = (types == 4) ? 5 : types;

		if (food > 0) {
			gain_resource(
			    player,
			    RESOURCE_FOOD, food
			);
		}
	}
}

static int pay_price(
    game_state *gs,
    player_state *player,
    const int *price
) {
	for (int i = 0; i < 3; i++) {
		int resource = price[i*2+0];
		int cost = price[(i*2)+1];

		if (resource == RESOURCE_NONE) break;

		int success = pay_resource(gs, player, resource, cost);
		if (!success) return 0;
	}
	return 1;
}

static int take_furnishing(
    player_state *player,
    game_state *gs,
    int type
) {
	// Get player number
	int player_num = get_player_num(gs, player);
	if (player_num == -1) {
		error(gs, E_INTERNAL,
		    "No such player in the game: %p",
		    player
		);
		return 0;
	}

	furnishing_state *furnishing = get_furnishing(gs, type);
	if (furnishing == NULL) {
		error(gs, E_INTERNAL,
		    "No such furnishing tile type: %d",
		    type
		);
		return 0;
	}

	if (furnishing->taken_by != -1) {
		error(gs, E_INTERNAL,
		    "The furnishing tile \"%s\" has already been "
		    "taken by player %d",
		    get_tile_name(type),
		    furnishing->taken_by
		);
		return 0;
	}

	// Log and execute
	// Log action and execute
	log_command2(
	    &player->log,
	    CMD_TAKE_FURNISHING,
	    type, 0
	);

	// Ordinary Dwelling tiles are considered unlimited,
	// and therefore that type is not taken by any player.
	if (furnishing->type != TILE_DWELLING) {
		furnishing->taken_by = player_num;
	}

	return 1;
}

/** game_state is required only for error messaging */
static int grow_family(player_state *player, game_state *gs) {
	int num_occupied = player->dwarfs + player->children;
	if (num_occupied == MAX_DWARFS) {
		error(gs, E_RULES,
		    "The player has six Dwarfs already. "
		    "Cannot do further family growth."
		);
		return 0;
	}

	int has_additional_dwelling
	    = has_tile(player, TILE_ADDITIONAL_DWELLING);

	int capacity = num_rooms_in_dwellings(player->board);

	if ((num_occupied == 5) && (!has_additional_dwelling)) {
		error(gs, E_RULES,
		    "The player has five Dwarfs, and the sixth Dwarf can be "
		    "accommodated only to the Additional dwelling, which "
		    "the player does not have."
		);
		return 0;
	} else if ((num_occupied <= 4) && (num_occupied == capacity)) {
		error(gs, E_RULES,
		    "There is no room in Dwellings for a new Dwarf"
		);
		return 0;
	}

	// Log and execute
	log_command2(
	    &player->log,
	    CMD_GROW_FAMILY,
	    0, 0
	);
	player->children++;

	return 1;
}


static void set_phase(game_state *gs, int phase) {
	// Log and execute
	log_command2(
	    &gs->log,
	    CMD_SET_PHASE,
	    phase, gs->phase
	);
	gs->phase = phase;
}

static void set_current_player(game_state *gs, int cur_player) {
	// Log and execute
	log_command2(
	    &gs->log,
	    CMD_SET_CURRENT_PLAYER,
	    cur_player, gs->cur_player
	);
	gs->cur_player = cur_player;
}

static void set_harvest(game_state *gs, int harvest) {
	// Log and execute
	log_command2(
	    &gs->log,
	    CMD_SET_HARVEST,
	    harvest, gs->harvest
	);
	gs->harvest = harvest;
}

static void set_breed(game_state *gs, int breed) {
	// Log and execute
	log_command2(
	    &gs->log,
	    CMD_SET_BREED,
	    breed, gs->breed
	);
	gs->breed = breed;
}

static void lay_stable(player_state *player, int x, int y, int z) {
	tile_state *tile = get_tile(player->board, x, y, z);

	// Log and execute
	log_command5(
	    &player->log,
	    CMD_LAY_STABLE,
	    x, y, z, 0, 0
	);
	player->stable++;
	tile->stable++;
}

static void set_weapon(player_state *player, int dwarf_num, int strength) {
	// Log and execute
	log_command2(
	    &player->log,
	    CMD_SET_WEAPON,
	    dwarf_num, strength
	);
	player->weapons[dwarf_num] = strength;
}

static void increase_weapon(player_state *player, int dwarf_num) {
	int *weapon = &player->weapons[dwarf_num];
	if (*weapon < MAX_WEAPON_STRENGTH) {
		// Log and execute
		log_command2(
		    &player->log,
		    CMD_INCREASE_WEAPON,
		    dwarf_num, 0
		);
		(*weapon)++;
	}
}

static void increase_all_weapons(player_state *player) {
	int delta[MAX_DWARFS];

	// Build the message first.
	for (int i = 0; i < MAX_DWARFS; i++) {
		int weapon = player->weapons[i];
		int increase
		    = (weapon > 0) && (weapon < MAX_WEAPON_STRENGTH);
		delta[i] = increase ? 1 : 0;
	}
	// Log and execute
	log_command6(
	    &player->log,
	    CMD_INCREASE_ALL_WEAPONS,
	    delta[0], delta[1], delta[2],
	    delta[3], delta[4], delta[5]
	);

	for (int i = 0; i < player->dwarfs; i++) {
		player->weapons[i] += delta[i];
	}
}

static void convert_weapons_to_food(player_state *player) {
	const int *weapons = player->weapons; // For convenience

	log_command6(
	    &player->log,
	    CMD_CONVERT_WEAPONS_TO_FOOD,
	    weapons[0], weapons[1], weapons[2],
	    weapons[3], weapons[4], weapons[5]
	);
	for (int i = 0; i < 6; i--) {
		add_resource(player, RESOURCE_FOOD, player->weapons[i]);
		player->weapons[i] = 0;
	}
}


/**
 * player_state is required due to action/command log.
 */
static int lay_tile(player_state *player, int x, int y, int type, int dir) {
	tile_state *board = player->board; // for convenience
	int z = get_depth(board, x, y);
	if (z == BOARD_DEPTH) {
		fprintf(stderr,
		    "(lay_tile) maximum depth reached\n"
		);
		exit(1);
	}

	log_command5(
	    &player->log,
	    CMD_LAY_TILE, type,
	    x, y, z, dir
	);

	tile_state *tile = get_tile(board, x, y, z);
	// Set the tile type
	tile->type = type;
	// Set direction, if any
	tile->dir = dir;
	// Reset the number of rounds the tile has been around.
	tile->rounds = 0;

	return 1;
}



/**
 * game_state needed only for the error reporting.
 */
/*
static int expect_coordinates_within(
    game_state *gs,
    player_state *player,
    int x, int y,
    int part
) {
	// Limits for the tile placements within the board part
	int xmin, ymin, xmax, ymax;
	const char *part_name = NULL;
	if (part == BOARD_FOREST) {
		get_forest_limits(player, &xmin, &ymin, &xmax, &ymax);
		part_name = "forest";
	} else if (part == BOARD_MOUNTAIN) {
		get_mountain_limits(player, &xmin, &ymin, &xmax, &ymax);
		part_name = "mountain";
	} else {
		error(gs, E_ORDERS,
		    "(Probably a bug) unknown board part: %d", part);
		return 0;
	}

	if (!are_coordinates_within(x, y, xmin, ymin, xmax, ymax)) {
		error(gs, E_ORDERS,
		    "Coordinate %c%d is not within "
		    "the %s\'s limits x=%d..%d, y=%c..%c",
		    'A'+y, x+1,
		    part_name,
		    xmin+1, xmax+1, 'A'+ymin, 'A'+ymax
		);
		return 0;
	}
	return 1;
}
*/

/*
static int expect_within_forest(
    game_state *gs,
    player_state *player,
    int x, int y
) {
	return expect_coordinates_within(
	    gs, player, x, y, BOARD_FOREST);
}

static int expect_within_mountain(
    game_state *gs,
    player_state *player,
    int x, int y
) {
	return expect_coordinates_within(
	    gs, player, x, y, BOARD_MOUNTAIN);
}
*/

static void copy_tile_contents_to_top(
    player_state *player, int x, int y, int z
) {
	const tile_state *tile = get_tile(player->board, x, y, z);
	int ztop;
	tile_state *top = get_top_tile(player->board, x, y, &ztop);

	// Copy Farm animals and dogs.
	top->dog = tile->dog;
	top->sheep = tile->sheep;
	top->donkey = tile->donkey;
	top->boar = tile->boar;
	top->cattle = tile->cattle;

	// Copy stables
	top->stable = tile->stable;
}


static int lay_single_tile(
    game_state *gs,
    player_state *player,
    const tile_placement *placement,
    int type,
    int underneath
) {
	// For convenience
	int x = placement->x;
	int y = placement->y;

	int part = -1; // TODO: BOARD_NONE sounds stupid, so use BPART_NONE?

	switch(underneath) {
	case TILE_FOREST:
	case TILE_MEADOW:
		part = BOARD_FOREST;
		break;
	case TILE_MOUNTAIN:
	case TILE_TUNNEL:
	case TILE_DEEP_TUNNEL:
	case TILE_CAVERN:
		part = BOARD_MOUNTAIN;
		break;
	};

	if (part == -1) {
		error(gs, E_ORDERS,
		    "(Probably a bug) unexpected underneath tile type: %d",
		    underneath
		);
		return 0;
	}

	// Limits for the tile placements within the board part
	int xmin, ymin, xmax, ymax;
	const char *part_name; // board part name
	switch(part) {
	case BOARD_FOREST:
		get_forest_limits(player, &xmin, &ymin, &xmax, &ymax);
		part_name = "forest";
		break;
	case BOARD_MOUNTAIN:
		get_mountain_limits(player, &xmin, &ymin, &xmax, &ymax);
		part_name = "mountain";
		break;
	default:
		fprintf(stderr,
		    "(lay_single_tile) unhandled board part: %d",
		    part
		);
		exit(1);
	}

	if (!are_coordinates_within(x, y, xmin, ymin, xmax, ymax)) {
		error(gs, E_ORDERS,
		    "Coordinate %c%d is not within "
		    "the %s\'s limits x=%d..%d, y=%c..%c",
		    'A'+y, x+1,
		    part_name,
		    xmin+1, xmax+1, 'A'+ymin, 'A'+ymax
		);
		return 0;
	}

	// Validate the underlying tile
	int z;
	const tile_state *top = get_top_tile(player->board, x, y, &z);
	if (top->type != underneath) {
		error(gs, E_ORDERS,
		    "Coordinates %c%d do not have %s tile "
		    "underneath, but %s tile instead",
		    'A'+y, x+1,
		    get_tile_name(underneath),
		    get_tile_name(top->type)
		);
		return 0;
	}

	// If the tile underneath is either TILE_MOUNTAIN or TILE_FOREST,
	// The placement must be adjacent to another landscape tile.
	if ((underneath == TILE_MOUNTAIN) || (underneath == TILE_FOREST)) {
		if (!has_adjacent_other_than(
		    player->board, x, y, underneath))
		{
			error(gs, E_ORDERS,
			    "Coordinates %c%d are not adjacent "
			    "to a non-%s tile\n",
			    'A'+y, x+1,
			    get_tile_name(underneath)
			);
			return 0;
		}
	}

	// At this point the operation will succeed.

	// Everything is valid. Lay the tile
	lay_tile(player, x, y, type, DIRECTION_NONE);

	// TILE_FIELD cannot be placed over a tile which contains a Stable.
	if ( (type == TILE_FIELD) && (top->stable > 0) ) {
		error(gs, E_ORDERS,
		    "Cannot place a Field tile at the Coordinates %c%d, "
		    "because there is a Stable underneath.",
		    'A'+y, x+1
		);
		return 0;
	}

	// Pick resources from the top forest/mountain tiles,
	// if there are any. Otherwise transport (or simply copy?)
	// the tile contents (stables, farm animals, crops)
	// to the new top tile.
	if ((underneath == TILE_FOREST) || (underneath == TILE_MOUNTAIN)) {
		take_tile_rewards(player, x, y, z);
		// NOTE: Single tiles cannot be overhung.
	}

	// Transport tile contents
	copy_tile_contents_to_top(player, x, y, z);

	return 1;
}

static int lay_twin_tile(
    game_state *gs,
    player_state *player,
    const tile_placement *placement,
    int type1,
    int type2,
    int underneath
) {
	tile_state *board = player->board;
	// Lot more difficult to asses...
	// Need the player board
	// 1) both coordinates are within the mountain
	//    (the size of the mountain depends on the office room)
	// 2) both coordinates have a "mountain tile" underneath.
	// 3) at least one coordinate is adjacent to a non-mountain tile.
	// 4) If there are resources on the underlying mountain tile, gain those.
	// 5) If the placement is hanging, gain 2 GP.
	int x1, y1, z1, x2, y2, z2;

	// call somethign that will populate all these six variables
	// and verifies that they form a legal placement

	get_both_coordinates(placement, &x1, &y1, &x2, &y2);

	// Limits for the tile placements
	int xmin, ymin, xmax, ymax;
	// Name of the board part
	const char *side = NULL;

	// Get either mountain limits or forest limits
	// depending on the underneath tile type.
	if ((underneath == TILE_MOUNTAIN)
	    || (underneath == TILE_TUNNEL))
	{
		get_mountain_limits(player, &xmin, &ymin, &xmax, &ymax);
		side = "mountain";
	} else if ((underneath == TILE_FOREST)
	    || (underneath == TILE_MEADOW))
	{
		get_forest_limits(player, &xmin, &ymin, &xmax, &ymax);
		side = "forest";
	} else {
		fprintf(stderr,
		    "(lay_twin_tile) unexpected underneath tile type: %d\n",
		    underneath
		);
		exit(1);
	}

	if (!are_coordinates_within(x1, y1, xmin, ymin, xmax, ymax)) {
		error(gs, E_ORDERS,
		    "Coordinate %c%d is not within "
		    "the %s\'s limits x=%d..%d, y=%c..%c",
		    'A'+y1, x1+1,
		    side,
		    xmin+1, xmax+1, 'A'+ymin, 'A'+ymax
		);
		return 0;
	}
	if (!are_coordinates_within(x2, y2, xmin, ymin, xmax, ymax)) {
		error(gs, E_ORDERS,
		    "Coordinate %c%d is not within "
		    "the %s\'s limits x=%d..%d, y=%c..%c",
		    'A'+y2, x2+1,
		    side,
		    xmin+1, xmax+1, 'A'+ymin, 'A'+ymax
		);
		return 0;
	}

	tile_state *top1 = get_top_tile(board, x1, y1, &z1);
	tile_state *top2 = get_top_tile(board, x2, y2, &z2);

	if (top1->type != underneath) {
		error(gs, E_ORDERS,
		    "Coordinates %c%d do not have "
		    "%s tile underneath, but %s tile instead",
		    'A'+y1, x1+1,
		    get_tile_name(underneath),
		    get_tile_name(top1->type)
		);
		return 0;
	}
	if (top2->type != underneath) {
		error(gs, E_ORDERS,
		    "Coordinates %c%d do not have "
		    "%s tile underneath, but %s tile instead",
		    'A'+y2, x2+1,
		    get_tile_name(underneath),
		    get_tile_name(top2->type)
		);
		return 0;
	}

	// TILE_FIELD cannot be placed over a tile which contains a Stable.
	if ( ((type1 == TILE_FIELD) && (top1->stable > 0))
	    || ((type2 == TILE_FIELD) && (top2->stable > 0)) )
	{
		int x = x1;
		int y = y1;
		if (type2 == TILE_FIELD) {
			x = x2;
			y = y2;
		}

		error(gs, E_ORDERS,
		    "Cannot place a Field tile at the Coordinates %c%d, "
		    "because there is a Stable underneath.",
		    'A'+y, x+1
		);
		return 0;
	}

	// If the tile underneath is either TILE_MOUNTAIN or TILE_FOREST,
	// The placement must be adjacent to another landscape tile.
	if ((underneath == TILE_MOUNTAIN)
	    || (underneath == TILE_FOREST))
	{
		if ((!has_adjacent_other_than(board, x1, y1, underneath))
		    && (!has_adjacent_other_than(board, x2, y2, underneath)))
		{
			error(gs, E_ORDERS,
			    "Neither coordinates %c%d nor %c%d "
			    "are adjacent to a non-%s tile\n",
			    'A'+y1, x1+1, 'A'+y2, x2+1,
			    get_tile_name(underneath)
			);
			return 0;
		}
	}

	// At this point the operation will succeed.

	int dir1 = placement->dir;
	int dir2 = get_opposite_direction(dir1);

	lay_tile(player, x1, y1, type1, dir1);
	lay_tile(player, x2, y2, type2, dir2);

	// Pick resources from the top forest/mountain tiles,
	// if there are any. Otherwise transport (or simply copy?)
	// the tile contents (stables, farm animals, crops)
	// to the new top tile.
	// Also, gain +2 Gold if overhung.
	if ((underneath == TILE_FOREST) || (underneath == TILE_MOUNTAIN)) {
		take_tile_rewards(player, x1, y1, z1);
		take_tile_rewards(player, x2, y2, z2);

		if (is_overhung(x1, y1) || is_overhung(x2, y2)) {
			// TODO: enable trigger effect
			//trigger_effect(player, TILE_OFFICE_ROOM, 1);
			gain_resource(player, RESOURCE_GOLD, 2);
		}
	}

	// Transport tile contents to the top
	copy_tile_contents_to_top(player, x1, y1, z1);
	copy_tile_contents_to_top(player, x2, y2, z2);

	return 1;
}

/** This action always succeeds. */
static void discount_price(
    player_state *player,
    int builder_effect,
    int is_furnishing,
    int *price
) {
	// Apply discount effects

	int has_carpenter = has_tile(player, TILE_CARPENTER);
	int has_stone_carver = has_tile(player, TILE_STONE_CARVER);
	int has_builder = has_tile(player, TILE_BUILDER);

	// If the player does not have Builder, reset the effect.
	// Also, if the Builder effect is available only to Furnishing
	// tile prices, which leaves Pastures and Stables out of its reach.
	if ((!has_builder) || (!is_furnishing)) {
		builder_effect = BUILDER_REPLACE_NONE;
	}

	// Carpenter and Stone Carver apply to
	// Furnishing tiles and Landscape tiles.
	// Stone Carver applies also to Stables.

	// Both affect:

	// Action: Furnish a Cavern
	// Loot item: Furnish a Cavern
	// Action: Furnish a Dwelling
	// Loot item: Furnish an ordinary Dwelling

	// In addition, Stone Carver affects also:

	// Action: Fence a small/large Pasture.
	// Loot item: Fence a small/large Pasture.

	// (Note: looted Stable is free anyway).

	if (has_carpenter) {
		// -1 Wood
		int *wood_cost = get_price_resource(price, RESOURCE_WOOD);
		if ((wood_cost != NULL) && (*wood_cost > 0)) {
			(*wood_cost)--;
		}
	}

	if (has_stone_carver) {
		// -1 Stone
		int *stone_cost = get_price_resource(price, RESOURCE_STONE);
		if ((stone_cost != NULL) && (*stone_cost > 0)) {
			(*stone_cost)--;
		}
	}

	if ((has_builder) && (builder_effect != BUILDER_REPLACE_NONE)) {
		int *wood_cost = get_price_resource(price, RESOURCE_WOOD);
		int *stone_cost = get_price_resource(price, RESOURCE_STONE);

		int *ore_cost = get_price_resource(price, RESOURCE_ORE);
		if (ore_cost == NULL) {
			ore_cost = set_price_resource(
			    price, RESOURCE_ORE, 0);
		}

		if ( ((builder_effect & BUILDER_REPLACE_WOOD) != 0)
		    && (wood_cost != NULL) && (*wood_cost > 0) )
		{
			// -1 Wood, +1 Ore
			(*wood_cost)--;
			(*ore_cost)++;
		}

		if ( ((builder_effect & BUILDER_REPLACE_STONE) != 0)
		    && (stone_cost != NULL) && (*stone_cost > 0) )
		{
			// -1 Stone, +1 Ore
			(*stone_cost)--;
			(*ore_cost)++;
		}
	}
}

/** game_state is probably only for error messaging in lay tile. */
static int fence_small_pasture(
    game_state *gs,
    player_state *player,
    const tile_placement *placement,
    int cost_wood
) {
	// Create price
	int price[3*2] = {
	    RESOURCE_WOOD, cost_wood
	};

	// Discount price
	discount_price(player, BUILDER_REPLACE_NONE, 0, price);

	// Attempt payment
	int success = pay_price(gs, player, price);
	if (!success) return 0;

	// Attempt to lay the single-tile
	success = lay_single_tile(
	    gs, player, placement,
	    TILE_SMALL_PASTURE, // type
	    TILE_MEADOW // tile underneath
	);
	if (!success) return 0;

	return 1;
}

static int fence_large_pasture(
    game_state *gs,
    player_state *player,
    const tile_placement *placement,
    int cost_wood
) {
	// Create price
	int price[3*2] = {
	    RESOURCE_WOOD, cost_wood
	};

	// Discount price
	discount_price(player, BUILDER_REPLACE_NONE, 0, price);

	// Attempt payment
	int success = pay_price(gs, player, price);
	if (!success) return 0;

	// Attempt to lay the twin-tile
	success = lay_twin_tile(
	    gs, player, placement,
	    TILE_LARGE_PASTURE, TILE_LARGE_PASTURE, // tile1, tile2
	    TILE_MEADOW // tile underneath
	);
	if (!success) return 0;

	return 1;
}

static int build_stable(
    game_state *gs,
    player_state *player,
    const tile_placement *placement,
    int cost_stone
) {
	// Pre-compute price
	int price[3*2] = {
	    RESOURCE_STONE, cost_stone
	};
	discount_price(player, BUILDER_REPLACE_NONE, 0, price);

	// Count the stables, because there is a limit.
	if (player->stable == 3) {
		error(gs, E_ORDERS,
		    "Cannot build another Stable, because "
		    "the player has already 3 Stables."
		);
		return 0;
	}

	// Forest limits
	int xmin, ymin, xmax, ymax;
	get_forest_limits(player, &xmin, &ymin, &xmax, &ymax);

	// For convenience
	int x = placement->x;
	int y = placement->y;

	// Validate coordinates
	if (!are_coordinates_within(x, y, xmin, ymin, xmax, ymax)) {
		error(gs, E_ORDERS,
		    "Coordinate %c%d is not within "
		    "the %s\'s limits x=%d..%d, y=%c..%c",
		    'A'+y, x+1,
		    "forest",
		    xmin+1, xmax+1, 'A'+ymin, 'A'+ymax
		);
		return 0;
	}

	// Validate the underlying tile
	int z;
	tile_state *top = get_top_tile(player->board, x, y, &z);
	if ((top->type != TILE_FOREST)
	    && (top->type != TILE_MEADOW)
	    && (top->type != TILE_SMALL_PASTURE)
	    && (top->type != TILE_LARGE_PASTURE))
	{
		error(gs, E_ORDERS,
		    "Coordinates %c%d do not have %s tile "
		    "underneath, but %s tile instead",
		    'A'+y, x+1,
		    "Forest, Meadow, nor Pasture",
		    get_tile_name(top->type)
		);
		return 0;
	}

	if (top->stable > 0) {
		error(gs, E_ORDERS,
		    "Tile at coordinates %c%d does already "
		    "have a Stable.",
		    'A'+y, x+1
		);
		return 0;
	}

	// Pay the discounted price only if the nominal price is non-zero
	if (cost_stone > 0) {
		int success = pay_price(gs, player, price);
		if (!success) return 0;
	}

	// Put the stable onto the board
	lay_stable(player, x, y, z);

	return 1;
}

/**
 * Returns zero if there is no such Furnishing tile.
 */
static int get_tile_price(
    int type,
    player_state *player,
    int builder_effect,
    int *price
) {

	// Get the Furnishing tile configuration,
	// which contains the nominal price.
	const furnishing_config *cfg = get_furnishing_config(type);

	if (cfg == NULL) {
		return 0;
	}

	// Make a copy of the price
	memcpy(price, cfg->price, sizeof(cfg->price));

	// Apply discount effects
	discount_price(player, builder_effect, 1, price);

	return 1;
}


// NOTE: game_state is required only for error code and message.
static int pay_furnishing_tile(
    game_state *gs,
    player_state *player,
    int type,
    int builder_effect
) {
	// Tile price
	int price[3*2];

	// Get the price
	int success = get_tile_price(type, player, builder_effect, price);
	if (!success) {
		error(gs, E_ORDERS,
		    "No such furnishing tile: %d", type
		);
		return 0;
	}

	// Pay the price
	success = pay_price(gs, player, price);
	if (!success) return 0;

	return 1;
}

static void trigger_furnish_effect(
    player_state *player,
    int type,
    int x,
    int y
) {
	switch(type) {
	case TILE_STONE_CARVER:
		// +2 Stone
		gain_resource(player, RESOURCE_STONE, 2);
		break;
	case TILE_BLACKSMITH:
		// +2 Ore
		gain_resource(player, RESOURCE_ORE, 2);
		break;
	case TILE_WEAVING_PARLOR:
		// +1 Food per Sheep
		gain_resource(player, RESOURCE_FOOD, 1*player->sheep);
		break;
	case TILE_MILKING_PARLOR:
		// +1 Food per Cow
		gain_resource(player, RESOURCE_FOOD, 1*player->cattle);
		break;
	case TILE_STATE_PARLOR:
		// +2 Food per adjacent Dwelling
		gain_resource(
		    player,
		    RESOURCE_FOOD,
		    2*num_adjacent_dwellings(player->board, x, y)
		);
		break;
	default:
		// No immediate effect
		break;
	}
}

static int lay_furnishing_tile(
    game_state *gs,
    player_state *player,
    int type,
    int x,
    int y
) {
	// Get Mountain limits
	int xmin, ymin, xmax, ymax;
	get_mountain_limits(player, &xmin, &ymin, &xmax, &ymax);

	// Verify the coordinates are valid
	if (!are_coordinates_within(x, y, xmin, ymin, xmax, ymax)) {
		error(gs, E_ORDERS,
		    "Coordinate %c%d is not within "
		    "the mountain\'s limits x=%d..%d, y=%c..%c",
		    'A'+y, x+1, xmin+1, xmax+1, 'A'+ymin, 'A'+ymax
		);
		return 0;
	}

	int z;
	tile_state *top = get_top_tile(player->board, x, y, &z);

	// Check Trader/Spare part storage mutual exclusion.
	// A player who has already built the Spare part storage and
	// decides to build the Trader as well must place the Trader
	// on top of the Spare part storage, thus overbuilding
	// the Spare part storage. (Do not return the Spare part
	// storage to the general supply.) He cannot use the Spare part
	// storage any longer and does not get any points at the end
	// of the game for it. The same applies if a player has already
	// built the Trader and decides to build the Spare part storage.
	// (Appendix, p. A4)
	int mutually_exclusive = 0;
	int underneath_type = TILE_NONE;

	if ( (type == TILE_SPARE_PART_STORAGE)
	    && has_tile(player, TILE_TRADER) )
	{
		underneath_type = TILE_TRADER;
		mutually_exclusive = 1;
	}
	else if ( (type == TILE_TRADER)
	    && has_tile(player, TILE_SPARE_PART_STORAGE) )
	{
		underneath_type = TILE_SPARE_PART_STORAGE;
		mutually_exclusive = 1;
	}

	// If the player has Work room, he/she is able to furnish
	// Tunnel and Deep Tunnel tiles also, in addition to
	// ordinary Tunnel tiles.

	if (mutually_exclusive) {
		const char *tile_name = get_tile_name(type);
		const char *top_name = get_tile_name(top->type);
		const char *underneath_name = get_tile_name(underneath_type);

		if (top->type != underneath_type) {
			error(gs, E_ORDERS,
			    "The %s must be built on top of the %s. "
			    "The coordinates %c%d do not have the %s "
			    "underneath, but %s tile instead",
			    tile_name, underneath_name,
			    'A'+y, x+1, underneath_name,
			    top_name
			);
			return 0;
		}
	}
	else if (!has_tile(player, TILE_WORK_ROOM)) {
		if (top->type != TILE_CAVERN) {
			error(gs, E_ORDERS,
			    "Coordinates %c%d do not have Cavern tile "
			    "underneath, but %s tile instead",
			    'A'+y, x+1, get_tile_name(top->type)
			);
			return 0;
		}
	} else if ( (top->type != TILE_CAVERN)
	    && (top->type != TILE_TUNNEL)
	    && (top->type != TILE_DEEP_TUNNEL) )
	{
		error(gs, E_ORDERS,
		    "Coordinates %c%d do not have Cavern, Tunnel, "
		    "or Deep Tunnel tile underneath, "
		    "but %s tile instead",
		    'A'+y, x+1, get_tile_name(top->type)
		);
		return 0;
	}

	// Placement has now been verified.

	// Take the Furnishing tile (ordinary Dwellings are unlimited)
	int success = take_furnishing(player, gs, type);
	if (!success) return 0;

	// Lay the tile.
	lay_tile(player, x, y, type, DIRECTION_NONE);

	// Execute any immediate effect the tile may have.
	trigger_furnish_effect(player, type, x, y);

	return 1;
}

static int furnish_tile(
    game_state *gs,
    player_state *player,
    int type,
    int x,
    int y,
    int builder_effect
) {
	// At this point the placement is OK!
	int success = pay_furnishing_tile(gs, player, type, builder_effect);
	if (!success) return 0;

	success = lay_furnishing_tile(gs, player, type, x, y);
	if (!success) return 0;

	return 1;
}

static int furnish_looted_dwelling(
    game_state *gs,
    player_state *player,
    const tile_placement *placement,
    int builder_effect
) {
	// Ordinary Dwelling costs 2 Wood + 2 Stone as a loot item.
	int price[3*2] = {
		RESOURCE_WOOD, 2,
		RESOURCE_STONE, 2
	};
	discount_price(player, builder_effect, 1, price);

	// Attempt payment
	int success = pay_price(gs, player, price);
	if (!success) return 0;

	success = lay_furnishing_tile(
	    gs, player, TILE_DWELLING, placement->x, placement->y);
	if (!success) return 0;

	return 1;
}

static int validate_either_or(
    game_state *gs,
    player_state *player,
    int do_action1,
    int do_action2
) {
	int has_guest_room = has_tile(player, TILE_GUEST_ROOM);
	if ( (!has_guest_room) && (do_action1) && (do_action2) ) {
		// This is an "either ... or" action space,
		// so a player without Guest room cannot do both
		// actions.
		error(gs, E_ORDERS,
		    "This is an \"either ... or\" action space. "
		    "Without the Guest room both actions cannot "
		    "be done simultaneously."
		);
		return 0;
	}
	return 1;
}


static int sow_crops(
    game_state *gs,
    player_state *player,
    const crop_placement *crops
) {
	// Get forest limits
	int xmin, ymin, xmax, ymax;
	get_forest_limits(player, &xmin, &ymin, &xmax, &ymax);

	// Quickly validate the crops
	int sown_grain = 0;
	int sown_vegetable = 0;
	for (int i = 0; i < 4; i++) {
		// For convenience
		const crop_placement *sow = &crops[i];
		int x = sow->x;
		int y = sow->y;
		int z; // will be set later on
		int type = sow->type;

		if (type == RESOURCE_NONE) {
			// Unused. Skip
			continue;
		}
		else if (type == RESOURCE_GRAIN) {
			sown_grain++;
		} else if (type == RESOURCE_VEGETABLE) {
			sown_vegetable++;
		} else {
			error(gs, E_ORDERS,
			    "(Likely a bug) Neither Grain nor Vegetable to sow. "
			    "Unexpected resource type: %d",
			    type
			);
			return 0;
		}
		if ((sown_grain > 2) || (sown_vegetable > 2)) {
			error(gs, E_ORDERS,
			    "Cannot sow more than 2 Grain and 2 Vegetable"
			);
			return 0;
		}

		if ( ((type == RESOURCE_GRAIN)
		    && (player->grain == 0))
		    || ((type == RESOURCE_VEGETABLE)
		    && (player->vegetable == 0)) )
		{
			const char *name = get_resource_name(type);
			error(gs, E_ORDERS,
			    "Cannot sow %s: there is no %s "
			    "left in the personal supply.",
			    name, name
			);
			return 0;
		}

		// Validate the coordinates
		if (!are_coordinates_within(x, y, xmin, ymin, xmax, ymax)) {
			error(gs, E_ORDERS,
			    "Coordinates %c%d are not within "
			    "the forest\'s limits x=%d..%d, y=%c..%c",
			    'A'+y, x+1, xmin+1, xmax+1, 'A'+ymin, 'A'+ymax
			);
			return 0;
		}

		// Otherwise, get the top tile at the location
		tile_state *top = get_top_tile(player->board, x, y, &z);
		// top != NULL, because we are within forest limits.

		// Validate tile type
		if (top->type != TILE_FIELD) {
			error(gs, E_ORDERS,
			    "Coordinates %c%d do not have Field tile, "
			    "but %s tile instead",
			    'A'+y, x+1, get_tile_name(top->type)
			);
			return 0;
		}

		// Validate the field is empty
		if ((top->grain != 0) || (top->vegetable != 0)) {
			error(gs, E_ORDERS,
			    "The field at Coordinates %c%d is not empty! "
			    "It has %d %s already",
			    'A'+y, x+1,
			    top->grain != 0 ? top->grain : top->vegetable,
			    top->grain != 0 ? "Grain" : "Vegetable"
			);
			return 0;
		}


		// If this point is reached, sowing is a valid action.
		// Carry on.
		int bonus = 0;
		if (type == RESOURCE_GRAIN) {
			bonus = 2;
		} else if (type == RESOURCE_VEGETABLE) {
			bonus = 1;
		} else {
			fprintf(stderr,
			    "(sow_crops) unhandled resource type: %d\n",
			    type
			);
			exit(1);
		}

		// Drop one crop to the tile
		drop_resource_to_tile(
		    player,
		    x, y, z,
		    type, 1
		);
		// Receive immediately few more.
		add_tile_resource(
		    player,
		    x, y, z,
		    type, bonus
		);
	}
	return 1;
}

static int forge_weapon(
    game_state *gs,
    player_state *player,
    int dwarf_num,
    int strength
) {
	if (player->weapons[dwarf_num] > 0) {
		error(gs, E_RULES,
		    "Cannot forge Weapon, because the Dwarf "
		    "has already strength %d Weapon",
		    player->weapons[dwarf_num]
		);
		return 0;
	}

	// Validate strength
	if ((strength < 0) || (strength > 8)) {
		error(gs, E_RULES,
		    "You can only forge a Weapon with a strength 1-8. "
		    "The Weapon strength specified is out of bounds: %d",
		    strength
		);
		return 0;
	}

	// Compute the price
	int cost = strength;

	// Apply Blacksmith discount (-2 Ore), and saturate.
	if (has_tile(player, TILE_BLACKSMITH)) cost -= 2;
	if (cost < 0) cost = 0;

	// Everything okay. Pay the price and forge the weapon
	int success = pay_resource(gs, player, RESOURCE_ORE, cost);
	if (!success) return 0;

	// Log and execute
	set_weapon(player, dwarf_num, strength);

	return 1;
}

/** Loot item "Breed up to 2 kind of Farm animal" requires access
 * to game_state phase and breed. Bummer. */
static int gain_loot(
    game_state *gs,
    player_state *player,
    const loot_selection *loot
) {
	int success = 1;
	switch(loot->type) {
	case LOOT_INCREASE_WEAPONS:
		// Cannot call this function with this loot.
		error(gs, E_INTERNAL,
		    "(Very likely a bug) increasing all weapons is "
		    "handled outside this function."
		);
		success = 0;
		break;
	case LOOT_WOOD:
		gain_resource(player, RESOURCE_WOOD, 1);
		break;
	case LOOT_DOG:
		gain_resource(player, RESOURCE_DOG, 1);
		break;
	case LOOT_GRAIN:
		gain_resource(player, RESOURCE_GRAIN, 1);
		break;
	case LOOT_SHEEP:
		gain_resource(player, RESOURCE_SHEEP, 1);
		break;
	case LOOT_STONE:
		gain_resource(player, RESOURCE_STONE, 1);
		break;
	case LOOT_DONKEY:
		gain_resource(player, RESOURCE_DONKEY, 1);
		break;
	case LOOT_VEGETABLE:
		gain_resource(player, RESOURCE_VEGETABLE, 1);
		break;
	case LOOT_2ORE:
		gain_resource(player, RESOURCE_ORE, 2);
		break;
	case LOOT_BOAR:
		gain_resource(player, RESOURCE_BOAR, 1);
		break;
	case LOOT_2GOLD:
		gain_resource(player, RESOURCE_GOLD, 2);
		break;
	case LOOT_FURNISH:
		// "Furnish a Cavern" action as usual.
		// (Usual furnishing discounts may apply)
		success = furnish_tile(
		    gs, player, loot->tile_type,
		    loot->placement.x, loot->placement.y,
		    loot->builder_effect
		);
		break;
	case LOOT_STABLE:
		// Cost: 0 Stone
		success = build_stable(gs, player, &loot->placement, 0);
		break;
	case LOOT_TUNNEL:
                success = lay_single_tile(
                    gs, player, &loot->placement,
                    TILE_TUNNEL, // type
                    TILE_MOUNTAIN // tile underneath
		);
		break;
	case LOOT_SMALL_PASTURE:
		// Costs 1 Wood using Expedition
		success = fence_small_pasture(
		    gs, player, &loot->placement, 1);
		break;
	case LOOT_CATTLE:
		gain_resource(player, RESOURCE_CATTLE, 1);
		break;
	case LOOT_LARGE_PASTURE:
		// Costs 2 Wood using Expedition
		success = fence_large_pasture(
		    gs, player, &loot->placement, 2);
		break;
	case LOOT_MEADOW:
                success = lay_single_tile(
                    gs, player, &loot->placement,
                    TILE_MEADOW, // type
                    TILE_FOREST // tile underneath
		);
		break;
	case LOOT_DWELLING:
		// Furnish an ordinary Dwelling
		// Cost: 2 Wood + 2 Stone
		success = furnish_looted_dwelling(
		    gs, player,
		    &loot->placement,
		    loot->builder_effect
		);
		break;
	case LOOT_FIELD:
                success = lay_single_tile(
                    gs, player, &loot->placement,
                    TILE_FIELD, // type
                    TILE_FOREST // tile underneath
		);
		break;
	case LOOT_SOW:
		success = sow_crops(gs, player, loot->sow);
		break;
	case LOOT_CAVERN:
                success = lay_single_tile(
                    gs, player, &loot->placement,
                    TILE_CAVERN, // type
                    TILE_MOUNTAIN // tile underneath
		);
		break;
	case LOOT_BREED2:
		if (gs->phase == PHASE_WORK) {
			set_phase(gs, PHASE_BREED);
			set_breed(gs, BREED_UPTO_2_ONCE);
		} else if ((gs->phase == PHASE_BREED)
		    && (gs->breed == BREED_UPTO_2_ONCE))
		{
			set_breed(gs, BREED_UPTO_2_TWICE);
		} else {
			fprintf(stderr,
			    "Unknown phase/breed combination: %d/%d\n",
			    gs->phase, gs->breed
			);
			exit(1);
		}
		break;
	default:
		fprintf(stderr,
		    "(gain_loot) unexpected loot->type: %d\n",
		    loot->type
		);
		exit(1);
	}

	return success;
}

static int make_expedition(
    game_state *gs,
    player_state *player,
    int dwarf_num,
    const loot_selection *loots,
    int level
) {
	int success = 1;

	int strength = player->weapons[dwarf_num];

	if (strength == 0) {
		error(gs, E_ORDERS,
		    "Cannot send an unarmed Dwarf to expedition: %d",
		    dwarf_num
		);
		return 0;
	}

	if (strength > MAX_WEAPON_STRENGTH) {
		error(gs, E_ORDERS,
		    "The Dwarf %d has invalid Weapon strength: %d",
		    dwarf_num,
		    strength
		);
		return 0;
	}

	// XOR loot
	for (int i = 0; i < level-1; i++) {
		for (int j = i+1; j < level; j++) {
			if (loots[i].type == loots[j].type) {
				success = 0;
				break;
			}
		}
	}
	if (!success) {
		error(gs, E_ORDERS,
		    "The loot items must be all different from each other"
		);
		return 0;
	}

	int num_items = 0;
	const int *loot_items = get_loot_items_upto(strength, &num_items);

	int increase_all = 0;

	for (int i = 0; i < level; i++) {
		const loot_selection *loot = &loots[i];
		int type = loot->type;
		int found = 0;
		for (int j = 0; j < num_items; j++) {
			if (loot_items[j] != type) {
				found = 1;
				break;
			}
		}
		if (!found) {
			error(gs, E_ORDERS,
			    "The loot item \"%s\" is not available "
			    "with Weapon strength %d",
			    get_loot_name(type), strength
			);
			return 0;
		}

		if (loot->type == LOOT_INCREASE_WEAPONS) {
			increase_all = 1;
			continue;
		}
		int success = gain_loot(gs, player, loot);
		if (!success) return 0;
	}

	if (increase_all) {
		increase_all_weapons(player);
	}
	increase_weapon(player, dwarf_num);

	return 1;
}


static int play_drift_mining(
    game_state *gs,
    int dwarf_num,
    const drift_mining_orders *orders
) {
	int success = 1;
	action_space *aspace = get_action_space(gs, ACTION_DRIFT_MINING);

	player_state *player = &gs->players[gs->cur_player];

	// The accumulating resources must be taken.
	take_action_resources(player, aspace);

	if (orders->do_mining) {
		success = lay_twin_tile(
		    gs, player, &orders->placement,
		    TILE_CAVERN, TILE_TUNNEL, // tile1, tile2
		    TILE_MOUNTAIN // tile underneath
		);
	}
	return success;
}

static int play_logging(
    game_state *gs,
    int dwarf_num,
    const logging_orders *orders
) {
	int success = 1;
	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_LOGGING);

	// The wood must be taken
	take_action_resources(player, aspace);

	if (orders->do_looting) {
		int success = make_expedition(
		    gs, player, dwarf_num, orders->loot, 1);
		if (!success) return 0;
	}
	return success;
}

static int play_wood_gathering(
    game_state *gs,
    int dwarf_num,
    const wood_gathering_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_WOOD_GATHERING);

	// Accumulating resources are always taken.
	take_action_resources(player, aspace);

	return success;
}

static int play_excavation(
    game_state *gs,
    int dwarf_num,
    const excavation_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_EXCAVATION);

	// Accumulating resources are always taken.
	take_action_resources(player, aspace);

	if (orders->do_mining) {
		int type1 = TILE_CAVERN;
		int type2 = orders->cc ? TILE_CAVERN : TILE_TUNNEL;
		success = lay_twin_tile(
		    gs, player, &orders->placement,
		    type1, type2, // tile1, tile2
		    TILE_MOUNTAIN // tile underneath
		);
	}

	return success;
}

static int play_ore_mining(
    game_state *gs,
    int dwarf_num,
    const ore_mining_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_ORE_MINING);

	// Accumulating resources are always taken.
	take_action_resources(player, aspace);

	// In addition, gain +2 Ore for each Ore mine.
	int ore_mines = num_tiles(player->board, TILE_ORE_MINE);
	if (ore_mines > 0) {
		gain_resource(player, RESOURCE_ORE, ore_mines*2);
	}

	return success;
}

static int play_sustenance(
    game_state *gs,
    int dwarf_num,
    const sustenance_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_SUSTENANCE);
	// Accumulating resources are always taken.
	take_action_resources(player, aspace);
	// Gain +1 Grain
	gain_resource(player, RESOURCE_GRAIN, 1);

	if (orders->do_clearing) {
		success = lay_twin_tile(
		    gs, player, &orders->placement,
		    TILE_MEADOW, TILE_FIELD, // tile1, tile2
		    TILE_FOREST // tile underneath
		);
		if (!success) return 0;
	}

	return 1;
}

static int play_ruby_mining(
    game_state *gs,
    int dwarf_num,
    const ruby_mining_orders *orders
) {
	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_RUBY_MINING);
	// Accumulating resources are always taken.
	take_action_resources(player, aspace);

	// Gain +1 Ruby, if the player has at least 1 Ruby mine
	if (has_tile(player, TILE_RUBY_MINE)) {
		gain_resource(player, RESOURCE_RUBY, 1);
	}

	return 1;
}

static int play_housework(
    game_state *gs,
    int dwarf_num,
    const housework_orders *orders
) {
	int success = 1;
	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	if (orders->take_dog) {
		// Gain one dog
		gain_resource(player, RESOURCE_DOG, 1);
	}

	if (orders->do_furnish) {
		success = furnish_tile(
			gs,
			player,
			orders->tile_type,
			orders->placement.x,
			orders->placement.y,
			orders->builder_flags
		);
	}
	return success;
}

static int play_slash_and_burn(
    game_state *gs,
    int dwarf_num,
    const slash_and_burn_orders *orders
) {
	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	if (orders->do_clearing) {
		int success = lay_twin_tile(
		    gs, player, &orders->placement,
		    TILE_MEADOW, TILE_FIELD, // tile1, tile2
		    TILE_FOREST // tile underneath
		);
		if (!success) return 0;
	}

	int success = sow_crops(gs, player, orders->sow);
	if (!success) return 0;

	return 1;
}

static int play_blacksmithing(
    game_state *gs,
    int dwarf_num,
    const blacksmithing_orders *orders
) {
	if ((!orders->do_forging) && (!orders->do_looting)) {
		error(gs, E_ORDERS,
		    "At least one action must be chosen"
		);
		return 0;
	}

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	if (orders->do_forging) {
		int success = forge_weapon(
		    gs, player, dwarf_num, orders->weapon);
		if (!success) return 0;
	}

	if (orders->do_looting) {
		int success = make_expedition(
		    gs, player, dwarf_num, orders->loot, 3);
		if (!success) return 0;
	}

	return 1;
}

static int play_sheep_farming(
    game_state *gs,
    int dwarf_num,
    const sheep_farming_orders *orders
) {
	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	int success = 1;

	// Build a Small pasture
	if (orders->build_small) {
		// Small Pasture costs 2 Wood using this action.
		success = fence_small_pasture(
		    gs, player, &orders->small_placement, 2);
		if (!success) return 0;
	}

	// Build a Large pasture
	if (orders->build_large) {
		// Large Pasture costs 4 Wood using this action.
		success = fence_large_pasture(
		    gs, player, &orders->large_placement, 4);
		if (!success) return 0;
	}

	// Build a Stable
	if (orders->build_stable) {
		// Stable costs 1 Stone using this action
		success = build_stable(
		    gs, player, &orders->stable_placement, 1);
		if (!success) return 0;

	}

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_SHEEP_FARMING);

	// Accumulating resources are always taken.
	take_action_resources(player, aspace);

	return 1;
}

static int play_ore_mine_construction(
    game_state *gs,
    int dwarf_num,
    const ore_mine_construction_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// TODO: Must do at least one action.

	if (orders->do_construction) {
		success = lay_twin_tile(
		    gs, player, &orders->placement,
		    TILE_ORE_MINE, TILE_DEEP_TUNNEL, // tile1, tile2
		    TILE_TUNNEL // tile underneath
		);
		// Gain +3 Ore due to succesful ore mine constrution
		gain_resource(player, RESOURCE_ORE, 3);
	}

	if (orders->do_looting) {
		int success = make_expedition(
		    gs, player, dwarf_num, orders->loot, 2);
		if (!success) return 0;
	}

	return success;
}

static int play_wish_for_children(
    game_state *gs,
    int dwarf_num,
    const wish_for_children_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// This is an "either ... or" action space.
	success = validate_either_or(
	    gs, player,
	    orders->furnish_dwelling,
	    orders->do_family_growth
	);
	if (!success) return 0;

	// Furnish a Dwelling first, as it may have impact on the capacity
	if (orders->furnish_dwelling) {
		success = furnish_tile(
			gs,
			player,
			orders->type,
			orders->placement.x,
			orders->placement.y,
			orders->builder_effect
		);
		if (!success) return 0;
	}

	if (orders->do_family_growth) {
		success = grow_family(player, gs);
		if (!success) return 0;
	}

	return 1;
}

static int play_urgent_wish_for_children(
    game_state *gs,
    int dwarf_num,
    const wish_for_children_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// This is an "either ... or" action space.
	success = validate_either_or(
	    gs, player,
	    orders->furnish_dwelling,
	    orders->take_gold
	);
	if (!success) return 0;

	if ((!orders->furnish_dwelling) && (orders->do_family_growth)) {
		error(gs, E_ORDERS,
		    "You may not grow your family unless you use "
		    "the Furnish a Dwelling action first."
		);
		return 0;
	}

	// Furnish a Dwelling first, as it may have impact on the capacity
	if (orders->furnish_dwelling) {
		success = furnish_tile(
			gs,
			player,
			orders->type,
			orders->placement.x,
			orders->placement.y,
			orders->builder_effect
		);
		if (!success) return 0;

		if (orders->do_family_growth) {
			success = grow_family(player, gs);
			if (!success) return 0;
		}
	}

	if (orders->take_gold) {
		// Gain +3 Gold
		gain_resource(player, RESOURCE_GOLD, 3);
	}

	return 1;
}


static int play_donkey_farming(
    game_state *gs,
    int dwarf_num,
    const donkey_farming_orders *orders
) {
	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	int success = 1;

	// Build a Small pasture
	if (orders->build_small) {
		// Small Pasture costs 2 Wood using this action.
		success = fence_small_pasture(
		    gs, player, &orders->small_placement, 2);
		if (!success) return 0;
	}

	// Build a Large pasture
	if (orders->build_large) {
		// Large Pasture costs 4 Wood using this action.
		success = fence_large_pasture(
		    gs, player, &orders->large_placement, 4);
		if (!success) return 0;
	}

	// Build a Stable
	if (orders->build_stable) {
		// Stable costs 1 Stone using this action
		success = build_stable(
		    gs, player, &orders->stable_placement, 1);
		if (!success) return 0;

	}

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_DONKEY_FARMING);

	// Accumulating resources are always taken.
	take_action_resources(player, aspace);

	return 1;
}


static int play_ruby_mine_construction(
    game_state *gs,
    int dwarf_num,
    const ruby_mine_construction_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// This is an "either ... or" action space.
	success = validate_either_or(
	    gs, player,
	    orders->do_construction1,
	    orders->do_construction2
	);
	if (!success) return 0;

	if (orders->do_construction1) {
		// On ordinary Tunnel Tile.
		success = lay_single_tile(
		    gs, player, &orders->placement1,
		    TILE_RUBY_MINE, // type
		    TILE_TUNNEL // tile underneath
		);
		if (!success) return 0;
	}

	if (orders->do_construction2) {
		// On Deep Tunnel Tile.
		success = lay_single_tile(
		    gs, player, &orders->placement2,
		    TILE_RUBY_MINE, // type
		    TILE_DEEP_TUNNEL // tile underneath
		);
		if (!success) return 0;
		// Gain +1 Ruby
		gain_resource(player, RESOURCE_RUBY, 1);
	}

	return success;
}

static int play_ore_delivery(
    game_state *gs,
    int dwarf_num,
    const ore_delivery_orders *orders
) {
	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_ORE_DELIVERY);

	// Accumulating resources are always taken (Ore and Stone)
	take_action_resources(player, aspace);

	// Gain +2 Ore for each Ore mine.
	int count = num_tiles(player->board, TILE_ORE_MINE);
	if (count > 0) {
		gain_resource(player, RESOURCE_ORE, count*2);
	}

	return 1;
}

static int play_family_life(
    game_state *gs,
    int dwarf_num,
    const family_life_orders *orders
) {
	int success = 1;

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	if (orders->do_family_growth) {
		success = grow_family(player, gs);
		if (!success) return 0;
	}

	success = sow_crops(gs, player, orders->sow);
	if (!success) return 0;

	return 1;
}

static int play_ore_trading(
    game_state *gs,
    int dwarf_num,
    const ore_trading_orders *orders
) {
	// For convenience
	player_state *player = &gs->players[gs->cur_player];
	int count = orders->count;

	// Build resource conversion
	if ((count < 1) || (count > 3)) {
		error(gs, E_ORDERS,
		    "You must perform the exchange 1-3 times."
		);
		return 0;
	}

	//int input[3*2] = {RESOURCE_ORE, 2*count};
	//int output[3*2] = {RESOURCE_GOLD, 2*count, RESOURCE_FOOD, 1*count};

	int success = pay_resource(gs, player, RESOURCE_ORE, count*2);
	if (!success) return 0;

	gain_resource(player, RESOURCE_GOLD, count*2);
	gain_resource(player, RESOURCE_FOOD, count*1);

	return 1;
}

static int play_adventure(
    game_state *gs,
    int dwarf_num,
    const adventure_orders *orders
) {
	if ((!orders->do_forging) && (!orders->do_looting)) {
		error(gs, E_ORDERS,
		    "At least one action must be chosen"
		);
		return 0;
	}

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	if (orders->do_forging) {
		int success = forge_weapon(
		    gs, player, dwarf_num, orders->weapon);
		if (!success) return 0;
	}

	if (orders->do_looting) {
		int success = 1;
		success = make_expedition(
		    gs, player, dwarf_num, orders->loot1, 1);
		if (!success) return 0;
		success = make_expedition(
		    gs, player, dwarf_num, orders->loot2, 1);
		if (!success) return 0;
	}


	return 1;
}

static int play_ruby_delivery(
    game_state *gs,
    int dwarf_num,
    const ruby_delivery_orders *orders
) {
	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Get the chosen action space
	action_space *aspace = get_action_space(gs, ACTION_RUBY_DELIVERY);
	// Accumulating resources are always taken.
	take_action_resources(player, aspace);

	// Gain +2 Ore for each Ore mine.
	int count = num_tiles(player->board, TILE_RUBY_MINE);
	if (count >= 2) {
		gain_resource(player, RESOURCE_RUBY, 1);
	}

	return 1;
}

static void incorporate_player_commands(game_state *gs, player_state *player) {
	int player_num = get_player_num(gs, player);

	if (player_num == -1) {
		fprintf(stderr,
		    "(incorporate_player_commands) no such player: %p\n",
		    player
		);
		exit(1);
	}

	command_record *iter = player->log.head;
	int count = 0;
	while (iter != NULL) {
		count++;
		iter->player_num = player_num;
		iter = iter->next;
	}

	if (player->log.head != NULL) {
		player->log.head->prev = gs->log.tail;
		if (gs->log.tail != NULL) {
			gs->log.tail->next = player->log.head;
		} else {
			gs->log.head = player->log.head;
		}
		gs->log.tail = player->log.tail;
		player->log.head = NULL;
		player->log.tail = NULL;

		// Update the last command pointer
		gs->last_command = gs->log.tail;
	}
}


int caverna_can_furnish(const player_state *player, int type) {
	int price[3*2];
	// Get the price
	const furnishing_config *cfg = get_furnishing_config(type);
	if (cfg == NULL) {
		// TODO: Should be soft, as this is exported api.
		fprintf(stderr,
		    "(caverna_can_furnish) unexpected type: %d\n",
		    type
		);
		exit(1);
	}
	// copy price
	memcpy(price, cfg->price, sizeof(cfg->price));

	// Apply discounts
	int has_carpenter = has_tile(player, TILE_CARPENTER);
	int has_stone_carver = has_tile(player, TILE_STONE_CARVER);
	int has_builder = has_tile(player, TILE_BUILDER);

	if (has_carpenter) {
		// -1 Wood
		int *wood_cost = get_price_resource(price, RESOURCE_WOOD);
		if ((wood_cost != NULL) && (*wood_cost > 0)) {
			(*wood_cost)--;
		}
	}
	if (has_stone_carver) {
		// -1 Stone
		int *stone_cost = get_price_resource(price, RESOURCE_STONE);
		if ((stone_cost != NULL) && (*stone_cost > 0)) {
			(*stone_cost)--;
		}
	}

	int result = check_price(price, player);
	if (result) return 1;
	if (has_builder) {
		int *wood_cost = get_price_resource(price, RESOURCE_WOOD);
		int *stone_cost = get_price_resource(price, RESOURCE_STONE);

		int *ore_cost = get_price_resource(price, RESOURCE_ORE);
		if (ore_cost == NULL) {
			ore_cost = set_price_resource(
			    price, RESOURCE_ORE, 0);
		}

		if ((wood_cost != NULL) && (*wood_cost > 0)) {
			// A) -1 Wood, +1 Ore
			(*wood_cost)--;
			(*ore_cost)++;
			result = check_price(price, player);
			if (result) return 1;
			(*wood_cost)++;
			(*ore_cost)--;
		}
		if ((stone_cost != NULL) && (*stone_cost > 0)) {
			// B) -1 Wood, -1 Stone, +2 Ore
			(*stone_cost)--;
			(*ore_cost)++;
			result = check_price(price, player);
			if (result) return 1;
			(*stone_cost)++;
			(*ore_cost)--;
		}
		if ((stone_cost != NULL) && (*stone_cost > 0)
		    && (wood_cost != NULL) && (wood_cost > 0))
		{
			// C) -1 Stone, +1 Ore
			(*wood_cost)--;
			(*stone_cost)--;
			(*ore_cost) += 2;
			result = check_price(price, player);
			if (result) return 1;
			(*wood_cost)++;
			(*stone_cost)++;
			(*ore_cost) -= 2;
		}
	}
	return 0;
}

static void undo_take_animal_from_tile(
    player_state *player,
    const int *values
) {
	int type = values[0];
	int quantity = values[1];
	int x = values[2];
	int y = values[3];
	int z = values[4];

	tile_state *tile = get_tile(player->board, x, y, z);
	int *on_tile = get_tile_resource(tile, type);
	int *placed = get_placed_animal(player, type);

	*on_tile += quantity;
	*placed += quantity;

}

static void undo_drop_animal_to_tile(
    player_state *player,
    const int *values
) {
	int type = values[0];
	int quantity = values[1];
	int x = values[2];
	int y = values[3];
	int z = values[4];

	tile_state *tile = get_tile(player->board, x, y, z);
	int *on_tile = get_tile_resource(tile, type);
	int *placed = get_placed_animal(player, type);

	*on_tile -= quantity;
	*placed -= quantity;
}

static void undo_take_resource_from_tile(
    player_state *player,
    const int *values
) {

	int type = values[0];
	int quantity = values[1];
	int x = values[2];
	int y = values[3];
	int z = values[4];

	tile_state *tile = get_tile(player->board, x, y, z);
	int *on_tile = get_tile_resource(tile, type);
	int *counter = get_resource(player, type);

	*on_tile += quantity;
	*counter -= quantity;
}

static void undo_drop_resource_to_tile(
    player_state *player,
    const int *values
) {

	int type = values[0];
	int quantity = values[1];
	int x = values[2];
	int y = values[3];
	int z = values[4];

	tile_state *tile = get_tile(player->board, x, y, z);
	int *on_tile = get_tile_resource(tile, type);
	int *counter = get_resource(player, type);

	*counter += quantity;
	*on_tile -= quantity;
}

/**
 * NOTE: This undo function could be replaced with
 * ordinary CMD_GAIN_RESOURCE, in addition to action
 * space counter reset.
 */
static void undo_take_action_resources(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int action_type = values[0];
	int counter = values[1];

	action_space *aspace = get_action_space(gs, action_type);

	// Untake the resources from the action space
	switch(aspace->type) {
	case ACTION_DRIFT_MINING:
		player->stone -= counter;
		break;
	case ACTION_LOGGING:
		player->wood -= counter;
		break;
	case ACTION_WOOD_GATHERING:
		player->wood -= counter;
		break;
	case ACTION_EXCAVATION:
		player->stone -= counter;
		break;
	case ACTION_ORE_MINING:
		player->ore -= counter;
		break;
	case ACTION_SUSTENANCE:
		player->food -= counter;
		break;
	case ACTION_RUBY_MINING:
		player->ruby -= counter;
		break;
	case ACTION_SHEEP_FARMING:
		player->sheep -= counter;
		break;
	case ACTION_DONKEY_FARMING:
		player->donkey -= counter;
		break;
	case ACTION_ORE_DELIVERY:
		player->stone -= counter;
		player->ore -= counter;
		break;
	case ACTION_RUBY_DELIVERY:
		player->ruby -= counter;
		break;
	default:
		fprintf(stderr,
		    "(undo_take_action_resources) "
		    "unhandled action space type: %d\n",
		    aspace->type
		);
		exit(1);
	}
	// Reset counter
	aspace->counter = counter;
}

static void undo_gain_resources(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int *counter = get_resource(player, values[0]);
	*counter -= values[1];
	//sub_resource(player, values[0], values[1]);
}

static void undo_add_tile_resource(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int type = values[0];
	int delta = values[1];
	int x = values[2];
	int y = values[3];
	int z = values[4];

	tile_state *tile = get_tile(player->board, x, y, z);
	int *counter = get_tile_resource(tile, type);
	*counter -= delta;
}


static void undo_pay_resources(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int *counter = get_resource(player, values[0]);
	*counter += values[1];
}

static void undo_take_furnishing(
    game_state *gs,
    player_state *player,
    const int *values
) {
	furnishing_state *furnishing = get_furnishing(gs, values[0]);
	furnishing->taken_by = -1;
}

static void undo_feed_family(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int food = values[0];
	int begging = values[1];
	int working_cave_effect = values[2];

	// Execute
	player->food += food;
	player->beggar -= begging;

	switch(working_cave_effect) {
	case WORKING_CAVE_FEED_1WOOD:
		player->wood += 1;
		break;
	case WORKING_CAVE_FEED_1STONE:
		player->stone += 1;
		break;
	case WORKING_CAVE_FEED_2ORE:
		player->ore += 2;
		break;
	default:
		// No Working cave utilization
		break;
	}
}

static void undo_lay_tile(
    game_state *gs,
    player_state *player,
    const int *values
) {
	// For convenience
	int x = values[1];
	int y = values[2];
	int z = values[3];

	tile_state *tile = get_tile(player->board, x, y, z);
	// Clear tile type and dir
	tile->type = TILE_NONE;
	tile->dir = DIRECTION_NONE;
}

static void undo_reset_counter(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int action_type = values[0];
	int counter = values[1];
	action_space *aspace = get_action_space(gs, action_type);
	aspace->counter = counter;
}

static void undo_increase_counter(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int action_type = values[0];
	int delta = values[1];
	int has_ruby = values[2];
	action_space *aspace = get_action_space(gs, action_type);
	aspace->counter -= delta;
	aspace->has_ruby = has_ruby;
}

static void undo_send_worker(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int dwarf_num = values[0];
	int atype = values[1];
	action_space *aspace = get_action_space(gs, atype);

	aspace->taken_by = -1;
	player->locations[dwarf_num] = ACTION_NONE;
	player->workers--;
}

static void undo_retrieve_worker(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int dwarf_num = values[0];
	int atype = values[1];
	action_space *aspace = get_action_space(gs, atype);

	int player_num = get_player_num(gs, player);
	// Cannot be -1, since the player param comes from gs itself.

	aspace->taken_by = player_num;
	player->locations[dwarf_num] = atype;
	player->workers++;
}


static void undo_set_phase(
    game_state *gs,
    player_state *player,
    const int *values
) {
	gs->phase = values[1];
}

static void undo_set_current_player(
    game_state *gs,
    player_state *player,
    const int *values
) {
	gs->cur_player = values[1];
}

static void undo_set_harvest(
    game_state *gs,
    player_state *player,
    const int *values
) {
	gs->harvest = values[1];
}

static void undo_set_breed(
    game_state *gs,
    player_state *player,
    const int *values
) {
	gs->breed = values[1];
}

static void undo_reorder_dwarfs(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int weapons[6];
	memcpy(weapons, player->weapons, sizeof(player->weapons));
	// Undo permutation
	for (int i = 0; i < MAX_DWARFS; i++) {
		int old_index = values[i];
		player->weapons[old_index] = weapons[i];
	}
}

static void undo_grow_up(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int children = values[0];
	player->dwarfs -= children;
	player->children = children;
	int *weapons = player->weapons; // For convenience
	memmove(
	    &weapons[0],
	    &weapons[children],
	    player->dwarfs*sizeof(int)
	);
}

static void undo_lay_stable(
    game_state *gs,
    player_state *player,
    const int *values
) {
	tile_state *tile = get_tile(
	    player->board, values[0], values[1], values[2]);
	player->stable--;
	tile->stable--;
}

static void undo_set_weapon(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int dwarf_num = values[0];
	player->weapons[dwarf_num] = 0;
}

static void undo_increase_weapon(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int dwarf_num = values[0];
	player->weapons[dwarf_num]--;
}

static void undo_increase_all_weapons(
    game_state *gs,
    player_state *player,
    const int *values
) {
	for (int i = 0; i < 6; i++) {
		player->weapons[i] -= values[i];
	}
}

static void undo_convert_weapons_to_food(
    game_state *gs,
    player_state *player,
    const int *values
) {
	for (int i = 0; i < 6; i++) {
		int v = values[i];
		player->food -= v;
		player->weapons[i] = v;
	}
}

static void undo_next_round(
    game_state *gs,
    player_state *player,
    const int *values
) {
	// If the action that is being removed is Family life,
	// replace Urgent wish for children with the normal variant.
	if (gs->actions[gs->num_actions-1].type == ACTION_FAMILY_LIFE) {
		action_space *aspace = get_action_space(
		    gs, ACTION_URGENT_WISH_FOR_CHILDREN);
		aspace->type = ACTION_WISH_FOR_CHILDREN;
	}

	gs->num_actions--;


	if ((gs->num_players <= 2) && (gs->cur_round == 10)) {
		// In Solo and 2-player games, the round 9 is skipped.
		gs->cur_round--;
		gs->num_actions--;
	}

	gs->cur_round--;

	int xmin, ymin, xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);
	for (int i = 0; i < gs->num_players; i++) {
		player_state *player = &gs->players[i];
		for (int y = ymin; y <= ymax; y++) {
			for (int x = xmin; x <= xmax; x++) {
				int z;
				tile_state *top = get_top_tile(
				    player->board, x, y, &z);
				top->rounds--;
			}
		}
	}

}

static void undo_grow_family(
    game_state *gs,
    player_state *player,
    const int *values
) {
	player->children--;
}

static void undo_convert_resources(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int conversion = values[0];
	int count = values[1];

	const conversion_config *cc = get_conversion_config(conversion);
	if (cc == NULL) {
		fprintf(stderr,
		    "(undo_convert_resources) conversion type not found: %d",
		    conversion
		);
		exit(1);
	}

	// The actual input/output of the resource conversion
	int input[3*2] = { RESOURCE_NONE, 0 };
	int output[3*2] = { RESOURCE_NONE, 0 };

	int success = get_resource_conversion(cc, count, input, output);
	if (!success) {
		fprintf(stderr,
		    "(undo_convert_resources) "
		    "unexpected conversion type: %d",
		    conversion
		);
		exit(1);
	}

	for (int i = 0; i < 3; i++) {
		int type = input[(i*2)+0];
		int cost = input[(i*2)+1];
		if (type == RESOURCE_NONE) break;

		int *counter = get_resource(player, type);
		*counter += cost;
	}
	for (int i = 0; i < 3; i++) {
		int type = output[(i*2)+0];
		int gain = output[(i*2)+1];
		if (type == RESOURCE_NONE) break;

		int *counter = get_resource(player, type);
		*counter -= gain;
	}
}

static void undo_put_ruby_on_action(
    game_state *gs,
    player_state *player,
    const int *values
) {
	action_space *aspace = get_action_space(gs, values[0]);
	if (aspace == NULL) {
		fprintf(stderr,
		    "(undo_put_ruby_on_action) action type not found: %d",
		    values[0]
		);
		exit(1);
	}
	aspace->has_ruby = 0;
	int *counter = get_resource(player, RESOURCE_RUBY);
	*counter += 1;
}

static void undo_breed_animal(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int type = values[0];
	int *counter = get_animal(player, type);
	int *newborns = get_newborn_animal(player, type);
	(*newborns) = 0;
	(*counter)--;
}

static void undo_unbreed_animal(
    game_state *gs,
    player_state *player,
    const int *values
) {
	int type = values[0];
	int *counter = get_animal(player, type);
	int *newborns = get_newborn_animal(player, type);
	(*newborns) = 1;
	(*counter)++;
}

static void undo_grow_newborns(
    game_state *gs,
    player_state *player,
    const int *values
) {
	player->newborn_sheep = values[0];
	player->newborn_donkey = values[1];
	player->newborn_boar = values[2];
	player->newborn_cattle = values[3];
}


static void rollback_command_record(
    command_record *cmd,
    player_state *player,
    game_state *gs
) {
	const int *v = cmd->value;
	switch(cmd->type) {
	case CMD_TAKE_TILE_ANIMAL:
		undo_take_animal_from_tile(player, v);
		break;
	case CMD_DROP_TILE_ANIMAL:
		undo_drop_animal_to_tile(player, v);
		break;
	case CMD_TAKE_TILE_RESOURCE:
		undo_take_resource_from_tile(player, v);
		break;
	case CMD_DROP_TILE_RESOURCE:
		undo_drop_resource_to_tile(player, v);
		break;
	case CMD_TAKE_ACTION_RESOURCE:
		undo_take_action_resources(gs, player, v);
		break;
	case CMD_GAIN_RESOURCE:
		undo_gain_resources(gs, player, v);
		break;
	case CMD_ADD_TILE_RESOURCE:
		undo_add_tile_resource(gs, player, v);
		break;
	case CMD_PAY_RESOURCE:
		undo_pay_resources(gs, player, v);
		break;
	case CMD_TAKE_FURNISHING:
		undo_take_furnishing(gs, player, v);
		break;
	case CMD_FEED_FAMILY:
		undo_feed_family(gs, player, v);
		break;
	case CMD_LAY_TILE:
		undo_lay_tile(gs, player, v);
		break;
	case CMD_RESET_COUNTER:
		undo_reset_counter(gs, player, v);
		break;
	case CMD_INCREASE_COUNTER:
		undo_increase_counter(gs, player, v);
		break;
	case CMD_SEND_WORKER:
		undo_send_worker(gs, player, v);
		break;
	case CMD_RETRIEVE_WORKER:
		undo_retrieve_worker(gs, player, v);
		break;
	case CMD_SET_PHASE:
		undo_set_phase(gs, player, v);
		break;
	case CMD_SET_CURRENT_PLAYER:
		undo_set_current_player(gs, player, v);
		break;
	case CMD_SET_HARVEST:
		undo_set_harvest(gs, player, v);
		break;
	case CMD_REORDER_DWARFS:
		undo_reorder_dwarfs(gs, player, v);
		break;
	case CMD_GROW_UP:
		undo_grow_up(gs, player, v);
		break;
	case CMD_LAY_STABLE:
		undo_lay_stable(gs, player, v);
		break;
	case CMD_SET_WEAPON:
		undo_set_weapon(gs, player, v);
		break;
	case CMD_INCREASE_WEAPON:
		undo_increase_weapon(gs, player, v);
		break;
	case CMD_INCREASE_ALL_WEAPONS:
		undo_increase_all_weapons(gs, player, v);
		break;
	case CMD_NEXT_ROUND:
		undo_next_round(gs, player, v);
		break;
	case CMD_GROW_FAMILY:
		undo_grow_family(gs, player, v);
		break;
	case CMD_CONVERT_WEAPONS_TO_FOOD:
		undo_convert_weapons_to_food(gs, player, v);
		break;
	case CMD_CONVERT_RESOURCES:
		undo_convert_resources(gs, player, v);
		break;
	case CMD_PUT_RUBY_ON_ACTION:
		undo_put_ruby_on_action(gs, player, v);
		break;
	case CMD_BREED_ANIMAL:
		undo_breed_animal(gs, player, v);
		break;
	case CMD_UNBREED_ANIMAL:
		undo_unbreed_animal(gs, player, v);
		break;
	case CMD_GROW_NEWBORNS:
		undo_grow_newborns(gs, player, v);
		break;
	case CMD_SET_BREED:
		undo_set_breed(gs, player, v);
		break;
	default:
		fprintf(stderr,
		    "(rollback_command_record) "
		    "unexpected command record type: %d\n",
		    cmd->type
		);
		exit(1);
	} // switch
}


static command_record *rollback(game_state *gs) {
	command_record *temp = gs->log.tail;
	if (temp != NULL) {
		// Detach tail from the temp
		gs->log.tail = temp->prev;
		if (gs->log.tail != NULL) {
			gs->log.tail->next = NULL;
		} else {
			gs->log.head = NULL;
		}
		// Detach temp from tail
		temp->prev = NULL;
		// For convenience
		player_state *player = NULL;
		if (temp->player_num != -1) {
			player = &gs->players[temp->player_num];
		}
		rollback_command_record(temp, player, gs);
		free(temp);
	} else {
		// Nothig to rollback
	}
	return gs->log.tail;
}

void caverna_rollback(game_state *gs) {
	rollback(gs);
}

static void rollback_player_commands(game_state *gs, player_state *player) {
	command_record *cmd = player->log.head;
	while (cmd != NULL) {
		rollback_command_record(cmd, player, gs);
		command_record *temp = cmd;
		cmd = cmd->next;
		free(temp);
	}
	clear_log(&player->log);
}

static void rollback_to(game_state *gs, const command_record *savepoint) {
	command_record *tail = gs->log.tail;
	while ((tail != NULL) && (tail != savepoint)) {
		tail = rollback(gs);
	}
}

static void replenish_action(game_state *gs, action_space *action, command_log *log) {
	// For convenience
	int type = action->type;
	int counter = action->counter;
	int num_players = gs->num_players;
	int round = gs->cur_round;
	int has_ruby = action->has_ruby;

	// Disabled action spaced are ignored altogether.
	if (type == ACTION_NONE) return;

	// If there is at least 6 resources on the action,
	// the action is subject to reset (on solo game only).
	// TODO: get number of players
	if ((counter >= 6) && (!has_ruby)) {
		log_command2(log, CMD_RESET_COUNTER, type, counter);
		counter = 0;
	}

	int delta = 0;
	switch(type) {
	case ACTION_DRIFT_MINING:
		delta = 1;
		break;
	case ACTION_LOGGING:
		delta = (counter == 0 ? 3 : 1);
		break;
	case ACTION_WOOD_GATHERING:
		delta = 1;
		break;
	case ACTION_EXCAVATION:
		delta = 1;
		break;
	case ACTION_SUPPLIES:
		break;
	//case ACTION_CLEARING: // TODO
	//case ACTION_STARTING_PLAYER: // TODO
	case ACTION_ORE_MINING:
		delta = (counter == 0 ? 2 : 1);
		break;
	case ACTION_SUSTENANCE:
		delta = 1;
		break;
	case ACTION_RUBY_MINING:
		if ((num_players == 1) || (round >= 2) || (num_players > 2)) {
			delta = 1;
		} else {
			delta = 0;
		}
		break;
	case ACTION_HOUSEWORK:
		break;
	case ACTION_SLASH_AND_BURN:
		break;
	case ACTION_BLACKSMITHING:
		break;
	case ACTION_SHEEP_FARMING:
		delta = 1;
		break;
	case ACTION_ORE_MINE_CONSTRUCTION:
		break;
	case ACTION_WISH_FOR_CHILDREN:
		break;
	case ACTION_URGENT_WISH_FOR_CHILDREN:
		break;
	case ACTION_DONKEY_FARMING:
		delta = 1;
		break;
	case ACTION_RUBY_MINE_CONSTRUCTION:
		break;
	case ACTION_ORE_DELIVERY:
		delta = 1;
		break;
	case ACTION_FAMILY_LIFE:
		break;
	case ACTION_ORE_TRADING:
		break;
	case ACTION_ADVENTURE:
		break;
	case ACTION_RUBY_DELIVERY:
		delta = (counter == 0 ? 2 : 1);
		break;
	default:
		fprintf(stderr,
		    "(replenish_action) unhandled action->type: %d\n",
		    type
		);
		exit(1);
	}

	if (delta != 0) {
		// Log command
		log_command5(log, CMD_INCREASE_COUNTER,
		    type, delta, has_ruby, 0, 0);
		// Increase the counter by delta
		counter += delta;
		// Remove the ruby, if any
		action->has_ruby = 0;
	}

	action->counter = counter;
}

static int replenish_all_actions(game_state *gs) {

	// Refill action spaces
	for (int i = 0; i < gs->num_actions; i++) {
		// For convenience
		action_space *action = &gs->actions[i];
		replenish_action(gs, action, &gs->log);
	}

	return 1;
}

int send_worker(
    player_state *player,
    int dwarf_num,
    game_state *gs,
    int atype
) {

	// Get player number
	int player_num = get_player_num(gs, player);
	if (player_num == -1) {
		error(gs, E_INTERNAL,
		    "No such player in the game: %p",
		    player
		);
		return 0;
	}

	if ((dwarf_num < 0) || (dwarf_num >= player->dwarfs)) {
		error(gs, E_INTERNAL,
		    "Invalid dwarf number: %d "
		    "(player %d has only %d dwarfs)",
		    dwarf_num,
		    player_num, player->dwarfs
		);
		return 0;
	}

	// Action space type
	int location = player->locations[dwarf_num];

	if (location != ACTION_NONE) {
		error(gs, E_INTERNAL,
		    "Cannot send: player\'s %d dwarf %d "
		    "is already on action space \"%s\"",
		    player_num, dwarf_num,
		    caverna_get_action_name(location)
		);
		return 0;
	}

	action_space *aspace = get_action_space(gs, atype);
	if (aspace == NULL) {
		error(gs, E_INTERNAL,
		    "No such action space: %d",
		    atype
		);
		return 0;
	}

	if (aspace->taken_by != -1) {
		error(gs, E_INTERNAL,
		    "Cannot send: player\'s %d has a dwarf "
		    "already on action space \"%s\"",
		    aspace->taken_by,
		    caverna_get_action_name(atype),
		    aspace->taken_by
		);
		return 0;
	}

	// Log & execute
	log_command2(&player->log, CMD_SEND_WORKER, dwarf_num, atype);
	aspace->taken_by = player_num;
	player->locations[dwarf_num] = atype;
	player->workers++;
	return 1;
}

/**
 * game_state required for: log, and asction spaces
 */
int retrieve_worker(
    player_state *player,
    int dwarf_num,
    game_state *gs
) {

	// Get player number
	int player_num = get_player_num(gs, player);
	if (player_num == -1) {
		error(gs, E_INTERNAL,
		    "No such player in the game: %p",
		    player
		);
		return 0;
	}

	if ((dwarf_num < 0) || (dwarf_num >= player->dwarfs)) {
		error(gs, E_INTERNAL,
		    "Invalid dwarf number: %d "
		    "(player %d has only %d dwarfs)",
		    dwarf_num,
		    player_num, player->dwarfs
		);
		return 0;
	}

	// Action space type
	int atype = player->locations[dwarf_num];

	if (atype == ACTION_NONE) {
		error(gs, E_INTERNAL,
		    "Cannot retrieve: player\'s %d dwarf %d "
		    "is not on any action space",
		    player_num, dwarf_num
		);
		return 0;
	}

	action_space *aspace = get_action_space(gs, atype);
	if (aspace == NULL) {
		error(gs, E_INTERNAL,
		    "No such action space: %d",
		    atype
		);
		return 0;
	}

	if (aspace->taken_by != player_num) {
		error(gs, E_INTERNAL,
		    "Cannot retrieve: player\'s %d dwarf %d location "
		    "\"%s\" is in contradiction with the location\'s "
		    "taken_by=%d",
		    player_num, dwarf_num,
		    caverna_get_action_name(atype),
		    aspace->taken_by
		);
		return 0;
	}

	// Log and execute
	log_command2(&player->log, CMD_RETRIEVE_WORKER, dwarf_num, atype);

	aspace->taken_by = -1;
	player->locations[dwarf_num] = ACTION_NONE;
	player->workers--;

	return 1;
}

static void swap_int(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
/**
 * game_state is needed only for error messaging
 */
static int reorder_and_grow_up(game_state *gs, player_state *player) {
	// For convenience
	int dwarfs = player->dwarfs;
	int children = player->children;

	// Sanity check
	if ((dwarfs+children) > MAX_DWARFS) {
		error(gs, E_INTERNAL,
		    "Cannot have more than 6 adult dwarfs"
		);
		return 0;
	}

	// Reorder existing (using a simple bubble sort)

	int *weapons = player->weapons; // for convenience
	int index[6]; // build command_record for reorder
	for (int i = 0; i < 6; i++) index[i] = i;
	// Do simple bubble sorting
	for (int i = 0; i < dwarfs; i++) {
		for (int j = i; j < dwarfs; j++) {
			if (weapons[i] < weapons[j]) continue;
			// swap
			swap_int(&weapons[i], &weapons[j]);
			swap_int(&index[i], &index[j]);
		}
	}

	// log reorder message
	log_command6(
	    &player->log,
	    CMD_REORDER_DWARFS,
	    index[0], index[1], index[2],
	    index[3], index[4], index[5]
	);

	// Make space at the beginning of the array for the new adults
	if (children > 0) {
		memmove(
		    &weapons[children],
		    &weapons[0],
		    dwarfs*sizeof(int)
		);
		for (int i = 0; i < children; i++) {
			player->locations[i] = ACTION_NONE;
			player->weapons[i] = 0;
		}
		// Log and execute
		log_command1(&player->log, CMD_GROW_UP, children);
		player->dwarfs += children;
		player->children = 0;
	}


	return 1;
}

static void get_next_dwarf(
    const player_state *player,
    int *next_dwarf,
    int *next_armed
) {
	// Next unemployed Dwarf
	*next_dwarf = -1;
	// Next unemployed, but armed Dwarf.
	*next_armed = -1;

	for (int i = 0; i < player->dwarfs; i++) {
		// Skip, if employed
		if (player->locations[i] != ACTION_NONE) continue;
		if (*next_dwarf == -1) {
			*next_dwarf = i;
		}

		if (player->weapons[i] > 0) {
			if (*next_armed == -1) {
				*next_armed = i;
				break;
			}
		}
	}
}

void caverna_get_next_dwarf(
    const game_state *gs,
    int *next_dwarf,
    int *next_armed
) {
	get_next_dwarf(&gs->players[gs->cur_player], next_dwarf, next_armed);
}

static void convert_resources(
    player_state *player,
    const int *input,
    const int *output
) {
	for (int i = 0; i < 3; i++) {
		int type = input[(i*2)+0];
		int cost = input[(i*2)+1];
		if (type == RESOURCE_NONE) break;

		// todo: use add_resource(), sub_resource()
		// in order to handle effect triggers
		sub_resource(player, type, cost);
		// int *counter = get_resource(player, type);
		// *counter -= cost;
	}
	for (int i = 0; i < 3; i++) {
		int type = output[(i*2)+0];
		int gain = output[(i*2)+1];
		if (type == RESOURCE_NONE) break;

		add_resource(player, type, gain);
		// int *counter = get_resource(player, type);
		// *counter += gain;
	}
}

static void unplace_animals(player_state *player, int type, int qty) {
	int xmin, ymin;
	int xmax, ymax;

	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x < xmax; x++) {
			int z;
			tile_state *t = get_top_tile(
			     player->board, x, y, &z);
			int *on_tile = get_tile_resource(t, type);
			if (*on_tile == 0) continue;

			int number = qty;
			if (number > *on_tile) number = *on_tile;

			take_animal_from_tile(
			    player, x, y, z,
			    type, number
			);
			qty -= number;
			if (qty == 0) return;
		}
	}
	fprintf(stderr,
	    "(unplace_animals) needed to unplace %d %s more\n",
	    qty,
	    get_resource_name(type)
	);
	exit(1);
}

static int expect_resources(
    game_state *gs,
    player_state *player,
    const int *input
) {
	for (int i = 0; i < 3; i++) {
		int type = input[(i*2)+0];
		int cost = input[(i*2)+1];
		if (type == RESOURCE_NONE) break;

		int *counter = get_resource(player, type);
		if (*counter < cost) {
			error(gs, E_RULES,
			    "Not enough %s for the conversion "
			    "(%d needed, have %d)",
			    get_resource_name(type),
			    cost, *counter
			);
			return 0;
		}

		if (is_animal_resource(type)) {
			int *placed = get_placed_animal(player, type);
			int unplaced = *counter - *placed;
			if (unplaced < cost) {
				// The number of animals needed to unplace
				unplace_animals(player, type, cost-unplaced);
			}
		}
	}
	return 1;
}


int caverna_convert_ruby_to_tile(
    game_state *gs,
    int conversion,
    const tile_placement *placement
) {
	// Get current player
	player_state *player = &gs->players[gs->cur_player];

	int cost_ruby = 0;
	int type = TILE_NONE;
	int underneath = TILE_NONE;

	int success = get_ruby_to_tile_conversion(
	    conversion, &cost_ruby, &underneath, &type);
	if (!success) {
		error(gs, E_INTERNAL,
		    "Unexpected conversion type: %d "
		    "(probably an ordinary resource conversion?)",
		    conversion
		);
		return 0;
	}

	success = pay_resource(gs, player, RESOURCE_RUBY, cost_ruby);
	if (!success) return 0;

	success = lay_single_tile(
	    gs, player,
	    placement,
	    type,
	    underneath
	);
	if (!success) return 0;

	return 1;
}

static int can_convert_ruby_to_tile(
    const player_state *player,
    int conversion
) {
	int cost_ruby = 0;
	int type = TILE_NONE;
	int underneath = TILE_NONE;

	int success = get_ruby_to_tile_conversion(
	    conversion, &cost_ruby, &underneath, &type);

	if (!success) {
		// TODO: crash?
		return 0;
	}

	if (player->ruby < cost_ruby) {
		// Not enough Rubies
		return 0;
	}

	if (!has_tile(player, underneath)) {
		// No proper tile to lay on
		return 0;
	}

	return 1;
}

static int can_convert_resources(
    const player_state *player,
    int conversion,
    int count
) {
	// Get configuration for the conversion
	const conversion_config *cc = get_conversion_config(conversion);
	if (cc == NULL) {
		// TODO: crash?
		return 0;
	}

	if ( (cc->tile_type != TILE_NONE)
	    && (!has_tile(player, cc->tile_type)) )
	{
		return 0;
	}

	if (conversion == CONV_PEACEFUL_CAVE) {
		return 1;
	}

	// The actual input/output of the resource conversion
	int input[3*2] = { RESOURCE_NONE, 0 };
	int output[3*2] = { RESOURCE_NONE, 0 };

	int success = get_resource_conversion(cc, count, input, output);
	if (!success) {
		// TODO: crash?
		return 0;
	}

	for (int i = 0; i < 3; i++) {
		int type = input[(i*2)+0];
		int cost = input[(i*2)+1];
		if (type == RESOURCE_NONE) break;

		int *counter = get_resource(player, type);
		if (*counter < cost) {
			return 0;
		}
	}

	return 1;
}

int caverna_can_convert(
    const player_state *player,
    int conversion,
    int count
) {
	if (is_ruby2tile_conversion(conversion)) {
		return can_convert_ruby_to_tile(player, conversion);
	}
	return can_convert_resources(player, conversion, count);
}

/** game_state is only for logging purposes */
int caverna_convert_resources(
    game_state *gs,
    int conversion,
    int count
) {

	// Verify game state.
	if ((gs->phase != PHASE_WORK)
	    && (gs->phase != PHASE_FINISH_TURN)
	    && (gs->phase != PHASE_HARVEST)
	    && (gs->phase != PHASE_FEED)
	    && (gs->phase != PHASE_BREED))
	{
		error(gs, E_RULES,
		    "Cannot convert resources in phase %d",
		    gs->phase
		);
		return 0;
	}

	// Get current player
	player_state *player = &gs->players[gs->cur_player];

	// Get configuration for the conversion
	const conversion_config *cc = get_conversion_config(conversion);

	// Assert that a configuration was found
	if (cc == NULL) {
		error(gs, E_INTERNAL,
		    "No such conversion type: %d",
		    conversion
		);
		return 0;
	}

	// Assert that a Furnishing tile requirement is
	// satisfied, if there is any.
	if ( (cc->tile_type != TILE_NONE)
	    && (!has_tile(player, cc->tile_type)) )
	{
		error(gs, E_RULES,
		    "Conversion type %d requires a Furnishing tile: %s",
		    conversion,
		    get_tile_name(cc->tile_type)
		);
		return 0;
	}

	// Special case: Peaceful cave
	if (conversion == CONV_PEACEFUL_CAVE) {
		convert_weapons_to_food(player);
		return 1;
	}

	// The actual input/output of the resource conversion
	int input[3*2] = { RESOURCE_NONE, 0 };
	int output[3*2] = { RESOURCE_NONE, 0 };

	int success;

	success = get_resource_conversion(cc, count, input, output);
	if (!success) {
		error(gs, E_INTERNAL,
		    "Unexpected conversion type: %d "
		    "(probably ruby-to-tile conversion?)",
		    conversion
		);
		return 0;
	}

	// Check that no newborn animal types are being converted
	for (int i = 0; i < 3; i++) {
		int type = input[(i*2)+0];
		if (type == RESOURCE_NONE) break;
		if (!is_farm_animal_type(type)) continue;
		int has_newborn = *get_newborn_animal(player, type);
		if (has_newborn) {
			error(gs, E_RULES,
			    "The resource conversion involves parent/newborn "
			    "%s, which is not allowed.",
			    get_resource_name(type)
			);
			return 0;
		}
	}


	// Check input requirements
	success = expect_resources(gs, player, input);
	if (!success) return 0;

	// Unplace animals, if necessary. TODO

	// Log and execute
	log_command2(
	    &player->log,
	    CMD_CONVERT_RESOURCES,
	    cc->type, count
	);
	convert_resources(player, input, output);

	// Resource conversion effects
	trigger_conversion_effect(player, conversion, count);

	return 1;
}

int caverna_take_action(
    game_state *gs,
    int dwarf_num,
    const action_orders *ao
) {

	if (gs->phase != PHASE_WORK) {
		error(gs, E_RULES,
		    "Cannot take an action space in phase %d",
		    gs->phase
		);
		return 0;
	}

	// For convenience
	int action_type = ao->type;

	// Get current player
	player_state *player = &gs->players[gs->cur_player];

	// Verify that the current player has actions left.
	if (player->workers >= player->dwarfs) {
		// The player does not have any dwarfs left.
		error(gs, E_ORDERS,
		    "The player #%d does not have any dwarfs left",
		    gs->cur_player
		);
		return 0;
	}

	// Please note that dwarf_num may be completely invalid
	// at this point, but the following check cannot yield
	// incorrect result. The validity of the dwarf_num
	// is verified at send_worker() function later on.

	// Find out whether the current dwarf is being played out of order,
	// in which case the player must pay 1 Ruby.

	int next_dwarf;
	int next_armed; // nuissance in this case
	get_next_dwarf(player, &next_dwarf, &next_armed);
	int out_of_order = (dwarf_num != next_dwarf);

	int success = 0;

	// Select correct function for handling the action orders.

	int (*play_action_func)(game_state *, int, const action_orders *);

	switch(action_type) {
	case ACTION_DRIFT_MINING:
		play_action_func = (void *) play_drift_mining;
		break;
	case ACTION_LOGGING:
		play_action_func = (void *) play_logging;
		break;
	case ACTION_WOOD_GATHERING:
		play_action_func = (void *) play_wood_gathering;
		break;
	case ACTION_EXCAVATION:
		play_action_func = (void *) play_excavation;
		break;
	// supplies
	// clearing
	// starting player
	case ACTION_ORE_MINING:
		play_action_func = (void *) play_ore_mining;
		break;
	case ACTION_SUSTENANCE:
		play_action_func = (void *) play_sustenance;
		break;
	case ACTION_RUBY_MINING:
		play_action_func = (void *) play_ruby_mining;
		break;
	case ACTION_HOUSEWORK:
		play_action_func = (void *) play_housework;
		break;
	case ACTION_SLASH_AND_BURN:
		play_action_func = (void *) play_slash_and_burn;
		break;
	case ACTION_BLACKSMITHING:
		play_action_func = (void *) play_blacksmithing;
		break;
	case ACTION_SHEEP_FARMING:
		play_action_func = (void *) play_sheep_farming;
		break;
	case ACTION_ORE_MINE_CONSTRUCTION:
		play_action_func = (void *) play_ore_mine_construction;
		break;
	case ACTION_WISH_FOR_CHILDREN:
		play_action_func = (void *) play_wish_for_children;
		break;
	case ACTION_URGENT_WISH_FOR_CHILDREN:
		play_action_func = (void *) play_urgent_wish_for_children;
		break;
	case ACTION_DONKEY_FARMING:
		play_action_func = (void *) play_donkey_farming;
		break;
	case ACTION_RUBY_MINE_CONSTRUCTION:
		play_action_func = (void *) play_ruby_mine_construction;
		break;
	case ACTION_ORE_DELIVERY:
		play_action_func = (void *) play_ore_delivery;
		break;
	case ACTION_FAMILY_LIFE:
		play_action_func = (void *) play_family_life;
		break;
	case ACTION_ORE_TRADING:
		play_action_func = (void *) play_ore_trading;
		break;
	case ACTION_ADVENTURE:
		play_action_func = (void *) play_adventure;
		break;
	case ACTION_RUBY_DELIVERY:
		play_action_func = (void *) play_ruby_delivery;
		break;
	default:
		// TODO: report this soft error using some other method.
		fprintf(stderr,
		    "(caverna_take_action) "
		    "unimplemented handler for action order type: %d\n",
		    action_type
		);
		play_action_func = NULL;
	}

	if (play_action_func == NULL) {
		return 0;
	}

	do {

		// If the Dwarf is being played out of order, pay 1 Ruby.
		if (out_of_order) {
			success = pay_resource(
			    gs, player,
			    RESOURCE_RUBY, 1
			);
	                if (!success) break;
		}

		// Send a dwarf to work before playing the action.
		// This will validate: (i) dwarf_num is in valid range,
		// (ii) dwarf_num is unemployed, (iii) action space is vacant.
		success = send_worker(player, dwarf_num, gs, ao->type);
		if (!success) break;

		success = play_action_func(
		    gs,
		    dwarf_num,
		    (const void *) ao->orders
		);
	} while (0);

	if (success) {
		incorporate_player_commands(gs, player);
		// The phase may have been set by gain_loot()
		// to PHASE_BREED with breed set to BREED_UPTO2_ONCE/TWICE.
		// In that case, retain the state.
		if (gs->phase == PHASE_WORK) {
			set_phase(gs, PHASE_FINISH_TURN);
		}
	} else {
		rollback_player_commands(gs, player);
	}

	return success;
}

int caverna_put_ruby_on_action(game_state *gs, int action_type) {
	if ((gs->phase != PHASE_WORK) && (gs->phase != PHASE_FINISH_TURN)) {
		error(gs, E_RULES,
		    "Cannot place a Ruby on an action space in phase %d",
		    gs->phase
		);
		return 0;
	}

	if (gs->num_players != 1) {
		error(gs, E_RULES,
		    "This operation is available only in the Solo game"
		);
		return 0;
	}

	player_state *player = &gs->players[gs->cur_player];

	return put_ruby_on_action(gs, player, action_type);


	return 1;
}


int caverna_start(game_state *gs, int num_players) {
	int success = 0;
	do {
		if ((num_players < 0) || (num_players > MAX_PLAYERS)) {
			break;
		}

		gs->num_players = num_players;
		gs->cur_player = 0;
		gs->cur_round = 0;
		gs->phase = PHASE_NONE;
		// TODO: Other setup

		for (int i = 0; i < num_players; i++) {
			player_state *p = &gs->players[i];
			// Setup the standard board.
			setup_board(p->board);
			reset_player(p);
			// Start with 2 dwarfs
			p->dwarfs = 2;
		}

		if (num_players == 1) {
			// Playing solo.
			// Start with 2 food
			gs->players[0].food = 2;
			// Setup actions accordingly
			setup_actions_solo(gs->actions, &gs->num_actions);
		} else {
			// Otherwise different foods.
			// TODO: setup_actions(actions, num_actions, num_players)
		}

		// This depends on game parameters. TODO
		setup_all_furnishings(gs->furnishings, &gs->num_furnishings);

		gs->phase = PHASE_BEGIN_ROUND;

		// The initial replenish cannot be undone.
		gs->last_command = gs->log.tail;

		success = 1;
	} while (0);

	return success;
}


int caverna_get_cur_round(const game_state *gs) {
	return gs->cur_round;
}

int caverna_get_cur_player(const game_state *gs) {
	return gs->cur_player;
}

const player_state *caverna_get_player(
    const game_state *gs,
    int player_num
) {
	if ((player_num < 0) || (player_num >= gs->num_players)) {
		return NULL;
	}
	return &gs->players[player_num];
}

int caverna_end_of_turn(const game_state *gs) {
	return gs->phase == PHASE_FINISH_TURN;
}

static int num_unplaced_animals(const player_state *player) {
	// Animals on the board (both Mountain and Forest)
	int sheep = 0;
	int donkey = 0;
	int boar = 0;
	int cattle = 0;
	int dog = 0;

	// Board limits
	int xmin, ymin, xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	// Account animals
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			const tile_state *top
			    = get_top_tile(player->board, x, y, &z);

			// Accumulate
			sheep += top->sheep;
			donkey += top->donkey;
			boar += top->boar;
			cattle += top->cattle;
			dog += top->dog;
		}
	}

	int diff[5];
	diff[0] = player->sheep - sheep;
	diff[1] = player->donkey - donkey;
	diff[2] = player->boar - boar;
	diff[3] = player->cattle - cattle;
	//diff[4] = player->dog - dog;
	diff[4] = 0; // Dogs are not accounted into this

	int total = 0;
	for (int i = 0; i < 5; i++) {
		total += diff[i];
	}
	return total;
}

int caverna_num_unplaced_animals(const game_state *gs) {
	const player_state *player = &gs->players[gs->cur_player];
	return num_unplaced_animals(player);
}

static int powi(int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}

/** player is needed for Cuddle room capacity computation */
static int get_animal_capacity(
    const player_state *player,
    int x, int y,
    int *type
) {
	int z;
	tile_state *top = get_top_tile(player->board, x, y, &z);
	int cap = 0;
	*type = RESOURCE_NONE;

	// Total number of Dogs in the tile or in both tiles,
	// if the tile is part of Large pasture.
	int dogs = top->dog;

	if (top->type == TILE_SMALL_PASTURE) {
		cap = 2;
		// Adjust for stable
		if (top->stable > 0) cap *= 2;
	}
	else if (top->type == TILE_LARGE_PASTURE) {
		// Total capacity of a Large pasture.
		cap = 4;
		// Get the other tile
		tile_state *other = get_other_tile(
		    player->board, x, y, top->dir);
		// Adjust for stables
		if (top->stable > 0) cap *= 2;
		if (other->stable > 0) cap *= 2;

		// Account the Dogs in the other tile too
		dogs += other->dog;
	}
	else if (top->type == TILE_INITIAL_DWELLING) {
		cap = 2;
	}
	else if (top->type == TILE_MIXED_DWELLING) {
		cap = 2;
	}
	else if (top->type == TILE_CUDDLE_ROOM) {
		// The baby Dwarfs are accounted here too (Appendix, p. A3)
		cap = player->dwarfs + player->children;
		*type = RESOURCE_SHEEP;
	}
	else if (top->type == TILE_BREAKFAST_ROOM) {
		// Breakfast room can hold up to 3 Cattle,
		// but no other Farm animals (Appendix, p. A3)
		cap = 3;
		*type = RESOURCE_CATTLE;
	}
	else if ((top->type == TILE_ORE_MINE)
	    || (top->type == TILE_RUBY_MINE))
	{
		// Each Ore or Ruby mine can hold 1 Donkey (Rules, p. 20)
		cap = 1;
		*type = RESOURCE_DONKEY;
	}
	else if (top->type == TILE_MEADOW) {
		// A Stable on a Meadow space can hold
		// any 1 Farm animal (Rules, p. 20)
		cap = (top->stable > 0);
	}
	else if (top->type == TILE_FOREST) {
		// A Stable on a Forest space that has not been covered
		// by a tile can hold exactly 1 Wild boar (Rules, p. 20)
		if (top->stable > 0) {
			cap = 1;
			*type = RESOURCE_BOAR;
		}
	}
	else if (top->type == TILE_FIELD) {
		// Stubble room: You can keep (exactly) 1 Farm animal
		// on each of your empty Fields (i.e. that currently do
		// not have any Grain or Vegetables sown on them).
		// (Appendix, p. A3)
		if ( has_tile(player, TILE_STUBBLE_ROOM)
		    && (top->vegetable == 0)
		    && (top->grain == 0) )
		{
			cap = 1;
		}
	}

	// Dog override
	if ( (top->type == TILE_MEADOW)
	    || (top->type == TILE_SMALL_PASTURE)
	    || (top->type == TILE_LARGE_PASTURE) )
	{
		// Instead of normal rules for Meadows and Pastures
		// (with or without Stables), you can apply the following
		// when you place Dogs on them: You can keep one more Sheep
		// on the Meadow or Pasture than there are Dogs on it.
		// (Rules, p. 20)
		if (top->dog > 0) {
			cap = dogs + 1;
			*type = RESOURCE_SHEEP;
		}
	}

	return cap;
}

static int verify_tile_animals(
    game_state *gs,
    const player_state *player,
    int x, int y
) {
	// For convenience
	const tile_state *board = player->board;

	int z; // nuissance
	tile_state *top = get_top_tile(board, x, y, &z);

	// There may be only one kind of Farm animal placed on the tile.
	int num_types = (top->sheep > 0) + (top->donkey > 0)
	    + (top->boar > 0) + (top->cattle > 0);

	if (num_types > 1) {
		error(gs, E_RULES,
		    "The tile (%s) at %c%d has %d types of Farm animals",
		    get_tile_name(top->type),
		    'A'+y, x+1, num_types
		);
		return 0;
	}

	// At this point: the tile contains one kind of Farm animal at most.
	// However, the tile may contain Dogs also.

	int type = get_tile_animal_type(top);
	int num_animals = 0;
	if (type != RESOURCE_NONE) {
		num_animals = *get_tile_resource(top, type);
	}

	// Compute the animal capacity for the tile,
	// and get the type of animal it may contain,
	// or RESOURCE_NONE, if the type is not restricted.
	// This accounts for the Dogs on the tile, if any.

	int capacity = 0;
	int only_type = RESOURCE_NONE;
	capacity = get_animal_capacity(player, x, y, &only_type);

	if ((type != RESOURCE_NONE) && (only_type != RESOURCE_NONE)
	    && (type != only_type))
	{
		error(gs, E_RULES,
		    "The tile (%s) at %c%d can only hold %s, "
		    "but currently it contains %d %s",
		    get_tile_name(top->type),
		    'A'+y, x+1,
		    get_resource_name(only_type),
		    num_animals, get_resource_name(type)
		);
		return 0;
	}

	if (num_animals > capacity) {
		error(gs, E_RULES,
		    "The tile (%s) at %c%d can only hold %d animals, "
		    "but currently it contains %d %s",
		    get_tile_name(top->type),
		    'A'+y, x+1,
		    capacity,
		    num_animals, get_resource_name(type)
		);
		return 0;
	}

	return 1;
}

static int verify_animal_placements(
    game_state *gs,
    const player_state *player
) {
	// Board limits
	int xmin, ymin, xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int success = verify_tile_animals(gs, player, x, y);
			if (!success) return 0;
		}
	}

	return 1;
}

int caverna_verify_animal_arrangement(game_state *gs, const player_state *player) {
	return verify_animal_placements(gs, player);
}


static int place_animals(player_state *player) {
	// Board limits
	int xmin, ymin, xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	// Account animals, and capacities
	// On the first rounds, place dogs on empty meadows

	// Linearize top tiles to an array for brevity and convenience
	tile_state *tiles[BOARD_LEVEL_SIZE];
	int z[BOARD_LEVEL_SIZE];
	int num_tiles = 0;
	int empty_meadows = 0;

	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			tile_state *t = get_top_tile(
			    player->board, x, y, &z[num_tiles]);
			tiles[num_tiles++] = t;

			if ((t->type == TILE_MEADOW)
			    && (t->stable == 0))
			{
				empty_meadows++;
			}
		}
	}

	// Animals on the board (both Mountain and Forest)
	int sheep = 0;
	int donkey = 0;
	int boar = 0;
	int cattle = 0;
	int dog = 0;

	for (int i = 0; i < num_tiles; i++) {
		tile_state *tile = tiles[i];

		// Accumulate
		sheep += tile->sheep;
		donkey += tile->donkey;
		boar += tile->boar;
		cattle += tile->cattle;
		dog += tile->dog;
	}

	// Compute the number of unplaced animals.
	sheep = player->sheep - sheep;
	donkey = player->donkey - donkey;
	boar = player->boar - boar;
	cattle = player->cattle - cattle;
	dog = player->dog - dog;

	sheep = player->sheep - player->placed_sheep;
	donkey = player->donkey - player->placed_donkey;
	boar = player->boar - player->placed_boar;
	cattle = player->cattle - player->placed_cattle;
	dog = player->dog - player->placed_dog;

	// Start by placing Donkeys in Mines,
	// Sheeps in Cuddle room, Cattles in Breakfast room.

	int x = xmin-1;
	int y = ymin;
	for (int i = 0; i < num_tiles; i++) {
		x++;
		if (x > xmax) {
			x = xmin;
			y++;
		}

		tile_state *tile = tiles[i];

		if ((tile->type == TILE_ORE_MINE)
		    || (tile->type == TILE_RUBY_MINE))
		{
			if ((tile->donkey == 0) && (donkey > 0)) {
				drop_animal_to_tile(
				    player, x, y, z[i],
				    RESOURCE_DONKEY, 1
				);
				donkey--;
			}
		}
		else if (tile->type == TILE_CUDDLE_ROOM) {
			// The baby dwarfs count here too.
			int space = (player->dwarfs + player->children)
			    - tile->sheep;
			if ((space > 0) && (sheep > 0)) {
				// Place as many Sheep as possible
				int qty = sheep;
				if (qty > space) qty = space;
				drop_animal_to_tile(
				    player, x, y, z[i],
				    RESOURCE_SHEEP, qty
				);
				sheep -= qty;
			}
		}
		else if (tile->type == TILE_BREAKFAST_ROOM) {
			// Breakfast room has space for 3 Cattle.
			int space = 3 - tile->cattle;
			if ((space > 0) && (cattle > 0)) {
				int qty = cattle;
				if (qty > space) qty = space;
				drop_animal_to_tile(
				    player, x, y, z[i],
				    RESOURCE_CATTLE, qty
				);
				cattle -= qty;
			}
		}
	}

	// Distribute unplaced Dogs evenly into Meadows
	for (int i = 1; i <= dog; i++) {
		x = xmin-1;
		y = ymin;
		for (int j = 0; j < num_tiles; j++) {
			x++;
			if (x > xmax) {
				x = xmin;
				y++;
			}

			tile_state *tile = tiles[j];

			if (tile->type != TILE_MEADOW) continue;
			if (tile->stable > 0) continue;
			if (tile->dog > i) continue;
			drop_animal_to_tile(
			    player, x, y, z[j],
			    RESOURCE_DOG, 1
			);
			dog--;
			if (dog == 0) break;
		}
		if (dog == 0) break;
	}

	// Place Sheep into Meadows with Dogs
	if ((sheep > 0) && (empty_meadows > 0)) {
		x = xmin-1;
		y = ymin;
		for (int i = 0; i < num_tiles; i++) {
			// Maintain coordinates
			x++;
			if (x > xmax) {
				x = xmin;
				y++;
			}
			tile_state *tile = tiles[i];
			if (tile->dog == 0) continue;
			int space = tile->dog + 1 - tile->sheep;
			if (space == 0) continue;

			int qty = sheep;
			if (qty > space) qty = space;

			drop_animal_to_tile(
			    player, x, y, z[i],
			    RESOURCE_SHEEP, qty
			);
			sheep -= qty;
			if (sheep == 0) break;
		}
	}

	// Traverse through to see if there is a dedicated
	// storage with unused capacity left, if so, put there.

	// Place any animal left in the first place
	// where they are allowed to be put
	for (int phase = 0; phase < 2; phase++) {
	x = xmin-1;
	y = ymin;
	for (int i = 0; i < num_tiles; i++) {
		// Maintain coordinates
		x++;
		if (x > xmax) {
			x = xmin;
			y++;
		}

		tile_state *tile = tiles[i];
		int type = RESOURCE_NONE;
		int only_type = RESOURCE_NONE;
		int space = 0;

		space = get_animal_capacity(player, x, y, &only_type);
		type = get_tile_animal_type(tile);

		// Do not bother if there is no space.
		if (space == 0) continue;

		if (tile->type == TILE_LARGE_PASTURE) {
			// Get other tile
			tile_state *other
			    = get_other_tile(player->board, x, y, tile->dir);

			int other_type = get_tile_animal_type(other);
			if (other_type != RESOURCE_NONE) {
				int *on_other_tile = get_tile_resource(
				    other, other_type);
				space -= *on_other_tile;
				if (type == RESOURCE_NONE) {
					type = other_type;
				} else if (type != other_type) {
					// TODO: Illegal placement
				}
			}
		}

		// Reduce the animals already occupying the tile.
		int *on_tile = NULL;
		int *left = NULL;

		if (type != RESOURCE_NONE) {
			// There is already some type of animal on the tile.
			if (type == RESOURCE_SHEEP) {
				left = &sheep;
			}
			else if (type == RESOURCE_DONKEY) {
				left = &donkey;
			}
			else if (type == RESOURCE_BOAR) {
				left = &boar;
			}
			else if (type == RESOURCE_CATTLE) {
				left = &cattle;
			}
		} else if ((phase == 0) && (only_type != RESOURCE_NONE)) {
			if (only_type == RESOURCE_SHEEP) {
				type = RESOURCE_SHEEP;
				left = &sheep;
			}
			else if (only_type == RESOURCE_DONKEY) {
				type = RESOURCE_DONKEY;
				left = &donkey;
			}
			else if (only_type == RESOURCE_BOAR) {
				type = RESOURCE_BOAR;
				left = &boar;
			}
			else if (only_type == RESOURCE_CATTLE) {
				type = RESOURCE_CATTLE;
				left = &cattle;
			}
		} else if ((phase == 1) && (only_type == RESOURCE_NONE)) {
			// Vacant space for any kind of animal
			if (sheep > 0) {
				type = RESOURCE_SHEEP;
				left = &sheep;
			} else if (donkey > 0) {
				type = RESOURCE_DONKEY;
				left = &donkey;
			} else if (boar > 0) {
				type = RESOURCE_BOAR;
				left = &boar;
			} else if (cattle > 0) {
				type = RESOURCE_CATTLE;
				left = &cattle;
			}
		}
		if ((left != NULL) && (*left == 0)) left = NULL;

		if (type != RESOURCE_NONE) {
			on_tile = get_tile_resource(tile, type);
			space -= *on_tile;
		}

		if ((left != NULL) && (type != RESOURCE_NONE)) {
			int qty = *left;
			if (qty > space) qty = space;

			drop_animal_to_tile(
			    player, x, y, z[i],
			    type, qty
			);

			*left -= qty;
		}

		// Now the information has been populated and time
		// to make decision

	}
	} // phase
	// TODO: What about dogs here?
	return (sheep + donkey + boar + cattle) == 0;
}

int caverna_place_animals(game_state *gs) {
	if ((gs->phase != PHASE_FINISH_TURN)
	    && (gs->phase != PHASE_WORK)
	    && (gs->phase != PHASE_BREED)
	    && (gs->phase != PHASE_HARVEST)
	    && (gs->phase != PHASE_FEED))
	{
		error(gs, E_RULES,
		    "Cannot place animals in phase %d",
		    gs->phase
		);
		return 0;
	}

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	return place_animals(player);
}

static void init_comb(int n, int k, unsigned int *c) {
	for (int i = 0; i < k; i++) c[i] = k - i;
}

static int next_comb(int m, int n, unsigned int *c) {
	int i;
	if (c[0]++ < m) {
		return 1;
	}

	for (i = 0; c[i] >= m - i;) {
		if (++i >= n) {
			return 0;
		}
	}

	for (c[i]++; i; i--) {
		c[i-1] = c[i] + 1;
	}
	return 1;
}

struct capacity_config {
	/** X coordinate for the holding space. */
	int x;

	/** Y coordinate for the holding space. */
	int y;

	/** Type of the animal the holding space can hold,
	 * or RESOURCE_NONE if any type. */
	int type;

	/** Capacity of the holding space. */
	int capacity;

	/** Number of dogs allocated to this space, or -1 if not possible. */
	int dog;

	/** Quantity of the resource to be accommodated. */
	int qty;
};
typedef struct capacity_config capacity_config;

struct animal_rearrangement {
	/** Capacity configurations. */
	capacity_config spaces[BOARD_LEVEL_SIZE];

	/** Total number of spaces. */
	int num_spaces;
};
typedef struct animal_rearrangement animal_rearrangement;

static void add_capacity(
    animal_rearrangement *re,
    int x, int y,
    int type,
    int capacity,
    int may_contain_dogs
) {
	// For convenience
	capacity_config *space = &re->spaces[re->num_spaces++];
	space->x = x;
	space->y = y;
	space->type = type;
	space->capacity = capacity;
	space->dog = may_contain_dogs ? 0 : -1;
	space->qty = 0;
}

static void swap_cap(capacity_config *a, capacity_config *b) {
	capacity_config temp = *a;
	*a = *b;
	*b = temp;
}


// forward declaration
static int rearrange_nchoosek(
    int *animals,
    int animal_num,
    capacity_config *caps,
    int num_caps,
    int k
);

static int rearrange(
    int *animals,
    int animal_num,
    capacity_config *caps,
    int num_caps
) {
	if (animal_num == 4) {
		return 1;
	}

	int needed = animals[animal_num];
	if (needed == 0) {
		// Skip to the next animal
		return rearrange(animals, animal_num+1, caps, num_caps);
	}

	if (num_caps == 0) {
		// There is at least one animal needing accommodation,
		// but there are not any holding capacity left.
		return 0;
	}

	for (int k = 1; k <= num_caps; k++) {
		int success;
		success = rearrange_nchoosek(
		    animals, animal_num, caps, num_caps, k);
		if (success == 1) {
			// Found match
			return 1;
		} else if (success == -1) {
			// All combinations fitted the current animal,
			// so do not bother to try the next size.
			break;
		}
	}

	// All combinations of all sizes exhausted
	return 0;
}

// If there is not enough capacity, but the Farm animal that is being fitted
// is Sheep and there are unplaced Dogs left. In that case reconsile
// the possibility to use Dogs. Placing dogs on a feature (Meadow with
// a Stable or a Pasture) converts the feature into a Sheep-only holding
// spaces, hopefully with a larger capacity.

// Here it is important to know that Large pastures are considered as
// a single spaces. See the message
//
// https://boardgamegeek.com/article/16305280#16305280
//
// This provides a desperately needed simplification to the algorithm.

// Consider the following fact. Once all dogs are placed into an empty
// Meadow, the total animal capacity cannot be increased by moving dogs
// to replace any feature capable of holding at least 1 animal.

// To see this, lets take an example.
// Let A = empty Meadow, B = Stabled Meadow #1, and C = Stabled Meadow #2.
// Lets try out different Dog assignments:
//
//   A   B   C    Capacity
//   6   0   0    7+1+1=9
//   5   1   0    6+2+1=9
//   4   1   1    5+2+2=9
//   3   2   1    4+3+2=9
//   2   2   2    3+3+3=9
//   1   3   2    2+4+3=9

// A consequence of this fact is that if there are empty Meadows, once
// the Dogs are distributed to those tiles, it is IMPOSSIBLE to increase
// the total capacity by moving dogs from a Meadow to some other features.

// Another consequence is that if there are no empty Meadows, the Dogs may
// be used to replace only one feature. Once a feature has been replaced,
// it is IMPOSSIBLE to increase the total capacity by moving dogs from that
// feature to replace another feature. Therefore, if there are no empty
// Meadows, the Dogs should replace the feature which has the least capacity,
// and only if the capacity of the original feature is less than
// the capacity provided by the dogs.

static int rearrange_nchoosek(
    int *animals,
    int animal_num,
    capacity_config *caps,
    int num_caps,
    int k
) {
	// Theoretical limit to num_caps
	unsigned int comb[16];
	init_comb(num_caps, k, comb);
	int needed = animals[animal_num];

	int type = RESOURCE_NONE;
	if (animal_num == 0) type = RESOURCE_SHEEP;
	else if (animal_num == 1) type = RESOURCE_DONKEY;
	else if (animal_num == 2) type = RESOURCE_BOAR;
	else if (animal_num == 3) type = RESOURCE_CATTLE;
	else {
		fprintf(stderr,
		    "(rearrange_nchoosek) "
		    "unexpected animal_num: %d\n",
		    animal_num
		);
		exit(1);
	}

	int unfittings = 0;
	do {
		// Count the total capacity
		int cap = 0;
		for (int i = 0; i < k; i++) cap += caps[comb[i]-1].capacity;

		if ( (cap < needed)
		    && (type == RESOURCE_SHEEP) && (animals[4] > 0) )
		{
			// For convenience
			int dogs = animals[4];

			// Count the number of holding spaces
			// in which Dogs may be placed.
			int num_spaces = 0;
			int indices[16];
			for (int i = 0; i < k; i++) {
				int j = comb[i]-1;
				if (caps[j].dog == -1) continue;
				indices[num_spaces++] = j;
			}

			// Dogs cannot be placed, so the capacity holds
			if (num_spaces == 0) {
				// No fit
				unfittings++;
				continue;
			}

			// Re-compute the capacity.
			// This tries out to replace each holding space

			int replaced_i = -1;
			int replaced_cap = -1;
			for (int i = 0; i < num_spaces; i++) {
				int j = indices[i];
				int j_cap = caps[j].capacity;
				int new_cap = cap + (dogs+1) - j_cap;

				// Skip if this replacement does not provide
				// enough capacity
				if (new_cap < needed) continue;

				// Otherwise see if this replacement
				// is more compact than the previous,
				// if any.
				if ((replaced_i == -1)
				    || (j_cap < replaced_cap))
				{
					replaced_i = i;
					replaced_cap = j_cap;
				}
			} // for: each different space

			if (replaced_i != -1) {
				// Sheeps can be fitted by replacing
				// this feature with Dogs.
				int j = indices[replaced_i];
				if (caps[j].dog == -1) {
					fprintf(stderr, "bug3\n");
					exit(1);
				}
				caps[j].dog = dogs;
				cap = cap + (dogs+1) - caps[j].capacity;
			}
		} // if: no capacity for Sheep, but there are Dogs

		if (cap < needed) {
			// No fit
			unfittings++;
			continue;
		}

		// Good to recurse.
		// Permute the caps left.
		for (int i = 0; i < k; i++) {
			int a = i;
			int b = comb[k-i-1]-1;
			caps[b].type = type;
			swap_cap(&caps[a], &caps[b]);
		}

		int success = rearrange(
		    animals, animal_num+1, &caps[k], num_caps-k);
		if (success) return 1;

		// Unpermute the caps left
		for (int i = 0; i < k; i++) {
			int a = i;
			int b = comb[k-i-1]-1;
			swap_cap(&caps[a], &caps[b]);
			caps[b].type = RESOURCE_NONE;
			// Remove any dogs
			if (caps[b].dog > 0) caps[b].dog = 0;
		}
	} while (next_comb(num_caps, k, comb));

	if (unfittings == 0) {
		// Current Farm animal type was succesfully fitted
		// to all combinations, but no arrangement was found
		// for the rest of the Farm animals.
		// In this case the algorithm signals the caller
		// that it is time to try a new combination
		// for the preceding Farm animals.
		return -1; // Rollback fast-forward.
	}

	// All combinations exhausted
	return 0;
}

static void fill_capacities(
    const player_state *player,
    int *animals,
    capacity_config *spaces,
    int num_spaces
) {
	// Accommodate specific ones
	for (int i = 0; i < num_spaces; i++) {
		// For convenience
		capacity_config *space = &spaces[i];

		// Skip if no type
		if (space->type == RESOURCE_NONE) continue;

		int *left = NULL;
		switch(space->type) {
		case RESOURCE_SHEEP:
			left = &animals[0];
			break;
		case RESOURCE_DONKEY:
			left = &animals[1];
			break;
		case RESOURCE_BOAR:
			left = &animals[2];
			break;
		case RESOURCE_CATTLE:
			left = &animals[3];
			break;
		default:
			fprintf(stderr,
			    "(fill_capacities) unexpected space->type: %d\n",
			    space->type
			);
			exit(1);
		}

		if (*left == 0) continue;

		// Compute the capacity (if dogs, they are used for capacity)
		int capacity = space->capacity;
		if (space->dog > 0) capacity = space->dog + 1;

		// Allocate qty for this capacity

		int qty = *left;
		if (qty > capacity) qty = capacity;
		*left -= qty;
		space->qty = qty;

		// Allocate dogs for this capacity, if any.
		if (space->dog != -1) {
			animals[4] -= space->dog;
		}
	}
}

/** Execute the animal diffing (take/drop) to the board */
static void rearrange_animals(
    player_state *player,
    const animal_rearrangement *re
) {
	static const int animal_types[] = {
		RESOURCE_SHEEP,
		RESOURCE_DONKEY,
		RESOURCE_BOAR,
		RESOURCE_CATTLE
	};

	for (int i = 0; i < re->num_spaces; i++) {
		const capacity_config *space = &re->spaces[i];
		int x1 = space->x;
		int y1 = space->y;
		int z1;
		int type = space->type;

		int x2 = x1;
		int y2 = y1;
		int z2;

		tile_state *tile = get_top_tile(player->board, x1, y1, &z1);
		tile_state *other = NULL;

		if (tile->type == TILE_LARGE_PASTURE) {
			move_coordinates(&x2, &y2, tile->dir);
			other = get_top_tile(player->board, x2, y2, &z2);
		}

		// TODO: Make it into a subroutine, taking animal type
		// and target qty as parameters, plus coordinates.
		for (int j = 0; j < 4; j++) {
			int animal_type = animal_types[j];

			int count1 = 0;
			int count2 = 0;

			count1 = *get_tile_resource(tile, animal_type);
			if (other != NULL) {
				count2 = *get_tile_resource(other, animal_type);
			}

			// Total number of animals in both tiles
			int total = count1 + count2;

			int qty1 = 0;
			int qty2 = 0;

		 	if (type != animal_type) {
				// Non-matching animal type.
				// Remove all, from both tiles.
				qty1 = count1;
				qty2 = count2;
			} else if (space->qty < total) {
				// Matching animal type.
				// Remove excess animals, if any.
				qty1 = total - space->qty;
				if (count1 < qty1) qty1 = count1;
				// Remove "qty1" from the first tile.
				// Update the number of animals left
				total -= qty1;
				// Compute the number of animals to remove
				// from the second tile
				qty2 = total - space->qty;
				// Assert count2 >= qty2
				if (count2 < qty2) {
					fprintf(stderr,
					    "(rearrange_animals) "
					    "Computation error: "
					    "count1=%d, count2=%d, "
					    "qty1=%d, qty2=%d\n",
					    count1, count2, qty1, qty2
					);
					exit(1);
				}
			}

			if (qty1 == 0) {
			} else {
				take_animal_from_tile(
				    player, x1, y1, z1,
				    animal_type, qty1
				);
			}
			if (other == NULL) {
				// No other tile.
			} else if (qty2 == 0) {
			} else {
				take_animal_from_tile(
				    player, x2, y2, z2,
				    animal_type, qty2
				);
			}
		} // for each animal type

		// Take off the excess dogs also
		int count1 = 0;
		int count2 = 0;
		count1 = tile->dog;
		if (other != NULL) {
			count2 = other->dog;
		}
		// Total number of dogs
		int total = count1 + count2;
		if ((space->dog != -1) && (space->dog < total)) {
			int qty1 = 0;
			int qty2 = 0;
			qty1 = total - space->dog;
			if (count1 < qty1) qty1 = count1;
			total -= qty1;
			qty2 = total - space->dog;
			if (count2 < qty2) {
					fprintf(stderr,
					    "(rearrange_animals) "
					    "Computation error: "
					    "count1=%d, count2=%d, "
					    "qty1=%d, qty2=%d\n",
					    count1, count2, qty1, qty2
					);
					exit(1);
			}

			if (qty1 > 0) {
				take_animal_from_tile(
				    player, x1, y1, z1,
				    RESOURCE_DOG, qty1
				);
			}
			if (qty2 > 0) {
				take_animal_from_tile(
				    player, x2, y2, z2,
				    RESOURCE_DOG, qty1
				);
			}
		}
	} // for each space

	// Drop animals to tiles
	for (int i = 0; i < re->num_spaces; i++) {
		const capacity_config *space = &re->spaces[i];
		int type = space->type;
		int x1 = space->x;
		int y1 = space->y;
		int z1;

		int x2 = x1;
		int y2 = y1;
		int z2;

		int count1 = 0;
		int count2 = 0;
		int total = 0;

		tile_state *tile = get_top_tile(player->board, x1, y1, &z1);
		tile_state *other = NULL;

		if (tile->type == TILE_LARGE_PASTURE) {
			move_coordinates(&x2, &y2, tile->dir);
			other = get_top_tile(player->board, x2, y2, &z2);
		}

		// Accommodate dogs, if any.

		count1 = tile->dog;
		if (other != NULL) {
			count2 = other->dog;
		}

		// Total number of dogs
		total = count1 + count2;

		// See if the tile is missing Dogs
		if ((space->dog != -1) && (total < space->dog)) {
			int qty1 = 0;
			int qty2 = 0;
			qty1 = space->dog - total;

			if (qty1 > 0) {
				drop_animal_to_tile(
				    player, x1, y1, z1,
				    RESOURCE_DOG, qty1
				);
			}
		}

		// Accommodate animals, if any.

		// Skip if nothing is going to be accommodated
		if (type == RESOURCE_NONE) continue;

		count1 = *get_tile_resource(tile, type);
		if (other != NULL) {
			count2 = *get_tile_resource(other, type);
		}
		total = count1 + count2;

		int qty1 = 0;
		int qty2 = 0;

		qty1 = space->qty - total;

		/*
		if (other != NULL) {
			// Distribute evenly
			qty2 = qty1 / 2;
			qty1 -= qty2;
		}
		*/

		// Skip, if the tile has the planned quantity.
		if (qty1 == 0) continue;

		// TODO: If twin-tile, distribute qty to both tiles evenly.
		drop_animal_to_tile(
		    player, x1, y1, z1,
		    type, qty1
		);
	}
}

static int find_animal_rearrangement(
    const player_state *player,
    animal_rearrangement *rearrangement
) {
	animal_rearrangement re;
	re.num_spaces = 0;

	int has_stubble_room = has_tile(player, TILE_STUBBLE_ROOM);

	// Animals on the board (both Mountain and Forest)

	// Board limits
	int xmin, ymin, xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	// Each Meadow can be used to place dogs,
	// which can guard Sheep. However, if the Meadow
	// has a Stable, it cannot be utilized if dogs are placed.
	int empty_meadows = 0;
	int stabled_meadows = 0;

	// TODO: Account for Stubble room

	// Account capacities
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			const tile_state *top
			    = get_top_tile(player->board, x, y, &z);

			if (top->type == TILE_FOREST) {
				if (top->stable == 0) continue;
				add_capacity(&re, x, y, RESOURCE_BOAR, 1, 0);
			}
			else if ((top->type == TILE_RUBY_MINE)
			    || (top->type == TILE_ORE_MINE))
			{
				add_capacity(&re, x, y, RESOURCE_DONKEY, 1, 0);
			}
			else if (top->type == TILE_MEADOW) {
				if (top->stable == 0) {
					empty_meadows++;
					// The empty meadow capacities will
					// be decided a posteriori.
					add_capacity(&re, x, y, RESOURCE_SHEEP, 0, 1);
				} else {
					stabled_meadows++;
					// Stable on a Meadow can
					// hold 1 Farm animal
					add_capacity(&re, x, y, RESOURCE_NONE, 1, 1);

				}
			} else if (top->type == TILE_FIELD) {
				if ( has_stubble_room
				    && (top->grain == 0)
				    && (top->vegetable == 0) )
				{
					add_capacity(&re, x, y,
					    RESOURCE_NONE, 1, 0);
				}
			}
			else if (top->type == TILE_CUDDLE_ROOM) {
				// There can be only 1 Cuddle room.
				int cap = player->dwarfs + player->children;
				add_capacity(&re, x, y,
				    RESOURCE_SHEEP, cap, 0);
			}
			else if (top->type == TILE_BREAKFAST_ROOM) {
				// There can be only 1 Breakfast room.
				add_capacity(&re, x, y, RESOURCE_CATTLE, 3, 0);
			}
			else if (top->type == TILE_INITIAL_DWELLING) {
				add_capacity(&re, x, y, RESOURCE_NONE, 2, 0);
			}
			else if (top->type == TILE_MIXED_DWELLING) {
				add_capacity(&re, x, y, RESOURCE_NONE, 2, 0);
			}
			else if (top->type == TILE_SMALL_PASTURE) {
				int cap = 2*powi(2, top->stable);
				add_capacity(&re, x, y, RESOURCE_NONE, cap, 1);
			}
			else if (top->type == TILE_LARGE_PASTURE) {
				if ((top->dir == DIRECTION_UP)
				    || (top->dir == DIRECTION_LEFT))
				{
					continue;
				}
				int x2 = x;
				int y2 = y;
				move_coordinates(&x2, &y2, top->dir);

				// Get the number of stables
				// in the other space.
				int z2;
				const tile_state *other = get_top_tile(
				    player->board, x2, y2, &z2);

				int stables = (top->stable > 0)
				    + (other->stable > 0);
				int cap = 4*powi(2, stables);
				add_capacity(&re, x, y, RESOURCE_NONE, cap, 1);
			}
		} // for x
	} // for y

	// Accommodate dogs to empty meadows.
	if (empty_meadows > 0) {
		int dogs_per_meadow = player->dog / empty_meadows;
		int plus_ones = player->dog % empty_meadows;

		// TODO: Also in this case there is a slight marginal
		// possibility that one non-empty meadow might be
		// needed to convert to a Sheep only space.

		for (int i = 0; i < re.num_spaces; i++) {
			capacity_config *space = &re.spaces[i];
			if ((space->type != RESOURCE_SHEEP)
			    || (space->capacity != 0))
			{
				continue;
			}
			int dog = dogs_per_meadow;
			if (plus_ones > 0) {
				dog += 1;
				plus_ones--;
			}
			if (dog == 0) continue;
			// Otherwise, add one, and place the dogs.
			space->capacity = dog + 1;
			space->dog = dog;
		}
	} else {
		// If there are no empty Meadows, the Dogs may be placed on
		// 1) a Meadow with a Stable (replacing cap 1)
		// 2) Small pasture (replacing cap 2 or 4)
		// 3) Large pasture (replacing cap 4, 8 or 16)

		// In each case, the number of capacities remain the same.
		// which means that it is only possible to replace
		// one or more capacities with Sheep-only capacities.

		// If the player does not have unplaced Sheep left after
		// using the specifics, there is no point in placing Dog
		// on any general holding space.

		// If the player does have Sheep left...
		// The rearranging algorithm may replace a general capacity
		// to a Sheep-only version.
	}

	if (re.num_spaces == 0) {
		// Cannot happen, since there is the Entry-level Dwelling.
	}

	// Reorder capacity configurations so that the non-general
	// are at the beginning
	for (int i = 0; i < re.num_spaces-1; i++) {
		for (int j = i; j < re.num_spaces; j++) {
			capacity_config *ic = &re.spaces[i];
			capacity_config *jc = &re.spaces[j];
			if ((ic->type == RESOURCE_NONE)
			    && (jc->type != RESOURCE_NONE))
			{
				// Swap configurations
				capacity_config temp;
				temp = *ic;
				*ic = *jc;
				*jc = temp;
			}
		}
	}

	// The animal vector, "anivector", indicating the number
	// of each animal type left for accommodation.
	int animals[5] = {
	    player->sheep,
	    player->donkey,
	    player->boar,
	    player->cattle,
	    player->dog
	};

	int space_num = 0;
	for (space_num = 0; space_num < re.num_spaces; space_num++) {
		capacity_config *space = &re.spaces[space_num];
		if (space->type == RESOURCE_NONE) break;
	}

	fill_capacities(
	    player,
	    animals,
	    &re.spaces[0],
	    space_num
	);

	// Okay what now...??
	// Let
	//    N number of different animals.
	//    K number of places where the animals can be placed
	//    C[i] the capacity of the ith place
	// Example:
	// If K is 7 for example.. then
	//     1   2   3   4   5   6   7
	// The algorithm can be thought as placing



	// 1. Try all 1-cap combinations
	// 2. Try all 2-cap combinations
	//	.. if all animal 1 can be fit to a combination,
	//	   recurse the algorithm for the next animal.
	// .. If every N-cap combination can hold all animals,
	//    do not continue to try (N+1)-cap combinations,
	//    because one of the plcaes will always be empty and unused.
	//

	// Quicktest
	int types_left = (animals[0] > 0) + (animals[1] > 0)
	    + (animals[2] > 0) + (animals[3] > 0);
	int spaces_left = re.num_spaces - space_num;

	if (spaces_left < types_left) {
		// Less storages than animal types.
		// Impossible to rearrange.
		return 0;
	}

	int success = rearrange(
	    animals, 0,
	    &re.spaces[space_num],
	    re.num_spaces - space_num
	);

	if (!success) return 0;

	// Do placing for the part space_num .. num_spaces
	fill_capacities(
	    player,
	    animals,
	    &re.spaces[space_num],
	    re.num_spaces - space_num
	);

	*rearrangement = re;
	return 1;
}

int caverna_rearrange_animals(player_state *player) {
	animal_rearrangement rearrangement;
	int success = find_animal_rearrangement(player, &rearrangement);
	if (!success) return 0;
	rearrange_animals(player, &rearrangement);
	return 1;
}


int caverna_finish_turn(game_state *gs) {
	if (gs->phase != PHASE_FINISH_TURN) {
		error(gs, E_RULES,
		    "Cannot finish turn in phase %d",
		    gs->phase
		);
		return 0;
	}

	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Verify that there are no excess animals.
	if (num_unplaced_animals(player) > 0) {
		error(gs, E_RULES,
		    "Cannot finish turn: there are unplaced animals"
		);
		return 0;
	}

	int success = verify_animal_placements(gs, player);
	if (!success) return 0;


	// Determine the next player
	int player_num = gs->cur_player;
	int next_player = -1;
	for (int i = 0; i < gs->num_players; i++) {
		player_num++;
		if (player_num == gs->num_players) player_num = 0;
		const player_state *player = &gs->players[player_num];
		if (player->workers < player->dwarfs) {
			// This player has dwarfs left.
			next_player = player_num;
			break;
		}
	}

	set_current_player(gs, next_player);
	if (next_player != -1) {
		set_phase(gs, PHASE_WORK);
	} else {
		set_phase(gs, PHASE_FINISH_ROUND);
	}
	return 1;
}

int caverna_end_of_round(const game_state *gs) {
	return gs->phase == PHASE_FINISH_ROUND;
}

int caverna_finish_round(game_state *gs) {
	if (gs->phase != PHASE_FINISH_ROUND) {
		error(gs, E_RULES,
		    "Cannot finish round in phase %d",
		    gs->phase
		);
		return 0;
	}

	// Return workes home.

	// Pick a savepoint
	command_record *savepoint = gs->log.tail;

	for (int i = 0; i < gs->num_players; i++) {
		player_state *player = &gs->players[i];
		int success = 1;
		for (int j = 0; j < player->dwarfs; j++) {
			success = retrieve_worker(player, j, gs);
			if (!success) break;
		}
		if (success) {
			incorporate_player_commands(gs, player);
		} else {
			rollback_player_commands(gs, player);
			rollback_to(gs, savepoint);
			return 0;
		}
	}

	// If there is a rune, turn it over.
	// Then there may be Harvest, Harvest Event,
	// No harvest, or pay 1 Food per Dwarf.
	// In Solo game there is no Harvest Events,
	// but Harvest at the end of every round
	// after the round 5

	// Both in Solo game and in Multiplayer game,
	// the first 5 rounds end exactly the same
	int harvest = HARVEST_NONE;
	if (gs->cur_round <= 5) {
		// End of round: what happens
		// 1: No harvest
		// 2: No harvest
		// 3: Harvest
		// 4: Pay 1 Food per Dwarf
		// 5: Harvest
		switch(gs->cur_round) {
		case 1:
		case 2:
			harvest = HARVEST_NONE;
			break;
		case 3:
			harvest = HARVEST_NORMAL;
			break;
		case 4:
			harvest = HARVEST_NONE_FEED_1FOOD;
			break;
		case 5:
			harvest = HARVEST_NORMAL;
			break;
		}
	} else if (gs->num_players == 1) {
		// 6-12: Harvest
		harvest = HARVEST_NORMAL;
	} else {
		// 6-12: Rune
	}

	// Record harvest information
	set_harvest(gs, harvest);

	if (harvest == HARVEST_NONE) {
		// No harvest. Begin next round.
		// 1) grow children into adults.
		// 2) determine next round or end-game

		// beginning_of_round()
		// begin_round()
		set_phase(gs, PHASE_GROW);
	} else if (harvest == HARVEST_NORMAL) {
		// Normal harvest
		// harvest(), feed(), breed()
		set_phase(gs, PHASE_HARVEST);
	} else if (harvest == HARVEST_NONE_FEED_1FOOD) {
		// No harvest, but must pay 1 Food per Dwarf
		set_phase(gs, PHASE_FEED);
		set_current_player(gs, 0); // TODO: account for starting player token.
	} else if (harvest == HARVEST_WITH_PHASE_SKIP) {
		// Harvest, but each player must skip
		// either field phase or breeding phase.
		set_phase(gs, PHASE_HARVEST);
	}

	return 1;
}

int caverna_grow(game_state *gs) {
	if (gs->phase != PHASE_GROW) {
		error(gs, E_RULES,
		    "Cannot grow up in phase %d",
		    gs->phase
		);
		return 0;
	}

	// Pick a savepoint
	command_record *savepoint = gs->log.tail;

	for (int i = 0; i < gs->num_players; i++) {
		player_state *player = &gs->players[i];
		int success = reorder_and_grow_up(gs, player);
		if (success) {
			incorporate_player_commands(gs, player);
		} else {
			rollback_player_commands(gs, player);
			rollback_to(gs, savepoint);
			return 0;
		}
	}

	// Determine whether there will be a new round or
	// whether the game has ended
	if (gs->cur_round == 12) {
		set_phase(gs, PHASE_FINISH_GAME);
	} else {
		set_phase(gs, PHASE_BEGIN_ROUND);
	}

	return 1;
}

int caverna_end_of_game(const game_state *gs) {
	return gs->phase == PHASE_FINISH_GAME;
}

int caverna_finish_game(game_state *gs) {
	if (gs->phase != PHASE_FINISH_GAME) {
		error(gs, E_RULES,
		    "Cannot finish game in phase %d",
		    gs->phase
		);
		return 0;
	}
	set_phase(gs, PHASE_GAME_OVER);
	return 1;
}

/** TODO: params: player, type, and the function itself discovers the effect. */
static void trigger_begin_round_effect(
    player_state *player,
    tile_state *tile
) {
	int rounds = tile->rounds;

	switch(tile->type) {
	case TILE_WOOD_SUPPLIER:
		if (rounds > 7) return;
		gain_resource(player, RESOURCE_WOOD, 1);
		break;
	case TILE_STONE_SUPPLIER:
		if (rounds > 5) return;
		gain_resource(player, RESOURCE_STONE, 1);
		break;
	case TILE_RUBY_SUPPLIER:
		if (rounds > 4) return;
		gain_resource(player, RESOURCE_RUBY, 1);
		break;
	case TILE_MINER:
		// Unlimited
		gain_resource(
		    player, RESOURCE_ORE,
		    num_donkeys_in_ore_mines(player->board)
		);
		break;
	default:
		// No effect
		break;
	}
}

static void trigger_begin_round_effects(player_state *player) {
	tile_state *board = player->board;
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			int z;
			tile_state *top = get_top_tile(board, x, y, &z);
			trigger_begin_round_effect(player, top);
		}
	}
}

int caverna_beginning_of_round(const game_state *gs) {
	return gs->phase == PHASE_BEGIN_ROUND;
}

static void next_round(game_state *gs) {
	// Log action and execute
	log_command1(&gs->log, CMD_NEXT_ROUND, 0);

	// Increase current round.
	// The current round is set to 0 when the game is started.
	// Thus, this is actually 1-based number, ie. the first
	// round is cur_round=1.
	gs->cur_round++;

	// In Solo and 2-player games, the round 9 is skipped.
	if ((gs->num_players <= 2) && (gs->cur_round == 9)) {
		gs->cur_round++;
		gs->num_actions++;
	}

	// Turn over the next Action space card.
	gs->num_actions++;

	// If the revealed action is Family life,
	// replace the action "Wish for children" with the Urgent variant.
	if (gs->actions[gs->num_actions-1].type == ACTION_FAMILY_LIFE) {
		action_space *aspace = get_action_space(
		    gs, ACTION_WISH_FOR_CHILDREN);
		aspace->type = ACTION_URGENT_WISH_FOR_CHILDREN;
	}

	// Advance the round count on each tile on each player board
	int xmin, ymin, xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);
	for (int i = 0; i < gs->num_players; i++) {
		player_state *player = &gs->players[i];

		for (int y = ymin; y <= ymax; y++) {
			for (int x = xmin; x <= xmax; x++) {
				int z;
				tile_state *top = get_top_tile(
				    player->board, x, y, &z);
				top->rounds++;
			}
		}
	}
}

int caverna_begin_round(game_state *gs) {
	if (gs->phase != PHASE_BEGIN_ROUND) {
		error(gs, E_RULES,
		    "Cannot begin a new round in phase %d",
		    gs->phase
		);
		return 0;
	}

	// Increase current round number, and skip round 9,
	// if playing Solo or 2-player game.
	next_round(gs);

	// Replenish all accumulating spaces
	replenish_all_actions(gs);

	// Trigger all "at the beginning of each round" effects
	for (int i = 0; i < gs->num_players; i++) {
		player_state *player = &gs->players[i];
		trigger_begin_round_effects(player);
		incorporate_player_commands(gs, player);
	}

	// Start work phase with the starting player (TODO).
	set_current_player(gs, 0);

	set_phase(gs, PHASE_WORK);
	return 1;
}

static int do_harvesting(player_state *player) {
	// get forest limits
	int xmin, ymin, xmax, ymax;
	get_forest_limits(player, &xmin, &ymin, &xmax, &ymax);
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			const tile_state *top
			    = get_top_tile(player->board, x, y, &z);
			if (top->type != TILE_FIELD) continue;
			if (top->grain > 0) {
				take_resource_from_tile(
				    player,
				    x, y, z,
				    RESOURCE_GRAIN, 1
				);
			}
			if (top->vegetable > 0) {
				take_resource_from_tile(
				    player,
				    x, y, z,
				    RESOURCE_VEGETABLE, 1
				);
			}
		} // for x
	} // for y
	return 1;
}

/** Field phase: Take top grain/vegetable from each field. */
int caverna_harvest(game_state *gs) {
	if (gs->phase != PHASE_HARVEST) {
		error(gs, E_RULES,
		    "Cannot do harvesting in phase %d",
		    gs->phase
		);
		return 0;
	}
	command_record *savepoint = gs->log.tail;
	for (int i = 0; i < gs->num_players; i++) {
		player_state *player = &gs->players[i];
		int success = do_harvesting(player);
		if (success) {
			incorporate_player_commands(gs, player);
		} else {
			rollback_player_commands(gs, player);
			rollback_to(gs, savepoint);
			return 0;
		}
	}
	set_phase(gs, PHASE_FEED);
	set_current_player(gs, 0); // TODO: account for starting player token.
	return 1;
}


/**
 * This does NOT verify that the player has Working cave.
 * It simply performs the resource computations, and logs the action.
 */
static void feed_family(
    player_state *player,
    int food,
    int working_cave_effect
) {
	// Calculate the number of Beggar cards needed,
	// and reduce Food costs accordingly.
	int beggar = 0;
	if (food > player->food) {
		beggar = food - player->food;
		food = player->food;
	}

	// Log command
	log_command5(
	    &player->log,
	    CMD_FEED_FAMILY,
	    food, beggar, working_cave_effect,
	    0, 0
	);

	// Execute
	player->food -= food;
	player->beggar += beggar;

	switch(working_cave_effect) {
	case WORKING_CAVE_FEED_1WOOD:
		player->wood -= 1;
		break;
	case WORKING_CAVE_FEED_1STONE:
		player->stone -= 1;
		break;
	case WORKING_CAVE_FEED_2ORE:
		player->ore -= 2;
		break;
	default:
		// No Working cave utilization
		break;
	}
}

static int compute_feeding_cost(
    const game_state *gs,
    const player_state *player,
    int working_cave_effect
) {
	int has_mining_cave = has_tile(player, TILE_MINING_CAVE);

	int hungry_dwarfs = player->dwarfs;

	// Apply Working cave effect, if any.
	if (working_cave_effect) {
		// Working cave effect applied; one Dwarf less to feed.
		hungry_dwarfs--;
	}

	int cost = 0;

	// Compute feeding costs
	if ((gs->harvest == HARVEST_NORMAL)
	    || (gs->harvest == HARVEST_WITH_PHASE_SKIP))
	{
		cost = (hungry_dwarfs*2) + (player->children*1);
	} else if (gs->harvest == HARVEST_NONE_FEED_1FOOD) {
		cost = (hungry_dwarfs*1) + (player->children*1);
	} else {
		return -1;
	}

	// Apply Mining cave discount
	if (has_mining_cave) {
		cost -= num_donkeys_in_mines(player->board);
		if (cost < 0) cost = 0; // Saturate
	}

	return cost;
}

int caverna_compute_feeding_cost(
    const game_state *gs,
    int working_cave_effect
) {
	const player_state *player = &gs->players[gs->cur_player];

	return compute_feeding_cost(gs, player, working_cave_effect);
}

/**
 * Feeding phase: Each adult dwarf needs 2 food, and each child 1 food.
 * game_state is needed for (i) error logging,
 * and for (ii) knowing the harvest variant
 */
static int do_feeding(
    game_state *gs,
    player_state *player,
    const family_feeding *feeding
) {
	int has_working_cave = has_tile(player, TILE_WORKING_CAVE);
	int has_mining_cave = has_tile(player, TILE_MINING_CAVE);

	int hungry_dwarfs = player->dwarfs;

	// Apply Working cave discount
	if (feeding->working_cave_effect) {
		if (!has_working_cave) {
			error(gs, E_RULES,
			    "Cannot use Working cave effect: "
			    "the player does not have Working cave"
			);
			return 0;
		}
		int type = RESOURCE_NONE;
		int count = 0;
		switch(feeding->working_cave_effect) {
		case WORKING_CAVE_FEED_1WOOD:
			type = RESOURCE_WOOD;
			count = 1;
			break;
		case WORKING_CAVE_FEED_1STONE:
			type = RESOURCE_STONE;
			count = 1;
			break;
		case WORKING_CAVE_FEED_2ORE:
			type = RESOURCE_ORE;
			count = 2;
			break;
		default:
			error(gs, E_INTERNAL,
			    "Unhandled Working cave effect: %d",
			    feeding->working_cave_effect
			);
			return 0;
		}
		int *counter = get_resource(player, type);
		if (*counter < count) {
			error(gs, E_RULES,
			    "Cannot use Working cave effect: "
			    "%d %s required, but the player has only %d",
			    count, get_resource_name(type), *counter
			);
			return 0;
		}

		// Working cave effect applied; one Dwarf less to feed.
		hungry_dwarfs--;
	}

	int cost = 0;

	// Compute feeding costs
	if ((gs->harvest == HARVEST_NORMAL)
	    || (gs->harvest == HARVEST_WITH_PHASE_SKIP))
	{
		cost = (hungry_dwarfs*2) + (player->children*1);
	} else if (gs->harvest == HARVEST_NONE_FEED_1FOOD) {
		cost = (hungry_dwarfs*1) + (player->children*1);
	} else {
		error(gs, E_INTERNAL,
		    "Unhandled harvest type: %d",
		    gs->harvest
		);
		return 0;
	}

	// Apply Mining cave discount
	if (has_mining_cave) {
		cost -= num_donkeys_in_mines(player->board);
		if (cost < 0) cost = 0; // Saturate
	}

	if (cost < feeding->food) {
		error(gs, E_RULES,
		    "Feeding too much; only %d Food required, "
		    "but the player is paying %d",
		    cost, feeding->food
		);
		return 0;
	}

	feed_family(player, cost, feeding->working_cave_effect);

	return 1;
}

int caverna_feed(game_state *gs, const family_feeding *feeding) {
	if (gs->phase != PHASE_FEED) {
		error(gs, E_RULES,
		    "Cannot do feeding in phase %d",
		    gs->phase
		);
		return 0;
	}

	command_record *savepoint = gs->log.tail;
	for (int i = 0; i < gs->num_players; i++) {
		player_state *player = &gs->players[i];
		int success = do_feeding(gs, player, feeding);
		if (success) {
			incorporate_player_commands(gs, player);
		} else {
			rollback_player_commands(gs, player);
			rollback_to(gs, savepoint);
			return 0;
		}
	}

	gs->cur_player++;
	if (gs->cur_player < gs->num_players) {
		// Feeding phase continues;
		set_current_player(gs, gs->cur_player);
	} else {
		// Feeding phase has ended.
		set_current_player(gs, -1);
		if (gs->harvest == HARVEST_NONE_FEED_1FOOD) {
			// There is no breeding
			set_phase(gs, PHASE_GROW);
		} else {
			set_phase(gs, PHASE_BREED);
			set_breed(gs, BREED_NORMAL);
			// TODO: account for starting player token.
			set_current_player(gs, 0);
		}
	}

	return 1;
}

/** Breed a given animal type for the current player. */
int caverna_breed(game_state *gs, int type) {
	if (gs->phase != PHASE_BREED) {
		error(gs, E_RULES,
		    "Cannot do breeding in phase %d",
		    gs->phase
		);
		return 0;
	}

	player_state *player = &gs->players[gs->cur_player];

	int *newborn = get_newborn_animal(player, type);
	int *counter = get_animal(player, type);

	if (*newborn > 0) {
		error(gs, E_RULES,
		    "Player has already bred %s",
		    get_resource_name(type)
		);
		return 0;
	}

	if (*counter < 2) {
		error(gs, E_RULES,
		    "Player does not have at least 2 %s needed for breeding",
		    get_resource_name(type)
		);
		return 0;
	}

	// If there is a limit on breeding.
	if ((gs->breed == BREED_UPTO_2_ONCE)
	    || (gs->breed == BREED_UPTO_2_TWICE))
	{
		int newborn_types
		    = (player->newborn_sheep > 0)
		    + (player->newborn_donkey > 0)
		    + (player->newborn_boar > 0)
		    + (player->newborn_cattle > 0);
		if (newborn_types == 2) {
			error(gs, E_RULES,
			    "Player has already bred 2 types of Farm animals"
			);
			return 0;
		}
	}

	// Otherwise log message and breed
	log_command2(
	    &player->log,
	    CMD_BREED_ANIMAL,
	    type, 0
	);

	*newborn = 1;
	*counter += 1;

	return 1;
}

/** Unbreed a given animal type for the current player. */
int caverna_unbreed(game_state *gs, int type) {
	if (gs->phase != PHASE_BREED) {
		error(gs, E_RULES,
		    "Cannot do unbreeding in phase %d",
		    gs->phase
		);
		return 0;
	}

	player_state *player = &gs->players[gs->cur_player];

	int *newborn = get_newborn_animal(player, type);
	int *counter = get_animal(player, type);

	if (*newborn == 0) {
		error(gs, E_RULES,
		    "Player has not bred %s",
		    get_resource_name(type)
		);
		return 0;
	}

	int *placed = get_placed_animal(player, type);
	int unplaced = *counter - *placed;

	if (unplaced < 1) {
		unplace_animals(player, type, 1);
	}

	// Otherwise log message and breed
	log_command2(
	    &player->log,
	    CMD_BREED_ANIMAL,
	    type, 0
	);

	*newborn = 0;
	*counter -= 1;

	return 1;

}

int caverna_commit_breeding(game_state *gs) {
	if (gs->phase != PHASE_BREED) {
		error(gs, E_RULES,
		    "Cannot commit breeding in phase %d",
		    gs->phase
		);
		return 0;
	}


	// For convenience
	player_state *player = &gs->players[gs->cur_player];

	// Verify that there are no excess animals.
	if (num_unplaced_animals(player) > 0) {
		error(gs, E_RULES,
		    "Cannot commit breeding: there are unplaced animals"
		);
		return 0;
	}

	// Verify animal placement
	int success = verify_animal_placements(gs, player);
	if (!success) return 0;

	// Trigger newborn effects
	trigger_newborn_effects(player);

	log_command5(
	    &player->log,
	    CMD_GROW_NEWBORNS,
	    player->newborn_sheep,
	    player->newborn_donkey,
	    player->newborn_boar,
	    player->newborn_cattle,
	    0
	);

	player->newborn_sheep = 0;
	player->newborn_donkey = 0;
	player->newborn_boar = 0;
	player->newborn_cattle = 0;

	// NOTE! The player commands MUST BE committed
	// prior to setting phase/breed of the game state.
	incorporate_player_commands(gs, player);

	// Determine the next phase and/or player in order
	if (gs->breed == BREED_UPTO_2_TWICE) {
		// The current player may breed again
		set_breed(gs, BREED_UPTO_2_ONCE);
	} else if (gs->breed == BREED_UPTO_2_ONCE) {
		// The control return splayer normal turn returns
		set_breed(gs, BREED_NONE);
		set_phase(gs, PHASE_FINISH_TURN);
	} else if (gs->breed == BREED_NORMAL) {
		// TODO: account for the starting player token
		int next_player = gs->cur_player + 1;
		if (next_player == gs->num_players) next_player = -1;

		set_current_player(gs, next_player);
		if (next_player == -1) {
			set_breed(gs, BREED_NONE);
			set_phase(gs, PHASE_GROW);
		}
	} else {
		fprintf(stderr,
		    "(caverna_commit_breeding) unknown breed variant: %d\n",
		    gs->breed
		);
		exit(1);
	}

	return 1;
}

int caverna_get_score(score_state *score, const player_state *player) {

	// Pre-compute the number of Farm animals
	int farm_animals
	    = player->sheep
	    + player->donkey
	    + player->boar
	    + player->cattle;

	// Pre-compute the number of missing Farm animal types.
	int missing_farm_animal_types
	    = (player->sheep == 0)
	    + (player->donkey == 0)
	    + (player->boar == 0)
	    + (player->cattle == 0);

	// Precompute the number of armed dwarfs
	int armed_dwarfs = 0;
	for (int i = 0; i < player->dwarfs; i++) {
		if (player->weapons[i] > 0) armed_dwarfs++;
	}

	int xmin, ymin;
	int xmax, ymax;
	get_board_limits(&xmin, &ymin, &xmax, &ymax);

	int unused_spaces = 0;
	int small_pastures = 0;
	int large_pastures = 0;
	int ore_mines = 0;
	int ruby_mines = 0;
	int furnishing_vp = 0;

	// Total count (both Personal supply and Home board)
	int grain = player->grain;
	int vegetable = player->vegetable;

	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			int z;
			const tile_state *top
			    = get_top_tile(player->board, x, y, &z);

			int is_unused = ((top->type == TILE_FOREST)
			    && (top->stable == 0))
			    || (top->type == TILE_MOUNTAIN);

			grain += top->grain;
			vegetable += top->vegetable;

			// Office room does not affect
			// to the unused spaces.
			if ((x > xmin) && (x < xmax)
			    && (y > ymin) && (y < ymax)
			    && (is_unused))
			{
				unused_spaces++;
			}

			if (top->type == TILE_SMALL_PASTURE) {
				small_pastures++;
			}
			else if (top->type == TILE_LARGE_PASTURE) {
				if ((top->dir == DIRECTION_RIGHT)
				    || (top->dir == DIRECTION_DOWN))
				{
					large_pastures++;
				}
			}
			else if (top->type == TILE_ORE_MINE) {
				ore_mines++;
			}
			else if (top->type == TILE_RUBY_MINE) {
				ruby_mines++;
			}

			const furnishing_config *fc
			    = get_furnishing_config(top->type);
			if (fc != NULL) {
				furnishing_vp += fc->vp;
			}
		}
	}

	// 1 VP per Farm animal and Dog.
	score->animals = farm_animals + player->dog;

	// 1 VP per Ruby
	score->ruby = player->ruby;

	// 1 VP per Dwarf
	score->dwarfs = player->dwarfs;

	// 1 VP per Gold
	score->gold = player->gold;

	// -2 VP per missing type of Farm animal.
	score->missing_farm_animals = missing_farm_animal_types*2;

	// 1/2 VP per Grain (rounded up).
	score->grain = (grain+1)/2;

	// 1 VP per Vegetable
	score->vegetable = vegetable;

	// -1 per Unused space
	score->unused_spaces = unused_spaces;

	// -3 per Begging marker
	score->begging = player->beggar*3;

	// Furnishing tiles
	score->furnishings = furnishing_vp;

	// +2 VP per Small pasture
	// +4 VP per Large pasture (or +2 VP per tile in Large pasture).
	score->pastures = (small_pastures*2) + (large_pastures*4);
	// +3 VP per Ore mine
	// +4 VP per Ruby mine
	score->mines = (ore_mines*3) + (ruby_mines*4);

	int bonus = 0;
	int acquittance = 0;

	// Special scoring tiles
	if (has_tile(player, TILE_WEAVING_PARLOR)) {
		// 1 VP per 2 Sheep (rounded down)
		bonus += player->sheep / 2;
	}
	if (has_tile(player, TILE_MILKING_PARLOR)) {
		// 1 VP per 1 Cattle
		bonus += player->cattle;
	}
	if (has_tile(player, TILE_STATE_PARLOR)) {
		// 4 VP for each adjacent Dwelling.
		int x, y, z;
		get_tile_coordinates(player,
		    TILE_STATE_PARLOR, &x, &y, &z);
		bonus += 4*num_adjacent_dwellings(player->board, x, y);
	}
	if (has_tile(player, TILE_STONE_STORAGE)) {
		// 1 VP per Stone
		bonus += player->stone;
	}
	if (has_tile(player, TILE_ORE_STORAGE)) {
		// 1 VP per 2 Ore (rounded down)
		bonus += player->ore / 2;
	}
	if (has_tile(player, TILE_MAIN_STORAGE)) {
		// 2 VP per Scoring tile (TODO: array of scoring tiles)
		bonus += 2*num_scoring_tiles(player->board);
	}
	if (has_tile(player, TILE_WEAPON_STORAGE)) {
		// 3 VP per armed Dwarf
		bonus += armed_dwarfs*3;
	}
	if (has_tile(player, TILE_SUPPLIES_STORAGE)) {
		// 8 VP if all Dwarfs in play have a Weapon
		if (armed_dwarfs == player->dwarfs) {
			bonus += 8;
		}
	}
	if (has_tile(player, TILE_BROOM_CHAMBER)) {
		// 5 VP for 5 Dwarfs
		// 10 VP for 6 Dwarfs
		if (player->dwarfs == 5) {
			bonus += 5;
		} else if (player->dwarfs == 6) {
			bonus += 10;
		}
	}
	if (has_tile(player, TILE_TREASURE_CHAMBER)) {
		// 1 VP per Ruby
		bonus += player->ruby;
	}
	if (has_tile(player, TILE_FOOD_CHAMBER)) {
		// 2 VP per 1 Vegetable + 1 Grain
		int pairs = vegetable;
		if (pairs > grain) {
			pairs = grain;
		}
		bonus += 2*pairs;
	}
	if (has_tile(player, TILE_PRAYER_CHAMBER)) {
		// 8 VP if no Dwarf has a Weapon when scoring the tile.
		if (armed_dwarfs == 0) {
			bonus += 8;
		}
	}
	if (has_tile(player,  TILE_FODDER_CHAMBER)) {
		// 1 VP per 3 Farm animals (rounded down)
		bonus += farm_animals / 3;
	}
	if (has_tile(player, TILE_WRITING_CHAMBER)) {
		// Prevents up to 7 negative points.
		acquittance = 7;
	}

	score->bonus = bonus;
	score->acquittance = acquittance;

	score->total
	    = score->animals
	    + score->ruby
	    + score->dwarfs
	    + score->gold
	    + score->grain
	    + score->vegetable
	    + score->pastures
	    + score->furnishings
	    + score->bonus;

	score->penalty
	    = score->missing_farm_animals
	    + score->unused_spaces
	    + score->begging
	    - score->acquittance;
	if (score->penalty < 0) score->penalty = 0;

	return score->total - score->penalty;
}

int caverna_finished(const game_state *gs) {
	return gs->phase == PHASE_GAME_OVER;
}

const char *caverna_strerror(const game_state *gs) {
	return gs->strerror;
}

int caverna_errno(const game_state *gs) {
	return gs->errno;
}


