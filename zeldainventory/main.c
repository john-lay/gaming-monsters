#include <gb/gb.h>
#include "tileset.c"
#include "tilemap.c"
#include "zeldaTypes.c"

UINT8 weaponScrollOffset = 0;
ZELDA_TREASURES equipped = ZELDA_TREASURE_UNDEFINED; // this will be read from GB Studio
UINT8 highlighted = 0;                               // if the equipped treasure is visible this is set to 1-6
UINT8 totalTreasuresFound = 10;                      // calculated at the same time as treasures[] based on GB Studio interrogation
UINT8 totalWeaponsFound = 18;
UINT8 slot = 0;
const UINT8 maxItemsOnScreen = 6;

// tile index starts at 54 and moves 4 tiles for each new item
UINT8 tileIndex = 54;

unsigned char treasureContainer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char weaponContainer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// this needs to be dynamically populated based on GB Studio variable interrogation
ZELDA_TREASURES treasures[10] = {ZELDA_TREASURE_PLANK,
                                 ZELDA_TREASURE_RAFT,
                                 ZELDA_TREASURE_REDBOOTS,
                                 ZELDA_TREASURE_REPELLENT,
                                 ZELDA_TREASURE_RUG,
                                 ZELDA_TREASURE_SALTCELLAR,
                                 ZELDA_TREASURE_TICKETA,
                                 ZELDA_TREASURE_TICKETB,
                                 ZELDA_TREASURE_VIALOFWIND,
                                 ZELDA_TREASURE_WATERBOTTLE};

ZELDA_WEAPONS weapons[19] = {ZELDA_WEAPON_BOOMERANG,
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
                             ZELDA_WEAPON_WAND};

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
        // set_bkg_data(tileIndex, 4, );
        break;
    default:
        break;
    }
}

void initialiseWeapons()
{
    tileIndex = 54;
    slot = 0;
    for (UINT8 i = 0; i < 8; i++)
    {
        addWeaponToVram(weapons[i], tileIndex);
        tileIndex += 4;

        if (i < maxItemsOnScreen)
        {
            placeItemOnScreen(weaponSlots[i], weaponContainer, slot);
            slot += 2;
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
        tileIndex = 54;
        tileIndex += (weaponScrollOffset)*4;

        // check if we've written to the end of 8*4 tile slots reserved for weapons
        if (weaponScrollOffset >= 8)
        {
            tileIndex = 54;
            tileIndex += (weaponScrollOffset - 8) * 4;
        }

        // add a new tile to VRAM
        addWeaponToVram(weapons[weaponScrollOffset], tileIndex);
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
        tileIndex = 54;

        if (weaponScrollOffset > 2)
        {
            tileIndex += (weaponScrollOffset - 2) * 4;
        }

        // check if we've written to the end of 8*4 tile slots reserved for weapons
        if (weaponScrollOffset >= 10)
        {
            tileIndex = 54;
            tileIndex += (weaponScrollOffset - 10) * 4;
        }

        // add a new tile to VRAM
        if (weaponScrollOffset > 1)
        {
            addWeaponToVram(weapons[weaponScrollOffset + 6], tileIndex);
            placeItemOnScreen(weaponSlots[0], weaponContainer, 0);
        }

        updateWeapons();
    }
}

void main()
{
    // load the core tiles that won't change (22 tiles)
    set_bkg_data(0, 22, staticTileset);

    // load the appropriate emblem to indicate celestial signs collected
    // 32 tiles starting at index 22 (after the 22 core tiles)
    set_bkg_data(22, 32, celestial0tileset);

    // load the weapons and treasures
    // set_bkg_data(54, 192, inventoryTileset);

    // draw the background tiles
    set_bkg_tiles(0, 0, 20, 18, questStatusMap);

    SHOW_BKG;
    DISPLAY_ON;

    // update the treasure tiles
    // populateTreasures();
    // set_bkg_tiles(4, 11, 12, 2, treasureMap);

    // update the weapon tiles
    initialiseWeapons();
    set_bkg_tiles(4, 15, 12, 2, weaponContainer);

    // weaponMap[0] = turquoiseRingMap[0];
    // weaponMap[1] = turquoiseRingMap[1];
    // weaponMap[12] = turquoiseRingMap[2];
    // weaponMap[13] = turquoiseRingMap[3];
    // set_bkg_tiles(4, 15, 12, 2, weaponsMap);

    // treasureMap[0] = compass7Map[0];
    // treasureMap[1] = compass7Map[1];
    // treasureMap[12] = compass7Map[2];
    // treasureMap[13] = compass7Map[3];
    // set_bkg_tiles(4, 11, 12, 2, treasureMap);

    // load a single weapon tileset
    // set_bkg_data(0, 4, turquoiseRingTileset);

    // // load a single treasure tileset
    // set_bkg_data(86, 4, compass7Tileset);

    // // draw treasure
    // placeItemOnScreen(treasureSlots[0], treasureContainer, 0);
    // set_bkg_tiles(4, 11, 12, 2, treasureContainer);

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
        }
    }
}
