#include <gb/gb.h>
#include <stdio.h>

void main()
{
    // these registers must be in this specific order!
    NR52_REG = 0x80; // turn on sound
    NR50_REG = 0x77; // sets the left and right channels to max volume
    NR51_REG = 0xff; // use all channels

    while (1)
    {
        UBYTE joypad_state = joypad();

        if (joypad_state)
        {
            NR41_REG = 0x1f;
            NR42_REG = 0xf1;
            NR43_REG = 0x30;
            NR44_REG = 0xc0;

            delay(1000);
        }
    }
}
