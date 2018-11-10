#include <iostream>
#include "VirtualMachine.h"

int main() {
    ifstream input("quack.in");
    VirtualMachine quack(input);
    input.close();

    ofstream output("quack.out");
    quack.translation(output);
    output.close();

    return 0;
}
