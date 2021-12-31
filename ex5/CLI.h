

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
	DefaultIO* dio;
	// you can add data members
public:
	CLI(DefaultIO* dio);
	void start();
	Command ** createCommandArray(std::vector<Command *> b);
	virtual ~CLI();
};

#endif /* CLI_H_ */
