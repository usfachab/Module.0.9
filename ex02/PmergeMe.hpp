#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe( const PmergeMe & );
    PmergeMe &operator=( const PmergeMe & );
    ~PmergeMe();
};

#endif