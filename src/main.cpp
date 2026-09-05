#include <3ds.h>
#include <cstdio>
#include <random>

int main()
{
    gfxInitDefault();

    PrintConsole topScreen, bottomScreen;

    //initialise both screensn for printing
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);

    //currently selected screen
    consoleSelect(&topScreen);

    printf("Dice Roller!\n");

    consoleSelect(&bottomScreen);
    printf("Press START to exit\n");

    while (aptMainLoop())
    {
        hidScanInput();

        if (hidKeysDown() & KEY_START)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
