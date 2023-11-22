#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe( const PmergeMe& obj ) { *this = obj; }

PmergeMe& PmergeMe::operator=( const PmergeMe& rhs )
{
    // if ( this != &rhs )
    return ( *this );
}

PmergeMe::~PmergeMe() {}

