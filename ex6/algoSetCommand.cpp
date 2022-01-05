#include "commands.h"
#include <fstream>
#include <iostream>
/*
algoSetCommand::algoSetCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des):ad(ad), Command(dio, des) {
	// TODO Auto-generated constructor stub
}
*/
algoSetCommand::~algoSetCommand() {
	// TODO Auto-generated destructor stub
}


void algoSetCommand::execute() {
    float f = this->ad->tempThreshold;
    this->dio->write("The current correlation threshold is ");
    this->dio->write(this->ad->tempThreshold);
    this->dio->write("\n");
    this->dio->read(&f);
	while (f < 0.0 || f > 1.0){
		this->dio->write("please choose a value between 0 and 1.\n");
        this->dio->write("The current correlation threshold is ");
        this->dio->write(this->ad->tempThreshold);
        this->dio->write("\n");
        this->dio->read(&f);
	}
	this->ad->tempThreshold = f;
}
