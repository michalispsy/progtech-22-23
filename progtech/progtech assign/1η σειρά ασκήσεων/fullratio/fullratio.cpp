#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

int rational::gcd(int a, int b)
{
    if(a==0 || b==0) return a+b;
    else if(a>b) return gcd(a%b, b);
    else return gcd(b%a, a);
}

rational::rational (int n, int d) 
{
    nom = n;
    den = d;
}

rational operator + (const rational &x, const rational &y) 
{
    return rational(x.nom * y.den + y.nom * x.den, y.den * x.den);
}

rational operator - (const rational &x, const rational &y)
{
    return rational(x.nom * y.den - x.den * y.nom, y.den * x.den);
}

rational operator * (const rational &x, const rational &y)
{
    return rational(x.nom*y.nom, x.den*y.den);
}

rational operator / (const rational &x, const rational &y)
{
    return rational( x.nom * y.den, x.den*y.nom);
}

ostream & operator << (ostream &out, const rational &x)
{
    if(x.nom < 0 && x.den >=0 || x.den < 0 && x.nom >0) out << '-';

    int q = rational::gcd(abs(x.nom), abs(x.den));
    out << abs(x.nom) / q << '/' << abs(x.den) / q;
    return out;
}