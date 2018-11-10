#ifndef QUACKINTERPRETER_VIRTUALMACHINE_H
#define QUACKINTERPRETER_VIRTUALMACHINE_H

#include <fstream>
#include <queue>
#include <map>
#include "Registers.h"

using namespace std;

const int MAX = 65536; // Константа для численных границ

/**
 * Виртуальная машина для языка Quack
 */
class VirtualMachine {
public:

    /**
     * Создание виртуальной машины и загрузка
     * в неё исходной программы
     * @param input входной поток
     */
    explicit VirtualMachine(ifstream & input);

    /**
     * Исполнение программы в выходном потоке
     * @param output выходной поток
     */
    void translation(ofstream &output);

private:
    vector <string> program; // Код всей программы построчно
    map <string, int> label; // Метки программы
    Registers registers;     // Регистры
    queue <int> queue;       // очередь для хранения целых чисел
    int counterLine;         // счетчик строк в программе

    /**
     * Интерпретатор языка Quack
     * @param line строка из кода программы
     * @param output выходной поток
     * @return конец ли программы (true - да, false - нет)
     */
    bool interpreter(string &line, ofstream &output);

    /**
     * Вспомогательная функция для выполнения математических операций
     * @param operation операция
     */
    void mathFunction(char operation);;
};



#endif //QUACKINTERPRETER_VIRTUALMACHINE_H
