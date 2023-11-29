#include "BitcoinExchange.hpp"

void BitcoinExchange::parseInfile( std::string filename ) const
{
    std::ifstream infile( filename );

    parseInfileFirstLine( infile );

    std::string line, date;
    std::cout << std::setprecision( 7 ); 
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

bool BitcoinExchange::whitespace( _ifs& infile ) const
{
    if ( infile.peek() == '\n' || infile.peek() == ' ' )
        return ( true );
    else if ( infile.peek() == '\f' || infile.peek() == '\r' )
        return ( true );
    else if ( infile.peek() == '\t' || infile.peek() == '\v' )
        return ( true );
    else
        return ( false );
}

void BitcoinExchange::parseInfileFirstLine( _ifs& infile ) const
{
    try
    {
        std::string line;
        while ( whitespace( infile ) )
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
            if ( itlow == dataBase.end() )
                --itlow;
            std::cout << itlow->first << " => " << value;
            std::cout << " = " <<  itlow->second * value << std::endl;
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
        throw std::invalid_argument( "Error: bad input => " + line );
    else if ( !strptime( date.c_str(), "%Y-%m-%d", &tm ) )
        throw std::invalid_argument( "Error: bad input => " + line );
    if ( !validate( date ) )
        throw std::invalid_argument( "Error: bad input => " + line );
    strtrim( date );
    return ( date );
}

bool BitcoinExchange::validate( std::string& date ) const
{
    unsigned int year;
    unsigned int month;
    unsigned int day;

    year    =   std::stoi( date.substr( 0, 4) );
    month   =   std::stoi( date.substr( 5, 2) );
    day     =   std::stoi( date.substr( 8, 2 ) );

    if ( year < 2009 || ( year <= 2009 && month <= 1 && day < 2 )  )
        return ( false );

    switch ( month )
    {
        case 4  :
        case 6  :  
        case 9  :
        case 11 : if ( day > 30 ) return ( false );
        case 2  : if ( !february( year, day ) ) return ( false );
        default:
            return ( true );
    }
}

bool BitcoinExchange::february( unsigned int year, unsigned int day ) const
{
    if ( day > 29 )
        return ( false );
    if ( day == 29 )
    {
        if ( year % 4 == 0 )
        {
            if ( year % 100 == 0 )
            {
                if ( year % 400 == 0 )
                    return ( true );
                else
                    return ( false );
            }
            else
                return ( true );
        }
        else
            return ( false );
    }
    return ( true );
}

float BitcoinExchange::legitValue( std::string& line ) const
{
    float x = 0.0f;
    int plusidx = -1;
    int minusidx = -1;
    int point = 0, space = 0;
    bool ndigi = true;
    std::string valueStr = line.substr( 12 );
    
    for ( size_t i = 0; i < valueStr.size(); i++ )
    {
        if ( valueStr.at( i ) == ' ' )
        {
            space++;
            continue ;
        }
        if ( valueStr.at( i ) == '.' )
        {
            point++;
            continue ;
        }
        if ( valueStr.at( i ) == '-' )
        {
             minusidx = i;
             continue ;
        }
        if ( valueStr.at( i ) == '+'  )
        {
            plusidx = i;
            continue ;
        }
        if ( !isdigit( valueStr.at( i ) ) )
            ndigi = false;
    }
    if ( space != 1 || point > 1 || ndigi == false || minusidx > 1 || plusidx > 1 )
        throw std::invalid_argument( "Error: bad input => " + line );
    try
    {
        x = std::stof( valueStr );
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument( "Error: bad input => " + line );
    }
    if ( x < 0 )
        throw std::invalid_argument( "Error: not a positive number.");
    if ( x > 1000 )
        throw std::invalid_argument( "Error: too large a number.");
    return ( x );

}
