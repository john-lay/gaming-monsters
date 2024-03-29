#include <gb/gb.h>
#include <stdio.h>
#include "zeldaTiles.c"
#include "zeldaMap.c"
#include "tileset.c"
#include "tilemap.c"
#include "zeldaHud.c"

BYTE healthChanged = 0;
BYTE heartsChanged = 0;

// https://github.com/chrismaltby/gb-studio/issues/540
// _script_variables are listed at memory location CC40
// variable $00$ is at 0xCCBA
int cachedHealth = 3;
int *health = (int *)0xCCBA;
int cachedMaxHearts = 4;
int maxHearts = 4;

void interruptLCD()
{
    HIDE_WIN;
    if (healthChanged || heartsChanged)
    {
        cachedHealth = *health;
        cachedMaxHearts = maxHearts;
        healthChanged = 0;
        heartsChanged = 0;
        CalculateHud(zeldaMap, 321, maxHearts, *health);
        set_win_tiles(0, 0, 20, 1, zeldaMap);
    }
}

void incrementHealth()
{
    if (!healthChanged)
    {
        healthChanged = 1;
        *health = 4;
    }
}

void decrementHealth()
{
    if (!healthChanged)
    {
        healthChanged = 1;
        *health = 3;
    }
}

void incrementMaxHearts()
{
    if (!heartsChanged)
    {
        heartsChanged = 1;
        maxHearts = 5;
    }
}

void decrementMaxHearts()
{
    if (!heartsChanged)
    {
        heartsChanged = 1;
        maxHearts = 4;
    }
}

void main()
{

    // load the windows tiles (rupee + hearts HUD)
    int numHudTiles = 15;
    set_bkg_data(0, numHudTiles, zeldaTiles); // there are 15 tiles in the HUD tile set
    // set_win_tiles(0, 0, 20, 1, zeldaMap);

    CalculateHud(zeldaMap, 321, 4, 3);

    set_win_tiles(0, 0, 20, 1, zeldaMap);

    // shift tile set
    // size of tile map = 360;
    // unsigned char modTilemap[360] = {0};
    // for (int i = 0; i <= sizeof(mytilemap); i++)
    // {
    //     modTilemap[i] = mytilemap[i] + 0xf;
    // }
    // the above should work, but doesn't. Working code from online scratch pad:
    // https://cplayground.com/?p=boar-pig-walrus
    const unsigned char modTilemap[] = {0xf, 0x10, 0x11, 0x11, 0x11, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x12, 0x12, 0x12, 0xf, 0xf, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0xf, 0x13, 0x14, 0x15, 0x16, 0x17, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0x13, 0xf, 0x18, 0x19, 0x1a, 0x1b, 0x13, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xf, 0x14, 0x15, 0x16, 0x17, 0x13, 0xf, 0xf, 0x13, 0x1d, 0x1e, 0x1f, 0x20, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x18, 0x19, 0x1a, 0x1b, 0xf, 0x13, 0x13, 0xf, 0x21, 0x22, 0x23, 0x24, 0x1c, 0x25, 0x26, 0x26, 0x26, 0x26, 0x27, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x13, 0xf, 0xf, 0x13, 0xf, 0x13, 0x1c, 0x1c, 0x25, 0x28, 0x29, 0x2a, 0x2a, 0x2a, 0x2b, 0x27, 0x21, 0x22, 0x23, 0x24, 0xf, 0x13, 0x13, 0xf, 0x13, 0xf, 0x1c, 0x1c, 0x2c, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x29, 0x2c, 0x1c, 0x1c, 0x13, 0xf, 0x13, 0xf, 0xf, 0x13, 0xf, 0x13, 0x1c, 0x1c, 0x2c, 0x2a, 0x2a, 0x29, 0x2a, 0x2a, 0x2a, 0x2c, 0x1c, 0x1c, 0xf, 0x13, 0xf, 0x13, 0x13, 0xf, 0x13, 0xf, 0x1c, 0x1c, 0x2c, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2c, 0x1c, 0x1c, 0x13, 0xf, 0x13, 0xf, 0xf, 0x13, 0xf, 0x13, 0x1c, 0x1c, 0x2b, 0x27, 0x2a, 0x2a, 0x2a, 0x2a, 0x25, 0x28, 0x1c, 0x1c, 0xf, 0x13, 0xf, 0x13, 0x13, 0xf, 0x13, 0xf, 0x1c, 0x1c, 0x1c, 0x2d, 0x2e, 0x2e, 0x2e, 0x2e, 0x2d, 0x1c, 0x1c, 0x1c, 0x13, 0xf, 0x13, 0xf, 0xf, 0x13, 0xf, 0x13, 0xf, 0x1c, 0x1c, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x1c, 0x1c, 0x13, 0xf, 0x13, 0xf, 0x13, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf, 0x13, 0xf};

    // load the background tiles (vision henge scene)
    set_bkg_data(numHudTiles, 32, mytileset);
    // set_bkg_tiles(0, 0, 20, 18, mytilemap); // now that the windows tiles are loaded the vision henge tiles are pointing to the wrong tiles
    set_bkg_tiles(0, 0, 20, 18, modTilemap); // point to the shifted tiles instead

    // Inspired by https://gbdev.gg8.se/forums/viewtopic.php?id=345
    STAT_REG = 0x45;
    LYC_REG = 0x08; //  Fire LCD Interupt on the 8th scan line

    disable_interrupts();

    SHOW_WIN;
    SHOW_BKG;
    // DISPLAY_ON;

    add_LCD(interruptLCD);
    enable_interrupts();

    set_interrupts(VBL_IFLAG | LCD_IFLAG);

    while (1)
    {
        SHOW_WIN;
        wait_vbl_done();

        switch (joypad())
        {
        case J_LEFT:
            decrementHealth();
            break;
        case J_RIGHT:
            incrementHealth();
            break;
        case J_DOWN:
            decrementMaxHearts();
            break;
        case J_UP:
            incrementMaxHearts();
            break;
        }
    }
}
