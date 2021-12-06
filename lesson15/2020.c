#include <gb/gb.h>

#include <stdio.h>
#include <string.h>

void set_RAM_bank1(void) nonbanked preserves_regs(b, c, d, e) { SWITCH_RAM_MBC1(0); }
addressmod set_RAM_bank1 DATA_1;

void set_RAM_bank2(void) nonbanked preserves_regs(b, c, d, e) { SWITCH_RAM_MBC1(1); }
addressmod set_RAM_bank2 DATA_2;

DATA_2 int highscores[5];
DATA_2 unsigned char names[5][10];

int highscore;
unsigned char name[10];

void main() {
    ENABLE_RAM_MBC1;
    SWITCH_4_32_MODE_MBC1;

    // load score
    highscore = highscores[0];
    for (UBYTE i = 0; i < 10; i++) name[i] = names[0][i];

    if (strcmp(name, "test") != 0) {
        // if score table is not initialized set default
        strcpy(name, "test"), highscore = 1;
    } else {
        // else increase score
        highscore++;
    }

    // save score
    highscores[0] = highscore;
    for (UBYTE i = 0; i < 10; i++)  names[0][i] = name[i];

    // print the score
    printf("name: %s score: %d", name, highscore);
}
