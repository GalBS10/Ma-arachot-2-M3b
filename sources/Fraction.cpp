#include "Fraction.hpp"
#include <cmath>

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
        // if(numer < 0 && denomin < 0){// if both negetive then its positive number.
        //     numer = 0-numer;
        //     denomin = 0-denomin;
        // }
        int _gcd = gcd(numer, denomin);
        numerator = numer / _gcd;
        denominator = denomin / _gcd;
}

Fraction Fraction::convert(float number){
    return Fraction(int(1000*number),1000);
}

Fraction::Fraction(float number)
{
    numerator = int(number*1000);
    denominator = 1000;
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
Fraction Fraction::operator+(const Fraction &fraction) const
{ // plus
    int new_num = numerator * fraction.getDenominator() + denominator * fraction.getNumerator();
    int new_den = denominator * fraction.getDenominator();
    Fraction answer(new_num, new_den);
    answer.minimilize(); // to check if it can be removed
    return answer;
}

Fraction Fraction::operator-(const Fraction &fraction) const
{ // minus
    int new_num = numerator * fraction.getDenominator() - denominator * fraction.getNumerator();
    int new_den = denominator * fraction.getDenominator();
    Fraction answer(new_num, new_den);
    answer.minimilize();
    return answer;
}

Fraction Fraction::operator/(const Fraction &fraction) const
{ // devision
    int new_num = numerator * fraction.getDenominator();
    int new_den = denominator * fraction.getNumerator();
    Fraction answer(new_num, new_den);
    answer.minimilize();
    return answer;
}

Fraction Fraction::operator*(const Fraction &fraction) const
{ // multiply
    int new_num = numerator * fraction.getNumerator();
    int new_den = denominator * fraction.getDenominator();
    Fraction answer(new_num, new_den);
    answer.minimilize();
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
    os << fraction.getNumerator() << "/" << fraction.getDenominator();
    return os;
}

std::istream &operator>>(std::istream & istream, Fraction &fraction){

    istream >> fraction.numerator;
    if (istream.rdbuf()->in_avail() == 0){ //found tihs check on stackoverflow.
        throw invalid_argument("needs to put two numbers");
    }
    istream >> fraction.denominator;
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
    return numerator == fraction.numerator && denominator == fraction.denominator;
}

bool Fraction::operator==(float number) const
{
    return *this == convert(number);
}

bool operator==(float number, const Fraction &fraction)
{
    return Fraction::convert(number) == fraction;
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
