#include "RPN.hpp"

int main(int argc, char const *argv[])
{
    try
    {
        if ( argc != 2 )
            throw std::invalid_argument( "usage: ./RPN \"operand operand operator\"" );
        RPN rpn( argv[ 1 ] );
        rpn.calculate();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
