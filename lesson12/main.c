#include <gb/gb.h>
#include <stdio.h>
#include "title_data.c"
#include "title_map.c"

void main()
{
    set_bkg_data(0, 118, title_data);
    set_bkg_tiles(0, 0, 20, 18, title_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);

    printf("Start of my game");
}
