#include <gb/gb.h>
#include "checkerTile.c"

UINT8 *beginSpriteMem = (UINT8 *)0x8000;
UINT8 checkerTileIndex = 16;

void LookUpTile()
{
    for(UINT8 i = 0; i < 128; i+=16)
    {
    if (*(beginSpriteMem + i) == CheckerTile[checkerTileIndex] 
        && *(beginSpriteMem + i + 1) == CheckerTile[checkerTileIndex + 1]
        && *(beginSpriteMem + i + 2) == CheckerTile[checkerTileIndex + 2]
        && *(beginSpriteMem + i + 3) == CheckerTile[checkerTileIndex + 3]
        && *(beginSpriteMem + i + 4) == CheckerTile[checkerTileIndex + 4]
        && *(beginSpriteMem + i + 5) == CheckerTile[checkerTileIndex + 5]
        && *(beginSpriteMem + i + 6) == CheckerTile[checkerTileIndex + 6]
        && *(beginSpriteMem + i + 7) == CheckerTile[checkerTileIndex + 7])
    {
        *beginSpriteMem = 0xa0;
    }
    
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
