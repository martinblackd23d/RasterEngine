#include "Display.h"
#include <iostream>
#include "windows.h"
#include "FlatLogic.h"
using namespace std;

/*class Pixel {
public:
	int r = 0;
	int g = 0;
	int b = 0;
};*/

int TrueMain(HWND hWnd) {
	


	COLORREF* arr = (COLORREF*)calloc(720*720, sizeof(COLORREF));

	Pixel sample;


	Pixel* rawarr = (Pixel*)calloc(720 * 720, sizeof(sample));



	//int BitArray = GetPixels(rawarr);
	GetPixels(rawarr, hWnd);
	int r;// = 255;
	int g;// = 0;
	int b;// = 0;
	/*
	char title[8] = { 'S', 'U', 'C','C', 'E', 'S', 'S' , '\0' };
	SetWindowTextA(hWnd, title);
	*/
	for (int i = 0; i < 720 * 720; i++) {
		r = rawarr[i].r;
		g = rawarr[i].g;
		b = rawarr[i].b;

		arr[i] = RGB(b, g, r); // b g r
	}

	HBITMAP map = CreateBitmap(720, 720, 1, 4 * 8, (void*)arr);
	HDC hdcDest = GetDC(hWnd);
	HDC hdcSrc = CreateCompatibleDC(hdcDest);
	SelectObject(hdcSrc, map);

	BitBlt(hdcDest, 0, 0, 720, 720, hdcSrc, 0, 0, SRCCOPY);

	DeleteDC(hdcSrc);

	return 0;

}