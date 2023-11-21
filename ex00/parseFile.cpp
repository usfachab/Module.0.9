#include "BitcoinExchange.hpp"

void BitcoinExchange::parseInfile( std::string filename ) const
{
    std::ifstream infile( filename );

    parseInfileFirstLine( infile );

    std::string line, date;

    while ( std::getline( infile, line ) )
    {
        while ( infile.peek() == '\n' )
            infile.ignore();
        strtrim( line );
        if ( !line.empty() )
            legitLine( line );
    }
}

void BitcoinExchange::strtrim( std::string& line ) const
{
    size_t bpos ( line.find_first_of( " \t\n\r\f\v" ) );
    size_t epos ( line.find_first_not_of( " \t\n\r\f\v" ) );

    if ( bpos ==  0 && epos ==  std::string::npos )
        line.erase( 0 );

    if ( bpos !=  std::string::npos && epos !=  std::string::npos )
        line.erase( bpos,  epos );

    size_t lpos ( line.find_last_not_of( " \t\n\r\f\v" ) );

    if ( lpos != std::string::npos )
        line.erase( lpos + 1 );
}
void BitcoinExchange::parseInfileFirstLine( _ifs& infile ) const
{
    try
    {
        std::string line;
        while ( infile.peek() == '\n' )
            infile.ignore();

        std::getline( infile, line );
        strtrim( line );

        if ( line != "date | value" )
            throw std::invalid_argument( "Error: input file first line is curropted." );

        while ( infile.peek() == '\n' )
            infile.ignore();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void BitcoinExchange::legitLine( std::string& line ) const
{
    std::string date;
    float value;
    try
    {
        date = legitDate( line );
        value = legitValue( line );
        if ( value > 1000 )
            throw std::invalid_argument( "Error: too large number." );
        else
        {
            iterator itlow = dataBase.lower_bound( date );
            std::cout << date << " => " << value  << " = "<<  itlow->second * value << std::endl;
        }
    }
    catch( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
}

std::string BitcoinExchange::legitDate( const std::string& line ) const
{
    struct tm tm;
    std::string date;
    std::stringstream ss( line );
    std::getline( ss, date, '|' );

    if ( date.length() != 11 || date.find_last_of( ' ' ) == std::string::npos )
        throw std::invalid_argument( "Error: bad input => " + date );
    else if ( !strptime( date.c_str(), "%Y-%m-%d", &tm ) )
        throw std::invalid_argument( "Error: bad input => " + date );
    strtrim( date );
    return ( date );
}

float BitcoinExchange::legitValue( std::string& line ) const
{
    int point ( 0 );
    bool digit ( true );
    std::string value ( line.substr( 12 ) );

    if ( value.empty() )
        throw std::invalid_argument( "Error: bad input value." );
    if ( value.at( 0 ) != 32 || !std::isdigit( value.at( 1 ) ) )
    {
        if ( value.at( 1 ) == '-' )
            throw std::invalid_argument( "Error: not a positive number.");
        else
            throw std::invalid_argument( "Error: bad input => " + value );
    }

    strtrim( value );
    for ( size_t i = 0; i < value.length(); i++ )
    {
        if ( value.at( i ) == '.' ) { point++; continue ; }
        if ( !std::isdigit( value.at( i ) ) ) digit = false;
    }

    if ( point > 1 || !digit )
        throw std::invalid_argument( "Error: bad input => " + value );
    
    return ( std::stof( value ) );
}
