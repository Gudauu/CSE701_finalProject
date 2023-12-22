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
    void removeZeroAtStart();
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

bigint& bigint::operator=(const bigint& rhs){
    sign = rhs.sign;
    digits = rhs.digits;
    return *this;
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
    removeZeroAtStart();
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
    return *this;
}

bigint& bigint::operator-=(const bigint& rhs){
    return *this += (-rhs);
}

bigint& bigint::operator*=(const bigint& rhs){
    if(rhs.sign == -1)
        sign = (sign == 1)?-1:1;
    const vector<uint8_t>& digits_rhs = rhs.digits;
    size_t len_l = digits.size();
    size_t len_r = digits_rhs.size();
    size_t i = 0;
    uint8_t carry = 0;
    bigint digits_sum;
    for(size_t i = 0;i < len_l;i++){
        bigint product;
        product.digits = vector<uint8_t>(i, 0);
        for(size_t j = 0;j < len_r;j++){
            uint8_t product_digit = digits[i]*digits_rhs[j] + carry;
            product.digits.push_back(product_digit%10);
            carry = product_digit/10;
        }
        digits_sum += product;
    }
    digits = digits_sum.digits;
    return *this;
}


void bigint::removeZeroAtStart(){
    size_t len = digits.size();
    size_t i = 0;
    for(;i < len && digits[i] == 0;i++);
    vector<uint8_t>digits_new;
    for(;i < len;i++)
        digits_new.push_back(digits[i]);
    digits = digits_new;
    if(!digits.size())
        digits.push_back(0);
}

