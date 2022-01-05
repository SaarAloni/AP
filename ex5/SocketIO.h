#ifndef STANDARD_IO_H_
#define STANDARD_IO_H_

#include "commands.h"

class SocketIO:public DefaultIO {

public:

  SocketIO(int s): // change the des to const
  DefaultIO(){}
        string read() {

        }
	virtual void write(string text);
	virtual void write(float f);
	virtual void read(float* f); // why is this void?
	virtual ~StandardIO(){}
};

#endif /* STANDARD_IO_H_ */
