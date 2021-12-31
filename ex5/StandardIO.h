#ifndef STANDARD_IO_H_
#define STANDARD_IO_H_

#include "commands.h"

class StandardIO:public DefaultIO {

public:
        virtual string read();
	virtual void write(string text);
	virtual void write(float f);
	virtual void read(float* f); // why is this void?
	virtual ~StandardIO(){}
};

#endif /* STANDARD_IO_H_ */