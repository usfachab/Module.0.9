#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cctype>
#include <map>

typedef std::map<std::string, float>::const_iterator iterator;
typedef std::pair<std::string, float> _kv;
typedef std::ifstream _ifs;

class BitcoinExchange
{
private:
    std::map<std::string, float> dataBase;
    BitcoinExchange( const BitcoinExchange& );
    BitcoinExchange &operator=( const BitcoinExchange& );
public:
    BitcoinExchange( char** );
    ~BitcoinExchange();

    void saveDatabase( _ifs& );
    void parseInfile( std::string ) const;
    void strtrim( std::string& ) const;
    void legitLine( std::string& ) const;
    void parseInfileFirstLine( _ifs&  ) const;
    std::string legitDate( const std::string&  ) const;
    float legitValue(  std::string&  ) const;
    bool validate( std::string& ) const;
    bool february( unsigned int, unsigned int ) const;
    bool whitespace( _ifs& ) const;
};


#endif