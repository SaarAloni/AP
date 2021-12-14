
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
  Circle():center(Point()), radius(0){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

// you can add here additional methods
Circle welzlMinCircle(vector<Point> points, vector<Point> r);

int isInsideCircle(Circle c, Point p);

Circle calcCircle(vector<Point> r);

int isInsideCircle(Circle c, float x, float y);

float distanceBetween2Points(Point p1, Point p2);

Point centerbetween2Points(Point p1, Point p2);

Circle findCirclefrom1Point(Point p);

Circle findCirclefrom2Points(Point p1, Point p2);

Circle findCirclefrom3Points(Point p1, Point p2, Point p3);

//std::vector<Point> pointOutsideCircle(Circle c, Point** points);

#endif /* MINCIRCLE_H_ */
