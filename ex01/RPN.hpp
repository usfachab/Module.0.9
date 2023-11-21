#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
private:
    std::string argument;
    std::stack<int> stack;
    RPN( const RPN & );
    RPN &operator=( const RPN & );
public:
    RPN( std::string );
    ~RPN();
    void calculate();
    int calc( int, int, char );
};

#endif