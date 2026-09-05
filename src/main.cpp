#include <3ds.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>


// map <int index, int range>
/*                                 D4      D6      D8      D10     D12      D20     */
std::map<int, int> die_types = { {0, 4}, {1, 6}, {2, 8}, {3, 10}, {4, 12}, {5, 20} };
int max_current = die_types.size() - 1; 
int min_current = 0;

int current_die = 0;


void drawTopScreen(PrintConsole screen, int selected)
{
    consoleSelect(&screen);
    consoleClear();
    printf("Dice Roller!\n");
    printf("Current Die: D%d\n", die_types.at(selected));
    printf("Press A to roll!\n");
}

void drawBotScreen(PrintConsole screen, int result)
{
	consoleSelect(&screen);
	consoleClear();
	printf("You rolled: %d\n", result);
}

void printChoice(int r)
{
    printf("You chose: D%d\n", r + 1);
}


int main()
{
    gfxInitDefault();
    srand(time(0));

    PrintConsole topScreen, bottomScreen;

    //initialise both screens for printing
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);

    drawTopScreen(topScreen, current_die);

    while (aptMainLoop())
    {
        hidScanInput();

        /* exit program */
        if (hidKeysDown() & KEY_START)
            break;

        /* selecting die */
        if (hidKeysDown() & KEY_DUP)
        {
            //roll around to min of the selction
            if (current_die == max_current)
            {
                current_die = min_current;
            } else
            {
                current_die++;
            }

            drawTopScreen(topScreen, current_die);
        }

        if (hidKeysDown() & KEY_DDOWN)
        {
            //roll around to max of the selction
            if (current_die == min_current)
            {
                current_die = max_current;
            } else 
            {
                current_die--;
            }

            drawTopScreen(topScreen, current_die);
        }

        /* Roll the die */
        if (hidKeysDown() & KEY_A)
        {
        	short int random = (std::rand() % die_types.at(current_die)) + 1;
        	drawBotScreen(bottomScreen, random);
        }


        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
