#include <gb/gb.h>
#include <stdio.h>
#include "../lesson8/LinkSprite.c"
#include "MazeSprites.c"
#include "MazeMap.c"

UINT8 playerlocation[2];
const unsigned char blankMap[1] = {0x00};
UBYTE debug, hasKey, gameRunning;

void performantDelay(UINT8 numloops)
{
    UINT8 i;
    for (i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

UBYTE canLinkMove(UINT8 desiredX, UINT8 desiredY)
{
    UINT16 topLeftX, topLeftY, tileIndex;
    UINT16 keyPos = 321;
    UINT16 doorPos = 263;
    UINT16 endPos = 340;

    topLeftX = (desiredX - 8) / 8;
    topLeftY = (desiredY - 16) / 8;
    tileIndex = (20 * topLeftY) + topLeftX;

    if (debug)
    {
        printf("%u %u\n", (UINT16)(desiredX), (UINT16)(desiredY));
        printf("%u %u %u\n", (UINT16)(topLeftX), (UINT16)(topLeftY), (UINT16)(tileIndex));
    }

    if (tileIndex == keyPos)
    {
        // collect key
        set_bkg_tiles(1, 16, 1, 1, blankMap);
        hasKey = 1;
        return 1;
    }
    else if (tileIndex == doorPos && hasKey)
    {
        // open door
        set_bkg_tiles(3, 13, 1, 1, blankMap);
        return 1;
    }
    else if (tileIndex == endPos)
    {
        gameRunning = 0;
        HIDE_SPRITES;
        printf("\n \n \n \n \n \n \n \n \n      YOU WIN!");
        return 1;
    }

    return MazeMap[tileIndex] == blankMap[0];
}

void animateSprite(UINT8 spriteIndex, INT8 x, INT8 y)
{
    while (x != 0)
    {
        scroll_sprite(spriteIndex, x < 0 ? -1 : 1, 0);
        x += (x < 0 ? 1 : -1);
        wait_vbl_done;
    }
    while (y != 0)
    {
        scroll_sprite(spriteIndex, 0, y < 0 ? -1 : 1);
        y += (y < 0 ? 1 : -1);
        wait_vbl_done;
    }
}

void main()
{
    set_bkg_data(0, 4, MazeSprites);
    set_bkg_tiles(0, 0, 20, 18, MazeMap);

    set_sprite_data(0, 1, linkSprite);
    set_sprite_tile(0, 0);

    playerlocation[0] = 16;
    playerlocation[1] = 24;

    move_sprite(0, playerlocation[0], playerlocation[1]);

    gameRunning = 1;

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while (gameRunning)
    {
        if (joypad() & J_A)
        {
            debug = 1;
        }
        if (joypad() & J_LEFT)
        {
            if (canLinkMove(playerlocation[0] - 8, playerlocation[1]))
            {
                playerlocation[0] -= 8;
                animateSprite(0, -8, 0);
            }
        }
        if (joypad() & J_RIGHT)
        {
            if (canLinkMove(playerlocation[0] + 8, playerlocation[1]))
            {
                playerlocation[0] += 8;
                animateSprite(0, 8, 0);
            }
        }
        if (joypad() & J_UP)
        {
            if (canLinkMove(playerlocation[0], playerlocation[1] - 8))
            {
                playerlocation[1] -= 8;
                animateSprite(0, 0, -8);
            }
        }
        if (joypad() & J_DOWN)
        {
            if (canLinkMove(playerlocation[0], playerlocation[1] + 8))
            {
                playerlocation[1] += 8;
                animateSprite(0, 0, 8);
            }
        }

        performantDelay(6);
    }
}
