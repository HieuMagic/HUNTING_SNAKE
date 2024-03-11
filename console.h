#pragma once
#ifndef _THE_CONSOLE
#define _THE_CONSOLE

#include <Windows.h>

const int FONT_SIZE = 20;

void disableResizeWindow();// vô hiệu hóa nút resize console
void disableCtrButton(bool Close, bool Min, bool Max);// vô hiệu hóa nút close, minimize, maximize
void showScrollbar(BOOL Show);//ẩn thanh cuộn
void resizeConsole(int width, int height);// thay đổi kích thước console
void gotoXY(int x, int y);// di chuyển con trỏ đến vị trí x, y
void setBackgroudAndText(int code);// thay đổi màu nền và màu chữ
//nếu code có dạng hecxa 0xnab thì a là màu nền, b là màu chữ
//n: 0-3 ko đổi, 4-7 kẻ ngang, 8-11 kẻ dọc, 12-15 kẻ caro
//hay n(0-15) << 8 | a << 4 | b hoặc n(0-3) << 10 | a << 4 | b
void setConsoleTextColor(int color);// thay đổi màu chữ
void setConsoleTextColor(int background, int text);// thay đổi màu nền và màu chữ
void setBackgroundColor(int color);// thay đổi màu nền
void getCursorPosition(int& x, int& y);// lấy tọa độ con trỏ
void setCursorColor(int color);// thay đổi màu con trỏ	
void setCursorSize(int size);// thay đổi kích thước con trỏ
void noneCursorType();// ẩn con trỏ
void setFontSize(int height, int width);// thay đổi kích thước font chữ
void setConsoleTitle(const char* title);// thay đổi tiêu đề console
void setConsoleIcon(const char* iconPath);// thay đổi icon console
void disableSelection();// vô hiệu hóa chọn text
void getMousePosConsole(MOUSE_EVENT_RECORD mer, int& x, int& y);// lấy vị trí chuột trên console
//void GetMousePosConsole(int& x, int& y);// lấy vị trí chuột trên console
//hàm GetMousePosWin lấy theo nguyên tắt 1 tọa độ là mạng lưới hàng và cột chứ ko tính theo pixel

#endif // !_THE_CONSOLE
