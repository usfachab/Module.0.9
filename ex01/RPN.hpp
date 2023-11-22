#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
private:
    std::string argument;
    std::stack<float> stack;
public:
    RPN( std::string );
    RPN( const RPN & );
    RPN &operator=( const RPN & );
    ~RPN();

    void calculate();
    float calc( float, float, char );
};

#endif