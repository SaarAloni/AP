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
  Point p2 = Point(9.0,4.0);
  Point p1 = Point(5.0,2.0);
  Circle c = findCirclefrom3Points(p1, p2, p3);
  printf("%f\n", c.radius);
  printf("%f\n", c.center.x);
  printf("%f\n", c.center.y);
  cout<<"dosssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssne"<<endl;
}
