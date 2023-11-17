#include "BitcoinExchange.hpp"


int main( int argc, char* argv[] )
{
    try
    {
        BitcoinExchange change( argv[ 1 ] );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    static_cast<void>( argc );
    return 0;
}



// int main()
// {
//     std::map< std::string, std::string > mymap;

//     mymap["2024-10-01"] = "50";
//     mymap["2024-05-20"] = "48";
//     mymap["2024-03-12"] = "60";
//     mymap["2024-07-05"] = "80";
//     mymap["2024-01-15"] = "100";

//     std::map<std::string, std::string>::iterator itlow;
//     itlow = mymap.lower_bound ( "2023-35-52" );
//     if( itlow != mymap.end() )
//         std::cout << itlow->first << " " << itlow->second << std::endl;
// }

// int main() {
//     struct tm tm;
//     // std::string s("2013-02-29");
//     if ( strptime("2013-02-30", "%Y-%m-%d", &tm) )
//         std::cout << "date is valid" << std::endl;
//     else
//         std::cout << "date is invalid" << std::endl;
// }