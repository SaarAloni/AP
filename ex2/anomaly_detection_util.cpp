/*
 * animaly_detection_util.cpp
 *
 * Author: 319339198 Artiom Divak
 * 316440023 Saar Aloni
 */

#include "anomaly_detection_util.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

template <typename T>
// returns the sum of all veribales
T sumOfArray(T* p, int size) {
  T result = 0;
  for(int i = 0; i < size; i++) {
    result = result + p[i];
  }
  return result;
}

template <typename T>
// adds add to each of arry veribales and puts the result into newArry
void addToAllArrayVeribals (T* arry, T* newArry,T toAdd,int size) {
  for (int i = 0; i < size; i++){
    newArry[i] = arry[i] + toAdd;
  }
}

template <typename T>
// multipile  each veribale in arryOne with arryTwo
//and put the answer int newArry
void multipileTwoArrays (T* arryOne, T* arryTwo, T* newArry, int size) {
  for (int i = 0; i < size; i++) {
    newArry[i] = arryOne[i] * arryTwo[i];
  }
}

// returns the variance of X and Y
float var(float* x, int size) {
  if (size == 0) {
    return 0;
  }
  float n = 1/(float) size;
  float sum = sumOfArray<float>(x, size);
  float expetation = n * sum;
  float arry[size];
  for (int i = 0; i < size; i++){
    arry[i] = (x[i] - expetation) * (x[i] - expetation);
  }
  float result = n * sumOfArray<float>(arry, size);
  return result;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
  if (size == 0) {
    return 0;
  }
  float n = 1/(float) size;
  float expetationOfX = sumOfArray<float>(x, size) * n;
  float expetationOfY = sumOfArray<float>(y, size) * n;
  float xMinusExpetation[size];
  float yMinusExpetation[size];
  addToAllArrayVeribals(x, xMinusExpetation, -expetationOfX, size);
  addToAllArrayVeribals(y, yMinusExpetation, -expetationOfY, size);
  float finalArry[size];
  multipileTwoArrays(xMinusExpetation, yMinusExpetation, finalArry, size);
  float result = sumOfArray<float>(finalArry, size) * n;
  return result;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
  float covariance = cov(x, y, size);
  if (var(x, size) <= 0 || var(y, size) >= 0) {

  }
  float sqrtOfXVar = std::sqrt(var(x, size));
  float sqrtOfYVar = std::sqrt(var(y, size));
  float result = covariance/(sqrtOfXVar*sqrtOfYVar);
  return result;
}

/*
* Function Name: linear_reg
* Input: Point points, int size
* Output: line equation
* Function Operation: performs a linear regression and returns the line equation
***/
Line linear_reg(Point** points, int size) {
  try {
    1/size;
  } catch (const std::exception& e) {
    throw;
  }
  float sumX = 0;
  float sumY = 0;
  float avgX = 0;
  float avgY = 0;
  float a = 0;
  float arrayX[size];
  float arrayY[size];
  for (int i = 0; i < size; i++) {
      sumX += points[i]->x;
      arrayX[i] = points[i]->x;
      sumY += points[i]->y;
      arrayY[i] = points[i]->y;
  }
  avgX = sumX / size;
  avgY = sumY / size;


  a = cov(arrayX, arrayY, size) / var(arrayX, size);
  Line l;
  l.a = a;
  l.b = avgY - (a * avgX);
  return l;
}

/*
* Function Name: linear_reg
* Input: 2 float array, int size
* Output: line equation
* Function Operation: performs a linear regression and returns the line equation
**/
Line linear_reg(float x, float* y, int size) {
  try {
    1/size;
  } catch (const std::exception& e) {
    throw;
  }
  float sumX = 0;
  float sumY = 0;
  float avgX = 0;
  float avgY = 0;
  float a = 0;
  for (int i = 0; i < size; i++) {
      sumX += x[i];
      sumY += y[i];
  }
  avgX = sumX / size;
  avgY = sumY / size;


  a = cov(x, y, size) / var(x, size);
  Line l;
  l.a = a;
  l.b = avgY - (a * avgX);
  return l;
}

/*
* Function Name: dev
* Input: Point p, Point points, int size
* Output: the devation
* Function Operation: returns the deviation between point p and the line equation of the points
***/
float dev(Point p, Point** points, int size) {
    Line l = linear_reg(points, size);
    return std::abs(p.y - l.f(p.x));
}

/***
* Function Name: dev
* Input: Point p, Line l
* Output: the devation
* Function Operation: returns the deviation between point p and the line
*/
float dev(Point p, Line l) {
  return std::abs(p.y - l.f(p.x));
}
