#pragma once
#include <iostream>
#include "windows.h"
using namespace std;

class Pixel {
public:
	int r;
	int g;
	int b;
};
int TrueMain(HWND hWnd);