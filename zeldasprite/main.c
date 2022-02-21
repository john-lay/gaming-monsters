#include <gb/gb.h>
#include "checkerTile.c"

UINT8 *beginSpriteMem = (UINT8 *)0x8000;

void LookUpTile()
{
    if (*beginSpriteMem == CheckerTile[0] &&
        *(beginSpriteMem + 0x0001) == CheckerTile[1])
    {
        *beginSpriteMem = 0xa0;
    }

    HIDE_SPRITES;
    SHOW_SPRITES;
}

void main()
{
    set_sprite_data(0, 3, CheckerTile);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1)
    {
        switch (joypad())
        {
        case J_LEFT:
            delay(100);
            break;
        case J_RIGHT:
            delay(100);
            break;
        case J_UP:
            LookUpTile();
            delay(100);
            break;
        case J_DOWN:
            delay(100);
            break;
        }
    }
}
