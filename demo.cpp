/**
 * @file demo.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include "bigint.hpp"


using std::cout;

int main()
{
    bigint A;
    int64_t v1 = 5; bigint B(v1);
    // string strTest = "100000000000000000000000000000000"; bigint C(strTest);
    int64_t v2 = -12; bigint D(v2);

    // cout << "A: " << A;
    // cout << "B: " << B;
    // cout << "C: " << C;
    // cout << "D: " << D;
    // try{
    //     string v3 = "-0000"; bigint E(v3);
    //     cout << "E: " << E;
    // }catch(invalid_argument e){
    //     cout << e.what() << '\n';
    // }
    // try{
    //     string v4 = "20700&0"; bigint F(v4);
    //     cout << "F: " << F;
    // }catch(invalid_argument e){
    //     cout << e.what() << '\n';
    // }
    A += B;  // 5
    B = (A + D);   // -7
    cout << "A: " << A;
    cout << "B: " << B;
    cout << "A - B: " << A - B;
    cout << "A * B: " << A * B;
    // A += B;
    // cout << "A: " << D;


}