#include <gb/gb.h>
#include <stdio.h>
#include "zeldaTiles.c"
#include "zeldaMap.c"
#include "tileset.c"
#include "tilemap.c"

void main() {
    // load the background tiles (vision henge scene)
    set_bkg_data(0, 32, mytileset); // there are 32 tiles 
    set_bkg_tiles(0, 0, 20, 18, mytilemap);

    // load the windows tiles
    // set_bkg_data(0, 15, zeldaTiles);
    // set_bkg_tiles(0, 0, 20, 1, zeldaMap);

    SHOW_BKG;
    DISPLAY_ON;
}
