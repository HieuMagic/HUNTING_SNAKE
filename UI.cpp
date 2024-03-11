#include "UI.h"
#include "console.h"
#include <conio.h>
#include <iostream>
//haha
#pragma comment(lib, "winmm.lib")

const char* GAME_TITLE = "HUNGTING SNAKE";
extern bool playing;


static void HUNTING_SNAKE()
{
    int x, y;
    x = 0; y = 0;
}
void soundTrack(bool& status)
{
    const char* filePath = "C:/Users/DELL/Downloads/musix.wav";
    PlaySoundA(filePath, NULL, SND_FILENAME | SND_ASYNC);
}
void soudPlay(bool& status)
{

}
void fillFullScreen(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
    
    setBackgroudAndText(color);
    for (int i = 0; i < consoleHeight; i++)
    {
        for (int j = 0; j < consoleWidth; j++)
        {
			std::cout << " ";
		}
	}
}

void init()
{
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);// toàn màng hình
    //DisableResizeWindow();// vô hiệu hóa nút resize console
    //DisableCtrButton(false, false, false);// vô hiệu hóa nút close, minimize, maximize
    //ShowScrollbar(FALSE);//ẩn thanh cuộn
}
void startGame()
{
    const int FONT_START = 20;

}
void endGame()
{
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'q') 
            {
                playing = false;
                break;
            }
        }
    }
}
