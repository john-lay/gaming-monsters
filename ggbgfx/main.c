#include <gb/gb.h>
#include <stdio.h>
#include "tileset.c"
#include "tilemap.c"

void main()
{
    set_bkg_data(0, 32, mytileset);
    set_bkg_tiles(0, 0, 20, 18, mytilemap);

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        scroll_bkg(1, 0);
        delay(100);
    }
}
