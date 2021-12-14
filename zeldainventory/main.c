#include <gb/gb.h>
#include "tileset.c"
#include "tilemap.c"
#include "zeldaTypes.c"

UINT8 scrollOffset = 0;
ZELDA_TREASURES equipped = ZELDA_TREASURE_UNDEFINED; // this will be read from GB Studio
UINT8 highlighted = 0;                               // if the equipped treasure is visible this is set to 1-6
UINT8 totalTreasuresFound = 10;                      // calculated at the same time as treasures[] based on GB Studio interrogation
const UINT8 maxItemsOnScreen = 6;

unsigned char treasureMap[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char weaponMap[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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

void insertItemTileIntoTileMap(unsigned char array[], UINT8 index, unsigned char item[])
{
    array[index] = item[0];
    array[index + 1] = item[1];
    array[index + 12] = item[2];
    array[index + 13] = item[3];
}

void populateTreasures()
{
    UINT8 treasuresAdded = 0;
    UINT8 treasureMapIndex = 0;

    // iterate over the treasures array and populate the tileMap accordingly
    for (UINT8 i = scrollOffset; i < maxItemsOnScreen + scrollOffset; i++)
    {
        if (treasures[i] == ZELDA_TREASURE_PLANK && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, plankMap);
            treasureMapIndex += 2;
            treasuresAdded++;

            // if this spell is equipped show the cursor sprite over it
            if (equipped == ZELDA_TREASURE_PLANK)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_RAFT && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, raftMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_RAFT)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_REDBOOTS && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, redBootsMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_REDBOOTS)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_REPELLENT && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, repellentMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_REPELLENT)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_RUG && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, rugMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_RUG)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_SALTCELLAR && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, saltcellarMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_SALTCELLAR)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_TICKETA && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, ticketAMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_TICKETA)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_TICKETB && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, ticketBMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_TICKETB)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_VIALOFWIND && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, vialWindMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_VIALOFWIND)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_WATERBOTTLE && treasuresAdded < maxItemsOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, waterBottleMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_WATERBOTTLE)
                highlighted = i - scrollOffset + 1;
        }
    }

    set_bkg_tiles(4, 11, 12, 2, treasureMap);
}

// reserve 8 tiles to represent the 6 on screen weapons plus 2 off screen
const unsigned char weaponsMap[8][4] = {
    {0x36, 0x37, 0x38, 0x39},
    {0x3A, 0x3B, 0x3C, 0x3D},
    {0x3E, 0x3F, 0x40, 0x41},
    {0x42, 0x43, 0x44, 0x45},
    {0x46, 0x47, 0x48, 0x49},
    {0x4A, 0x4B, 0x4C, 0x4D},
    {0x4E, 0x4F, 0x50, 0x51},
    {0x52, 0x53, 0x54, 0x55},
    };
    
void initialiseWeapons()
{
    UINT8 tileIndex = 54;
    UINT8 weaponMapIndex = 0;
    // load the boomerang tile (starting from index 54 core + celestial)
    set_bkg_data(tileIndex, 4, boomerangTileset);
    insertItemTileIntoTileMap(weaponMap, weaponMapIndex, weaponsMap[0]);
    tileIndex += 4; // move across 4 tiles in memory
    weaponMapIndex += 2; // move across 2 tiles on screen

    set_bkg_data(tileIndex, 4, bowArrowTileset);
    insertItemTileIntoTileMap(weaponMap, weaponMapIndex, weaponsMap[1]);
    tileIndex += 4; 
    weaponMapIndex += 2;
}

void updateWeapons() 
{
    
}

UBYTE CanScrollLeft()
{
    return scrollOffset > 0;
}

UBYTE CanScrollRight()
{
    return scrollOffset < totalTreasuresFound - maxItemsOnScreen;
}

void ScrollLeft()
{
    if (CanScrollLeft())
    {
        scrollOffset--;
        populateTreasures();
    }
}

void ScrollRight()
{
    if (CanScrollRight())
    {
        scrollOffset++;
        populateTreasures();
    }
}

void ScrollUp()
{
    scrollOffset--;
    updateWeapons();
}

void ScrollDown()
{
    scrollOffset++;
    updateWeapons();
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
    set_bkg_tiles(4, 15, 12, 2, weaponMap);

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

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        switch (joypad())
        {
        case J_LEFT:
            ScrollLeft();
            delay(100);
            break;
        case J_RIGHT:
            ScrollRight();
            delay(100);
            break;
        case J_UP:
            ScrollUp();
            delay(100);
            break;
        case J_DOWN:
            ScrollDown();
            delay(100);
            break;
        }
    }
}
