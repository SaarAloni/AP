
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"
#include <cmath>

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

      for (int i = 0; i < ts.getColumnLength(); i++) {
          float p = 0;
          float core = 0;
          float max = 0;
          int index = -1;
          for (int j = i + 1; j <  ts.getColumnLength(); j++) {
              float* a = &(ts.getColumnByIndex(i).second[0]);
              float* b = &(ts.getColumnByIndex(j).second[0]);
              p = abs(pearson(a, b, ts.getColumnLength()));
              if (p > core) {
                  core = p;
                  index = j;
              }
          }
          if (index != -1) {
              this->cf[i].corrlation = core;
              this->cf[i].feature1 = ts.getColumnByIndex(i).first;
              this->cf[i].feature2 = ts.getColumnByIndex(index).first;
              this->cf[i].lin_reg = linear_reg((a, a), ts.getRowLength());

              for (int j = 0; j < ts.getRowLength(); j++) {
                  Point point = Point(ts.getColumnByIndex(i).second[j], ts.getColumnByIndex(index).second[j]);
                  float devation = dev(point, this->cf[i].lin_reg);
                  if (devation > max) {
                      max = devation;
                  }
              }
              this->cf[i].threshold = max * 1.1;
          }
      }
	// TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
  std::vector<AnomalyReport> report = {};
  std::vector<float> times = ts.getColumnByName("Times");
  if (!times.empty()) {
    for (int i = 0; i < this->cf.size(); i++) {
      std::vector<float> column1 = ts.getColumnByName(this->cf.at(i).feature1);
      std::vector<float> column2 = ts.getColumnByName(this->cf.at(i).feature2);
      for (int j = 0; j < column1.size(); j++) {
        Point p = Point(column1.at(j), column2.at(j));
        float deviation = dev(p, this->cf.at(i).lin_reg);
        if (deviation>= this->cf.at(i).threshold) {
          report.push_back(AnomalyReport(string(cf.at(i).feature1 + "-" + cf.at(i).feature2), times.at(j)));
        }
      }
    }
  }
  return report;
}
