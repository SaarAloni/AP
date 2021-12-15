#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts) {
  SimpleAnomalyDetector::learnNormal(ts);
  for (long int i = 0; i < this->cf.size(); i++) {
    std::cout << i << '\n';
    std::cout << ts.getColumnByName(cf.at(i).feature2)[0] << '\n';
    std::cout << ts.getColumnByName(cf.at(i).feature1)[0]<< '\n';
    if (cf.at(i).threshold/1.1 < 0.9) {
      Point ** p = floatsToPoints(ts.getColumnByName(cf.at(i).feature1),ts.getColumnByName(cf.at(i).feature2));
      std::cout << "result"<< p[0]->y << '\n';
      cf.at(i).circle =
       findMinCircle(floatsToPoints(ts.getColumnByName(cf.at(i).feature1),
       ts.getColumnByName(cf.at(i).feature2)),
        ts.getColumnByName(cf.at(i).feature1).size());
        std::cout << "here" << '\n';
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
      std::vector<float> column1 = ts.getColumnByName(this->cf.at(i).feature1);
      std::vector<float> column2 = ts.getColumnByName(this->cf.at(i).feature2);
      TimeSeries newTS = TimeSeries(column1, this->cf.at(i).feature1,column2, this->cf.at(i).feature2);
      if(cf.at(i).circle.radius == -1) {
        std::vector<AnomalyReport> vec = SimpleAnomalyDetector::detect(newTS);
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
  Point ** result;
  std::cout << "/* message */" << '\n';
  for (int i = 0; i < x.size() ; i++) {
      Point * p = new Point(x.at(i), y.at(i));
      result[i] = p;
  }

  return result;
}
