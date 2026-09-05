#include <3ds.h>
#include <cstdio>

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("Hello World\n");
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
