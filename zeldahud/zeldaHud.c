#include "zeldaHud.h"

const int HEART_START_DRAW = 16;

int GetNumberTile(int number)
{
    switch (number)
    {
    case 0:
        return ZELDA_HUD_0;
        break;
    case 1:
        return ZELDA_HUD_1;
        break;
    case 2:
        return ZELDA_HUD_2;
        break;
    case 3:
        return ZELDA_HUD_3;
        break;
    case 4:
        return ZELDA_HUD_4;
        break;
    case 5:
        return ZELDA_HUD_5;
        break;
    case 6:
        return ZELDA_HUD_6;
        break;
    case 7:
        return ZELDA_HUD_7;
        break;
    case 8:
        return ZELDA_HUD_8;
        break;
    case 9:
        return ZELDA_HUD_9;
        break;

    default:
        return ZELDA_HUD_BLANK;
        break;
    }
}

void CalculateRupees(char *hud, int rupees)
{
    int count = 1;
    while (rupees > 0)
    {
        int digit = rupees % 10;
        // set the hundreds
        if (count == 3)
        {
            hud[2] = GetNumberTile(digit);
        }
        // set the tens
        if (count == 2)
        {
            hud[3] = GetNumberTile(digit);
        }
        // set the units
        if (count == 1)
        {
            hud[4] = GetNumberTile(digit);
        }

        rupees /= 10;
        count++;
    }
}

void CalculateHearts(char *hud, int maxHearts, int health)
{
    // max hearts is 14
    // max health is 28 (2 half hearts)
    int healthCounter = health;
    int startDraw = HEART_START_DRAW - maxHearts + 3;

    for (int i = 6; i < 19; i++)
    {
        if (i < startDraw)
        {
            hud[i] = ZELDA_HUD_BLANK;
        }
        else if (healthCounter > 2)
        {
            hud[i] = ZELDA_HUD_HEART_FULL;
            healthCounter -= 2;
            continue;
        }
        else if (healthCounter == 2)
        {
            hud[i] = ZELDA_HUD_HEART_FULL;
            healthCounter -= 2;
            continue;
        }
        else if (healthCounter == 1)
        {
            hud[i] = ZELDA_HUD_HEART_HALF;
            healthCounter--;
            continue;
        }
        else
        {
            hud[i] = ZELDA_HUD_HEART_EMPTY;
        }
    }

    // special case for last heart as we nornally leave the last tile empty
    if (maxHearts == 14)
    {
        if (health == 28)
        {
            hud[19] = ZELDA_HUD_HEART_FULL;
        }
        else if (health == 27)
        {
            hud[19] = ZELDA_HUD_HEART_HALF;
        }
        else
        {
            hud[19] = ZELDA_HUD_HEART_EMPTY;
        }
    }
    else
    {
        hud[19] = ZELDA_HUD_BLANK;
    }
}

void CalculateHud(char *hud, int rupees, int maxHearts, int health)
{

    // set the rupee count
    CalculateRupees(hud, rupees);

    // set the hearts
    CalculateHearts(hud, maxHearts, health);
}
