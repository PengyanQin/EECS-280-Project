/*  calc.cpp
 *
 *  Created by Pengyan Qin 
 *  on 6/21/15.
 */


#include "Stack.h"
#include "Rational.h"
#include <iostream>
#include <cassert>
#include <string>
#include <cstdlib>
using namespace std;

class compareWithtop{
    Rational top_elt;
public:
    compareWithtop(Rational top_in):top_elt(top_in) {}
    bool operator() (Rational rest){
        return top_elt == rest;
    }
};

int main(){
    Stack<Rational> s;
    string line;
    while(getline(cin, line)){
        for(unsigned int i = 0; i < line.length();){
            if(line[i] == '+'){
                assert(s.size() >= 2);
                Rational right = s.pop();
                Rational left = s.pop();
                Rational res = left + right;
                s.push(res);
            }
            else if(line[i] == '-'){
                assert(s.size() >= 2);
                Rational right = s.pop();
                Rational left = s.pop();
                Rational res = left - right;
                s.push(res);
            }
            else if (line[i] == '*'){
                assert(s.size() >= 2);
                Rational right = s.pop();
                Rational left = s.pop();
                Rational res = left * right;
                s.push(res);
            }
            else if (line[i] == '/'){
                assert(s.size() >= 2);
                Rational right = s.pop();
                Rational left = s.pop();
                Rational res = left / right;
                s.push(res);
            }
            else if(line[i] == 'd'){
                assert(s.size() >= 1);
                Rational copy = s.pop();
                s.push(copy);
                s.push(copy);
            }
            else if(line[i] == 'r'){
                assert(s.size() >= 2);
                Rational first = s.pop();
                Rational second = s.pop();
                s.push(first);
                s.push(second);
            }
            else if(line[i] == 'p'){
                assert(s.size() >= 1);
                cout << s.top() << endl;
            }
            else if(line[i] == 'c'){
                while(!s.empty())
                    s.pop();
            }
            else if(line[i] == 'a'){
                cout << s << endl;
            }
            else if(line[i] == 'n'){
                assert(s.size() >= 1);
                Rational neg(-1);
                s.top() = s.top() * neg;
            }
            else if(line[i] == 'm'){
                assert(s.size() >= 1);
                Rational check = s.pop();
                compareWithtop compare(check);
                Rational res(s.count_if(compare));
                s.push(res);
            }
            else if(line[i] == 'q'){
                 goto stop;
            }
            else{
                string line_sub = line.substr(i);
                int elt = atoi(line_sub.c_str());
                assert(elt >= 0);
                Rational rational(elt);
                s.push(rational);
            }
            while( i < line.length() && line[i] != ' ')
                ++i;
            while(i < line.length() && line[i] == ' ')
                ++i;
        }
    }
stop:
    return 0;
}





