#include "RPN.hpp"

int main(int argc, char const *argv[])
{
    if ( argc != 2 )
    {
        std::cerr << "usage: ./RPN \"operand operand operator\"" << std::endl;
        return ( 1 );
    }

    try
    {
        RPN rpn( argv[ 1 ] );
        rpn.calculate();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return 0;
}
