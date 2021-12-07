#include <gb/gb.h>
#include "tileset.c"
#include "tilemap.c"

UBYTE hasScrolledLeft = 0;

void ScrollLeft()
{
    if (!hasScrolledLeft)
    {
        // replace the firestorm with the shield
        unsigned char shieldMap[] = {0x34, 0x35, 0x3E, 0x3F};        
        set_bkg_tiles(4, 11, 2, 2, shieldMap);

        hasScrolledLeft = 1;
    }
}

void ScrollRight()
{
    if (hasScrolledLeft)
    {
        // replace the shield with the firestorm
        unsigned char firestormMap[] = {0x30,0x31, 0x3A,0x3B};      
        set_bkg_tiles(4, 11, 2, 2, firestormMap);

        hasScrolledLeft = 0;
    }
    
}

void main()
{
    set_bkg_data(0, 73, mytileset);
    set_bkg_tiles(0, 0, 20, 18, mytilemap);

    SHOW_BKG;
    DISPLAY_ON;

    // change the first 2 tiles of the firestorm to the shield
    // unsigned char topShieldMap[] = {0x34, 0x35};
    // set_bkg_tiles(4, 11, 2, 1, topShieldMap);

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        // scroll_bkg(1, 0);
        // deay(100);

        switch (joypad())
        {
        case J_LEFT:
            ScrollLeft();
            break;
        case J_RIGHT:
            ScrollRight();
            break;
        }
    }
}
