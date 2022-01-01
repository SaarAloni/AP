

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class ReportSpan{
public:
    int begin,end;
    ReportSpan(int begin, int end):begin(begin),end(end){}
};

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command{
protected: // changed to protected because why should it be private?
	DefaultIO* dio;
public:
	std::string description;
	Command(DefaultIO* dio, std::string des):dio(dio), description(des){}
	virtual void execute()=0;
	virtual ~Command(){}
};

// implement here your command classes

class uploadCommand:public Command {

public:
        uploadCommand(DefaultIO* dio, std::string des): // change the des to const
        Command(dio, des){}
        ~uploadCommand(){}
				void execute() {
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
};

class displayCommand:public Command {

public:
        SimpleAnomalyDetector* ad;
        vector<AnomalyReport>* ar;
        displayCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des, vector<AnomalyReport>* ar):ad(ad), ar(ar), // change the des to const
        Command(dio, des){}
        ~displayCommand(){}
				void execute() {
				    vector<AnomalyReport>* pAnomaly = this->ar;
				    for(int i = 0; i < pAnomaly->size(); i++) {
				        this->dio->write(pAnomaly->at(i).timeStep);
				        this->dio->write("\t" + pAnomaly->at(i).description + "\n");
				    }
				    this->dio->write("Done.\n");
				}
};

class detectCommand:public Command {

public:
				int *n;
        SimpleAnomalyDetector* ad;
        vector<AnomalyReport>* ar;
        detectCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des, vector<AnomalyReport>* ar, int *n):ad(ad), ar(ar),n(n), // change the des to const
        Command(dio, des){}
        ~detectCommand(){}
				void execute() {
				    TimeSeries ts("anomalyTrain.csv");
					  this->ad->learnNormal(ts);
				    TimeSeries ts2("anomalyTest.csv");
						*(this->n) = ts2.getRowSize();
				    *(this->ar) = this->ad->detect(ts2);
				    this->dio->write("anomaly detection complete.\n");
				}
};

class algoSetCommand:public Command {

public:
        SimpleAnomalyDetector* ad;
        algoSetCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des):ad(ad), // change the des to const
        Command(dio, des){}
        ~algoSetCommand(){

				}
				void execute() {
				    float f = this->ad->tempThreshold;
				    this->dio->write("The current correlation threshold is ");
				    this->dio->write(this->ad->tempThreshold);
				    this->dio->write("\nType a new threshold\n");
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
};

class analayzeCommand:public Command {

public:
        SimpleAnomalyDetector* ad;
           vector<AnomalyReport>* ar;
				int * n;
        analayzeCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des, vector<AnomalyReport>* ar, int *n):ad(ad), ar(ar),n(n), // change the des to const
        Command(dio, des){}
        ~analayzeCommand() {
				}
        void execute() {
            std::vector<ReportSpan> rsServer;
            std::vector<ReportSpan> rsClient;
            float N = (float)*(this->n);
            float FP = 0;
            float TP = 0;
            float P = 0;
            float TPR = 0;
            float FPR = 0;

            for (int i = 0; i < this->ar->size() - 1;) {
                int j = 1;
                while (this->ar->at(i).description == this->ar->at(i+j).description && (this->ar->at(i).timeStep + 1) == this->ar->at(i+j).timeStep) {
                    j++;
										if (i + j < this->ar->size()) {
											continue;
										}
										break;
                }

                rsServer.push_back(ReportSpan(this->ar->at(i).timeStep,this->ar->at(i + j-1).timeStep));
                i += j;
            }
						// for the last anomaly we cant check it with the next anomaly so we make an exeption
						if (this->ar->at(this->ar->size() - 2).description != this->ar->at(this->ar->size() - 1).description) {
							rsServer.push_back(ReportSpan(this->ar->at(this->ar->size()-1).timeStep, this->ar->at(this->ar->size()-1).timeStep));
						}
            this->dio->write("Please upload your local train CSV file.\n");
            std::string s = this->dio->read();
            while (s != "done"){
                std::string input;
                std::vector<std::string> results;
                std::istringstream ss(s);
                while(getline(ss, input, ',')) {
                    results.push_back(input);
                }
                rsClient.push_back(ReportSpan(std::stoi(results.at(0)), (std::stoi(results.at(1)))));
								N = N - ((std::stoi(results.at(1))) - (std::stoi(results.at(0))) + 1 );
                P++;
                  s = this->dio->read();
            }
            this->dio->write("Upload complete.\n");
            for (int i = 0; i < rsServer.size(); i++) {
                int flag = 0;
                for (int j = 0; j < rsClient.size(); j++) {
                    if ((rsServer.at(i).begin > rsClient.at(j).begin && rsServer.at(i).begin < rsClient.at(j).end) ||
                     (rsServer.at(i).end > rsClient.at(j).begin && rsServer.at(i).end < rsClient.at(j).end) ||
                     (rsServer.at(i).begin < rsClient.at(j).begin && rsServer.at(i).end > rsClient.at(j).end)) {
                         TP+=1;
                         flag = 1;
                         break;
                     }

                }
                if (flag == 0) {
                    FP+=1;
                }
            }
            this->dio->write("True Positive Rate: ");
            this->dio->write(TP / P);
            this->dio->write("\nFalse Positive Rate: ");
            this->dio->write(FP / N);
            this->dio->write("\n");

        }
};

class exitCommand:public Command {

public:
        exitCommand(DefaultIO* dio, std::string des): // change the des to const
        Command(dio, des){}
        ~exitCommand(){}
        void execute(){}
};

#endif /* COMMANDS_H_ */
