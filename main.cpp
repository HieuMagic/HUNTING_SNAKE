#include "console.h"
#include "UI.h"
#include "object.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>


bool playing;
bool playContinue;
std::string name;
int score;
double timePlay;
int level;

struct user
{
	std::string name;
	int score;
	double timePlay;
    user* next;
    user()
    {
        next = nullptr;
    }
};

void readData()
{
    std::fstream file;
    file.open("data.txt", std::ios::in);
    
    //5 dòng
    if (file.is_open())
    {
        while (!file.eof())
        {
			std::string buffer;

            getline(file, buffer);//dòng 1 kiểm tra xem người chơi có muốn chơi tiếp không
            ::playContinue = std::stoi(buffer);
            if (playContinue == 0) return;//người chơi không lưu thì phải chơi lại từ đầu

            getline(file, buffer);//dòng 2 tên người chơi
            ::name = buffer;

			getline(file, buffer);//dòng 3 điểm người chơi
            ::score = std::stoi(buffer);

            getline(file, buffer);//dòng 4 thời gian chơi
            ::timePlay = std::stod(buffer);

            getline(file, buffer);//dòng 5 level người chơi
            ::level = std::stoi(buffer);
		}

        file.close();
	}
    else std::cerr << "Can't open file" << std::endl;
}
void writeData()
{
    std::fstream file;
	file.open("data.txt", std::ios::out);
    if (file.is_open())
    {
		file << ::playContinue << std::endl;
		file << ::name << std::endl;
		file << ::score << std::endl;
		file << ::timePlay << std::endl;
        file << ::level;//không dùng endl nếu dùng sẽ tạo 6 dòng gây ra lỗi
		file.close();
	}
	else std::cerr << "Can't open file" << std::endl;

}
void readRecord(user* listUser, int& countUser)
{
    const int max = 5;// lấy 5 người chơi có điểm cao nhất

    std::fstream file;
	file.open("record.txt", std::ios::in);

    countUser = 0;
    if (file.is_open())
    {
        while (!file.eof())
        {
            std::string buffer;

            getline(file, buffer);
            if (buffer == "end") break;//end là dấu hiệu kết thúc file
            if (countUser == max) break;//đã đọc đủ 5 người chơi

            listUser = new user;

			getline(file, buffer);
			listUser->name = buffer;

            getline(file, buffer);
            listUser->score = std::stoi(buffer);

            getline(file, buffer);
            listUser->timePlay = std::stod(buffer);

            countUser++;
            listUser = listUser->next;
		}
		file.close();
	}
	else std::cerr << "Can't open file" << std::endl;
}
void updateRecord(user* listUser, const int& countUser)
{
    while (listUser != nullptr)
    {
		if(listUser->score < ::score)
		{ 
            user* tmp = new user;
            tmp->name = ::name;
            tmp->score = ::score;
            tmp->timePlay = ::timePlay;
            tmp->next = listUser;
            listUser = tmp;
            break;
        }
        if (listUser->score == ::score)
        {
            if (listUser->timePlay > ::timePlay)
            {
				user* tmp = new user;
				tmp->name = ::name;
				tmp->score = ::score;
				tmp->timePlay = ::timePlay;
				tmp->next = listUser;
				listUser = tmp;
				break;
			}
            else
            {
                user* tmp = new user;
                tmp->name = ::name;
                tmp->score = ::score;
                tmp->timePlay = ::timePlay;
                tmp->next = listUser->next;
                listUser->next = tmp;
                break;
            }
        }
        if (listUser->next == nullptr)
        {
            user* tmp = new user;
            tmp->name = ::name;
            tmp->score = ::score;
            tmp->timePlay = ::timePlay;
            tmp->next = nullptr;
            listUser->next = tmp;
            break;
        }
        listUser = listUser->next;
	}

    std::fstream file;
	file.open("history.txt", std::ios::out);
    if (file.is_open())
    {
        for (int i = 0; i < 5; i++)
        {
            if(listUser == nullptr) break;
            file << listUser->name << std::endl;
            file << listUser->score << std::endl;
            file << listUser->timePlay << std::endl;
            listUser = listUser->next;
        }
        file << "end";
        file.close();
	}
	else std::cerr << "Can't open file" << std::endl;

    while (listUser) 
    {
        user* temp = listUser;
        listUser = listUser->next;
        delete temp;
    }
}

void EnumerateFonts() {
    HDC hdc = GetDC(nullptr);

    LOGFONT lf;
    ZeroMemory(&lf, sizeof(LOGFONT));
    lf.lfCharSet = DEFAULT_CHARSET;

    EnumFontFamiliesEx(hdc, &lf, [](const LOGFONT* lpelfe, const TEXTMETRIC* lpntme, DWORD FontType, LPARAM lParam) -> int {
        std::wcout << L"Font Name: " << lpelfe->lfFaceName << std::endl;
        return 1;  // Continue enumeration
        }, 0, 0);

    ReleaseDC(nullptr, hdc);
}
void SetConsoleFont(const wchar_t* fontName, int fontSizeX, int fontSizeY) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);  // Lấy thông tin font hiện tại

    wcscpy_s(fontInfo.FaceName, fontName);  // Đặt tên font
    fontInfo.dwFontSize.X = fontSizeX;      // Đặt kích thước font X
    fontInfo.dwFontSize.Y = fontSizeY;      // Đặt kích thước font Y

    // Áp dụng font mới
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}
void getConsoleFont() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	std::wcout << L"Font Name: " << fontInfo.FaceName << std::endl;
	std::wcout << L"Font Size: " << fontInfo.dwFontSize.X << L" x " << fontInfo.dwFontSize.Y << std::endl;
}


int main()
{
	//init();
    //setFontSize(20,20);
	//fillFullScreen(0x30);
	//gotoXY(20, 10);
    //setBackgroudAndText(0x35);
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x1235);
	//button(0xc0,0x08, "HUNTING SNAKE", 25, 25);
    //std::cout << "HUNTING SNAKE";
    //endGame();


	return 0;
}