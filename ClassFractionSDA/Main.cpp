#include <iostream>
#include <stdexcept>
#include <windows.h>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

    // ������� ��� ���������� ����������� ������ ��������
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

    // ������� ��� ��������� �����
    void simplify()
    {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
    }

public:
    // ����������� �� ���������
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom)
    {
        if (denom == 0)
        {
            throw invalid_argument("����������� �� ����� ���� ����� ����");
        }
        simplify();
    }

    // ������� ��� ����� ������
    void setNumerator(int num)
    {
        numerator = num;
        simplify();
    }

    void setDenominator(int denom)
    {
        if (denom == 0)
        {
            throw invalid_argument("����������� �� ����� ���� ����� ����");
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

    // ���������� ���������� ��� �������������� ��������
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
            throw invalid_argument("������ ������ �� ����");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Fraction(num, denom);
    }

    // ���������� ��������� �����
    friend istream& operator>>(istream& in, Fraction& frac)
    {
        cout << "������� ���������: ";
        in >> frac.numerator;
        cout << "������� �����������: ";
        in >> frac.denominator;
        if (frac.denominator == 0)
        {
            throw invalid_argument("����������� �� ����� ���� ����� ����");
        }
        frac.simplify();
        return in;
    }

    // ���������� ��������� ������
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

        cout << "������� ������ �����:" << endl;
        cin >> f1;
        cout << "������� ������ �����:" << endl;
        cin >> f2;

        Fraction sum = f1 + f2;
        Fraction diff = f1 - f2;
        Fraction prod = f1 * f2;
        Fraction quot = f1 / f2;

        cout << "������ �����: " << f1 << endl;
        cout << "������ �����: " << f2 << endl;
        cout << "�����: " << sum << endl;
        cout << "�������: " << diff << endl;
        cout << "������������: " << prod << endl;
        cout << "�������: " << quot << endl;
    }
    catch (const invalid_argument& e)
    {
        cerr << "������: " << e.what() << endl;
    }

    return 0;
}