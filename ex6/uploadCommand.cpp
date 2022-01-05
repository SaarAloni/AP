#include "commands.h"
#include <fstream>
#include <iostream>
/*
uploadCommand::uploadCommand(DefaultIO* dio, std::string des):Command(dio, des) {
	// TODO Auto-generated constructor stub
}
*/
uploadCommand::~uploadCommand() {
	// TODO Auto-generated destructor stub
}


void uploadCommand::execute() {
    this->dio->write("Please upload your local train CSV file.\n");
    ofstream out("anomalyTrain.csv");
	std::string s = this->dio->read();
	while (s != "done"){
		out<<s<<endl;
        s = this->dio->read();
	}
	out.close();
    this->dio->write("Upload complete.\n");
    this->dio->write("Please upload your local test CSV file.\n");
    ofstream out2("anomalyTest.csv");
    s = this->dio->read();
	while (s != "done"){
		out2<<s<<endl;
        s = this->dio->read();
	}
	out2.close();
    this->dio->write("Upload complete.\n");
}
