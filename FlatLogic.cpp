#include "FlatLogic.h"
#include <iostream>
#include "windows.h"
#include "Display.h"
#include <cmath>
#include <vector>
#include <chrono>
//#include "Orthographic.h"
using namespace std;

/// <summary>
/// base classes///////////////////////////////////////////////////////////////////////////////////////////
/// </summary>

//Color

void Color::init(int ir, int ig, int ib) {
	r = ir;
	g = ig;
	b = ib;
}

//Point

void Point::init(int ix, int iy) {
	x = ix;
	y = iy;
}


//Line

void Line::init(Point istart, Point iend) {
	start = istart;
	end = iend;
}

//CPolygon

void CPolygon::init(vector<Point> cpoints) {
	auto k = cpoints.begin();
	points.push_back(*k);

	boundingbox[0] = (*k).x;
	boundingbox[1] = (*k).y;
	boundingbox[2] = (*k).x;
	boundingbox[3] = (*k).y;

	Point tempstart = *k;
	Point tempend;
	Line templine;
	++k;

	for (int i = 0; i < cpoints.size()-1; i++) {
		points.push_back(*k);
		updateboundingbox(*k);
		tempend = *k;
		templine.init(tempstart, tempend);
		lines.push_back(templine);
		size++;
		tempstart = *k;
		++k;
	}
	templine.init(tempstart, *cpoints.begin());
	lines.push_back(templine);
}

void CPolygon::updateboundingbox(Point point) {
	if (point.x < boundingbox[0]) { boundingbox[0] = point.x; }
	if (point.x > boundingbox[2]) { boundingbox[2] = point.x; }
	if (point.y < boundingbox[1]) { boundingbox[1] = point.y; }
	if (point.y > boundingbox[3]) { boundingbox[3] = point.y; }
}

bool CPolygon::isactive(Point point0) {
	if (point0.x >= boundingbox[0] and point0.x <= boundingbox[2] and point0.y >= boundingbox[1] and point0.y <= boundingbox[3]) { return true; }
	else { return false; }
};

bool CPolygon::isedge(Point point0) {
	int width = 1;
	double d;
	int x = point0.x;
	int y = point0.y;
	int x1;
	int y1;
	int x2;
	int y2;
	Line temp;
	for (auto i = lines.begin(); i != lines.end(); ++i) {
		temp = *i;
		x1 = temp.start.x;
		y1 = temp.start.y;
		x2 = temp.end.x;
		y2 = temp.end.y;

		//if (!((x >= x1) xor (x <= x2)) and !((y >= y1) xor (y <= y2))) {
			d = ((x2 - x1) * (y1 - y) - (x1 - x) * (y2 - y1)) / sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
			if (d < width and d >(-1) * width and !((x >= x1) xor (x <= x2)) and !((y >= y1) xor (y <= y2))) { return true; };
		//}
	}
	return false;
}

bool CPolygon::isinside(Point point0) {
	int x = point0.x;
	int y = point0.y;
	int x1;
	int y1;
	int x2;
	int y2;

	Point temp;
	temp.init(x, 10000);



	int xcounter = 0;


	for (auto i = lines.begin(); i != lines.end(); ++i) {
		x1 = (*i).start.x;
		y1 = (*i).start.y;
		x2 = (*i).end.x;
		y2 = (*i).end.y;

		if ((orientation((*i).start, (*i).end, temp) != orientation((*i).start, (*i).end, point0)) and (orientation(point0, temp, (*i).start) != orientation(point0, temp, (*i).end))) { xcounter++; }

		if (x == x1 and y <= y1) {
			if (i == lines.begin()) {
				if (orientation(point0, temp, (*i).end) != orientation(point0, temp, (*lines.rbegin()).start)) { xcounter--; };
			} else {
				auto k = i - 1;
				if (orientation(point0, temp, (*i).end) != orientation(point0, temp, (*k).start)) { xcounter--; };
			}
		}
	}

	if (xcounter % 2 == 1) { return true; }
	else { return false; }

}

int CPolygon::orientation(Point point1, Point point2, Point point3) {
	int k = (point2.y - point1.y) * (point3.x - point2.x) - (point3.y - point2.y) * (point2.x - point1.x);
	if (k == 0) { return 0; }
	else if (k < 0) { return 1; }
	else { return 2; };

}

/// <summary>
/// scenes///////////////////////////////////////////////////////////////////////////////////////////
/// </summary>

class Scene {
public:
	vector<CPolygon> objects;

	///void init() {};

	void color(int x, int y, Color* color) {
		Point temp;
		temp.x = x;
		temp.y = y;
		int k = 0;

		for (auto i = objects.begin(); i != objects.end(); ++i) {
			if ((*i).isactive(temp) and (*i).isedge(temp)) { (*color).init((*i).color.r, (*i).color.g, (*i).color.b); };
			k++;
		}
	}
};

class Scene1 : public Scene {
public:
	void init() {
		Point point1;
		Point point2;
		Point point3;
		Point point4;
		point1.x = 300;
		point1.y = 300;
		point2.x = 250;
		point2.y = 500;
		point3.x = 400;
		point3.y = 400;
		vector<Point> points{ point1, point2, point3 };
		CPolygon object;
		object.init(points);

		Color color;
		color.init(0, 255, 0);
		object.color = color;
		objects.push_back(object);
		
		Color color2;
		CPolygon object2;
		point1.x = 200;
		point1.y = 500;
		point2.x = 350;
		point2.y = 600;
		point3.x = 500;
		point3.y = 300;
		point4.x = 200;
		point4.y = 200;
		points = { point1, point2, point3, point4 };
		color2.init(0, 0, 255);
		object2.init(points);
		object2.color = color2;
		objects.push_back(object2);
		
		Color color3;
		CPolygon object3;
		point1.init(500, 100);
		point2.init(500, 200);
		point4.init(600, 100);
		point3.init(600, 200);
		points = { point1, point2, point3, point4 };
		color3.init(255, 0, 0);
		object3.init(points);
		object3.color = color3;
		objects.push_back(object3);
	}
};

/// <summary>
/// main function///////////////////////////////////////////////////////////////////////////////////////////
/// </summary>

int GetPixels(Pixel* rawarr, HWND hWnd) {	
	int x = 0;
	int y = 0;
	int rgb[] = { 0, 0, 0 };
	Color color; 
	Scene1 scene;//change scene here
	scene.init();

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < 720 * 720; i++) {
///////////////////////////////////////////////////

		scene.color(x, y, &color);

		if (x == 0 or y == 0 or x == 719 or y == 719) { color.init(127, 127, 0); };

		rawarr[i].r = color.r;
		rawarr[i].g = color.g;
		rawarr[i].b = color.b;
		color.init(0, 0, 0);
///////////////////////////////////////////////////
		x++;
		if (x == 720 && y == 720) { break; }
		else if (x == 720) { y++; x = 0; };
	};

	auto stop = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	int counter = 1;
	int rem = duration.count();

	vector<int> digits;
	while (true) {
		if (rem == 0) { break; }
		digits.push_back(rem % 10);
		rem = (rem - rem % 10) / 10;
		counter++;
	};

	char* title = (char*)calloc(counter, sizeof(char));
	counter = 0;
	char chars[10] = { '0','1','2','3','4','5','6','7','8','9' };

	for (auto i = digits.rbegin(); i != digits.rend(); i++) {
		title[counter] = chars[*i];
		counter++;
	}
	title[counter] = '\0';


	//char title[8] = { 'S', 'U', 'C','C', 'E', 'S', 'S' , '\0' };
	SetWindowTextA(hWnd, title);
	
	return 0;
};