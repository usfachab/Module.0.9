#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( char** argv )
{
    _ifs infile( argv[ 1 ] );

    std::string str;

    if ( argv[ 2 ] )
        str = argv[ 2 ];
    else    
        str = "data.csv" ;

    _ifs dbfile( str.c_str() );

    if ( !infile.is_open() || !dbfile.is_open() )
        throw std::invalid_argument( "Error: could not open file." );
    else
        saveDatabase( dbfile );
    infile.close();
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& obj ) { *this = obj; }

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& rhs )
{
    static_cast<void>( rhs ); return ( *this );
}

BitcoinExchange::~BitcoinExchange() {}


void BitcoinExchange::saveDatabase( _ifs& dbfile )
{
    std::string line, key, value;

    dbfile.ignore( LONG_MAX, '\n' );
    while ( std::getline( dbfile, line ) )
    {
        std::stringstream ss( line );
        std::getline( ss, key, ',' );
        std::getline( ss, value );
        if ( key.empty() || value.empty() )
            throw std::invalid_argument( "Error: database is corrupted." );
        dataBase.insert( _kv( key, std::atof( value.c_str() ) ) );
    }

    if ( dataBase.empty() )
        throw std::invalid_argument( "Error: emtpy database." );
}