#include <iostream>
#include <stdexcept>
#include <windows.h>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

    // Функция для нахождения наибольшего общего делителя
    int gcd(int a, int b) const
    {
        while (b != 0)
        {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    // Функция для упрощения дроби
    void simplify()
    {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
    }

public:
    // Конструктор по умолчанию
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom)
    {
        if (denom == 0)
        {
            throw invalid_argument("Знаменатель не может быть равен нулю");
        }
        simplify();
    }

    // Функции для ввода данных
    void setNumerator(int num)
    {
        numerator = num;
        simplify();
    }

    void setDenominator(int denom)
    {
        if (denom == 0)
        {
            throw invalid_argument("Знаменатель не может быть равен нулю");
        }
        denominator = denom;
        simplify();
    }

    int getNumerator() const
    {
        return numerator;
    }

    int getDenominator() const
    {
        return denominator;
    }

    // Перегрузка операторов для арифметических операций
    Fraction operator+(const Fraction& other) const
    {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator-(const Fraction& other) const
    {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator*(const Fraction& other) const
    {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator/(const Fraction& other) const
    {
        if (other.numerator == 0)
        {
            throw invalid_argument("Нельзя делить на ноль");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Fraction(num, denom);
    }

    // Перегрузка оператора ввода
    friend istream& operator>>(istream& in, Fraction& frac)
    {
        cout << "Введите числитель: ";
        in >> frac.numerator;
        cout << "Введите знаменатель: ";
        in >> frac.denominator;
        if (frac.denominator == 0)
        {
            throw invalid_argument("Знаменатель не может быть равен нулю");
        }
        frac.simplify();
        return in;
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& out, const Fraction& frac)
    {
        out << frac.numerator << "/" << frac.denominator;
        return out;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try
    {
        Fraction f1;
        Fraction f2;

        cout << "Введите первую дробь:" << endl;
        cin >> f1;
        cout << "Введите вторую дробь:" << endl;
        cin >> f2;

        Fraction sum = f1 + f2;
        Fraction diff = f1 - f2;
        Fraction prod = f1 * f2;
        Fraction quot = f1 / f2;

        cout << "Первая дробь: " << f1 << endl;
        cout << "Вторая дробь: " << f2 << endl;
        cout << "Сумма: " << sum << endl;
        cout << "Разница: " << diff << endl;
        cout << "Произведение: " << prod << endl;
        cout << "Частное: " << quot << endl;
    }
    catch (const invalid_argument& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}