#include <gb/gb.h>
#include <stdio.h>
#include "zeldaTiles.c"
#include "zeldaMap.c"

void main() {
    set_bkg_data(0, 15, zeldaTiles);
    set_bkg_tiles(0, 0, 20, 1, zeldaMap);

    SHOW_BKG;
    DISPLAY_ON;
}
