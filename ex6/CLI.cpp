#include "CLI.h"
#include "commands.h"

CLI::CLI(DefaultIO* dio):dio(dio) {
}

void CLI::start(){
  std::vector<Command *> cmnds;
  HybridAnomalyDetector * ad = new HybridAnomalyDetector();
  vector<AnomalyReport> ar;
  int lineNum = 0;
  cmnds.push_back(new uploadCommand(this->dio,"upload a time series csv file"));
  cmnds.push_back(new algoSetCommand(this->dio, ad, "algorithm settings"));
  cmnds.push_back(new detectCommand(this->dio, ad, "detect anomalies", &ar, &lineNum));
  cmnds.push_back(new displayCommand(this->dio, ad, "display results", &ar));
  cmnds.push_back(new analayzeCommand(this->dio, ad, "upload anomalies and analyze results", &ar, &lineNum));
  cmnds.push_back(new exitCommand(this->dio,"exit"));
  Command ** c = &cmnds[0];
    //Command ** c = createCommandArray(b);
    int i = 0;
    float n;
    do {
        this->dio->write("Welcome to the Anomaly Detection Server.\n");
        this->dio->write("Please choose an option:\n");
        for (int j = 0; j < 6; j++) {
            this->dio->write((int)(j + 1));
            this->dio->write("." + c[j]->description + "\n");
        }
        this->dio->read(&n);
        i = n;
        if (i != 6) {
            c[i - 1]->execute();
        }

    } while(i != 6);
}
CLI::~CLI() {
}
