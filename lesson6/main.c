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
            NR10_REG = 0x16;
            NR11_REG = 0x40;
            NR12_REG = 0x73;
            NR13_REG = 0x00;
            NR14_REG = 0xc3;

            delay(1000);
        }
    }
}
