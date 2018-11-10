#ifndef QUACKINTERPRETER_REGISTERS_H
#define QUACKINTERPRETER_REGISTERS_H

#include <fstream>
#include <vector>

const int ASCII = 256; // Константа для символьных границ

/**
 * Класс регистров, для единообразной работы с ними
 */
class Registers {
public:

    /**
     * Конструктор с параметром
     * @param count колличество регистров
     */
    explicit Registers(const std::size_t count);

    /**
     * Деструктор
     */
    ~Registers();

    /**
     * Взятие значение из регистра
     * @param i индекс регистра
     * @return значение
     */
    int get(const int i) const;

    /**
     * Положить значение в регистр
     * @param i индекс регистра
     * @param value значение
     */
    void set(const int i, const int value);

    /**
     * Взятия значения как символа из регистра
     * @param i индекс регистра
     * @return символьное значение
     */
    char getChar(const int i) const;

private:
    std::vector<int> registers;
};

#endif //QUACKINTERPRETER_REGISTERS_H
