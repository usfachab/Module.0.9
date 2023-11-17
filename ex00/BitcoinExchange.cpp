#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( const char* filename )
{
    std::ifstream infile( filename );
    std::ifstream dbfile( "data.csv" );

    if ( !infile.is_open() || !dbfile.is_open() )
        throw std::invalid_argument( "Error: could not open file." );
    else
    {
        parseInfile( infile );
        parseDbfile( dbfile );
    }
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& obj ) { *this = obj; }

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& rhs )
{
    static_cast<void>( rhs ); return ( *this );
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parseInfile( ifstm& infile ) const
{
    parseInfileFirstLine( infile );

    std::string line;
    std::string date;

    while ( std::getline( infile, line ) )
    {
        while ( infile.peek() == '\n' )
            infile.ignore();

        strtrim( line );
        
        date = line.substr( 0, 10 );
        if ( date.empty() )
            continue ;
        
        validDate( line );
         
            
    }
}
void BitcoinExchange::parseDbfile( ifstm& dbfile ) const
{
    (void) dbfile;
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
void BitcoinExchange::parseInfileFirstLine( ifstm& infile ) const
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

void BitcoinExchange::validDate( std::string& date ) const
{
    std::string year, month, day;
    std::stringstream ss( date );

    std::getline( ss, year, '-' );
    std::getline( ss, month, '-' );
    std::getline( ss, day );

    std::cout << year << "-" << month << "-" << day << std::endl;

}

// struct tm tm;
// if ( strptime( date.c_str(), "%Y-%m-%d", &tm) )
//             std::cout << "date is valid" << std::endl;
// else
//     std::cout << "date is invalid" << std::endl;