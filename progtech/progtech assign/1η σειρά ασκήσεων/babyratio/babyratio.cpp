#ifndef CONTEST
#include "babyratio.hpp"
#endif
#include <iostream>
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

rational rational::add (rational r)
{   
    r.nom = r.nom * den + nom * r.den;
    r.den = den * r.den;

    return r;
}

rational rational::sub (rational r)
{   
    r.nom = nom * r.den - r.nom * den;
    r.den = den * r.den;

    return r;
}

rational rational::mul (rational r)
{   
    r.nom = nom * r.nom;
    r.den = den * r.den;

    return r;
}

rational rational::div (rational r)
{   
    int temp = r.nom;
    r.nom = nom * r.den;
    r.den = den * temp;
    
    return r;
}

void rational::print()
{
    if(nom < 0 && den >=0 || den < 0 && nom >0) cout << '-';

    int q = gcd(abs(nom), abs(den));
    nom = abs(nom) / q;
    den = abs(den) / q;
    
    cout << nom << "/" << den;
}