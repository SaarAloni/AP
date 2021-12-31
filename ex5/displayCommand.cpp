#include "commands.h"
#include <fstream>
#include <iostream>
/*
displayCommand::displayCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des, vector<AnomalyReport>** ar):ad(ad), ar(ar),
     Command(dio, des) {
	// TODO Auto-generated constructor stub
}
*/
displayCommand::~displayCommand() {
	// TODO Auto-generated destructor stub
}


void displayCommand::execute() {
    vector<AnomalyReport>* pAnomaly = this->ar[0];
    for(int i = 0; i < pAnomaly->size(); i++) {
        this->dio->write(pAnomaly->at(i).timeStep);
        this->dio->write("\t" + pAnomaly->at(i).description + "\n");
    }
    this->dio->write("Done.\n");

    /*
    for (std::vector<AnomalyReport>::iterator it = this->ar[0]->begin(); it != this.ar[0]->end(); ++it) {

    }
    */
}
