#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(ifstream &input) : registers(26) {
    string line;
    counterLine = 0;

    // Считываем программу из файла
    while(input >> line) {
        if (line[0] == ':')
            label[line.substr(1)] = counterLine;
        program.push_back(line);
        counterLine++;
    }
}

void VirtualMachine::translation(ofstream &output) {
    counterLine = 0;

    // Интерпретация программы
    while (counterLine != program.size()) {
        if (interpreter(program[counterLine], output))
            break;
        counterLine++;
    }
}

bool VirtualMachine::interpreter(string &line, ofstream &output) {
    switch(line[0]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            queue.push(atoi(line.c_str()));
            break;
        case '>':
            registers.set(line[1] - 'a', queue.front());
            queue.pop();
            break;
        case '<':
            queue.push(registers.get(line[1] - 'a'));
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            mathFunction(line[0]);
            break;
        case 'P':
            if (line.size() == 1) {
                output << queue.front() << endl;
                queue.pop();
            }
            else
                output << registers.get(line[1] - 'a') << endl;
            break;
        case 'C':
            if (line.size() == 1) {
                output << (char) (queue.front() % ASCII);
                queue.pop();
            }
            else
                output << registers.getChar(line[1] - 'a');
            break;
        case ':':
            break;
        case 'J':
            counterLine = label[line.substr(1)];
            break;
        case 'Z':
            if (registers.get(line[1] - 'a') == 0)
                counterLine = label[line.substr(2)];
            break;
        case 'E':
            if (registers.get(line[1] - 'a') == registers.get(line[2] - 'a'))
                counterLine = label[line.substr(3)];
            break;
        case 'G':
            if (registers.get(line[1] - 'a') > registers.get(line[2] - 'a'))
                counterLine = label[line.substr(3)];
            break;
        case 'Q':
        default:
            return true;
    }
    return false;
}

void VirtualMachine::mathFunction(char operation) {
    int x = queue.front();
    queue.pop();
    int y = queue.front();
    queue.pop();
    int tmp;

    switch(operation) {
        case '+':
            tmp = (x + y) % MAX;
            queue.push(tmp < 0 ? (tmp + MAX) : tmp);
            break;
        case '-':
            tmp = (x - y) % MAX;
            queue.push(tmp < 0 ? (tmp + MAX) : tmp);
            break;
        case '*':
            tmp = (x * y) % MAX;
            queue.push(tmp < 0 ? (tmp + MAX) : tmp);
            break;
        case '/':
            queue.push((y == 0) ? 0 : (x / y));
            break;
        case '%':
            tmp = x % y;
            queue.push((y == 0) ? 0 : (tmp < 0 ? (tmp + MAX) : tmp));
            break;
        default:
            return;
    }
}
