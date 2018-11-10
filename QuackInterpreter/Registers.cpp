#include "Registers.h"

Registers::Registers(const size_t count) {
    registers.resize(count);
}

Registers::~Registers() {
    registers.clear();
}

int Registers::get(const int i) const {
    return registers[i];
}

void Registers::set(const int i, const int value) {
    registers[i] = value;
}

char Registers::getChar(const int i) const {
    return (char)(registers[i] % ASCII);
}

