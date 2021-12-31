#include "StandardIO.h"

/*
StandardIO::StandardIO() {
	// TODO Auto-generated constructor stub
}

StandardIO::~StandardIO() {
	// TODO Auto-generated destructor stub
}
*/

void StandardIO::write(string text) {
    std::cout << text; // /n in the text or here?
}

void StandardIO::write(float f) {
    std::cout << f; // /n in the text or here?
}

string StandardIO::read() {
    std::string s;
    std::cin >> s;
    return s;
}

void StandardIO::read(float* f) {
    std::cin >> *f;
    return;
}
