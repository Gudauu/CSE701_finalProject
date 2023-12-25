/**
 * @file demo.cpp
 * @author {Eva Wu} ({gudautd@gmail.com})
 * @brief A demo program showcasing all features of class 'bigint'
 * @version 0.1
 * @date 2023-12-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <cassert>
#include "bigint.hpp"

using std::cout;

void testDefaultConstructor() {
    bigint a;
    assert(a == bigint(0)); // bigint should be initialized to zero
}

void testIntegerConstructor() {
    bigint a(12345);
    bigint b(-12345);
    bigint c(0);
    assert(a == bigint("12345"));
    assert(b == bigint("-12345"));
    assert(c == bigint("0"));
}

void testStringConstructor() {
    bigint a("12345");
    bigint b("-12345");
    bigint c("0");
    assert(a == bigint(12345));
    assert(b == bigint(-12345));
    assert(c == bigint(0));

    // Invalid string (throws exception)
    try {
        bigint invalid("abc");
        assert(false); // Should not reach here
    } catch (const invalid_argument&) {
        assert(true); // Exception caught as expected
    }
}

void testAddition() {
    bigint a("123");
    bigint b("456");
    bigint c("-789");
    bigint d("0");
    assert(a + b == bigint("579"));
    assert(a + c == bigint("-666"));
    assert(a + d == a);
}

void testSubtraction() {
    bigint a("500");
    bigint b("300");
    bigint c("-300");
    assert(a - b == bigint("200"));
    assert(b - a == bigint("-200"));
    assert(a - c == bigint("800"));
}

void testMultiplication() {
    bigint a("123");
    bigint b("-456");
    bigint c("0");
    assert(a * b == bigint("-56088"));
    bigint d = a * c;
    assert(a * c == bigint("0"));
}

void testNegation() {
    bigint a("12345");
    bigint b("-12345");
    assert(-a == bigint("-12345"));
    assert(-b == bigint("12345"));
}

void testAssignment() {
    bigint a("123");
    bigint b = a;
    assert(b == a);

    bigint c;
    c = b;
    assert(c == b);
}


void testEquality() {
    bigint a("12345");
    bigint b("12345");
    bigint c("54321");
    assert(a == b);
    assert(a != c);
}

void testComparison() {
    bigint a("12345");
    bigint b("54321");
    bigint c("-12345");
    bool flag = a < b;
    cout << flag;
    assert(a < b);
    assert(b > a);
    assert(c < a);
    assert(a >= c);
    assert(c <= a);
}

void testLargeNumbers() {
    bigint a("99999999999999999999999999999999");
    bigint b("1");
    assert(a + b == bigint("100000000000000000000000000000000"));
    assert(a - b == bigint("99999999999999999999999999999998"));
}

void testLeadingZeros() {
    try{
        bigint a("00012345");
        bigint b("-00012345");
        assert(a == bigint("12345"));
        assert(b == bigint("-12345"));
    }catch(const invalid_argument& e){
        cout << e.what() << '\n';
    }
    
}

void testInvalidString() {
    try {
        bigint invalid("1a2b3c");
        assert(false); // Should not reach here
    } catch (const invalid_argument& e) {
        assert(true); // Exception caught as expected
    }
}

int main()
{

    testAddition();
    testAssignment();
    testComparison();
    testDefaultConstructor();
    testEquality();
    testIntegerConstructor();
    testInvalidString();
    testLargeNumbers();
    testLeadingZeros();
    testMultiplication();
    testNegation();
    testStringConstructor();
    // /* A, B, C, D: constructors */
    // bigint A;           // default (0) constructor
    // int64_t v1 = 5;
    // bigint B(v1);       // integer constructor
    // string str1 = "100000000000000000000000000000000";
    // bigint C(str1);     // string constructor
    // int64_t v2 = -12;
    // bigint D(v2);       // negative integer constructor

    // cout << "A: " << A;
    // cout << "B: " << B;
    // cout << "C: " << C;
    // cout << "D: " << D;

    // /* E, F : invalid string construction */
    
    // try                  // E: zero start
    // {
    //     string v3 = "-0000";
    //     bigint E(v3);       
    //     cout << "E: " << E;
    // }
    // catch (const invalid_argument& e)
    // {
    //     cout << e.what() << '\n';
    // }
    
    // try                 // F: zero start
    // {
    //     string v4 = "20700&0";
    //     bigint F(v4);
    //     cout << "F: " << F;
    // }
    // catch (const invalid_argument& e)
    // {
    //     cout << e.what() << '\n';
    // }

    // /* demonstrate operators */

    // cout << "-1932138 * -111119: " << bigint("-1932138") * bigint(-111119);
    // cout << "A += B: " << (A += B);
    // cout << "A -= B: " << (A -= B);
    // cout << "A + B: " << (A + B);
    // cout << "A - B: " << (A - B);
    // cout << "A *= B: " << (A *= B);
    // cout << "A * B: " << (A * B);
    // cout << "B = A: " << (B = A);
    // cout << "A == B: " << (A == B) << '\n';
    // cout << "A != B: " << (A != B) << '\n';
    // cout << "A > B: " << (A > B) << '\n';
    // cout << "A < B: " << (A < B) << '\n';
    // cout << "A == -B: " << (A == -B) << '\n';
    // cout << "A <= -B: " << (A <= -B) << '\n';
    // cout << "A >= -B: " << (A >= -B) << "\n\n";
    // try{
    //     A = bigint(12);
    //     B = bigint("-112");
    // }
    // catch (const invalid_argument& e)
    // {
    //     cout << e.what() << '\n';
    // }
    
    // cout << "A += B: " << (A += B);
    // cout << "A -= B: " << (A -= B);
    // cout << "A + B: " << (A + B);
    // cout << "A - B: " << (A - B);
    // cout << "A *= B: " << (A *= B);
    // cout << "A * B: " << (A * B);
    // cout << "A == B: " << (A == B) << '\n';
    // cout << "A != B: " << (A != B) << '\n';
    // cout << "A > B: " << (A > B) << '\n';
    // cout << "A < B: " << (A < B) << '\n';
    // cout << "A == -B: " << (A == -B) << '\n';
    // cout << "A <= -B: " << (A <= -B) << '\n';
    // cout << "A >= -B: " << (A >= -B) << '\n';

}