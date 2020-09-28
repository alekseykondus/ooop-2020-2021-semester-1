#pragma once
#include <windows.h>
#include <direct.h> 

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void out_BLUE_RED(const char str[100])
{
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED);
	std::cout << str << std::endl;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
void out_RED(const char str[100])
{
	SetConsoleTextAttribute(console, FOREGROUND_RED);
	std::cout << str << std::endl;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
void out_GREEN(const char str[100])
{
	SetConsoleTextAttribute(console, FOREGROUND_GREEN);
	std::cout << str << std::endl;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

