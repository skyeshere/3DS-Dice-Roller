#include <3ds.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <cstring>


/*                             D4 D6 D8 D10 D12 D20     */
const short int die_types[6] = {4, 6, 8, 10, 12, 20};
const short int max_current = (sizeof(die_types) / sizeof(die_types[0])) - 1 ; //size of array taken like this because of array decay
const short int min_current = 0;

int current_die = 0;

//draw selection to top screen
void drawTopScreen(PrintConsole screen, int selected, bool debug)
{
    consoleSelect(&screen);
    consoleClear(); //clear screen for new frame
    printf("\x1b[1;1HWelcome to the Dice Roller! Select with D-UP/DOWN\n\n");
    printf("Current Die: D%d\n", die_types[selected]);
    printf("Press A to roll!\n");

    if(debug)
    {
        printf("\n<-- DEBUG VARIABLE WATCH -->\n");

        printf("die_types: {");
        for (int i : die_types)
        {
            printf("%d, ", i);
        }
        printf("}\n");

        printf("short int selected: %d\n", selected);
        printf("max_current: %d\n", max_current);
    }

    printf("\x1b[30;1HPress SELECT to exit");
}

//draw result on bottom 3ds screen
void drawBotScreen(PrintConsole screen, int result)
{
	//this is very jank and most likely very unsafe lol
	consoleSelect(&screen);
	consoleClear(); //clear screen for new frame
	std::string res_string = "";
	if (result <= 9)
	{
		res_string = "0" + std::to_string(result);
	}
	else
	{
		res_string = std::to_string(result);
	}

	char strbuf[60];
	std::strncpy(strbuf, res_string.c_str(), sizeof(res_string));
	strbuf[sizeof(res_string) - 1] = 0;

	printf("You rolled a: %d\n", result);
	printf("       -----\n");
	printf("   ---/  |  \\---\n");
	printf("  /      |      \\\n");
	printf(" /-------+-------\\\n");
	printf("/\\      / \\      /\\\n");
	printf("| \\    /%s \\    / |\n", strbuf);
	printf("|  \\  /     \\  /  |\n");
	printf("|   /---------\\   |\n");
	printf("|  /  \\     /  \\  |\n");
	printf(" \\/    \\   /    \\/\n");
	printf("  \\-    \\ /    -/\n");
	printf("    \\----+----/\n");
}

int main()
{
    gfxInitDefault();

    bool debug_mode = false;

    srand(time(0));

    PrintConsole topScreen, bottomScreen;

    //initialise both screens for printing
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);


    //initial draw to top screen
    drawTopScreen(topScreen, current_die, debug_mode);

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
            if (current_die >= max_current)
            {
                current_die = min_current;
            } else
            {
                current_die++;
            }

            drawTopScreen(topScreen, current_die, debug_mode);
        }

        if (hidKeysDown() & KEY_DDOWN)
        {
            //roll around to max of the selction
            if (current_die <= min_current)
            {
                current_die = max_current;
            } else 
            {
                current_die--;
            }

            drawTopScreen(topScreen, current_die, debug_mode);
        }

        /* Roll the die */
        if (hidKeysDown() & KEY_A)
        {
        	short int random = (std::rand() % die_types[current_die]) + 1;
        	drawBotScreen(bottomScreen, random);
        }

        if (hidKeysDown() & KEY_ZL)
        {
            if(debug_mode)
            {
                debug_mode = false;
            }
            else
            {
                debug_mode = true;
            }
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}