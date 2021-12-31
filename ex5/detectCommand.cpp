#include "commands.h"
#include <fstream>
#include <iostream>
/*
detectCommand::detectCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des, vector<AnomalyReport>** ar):ad(ad), ar(ar),
     Command(dio, des) {
	// TODO Auto-generated constructor stub
}
*/
detectCommand::~detectCommand() {
	// TODO Auto-generated destructor stub
}



void detectCommand::execute() {

    TimeSeries ts("anomalyTrain.csv");
	  this->ad->learnNormal(ts);
    TimeSeries ts2("anomalyTest.csv");
	//vector<AnomalyReport> r = this->ad->detect(ts2);

    //vector<AnomalyReport> r = this->ad->detect(ts2);
    *(this->ar) = this->ad->detect(ts2);
    //this->ar = &r; //prey
    this->dio->write("anomaly detection complete.\n");
}
