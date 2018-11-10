#include <iomanip>
#include <fstream>
#include <cmath>

int main() {
    int count;
    double A, x, n;

    std::ifstream input("garland.in");
    input >> count >> A;
    input.close();

    // Рассчет колличества ламп на левой ветви
    // прибавляем 0.5 для корректности округления
    n = floor(sqrt(A) + 1 + 0.5) ;

    // Рассчет параметра x
    if (count > n) {
        x = ((n - 2) * A - (n - 1) * (n - 2)) / (n - 1);
    }
    else {
        x = ((count - 2) * A - (count - 1) * (count - 2)) / (count - 1);
    }

    std::ofstream output("garland.out");
    output << std::fixed << std::setprecision(2) << (count - 1) * x + (count - 1) * (count - 2) - (count - 2) * A;
    output.close();

    return 0;
}