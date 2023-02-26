#pragma once
#include <iostream>
#include "windows.h"
#include "Display.h"
using namespace std;

class Color {
public:
	int r = 0;
	int g = 0;
	int b = 0;
public:
	void init(int ir, int ig, int ib) {}
};

class Point {
public:
	int x;
	int y;
public:
	void init(int ix, int iy) {}
};

class Line {
public:
	Point start;
	Point end;
public:
	void init(Point istart, Point iend) {}
};

class CPolygon {
public:
	int type = 0;
	int size = 2;
	vector<Point> points;
	vector<Line> lines;
	Color color;
	int boundingbox[4]; //{minx, miny, maxx, maxy}

public:
	void init(vector<Point> cpoints) {}

	void updateboundingbox(Point point) {}

	bool isactive(Point point0) {};

	bool isedge(Point point0) {}

	bool isinside(Point point0) {}

	int orientation(Point point1, Point point2, Point point3) {}
};

int GetPixels(Pixel* rawarr, HWND hWnd);