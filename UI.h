#pragma once
#ifndef _MY_UI
#define _MY_UI

void soundTrack(bool& status);
void soudPlay(bool& status);
void fillFullScreen(int color);
void button(int colorBackgroud, int colorText, const char* text, int wight, int height);
void init();
void startGame();
void endGame();


#endif // !_MY_UI