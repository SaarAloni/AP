#include "minCircle.h"
#include <cmath>

// return 1 if point is inside the circle, 0 otherwise
int isInsideCircle(Circle c, Point p) {
  if (c.center.x + c.radius < p.x || c.center.x - c.radius > p.x ||
     c.center.y + c.radius < p.y || c.center.y - c.radius > p.y) {
       return 0;
     }
     return 1;
}

// return 1 if point is inside the circle, 0 otherwise
int isInsideCircle(Circle c, float x, float y) {
  if (c.center.x + c.radius < x || c.center.x - c.radius > x ||
     c.center.y + c.radius < y || c.center.y - c.radius > y) {
       return 0;
     }
     return 1;
}

// create a circle from 3 point using 3 equation.
Circle findCirclefrom3Points(Point p1, Point p2, Point p3) {
  float resultX, resultY, resultR;
  float factorX1, factorY1, factorX2, factorY2;
  float cons1, cons2;
  factorX1 = (p1.x * 2.0) - (p2.x * 2.0);
  factorY1 = (p1.y * 2.0) - (p2.y * 2.0);
  factorX2 = (p3.x * 2.0) - (p2.x * 2.0);
  factorY2 = (p3.y * 2.0) - (p2.y * 2.0);
  cons1 = pow(p1.x, 2) - pow(p2.x, 2) + pow(p1.y,2) - pow(p2.y, 2);
  cons2 = pow(p3.x, 2) - pow(p2.x, 2) + pow(p3.y,2) - pow(p2.y, 2);
  resultX = ((cons1 * (factorY2 / factorY1)) - cons2) /
   ((factorX1 * (factorY2 / factorY1)) - factorX2);
  resultY = (cons1 - (resultX * factorX1)) / (factorY1);
  resultR = sqrt(pow(p1.x - resultX, 2) + pow(p1.y - resultY, 2));
  Circle c;
  c.center.x = resultX;
  c.center.y = resultY;
  c.radius = resultR;
  return c;
}
