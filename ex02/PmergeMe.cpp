#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe( const PmergeMe& obj ) { *this = obj; }

PmergeMe& PmergeMe::operator=( const PmergeMe& rhs )
{
    static_cast<void>( rhs );
    return ( *this );
}

PmergeMe::~PmergeMe() {}

void PmergeMe::printime( struct timeval ST,struct timeval ET , std::string str, int argc ) const
{
    long micro = (ET.tv_sec - ST.tv_sec) * 1000000 + (ET.tv_usec - ST.tv_usec);
	double time = micro / 1000.0;

    std::cout << "Time to process a range of " << argc - 1;
    std::cout << " elements with " <<  str << " : ";
    std::cout << time << " us" << std::endl;
}
