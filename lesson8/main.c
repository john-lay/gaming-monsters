#include <gb/gb.h>
#include <stdio.h>
#include "LinkSprite.c"
#include "main.h"

INT8 playerLocation[2]; // store x and y position
BYTE jumping;
UINT8 gravity = -2;
UINT8 currentSpeedY;
UINT8 floorY = 100;

void main()
{
    set_sprite_data(0, 8, linkSprite);
    set_sprite_tile(0, 0);

    playerLocation[0] = 10;
    playerLocation[1] = floorY;
    jumping = 0;

    move_sprite(0, playerLocation[0], playerLocation[1]);

    DISPLAY_ON;
    SHOW_SPRITES;

    while (1)
    {
        if (joypad() & J_LEFT)
        {
            playerLocation[0] = playerLocation[0] - 2;
            move_sprite(0, playerLocation[0], playerLocation[1]);
        }
        if (joypad() & J_RIGHT)
        {
            playerLocation[0] = playerLocation[0] + 2;
            move_sprite(0, playerLocation[0], playerLocation[1]);
        }
        if ((joypad() & J_A) || jumping == 1)
        {
            jump(0, playerLocation);
        }
        performantDelay(5);
    }
}

void performantDelay(UINT8 numloops)
{
    UINT8 i;
    for (i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

INT8 checkGroundCollision(UINT8 projectedY)
{
    if (projectedY >= floorY)
    {
        return floorY;
    }

    return -1;
}

void jump(UINT8 spriteId, UINT8 spriteLocation[2])
{
    INT8 maybeFloor;

    if (jumping == 0)
    {
        jumping = 1;
        currentSpeedY = 10;
    }

    currentSpeedY = currentSpeedY + gravity;

    spriteLocation[1] = spriteLocation[1] - currentSpeedY;
    maybeFloor = checkGroundCollision(spriteLocation[1]);

    if (maybeFloor > -1)
    {
        jumping = 0;
        move_sprite(spriteId, spriteLocation[0], floorY);
    }
    else
    {
        move_sprite(spriteId, spriteLocation[0], spriteLocation[1]);
    }
}
