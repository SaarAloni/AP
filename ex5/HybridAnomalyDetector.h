

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
	SimpleAnomalyDetector sap;
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
	void learnNormal(const TimeSeries& ts);
	Point ** floatsToPoints(std::vector<float> x, std::vector<float> y);
  vector<AnomalyReport> detect(const TimeSeries& ts);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
