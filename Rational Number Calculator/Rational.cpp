/*  Rational.cpp
 *
 *  Created by Pengyan Qin 
 *  on 6/20/15.
 */

#include <iostream>
#include "Rational.h"
#include <algorithm>

using namespace std;

int GCD(int a, int b){
    if(a < b)
        swap(a, b);
    int r = a%b;
    int d = a/b;
    
    while(r){
        a = b;
        b = r;
        r = a%b;
        d = a/b;
    }
    return b;
}

Rational::Rational(): numerator(0), denominator(1){}

Rational::Rational(int val): numerator(val), denominator(1){}

Rational::Rational(int numerator_in, int denominator_in){
    if(denominator_in == 0){
        denominator = 0;
        if(numerator_in == 0){
            numerator = 0;
        }
        else if(numerator_in > 0){
            numerator = 1;
        }
        else if(numerator_in < 0){
            numerator = -1;
        }
    }
    else if(denominator_in < 0){
        if(numerator_in == 0){
            numerator = 0;
            denominator = 1;
            
        }
        else if(numerator_in > 0){
            denominator_in = -denominator_in;
            int divisor = GCD(numerator_in, denominator_in);
            numerator = -numerator_in/divisor;
            denominator = denominator_in/divisor;
        }
        else if(numerator_in < 0){
            numerator_in = -numerator_in;
            denominator_in = -denominator_in;
            int divisor = GCD(numerator_in, denominator_in);
            numerator = numerator_in/divisor;
            denominator = denominator_in/divisor;
        }
    }
    else if(denominator_in > 0){
        if(numerator_in == 0){
            numerator = 0;
            denominator = 1;
        }
        else if(numerator_in > 0){
            int divisor = GCD(numerator_in, denominator_in);
            numerator = numerator_in/divisor;
            denominator = denominator_in/divisor;
        }
        else if(numerator_in < 0){
            numerator_in = -numerator_in;
            int divisor = GCD(numerator_in, denominator_in);
            numerator = -numerator_in/divisor;
            denominator = denominator_in/divisor;
        }
    }
}

int Rational::get_numerator() const{
    return numerator;
}

int Rational::get_denominator() const{
    return denominator;
}

std::ostream& operator<<(std::ostream& os, const Rational& obj){
    int n = obj.get_numerator();
    int d = obj.get_denominator();
    if(d == 1)
        os << n;
    else
        os << n << "/" << d;
    
    return os;
}

Rational operator+(const Rational &lhs, const Rational &rhs){
    int n = lhs.get_numerator() * rhs.get_denominator() + lhs.get_denominator() * rhs.get_numerator();
    int d = lhs.get_denominator() * rhs.get_denominator();
    Rational res(n, d);
    return res;
}

Rational operator-(const Rational &lhs, const Rational &rhs){
    int n = lhs.get_numerator() * rhs.get_denominator() - lhs.get_denominator() * rhs.get_numerator();
    int d = lhs.get_denominator() * rhs.get_denominator();
    Rational res(n, d);
    return res;
}

Rational operator*(const Rational &lhs, const Rational &rhs){
    int n = lhs.get_numerator() * rhs.get_numerator();
    int d = lhs.get_denominator() * rhs.get_denominator();
    Rational res(n, d);
    return res;
}

Rational operator/(const Rational &lhs, const Rational &rhs){
    int n = lhs.get_numerator() * rhs.get_denominator();
    int d = lhs.get_denominator() * rhs.get_numerator();
    Rational res(n, d);
    return res;

}

bool operator==(const Rational &lhs, const Rational &rhs){
    return (lhs.get_numerator() == rhs.get_numerator()) &&
    (lhs.get_denominator() == rhs.get_denominator());
    
}




