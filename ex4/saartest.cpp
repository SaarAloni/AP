#include <iostream>
#include <vector>
#include "AnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

int main() {
  //Point p3 = Point(-6.0,3.0);
  //Point p2 = Point(2.0,0.0);
  //Point p1 = Point(3.0,0.0);
  Point p3 = Point(5.0,4.0);
  Point p2 = Point(5.0,2.0);
  Point p1 = Point(9.0,4.0);

  Circle c = findCirclefrom3Points(p1, p2, p3);
  printf("%f\n", c.radius);
  printf("%f\n", c.center.x);
  printf("%f\n", c.center.y);

  std::vector<Point> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);

  Point * p4,p5,p6;
  p4 = &p1;
  //p5 = &p2;
  //p6 = &p3;
  std::vector<Point*> v2;
  v2.push_back(p4);
  //v2.push_back(p5);
  //v2.push_back(p6);
  //Point ** p = &v[0];
  Circle c2 = findMinCircle(&(v2[0]), (size_t)1);
  std::cout << "r:"<<c2.radius << "x:" << c2.center.x << "y:" << c2.center.y << '\n';



}
