#ifndef CAVERNA_H
#define CAVERNA_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Maximum error message length
 */
#define MAX_STRERROR_LENGTH 512

/*
 * Error codes
 */

#define E_OK 0
#define E_ORDERS 1
#define E_RULES 2
#define E_INTERNAL 3

/**
 * Maximum number of players
 */
#define MAX_PLAYERS 7

/**
 * Maximum number of action spaces simultaneously in play.
 * TODO: fix the limit
 */
//#define MAX_ACTIONS 32
#define MAX_ACTIONS (32+12)

/**
 * Maximum number of dwarfs a player can have
 */
#define MAX_DWARFS 6

/**
 * Maximum number of different furnishing tiles available.
 */
#define MAX_FURNISHINGS (4*12)

/**
 * Maximum Weapon strength
 */
#define MAX_WEAPON_STRENGTH 14

/*
 * Actions
 */

#define ACTION_NONE 0
// Board 1
#define ACTION_DRIFT_MINING 1
#define ACTION_LOGGING 2
#define ACTION_WOOD_GATHERING 3

#define ACTION_EXCAVATION 4
#define ACTION_SUPPLIES 5
#define ACTION_CLEARING 6

#define ACTION_STARTING_PLAYER 7
#define ACTION_ORE_MINING 8
#define ACTION_SUSTENANCE 9

#define ACTION_RUBY_MINING 10
#define ACTION_HOUSEWORK 11
#define ACTION_SLASH_AND_BURN 12

// Action space cards
#define ACTION_BLACKSMITHING 101
#define ACTION_SHEEP_FARMING 102
#define ACTION_ORE_MINE_CONSTRUCTION 103

#define ACTION_WISH_FOR_CHILDREN 104
#define ACTION_URGENT_WISH_FOR_CHILDREN 204
#define ACTION_DONKEY_FARMING 105
#define ACTION_RUBY_MINE_CONSTRUCTION 106

#define ACTION_ORE_DELIVERY 107
#define ACTION_FAMILY_LIFE 108
//#define ACTION_EXPLORATION ?

#define ACTION_ORE_TRADING 110
#define ACTION_ADVENTURE 111
#define ACTION_RUBY_DELIVERY 112

/**
 * Game states (somewhat similar to phases)
 */

/** Invalid phase. */
#define PHASE_NONE 0
/** At the beginning of each round, turn over the top Action space card. */
/** Replenish accumulating action spaces. */
#define PHASE_BEGIN_ROUND 1
/** Take turns to place 1 Dwarf per turn on an Action space. */
#define PHASE_WORK 2
/** After placing 1 Dwarf on an Action space, the turn must be finished. */
#define PHASE_FINISH_TURN 3
/** Return Dwarfs to their Dwellings. */
#define PHASE_FINISH_ROUND 4
/** Field sub-phase of the harvest, which is the actual harvest. */
#define PHASE_HARVEST 5
/** Harvest's Feeding sub-phase. */
#define PHASE_FEED 6
/** Harvest's Breeding sub-phase. */
#define PHASE_BREED 7
/** At the end of each round, child Dwarfs become adults. */
#define PHASE_GROW 8
/** Game finished. Last conversion can still be made before scoring. */
#define PHASE_FINISH_GAME 9
/** Game has been scored. */
#define PHASE_GAME_OVER 10

/**
 * Harvest variant
 */
#define HARVEST_NONE 0
#define HARVEST_NORMAL 1
#define HARVEST_NONE_FEED_1FOOD 2
#define HARVEST_WITH_PHASE_SKIP 3

/**
 * Breed variant
 */
#define BREED_NONE 0
#define BREED_NORMAL 1
#define BREED_UPTO_2_ONCE 2
#define BREED_UPTO_2_TWICE 3

/*
 * Directions
 */

#define DIRECTION_NONE -1
#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

/*
 The board coordinates
-----------------------

  0  1  2  3 | 4  5  6  7
A ,  ,  ,  , | ,  ,  ,  ,
B ,  O  O  O | X  X  X  ,
C ,  O  O  O | X  X  X  ,
D ,  O  O  O |    X  X  ,
E ,  O  O  O = #  X  X  ,
F ,  ,  ,  , | #  ,  ,  ,

*/

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 6
#define BOARD_DEPTH 4

/*
 * 0. Bottom tile (mountain)   -  Bottom tile (forest)
 * 1. Cavern / Tunnel          -  Meadow/Field
 * 2. Ore mine / Furnishing    -  Pasture
 * 3. Ruby mine                -

 * Max depth is therefore 4 tiles
 */

/**
 * Size of single board level
 */
#define BOARD_LEVEL_SIZE (BOARD_WIDTH*BOARD_HEIGHT)

/**
 * Size of the whole board (all levels)
 */
#define BOARD_SIZE (BOARD_LEVEL_SIZE*BOARD_DEPTH)

/**
 * Board parts
 */
#define BOARD_FOREST 0
#define BOARD_MOUNTAIN 1

/**
 * X-coordinate for the beginning of the mountain
 */
#define BOARD_MOUNTAIN_X 4

/**
 * Entry point to the forest
 */
#define BOARD_FOREST_ENTRY_X 3
#define BOARD_FOREST_ENTRY_Y 4

/**
 * Pseudo-tiles
 */

#define TILE_FOREST -2
#define TILE_MOUNTAIN -1
#define TILE_NONE 0
#define TILE_INITIAL_DWELLING 1
#define TILE_BLOCKED 2

/*
 * Landscape tiles
 */

#define TILE_CAVERN 3
#define TILE_TUNNEL 4
#define TILE_MEADOW 5
#define TILE_FIELD 6
#define TILE_DEEP_TUNNEL 7
#define TILE_ORE_MINE 8
#define TILE_SMALL_PASTURE 9
#define TILE_LARGE_PASTURE 10
#define TILE_RUBY_MINE 11

/* One possible solution... */
//#define FLAG_DWELLING_TILE 0x00010000

/**
 * Furnishing tiles
 */
#define TILE_DWELLING 101
#define TILE_SIMPLE_DWELLING_1 102
#define TILE_SIMPLE_DWELLING_2 103
#define TILE_MIXED_DWELLING 104
#define TILE_COUPLE_DWELLING 105
#define TILE_ADDITIONAL_DWELLING 106

#define TILE_CUDDLE_ROOM 201
#define TILE_BREAKFAST_ROOM 202
#define TILE_STUBBLE_ROOM 203
#define TILE_WORK_ROOM 204
#define TILE_GUEST_ROOM 205
#define TILE_OFFICE_ROOM 206

#define TILE_CARPENTER 300
#define TILE_STONE_CARVER 301
#define TILE_BLACKSMITH 302
#define TILE_MINER 303
#define TILE_BUILDER 304
#define TILE_TRADER 305

#define TILE_WOOD_SUPPLIER 400
#define TILE_STONE_SUPPLIER 401
#define TILE_RUBY_SUPPLIER 402
#define TILE_DOG_SCHOOL 403
#define TILE_QUARRY 404
#define TILE_SEAM 405

#define TILE_SLAUGHTERING_CAVE 500
#define TILE_COOKING_CAVE 501
#define TILE_WORKING_CAVE 502
#define TILE_MINING_CAVE 503
#define TILE_BREEDING_CAVE 504
#define TILE_PEACEFUL_CAVE 505

#define TILE_WEAVING_PARLOR 600
#define TILE_MILKING_PARLOR 601
#define TILE_STATE_PARLOR 602
#define TILE_HUNTING_PARLOR 603
#define TILE_BEER_PARLOR 604
#define TILE_BLACKSMITHING_PARLOR 605

#define TILE_STONE_STORAGE 700
#define TILE_ORE_STORAGE 701
#define TILE_SPARE_PART_STORAGE 702
#define TILE_MAIN_STORAGE 703
#define TILE_WEAPON_STORAGE 704
#define TILE_SUPPLIES_STORAGE 705

#define TILE_BROOM_CHAMBER 800
#define TILE_TREASURE_CHAMBER 801
#define TILE_FOOD_CHAMBER 802
#define TILE_PRAYER_CHAMBER 803
#define TILE_WRITING_CHAMBER 804
#define TILE_FODDER_CHAMBER 805

/*
 * Constants specific to certain tiles.
 */

/** No Builder effect applied. */
#define BUILDER_REPLACE_NONE  0x000
/** Replace 1 Wood with 1 Ore when paying for a Furnishing tile. */
#define BUILDER_REPLACE_WOOD  0x0001
/** Replace 1 Stone with 1 Ore when paying for a Furnishing tile. */
#define BUILDER_REPLACE_STONE 0x0002

/** Feed exactly 1 Dwarf with 1 Wood */
#define WORKING_CAVE_FEED_1WOOD 0x0001
/** Feed exactly 1 Dwarf with 1 Stone */
#define WORKING_CAVE_FEED_1STONE 0x0002
/** Feed exactly 1 Dwarf with 2 Ore */
#define WORKING_CAVE_FEED_2ORE 0x0003
/** Bit mask for Working Cave's feeding options. */
#define WORKING_CAVE_FEED_MASK 0x0003

/*
 * Resources
 */

/**
 * It is important that RESOURCE_NONE is equal to zero, because
 * the furnishing tile prices are arrays, and those arrays are
 * only partially initialized (missing elements are then set to
 * zero by the compiler).
 */
#define RESOURCE_NONE 0

#define RESOURCE_GRAIN 1
#define RESOURCE_VEGETABLE 2
#define RESOURCE_FOOD 3
#define RESOURCE_GOLD 4
#define RESOURCE_STONE 5
#define RESOURCE_WOOD 6
#define RESOURCE_RUBY 7
#define RESOURCE_ORE 8
#define RESOURCE_DOG 9
#define RESOURCE_SHEEP 10
#define RESOURCE_BOAR 11
#define RESOURCE_DONKEY 12
#define RESOURCE_CATTLE 13

/*
 * Expedition loot
 */
#define LOOT_NONE 0
// Level 1
#define LOOT_INCREASE_WEAPONS 1
#define LOOT_WOOD 2
#define LOOT_DOG 3
// Level 2
#define LOOT_GRAIN 4
#define LOOT_SHEEP 5
// Level 3
#define LOOT_STONE 6
#define LOOT_DONKEY 7
// Level 4
#define LOOT_VEGETABLE 8
#define LOOT_2ORE 9
// Level 5
#define LOOT_BOAR 10
// Level 6
#define LOOT_2GOLD 11
// Level 7
#define LOOT_FURNISH 12
// Level 8
#define LOOT_STABLE 13
// Level 9
#define LOOT_TUNNEL 14
#define LOOT_SMALL_PASTURE 15
// Level 10
#define LOOT_CATTLE 16
#define LOOT_LARGE_PASTURE 17
// Level 11
#define LOOT_MEADOW 18
#define LOOT_DWELLING 19
// Level 12
#define LOOT_FIELD 20
#define LOOT_SOW 21
// Level 13
// (Nothing)
// Level 14
#define LOOT_CAVERN 22
#define LOOT_BREED2 23


/*
 * Conversions
 */

#define CONV_NONE 0

// xxx-to-food conversions

#define CONV_SHEEP_TO_FOOD 1
#define CONV_GRAIN_TO_FOOD 2
#define CONV_DONKEY_TO_FOOD 3
#define CONV_BOAR_TO_FOOD 4
#define CONV_VEGETABLE_TO_FOOD  5
#define CONV_RUBY_TO_FOOD 6
#define CONV_CATTLE_TO_FOOD 7
#define CONV_GOLD_TO_FOOD 8

// ruby-to-yyyy conversions
// Cattle requires 1 Ruby + 1 Food

#define CONV_RUBY_TO_DOG 11
#define CONV_RUBY_TO_GRAIN 12
#define CONV_RUBY_TO_VEGETABLE 13
#define CONV_RUBY_TO_SHEEP 14
#define CONV_RUBY_TO_WOOD 15
#define CONV_RUBY_TO_DONKEY 16
#define CONV_RUBY_TO_STONE 17
#define CONV_RUBY_TO_BOAR 18
#define CONV_RUBY_TO_ORE 19
#define CONV_RUBY_TO_CATTLE 20

// ruby-to-tile conversions (aka "non-resource conversions")
// Cavern requires 2 Ruby

#define CONV_RUBY_TO_MEADOW 21
#define CONV_RUBY_TO_FIELD 22
#define CONV_RUBY_TO_TUNNEL 23
#define CONV_RUBY_TO_CAVERN 24

// Furnishing tile conversions

// Ones that provide food
#define CONV_COOKING_CAVE 31
#define CONV_PEACEFUL_CAVE 32
#define CONV_HUNTING_PARLOR 33
#define CONV_BEER_PARLOR_FOOD 35
#define CONV_BLACKSMITHING_PARLOR 36
// Ones that provide non-food resources
#define CONV_TRADER 30
#define CONV_BEER_PARLOR_GOLD 34
#define CONV_SPARE_PART_STORAGE 37


/**
 * Take animal resource from a tile.
 * values = { animal_type, int count, tile_x, tile_y, tile_z }
 */
#define CMD_TAKE_TILE_ANIMAL 2

/**
 * Drop animal resource to a tile.
 * values = { animal_type, int count, tile_x, tile_y, tile_z }
 */
#define CMD_DROP_TILE_ANIMAL 3

/**
 * Take non-animal resource from a tile.
 * values = { resource_type, int count, tile_x, tile_y, tile_z }
 */
#define CMD_TAKE_TILE_RESOURCE 4

/**
 * Drop non-animal resource to a tile.
 * values = { resource_type, int count, tile_x, tile_y, tile_z }
 */
#define CMD_DROP_TILE_RESOURCE 5

/**
 * Take resources from an action space.
 * values = { action, int count, 0, 0, 0 }
 */
#define CMD_TAKE_ACTION_RESOURCE 6

/**
 * Gain resources from an action space or from a furnishing tile.
 * values = { resource_type, int count, 0, 0, 0 }
 */
#define CMD_GAIN_RESOURCE 7

/**
 * Pay resources for a furnishing tile.
 * values = { resource_type, int count, 0, 0, 0 }
 */
#define CMD_PAY_RESOURCE 8

/**
 * Take furnishing tile (set taken_by, player_num is implied)
 * values = { furnishing_type }
 */
#define CMD_TAKE_FURNISHING 9

/**
 * Feed family (eat Food and optionally gain Beggar cards).
 * values = { food, beggar, flags }
 */
#define CMD_FEED_FAMILY 10

/**
 * Add resources to a tile.
 * values = { resource_type, delta, x, y, z}
 */
#define CMD_ADD_TILE_RESOURCE 11

/**
 * Lay a tile on top
 * values = { tile_type, x, y, z, dir }
 */
#define CMD_LAY_TILE 12

/**
 * Refill an action space
 * values = { action_type, int old_value }
 */
#define CMD_RESET_COUNTER 13

/**
 * Refill an action space
 * values = { action_type, delta, had_ruby }
 */
#define CMD_INCREASE_COUNTER 14

/**
 * Send a worker to an action space
 * values = { action_type }
 */
#define CMD_SEND_WORKER 15

/**
 * Retrieve a worker from an action space.
 * values = { dwarf_num, action_type }
 */
#define CMD_RETRIEVE_WORKER 16

/**
 * Set the game phase.
 * values = { phase, old_phase }
 */
#define CMD_SET_PHASE 17

/**
 * Set the current player number.
 * values = { cplayer_num, old_cplayer_num }
 */
#define CMD_SET_CURRENT_PLAYER 18

/**
 * Set harvest
 * values = { harvest, old_harvest }
 */
#define CMD_SET_HARVEST 19

/**
 * Reorder dwarfs
 * values = { new_dwarf1, new_dwarf2, ... }
 */
#define CMD_REORDER_DWARFS 20

/**
 * Grow children into adults
 * valeus = { num_children }
 */
#define CMD_GROW_UP 21

/**
 * Lay a stable on a tile.
 * values = { x, y, z }
 */
#define CMD_LAY_STABLE 22

/**
 * Set a Weapon strength.
 * values = { dwarf_num, strength }
 */
#define CMD_SET_WEAPON 23

/**
 * Increase weapon strength after an expedition
 * values = { dwarf_num }
 */
#define CMD_INCREASE_WEAPON 24

/**
 * Increase all weapons after an expedition
 * values = { delta_dwarf1, ..., delta_dwarf6 }
 */
#define CMD_INCREASE_ALL_WEAPONS 25

/**
 * Increase currend round and the number of action spaces.
 * values = { }
 */
#define CMD_NEXT_ROUND 26

/**
 * Increase the number of children by one.
 * values = { }
 */
#define CMD_GROW_FAMILY 27

/**
 * Ordinary resources conversion operation
 * values = { type, count }
 */
#define CMD_CONVERT_RESOURCES 28

/**
 * Convert Weapons to Food with 1:1 ratio (Peaceful cave)
 * values = { strength_0, strength_1, ..., strength_6 }
 */
#define CMD_CONVERT_WEAPONS_TO_FOOD 29

/**
 * Trigger effect
 * values = { type, count }
 */
#define CMD_TRIGGER_EFFECT 30

/**
 * A player puts a Ruby on an action space
 * values = { action_type }
 */
#define CMD_PUT_RUBY_ON_ACTION 31


/**
 * Breed animal
 * values = { animal_type }
 */
#define CMD_BREED_ANIMAL 32

/**
 * Unbreed animal; revert breeding
 * values = { animal_type }
 */
#define CMD_UNBREED_ANIMAL 33

/**
 * Grow newborns into fully grown ups.
 * Values are the previous newborn values.
 * values = { sheep, donkey, boar, cattle }
 */
#define CMD_GROW_NEWBORNS 34

/**
 * Set breed variant
 * values = { breed, old_breed }
 * values = {}
 */
#define CMD_SET_BREED 35


struct command_record {
	struct command_record *next;
	struct command_record *prev;

	/** Command type. */
	int type;
	/** Number of the affected player, or -1. */
	int player_num;
	/** Parameters depending on the command type. */
	int value[6];
};
typedef struct command_record command_record;

struct command_log {
	command_record *head;
	command_record *tail;
};
typedef struct command_log command_log;


struct action_space {
	/** Action space type. */
	int type;
	/** Resource counter. */
	int counter;
	/** In solo play, a ruby can be spent on an action space. */
	int has_ruby;
	/** Player number who took this action in the current round, or -1. */
	int taken_by;
};
typedef struct action_space action_space;


struct tile_placement {
	int x;
	int y;
	int dir;
};
typedef struct tile_placement tile_placement;

struct crop_placement {
	int x;
	int y;
	/** Either RESOURCE_GRAIN or RESOURCE_VEGETABLE. */
	int type;
};
typedef struct crop_placement crop_placement;


struct loot_selection {
	/** Loot type */
	int type;

	// LOOT_FURNISH
	/** Furnishing tile type */
        int tile_type;

        // LOOT_FURNISH, LOOT_DWELLING
	/** Builder effect, if in play. These affect the costs. */
        int builder_effect;

	// LOOT_FURNISH, LOOT_DWELLING,
	// LOOT_SMALL_PASTURE, LOOT_LARGE_PASTURE, LOOT_STABLE
	// LOOT_CAVERN, LOOT_TUNNEL,
	// LOOT_FIELD, LOOT_MEADOW
	/** Placement for a single-tile or twin-tile placement. */
	tile_placement placement;

	/** Crop placement for sowing action. */
	crop_placement sow[4];

	/** Optionally two Farm animal type selection. */
	// TODO
};
typedef struct loot_selection loot_selection;

struct furnishing_selection {
	/** Furnishing tile type */
	int type;
	/** Placement for the Furnishing tile */
	tile_placement placement;
	/** Builder effect used, if any. */
	int builder_effect;
};
typedef struct furnishing_selection furnishing_selection;


struct action_orders {
	/** Action space type */
	int type;
	/** Take the resources, if any. */
	//int take_resources;
	/** Orders specific to the chosen action space. */
	char orders[];
};
typedef struct action_orders action_orders;

/**
 * Drift mining (not available in Solo).
 *
 * Take all the Stone that has accumulated. [...]
 * Additionally, you may place a Cavern/Tunnel twin-tile on 2 adjacent
 * empty Mountain spaces. [...]. You have to place the twin-tile adjacent
 * to an already occupied Mountain space [...].
 * (Appendix, p. A6)
 *
 * Accumulation:
 * 1-3 players: 1 Stone
 * 4-7 players: 2(1) Stone
 */
struct drift_mining_orders {
	int take_stone;
	int do_mining;

	// If the mining takes place
	tile_placement placement;
};
typedef struct drift_mining_orders drift_mining_orders;

/**
 * Logging.
 *
 * Take all the Wood that has accumulated. [...]
 * Afterwards, you may undertake a Level 1 Expedition
 * if your Dwarf has a Weapon.
 * (Appendix, p. A6)
 *
 * Accumulation:
 * 1-3 players: 3(1) Wood
 * 4-7 players: 3 Wood
 */
struct logging_orders {
	int take_wood;

	// Level 1 Expedition
	int do_looting;
	loot_selection loot[1];
};
typedef struct logging_orders logging_orders;

/**
 * Wood gathering (available only in 1-3 player games).
 *
 * Take all the Wood that has accumulated on this Action space.
 * (Appendix, p. A7)
 *
 * Accumulation:
 * 1-3 players: 1 Wood
 */
struct wood_gathering_orders {
	int take_wood;
};
typedef struct wood_gathering_orders wood_gathering_orders;

/**
 * Excavatíon.
 *
 * Take all the Stone that has accumulated on this Action space. [...]
 * Additionally, you may place a Cavern/Tunnel or a Cavern/Cavern twin-tile
 * on 2 adjacent empty Mountain spaces of your Home board. [...]
 * You have to place the twin-tile adjacent to an already occupied
 * Mountain space [...].
 * (Appendix, p. A6)
 *
 * Accumulation:
 * 1-3 players: 1 Stone
 * 4-7 players: 2(1) Stone
 */
struct excavation_orders {
	int take_stone;
	int do_mining;

	/**
	 * Boolean determining the twin-tile type.
	 * True (nonzero) means Cavern/Cavern (hence the name 'cc'),
	 * and False (zero) means Cavern/Tunnel.
	 */
	int cc;

	/** Twin-tile placement, if the mining takes place. */
	tile_placement placement;
};
typedef struct excavation_orders excavation_orders;

/**
 * Ore mining.
 *
 * Take all the Ore that has accumulated on this Action space. [...]
 * Additionally, you may take 2 Ore from the general supply
 * for each Ore mine you have.
 * (Appendix, p. A6)
 *
 * Accumulation:
 * 1-3 players: 2(1) Ore
 * 4-7 players: 3(2) Ore
 */
struct ore_mining_orders {
	int take_ore;
};
typedef struct ore_mining_orders ore_mining_orders;

/**
 * Sustenance.
 *
 * Take all the goods or Food markers that have accumulated
 * on this Action space. [...]
 * In games with 1-3 players, also take 1 Grain from the general supply.
 * Additionally, you may place a Meadow/Field twin-tile on 2 adjacent
 * Forest spaces of your Home board that are not covered by any tiles.
 * (Appendix, p. A6)
 *
 * Accumulation:
 * 1-3 players: 1 Food
 * 4-7 players: 1 Grain (1 Vegetable)
 */
struct sustenance_orders {
	int take_food;
	int do_clearing;

	/** Twin-tile placement, if the clearing takes place. */
	tile_placement placement;
};
typedef struct sustenance_orders sustenance_orders;

/**
 * Ruby mining.
 *
 * Take all the Rubies that have accumulated on this Action space.
 * Take one more Ruby from the general supply if you have at least one
 * Ruby mine. (In the first two rounds of a 2-player game, no Rubies
 * will be added to this Action space.)
 * (Appendix, p. A6)
 *
 * Accumulation:
 * 1 player: 1 Ruby
 * 2 players: 1 Ruby (except on first two rounds)
 * 3-7 players: 1 Ruby
 */
struct ruby_mining_orders {
	int take_ruby;
};
typedef struct ruby_mining_orders ruby_mining_orders;


/**
 * Housework.
 *
 * Take 1 Dog from the general supply.
 * Additionally or alternatively, take a Furnishing tile, pay its building
 * costs and place it on an empty Cavern in your cave system. You may choose
 * from all Furnishing tiles (including Dwellings). If you cannot place
 * a Furnishingtile on your Home board, you may no take any.
 * (This is an "and/or" Action space; you may carry out the actions
 * in either order. For instance, you might want to take the Dog after
 * building the "Dog school".)
 * (Appendix, p. A6)
 *
 */
struct housework_orders {
	int take_dog;
	int do_furnish;
	int tile_type;
	tile_placement placement;
	// Flags for the Builder, if in play. These affect the costs.
	int builder_flags;
};
typedef struct housework_orders housework_orders;

/**
 * Slash and burn.
 *
 * Place a Meadow/Field twin-tile on 2 adjacent Forest spaces of your
 * Home board that are not covered by any tiles.
 * Afterwards, you may carry out a Sow action to sow up to 2 new Grain
 * and/or 2 new Vegetable fields (as usual).
 * (Appendix, p. A6)
 */
struct slash_and_burn_orders {
	int do_clearing;
	/** Twin-tile placement, if the clearing takes place. */
	tile_placement placement;

	// May sow up to 2 Vegetables and 2 Grains.
	crop_placement sow[4];
};
typedef struct slash_and_burn_orders slash_and_burn_orders;


struct blacksmithing_orders {
	int do_forging;
	int weapon; // Weapon strength to forge

	// Level 3 Expedition
	int do_looting;
	loot_selection loot[3];
};
typedef struct blacksmithing_orders blacksmithing_orders;

struct animal_farming_orders {
	/** Fence a Small pasture, cost 2 Wood. */
	int build_small;
	/** Small pasture placement. */
	tile_placement small_placement;

	/** Fence a Large pasture (twin-tile), cost 4 Wood. */
	int build_large;
	/** Large pasture placement. */
	tile_placement large_placement;

	/** Build a Stable, cost 1 Stone. */
	int build_stable;
	tile_placement stable_placement;

	/** Take the accumulating Sheep. */
	int take_animals;
};
typedef struct animal_farming_orders sheep_farming_orders;
typedef struct animal_farming_orders donkey_farming_orders;

struct ore_mine_construction_orders {
	int do_construction;
	tile_placement placement;

	// Level 2 Expedition
	int do_looting;
	loot_selection loot[2];
};
typedef struct ore_mine_construction_orders ore_mine_construction_orders;

/**
 * In Urgent wish for children there is xor(furnish_dwelling, take_gold),
 * and the Furnish a Dwelling action may be followed with family growth.
 * In Wish for children, there is xor(furnish_dwelling, do_family_growth).
 */
struct wish_for_children_orders {
	/** Parameters for furnishing a Dwelling. */
	int furnish_dwelling;
	int type;
	tile_placement placement;
	int builder_effect;

	/** Grow family. */
	int do_family_growth;

	/** Gain 3 Gold, only with Urgent wish for children. */
	int take_gold;
};
typedef struct wish_for_children_orders wish_for_children_orders;

/**
 * This is an "either...or" action space.
 */
struct ruby_mine_construction_orders {
	// On ordinary Tunnel tile.
	int do_construction1;
	tile_placement placement1;

	// On Deep Tunnel tile.
	int do_construction2;
	tile_placement placement2;
};
typedef struct ruby_mine_construction_orders ruby_mine_construction_orders;

struct ore_delivery_orders {
	int take_stone_and_ore;
};
typedef struct ore_delivery_orders ore_delivery_orders;

struct family_life_orders {
	int do_family_growth;
	// May sow up to 2 Vegetables and 2 Grains.
	crop_placement sow[4];
};
typedef struct family_life_orders family_life_orders;

struct ore_trading_orders {
	// How many times the resource conversion is performed, 1-3.
	int count;
};
typedef struct ore_trading_orders ore_trading_orders;

struct adventure_orders {
	int do_forging;
	int weapon; // Weapon strength to forge

	int do_looting;
	loot_selection loot1[1];
	loot_selection loot2[1];
};
typedef struct adventure_orders adventure_orders;

struct ruby_delivery_orders {
	int take_ruby;
};
typedef struct ruby_delivery_orders ruby_delivery_orders;


/**
 * This is used to control Feeding sub-phase of the Harvest.
 */
struct family_feeding {
	/** Number of Food to eat. */
	int food;

	/** Working cave effect, if any. */
	int working_cave_effect;
};
typedef struct family_feeding family_feeding;

struct tile_state {
	/** Tile type. */
	int type;

	/**
	 * Direction in which the other tile
	 * of a twin-tile is located at.
	 */
	int dir;

	/** How many rounds the tile has been in play. */
	int rounds;

	/** Number of stables in the tile. */
	int stable;
	/** Number of dogs in the tile. */
	int dog;
	/** Number of sheeps in the tile. */
	int sheep;
	/** Number of donkeys in the tile. */
	int donkey;
	/** Number of boars in the tile. */
	int boar;
	/** Number of cattles in the tile. */
	int cattle;

	/** Number of grains in the tile. */
	int grain;
	/** Number of vegetables in the tile. */
	int vegetable;

	/** Tile reward, if any in format (type, qty). */
	int reward[2];
};
typedef struct tile_state tile_state;

struct furnishing_state {
	/** Furnishing type. */
	int type;
	/** The player who bought the tile, or -1 if none. */
	int taken_by;
};
typedef struct furnishing_state furnishing_state;

struct animals_state {
	/** Number of Dogs. */
	int dog;
	/** Number of Sheeps. */
	int sheep;
	/** Number of Donkeys. */
	int donkey;
	/** Number of Boars. */
	int boar;
	/** Number of Cattles. */
	int cattle;
};
typedef struct animals_state animals_state;


struct player_state {
	/** Home board. */
	tile_state board[BOARD_SIZE];
	//int depth[BOARD_SIZE];

	/** Command log for actions taken during the turn. */
	command_log log;

	/** Number of (adult) dwarfs in the family. */
	int dwarfs;
	/** Number of children in the family. */
	int children;

	/** Number of (adult) dwarfs which have been employed. */
	int workers;

	/** The weapon strength each Dwarf has, or zero. */
	int weapons[MAX_DWARFS];
	/** The action space in which each dwarf is employed, if any. */
	int locations[MAX_DWARFS];

	/*
	 * Personal supply
	 */

	/** Number of begging markers */
	int beggar;

	/** Number of stables. */
	int stable;

	/** Number of grains in personal supply. */
	int grain;
	/** Number of vegetables in personal supply. */
	int vegetable;
	/** Number of food in personal supply. */
	int food;
	/** Number of gold pieces in personal supply. */
	int gold;
	/** Number of stone in personal supply. */
	int stone;
	/** Number of wood in personal supply. */
	int wood;
	/** Number of rubies in personal supply. */
	int ruby;
	/** Number of ore in personal supply. */
	int ore;

	/*
	 * Animal summary (accommodated plus gained ones)
	 * Animals that are gained during the Work phase may be
	 * converted into Food immediately.
	 */

	/** Total number of animals both on and off the Home board. */
	//animal_state animals;

	/** Number of accommodated animals. */
	//animal_state accommodated;

	int dog;
	int sheep;
	int donkey;
	int boar;
	int cattle;

	int placed_dog;
	int placed_sheep;
	int placed_donkey;
	int placed_boar;
	int placed_cattle;

	/** Whether the player has a newborn in his/her animal count. */
	//int newborn_dog;
	int newborn_sheep;
	int newborn_donkey;
	int newborn_boar;
	int newborn_cattle;

};
typedef struct player_state player_state;


struct game_state {

	/** The current round number. */
	int cur_round;

	/** Current phase. */
	int phase;

	/** Whether there is a harvest and what kind of. */
	int harvest;

	/** Which kind of breeding event. */
	int breed;

	/** Current player number. */
	int cur_player;

	/** Number of players in the game. */
	int num_players;

	/** Individual player states. */
	player_state players[MAX_PLAYERS];

	/** Number of action spaces available. */
	int num_actions;

	/** Action spaces */
	action_space actions[MAX_ACTIONS];

	/** Number of furnishing tiles. */
	int num_furnishings;

	/** Supply board containing the furnishing tiles. */
	furnishing_state furnishings[MAX_FURNISHINGS];

	/** Command log. */
	command_log log;

	/** Pointer to the last executed tail. */
	command_record *last_command;

	/** Error state */
	int errno;
	char strerror[MAX_STRERROR_LENGTH];
};
typedef struct game_state game_state;


struct score_state {
	// 1 VP per Farm animal and Dog
	int animals;
	// 1 VP per Ruby
	int ruby;
	// 1 VP per Dwarf
	int dwarfs;
	// 1 VP per Gold
	int gold;
	// 1/2 VP per Grain (rounded up)
	int grain;
	// 1 VP per Vegetable
	int vegetable;
	// 2 VP per Small pasture, and 4 VP per Large pasture
	int pastures;
	// 3 VP per Ore mine, and 4 VP per Ruby mine.
	int mines;
	// Static VP for Furnishing tiles
	int furnishings;
	// Dynamic VP for Furnishing tiles;
	int bonus;

	// Penalty: -2 VP for each missing Farm animal type
	int missing_farm_animals;
	// Penalty: -1 VP per unused space
	int unused_spaces;
	// Penalty: -3 VP per Begging marker
	int begging;
	// Penalty acquittance
	int acquittance;

	// Total score before penalty. TODO: rename: total_gain?
	int total;
	// Total penalty. TODO: rename: total_loss?
	int penalty;
};
typedef struct score_state score_state;


int caverna_init(game_state *gs);
void caverna_deinit(game_state *gs);

game_state *caverna_create(void);
void caverna_free(game_state *gs);

int caverna_finished(const game_state *gs);

int caverna_start(game_state *gs, int num_players);

int caverna_get_cur_round(const game_state *gs);
int caverna_get_cur_player(const game_state *gs);
void caverna_get_next_dwarf(const game_state *gs, int *next_dwarf, int *next_armed);
const player_state *caverna_get_player(const game_state *gs, int player_num);
int *caverna_get_resource(const player_state *player, int type);

const char *caverna_get_action_name(int type);
const char *caverna_get_resource_name(int type);
const char *caverna_get_tile_name(int type);
const char *caverna_get_furnishing_name(int type);
const char *caverna_get_loot_name(int type);
const int *caverna_get_loot_items_upto(int strength, int *num_items);
const int *caverna_get_all_furnishing_types(const game_state *gs, int *num_types);
const int *caverna_get_all_conversion_types(int *num_types);
int caverna_get_conversion_description(int type, const char **input_desc, const char **output_desc);

const int *caverna_get_ruby2tile_conversion_types(int *num_types);
int caverna_is_ruby2tile_conversion(int type);

int caverna_get_action_resource(int type);
const int *caverna_get_furnishing_price(int type);
int caverna_has_player_tile(const player_state *player, int type);
int caverna_get_furnishing_owner(const game_state *gs, int type);
void caverna_get_both_coordinates(
    const tile_placement *placement,
    int *x1, int *y1, int *x2, int *y2
);
void caverna_get_mountain_limits(const player_state *player, int *xmin, int *ymin, int *xmax, int *ymax);
void caverna_get_forest_limits(const player_state *player, int *xmin, int *ymin, int *xmax, int *ymax);
int caverna_has_adjacent_other_than(const tile_state *board, int x, int y, int type);


int caverna_num_donkeys_in_ore_mines(const player_state *player);
int caverna_num_rooms_in_dwellings(const player_state *player);
int caverna_num_caverns(const player_state *player);

tile_state *caverna_get_top_tile(const tile_state *board, int x, int y);

void *caverna_malloc_orders(int type);

int caverna_beginning_of_round(const game_state *gs);
int caverna_begin_round(game_state *gs);

int caverna_convert_ruby_to_tile(game_state *gs, int conversion, const tile_placement *placement);
int caverna_convert_resources(game_state *gs, int conversion, int count);
int caverna_take_action(game_state *gs, int dwarf_num, const action_orders *ao);
int caverna_put_ruby_on_action(game_state *gs, int action_type);

int caverna_end_of_turn(const game_state *gs);
int caverna_num_unplaced_animals(const game_state *gs);
int caverna_finish_turn(game_state *gs);

int caverna_end_of_round(const game_state *gs);
int caverna_finish_round(game_state *gs);

int caverna_harvest(game_state *gs);
int caverna_compute_feeding_cost(const game_state *gs, int working_cave_effect);

int caverna_feed(game_state *gs, const family_feeding *feeding);

int caverna_breed(game_state *gs, int type);
int caverna_unbreed(game_state *gs, int type);
int caverna_commit_breeding(game_state *gs);
//int caverna_rollback_breeding(game_state *gs);

int caverna_grow(game_state *gs);

int caverna_end_of_game(const game_state *gs);
int caverna_finish_game(game_state *gs);

const char *caverna_strerror(const game_state *gs);
int caverna_errno(const game_state *gs);

void caverna_rollback(game_state *gs);

int caverna_can_furnish(const player_state *player, int type);
int caverna_can_convert(const player_state *player, int conversion, int count);

//int caverna_drop_animal_to_tile(game_state *gs, int x, int y, int type, int quantity);
//int caverna_take_animal_from_tile(game_state *gs, int x, int y, int type, int quantity);

int caverna_place_animals(game_state *gs);
int caverna_rearrange_animals(player_state *player);
int caverna_verify_animal_arrangement(game_state *gs, const player_state *player);

int caverna_get_score(score_state *score, const player_state *player);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
