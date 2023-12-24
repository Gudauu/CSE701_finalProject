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
#include "bigint.hpp"

using std::cout;

int main()
{
    /* A, B, C, D: constructors */
    bigint A;           // default (0) constructor
    int64_t v1 = 5;
    bigint B(v1);       // integer constructor
    string str1 = "100000000000000000000000000000000";
    bigint C(str1);     // string constructor
    int64_t v2 = -12;
    bigint D(v2);       // negative integer constructor

    cout << "A: " << A;
    cout << "B: " << B;
    cout << "C: " << C;
    cout << "D: " << D;

    /* E, F : invalid string construction */
    
    try                  // E: zero start
    {
        string v3 = "-0000";
        bigint E(v3);       
        cout << "E: " << E;
    }
    catch (invalid_argument e)
    {
        cout << e.what() << '\n';
    }
    
    try                 // F: zero start
    {
        string v4 = "20700&0";
        bigint F(v4);
        cout << "F: " << F;
    }
    catch (invalid_argument e)
    {
        cout << e.what() << '\n';
    }

    /* demonstrate operators */

    cout << "-1932138 * -111119: " << bigint("-1932138") * bigint(-111119);
    cout << "A += B: " << (A += B);
    cout << "A -= B: " << (A -= B);
    cout << "A + B: " << (A + B);
    cout << "A - B: " << (A - B);
    cout << "A *= B: " << (A *= B);
    cout << "A * B: " << (A * B);
    cout << "B = A: " << (B = A) << '\n';
    cout << "A == B: " << (A == B) << '\n';
    cout << "A != B: " << (A != B) << '\n';
    cout << "A > B: " << (A > B) << '\n';
    cout << "A < B: " << (A < B) << '\n';
    cout << "A == -B: " << (A == -B) << '\n';
    cout << "A <= -B: " << (A <= -B) << '\n';
    cout << "A >= -B: " << (A >= -B) << '\n';

}