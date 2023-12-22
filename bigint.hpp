#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

using std::invalid_argument;
using std::ostream;
using std::string;
using std::vector;

/** @brief Class representing an arbitrary-precision integer. */
class bigint
{
private:
    /** @brief Vector of digits representing the bigint in base 10. */
    vector<uint8_t> digits;

    /** @brief Sign of the bigint, 1 for positive, -1 for negative. */
    int8_t sign = 1;

    /** @brief Sets the digits of the bigint.
     *  @param opr Vector of uint8_t representing the digits.
     */
    void setDigits(const vector<uint8_t> &opr);

    /** @brief Sets the sign of the bigint.
     *  @param new_sign The new sign value.
     */
    void setSign(const int8_t &new_sign);

    /** @brief Adds another bigint to the current bigint, assuming both have the same sign.
     *  @param rhs The bigint to be added.
     *  @return Reference to the current bigint after addition.
     */
    bigint &add(const bigint &rhs);

    /** @brief Subtracts another bigint from the current bigint, assuming both are non-negative and the current bigint is larger.
     *  @param rhs The bigint to be subtracted.
     *  @return Reference to the current bigint after subtraction.
     */
    bigint &minus(const bigint &rhs);

    /** @brief Removes leading zeros from the bigint representation. */
    void removeZeroAtStart();

    /** @brief Exception for invalid string initialization. */
    inline static invalid_argument invalid_initializing_string = invalid_argument("Initializing string should contain digits only!");

    /** @brief Exception for string initialization starting with zero. */
    inline static invalid_argument zero_initializing_string = invalid_argument("Initializing string should not start with zero!");

public:
    /** @brief Constructs a new bigint initialized to zero. */
    bigint();

    /** @brief Constructs a bigint from an int64_t.
     *  @param number The int64_t value to initialize from.
     */
    bigint(int64_t number);

    /** @brief Constructs a bigint from a string.
     *  @param str The string to initialize from.
     */
    bigint(const string &str);

    /** @brief Assigns a bigint to the current bigint.
     *  @param rhs The bigint to assign from.
     *  @return Reference to the current bigint after assignment.
     */
    bigint &operator=(const bigint &rhs);

    /** @brief Adds a bigint to the current bigint.
     *  @param rhs The bigint to add.
     *  @return Reference to the current bigint after addition.
     */
    bigint &operator+=(const bigint &rhs);

    /** @brief Subtracts a bigint from the current bigint.
     *  @param rhs The bigint to subtract.
     *  @return Reference to the current bigint after subtraction.
     */
    bigint &operator-=(const bigint &rhs);

    /** @brief Multiplies a bigint with the current bigint.
     *  @param rhs The bigint to multiply with.
     *  @return Reference to the current bigint after multiplication.
     */
    bigint &operator*=(const bigint &rhs);

    /** @brief Negates the current bigint. */
    void negate();

    /** @brief Gets the sign of the bigint.
     *  @return The sign of the bigint.
     */
    int8_t getSign() const;

    /** @brief Gets the digits of the bigint.
     *  @return Vector of digits of the bigint.
     */
    vector<uint8_t> getDigits() const;
};

// Operator overloads and other functions would also have similar Doxygen comments.

// Implementation details would have inline comments explaining complex logic or important steps.


/**
 * @brief Negates a bigint.
 * @param opr The bigint to negate.
 * @return The negated bigint.
 */
bigint operator-(const bigint &opr);

/**
 * @brief Adds two bigint numbers.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint.
 * @return The sum of lhs and rhs.
 */
bigint operator+(bigint lhs, const bigint &rhs);

/**
 * @brief Subtracts one bigint from another.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint to subtract from lhs.
 * @return The difference of lhs and rhs.
 */
bigint operator-(bigint lhs, const bigint &rhs);

/**
 * @brief Multiplies two bigint numbers.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint.
 * @return The product of lhs and rhs.
 */
bigint operator*(bigint lhs, const bigint &rhs);

/**
 * @brief Compares two bigint numbers for equality.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint.
 * @return True if lhs is equal to rhs, false otherwise.
 */
bool operator==(const bigint &lhs, const bigint &rhs);

/**
 * @brief Compares two bigint numbers for inequality.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint.
 * @return True if lhs is not equal to rhs, false otherwise.
 */
bool operator!=(const bigint &lhs, const bigint &rhs);

/**
 * @brief Checks if one bigint is less than another.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint.
 * @return True if lhs is less than rhs, false otherwise.
 */
bool operator<(const bigint &lhs, const bigint &rhs);

/**
 * @brief Checks if one bigint is less than or equal to another.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint.
 * @return True if lhs is less than or equal to rhs, false otherwise.
 */
bool operator<=(const bigint &lhs, const bigint &rhs);

/**
 * @brief Checks if one bigint is greater than another.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint.
 * @return True if lhs is greater than rhs, false otherwise.
 */
bool operator>(const bigint &lhs, const bigint &rhs);

/**
 * @brief Checks if one bigint is greater than or equal to another.
 * @param lhs The left-hand side bigint.
 * @param rhs The right-hand side bigint.
 * @return True if lhs is greater than or equal to rhs, false otherwise.
 */
bool operator>=(const bigint &lhs, const bigint &rhs);

/**
 * @brief Overload the ostream operator for bigint.
 * @param out The output stream.
 * @param opr The bigint to be streamed.
 * @return The updated output stream containing the bigint representation.
 */
ostream &operator<<(ostream &out, const bigint &opr);


/** implementation starts **/

/**
 * @brief Construct a new bigint::bigint object
 * 
 */
bigint::bigint()
{
    setDigits({0});
}

/**
 * @brief Construct a new bigint::bigint object
 * 
 * @param number The int64_t value to be converted 
 */
bigint::bigint(int64_t number)
{
    int64_t new_sign = (number > 0) ? 1 : -1;
    setSign(new_sign);
    while (number)
    {
        digits.push_back(new_sign * (number % 10));
        number /= 10;
    }
}

/**
 * @brief Construct a new bigint::bigint object
 * 
 * @param str The string value to be converted 
 */
bigint::bigint(const string &str)
{
    size_t len = str.size();
    if (!len)
    { // empty string
        bigint();
        return;
    }
    // deal with first char separately due to possible sign and zero start
    size_t i = 0;
    if (str[0] == '-')
    {
        setSign(-1);
        i++;
    }
    if (str[i] == '0')
        throw zero_initializing_string;
    vector<uint8_t> digits_new;
    // deal with rest of the string
    for (; i < len; i++)
    {
        char ch = str[i];
        if (ch < '0' || ch > '9')
            throw invalid_initializing_string;
        else
            digits_new.push_back(ch - '0');
    }
    std::reverse(digits_new.begin(), digits_new.end());
    setDigits(digits_new);
}

/**
 * @brief 
 * 
 * @param rhs 
 * @return bigint& 
 */
bigint &bigint::operator=(const bigint &rhs)
{
    sign = rhs.sign;
    digits = rhs.digits;
    return *this;
}
// add: for addition of same sign. No modification to sign.
bigint &bigint::add(const bigint &rhs)
{
    const vector<uint8_t> &digits_rhs = rhs.digits;
    size_t len_l = digits.size();
    size_t len_r = digits_rhs.size();
    size_t i = 0;
    bool carry = false;
    for (; i < std::min(len_l, len_r); i++)
    {
        uint8_t sum_new = digits[i] + digits_rhs[i] + carry;
        digits[i] = sum_new % 10;
        carry = (sum_new >= 10);
    }
    // the left over parts
    for (; i < len_l; i++)
    {
        uint8_t sum_new = digits[i] + carry;
        digits[i] = sum_new % 10;
        carry = (sum_new >= 10);
    }
    for (; i < len_r; i++)
    {
        uint8_t sum_new = digits_rhs[i] + carry;
        digits.push_back(sum_new % 10);
        carry = (sum_new >= 10);
    }
    if (carry)
        digits.push_back(1);
    return *this;
}

// minus: for minus of two non-negative. Larger - smaller.
bigint &bigint::minus(const bigint &rhs)
{
    const vector<uint8_t> &digits_rhs = rhs.digits;
    size_t len_l = digits.size();
    size_t len_r = digits_rhs.size();
    size_t i = 0;
    bool carry = false;
    for (; i < std::min(len_l, len_r); i++)
    {
        uint8_t sum_new = digits[i] + 10 - digits_rhs[i] - carry;
        digits[i] = sum_new % 10;
        carry = (sum_new < 10);
    }
    // the left over parts
    for (; i < len_l; i++)
    {
        uint8_t sum_new = digits[i] + 10 - carry;
        digits[i] = sum_new % 10;
        carry = (sum_new < 10);
    }
    removeZeroAtStart();
    return *this;
}

bigint &bigint::operator+=(const bigint &rhs)
{
    if (sign * rhs.sign == 1)
        return add(rhs);
    else if (sign == 1)
    {
        if (*this >= -rhs)
            return minus(-rhs);
        else
        {
            bigint temp = -rhs;
            temp.minus(*this);
            *this = -temp;
        }
    }
    else
    {
        if (-(*this) >= rhs)
        {
            bigint temp = -(*this);
            temp.minus(rhs);
            *this = -temp;
        }
        else
        {
            bigint temp = rhs;
            temp.minus(-(*this));
            *this = temp;
        }
    }
    // if zero, set sign to 1
    if (digits[0] == 0)
        setSign(1);
    return *this;
}

bigint &bigint::operator-=(const bigint &rhs)
{
    return *this += (-rhs);
}

bigint &bigint::operator*=(const bigint &rhs)
{
    if (rhs.sign == -1)
        negate();
    const vector<uint8_t> &digits_rhs = rhs.digits;
    size_t len_l = digits.size();
    size_t len_r = digits_rhs.size();
    size_t i = 0;
    uint8_t carry;
    bigint digits_sum;
    for (size_t i = 0; i < len_l; i++)
    {
        bigint product;
        product.setDigits(vector<uint8_t>(i, 0));
        carry = 0;
        for (size_t j = 0; j < len_r; j++)
        {
            uint8_t product_digit = digits[i] * digits_rhs[j] + carry;
            product.digits.push_back(product_digit % 10);
            carry = product_digit / 10;
        }
        if (carry)
            product.digits.push_back(carry);
        digits_sum += product;
    }
    digits = digits_sum.digits;
    return *this;
}

void bigint::removeZeroAtStart()
{
    while (digits.back() == 0)
        digits.pop_back();
    if (!digits.size())
        digits.push_back(0);
}

int8_t bigint::getSign() const
{
    return sign;
}
vector<uint8_t> bigint::getDigits() const
{
    return digits;
}

void bigint::setDigits(const vector<uint8_t> &opr)
{
    digits = opr;
}
void bigint::setSign(const int8_t &new_sign)
{
    sign = new_sign;
}
void bigint::negate()
{
    sign *= -1;
}

bigint operator-(const bigint &opr)
{
    bigint result = opr;
    result.negate();
    return result;
}
bigint operator+(bigint lhs, const bigint &rhs)
{
    return (lhs += rhs);
}
bigint operator-(bigint lhs, const bigint &rhs)
{
    return (lhs -= rhs);
}
bigint operator*(bigint lhs, const bigint &rhs)
{
    return (lhs *= rhs);
}

bool operator==(const bigint &lhs, const bigint &rhs)
{
    if (lhs.getSign() != rhs.getSign())
        return false;
    vector<uint8_t> digits_lhs = lhs.getDigits();
    vector<uint8_t> digits_rhs = rhs.getDigits();
    size_t len_l = digits_lhs.size();
    if (len_l != digits_rhs.size())
        return false;
    size_t i;
    for (i = 0; i < len_l && digits_lhs[i] == digits_rhs[i]; i++)
        ;
    return i == len_l;
}

bool operator!=(const bigint &lhs, const bigint &rhs)
{
    return !(lhs == rhs);
}
bool operator<(const bigint &lhs, const bigint &rhs)
{
    if (lhs.getSign() < rhs.getSign())
        return true;
    if (lhs.getSign() > rhs.getSign())
        return false;
    vector<uint8_t> digits_lhs = lhs.getDigits();
    vector<uint8_t> digits_rhs = rhs.getDigits();
    size_t len_l = digits_lhs.size();
    size_t len_r = digits_rhs.size();
    bool isPos = (lhs.getSign() == 1);

    if (len_l == len_r)
    {
        size_t i;
        for (i = 0; i < len_l && digits_lhs[i] == digits_rhs[i]; i++);
        if (i == len_l)
            return false;
        return (isPos && digits_lhs[i] < digits_rhs[i]) || (!isPos && digits_lhs[i] > digits_rhs[i]);
    }
    bool isShorter = len_l < len_r;
    return (isShorter && isPos) || !(isShorter || isPos);
}
bool operator<=(const bigint &lhs, const bigint &rhs)
{
    if (lhs.getSign() < rhs.getSign())
        return true;
    if (lhs.getSign() > rhs.getSign())
        return false;
    vector<uint8_t> digits_lhs = lhs.getDigits();
    vector<uint8_t> digits_rhs = rhs.getDigits();
    size_t len_l = digits_lhs.size();
    size_t len_r = digits_rhs.size();
    bool isPos = (lhs.getSign() == 1);

    if (len_l == len_r)
    {
        size_t i;
        for (i = 0; i < len_l && digits_lhs[i] == digits_rhs[i]; i++);
        if (i == len_l)
            return true;
        return (isPos && digits_lhs[i] < digits_rhs[i]) || (!isPos && digits_lhs[i] > digits_rhs[i]);
    }
    bool isShorter = len_l < len_r;
    return (isShorter && isPos) || !(isShorter || isPos);
}
bool operator>(const bigint &lhs, const bigint &rhs)
{
    return !(lhs <= rhs);
}
bool operator>=(const bigint &lhs, const bigint &rhs)
{
    return !(lhs < rhs);
}

ostream &operator<<(ostream &out, const bigint &opr)
{
    vector<uint8_t> digits = opr.getDigits();
    if (opr.getSign() == -1)
        out << '-';
    size_t len = digits.size();
    // for (size_t i = 0; i < len; i++)
    for (int64_t i = (len - 1); i >= 0; i--)
        out << static_cast<int64_t>(digits[i]);
    out << '\n';
    return out;
}
