#include <gb/gb.h>
#include <stdio.h>
#include "../lesson12/title_data.c"
#include "../lesson12/title_map.c"
#include "../lesson11/MazeSprites.c"
#include "../lesson11/MazeMap.c"

UINT8 i;

void performantDelay(UINT8 numloops)
{
    UINT8 j;
    for (j = 0; j < numloops; j++)
    {
        wait_vbl_done();
    }
}

void fadeout()
{
    for (i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            BGP_REG = 0xe4;
            break;
        case 1:
            BGP_REG = 0xf9;
            break;
        case 2:
            BGP_REG = 0xfe;
            break;
        case 3:
            BGP_REG = 0xff;
            break;
        }
        performantDelay(10);
    }
}

void fadein()
{
    for (i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            BGP_REG = 0xfe;
            break;
        case 1:
            BGP_REG = 0xf9;
            break;
        case 2:
            BGP_REG = 0xe4;
            break;
        }
        performantDelay(10);
    }
}

void main()
{
    set_bkg_data(0, 118, title_data);
    set_bkg_tiles(0, 0, 20, 18, title_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);

    fadeout();

    set_bkg_data(0, 4, MazeSprites);
    set_bkg_tiles(0, 0, 20, 18, MazeMap);

    fadein();
}
