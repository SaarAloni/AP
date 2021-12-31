#include <iostream>
#include <fstream>
#include "commands.h"
#include "CLI.h"
#include "StandardIO.h"


int main() {
    DefaultIO * a = new StandardIO();
    CLI *c = new CLI(a);
    std::cout << "test alooc" << '\n';
    c->start();
    std::cout << "finish" << '\n';
}
