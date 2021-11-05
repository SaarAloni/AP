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
  TimeSeries t("testcsv.csv");
  std::cout << t.getRowLength() << "\n";
  std::cout << t.getColumnLength() << "\n";
  std::cout << t.getColumnByName("size1").at(1) << "\n";
  try {
      std::cout << t.getColumnByIndex(0,0)<< "\n";
  }
  catch (invalid_argument& e) {
    std::cerr << e.what() << '\n';
    return -1;
  }
}
