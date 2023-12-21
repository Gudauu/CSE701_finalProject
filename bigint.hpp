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
    bigint& add(const bigint&);
    bigint& minus(const bigint&);
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
    size_t len = str.size();
    if(!len){   // empty string
        bigint();
        return;
    }
    // deal with first char separately due to possible sign and zero start
    size_t i = 0;
    if(str[0] == '0')
        throw zero_initializing_string;
    if(str[0] == '-'){
        sign = -1;
        i++;
    }
    // deal with rest of the string
    for(;i < len; i++){
        char ch = str[i];
        if(ch < '0' || ch > '9')
            throw invalid_initializing_string;
        else    
            digits.push_back(ch - '0');
    }
}

// add: for addition of same sign. No modification to sign.
bigint& bigint::add(const bigint& rhs){
    const vector<uint8_t>& digits_rhs = rhs.digits;
    size_t len_l = digits.size();
    size_t len_r = digits_rhs.size();
    size_t i = 0;
    bool carry = false;
    for(; i < std::min(len_l, len_r);i++){
        uint8_t sum_new = digits[i] + digits_rhs[i] + carry;
        digits[i] = sum_new%10;
        carry = (sum_new >= 10);
    }
    // the left over parts
    for(; i < len_l;i++){
        uint8_t sum_new = digits[i] + carry;
        digits[i] = sum_new%10;
        carry = (sum_new >= 10);
    }
    for(; i < len_r;i++){
        uint8_t sum_new = digits_rhs[i] + carry;
        digits.push_back(sum_new%10);
        carry = (sum_new >= 10);
    }
    if(carry)
        digits.push_back(1);
    return *this;
}

// minus: for minus of two non-negative. Larger - smaller.
bigint& bigint::minus(const bigint& rhs){
    const vector<uint8_t>& digits_rhs = rhs.digits;
    size_t len_l = digits.size();
    size_t len_r = digits_rhs.size();
    size_t i = 0;
    bool carry = false;
    for(; i < std::min(len_l, len_r);i++){
        uint8_t sum_new = digits[i] + 10 - digits_rhs[i] - carry;
        digits[i] = sum_new%10;
        carry = (sum_new < 10);
    }
    // the left over parts
    for(; i < len_l;i++){
        uint8_t sum_new = digits[i] + 10 - carry;
        digits[i] = sum_new%10; 
        carry = (sum_new < 10);
    }
    return *this;
}

bigint& bigint::operator+=(const bigint& rhs){
    if(sign*rhs.sign == 1)
        return add(rhs);
    else if(sign == 1){
        if(*this >= -rhs)
            return minus(-rhs);
        else{
            bigint temp = -rhs;
            temp.minus(*this);
            *this = -temp;
        }   
    }else{
        if(-(*this) >= rhs){
            bigint temp = -(*this);
            temp.minus(rhs);
            *this = -temp;
        }else{
            bigint temp = rhs;
            temp.minus(-(*this));
            *this = temp;
        }
    }
}

bigint& bigint::operator-=(const bigint& rhs){
    return *this += (-rhs);
}




