#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
const double PI = 3.14159265358979323846;

double func1(double x) {
    return 2 * x * x - x + 1;
}

double func2(double x) {
    return 2 * sin(3 * x);
}

double func3(double x) {
    return x * x - 3 * sin(3 * x);
}

// вузли Чебишова
vector<double> chebyshev_nodes(int n, double a, double b) {
    vector<double> nodes;
    for (size_t i = 0; i < n; ++i) {
        nodes.push_back(((a + b) / 2) + (((b - a) / 2) * cos(((2.0 * i + 1.0) * PI) / (2.0 * n))));
    }
    return nodes;
}

// обчислення коефіціентів інтерполяційного полінома Ньютона
void newton_polynom_coef(const vector<double>& x, const vector<double>& y, vector<double>& coef) {
    for (size_t k = 0; k < x.size(); k++) {
        for (size_t j = 0; j <= k; j++) {
            double temp = 1.0;
            for (size_t i = 0; i <= k; i++) {
                if (i != j) {
                    temp *= (x[j] - x[i]);
                }
            }
            coef[k] += y[j] / temp;
        }
    }
}

// обчислення інтерполяційного полінома Ньютона у точці xi
double newton_polynom_at(const vector<double>& x, const vector<double>& coef, double xi) {
    double result = 0.0;
    for (size_t i = 0; i < coef.size(); ++i) {
        double term = 1;
        for (size_t j = 0; j < i; ++j) {
            term = term * (xi - x[j]);
        }
        result += term * coef[i];
    }
    return result;
}

// обчислення полінома Лагранжа у точці xi
double lagrange_polynom_at(const vector<double>& x, const vector<double>& y, double xi) {
    double result = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        double term = 1;
        for (size_t j = 0; j < x.size(); ++j) {
            if (j != i) {
                term = term * (xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += term * y[i];
    }
    return result;
}

// Рахуємо графіки результатів для видачі в gnuplot
// 1 колонка - x, 2 колонка - вихідна ф-я, 3 колонка - поліном Ньютона, 4 поліном Лагранжа
void write_graph_file_for_gnuplot(
    double a, double b,
    int number_of_chebyshev_nodes, int number_of_graph_steps,
    double (*func)(double), const char* filename
) {

    // Обчислюємо вузли Чебишева
    vector<double> chebyshev_x = chebyshev_nodes(number_of_chebyshev_nodes, a, b);

    // Обчислюємо вихідну функцію на вузлах Чебишева
    vector<double> chebyshev_y;
    for (double x : chebyshev_x) { chebyshev_y.push_back(func(x)); }

    // Обчислюємо коефіціенти інтерполяційного полінома Ньютона на вузлах Чебишева
    vector<double> newton_coef(chebyshev_x.size(), 0.0);
    newton_polynom_coef(chebyshev_x, chebyshev_y, newton_coef);

    ofstream outfile;
    outfile.open(filename);
    // Рахуємо графіки результатів для видачі в gnuplot
    // 1 колонка - x, 2 колонка - вихідна ф-я, 3 колонка - поліном Ньютона, 4 поліном Лагранжа
    double step = (b - a) / number_of_graph_steps;
    for (double x = a; x <= b; x += step) {
        outfile << x << " ";
        outfile << func(x) << " ";
        outfile << newton_polynom_at(chebyshev_x, newton_coef, x) << " ";
        outfile << lagrange_polynom_at(chebyshev_x, chebyshev_y, x) << endl;
    }
    outfile.close();
}

int main() {
    // початкові умови
    double a = -1.0;
    double b = 3.0;
    // будуємо інтерполяцію на 12 нодах
    int number_of_chebyshev_nodes = 12;
    // графік на 80 кроків
    int number_of_graph_steps = 80;
    write_graph_file_for_gnuplot(a, b, number_of_chebyshev_nodes, number_of_graph_steps, &func1, "func1.data");
    write_graph_file_for_gnuplot(a, b, number_of_chebyshev_nodes, number_of_graph_steps, &func2, "func2.data");
    write_graph_file_for_gnuplot(a, b, number_of_chebyshev_nodes, number_of_graph_steps, &func3, "func3.data");
    return 0;
}
