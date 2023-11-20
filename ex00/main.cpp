#include "BitcoinExchange.hpp"


int main( int argc, char* argv[] )
{
    try
    {
        BitcoinExchange change( argv[ 1 ] );
        change.parseInfile( argv[ 1 ] );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    static_cast<void>( argc );
    return 0;
}
