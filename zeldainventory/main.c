#include <gb/gb.h>
#include "tileset.c"
#include "tilemap.c"
#include "zeldaTypes.c"

const UINT8 maxItemsOnScreen = 6;
ZELDA_TREASURES equipped = ZELDA_TREASURE_UNDEFINED; // this will be read from GB Studio
UINT8 highlighted = 0;                               // if the equipped treasure is visible this is set to 1-6
UINT8 slot = 0;

UINT8 weaponScrollOffset = 0;
UINT8 totalWeaponsFound = 19; // calculated at the same time as treasures[] based on GB Studio interrogation
UINT8 weaponTileIndex = 54;   // tile index starts at 54 and moves 4 tiles for each new item

UINT8 treasureScrollOffset = 0;
UINT8 totalTreasuresFound = 41;
UINT8 treasureTileIndex = 86; // tile index starts at 86 and moves 4 tiles for each new item

unsigned char treasureContainer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char weaponContainer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

ZELDA_TREASURES treasures[41] = {ZELDA_TREASURE_BLACKORB,
                                 ZELDA_TREASURE_BONE,
                                 ZELDA_TREASURE_BOUQUET,
                                 ZELDA_TREASURE_CANDLE,
                                 ZELDA_TREASURE_COAL,
                                 ZELDA_TREASURE_COMPASS1,
                                 ZELDA_TREASURE_COMPASS2,
                                 ZELDA_TREASURE_COMPASS3,
                                 ZELDA_TREASURE_COMPASS4,
                                 ZELDA_TREASURE_COMPASS5,
                                 ZELDA_TREASURE_COMPASS6,
                                 ZELDA_TREASURE_COMPASS7,
                                 ZELDA_TREASURE_DIAMOND,
                                 ZELDA_TREASURE_EMPTYBOTTLE,
                                 ZELDA_TREASURE_FLUTE,
                                 ZELDA_TREASURE_GOLDENBOOTS,
                                 ZELDA_TREASURE_HARP,
                                 ZELDA_TREASURE_KEY,
                                 ZELDA_TREASURE_KNIFE,
                                 ZELDA_TREASURE_LADDER,
                                 ZELDA_TREASURE_LIFEPOTION,
                                 ZELDA_TREASURE_MAGICSHIELD,
                                 ZELDA_TREASURE_MAP1,
                                 ZELDA_TREASURE_MAP2,
                                 ZELDA_TREASURE_MAP3,
                                 ZELDA_TREASURE_MAP4,
                                 ZELDA_TREASURE_MAP5,
                                 ZELDA_TREASURE_MAP6,
                                 ZELDA_TREASURE_MAP7,
                                 ZELDA_TREASURE_PLANK,
                                 ZELDA_TREASURE_RAFT,
                                 ZELDA_TREASURE_REDBOOTS,
                                 ZELDA_TREASURE_REDBOW,
                                 ZELDA_TREASURE_REPELLENT,
                                 ZELDA_TREASURE_RUG,
                                 ZELDA_TREASURE_RUPEE,
                                 ZELDA_TREASURE_SALTCELLAR,
                                 ZELDA_TREASURE_TICKETA,
                                 ZELDA_TREASURE_TICKETB,
                                 ZELDA_TREASURE_VIALOFWIND,
                                 ZELDA_TREASURE_WATERBOTTLE};

// this needs to be dynamically populated based on GB Studio variable interrogation
ZELDA_WEAPONS weapons[19] = {
    ZELDA_WEAPON_WAND,
    ZELDA_WEAPON_BOOMERANG,
    ZELDA_WEAPON_BOWANDARROW,
    ZELDA_WEAPON_BROADSWORD,
    ZELDA_WEAPON_CALM,
    ZELDA_WEAPON_DAGGER,
    ZELDA_WEAPON_GOLDNECKLACE,
    ZELDA_WEAPON_FEATHER,
    ZELDA_WEAPON_FIRESTORM,
    ZELDA_WEAPON_HAMMER,
    ZELDA_WEAPON_JADEAMULET,
    ZELDA_WEAPON_JADERING,
    ZELDA_WEAPON_JOUST,
    ZELDA_WEAPON_NOISE,
    ZELDA_WEAPON_PYROS,
    ZELDA_WEAPON_RINGSOFFIRE,
    ZELDA_WEAPON_ROARSTICK,
    ZELDA_WEAPON_SHORTAXE,
    ZELDA_WEAPON_TURQUOISERING,
};

UBYTE GetBit(UINT8 byte, UINT8 bit)
{
    return (byte & (1 << bit)) != 0;
}

void placeItemOnScreen(unsigned char item[], unsigned char container[], UINT8 slot)
{
    container[slot] = item[0];
    container[slot + 1] = item[1];
    container[slot + 12] = item[2];
    container[slot + 13] = item[3];
}

// reserve 8 slots to represent the 6 on screen treasures plus 2 off screen
const unsigned char treasureSlots[8][4] = {
    {0x56, 0x57, 0x58, 0x59},
    {0x5A, 0x5B, 0x5C, 0x5D},
    {0x5E, 0x5F, 0x60, 0x61},
    {0x62, 0x63, 0x64, 0x65},
    {0x66, 0x67, 0x68, 0x69},
    {0x6A, 0x6B, 0x6C, 0x6D},
    {0x6E, 0x6F, 0x70, 0x71},
    {0x72, 0x73, 0x74, 0x75},
};

// reserve 8 slots to represent the 6 on screen weapons plus 2 off screen
const unsigned char weaponSlots[8][4] = {
    {0x36, 0x37, 0x38, 0x39},
    {0x3A, 0x3B, 0x3C, 0x3D},
    {0x3E, 0x3F, 0x40, 0x41},
    {0x42, 0x43, 0x44, 0x45},
    {0x46, 0x47, 0x48, 0x49},
    {0x4A, 0x4B, 0x4C, 0x4D},
    {0x4E, 0x4F, 0x50, 0x51},
    {0x52, 0x53, 0x54, 0x55},
};

void addWeaponToVram(ZELDA_WEAPONS weapon, UINT8 tileIndex)
{
    switch (weapon)
    {
    case ZELDA_WEAPON_BOOMERANG:
        set_bkg_data(tileIndex, 4, boomerangTileset);
        break;
    case ZELDA_WEAPON_BOWANDARROW:
        set_bkg_data(tileIndex, 4, bowArrowTileset);
        break;
    case ZELDA_WEAPON_BROADSWORD:
        set_bkg_data(tileIndex, 4, broadswordTileset);
        break;
    case ZELDA_WEAPON_CALM:
        set_bkg_data(tileIndex, 4, calmTileset);
        break;
    case ZELDA_WEAPON_DAGGER:
        set_bkg_data(tileIndex, 4, daggerTileset);
        break;
    case ZELDA_WEAPON_GOLDNECKLACE:
        set_bkg_data(tileIndex, 4, goldNecklaceTileset);
        break;
    case ZELDA_WEAPON_FEATHER:
        set_bkg_data(tileIndex, 4, featherTileset);
        break;
    case ZELDA_WEAPON_FIRESTORM:
        set_bkg_data(tileIndex, 4, firestormTileset);
        break;
    case ZELDA_WEAPON_HAMMER:
        set_bkg_data(tileIndex, 4, hammerTileset);
        break;
    case ZELDA_WEAPON_JADEAMULET:
        set_bkg_data(tileIndex, 4, jadeAmuletTileset);
        break;
    case ZELDA_WEAPON_JADERING:
        set_bkg_data(tileIndex, 4, jadeRingTileset);
        break;
    case ZELDA_WEAPON_JOUST:
        set_bkg_data(tileIndex, 4, joustTileset);
        break;
    case ZELDA_WEAPON_NOISE:
        set_bkg_data(tileIndex, 4, noiseTileset);
        break;
    case ZELDA_WEAPON_PYROS:
        set_bkg_data(tileIndex, 4, pyrosTileset);
        break;
    case ZELDA_WEAPON_RINGSOFFIRE:
        set_bkg_data(tileIndex, 4, ringsFireTileset);
        break;
    case ZELDA_WEAPON_ROARSTICK:
        set_bkg_data(tileIndex, 4, roarStickTileset);
        break;
    case ZELDA_WEAPON_SHORTAXE:
        set_bkg_data(tileIndex, 4, shortAxeTileset);
        break;
    case ZELDA_WEAPON_TURQUOISERING:
        set_bkg_data(tileIndex, 4, turquoiseRingTileset);
        break;
    case ZELDA_WEAPON_WAND:
        set_bkg_data(tileIndex, 4, wandTileset);
        break;
    default:
        break;
    }
}

void initialiseWeapons()
{
    weaponTileIndex = 54;
    slot = 0;
    for (UINT8 i = 0; i < 8; i++)
    {
        if (i < totalWeaponsFound)
        {
            addWeaponToVram(weapons[weaponScrollOffset + i], weaponTileIndex);
            weaponTileIndex += 4;

            if (i < maxItemsOnScreen)
            {
                placeItemOnScreen(weaponSlots[i], weaponContainer, slot);
                slot += 2;
            }
        }
    }
}

void updateWeapons()
{
    slot = 0;
    for (UINT8 i = 0; i < maxItemsOnScreen; i++)
    {
        // items pushed to beginning of array (2nd overwrite)
        if (weaponScrollOffset + i >= 16)
        {
            placeItemOnScreen(weaponSlots[weaponScrollOffset + i - 16], weaponContainer, slot);
        }
        // items pushed to beginning of array (1st overwrite)
        else if (weaponScrollOffset + i >= 8)
        {
            placeItemOnScreen(weaponSlots[weaponScrollOffset + i - 8], weaponContainer, slot);
        }
        else
        {
            placeItemOnScreen(weaponSlots[weaponScrollOffset + i], weaponContainer, slot);
        }

        slot += 2;
    }

    // update the 6 onscreen weapons
    set_bkg_tiles(4, 15, 12, 2, weaponContainer);
}

UBYTE CanScrollWeaponsLeft()
{
    return weaponScrollOffset > 0;
}

UBYTE CanScrollWeaponsRight()
{
    return weaponScrollOffset < totalWeaponsFound - maxItemsOnScreen;
}

void ScrollWeaponsLeft()
{
    if (CanScrollWeaponsLeft())
    {
        weaponScrollOffset--;

        // calculate tile index
        weaponTileIndex = 54;
        weaponTileIndex += (weaponScrollOffset)*4;

        // check if we've written to the end of 8*4 tile slots reserved for weapons
        if (weaponScrollOffset >= 8)
        {
            weaponTileIndex = 54;
            weaponTileIndex += (weaponScrollOffset - 8) * 4;
        }

        // add a new tile to VRAM
        addWeaponToVram(weapons[weaponScrollOffset], weaponTileIndex);
        placeItemOnScreen(weaponSlots[0], weaponContainer, 0);

        updateWeapons();
    }
}

void ScrollWeaponsRight()
{
    if (CanScrollWeaponsRight())
    {
        weaponScrollOffset++;

        // calculate the tile index
        weaponTileIndex = 54;

        if (weaponScrollOffset > 2)
        {
            weaponTileIndex += (weaponScrollOffset - 2) * 4;
        }

        // check if we've written to the end of 8*4 tile slots reserved for weapons
        if (weaponScrollOffset >= 10)
        {
            weaponTileIndex = 54;
            weaponTileIndex += (weaponScrollOffset - 10) * 4;
        }

        // add a new tile to VRAM
        if (weaponScrollOffset > 1)
        {
            addWeaponToVram(weapons[weaponScrollOffset + 6], weaponTileIndex);
            placeItemOnScreen(weaponSlots[0], weaponContainer, 0);
        }

        updateWeapons();
    }
}

void addTreasureToVram(ZELDA_TREASURES treasure, UINT8 tileIndex)
{
    switch (treasure)
    {
    case ZELDA_TREASURE_BLACKORB:
        set_bkg_data(tileIndex, 4, blackOrbTileset);
        break;
    case ZELDA_TREASURE_BONE:
        set_bkg_data(tileIndex, 4, boneTileset);
        break;
    case ZELDA_TREASURE_BOUQUET:
        set_bkg_data(tileIndex, 4, bouquetTileset);
        break;
    case ZELDA_TREASURE_CANDLE:
        set_bkg_data(tileIndex, 4, candleTileset);
        break;
    case ZELDA_TREASURE_COAL:
        set_bkg_data(tileIndex, 4, coalTileset);
        break;
    case ZELDA_TREASURE_COMPASS1:
        set_bkg_data(tileIndex, 4, compass1Tileset);
        break;
    case ZELDA_TREASURE_COMPASS2:
        set_bkg_data(tileIndex, 4, compass2Tileset);
        break;
    case ZELDA_TREASURE_COMPASS3:
        set_bkg_data(tileIndex, 4, compass3Tileset);
        break;
    case ZELDA_TREASURE_COMPASS4:
        set_bkg_data(tileIndex, 4, compass4Tileset);
        break;
    case ZELDA_TREASURE_COMPASS5:
        set_bkg_data(tileIndex, 4, compass5Tileset);
        break;
    case ZELDA_TREASURE_COMPASS6:
        set_bkg_data(tileIndex, 4, compass6Tileset);
        break;
    case ZELDA_TREASURE_COMPASS7:
        set_bkg_data(tileIndex, 4, compass7Tileset);
        break;
    case ZELDA_TREASURE_DIAMOND:
        set_bkg_data(tileIndex, 4, diamondTileset);
        break;
    case ZELDA_TREASURE_EMPTYBOTTLE:
        set_bkg_data(tileIndex, 4, emptyBottleTileset);
        break;
    case ZELDA_TREASURE_FLUTE:
        set_bkg_data(tileIndex, 4, fluteTileset);
        break;
    case ZELDA_TREASURE_GOLDENBOOTS:
        set_bkg_data(tileIndex, 4, goldenBootsTileset);
        break;
    case ZELDA_TREASURE_HARP:
        set_bkg_data(tileIndex, 4, harpTileset);
        break;
    case ZELDA_TREASURE_KEY:
        set_bkg_data(tileIndex, 4, keyTileset);
        break;
    case ZELDA_TREASURE_KNIFE:
        set_bkg_data(tileIndex, 4, knifeTileset);
        break;
    case ZELDA_TREASURE_LADDER:
        set_bkg_data(tileIndex, 4, ladderTileset);
        break;
    case ZELDA_TREASURE_LIFEPOTION:
        set_bkg_data(tileIndex, 4, lifePotionTileset);
        break;
    case ZELDA_TREASURE_MAGICSHIELD:
        set_bkg_data(tileIndex, 4, magicShieldTileset);
        break;
    case ZELDA_TREASURE_MAP1:
        set_bkg_data(tileIndex, 4, map1Tileset);
        break;
    case ZELDA_TREASURE_MAP2:
        set_bkg_data(tileIndex, 4, map2Tileset);
        break;
    case ZELDA_TREASURE_MAP3:
        set_bkg_data(tileIndex, 4, map3Tileset);
        break;
    case ZELDA_TREASURE_MAP4:
        set_bkg_data(tileIndex, 4, map4Tileset);
        break;
    case ZELDA_TREASURE_MAP5:
        set_bkg_data(tileIndex, 4, map5Tileset);
        break;
    case ZELDA_TREASURE_MAP6:
        set_bkg_data(tileIndex, 4, map6Tileset);
        break;
    case ZELDA_TREASURE_MAP7:
        set_bkg_data(tileIndex, 4, map7Tileset);
        break;
    case ZELDA_TREASURE_PLANK:
        set_bkg_data(tileIndex, 4, plankTileset);
        break;
    case ZELDA_TREASURE_RAFT:
        set_bkg_data(tileIndex, 4, raftTileset);
        break;
    case ZELDA_TREASURE_REDBOOTS:
        set_bkg_data(tileIndex, 4, redBootsTileset);
        break;
    case ZELDA_TREASURE_REDBOW:
        set_bkg_data(tileIndex, 4, redBowTileset);
        break;
    case ZELDA_TREASURE_REPELLENT:
        set_bkg_data(tileIndex, 4, repellentTileset);
        break;
    case ZELDA_TREASURE_RUG:
        set_bkg_data(tileIndex, 4, rugTileset);
        break;
    case ZELDA_TREASURE_RUPEE:
        set_bkg_data(tileIndex, 4, rupeeTileset);
        break;
    case ZELDA_TREASURE_SALTCELLAR:
        set_bkg_data(tileIndex, 4, saltcellarTileset);
        break;
    case ZELDA_TREASURE_TICKETA:
        set_bkg_data(tileIndex, 4, ticketATileset);
        break;
    case ZELDA_TREASURE_TICKETB:
        set_bkg_data(tileIndex, 4, ticketBTileset);
        break;
    case ZELDA_TREASURE_VIALOFWIND:
        set_bkg_data(tileIndex, 4, vialWindTileset);
        break;
    case ZELDA_TREASURE_WATERBOTTLE:
        set_bkg_data(tileIndex, 4, waterBottleTileset);
        break;
    default:
        break;
    }
}

void initialiseTreasures()
{
    treasureTileIndex = 86;
    slot = 0;
    for (UINT8 i = 0; i < 8; i++)
    {
        if (i < totalTreasuresFound)
        {
            addTreasureToVram(treasures[treasureScrollOffset + i], treasureTileIndex);
            treasureTileIndex += 4;

            if (i < maxItemsOnScreen)
            {
                placeItemOnScreen(treasureSlots[i], treasureContainer, slot);
                slot += 2;
            }
        }
    }
}

void updateTreasures()
{
    slot = 0;
    for (UINT8 i = 0; i < maxItemsOnScreen; i++)
    {
        // items pushed to beginning of array (5th overwrite)
        if (treasureScrollOffset + i >= 40)
        {
            placeItemOnScreen(treasureSlots[treasureScrollOffset + i - 40], treasureContainer, slot);
        }
        // items pushed to beginning of array (4th overwrite)
        else if (treasureScrollOffset + i >= 32)
        {
            placeItemOnScreen(treasureSlots[treasureScrollOffset + i - 32], treasureContainer, slot);
        }
        // items pushed to beginning of array (3rd overwrite)
        else if (treasureScrollOffset + i >= 24)
        {
            placeItemOnScreen(treasureSlots[treasureScrollOffset + i - 24], treasureContainer, slot);
        }
        // items pushed to beginning of array (2nd overwrite)
        else if (treasureScrollOffset + i >= 16)
        {
            placeItemOnScreen(treasureSlots[treasureScrollOffset + i - 16], treasureContainer, slot);
        }
        // items pushed to beginning of array (1st overwrite)
        else if (treasureScrollOffset + i >= 8)
        {
            placeItemOnScreen(treasureSlots[treasureScrollOffset + i - 8], treasureContainer, slot);
        }
        else
        {
            placeItemOnScreen(treasureSlots[treasureScrollOffset + i], treasureContainer, slot);
        }

        slot += 2;
    }

    // update the 6 onscreen treasures
    set_bkg_tiles(4, 11, 12, 2, treasureContainer);
}

UBYTE CanScrollTreasuresLeft()
{
    return treasureScrollOffset > 0;
}

UBYTE CanScrollTreasuresRight()
{
    return treasureScrollOffset < totalTreasuresFound - maxItemsOnScreen;
}

void ScrollTreasuresLeft()
{
    if (CanScrollTreasuresLeft())
    {
        treasureScrollOffset--;

        // calculate tile index
        treasureTileIndex = 86;
        treasureTileIndex += (treasureScrollOffset)*4;

        // check if we've written to the end of 8*4 tile slots reserved for weapons
        if (treasureScrollOffset >= 32)
        {
            treasureTileIndex = 86;
            treasureTileIndex += (treasureScrollOffset - 32) * 4;
        }
        else if (treasureScrollOffset >= 24)
        {
            treasureTileIndex = 86;
            treasureTileIndex += (treasureScrollOffset - 24) * 4;
        }
        else if (treasureScrollOffset >= 16)
        {
            treasureTileIndex = 86;
            treasureTileIndex += (treasureScrollOffset - 16) * 4;
        }
        else if (treasureScrollOffset >= 8)
        {
            treasureTileIndex = 86;
            treasureTileIndex += (treasureScrollOffset - 8) * 4;
        }

        // add a new tile to VRAM
        addTreasureToVram(treasures[treasureScrollOffset], treasureTileIndex);
        placeItemOnScreen(treasureSlots[0], treasureContainer, 0);

        updateTreasures();
    }
}

void ScrollTreasuresRight()
{
    if (CanScrollTreasuresRight())
    {
        treasureScrollOffset++;

        // calculate the tile index
        treasureTileIndex = 86;

        if (treasureScrollOffset > 2)
        {
            treasureTileIndex += (treasureScrollOffset - 2) * 4;
        }

        // check if we've written to the end of 8*4 tile slots reserved for treasures
        if (treasureScrollOffset >= 34)
        {
            treasureTileIndex = 86;
            treasureTileIndex += (treasureScrollOffset - 34) * 4;
        }
        else if (treasureScrollOffset >= 26)
        {
            treasureTileIndex = 86;
            treasureTileIndex += (treasureScrollOffset - 26) * 4;
        }
        else if (treasureScrollOffset >= 18)
        {
            treasureTileIndex = 86;
            treasureTileIndex += (treasureScrollOffset - 18) * 4;
        }
        else if (treasureScrollOffset >= 10)
        {
            treasureTileIndex = 86;
            treasureTileIndex += (treasureScrollOffset - 10) * 4;
        }

        // add a new tile to VRAM
        if (treasureScrollOffset > 1)
        {
            addTreasureToVram(treasures[treasureScrollOffset + 6], treasureTileIndex);
            placeItemOnScreen(treasureSlots[0], treasureContainer, 0);
        }

        updateTreasures();
    }
}

void main()
{
    // load the core tiles that won't change (22 tiles)
    set_bkg_data(0, 22, staticTileset);

    // load the appropriate emblem to indicate celestial signs collected
    // 32 tiles starting at index 22 (after the 22 core tiles)
    set_bkg_data(22, 32, celestial0tileset);

    // draw the background tiles
    set_bkg_tiles(0, 0, 20, 18, questStatusMap);

    // initialise the treasure tiles
    initialiseTreasures();
    set_bkg_tiles(4, 11, 12, 2, treasureContainer);

    // initialise the weapon tiles
    initialiseWeapons();
    set_bkg_tiles(4, 15, 12, 2, weaponContainer);

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        switch (joypad())
        {
        case J_LEFT:
            ScrollWeaponsLeft();
            delay(100);
            break;
        case J_RIGHT:
            ScrollWeaponsRight();
            delay(100);
            break;
        case J_UP:
            ScrollTreasuresLeft();
            delay(100);
            break;
        case J_DOWN:
            ScrollTreasuresRight();
            delay(100);
            break;
        }
    }
}
