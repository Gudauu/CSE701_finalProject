/**
 * @file bigint.hpp
 * @author {Eva Wu} ({gudautd@gmail.com})
 * @brief Header file and implementation of arbitrary precision integer class 'bigint'
 * @version 0.1
 * @date 2023-12-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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

    /** @brief Gets the digits of the bigint in vector<uint8_t> form.
     *  @return Vector of digits of the bigint.
     */
    vector<uint8_t> getDigits() const;
};

// Implementation details have inline comments explaining complex logic or important steps.

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


bigint::bigint()
{
    setDigits({0});
}


bigint::bigint(int64_t number)
{
    int64_t new_sign = (number >= 0) ? 1 : -1;
    setSign(new_sign);
    if(!number) // if number is zero
        setDigits({0});
    while (number)
    {
        digits.push_back(new_sign * (number % 10));
        number /= 10;
    }
    
}

bigint::bigint(const string &str)
{
    size_t len = str.size();
    if (!len || (len == 1 && str[0] == '0'))
    { // empty string or zero string
        setDigits({0});
        return;
    }
    // deal with first char separately due to possible sign and zero start
    // i: records the index in string we are on 
    size_t i = 0;
    // negative sign, move forward one 
    if (str[0] == '-')
    {
        setSign(-1);
        i++;
    }
    // if the first digit is 0, throw invalid
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


bigint &bigint::operator=(const bigint &rhs)
{
    sign = rhs.sign; // Copy the sign from the right-hand side (rhs)
    digits = rhs.digits; // Copy the digits from rhs
    return *this; // Return the current object for chaining assignments
}

bigint &bigint::add(const bigint &rhs)
{
    const vector<uint8_t> &digits_rhs = rhs.digits; // Digits of the right-hand side bigint
    size_t len_l = digits.size(); // Length of current bigint's digits
    size_t len_r = digits_rhs.size(); // Length of rhs bigint's digits
    size_t i = 0;   
    bool carry = false; // To store carry-over during addition

    // Add corresponding digits of both numbers and handle carry
    for (; i < std::min(len_l, len_r); i++)
    {
        uint8_t sum_new = digits[i] + digits_rhs[i] + carry;
        digits[i] = sum_new % 10; // Store the last digit of sum
        carry = (sum_new >= 10); // Determine if there's a carry for next digits
    }

    // Handle remaining digits and carry for the larger number
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

    // Add a new digit if there's a carry left after processing all digits
    if (carry)
        digits.push_back(1);
    return *this;
}

bigint &bigint::minus(const bigint &rhs)
{
    const vector<uint8_t> &digits_rhs = rhs.digits;
    size_t len_l = digits.size();
    size_t len_r = digits_rhs.size();
    size_t i = 0;
    bool borrow = false; // To store borrow during subtraction

    // Subtract corresponding digits of both numbers and handle borrow
    for (; i < std::min(len_l, len_r); i++)
    {
        uint8_t sum_new = digits[i] + 10 - digits_rhs[i] - borrow;
        digits[i] = sum_new % 10; // Store the last digit of sum
        borrow = (sum_new < 10); // Determine if there's a borrow for next digits
    }

    // Handle remaining digits and borrow for the larger number
    for (; i < len_l; i++)
    {
        uint8_t sum_new = digits[i] + 10 - borrow;
        digits[i] = sum_new % 10;
        borrow = (sum_new < 10);
    }

    // Remove leading zeros after subtraction
    removeZeroAtStart();
    return *this;
}


bigint &bigint::operator+=(const bigint &rhs)
{
    // If both bigint have the same sign, directly add() them.
    if (sign * rhs.sign == 1)
        return add(rhs);

    // current bigint is positive and rhs is negative
    else if (sign == 1)
    {
        // If current bigint is larger than rhs, subtract abs(rhs) from it.
        if (*this >= -rhs)
            return minus(-rhs);
        else
        {
            // If rhs is larger, subtract current bigint from rhs and negate the result.
            bigint temp = -rhs;
            temp.minus(*this);
            *this = -temp;
        }
    }
    else // If the current bigint is negative and rhs is positive
    {
        // If the abs(current bigint) is larger than rhs, subtract rhs from it and negate the result.
        if (-(*this) >= rhs)
        {
            bigint temp = -(*this);
            temp.minus(rhs);
            *this = -temp;
        }
        else
        {
            // If rhs is larger, subtract the absolute value of current bigint from rhs.
            bigint temp = rhs;
            temp.minus(-(*this));
            *this = temp;
        }
    }
    // If the result is zero, set the sign to positive.
    if (digits[0] == 0)
        setSign(1);
    return *this;
}


bigint &bigint::operator-=(const bigint &rhs)
{
    // Utilize the += operator for subtraction by negating rhs.
    return *this += (-rhs);
}



bigint &bigint::operator*=(const bigint &rhs)
{
    // Negate the current bigint if rhs is negative.
    if (rhs.sign == -1)
        negate();

    const vector<uint8_t> &digits_rhs = rhs.digits; // Digits of the right-hand side bigint.
    size_t len_l = digits.size(); // Length of current bigint's digits.
    size_t len_r = digits_rhs.size(); // Length of rhs bigint's digits.
    uint8_t carry;      // To store carry-over during multiplication
    bigint digits_sum;  // To store the sum of the products.

    // Iterate over each digit of the current bigint.
    for (size_t i = 0; i < len_l; i++)
    {
        bigint product; // To store the product of a single digit multiplication.
        product.setDigits(vector<uint8_t>(i, 0)); // Add zeros for lower positions, equivalent to shifting in base 10.

        carry = 0; 
        // Multiply the current digit with each digit of rhs bigint.
        for (size_t j = 0; j < len_r; j++)
        {
            uint8_t product_digit = digits[i] * digits_rhs[j] + carry;
            product.digits.push_back(product_digit % 10); // Store the last digit of the product.
            carry = product_digit / 10; // Carry for the next digit.
        }

        // Add remaining carry if present.
        if (carry)
            product.digits.push_back(carry);

        // Add the product to the total sum.
        digits_sum += product;
    }

    // Replace the current bigint's digits with the sum's digits.
    digits = digits_sum.digits;
    return *this;
}






void bigint::removeZeroAtStart()
{
    // Removing zeros from the end of the vector until a non-zero digit is encountered
    // or the vector becomes empty.
    while (digits.back() == 0 && digits.size() > 1)
        digits.pop_back();

    // If all digits are zeros, ensure the bigint is set to zero (not an empty vector).
    if (digits.empty())
        digits.push_back(0);
}


int8_t bigint::getSign() const
{
    return sign; // Returns the sign of the bigint
}


vector<uint8_t> bigint::getDigits() const
{
    return digits; // Returns a copy of the bigint's digits
}


void bigint::setDigits(const vector<uint8_t> &opr)
{
    digits = opr; // Sets the bigint's digits to the provided vector
}


void bigint::setSign(const int8_t &new_sign)
{
    sign = new_sign; // Sets the bigint's sign to the provided value
}


void bigint::negate()
{
    if(digits[0] != 0)
        sign *= -1; // Flips the sign of the bigint unless it's 0 (invariable)
}


bigint operator-(const bigint &opr)
{
    bigint result = opr; // Make a copy of the bigint
    result.negate(); // Negate the copied bigint
    return result; // Return the negated bigint
}


bigint operator+(bigint lhs, const bigint &rhs)
{
    return lhs += rhs; // Use the compound addition-assignment operator
}


bigint operator-(bigint lhs, const bigint &rhs)
{
    return lhs -= rhs; // Use the compound subtraction-assignment operator
}


bigint operator*(bigint lhs, const bigint &rhs)
{
    return lhs *= rhs; // Use the compound multiplication-assignment operator
}


bool operator==(const bigint &lhs, const bigint &rhs)
{
    // First, compare the signs. If they are different, bigint are not equal.
    // 0 always has sign value 1 (invariant)
    if (lhs.getSign() != rhs.getSign())
        return false;

    // Then, compare the sizes of digit vectors.
    vector<uint8_t> digits_lhs = lhs.getDigits();
    vector<uint8_t> digits_rhs = rhs.getDigits();
    if (digits_lhs.size() != digits_rhs.size())
        return false;

    // Finally, compare the digits.
    for (size_t i = 0; i < digits_lhs.size(); i++)
    {
        if (digits_lhs[i] != digits_rhs[i])
            return false;
    }

    // If all checks pass, the bigint are equal.
    return true;
}


bool operator!=(const bigint &lhs, const bigint &rhs)
{
    return !(lhs == rhs); // Utilize the overloaded equality operator
}


bool operator<(const bigint &lhs, const bigint &rhs)
{
    // Negative numbers are smaller than positive numbers.
    if (lhs.getSign() < rhs.getSign())
        return true;
    if (lhs.getSign() > rhs.getSign())
        return false;

    vector<uint8_t> digits_lhs = lhs.getDigits();
    vector<uint8_t> digits_rhs = rhs.getDigits();
    size_t len_l = digits_lhs.size();
    size_t len_r = digits_rhs.size();
    // isPos: now we are assured they have the same sign, record whether they are positive ot negative
    bool isPos = (lhs.getSign() == 1);

    // For numbers with the same sign and number of digits, compare digit by digit.
    if (len_l == len_r)
    {
        size_t i;
        // find the first different digit
        for (i = 0; i < len_l && digits_lhs[i] == digits_rhs[i]; i++);
        if (i == len_l) // All digits are the same, hence not less than.
            return false;
        // For positive numbers, a smaller digit means smaller number and vice versa for negative numbers.
        return (isPos && digits_lhs[i] < digits_rhs[i]) || (!isPos && digits_lhs[i] > digits_rhs[i]);
    }
    // If the number of digits is different, the number with fewer digits is smaller for positive numbers and larger for negative numbers.
    bool isShorter = len_l < len_r;
    return (isShorter && isPos) || !(isShorter || isPos);
}


bool operator<=(const bigint &lhs, const bigint &rhs)
{
    // Negative numbers are smaller than positive numbers.
    if (lhs.getSign() < rhs.getSign())
        return true;
    if (lhs.getSign() > rhs.getSign())
        return false;

    vector<uint8_t> digits_lhs = lhs.getDigits();
    vector<uint8_t> digits_rhs = rhs.getDigits();
    size_t len_l = digits_lhs.size();
    size_t len_r = digits_rhs.size();
    // isPos: now we are assured they have the same sign, record whether they are positive ot negative
    bool isPos = (lhs.getSign() == 1);

    // For numbers with the same sign and number of digits, compare digit by digit.
    if (len_l == len_r)
    {
        size_t i;
        // find the first different digit
        for (i = 0; i < len_l && digits_lhs[i] == digits_rhs[i]; i++);
        if (i == len_l) // All digits are the same, also meets condition.
            return true;
        // For positive numbers, a smaller digit means smaller number and vice versa for negative numbers.
        return (isPos && digits_lhs[i] < digits_rhs[i]) || (!isPos && digits_lhs[i] > digits_rhs[i]);
    }
    // If the number of digits is different, the number with fewer digits is smaller for positive numbers and larger for negative numbers.
    bool isShorter = len_l < len_r;
    return (isShorter && isPos) || !(isShorter || isPos);
}


bool operator>(const bigint &lhs, const bigint &rhs)
{
    return !(lhs <= rhs); // Utilizing the operator<= for comparison.
}


bool operator>=(const bigint &lhs, const bigint &rhs)
{
    return !(lhs < rhs); // Utilizing the operator< for comparison.
}


ostream &operator<<(ostream &out, const bigint &opr)
{
    vector<uint8_t> digits = opr.getDigits();
    // Outputting the sign if negative
    if (opr.getSign() == -1)
        out << '-';
    size_t len = digits.size();

    // Outputting each digit starting from the most significant one
    for (int64_t i = (len - 1); i >= 0; i--)
        out << static_cast<int64_t>(digits[i]);

    out << '\n'; // Newline after printing the bigint
    return out;
}
