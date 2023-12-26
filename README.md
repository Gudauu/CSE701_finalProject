# Documentation for BigInt Class

The $bigint$ class is a C++ implementation for handling arbitrary-precision integers. This class allows for the storage and manipulation of integers much larger than those that can be handled by standard C++ integer types, limited only by the available memory of the machine.

## Class Overview

* Storage: Internally, a $bigint$ object stores its integer value as a vector of uint8_t, where each element of the vector represents a single digit in base 10. This allows for easy expansion and manipulation of the integer.
* Sign Handling: The $sign$ of the number (positive or negative) is stored separately as an int8_t, which can be either 1 (positive) or -1 (negative).
* Operations: The class provides various operators to perform arithmetic operations (addition, subtraction, multiplication) and comparisons between $bigint$ objects.

## Public Functions

### Constructors and Assignment Operator

* Default Constructor: Initializes the $bigint$ to zero.
* Integer Constructor: Initializes the $bigint$ from an int64_t value.
* String Constructor: Initializes the $bigint$ from a string representation of the number.
* Copy Constructor: Initializes a new $bigint$ as a copy of an existing $bigint$.
* Assignment Operator: Allows for the assignment of one $bigint$ to another.


### Arithmetic Operators
### Member Functions
* Addition (operator+=): Adds another $bigint$ to the current $bigint$.
* Subtraction (operator-=): Subtracts another $bigint$ from the current $bigint$.
* Multiplication (operator*=): Multiplies the current $bigint$ with another $bigint$.
* Addition (operator+): Creates a new $bigint$ by adding two $bigint$ values. This operator uses the operator+= internally to perform the addition.

#### Non-member Functions
* Subtraction (operator-): Creates a new $bigint$ by subtracting one $bigint$ from another. It leverages the operator-= internally to carry out the subtraction.
* Multiplication (operator*): Generates a new $bigint$ as the product of two $bigint$ values. This operation is facilitated by the operator*= to perform the multiplication.


### Unary Operations

* Negate (negate): Changes the $sign$ of the $bigint$.

### Comparison Operators

* Equal (operator==): Checks if two $$bigint$s$ are equal.
* Not Equal (operator!=): Checks if two $$bigint$s$ are not equal.
* Less Than (operator<): Checks if one $bigint$ is less than another.
* Less Than or Equal (operator<=): Checks if one $bigint$ is less than or equal to another.
* Greater Than (operator>): Checks if one $bigint$ is greater than another.
* Greater Than or Equal (operator>=): Checks if one $bigint$ is greater than or equal to another.

### Input/Output Stream

* Output Stream (operator<<): Overloads the $ostream$ operator to allow for easy printing of $bigint$ values.

## Private Member Functions

* Set $Digits$ (setDigits): Sets the $digits$ of the $bigint$.
* Set $Sign$ (setSign): Sets the $sign$ of the $bigint$.
* Add ($add$): Adds two $$bigint$s$ of the same sign.
* Minus ($minus$): Subtracts one non-negative $bigint$ from another.
* Remove Leading Zeros ($removeZeroAtStart$): Removes any leading zeros from the $bigint$ representation.

## Implementation

### Addition Algorithm (add Method)

The $add()$ private method performs the addition of two $bigint$ numbers with the same sign.  

Algorithm:

* Initialize Carry: A carry variable is set to zero.
* Equal Length Iteration: For each digit index i up to the minimum length of both numbers, the following steps are performed:
    * Digit Addition: Add the $digits$ from both numbers at index i along with the carry.
    * Handle Carry and Store Result: Calculate the new carry (1 if the sum is 10 or more) and update the digit of the current $bigint$ at index i to be the last digit of the sum.
* Process Remaining Digits: Continue the process for the remaining $digits$ of the longer number, if any, taking into account only the carry.
* Handle Final Carry: If there's a remaining carry after processing all $digits$, append a new digit 1 to the current $bigint$.
### Subtraction Algorithm (minus Method)

The $minus()$ private method subtracts $rhs$ $bigint$ from the current $bigint$. It assumes that the current $bigint$ is larger or equal to $rhs$.

Algorithm:
* Initialize Borrow: A borrow variable is set to zero.
* Equal Length Iteration: For each digit index i up to the minimum length of both numbers, perform the following:
    * Digit Subtraction: Subtract the digit of $rhs$ and borrow from the current $bigint$'s digit at index i.
    * Handle Borrow and Store Result: If the result is negative, set borrow to 1 and add 10 to the result before storing it in the current $bigint$'s digit at index i.
* Process Remaining Digits: Continue the process for the remaining $digits$ of the current $bigint$, if any, taking into account only the borrow.
* Remove Leading Zeros: After subtraction, if any leading zeros are produced, remove them.

### Addition Assignment Operator (operator+=)

The operator+= performs addition, considering the signs of the two $bigint$ numbers involved.

Algorithm:

* Same Sign Addition: If both $$bigint$s$ have the same $sign$, use the add method directly as no sign modification is required.
* Different Sign Handling:
    * If the current $bigint$ is larger (in absolute value) than $rhs$, subtract $rhs$ from it.
    * If $rhs$ is larger, subtract the current $bigint$ from $rhs$ and adjust the $sign$ of the result accordingly.
* Zero Handling: If the result of the operation is zero, set the $sign$ of the current $bigint$ to positive.

### Subtraction Assignment Operator (operator-=)

The operator-= performs subtraction by leveraging the operator+=.

Algorithm:

* Negate and Add: Negate the $rhs$ $bigint$ and then add it to the current $bigint$ using operator+=. This effectively performs subtraction.

### Multiplication Algorithm (operator*=)

The multiplication operation follows the traditional multiplication algorithm used in arithmetic but adapted for base 10 represented by vectors.

* Negate if Necessary: If the $rhs$ $bigint$ is negative, negate the current $bigint$.
* Initialization: Create a $bigint$ to hold the sum of partial products.
* Iterate Over Each Digit: For each digit in the current $bigint$, create a temporary $bigint$ product to hold the partial product.
    * Shift: Initialize product with zeros for lower positions, equivalent to shifting in base 10.
    * Digit-wise Multiplication: Multiply each digit of $rhs$ $bigint$ with the current digit of the $bigint$, add the carry from the previous multiplication, and store the last digit of the result in product.
    * Carry Handling: Update the carry after each multiplication.

* Summation of Products: Add each partial product to the digits_sum.
* Result Assignment: Replace the current $bigint$'s $digits$ with the $digits$ of digits_sum and remove any leading zeros.
### Equality Operator (operator==)

The operator== checks whether two $bigint$ instances are equal.

Algorithm:

* Compare Signs: If the signs of the two $$bigint$s$ are different, they are not equal. Zero is treated as a special case where its $sign$ is always positive.
* Compare Lengths: If the sizes of their digit vectors are different, they are not equal.
* Compare Digits: Iterate through each digit; if any pair of corresponding $digits$ differs, the $$bigint$s$ are not equal.
* Result: Return true if all $digits$ are the same; otherwise, return false.

### Less Than Operator (operator<)

The operator< determines if one $bigint$ is less than another.

Algorithm:

* Sign Comparison: A negative number is always less than a positive one.
* Equal Sign Comparison: For $$bigint$s$ with the same $sign$:
    * Equal Lengths: If the number of $digits$ is the same, compare $digits$ starting from the most significant. The first pair of differing $digits$ determines the result.
    * Different Lengths: For positive numbers, the one with fewer $digits$ is smaller; for negative numbers, the one with fewer $digits$ is larger.
* Result: Return true if the left-hand side ($lhs$) is found to be smaller; otherwise, false.

### Less Than or Equal Operator (operator<=)

The operator<= checks if one $bigint$ is less than or equal to another.

Algorithm:

* Sign Comparison: Similar to operator<, negative is always less than positive.
* Equal Sign Comparison: For $$bigint$s$ with the same $sign$:
    * Equal Lengths: Compare $digits$ starting from the most significant. If all corresponding $digits$ are the same, or the $lhs$ is found to be smaller, the result is true.
    * Different Lengths: Similar to operator<, consider the number of $digits$. A positive number with fewer $digits$ or a negative number with more $digits$ is smaller.
* Result: Return true if $lhs$ is less than or equal to $rhs$; otherwise, false.


## Exceptions
* The class throws an invalid_argument exception if an attempt is made to initialize a $bigint$ with an invalid string (e.g., non-digit characters).
* Leading zeros in the string constructor are not allowed and will also result in an invalid_argument exception.
