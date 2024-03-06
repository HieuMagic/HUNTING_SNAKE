#include "UI.h"
#include "console.h"
#include <conio.h>

#pragma comment(lib, "winmm.lib")

const char* GAME_TITLE = "HUNGTING SNAKE";
extern bool Playgame;


void soundtrack(bool& status)
{
    const char* filePath = "C:/Users/DELL/Downloads/musix.wav";
    PlaySoundA(filePath, NULL, SND_FILENAME | SND_ASYNC);
}

void soudplay(bool& status)
{
}

void Init()
{
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);// toàn màng hình
    DisableResizeWindow();// vô hiệu hóa nút resize console
    DisableCtrButton(false, false, false);// vô hiệu hóa nút close, minimize, maximize
    ShowScrollbar(FALSE);//ẩn thanh cuộn

}
void StartGame()
{

}
void EndGame()
{
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'q') 
            {
                Playgame = false;
                break;
            }
        }
    }
}
