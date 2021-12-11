#include <gb/gb.h>
#include "tileset.c"
#include "tilemap.c"

UINT8 scrollOffset = 0;

unsigned char treasureMap[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char weaponsMap[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
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
UINT8 highlighted = 0;                               // if the equipped treasure is visible this is set to 1-6

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
            if (equipped == ZELDA_TREASURE_FIRESTORM)
                highlighted = i - scrollOffset + 1;
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
            treasureMap[treasureMapIndex] = magicShieldMap[0];
            treasureMap[treasureMapIndex + 1] = magicShieldMap[1];
            treasureMap[treasureMapIndex + 12] = magicShieldMap[2];
            treasureMap[treasureMapIndex + 13] = magicShieldMap[3];
            treasureMapIndex += 4;

            treasuresAdded++;
        }
        if (treasures[i] == ZELDA_TREASURE_RING && treasuresAdded < maxTreasuresOnScreen)
        {
            treasureMap[treasureMapIndex] = jadeRingMap[0];
            treasureMap[treasureMapIndex + 1] = jadeRingMap[1];
            treasureMap[treasureMapIndex + 12] = jadeRingMap[2];
            treasureMap[treasureMapIndex + 13] = jadeRingMap[3];
            treasureMapIndex += 4;

            treasuresAdded++;
        }
        if (treasures[i] == ZELDA_TREASURE_BOOK && treasuresAdded < maxTreasuresOnScreen)
        {
            treasureMap[treasureMapIndex] = noiseMap[0];
            treasureMap[treasureMapIndex + 1] = noiseMap[1];
            treasureMap[treasureMapIndex + 12] = noiseMap[2];
            treasureMap[treasureMapIndex + 13] = noiseMap[3];
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
    set_bkg_tiles(0, 0, 20, 18, questStatusMap);

    SHOW_BKG;
    DISPLAY_ON;

    // update the treasure tiles
    // populateTreasures();
    // set_bkg_tiles(4, 11, 12, 2, treasureMap);

    weaponsMap[0] = turquoiseRingMap[0];
    weaponsMap[1] = turquoiseRingMap[1];
    weaponsMap[12] = turquoiseRingMap[2];
    weaponsMap[13] = turquoiseRingMap[3];
    set_bkg_tiles(4, 15, 12, 2, weaponsMap);
    
    treasureMap[0] = compass7Map[0];
    treasureMap[1] = compass7Map[1];
    treasureMap[12] = compass7Map[2];
    treasureMap[13] = compass7Map[3];
    set_bkg_tiles(4, 11, 12, 2, treasureMap);
    

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
