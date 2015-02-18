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
//TODO: Makefile

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "/////////////////////////////////////////////////////////\n";
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+       Testing Assign                +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;

    BigInt* myBigInt = new BigInt();
    
    //Testing assign with inputs as integers and string
    myBigInt->assign(1234);
    cout << "a = ";
    myBigInt->print();
    cout << "b = ";
    myBigInt->assign("5678");
    myBigInt->print();
    
    cout << "===================" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+       Testing Comparisons           +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    BigInt secondBigInt;
    //Compares two numbers where A is greater than B
    secondBigInt.assign(5678);
    //secondBigInt.print();
    cout << "a = ";
    myBigInt->print();
    cout << "b = ";
    myBigInt->assign("5678");
    myBigInt->print();
    if(myBigInt->compare(secondBigInt) > 0){
        cout << "a is greater than b" << endl;
    }else if (myBigInt->compare(secondBigInt) < 0){
        cout << "b is greater than a" <<  endl;
    }else{
        cout << "a is Equal to b" << endl;
    }
    cout << "===================" << endl;
    
    //Compares two numbers where B is greater than A
    secondBigInt.assign(6789);
    //secondBigInt.print();
    cout << "a = ";
    myBigInt->print();
    cout << "b = ";
    secondBigInt.print();
    if(myBigInt->compare(secondBigInt) > 0){
        cout << "a is greater than b" << endl;
    }else if (myBigInt->compare(secondBigInt) < 0){
        cout << "b is greater than a" <<  endl;
    }else{
        cout << "a is Equal to b" << endl;
    }
    cout << "===================" << endl;

    //Compares two numbers where two numbers are equal
    secondBigInt.assign(5199);
    //secondBigInt.print();
    cout << "a = ";
    myBigInt->print();
    cout << "b = ";
    secondBigInt.print();
    if(myBigInt->compare(secondBigInt) > 0){
        cout << "a is greater than b" << endl;
    }else if (myBigInt->compare(secondBigInt) < 0){
        cout << "b is greater than a" <<  endl;
    }else{
        cout << "a is Equal to b" << endl;
    }
    cout << "==================="<< endl;
    
    
    
    //Testing adding A + B
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+       Addition                     +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "a = ";
    myBigInt->print();
    cout << "b = ";
    secondBigInt.print();
    myBigInt->add(secondBigInt);
    cout << "The result when adding a + b: ";
    myBigInt->print();
    cout << "==================="<< endl;
    
    secondBigInt.assign(5199);
    //Testing subtraction for A - B
    cout << "--------------------------------------" << endl;
    cout << "|       Subtraction                  |" << endl;
    cout << "--------------------------------------" << endl;
    cout << "a = ";
    myBigInt->print();
    cout << "b = ";
    secondBigInt.print();
    myBigInt->subtract(secondBigInt);
    cout << "The result when subtracting a - b: ";
    myBigInt->print();
    cout << "==================="<< endl;
    
    //Example provided in the assignment
    BigInt a, b, c;
    cout << "--------------------------------------" << endl;
    cout << "|      Example in Assignment         |" << endl;
    cout << "--------------------------------------" << endl;
    a.assign("123456789012345678901234567890");
    cout << "a = ";
    a.print();
    cout << "b = ";
    b.assign("111222333444555666777888999000");
    b.print();
    cout << "c = ";
    c.assign(696969);        // 69 is small enough to be an int.
    c.print();
    cout << endl;
    cout << "a + b =    ";// a + b = 234679122456901345679123566890
    a.add(b);                // a += b;
    a.print();
   
    cout << "a + b - c: "; // 234679122456901345679122869921
    a.subtract(c);           // a -= b;
    a.print();
    cout << "==================="<< endl;
    std::cout << "/////////////////////////////////////////////////////////\n";
    
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
