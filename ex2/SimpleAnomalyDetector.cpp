
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"
#include <cmath>

SimpleAnomalyDetector::SimpleAnomalyDetector(): cf()  {
	// TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
      for (int i = 0; i < ts.getRowLength(); i++) {
          float p = 0;
          float core = 0;
          float max = 0;
          int index = -1;
          for (int j = i + 1; j <  ts.getRowLength(); j++) {
              p = abs(pearson(&(ts.getColumnByIndex(i).second[0]), &(ts.getColumnByIndex(j).second[0]), ts.getRowLength()));
              if (p > core) {
                  core = p;
                  index = j;
              }
          }
          if (index != -1) {
              correlatedFeatures c;
              c.corrlation = core;
              c.feature1 = ts.getColumnByIndex(i).first;
              c.feature2 = ts.getColumnByIndex(index).first;
              c.lin_reg = linear_reg(&(ts.getColumnByIndex(i).second[0]), &(ts.getColumnByIndex(index).second[0]), ts.getColumnLength());

              for (int j = 0; j < ts.getColumnLength(); j++) {
                  Point point = Point(ts.getColumnByIndex(i).second[j], ts.getColumnByIndex(index).second[j]);
                  float devation = dev(point, c.lin_reg);
                  if (devation > max) {
                      max = devation;
                  }
              }
              c.threshold = max * 1.1;
              this->cf.push_back(c);
          }
      }
    // TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
  std::vector<AnomalyReport> report = {};
    for (int i = 0; i < this->cf.size(); i++) {
      std::vector<float> column1 = ts.getColumnByName(this->cf.at(i).feature1);
      std::vector<float> column2 = ts.getColumnByName(this->cf.at(i).feature2);
      for (int j = 0; j < column1.size(); j++) {
        Point p = Point(column1.at(j), column2.at(j));
        float deviation = dev(p, this->cf.at(i).lin_reg);
        if (deviation>= this->cf.at(i).threshold) {
          report.push_back(AnomalyReport(string(cf.at(i).feature1 + "-" + cf.at(i).feature2), j));
        }
    }
  }
  return report;
}
