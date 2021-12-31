

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

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
        virtual ~uploadCommand();
	    virtual void execute();
};

class displayCommand:public Command {

public:
        SimpleAnomalyDetector* ad;
        vector<AnomalyReport>** ar;
        displayCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des, vector<AnomalyReport>** ar):ad(ad), ar(ar), // change the des to const
        Command(dio, des){}
        virtual ~displayCommand();
	    virtual void execute();
};

class detectCommand:public Command {

public:
        SimpleAnomalyDetector* ad;
        vector<AnomalyReport>** ar;
        detectCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des, vector<AnomalyReport>** ar):ad(ad), ar(ar), // change the des to const
        Command(dio, des){}
        virtual ~detectCommand();
	    virtual void execute();
};

class algoSetCommand:public Command {

public:
        SimpleAnomalyDetector* ad;
        algoSetCommand(DefaultIO* dio, SimpleAnomalyDetector* ad, std::string des):ad(ad), // change the des to const
        Command(dio, des){}
        virtual ~algoSetCommand();
	    virtual void execute();
};

#endif /* COMMANDS_H_ */
