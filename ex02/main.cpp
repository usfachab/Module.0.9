#include "PmergeMe.hpp"

int main( int argc, char const **argv )
{
    
    if ( argc == 1 )
    {
        std::cerr << "Error: more than one argument required" << std::endl;
        return 0;
    }
    try
    {
        struct timeval st,et;
        PmergeMe obj;

        {
            std::vector<int> vec;
            gettimeofday( &st,NULL );
            obj.fillContainer( vec, argc, argv );
            obj.printResult( vec, "before: " );
            obj.startMerge<std::vector<int> >( vec );
            gettimeofday( &et,NULL );
            obj.printResult( vec, "after: " );
            obj.printime( st, et, "std::vector", argc );
        }

        {
            std::deque<int> deq;
            gettimeofday( &st,NULL );
            obj.fillContainer( deq, argc, argv );
            obj.startMerge<std::deque<int> >( deq );
            gettimeofday( &et,NULL );
            obj.printime( st, et, "std::deque", argc );
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}
