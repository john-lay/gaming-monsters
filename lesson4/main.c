#include <gb/gb.h>
#include <stdio.h>
#include "../lesson2/ZeldaSprites.c"
#include "ZeldaMap.c"

void main()
{
    set_bkg_data(0, 7, Zelda);
    set_bkg_tiles(0, 0, 40, 18, ZeldaMap);

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        scroll_bkg(1, 0);
        delay(100);
    }
}
