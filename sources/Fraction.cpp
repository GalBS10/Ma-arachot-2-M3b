#include "Fraction.hpp"
#include <cmath>

//people i have talked to:
//-Lidor Keren Yeshua
//

Fraction::Fraction()
{
    Fraction(1,1);
}

Fraction::Fraction(int numer, int denomin)
{ // constructor
    if (denomin == 0)
    {
        throw std::invalid_argument("Division by zero exception");//found this throw in stackoverflow.
    }
    if(numer < 0 && denomin < 0){// if both negetive then its positive number.
        numer = 0-numer;
        denomin = 0-denomin;
    }
    int _gcd = gcd(numer, denomin);
    numerator = numer / _gcd;
    denominator = denomin / _gcd;
}

Fraction::Fraction(float number)
{
    numerator = int(number*1000);
    denominator = 1000;
}

void Fraction::convert (Fraction &fraction)
{
    float result = static_cast<float>(fraction.getNumerator()) / static_cast<float>(fraction.getDenominator());
    result = roundf(result * 1000); // round to 3 decimal places
    fraction.numerator = result;
    fraction.denominator = 1000;
}

Fraction Fraction::convert(float number)
{
    return Fraction(int(1000*number),1000);
}


// getters
int Fraction::getNumerator() const
{
    return numerator;
}

int Fraction::getDenominator() const
{
    return denominator;
}

// operators only with Fractions
Fraction Fraction::operator+(const Fraction& fraction) const {
    int new_num = numerator * fraction.getDenominator() + denominator * fraction.getNumerator();
    int new_den = denominator * fraction.getDenominator();

    // float sum_float = float(new_num) / float(new_den);
    // sum_float = round(sum_float * 1000.0) / 1000.0;

    // Fraction sum_fraction(sum_float);
    // sum_fraction.minimilize();
    // return sum_fraction;
    Fraction answer(new_num, new_den);
    // answer.minimilize();
    return answer;
}


Fraction Fraction::operator-(const Fraction &fraction) const
{ // minus
    int new_num = numerator * fraction.getDenominator() - denominator * fraction.getNumerator();
    int new_den = denominator * fraction.getDenominator();
    Fraction answer(new_num, new_den);
    // answer.minimilize();
    return answer;
}

Fraction Fraction::operator/(const Fraction &fraction) const
{ // devision
    if(fraction.numerator == 0){
        throw std::runtime_error("Division by zero exception");
    }
    int new_num = numerator * fraction.getDenominator();
    int new_den = denominator * fraction.getNumerator();
    Fraction answer(new_num, new_den);
    // answer.minimilize();
    return answer;
}

Fraction Fraction::operator*(const Fraction &fraction) const
{ // multiply
    int new_num = numerator * fraction.getNumerator();
    int new_den = denominator * fraction.getDenominator();
    Fraction answer(new_num, new_den);
    // answer.minimilize();
    return answer;
}

Fraction &Fraction::operator++()
{ // plus 1 and then execute
    numerator += denominator;
    return *this;
}

Fraction &Fraction::operator--()
{ // minus 1 and then execute
    numerator -= denominator;
    return *this;
}

Fraction Fraction::operator++(int)
{ // execute and then plus 1
    Fraction result = *this;
    numerator += denominator;
    return result;
}

Fraction Fraction::operator--(int)
{ // execute and then minus 1
    Fraction result = *this;
    numerator -= denominator;
    return result;
}

// operators with consts and Fractions
// plus
Fraction Fraction::operator+(float number) const
{ 
    return *this+convert(number);
}

Fraction operator+(float number, const Fraction &fraction){
    return Fraction::convert(number)+fraction;//because its a "friend" function we need to use ::
}
// minus
Fraction Fraction::operator-(float number) const
{ 
    return *this-convert(number);
}

Fraction operator-(float number, const Fraction &fraction){
    return Fraction::convert(number)-fraction;
}
// devision
Fraction Fraction::operator/(float number) const
{ 
    return *this/convert(number);
}

Fraction operator/(float number, const Fraction &fraction)
{
    return Fraction::convert(number)/fraction;
} 
// multiply
Fraction Fraction::operator*(float number) const
{ 
    return *this* Fraction::convert(number);
}

Fraction operator*(float number, const Fraction &fraction)
{
    return Fraction::convert(number)*fraction;
}

std::ostream &operator<<(std::ostream &os, const Fraction &fraction)
{ // to string
    float numer = fraction.getNumerator();
    float denom = fraction.getDenominator();
    if(numer<0 || denom<0){
        numer = abs(numer);
        denom = abs(denom);
        os << "-";
    }
    os << numer << "/" << denom;
    return os;
}

std::istream &operator>>(std::istream & istream, Fraction &fraction)
{
    if (istream.rdbuf()->in_avail() == 0){ //found this check on stackoverflow.
        throw runtime_error("needs to put two numbers");
    }
    istream >> fraction.numerator;
    if (istream.rdbuf()->in_avail() == 0){ //found this check on stackoverflow.
        throw runtime_error("needs to put two numbers");
    }
    istream >> fraction.denominator;
    if(fraction.denominator == 0){
        throw std::runtime_error("Division by zero exception");
    }
    return istream;
}


// boolean

// bigger
bool Fraction::operator>(const Fraction &fraction) const
{ 
    return (float)numerator / denominator > (float)fraction.getNumerator() / fraction.getDenominator();
}

bool Fraction::operator>(float number) const
{
    return *this>Fraction::convert(number);
}

bool operator>( float number, const Fraction &fraction1)
{
    return Fraction::convert(number)>fraction1;
}

// smaller
bool Fraction::operator<(const Fraction &fraction) const
{
    return (float)numerator / denominator < (float)fraction.getNumerator() / fraction.getDenominator();
}

bool Fraction::operator<(float number) const
{ 
    return *this < Fraction::convert(number);
}
bool operator<(float number, const Fraction &fraction1)
{
    return Fraction::convert(number) < fraction1;
}

// bigger or equal to
bool Fraction::operator>=(const Fraction &fraction) const
{ 
    return (float)numerator / denominator >= (float)fraction.getNumerator() / fraction.getDenominator();
}

bool Fraction::operator>=(float number) const
{
    return *this >= convert(number);
}

bool operator>=(float number, const Fraction &fraction)
{
    return Fraction::convert(number) >= fraction;
}

// smaller or equal to
bool Fraction::operator<=(const Fraction &fraction) const
{ 
    return (float)numerator / denominator <= (float)fraction.getNumerator() / fraction.getDenominator();
}

bool Fraction::operator<=(float number) const
{
    return *this <= convert(number);
}

bool operator<=(float number, const Fraction &fraction)
{
    return Fraction::convert(number) <= fraction;
}

// equal
bool Fraction::operator==(const Fraction &fraction) const
{
    // if(numerator != fraction.numerator){
    //     cout << "numerator difference : " << numerator << " != " << fraction.numerator << endl;
    // }
    // if(denominator != fraction.denominator)
    // {
    //     cout << "denominator difference : " << denominator << " != " << fraction.numerator << endl;
    // }

    // return numerator == fraction.numerator && denominator == fraction.denominator;

    float number1 = round(1000*float(numerator)/denominator)/1000.0;
    float number2 = round(1000*float(fraction.numerator)/fraction.denominator)/1000.0;

    return number1 == number2;


}

bool Fraction::operator==(float number) const
{
    return *this == convert(number);
}

bool operator==(float number, const Fraction &fraction)
{
    float number2 = round(1000*float(fraction.numerator)/fraction.denominator)/1000.0;
    return number == number2;
}


//side functions
void Fraction::minimilize()
{

    int _gcd = gcd(getNumerator(), getDenominator()); // minimalizing the Fraction.
    if (_gcd != 1)
    {
        numerator = getNumerator() / _gcd;
        denominator = getDenominator() / _gcd;
    }
    // else nothing happens
}

int Fraction::gcd(int numer, int denom)//found this code on the internet.
{ // getting the max num that divide both of the numerator and denominator.
    if (denom != 0)
        return gcd(denom, numer % denom);
    else
        return numer;
}
