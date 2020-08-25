#include <gb/gb.h>
#include <stdio.h>
#include "keyboardTiles.c"
#include "keyboardMap.c"
#include "CursorTile.c"
#include "cursor.c"

struct Cursor cursor;
UBYTE keydown;
const UINT8 mincursorx = 12;
const UINT8 mincursory = 80;
const UINT8 maxcursorx = 156;
const UINT8 maxcursory = 128;
UINT8 nameLength;
UINT8 name[18];
UBYTE finished;

void performantDelay(UINT8 numloops)
{
    UINT8 j;
    for (j = 0; j < numloops; j++)
    {
        wait_vbl_done();
    }
}

UBYTE isValidLocation(UINT8 x, UINT8 y)
{
    if (x == 140 && y == 144 || x == 156 && y == 144)
    {
        return 1;
    }

    return x >= mincursorx && x <= maxcursorx && y >= mincursory && y <= maxcursory;
}

void addName(struct Cursor *cursor)
{
    UINT8 charIndex = cursor->row * 10 + cursor->col + 1;

    if (nameLength == 18)
    {
        return;
    }

    name[nameLength] = charIndex;
    nameLength++;
}

void removeName()
{
    if (nameLength > 0)
    {
        nameLength--;
        name[nameLength] = 0;
    }
}

void drawName()
{
    set_bkg_tiles(1, 4, 18, 1, name);
}

void updateName(struct Cursor *cursor)
{
    if (cursor->col == 8 && cursor->row == 4)
    {
        //delete
        removeName();
        drawName();
    }
    else if (cursor->col == 9 && cursor->row == 4)
    {
        // finished
        finished = 1;
    }
    else
    {
        // add character to name
        addName(cursor);
        drawName();
    }
}

void main()
{
    set_sprite_data(0, 1, CursorSprite);
    set_sprite_tile(0, 0);

    cursor.x = 12;
    cursor.y = 80;
    cursor.col = 0;
    cursor.row = 0;
    move_sprite(0, cursor.x, cursor.y);

    set_bkg_data(0, 45, keyboard);
    set_bkg_tiles(0, 0, 20, 18, KeyboardMap);
    scroll_bkg(-4, 0);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (!finished)
    {
        if (keydown)
        {
            waitpadup();
            keydown = 0;
        }

        switch (joypad())
        {
        case J_UP:
            if (isValidLocation(cursor.x, cursor.y - 16))
            {
                cursor.y -= 16;
                cursor.row--;
                scroll_sprite(0, 0, -16);
                keydown = 1;
            }
            break;
        case J_DOWN:
            if (isValidLocation(cursor.x, cursor.y + 16))
            {
                cursor.y += 16;
                cursor.row++;
                scroll_sprite(0, 0, 16);
                keydown = 1;
            }
            break;
        case J_LEFT:
            if (isValidLocation(cursor.x - 16, cursor.y))
            {
                cursor.x -= 16;
                cursor.col--;
                scroll_sprite(0, -16, 0);
                keydown = 1;
            }
            break;
        case J_RIGHT:
            if (isValidLocation(cursor.x + 16, cursor.y))
            {
                cursor.x += 16;
                cursor.col++;
                scroll_sprite(0, 16, 0);
                keydown = 1;
            }
            break;
        case J_A:
            updateName(&cursor);
            keydown = 1;
            break;
        }

        performantDelay(2);
    }
}
