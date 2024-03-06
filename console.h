#pragma once
#ifndef _THE_CONSOLE
#define _THE_CONSOLE

#include <Windows.h>

const int FONT_SIZE = 20;

void DisableResizeWindow();// vô hiệu hóa nút resize console
void DisableCtrButton(bool Close, bool Min, bool Max);// vô hiệu hóa nút close, minimize, maximize
void ShowScrollbar(BOOL Show);//ẩn thanh cuộn
void resizeConsole(int width, int height);// thay đổi kích thước console
void gotoXY(int x, int y);// di chuyển con trỏ đến vị trí x, y
void setConsoleTextColor(int background, int text);// đổi màu chữ và nền
void getCursorPosition(int& x, int& y);// lấy tọa độ con trỏ
void setCursorColor(int color);// thay đổi màu con trỏ	
void setCursorSize(int size);// thay đổi kích thước con trỏ
void Nonecursortype();// ẩn con trỏ
void setFontSize(int height, int width);// thay đổi kích thước font chữ
void setConsoleTitle(const char* title);// thay đổi tiêu đề console
void setConsoleIcon(const char* iconPath);// thay đổi icon console
void DisableSelection();// vô hiệu hóa chọn text
void GetMousePosConsole(MOUSE_EVENT_RECORD mer, int& x, int& y);// lấy vị trí chuột trên console
//void GetMousePosConsole(int& x, int& y);// lấy vị trí chuột trên console
//hàm GetMousePosWin lấy theo nguyên tắt 1 tọa độ là mạng lưới hàng và cột chứ ko tính theo pixel

#endif // !_THE_CONSOLE
