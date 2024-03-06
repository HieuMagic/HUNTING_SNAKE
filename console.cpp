#include "console.h"

void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void DisableCtrButton(bool Close, bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}
void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
void resizeConsole(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);
    MoveWindow(console, rect.left, rect.top, width, height, TRUE);
}
void gotoXY(int x, int y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x - 1, y - 1 };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void GetConsoleSize(int& width, int& height) {
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
}
void setConsoleTextColor(int color) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}
void setConsoleTextColor(int background, int text) {
    int color = (background << 4) | text;
    setConsoleTextColor(color);
}
void getCursorPosition(int& x, int& y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    x = csbi.dwCursorPosition.X;
    y = csbi.dwCursorPosition.Y;
}
void setCursorColor(int color)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);

    cursorInfo.bVisible = TRUE;
    cursorInfo.dwSize = 100;

    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void setCursorSize(int size) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = TRUE;
    Info.dwSize = size;
    SetConsoleCursorInfo(consoleHandle, &Info);
}
void Nonecursortype()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void setFontSize(int height = FONT_SIZE, int width = FONT_SIZE)
{
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = width;
    fontInfo.dwFontSize.Y = height; 
        fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);
}
void setConsoleTitle(const char* title)
{
    SetConsoleTitleA(title);
}
void setConsoleIcon(const char* iconPath)
{
    HWND console = GetConsoleWindow();
    HICON icon = (HICON)LoadImageA(NULL, iconPath, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    SendMessageA(console, WM_SETICON, ICON_SMALL, (LPARAM)icon);
    SendMessageA(console, WM_SETICON, ICON_BIG, (LPARAM)icon);
}
void DisableSelection()
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hOutput, &prev_mode);
    SetConsoleMode(hOutput, prev_mode | ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
}
void GetMousePosConsole(MOUSE_EVENT_RECORD mer, int& x, int& y)
{
    INPUT_RECORD Inrec;
    DWORD eventRead;
    HANDLE hStdIn;
    DWORD dwMode;
    bool Captured = false;

    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    dwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

    // Kiểm tra xem console đã ở chế độ chấp nhận input từ chuột chưa
    if (SetConsoleMode(hStdIn, dwMode | ENABLE_MOUSE_INPUT) == TRUE)
        GetConsoleMode(hStdIn, &dwMode);
    SetConsoleMode(hStdIn, (dwMode & (ENABLE_MOUSE_INPUT)));

    // Vòng lặp này sẽ lấy các event trong bộ nhớ ra để xử lý
    do
    {
        PeekConsoleInput(hStdIn, &Inrec, 1, &eventRead);
        if (eventRead)
        {
            ReadConsoleInput(hStdIn, &Inrec, 1, &eventRead);
            x = Inrec.Event.MouseEvent.dwMousePosition.X;
            y = Inrec.Event.MouseEvent.dwMousePosition.Y;
            if (Inrec.EventType == MOUSE_EVENT)
            {
                if (Inrec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    Captured = true;
                    break;
                }
            }
        }
    } while (!Captured);
}
//void GetMousePosConsole(int& x, int& y)
//{
//    HANDLE hStdin;
//    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//    COORD CursorPosition;
//    DWORD cNumRead, fdwMode, i;
//    INPUT_RECORD irInBuf[128];
//    int counter = 0;
//
//    // Get the standard input handle.
//    hStdin = GetStdHandle(STD_INPUT_HANDLE);
//    if (hStdin == INVALID_HANDLE_VALUE) {
//        //std::wcerr << " Error GetStdHandle";
//    }
//        
//
//    // Mở cửa sổ ở chế độ mở
//    fdwMode = ENABLE_EXTENDED_FLAGS;
//    if (!SetConsoleMode(hStdin, fdwMode)) {
//        //std::wcerr << "SetConsoleMode";
//    }
//
//    // Mở cửa sổ ở chế độ chấp nhận input
//    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
//    if (!SetConsoleMode(hStdin, fdwMode)) {
//        //std::wcerr << "SetConsoleMode";
//    }
//
//    // Vòng lặp để quét qua các event
//    while (!counter) {
//        // Đọc event vào
//        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
//            //std::wcerr << "ReadConsoleInput";
//        }
//
//        // Xử lý từng event một
//        for (i = 0; i < cNumRead; i++) {
//            
//            switch (irInBuf[i].EventType) {
//            case MOUSE_EVENT:
//                // Khi có event của chuột
//
//                GetMousePosConsole_Helps(irInBuf[i].Event.MouseEvent, x, y);
//                std::cout << "x: " << x << " y: " << y << std::endl;
//                break;
//                // Ngoài ra còn có event của bàn phím, của chuột
//            default:
//                break;
//            }
//        }
//    }
//}