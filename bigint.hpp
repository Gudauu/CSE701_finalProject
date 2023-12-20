#include <iostream>
#include <cstdint>
#include <vector>

using std::vector;
using std::string;
using std::ostream;


class bigint
{
private:
    vector<uint8_t>digits;
    int8_t sign = 1;
public:
    bigint();
    bigint(const int64_t&);
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






