#include "RPN.hpp"

RPN::RPN( std::string arg ) : argument ( arg ) {}

RPN::RPN( const RPN& obj ) { *this = obj; }

RPN& RPN::operator=( const RPN& rhs )
{
    if ( this != &rhs )
        argument = rhs.argument;
    return ( *this );
}

RPN::~RPN() {}

void RPN::calculate()
{
    float _v1, _v2, _v3;

    for ( size_t i = 0; i < argument.length(); i++ )
    {
        if ( isdigit( argument.at( i ) ) )
            stack.push( argument.at( i ) - 48 );
        else if ( argument.at( i ) != ' ' )
        {
            if ( stack.size() < 2 )
                throw std::invalid_argument( "Error" );
            _v2 = stack.top();
            stack.pop();
            _v1 = stack.top();
            stack.pop();
            _v3 = calc( _v1, _v2, argument.at( i ) );
            stack.push( _v3 );
        }
    }
    if ( stack.size() == 1 )
        printf( "%g\n",  stack.top() );
    else
        throw std::invalid_argument( "Error" );
}

float RPN::calc( float v1, float v2, char opr )
{
    switch ( opr )
    {
        case '+': return ( v1 + v2 );
        case '-': return ( v1 - v2 );
        case '*': return ( v1 * v2 );
        case '/':
            if ( v1 == 0 && v2 == 0 ) throw std::invalid_argument( "NaN" );
            if ( v2 == 0 ) throw std::invalid_argument( "infinity" );
            return ( v1 / v2 );
        default:
            throw std::invalid_argument( "invalid operator" );
    }
}