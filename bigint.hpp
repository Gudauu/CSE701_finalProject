#include <iostream>
#include <cstdint>
#include <vector>

using std::vector;
using std::string;
using std::ostream;
using std::invalid_argument;

/** declaration starts **/

class bigint
{
private:
    vector<uint8_t>digits;
    int8_t sign = 1;
    // Exception to be thrown if.
    inline static invalid_argument invalid_initializing_string = invalid_argument("Initializing string should contain digits only!");
    inline static invalid_argument zero_initializing_string = invalid_argument("Initializing string should not start with zero!");
public:
    bigint();
    bigint(int64_t);
    bigint(const string&);
    bigint& operator+=(const bigint&);
    bigint& operator-=(const bigint&);
    bigint& operator*=(const bigint&);
    bigint& operator=(const bigint&);
    
};

bigint operator-(const bigint&);
bigint operator+(bigint, const bigint&);
bigint operator-(bigint, const bigint&);
bigint operator*(bigint, const bigint&);

bool operator==(const bigint&, const bigint&);
bool operator!=(const bigint&, const bigint&);
bool operator<(const bigint&, const bigint&);
bool operator<=(const bigint&, const bigint&);
bool operator>(const bigint&, const bigint&);
bool operator>=(const bigint&, const bigint&);

ostream& operator<<(ostream&, const bigint&);



/** implementation starts **/

bigint::bigint()
{
    digits = {};
}

bigint::bigint(int64_t number)
{
    sign = (number > 0)? 1 : -1;
    while(number){
        digits.push_back(number%10);
        number /= 10;
    }
}

bigint::bigint(const string& str)
{
    if(str[0] == '0')
        throw zero_initializing_string;
    if(str[0] == '-')
        sign = -1;
    size_t len = str.size();
    for(size_t i = 1; i < len; i++){
        char ch = str[i];
        if(ch < '0' || ch > '9')
            throw invalid_initializing_string;
        else    
            digits.push_back(ch - '0');
    }
}




