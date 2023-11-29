#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <sys/time.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>

class PmergeMe
{
private:
    template<typename C>
    void devide( C& container, int start, int end ) const
    {
        if ( start >= end ) return ;

        int mid = ( start + end ) / 2;

        devide( container, start, mid );
        devide( container, mid + 1, end );
        mergeSort( container, start, mid, end );
    }
    template<typename C>
    void mergeSort( C& container, int start , int mid, int end ) const
    {
        int left_length     ( mid - start + 1 );
        int right_length    ( end - mid );

        C left_container;
        C right_container;

        for ( int i = 0; i < left_length; i++ )
            left_container.push_back( container.at( start + i ) );

        for ( int i = 0; i < right_length; i++ )
            right_container.push_back( container.at( mid + 1 + i ) );

        for ( int i = 0, j = 0, k = start; k <= end; k++ )
        {
            if ( i < left_length &&
            ( j >= right_length || left_container.at( i ) <= right_container.at( j ) ) )
                container.at( k ) = left_container.at( i++ );
            else
                container.at( k ) = right_container.at( j++ );
        }
    } 
public:
    PmergeMe();
    PmergeMe( const PmergeMe& );
    PmergeMe &operator=( const PmergeMe& );
    ~PmergeMe();

    template<typename C>
    void fillContainer( C& container,int argc, const char *argv[] ) const
    {
        for ( int i = 1; i < argc; i++ )
        {
            int value = std::stoi( argv[ i ] );
            if ( value < 0 )
                throw std::invalid_argument( "Error: positive numbers only." );
            container.push_back( value );
        }
    }

    template<typename C>
    void startMerge( C& container ) const
    {
        int start   ( 0 );
        int end     ( container.size() - 1 );

        devide( container, start, end );
    }

    template <typename C>
    void printResult( const C&  container, std::string prefix ) const
    {
        typedef typename C::const_iterator iterator;
        std::cout << prefix;
        for ( iterator it = container.begin() ; it != container.end(); it++ )
            std::cout << *it << " ";
        std::cout << std::endl;
    }

    void printime( struct timeval ,struct timeval, std::string, int  ) const;
};

#endif