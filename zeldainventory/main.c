#include <gb/gb.h>
#include "tileset.c"
#include "tilemap.c"

UINT8 scrollOffset = 0;


const unsigned char firestormMap[] = {0x30, 0x31, 0x3A, 0x3B};
const unsigned char calmMap[] = {0x32, 0x33, 0x3C, 0x3D};
const unsigned char shieldMap[] = {0x34, 0x35, 0x3E, 0x3F};
const unsigned char ringMap[] = {0x36, 0x37, 0x40, 0x41};
const unsigned char bookMap[] = {0x38, 0x39, 0x42, 0x43};
unsigned char treasureMap[] = {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
                               0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};

typedef enum
{
    ZELDA_TREASURE_UNDEFINED = 0,
    ZELDA_TREASURE_FIRESTORM,
    ZELDA_TREASURE_CALM,
    ZELDA_TREASURE_SHIELD,
    ZELDA_TREASURE_RING,
    ZELDA_TREASURE_BOOK,
} ZELDA_TREASURES;

// this needs to be dynamically populated based on GB Studio variable interrogation
ZELDA_TREASURES treasures[6] = {ZELDA_TREASURE_FIRESTORM, ZELDA_TREASURE_CALM, ZELDA_TREASURE_SHIELD,
                                ZELDA_TREASURE_RING, ZELDA_TREASURE_BOOK, ZELDA_TREASURE_UNDEFINED};

ZELDA_TREASURES equipped = ZELDA_TREASURE_FIRESTORM; // this will be read from GB Studio
UINT8 highlighted = 0; // if the equipped treasure is visible this is set to 1-6

UBYTE GetBit(UINT8 byte, UINT8 bit)
{
    return (byte & (1 << bit)) != 0;
}

void populateTreasures()
{
    UINT8 treasuresAdded = 0;
    UINT8 treasureMapIndex = 0;
    UINT8 maxTreasuresOnScreen = 3;

    // iterate over the treasures array and populate the tileMap accordingly
    for (UINT8 i = scrollOffset; i < 6; i++)
    {
        if (treasures[i] == ZELDA_TREASURE_FIRESTORM && treasuresAdded < maxTreasuresOnScreen)
        {
            treasureMap[treasureMapIndex] = firestormMap[0];
            treasureMap[treasureMapIndex + 1] = firestormMap[1];
            treasureMap[treasureMapIndex + 12] = firestormMap[2];
            treasureMap[treasureMapIndex + 13] = firestormMap[3];
            treasureMapIndex += 4;

            treasuresAdded++;

            // if this spell is equipped show the cursor sprite over it
            if(equipped == ZELDA_TREASURE_FIRESTORM) highlighted = i - scrollOffset + 1;
        }
        if (treasures[i] == ZELDA_TREASURE_CALM && treasuresAdded < maxTreasuresOnScreen)
        {
            treasureMap[treasureMapIndex] = calmMap[0];
            treasureMap[treasureMapIndex + 1] = calmMap[1];
            treasureMap[treasureMapIndex + 12] = calmMap[2];
            treasureMap[treasureMapIndex + 13] = calmMap[3];
            treasureMapIndex += 4;

            treasuresAdded++;
        }
        if (treasures[i] == ZELDA_TREASURE_SHIELD && treasuresAdded < maxTreasuresOnScreen)
        {
            treasureMap[treasureMapIndex] = shieldMap[0];
            treasureMap[treasureMapIndex + 1] = shieldMap[1];
            treasureMap[treasureMapIndex + 12] = shieldMap[2];
            treasureMap[treasureMapIndex + 13] = shieldMap[3];
            treasureMapIndex += 4;

            treasuresAdded++;
        }
        if (treasures[i] == ZELDA_TREASURE_RING && treasuresAdded < maxTreasuresOnScreen)
        {
            treasureMap[treasureMapIndex] = ringMap[0];
            treasureMap[treasureMapIndex + 1] = ringMap[1];
            treasureMap[treasureMapIndex + 12] = ringMap[2];
            treasureMap[treasureMapIndex + 13] = ringMap[3];
            treasureMapIndex += 4;

            treasuresAdded++;
        }
        if (treasures[i] == ZELDA_TREASURE_BOOK && treasuresAdded < maxTreasuresOnScreen)
        {
            treasureMap[treasureMapIndex] = bookMap[0];
            treasureMap[treasureMapIndex + 1] = bookMap[1];
            treasureMap[treasureMapIndex + 12] = bookMap[2];
            treasureMap[treasureMapIndex + 13] = bookMap[3];
            treasureMapIndex += 4;

            treasuresAdded++;
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
    // TODO: calculate based on treasures acquired and slots available on screen
    return scrollOffset < 2;
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
    set_bkg_tiles(0, 0, 20, 18, mytilemap);

    SHOW_BKG;
    DISPLAY_ON;

    // update the treasure tiles
    // populateTreasures();
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
