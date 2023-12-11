#ifndef H_FORSCREEN
#define H_FORSCREEN
#include <conio.h>
#include <Windows.h>
#include <iostream>


void gotoXY(HANDLE hStdOut, int x, int y);
void SetScreenTitle();
void CursorVisiability(bool);
void SetUsualTextColor();
void SetEventTextColor();
#endif 

