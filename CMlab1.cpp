#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double eps = 0.0001;
double equation(double x) { return (x*x*x*x) + 4*(x*x*x) - x*x - (4 * x) - 1; }
double simpleEq(double x) { return ((x*x*x*x) + 4*(x*x*x) - x*x - 1) / 4; }
double proizv(double x) { return 4*(x*x*x) + 12 *(x*x) - 2*x-4; }
double proizv2(double x) { return 12*(x*x)+24*x-2; }

void iterations(double a, double b)
{
    unsigned int it = 1;
    double x = a;   
    double next = simpleEq(x);
    
    while ((fabs(x - next) > eps) && it < 100) {
        x = next;
        next = simpleEq(x);
        ++it;
    }

    cout << setprecision(4) << "\nМетод простой итерации - " << next << ", количество итераций - " << it;
}

void divisions(double a, double b)
{
    unsigned int it = 0;
    double res = 0, c = 0;

    while (abs(a - b) > eps && it < 100) {
        c = (a + b) * 0.5;
        if (equation(a) * equation(c) < 0)
            b = c;
        else
            a = c;
        res = (a + b) * 0.5;
        ++it;
    }

    cout << setprecision(4) << "\nМетод половинного деления - " << res << ", количество итераций - " << it;
}

void chords(double a, double b)
{
    int it = 0;
    double res = 0;
    double c = 0;
   
    if ((a > 0 && proizv2(a) > 0) || (a < 0 && proizv2(a) < 0)) {
        double tmp = a;
        a = b;
        b = tmp;
    }
  
    c = a - (equation(a) * (a - b) / (equation(a) - equation(b)));
    while ((fabs(c - a) > eps) && it <=100) {
        a = c;
        c = a - (equation(a) * (a - b) / (equation(a) - equation(b)));
        ++it;
    }

    cout << setprecision(4) << "\nМетод хорд - " << c << ", количество итераций - " << it;
}

void newtons(double a, double b)
{
    int it = 0;
    while (fabs(a - b) > eps && it < 100){
        ++it;
        a = b;
        b = a - (equation(a) / proizv(a));
    }

    cout << setprecision(4) << "\nМетод Ньютона - " << b << ", количество итераций - " << it;
}

int main()
{
    setlocale(LC_ALL, "rus");

    double a,b;
    cout << "\nЛевая граница - ";
    cin >> a;

    cout << "\nПравая граница - ";
    cin >> b;
   
    iterations(a,b);
    divisions(a,b);
    chords(a,b);
    newtons(a,b);

    return 0;
}