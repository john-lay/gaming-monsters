#include <gb/gb.h>
#include <stdio.h>
#include "Zelda.c"
#include "Octorok.c"
#include "GameCharacter.c"

struct GameCharacter zelda;
struct GameCharacter octorok;
UBYTE spriteSize = 8;

void moveCharacter(struct GameCharacter *character, UINT8 x, UINT8 y)
{
    move_sprite(character->spriteIds[0], x, y);
    move_sprite(character->spriteIds[1], x + spriteSize, y);
    move_sprite(character->spriteIds[2], x, y + spriteSize);
    move_sprite(character->spriteIds[3], x + spriteSize, y + spriteSize);
}

void setupZelda()
{
    zelda.x = 80;
    zelda.y = 130;
    zelda.width = 16;
    zelda.height = 16;

    set_sprite_tile(0, 0);
    zelda.spriteIds[0] = 0;
    set_sprite_tile(1, 1);
    zelda.spriteIds[1] = 1;
    set_sprite_tile(2, 2);
    zelda.spriteIds[2] = 2;
    set_sprite_tile(3, 3);
    zelda.spriteIds[3] = 3;

    moveCharacter(&zelda, zelda.x, zelda.y);
}

void setupOctorok()
{
    octorok.x = 30;
    octorok.y = 0;
    octorok.width = 16;
    octorok.height = 16;

    set_sprite_tile(4, 4);
    octorok.spriteIds[0] = 4;
    set_sprite_tile(5, 5);
    octorok.spriteIds[1] = 5;
    set_sprite_tile(6, 6);
    octorok.spriteIds[2] = 6;
    set_sprite_tile(7, 7);
    octorok.spriteIds[3] = 7;

    moveCharacter(&octorok, octorok.x, octorok.y);
}

void performantDelay(UINT8 numloops)
{
    UINT8 i;
    for (i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

void main()
{
    set_sprite_data(0, 4, ZeldaSprite);
    set_sprite_data(4, 4, OctorokSprite);

    setupZelda();
    setupOctorok();

    SHOW_SPRITES;
    DISPLAY_ON;

    while (1)
    {
        if (joypad() & J_LEFT)
        {
            zelda.x -= 2;
            moveCharacter(&zelda, zelda.x, zelda.y);
        }
        if (joypad() & J_RIGHT)
        {
            zelda.x += 2;
            moveCharacter(&zelda, zelda.x, zelda.y);
        }

        octorok.y += 5;

        if (octorok.y >= 144)
        {
            octorok.y = 0;
            octorok.x = zelda.x;
        }

        moveCharacter(&octorok, octorok.x, octorok.y);

        performantDelay(5);
    }
}
