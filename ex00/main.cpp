#include "BitcoinExchange.hpp"


int main( int argc, char* argv[] )
{
    try
    {
        if ( argc < 2 || argc > 3)
            throw std::invalid_argument( "usage: btc infile database" );
        BitcoinExchange change( argv );
        change.parseInfile( argv[ 1 ] );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
