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
    // float value;
    try
    {
        date = legitDate( line );
        // value = legitValue( line );
    }
    catch( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
}

const std::string& BitcoinExchange::legitDate( const std::string& line ) const
{
    struct tm tm;
    std::string date;
    std::stringstream ss( line );
    std::getline( ss, date, '|' );

    if ( date.length() != 11 || date.find_last_of( ' ' ) == std::string::npos )
        throw std::invalid_argument( "Error: bad input => " + date );
    if ( !strptime( date.c_str(), "%Y-%m-%d", &tm ) )
        throw std::invalid_argument( "Error: bad input => " + date );

    return ( line );
}
