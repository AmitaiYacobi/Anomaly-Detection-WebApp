// 313301764 Omer Schloss
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_
#include <iostream>
#include <vector>
#include <stdlib.h> /* srand, rand */
#include <time.h>	/* time */
#include "anomaly_detection_util.h"

using namespace std;

// ------------ DO NOT CHANGE -----------
//class Point{
//public:
//	float x,y;
//	Point(float x,float y):x(x),y(y){}
//};

class Circle
{
public:
	Point center;
	float radius;
	Circle() : center(0, 0), radius(0) {}
	Circle(Point c, float r) : center(c), radius(r) {}
};
// --------------------------------------

Circle findCircleByThreePoints(const Point &p1, const Point &p2, const Point &p3);

Circle findCircleByTwoPoints(const Point &p1, const Point &p2);

bool isLegalCircle(const Circle &c, const vector<Point> &points_vector);

float dist(Point a, Point b);

Circle findMinCircle(Point **points, size_t size, vector<Point> R = {});

#endif /* MINCIRCLE_H_ */