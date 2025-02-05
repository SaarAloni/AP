#include "anomaly_detection_util.h"
#include <iostream>
#include <cmath>


void printsaar() {
    printf("saar");
}

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
  float n = 1/size;
  float sum = sumOfArray<float>(x, size);
  float expetation = n * sum;
  float arry[size];
  for (int i = 0; i < size; i++){
    arry[i] = (x[i] - expetation) * (x[i] - expetation);
  }
  float var = n * sumOfArray<float>(arry, size);
  return var;
}


/*************************************************
* Function Name: cov
* Input: float* x, float* y, int size
* Output: convariance result
* Function Operation: returns the covariance of X and Y
*************************************************/
float cov(float* x, float* y, int size) {
  float varOfX = var(x, size);
  float varOfY = var(y, size);
  float xMinusExpetation[size];
  float yMinusExpetation[size];
  addToAllArrayVeribals(x, xMinusExpetation, -varOfX, size);
  addToAllArrayVeribals(y, yMinusExpetation, -varOfY, size);
  float finalArry[size];
  multipileTwoArrays(xMinusExpetation, yMinusExpetation, finalArry, size);
  float result = var(finalArry, size);
  return result;
}

/*************************************************
* Function Name: pearson
* Input: float* x, float* y, int size
* Output: Pearson result
* Function Operation: returns the Pearson correlation coefficient of X and Y
*************************************************/
float pearson(float* x, float* y, int size) {
  float covariance = cov(x, y, size);
  float sqrtOfXVar = std::sqrt(var(x, size));
  float sqrtOfYVar = std::sqrt(var(y, size));
  float result = covariance/(sqrtOfXVar*sqrtOfYVar);
  return result;
}

/*************************************************
* Function Name: main
* Input: int argc,
* Output: Pearson result
* Function Operation: returns the Pearson correlation coefficient of X and Y
*************************************************/
int main(int argc, char const *argv[]) {
  int arr[3] = {8,2,4};
  multipileTwoArrays<int>(arr,arr,arr,3);
  std::cout << arr[0];
  return 0;
}
