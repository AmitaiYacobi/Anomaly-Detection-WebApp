/*
 * animaly_detection_util.cpp
 *
 * Author: 313301764 Omer Schloss
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float *x, int size)
{
	float u = 0;
	for (int i = 0; i < size; i++)
	{
		u += x[i];
	}
	u = u / size;
	return u;
}

// returns the variance of X and Y
float var(float *x, int size)
{
	float result = 0;
	float u = avg(x, size);
	for (int i = 0; i < size; i++)
	{
		result += powf(x[i] - u, 2);
	}
	result = result / size;
	return result;
}

// returns the covariance of X and Y
float cov(float *x, float *y, int size)
{
	float avgX = avg(x, size);
	float avgY = avg(y, size);
	float result = 0;
	for (int i = 0; i < size; i++)
	{
		result += (x[i] - avgX) * (y[i] - avgY);
	}
	result = result / size;
	return result;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size)
{
	return cov(x, y, size) / ((sqrtf(var(x, size)) * sqrtf(var(y, size))));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size)
{
	float *x = new float[size];
	float *y = new float[size];
	for (int i = 0; i < size; i++)
	{
		x[i] = points[i]->x;
		y[i] = points[i]->y;
	}
	float a = cov(x, y, size) / var(x, size);
	float b = avg(y, size) - a * avg(x, size);
	return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size)
{
	return dev(p, linear_reg(points, size));
}

// returns the deviation between point p and the line
float dev(Point p, Line l)
{
	if ((l.f(p.x) - p.y) < 0)
	{
		return -(l.f(p.x) - p.y);
	}
	return (l.f(p.x) - p.y);
}