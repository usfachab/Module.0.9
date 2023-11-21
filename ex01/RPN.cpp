#include "RPN.hpp"

RPN::RPN( std::string arg ) : argument ( arg ) {}

RPN::RPN( const RPN& obj ) { static_cast<void>( obj ); }

RPN& RPN::operator=( const RPN& rhs ) { static_cast<void>( rhs ); return ( *this ); }

RPN::~RPN() {}

void RPN::calculate()
{
    std::stringstream ss( argument );
    std::string value;
    int _v1;
    int _v2;
    int _v3;

    while ( std::getline( ss, value, ' ' ) )
    {
        if ( value.length() > 1)
            throw std::invalid_argument( "Error" );
        if ( isdigit( value.at( 0 ) ) )
            stack.push( std::stoi( value ) );
        else if ( !isdigit( value.at( 0 ) ) )
        {
            if ( stack.size() < 2 )
                throw std::invalid_argument( "Error" );
            _v1 = stack.top();
            stack.pop();
            _v2 = stack.top();
            stack.pop();
            _v3 = calc( _v2, _v1, value.at( 0 ) );
            stack.push( _v3 );
        }
    }
    std::cout << stack.top() << std::endl;
}

int RPN::calc( int v1, int v2, char opr )
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