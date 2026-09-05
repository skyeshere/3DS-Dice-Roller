#include <3ds.h>
#include <cstdio>
#include <cstdlib>
#include <string>

//i just think this is funny tbh, 0 -> 2**8.  this saves memory surely!!
unsigned short int range = 0;

//possible add an ASCII esque rolling animation for D20 rolls
void dTwentyAnim()
{
    /*
        possible run of this method would be:
        clearconsole ->
        print frame 1 ->
        clear console ->
        print frame 2 ->
        clear console ->
        print result

        Maybe use bottom screen?
    */
}

//possible add an ASCII esque rolling animatio for D6 rolls
void dSixAnim()
{

}

void initPrint()
{
    printf("Dice Roller!\n");
    printf("Press X for D6 or Y for D20\n");
    printf("Press A to roll!\n");
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

    //print init top screen content
    consoleSelect(&topScreen);
    initPrint();


    //select to print to bottom screen
    consoleSelect(&bottomScreen);
    printf("Press START to exit at any time\n");

    consoleSelect(&topScreen);

    while (aptMainLoop())
    {
        hidScanInput();

        if (hidKeysDown() & KEY_START)
            break;

        if (hidKeysDown() & KEY_X)
        {
            //option choice roll D6
            range = 5;
            printChoice(range);
        }

        if (hidKeysDown() & KEY_Y)
        {
            //option choice roll D20
            range = 19;
            printChoice(range);
        }

        if (hidKeysDown() & KEY_A)
        {
            if (range != 0) //if a range is selected...
            {
                unsigned short int random = (std::rand() % range) + 1; //random generated 0 - 19 add one to make it 1 - 20 (D20) //another funny unsigned short int :3
                printf("you rolled: %d\n", random);
            }else //else a range isnt selected
            {
                printf("Please choose a die to roll!\n");
            }
            
        }

        if (hidKeysDown() & KEY_L)
        {
            //clear screen debug
            consoleClear();
            consoleSelect(&topScreen);
            initPrint();
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
