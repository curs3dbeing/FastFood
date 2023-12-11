#include "for_screen.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>


void gotoXY(HANDLE hStdOut, short x, short y) {
	SetConsoleCursorPosition(hStdOut, {x, y});
}

void SetScreenTitle() {
	SetConsoleTitle(L"Order Menu");
}

void CursorVisiability(HANDLE hStdOut, bool visible) {
	visible = 0;
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(hStdOut, &cursor);
	cursor.bVisible = visible;
}

void SetUsualTextColor(HANDLE hStdOut) {
	SetConsoleTextAttribute(hStdOut, 3);
}

void SetEventTextColor(HANDLE hStdOut) {
	SetConsoleTextAttribute(hStdOut, 11);
}