#include <gb/gb.h>
#include <stdio.h>
#include "tileset.c"
#include "tilemap.c"

void AnimateTile()
{
    // UINT8 *a = (UINT8 *)0x90f2;
    // UINT8 *b = (UINT8 *)0x91f2;
    // *a = *b;
    // *(UINT8 *)0x90f2 = *(UINT8 *)0x9102;

    *(UINT8 *)0x90f2 = *(UINT8 *)0x9102;

    UINT8 *tile1 = (UINT8 *)0x90f0;
    UINT8 *tile2 = (UINT8 *)0x9100;
    UINT8 *tile3 = (UINT8 *)0x9110;
    UINT8 *tile4 = (UINT8 *)0x9120;

    // step 0: 1 2 3 4
    // step 1: 2 1 3 4
    // step 2: 2 3 1 4
    // step 3: 2 3 4 1
    for(UINT8 i = 0; i < 16; i++)
    {
        // *(tile1 + i) = *(tile2 + i);

        // swap elements 0 and 1 (tile 1 and 2)
        *(tile1 + i) ^= *(tile2 + i);
        *(tile2 + i) ^= *(tile1 + i);
        *(tile1 + i) ^= *(tile2 + i);
    }

    // for(UINT8 i = 0; i < 16; i++)
    // {
    //    // swap elements 1 and 2 (tile 1 and 3)
    //     *(tile2 + i) ^= *(tile3 + i);
    //     *(tile3 + i) ^= *(tile2 + i);
    //     *(tile2 + i) ^= *(tile3 + i);
    // }

    // for(UINT8 i = 0; i < 16; i++)
    // {
    //     // swap elements 2 and 3 (tile 1 and 4)
    //     *(tile3 + i) ^= *(tile4 + i);
    //     *(tile4 + i) ^= *(tile3 + i);
    //     *(tile4 + i) ^= *(tile4 + i);
    // }
}

void main()
{
    set_bkg_data(0, 50, mytileset);
    set_bkg_tiles(0, 0, 20, 18, mytilemap);

    SHOW_BKG;
    DISPLAY_ON;

    

    while (1)
    {
        AnimateTile();
        delay(1000);

        // switch (joypad())
        // {
        // case J_LEFT:
        //     delay(100);
        //     break;
        // case J_RIGHT:
        //     delay(100);
        //     break;
        // case J_UP:
        //     LookUpTile();
        //     delay(100);
        //     break;
        // case J_DOWN:
        //     delay(100);
        //     break;
        // }
    }
}
