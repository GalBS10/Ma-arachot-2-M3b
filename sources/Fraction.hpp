#ifndef FRACTION
#define FRACTION
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace ariel
{

}
class Fraction
{

private:
    int numerator;
    int denominator;

public:
    Fraction(); //Default
    Fraction(float number);
    Fraction(int numer, int denomin);
    int getNumerator() const;
    int getDenominator() const;

    Fraction operator+(const Fraction& fraction) const;
    Fraction operator+(float number) const;
    friend Fraction operator+(float number, const Fraction &fraction);

    Fraction operator-(const Fraction& fraction) const;
    Fraction operator-(float number) const;
    friend Fraction operator-(float number, const Fraction &fraction);

    Fraction operator/(const Fraction& fraction) const;
    Fraction operator/(float number) const;
    friend Fraction operator/(float number, const Fraction &fraction);

    Fraction operator*(const Fraction& fraction) const;
    Fraction operator*(float number) const;
    friend Fraction operator*(float number, const Fraction &fraction);

    Fraction &operator++();   // prefix++ operator
    Fraction &operator--();   // prefix -- operator
    Fraction operator++(int); // postfix ++ operator
    Fraction operator--(int); // postfix -- operator

    bool operator>(const Fraction& fraction) const;
    bool operator>(float number) const;
    friend bool operator>( float number, const Fraction &fraction1);

    bool operator<(const Fraction& fraction) const;
    bool operator<(float number) const;
    friend bool operator<(float number, const Fraction &fraction1);

    bool operator>=( const Fraction &fraction) const;
    bool operator>=(float number) const;
    friend bool operator>=(float number, const Fraction &fraction);


    bool operator<=(const Fraction &fraction) const;
    bool operator<=(float number) const;
    friend bool operator<=(float number, const Fraction &fraction);

    bool operator==(const Fraction &fraction) const;
    bool operator==(float number) const;
    friend bool operator==(float number, const Fraction &fraction);
    
    friend std::ostream &operator<<(std::ostream &_ostream, const Fraction &fraction);
    friend std::istream &operator>>(std::istream &_istream, Fraction &fraction);

    void minimilize();
    int gcd(int numer, int denom);
    static Fraction convert(float number);
};
#endif
