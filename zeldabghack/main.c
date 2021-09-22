#include <gb/gb.h>
#include <stdio.h>
#include "tileset.c"
#include "tilemap.c"
#include "../zeldahud/zeldahud.c"

void Left() {}
void Right() {
    unsigned char *test = (unsigned char *)0x9012;
    *test = 0x19;
}
void Up() {}
void Down() {
    findTilesInVram();
}

void main()
{
    // load the background tiles (vision henge scene)
    set_bkg_data(0, 48, mytileset);
    set_bkg_tiles(0, 0, 20, 18, mytilemap); // now that the windows tiles are loaded the vision henge tiles are pointing to the wrong tiles
    
    unsigned char zeldasAdventureHudMap[] = {0x00, 0x0B, 0x0A, 0x0A, 0x0A, 0x00, 0x0E,
                                           0x0E, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
                                           0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C};
    CalculateHud(zeldasAdventureHudMap, 123, 4, 3);
    set_bkg_tiles(0, 0, 20, 1, zeldasAdventureHudMap);
    
    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        wait_vbl_done();

        switch (joypad())
        {
        case J_LEFT:
            Left();
            break;
        case J_RIGHT:
            Right();
            break;
        case J_DOWN:
            Down();
            break;
        case J_UP:
            Up();
            break;
        }
    }
}

