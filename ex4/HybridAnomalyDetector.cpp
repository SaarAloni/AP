#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts) {
  SimpleAnomalyDetector::learnNormal(ts);
  for (long int i = 0; i < this->cf.size(); i++) {
    if (cf.at(i).corrlation/1.1 < 0.9) {
      std::vector<Point *> result;
      int size = ts.getAttributeData(this->cf.at(i).feature1).size();
      std::vector<float> v1 = ts.getAttributeData(this->cf.at(i).feature1);
      std::vector<float> v2 = ts.getAttributeData(this->cf.at(i).feature2);
      for (int j = 0; j <  size; j++) {
          Point * p = new Point(v1.at(j), v2.at(j));
          result.push_back(p);
      }
      this->cf.at(i).circle =
       findMinCircle(&result[0],
        ts.getAttributeData(this->cf.at(i).feature1).size());
    }
    else {
      cf.at(i).circle = Circle();
      cf.at(i).circle.radius = -1;
    }
  }

  }

  vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts){
    std::vector<AnomalyReport> report = {};
    for (int i = 0; i < this->cf.size(); i++) {
      std::vector<float> column1 = ts.getAttributeData(this->cf.at(i).feature1);
      std::vector<float> column2 = ts.getAttributeData(this->cf.at(i).feature2);
      correlatedFeatures c = this->cf.at(i);
      if(cf.at(i).circle.radius == -1) {
        std::vector<AnomalyReport> vec = SimpleAnomalyDetector::detect(c, column1, column2);
        for (AnomalyReport ar : vec) {
          report.push_back(ar);
        }
      }
      else {
        std::vector<AnomalyReport> v = {};
        for (int j = 0; j < column1.size() ; j++) {
          if(isInsideCircle(cf.at(i).circle, column1.at(j), column2.at(j)) == 0) {
            report.push_back(AnomalyReport(string(this->cf.at(i).feature1 + "-" + this->cf.at(i).feature2), j+1));
          }
        }
      }

    }
    return report;
   }

Point ** HybridAnomalyDetector::floatsToPoints(std::vector<float> x, std::vector<float> y) {
  std::vector<Point *> v = {};

  for (int i = 0; i < x.size() ; i++) {
      Point * p = new Point(x.at(i), y.at(i));
      v.push_back(p);
  }
  return &v[0];
}
