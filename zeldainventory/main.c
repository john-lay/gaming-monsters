#include <gb/gb.h>
#include "tileset.c"
#include "tilemap.c"
#include "zeldaTypes.c"

UINT8 scrollOffset = 0;
ZELDA_TREASURES equipped = ZELDA_TREASURE_UNDEFINED; // this will be read from GB Studio
UINT8 highlighted = 0;                               // if the equipped treasure is visible this is set to 1-6
UINT8 totalTreasuresFound = 10;                      // calculated at the same time as treasures[] based on GB Studio interrogation
const UINT8 maxTreasuresOnScreen = 6;

unsigned char treasureMap[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char weaponsMap[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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
    for (UINT8 i = scrollOffset; i < maxTreasuresOnScreen + scrollOffset; i++)
    {
        if (treasures[i] == ZELDA_TREASURE_PLANK && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, plankMap);
            treasureMapIndex += 2;
            treasuresAdded++;

            // if this spell is equipped show the cursor sprite over it
            if (equipped == ZELDA_TREASURE_PLANK)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_RAFT && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, raftMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_RAFT)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_REDBOOTS && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, redBootsMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_REDBOOTS)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_REPELLENT && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, repellentMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_REPELLENT)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_RUG && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, rugMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_RUG)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_SALTCELLAR && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, saltcellarMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_SALTCELLAR)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_TICKETA && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, ticketAMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_TICKETA)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_TICKETB && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, ticketBMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_TICKETB)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_VIALOFWIND && treasuresAdded < maxTreasuresOnScreen)
        {
            insertItemTileIntoTileMap(treasureMap, treasureMapIndex, vialWindMap);
            treasureMapIndex += 2;
            treasuresAdded++;
            if (equipped == ZELDA_TREASURE_VIALOFWIND)
                highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_WATERBOTTLE && treasuresAdded < maxTreasuresOnScreen)
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

UBYTE CanScrollLeft()
{
    return scrollOffset > 0;
}

UBYTE CanScrollRight()
{
    return scrollOffset < totalTreasuresFound - maxTreasuresOnScreen;
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

void main()
{
    // load the core tiles that won't change
    set_bkg_data(0, 22, staticTileset);

    // load the appropriate emblem to indicate celestial signs collected
    set_bkg_data(22, 32, celestial0tileset);

    // load the weapons and treasures
    set_bkg_data(54, 192, inventoryTileset);

    // draw the background tiles
    set_bkg_tiles(0, 0, 20, 18, questStatusMap);

    SHOW_BKG;
    DISPLAY_ON;

    // update the treasure tiles
    populateTreasures();
    set_bkg_tiles(4, 11, 12, 2, treasureMap);

    weaponsMap[0] = turquoiseRingMap[0];
    weaponsMap[1] = turquoiseRingMap[1];
    weaponsMap[12] = turquoiseRingMap[2];
    weaponsMap[13] = turquoiseRingMap[3];
    set_bkg_tiles(4, 15, 12, 2, weaponsMap);

    // treasureMap[0] = compass7Map[0];
    // treasureMap[1] = compass7Map[1];
    // treasureMap[12] = compass7Map[2];
    // treasureMap[13] = compass7Map[3];
    // set_bkg_tiles(4, 11, 12, 2, treasureMap);

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
        }
    }
}
