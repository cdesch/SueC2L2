//
//  main.cpp
//  SueC2L2
//
//  Created by cj on 2/10/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <math.h>
#include "SmcArray.hpp"
#include "BigInt.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    BigInt* myBigInt = new BigInt();
    
    myBigInt->assign(1234);
    myBigInt->print();
    myBigInt->assign("5678");
    myBigInt->print();
    

   BigInt secondBigInt;
   secondBigInt.assign(2222);
    secondBigInt.print();
    if(myBigInt->compare(secondBigInt) > 0){
        cout << "A is greater than B" << endl;
    }else if (myBigInt->compare(secondBigInt) < 0){
        cout << "B is grater than A" <<  endl;
    }else{
        cout << "A is Equal to B" << endl;
    }
   
   secondBigInt.print();
    
   myBigInt->add(secondBigInt);
   myBigInt->print();
    
    
   myBigInt->subtract(secondBigInt);
   myBigInt->print(); 
    
    return 0;
}


/*
 The Unlimitedly Enormous Int, part 1.
 
 Define a class that will be able to represent integers with an unlimited number
 of digits, and perform arithmentical operations on them with perfect accuracy.
 
 The most important protected member of your class will be one of the flexible
 resizable arrays that you created for assignment 1. It will be an Array<int>
 where each int contains just one digit of the enormous int being represented.
 
 Pretend that negative numbers do not even exist for this assignment.
 
 Required parts:
 
 class bigint
 { protected:
 Array<int> digits;    // ass you created for assignment 1
 // any other members you need
 
 public:
 bigint();                        // initialise to zero.
 void assign(const bigint & a);
 void assign(int a);              // various ways to initialise
 void assign(string a);
 void print();
 void add(const bigint & a);
 void subtract(const bigint & a);
 int compare(const bigint & a);
 // any "helper methods" you want
 };
 
 So, for example, if you want to find out the value of
 123456789012345678901234567890 + 111222333444555666777888999000 - 696969
 
 bigint a, b, c;
 a.assign("123456789012345678901234567890");
 b.assign("111222333444555666777888999000");
 c.assign(696969);        // 69 is small enough to be an int.
 a.add(b);                // a += b;
 a.subtract(c);           // a -= b;
 a.print();
 
 Of course, more will be coming in the future, including multiply and divide.
 
 a.compare(b) should return:
 if a < b, a negative int (any negative int will do),
 if a = b, zero
 if a > b, a (any) positive int.
 that way you get all six comparisons < <= == != > >= out of one method.
 if (a.compare(B) == 0)  //equal
 */
