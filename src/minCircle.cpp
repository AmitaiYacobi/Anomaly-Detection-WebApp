// 313301764 Omer Schloss
#include "minCircle.h"

Circle findCircleByThreePoints(const Point &p1, const Point &p2, const Point &p3)
{
	float A = p1.x * (p2.y - p3.y) - p1.y * (p2.x - p3.x) + p2.x * p3.y - p3.x * p2.y;
	float B = (powf(p1.x, 2) + powf(p1.y, 2)) * (p3.y - p2.y) + (powf(p2.x, 2) + powf(p2.y, 2)) * (p1.y - p3.y) + (powf(p3.x, 2) + powf(p3.y, 2)) * (p2.y - p1.y);
	float C = (powf(p1.x, 2) + powf(p1.y, 2)) * (p2.x - p3.x) + (powf(p2.x, 2) + powf(p2.y, 2)) * (p3.x - p1.x) + (powf(p3.x, 2) + powf(p3.y, 2)) * (p1.x - p2.x);
	Point center(-B / (2 * A), -C / (2 * A));
	return Circle(center, sqrtf(powf(center.x - p1.x, 2) + powf(center.y - p1.y, 2)));
}

Circle findCircleByTwoPoints(const Point &p1, const Point &p2)
{
	Point center((p1.x + p2.x) / (float)2, (p1.y + p2.y) / (float)2);
	return Circle(center, sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)) / (float)2);
}

bool isLegalCircle(const Circle &c, const vector<Point> &points_vector)
{
	vector<Point>::const_iterator it;
	for (it = points_vector.begin(); it != points_vector.end(); it++)
	{
		bool check =( sqrtf(pow(c.center.x - it->x, 2) + pow(c.center.y - it->y, 2)) <= c.radius);
		if (!check)
		{
			return false;
		}
	}
	return true;
}

Circle trivialCircle(vector<Point> &points_vector)
{
	if (points_vector.empty())
	{
		return Circle(Point(0, 0), 0);
	}
	else if (points_vector.size() == 1)
	{
		return Circle(points_vector[0], 0);
	}
	else if (points_vector.size() == 2)
	{
		return findCircleByTwoPoints(points_vector[0], points_vector[1]);
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{

			Circle c = findCircleByTwoPoints(points_vector[i], points_vector[j]);
			if (isLegalCircle(c, points_vector))
				return c;
		}
	}
	return findCircleByThreePoints(points_vector[0], points_vector[1], points_vector[2]);
}

float dist(Point a, Point b)
{
	float x2 = (a.x - b.x) * (a.x - b.x);
	float y2 = (a.y - b.y) * (a.y - b.y);
	return sqrt(x2 + y2);
}

// implement
Circle findMinCircle(Point **points, size_t size, vector<Point> R)
{
	if ((size == 0) || (R.size() == 3))
	{
		return trivialCircle(R);
	}
	Circle c = findMinCircle(points, size - 1, R);
	if (sqrtf(pow(c.center.x - points[size - 1]->x, 2) + pow(c.center.y - points[size - 1]->y, 2)) <= c.radius)
	{
		return c;
	}
	R.push_back(*points[size - 1]);
	return findMinCircle(points, size - 1, R);
}