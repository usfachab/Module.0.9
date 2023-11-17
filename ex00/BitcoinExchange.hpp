#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
// #include <ctime>

typedef std::ifstream ifstm;

class BitcoinExchange
{
private:
    std::map<std::string, std::string> dataBase;
    BitcoinExchange( const BitcoinExchange& );
    BitcoinExchange &operator=( const BitcoinExchange& );
public:
    BitcoinExchange( const char* );
    ~BitcoinExchange();

    void parseInfile( ifstm& ) const;
    void parseDbfile( ifstm& ) const;
    void parseInfileFirstLine( ifstm&  ) const;
    void strtrim( std::string& ) const;
    void validDate( std::string& ) const;
};


#endif