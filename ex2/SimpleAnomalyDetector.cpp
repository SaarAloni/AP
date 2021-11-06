
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

  float threshold = 0.75;

      TimeSeries t = ts;
      pair<int, float> result[ts.getColumnLength()];
      for (int i = 0; i < ts.getColumnLength(); i++) {
          float p = 0;
          if (result[i] != NULL) {
              p = result[i].second;
          }
          float core = 0;
          int index = -1;
          for (int j = i + 1; j <  ts.getColumnLength(); j++) {
              if (p = pearson(ts.getColumnByIndex(i).second, ts.getColumnByIndex(j).second, ts.getColumnLength()) > core && p > threshold) {
                  core = p;
                  index = j;
              }
          }
          if (index != -1) {
              result[i].first = index;
              result[i].second = p;
              result[index].first = i;

          }
      }
	// TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}
