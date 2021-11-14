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
  TimeSeries t("testFile1.csv");
  for (int i = 0; i < t.getColumnLength() ;i++) {
    for (size_t j = 0; j < t.getRowLength(); j++) {
      std::cout << t.getColumnByIndex(j,i) << ",";
    }
    std::cout << '\n';
  }
}
