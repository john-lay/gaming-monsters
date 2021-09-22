#include "zeldaHud.h"

const UINT8 HEART_START_DRAW = 16;

UINT8 ZELDA_HUD_BLANK = 0x00;
UINT8 ZELDA_HUD_1 = 0x01;
UINT8 ZELDA_HUD_2 = 0x02;
UINT8 ZELDA_HUD_3 = 0x03;
UINT8 ZELDA_HUD_4 = 0x04;
UINT8 ZELDA_HUD_5 = 0x05;
UINT8 ZELDA_HUD_6 = 0x06;
UINT8 ZELDA_HUD_7 = 0x07;
UINT8 ZELDA_HUD_8 = 0x08;
UINT8 ZELDA_HUD_9 = 0x09;
UINT8 ZELDA_HUD_0 = 0x0A;
UINT8 ZELDA_HUD_RUPEE = 0x0B;
UINT8 ZELDA_HUD_HEART_EMPTY = 0x0C;
UINT8 ZELDA_HUD_HEART_HALF = 0x0D;
UINT8 ZELDA_HUD_HEART_FULL = 0x0E;

UINT8 GetNumberTile(UINT8 number)
{
    switch (number)
    {
    case 0:
        return ZELDA_HUD_0;
        break;
    case 1:
        return ZELDA_HUD_1;
        break;
    case 2:
        return ZELDA_HUD_2;
        break;
    case 3:
        return ZELDA_HUD_3;
        break;
    case 4:
        return ZELDA_HUD_4;
        break;
    case 5:
        return ZELDA_HUD_5;
        break;
    case 6:
        return ZELDA_HUD_6;
        break;
    case 7:
        return ZELDA_HUD_7;
        break;
    case 8:
        return ZELDA_HUD_8;
        break;
    case 9:
        return ZELDA_HUD_9;
        break;

    default:
        return ZELDA_HUD_BLANK;
        break;
    }
}

void CalculateRupees(char *hud, UINT8 rupees)
{
    UINT8 count = 1;
    while (rupees > 0)
    {
        UINT8 digit = rupees % 10;
        // set the hundreds
        if (count == 3)
        {
            hud[2] = GetNumberTile(digit);
        }
        // set the tens
        if (count == 2)
        {
            hud[3] = GetNumberTile(digit);
        }
        // set the units
        if (count == 1)
        {
            hud[4] = GetNumberTile(digit);
        }

        rupees /= 10;
        count++;
    }
}

void CalculateHearts(char *hud, UINT8 maxHearts, UINT8 health)
{
    // max hearts is 14
    // max health is 28 (2 half hearts)
    UINT8 healthCounter = health;
    UINT8 startDraw = HEART_START_DRAW - maxHearts + 3;

    for (UINT8 i = 6; i < 19; i++)
    {
        if (i < startDraw)
        {
            hud[i] = ZELDA_HUD_BLANK;
        }
        else if (healthCounter > 2)
        {
            hud[i] = ZELDA_HUD_HEART_FULL;
            healthCounter -= 2;
            continue;
        }
        else if (healthCounter == 2)
        {
            hud[i] = ZELDA_HUD_HEART_FULL;
            healthCounter -= 2;
            continue;
        }
        else if (healthCounter == 1)
        {
            hud[i] = ZELDA_HUD_HEART_HALF;
            healthCounter--;
            continue;
        }
        else
        {
            hud[i] = ZELDA_HUD_HEART_EMPTY;
        }
    }

    // special case for last heart as we nornally leave the last tile empty
    if (maxHearts == 14)
    {
        if (health == 28)
        {
            hud[19] = ZELDA_HUD_HEART_FULL;
        }
        else if (health == 27)
        {
            hud[19] = ZELDA_HUD_HEART_HALF;
        }
        else
        {
            hud[19] = ZELDA_HUD_HEART_EMPTY;
        }
    }
    else
    {
        hud[19] = ZELDA_HUD_BLANK;
    }
}

void findTilesInVram()
{
    const unsigned char white[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    const unsigned char black[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    const unsigned char three[16] = {0x00, 0x00, 0x3C, 0x3C, 0x66, 0x66, 0x0C, 0x0C, 0x06, 0x06, 0x66, 0x66, 0x3C, 0x3C, 0x00, 0x00};

    //https://gbdev.gg8.se/wiki/articles/Video_Display#VRAM_Tile_Data
    // bank 3: bg tile data range $9000-97ff;

    // if a tile is defined like this:
    //      unsigned char *someTile = (unsigned char *)0x9000;
    // the adjecent tile can be referenced in 2 ways (creating a variable or inline):
    //      unsigned char *nextTile = someTile + 0x0001;
    //      *(someTile + 0x0001)

    // unsigned char *tile[16] = {
    //     (unsigned char *)0x9000, (unsigned char *)0x9001, (unsigned char *)0x9002, (unsigned char *)0x9003,
    //     (unsigned char *)0x9004, (unsigned char *)0x9005, (unsigned char *)0x9006, (unsigned char *)0x9007,
    //     (unsigned char *)0x9008, (unsigned char *)0x9009, (unsigned char *)0x900a, (unsigned char *)0x900b,
    //     (unsigned char *)0x900c, (unsigned char *)0x900d, (unsigned char *)0x900e, (unsigned char *)0x900f};

    unsigned char *tileMemoryStart = (unsigned char *)0x9000;
    unsigned char *tileMemoryEnd = (unsigned char *)0x9010;

    // *(tileMemoryStart + 0x000f) = black[0];
    // *(tileMemoryStart + 0x000e) = black[0];
    // *(tileMemoryStart + 0x000d) = black[0];
    // *(tileMemoryStart + 0x000c) = black[0];
    // *(tileMemoryStart + 0x000b) = black[0];
    // *(tileMemoryStart + 0x000a) = black[0];
    // *(tileMemoryStart + 0x0009) = black[0];
    // *(tileMemoryStart + 0x0008) = black[0];
    // *(tileMemoryStart + 0x0007) = black[0];
    // *(tileMemoryStart + 0x0006) = black[0];
    // *(tileMemoryStart + 0x0005) = black[0];
    // *(tileMemoryStart + 0x0004) = black[0];
    // *(tileMemoryStart + 0x0003) = black[0];
    // *(tileMemoryStart + 0x0002) = black[0];
    // *(tileMemoryStart + 0x0001) = black[0];
    // *tileMemoryStart = black[0];

    if (*tileMemoryStart == white[0] && *(tileMemoryStart + 0x0001) == white[1])
    {
        // match
        *tileMemoryStart = black[0];
    }







    // while(tileMemoryStart < tileMemoryEnd) {

    //     tileMemoryStart += 0x0010;
    // }
}

void CalculateHud(char *hud, UINT8 rupees, UINT8 maxHearts, UINT8 health)
{
    findTilesInVram();
    // set the rupee count
    CalculateRupees(hud, rupees);

    // set the hearts
    CalculateHearts(hud, maxHearts, health);
}
