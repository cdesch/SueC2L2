//
//  main.cpp
//  SueC2L2
//
//  Created by cj on 2/10/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

#include <iostream>

#include "SmcArray.hpp"
#include "BigInt.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
enum TOKEN { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, NUMBER };
void testAdditionCase(int numA, int numB){
    BigInt myBigInt;
    BigInt secondBigInt;
    myBigInt.assign(numA);
    myBigInt.print();
    secondBigInt.assign(numB);
    secondBigInt.print();
    myBigInt.add(secondBigInt);
    BigInt result;
    //result.print();
    cout << "actual obj : ";
    myBigInt.print();

    result.assign(numA + numB);
    cout << "expected obj : ";
    result.print();
    if(myBigInt.compare(result) == 0){
        
        cout << "Test Passed - Add: " << numA << "+" << numB << "=" << numA + numB;
        cout << " *****TEST PASSED******" << endl;
    }else{
        cout << "Test Failed - Add: " << numA << "+" << numB << "=" << numA + numB;
        cout << " **===TEST FAILED===***" << endl;
        cout << "The expected result when adding a + b : " << numA + numB << endl;
        cout << "The actual result when adding a + b   : ";
        myBigInt.print();
    }
}

void testSubtractionCase(int numA, int numB){
    BigInt myBigInt;
    BigInt secondBigInt;
    myBigInt.assign(numA);
    secondBigInt.assign(numB);
    myBigInt.subtract(secondBigInt);
    //FIXME: Overload Compare function on BigInt
    BigInt result;
    result.assign(numA - numB);
    if(myBigInt.compare(result) == 0){
        
        cout << "Test Passed - Subtract: " << numA << "-" << numB << "=" << numA - numB;
        cout << " *****TEST PASSED******" << endl;
    }else{
        cout << "Test Failed - Subtract: " << numA << "-" << numB << "=" << numA - numB;
        cout << " **===TEST FAILED===***" << endl;
        cout << "The expected result when subtracting a - b : " << numA - numB << endl;
        cout << "The actual result when subtracting a - b   : ";
        myBigInt.print();
    }
}


void testMultiplicationCase(int numA, int numB){
    BigInt myBigInt;
    BigInt secondBigInt;
    myBigInt.assign(numA);
    secondBigInt.assign(numB);
    myBigInt.multiply(secondBigInt);
    
    BigInt result;
    result.assign(numA * numB);
    if(myBigInt.compare(result) == 0){
        
        cout << "Test Passed - Multiply: " << numA << "*" << numB << "=" << numA * numB;
        cout << " *****TEST PASSED******" << endl;
    }else{
        cout << "Test Failed - Multiply: " << numA << "*" << numB << "=" << numA * numB;
        cout << " **===TEST FAILED===***" << endl;
        cout << "The expected result when Multiplying a * b : " << numA * numB << endl;
        cout << "The actual result when Multiplying a * b : ";
        myBigInt.print();
    }
}

void testDivideCase(int numA, int numB){
    BigInt myBigInt;
    BigInt secondBigInt;
    myBigInt.assign(numA);
    secondBigInt.assign(numB);
    myBigInt.divide(secondBigInt);
    
    BigInt result;
    result.assign(numA / numB);
    if(myBigInt.compare(result) == 0){
        
        cout << "Test Passed - Divide: " << numA << "/" << numB << "=" << numA / numB;
        cout << " *****TEST PASSED******" << endl;
    }else{
        cout << "Test Failed - Divide: " << numA << "/" << numB << "=" << numA / numB;
        cout << " **===TEST FAILED===***" << endl;
        cout << "The expected result when Dividing a / b : " << numA / numB << endl;
        cout << "The actual result when Dividing a / b   : ";
        myBigInt.print();
    }
}

void testScenarioOne(){
    //Example provided in the assignment
    BigInt a, b, c;
    cout << "--------------------------------------" << endl;
    cout << "|      Example in Assignment         |" << endl;
    cout << "|        Test Scenario One           |" << endl;
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
    a.multiply(b);
    a.print();
    a.divide(b);
    a.print();
    cout << "==================="<< endl;
    std::cout << "/////////////////////////////////////////////////////////\n";
}
void testScenarioTwo(){
    //Example provided in the assignment
    BigInt a, b, c;
    cout << "--------------------------------------" << endl;
    cout << "|      Example in Assignment         |" << endl;
    cout << "|        Test Scenario Two           |" << endl;
    cout << "--------------------------------------" << endl;
    a.assign("123456789012345678901234567890");
    cout << "a = ";
    a.print();
    cout << "b = ";
    b.assign("111222333444555666777888999000");
    b.print();
    cout << "a * b = ";
    a.multiply(b);
    a.print();
    cout << "*********" << endl;
    cout << "a = ";
    a.print();
    cout << "b = ";
    b.print();
    cout << "a / b = "; //
    a.divide(b);
    a.print();
    cout << "==================="<< endl;
    
    a.assign("111222333444555666777888999000");
    cout << "a = ";
    a.print();
    cout << "b = ";
    b.assign("123456789012345678901234567890");
    b.print();
    cout << "a * b = ";
    a.multiply(b);
    a.print();
    cout << "*********" << endl;
    cout << "a = ";
    a.print();
    cout << "b = ";
    b.print();
    cout << "a / b = ";
    a.divide(b);
    a.print();
    cout << "==================="<< endl;
    a.assign("111222333444555666777888999000");
    cout << "a = ";
    a.print();
    cout << "b = ";
    b.assign("123456789012345678901234567890");
    b.print();
    cout << "a / b = "; //
    a.divide(b);
    a.print();
    cout << "==================="<< endl;
    a.assign("123456789012345678901234567890");
    cout << "a = ";
    a.print();
    cout << "b = ";
    b.assign("111222333444555666777888999000");
    b.print();
    cout << "a / b = "; //
    a.divide(b);
    a.print();
    std::cout << "/////////////////////////////////////////////////////////\n";
}

void testAddition(){
    cout << "Tests for Addition: " << endl;
    cout << "-------------------" << endl;
    testAdditionCase(0, 1234);
    testAdditionCase(1234, 0);
    testAdditionCase(79492, 794920);
    testAdditionCase(794920, 79492);
    testAdditionCase(7940, 792123122);
    testAdditionCase(792123122, 7940);
    testAdditionCase(1, 2222);
    testAdditionCase(2222,1);
    testAdditionCase(12, 2222);
    testAdditionCase(2222,12);
    testAdditionCase(2222, 2222);
    testAdditionCase(0, 0);
    testAdditionCase(0,25635);
    testAdditionCase(25635, 307620);
    testAdditionCase(333255,1025400);
    testAdditionCase(1358655, 20508000);
    testAdditionCase(500, 500);
    testAdditionCase(0, 0);
    testAdditionCase(0,132);
    testAdditionCase(132, 880);
    testAdditionCase(1012,15400);
    testAdditionCase(16412, 198000);
    testAdditionCase(4123, 6999);
    testAdditionCase(6999, 4123);
    testAdditionCase(8, 9099);
    testAdditionCase(6, 99);
    testAdditionCase(5, 99);
    testAdditionCase(1, 999);
    testAdditionCase(99, 55);
    testAdditionCase(55, 99);
    testAdditionCase(999, 1);
    testAdditionCase(99, 5);
    testAdditionCase(99, 6);
    testAdditionCase(99, 6);
    testAdditionCase(9099, 8);
    testAdditionCase(90900999, 9);
    testAdditionCase(90900999, 1);
    cout <<endl;
}

void testSubtraction(){
    cout << "Tests for Subtraction: " << endl;
    cout << "----------------------" << endl;
    //testSubtractionCase(0, 1234);
    testSubtractionCase(1234, 0);
    //testSubtractionCase(79492, 794920);
    testSubtractionCase(794920, 79492);
    //testSubtractionCase(7940, 792123122);
    testSubtractionCase(792123122, 7940);
    //testSubtractionCase(1, 2222);
    testSubtractionCase(2222,1);
    testSubtractionCase(2222,9);
    //testSubtractionCase(12, 2222);
    testSubtractionCase(2222,12);
    testSubtractionCase(2222, 2222);
    testSubtractionCase(0, 0);
    //testSubtractionCase(0,25635);
    //testSubtractionCase(25635, 307620);
    testSubtractionCase(33325500,1025400);
    //testSubtractionCase(1358655, 20508000);
    testSubtractionCase(500, 500);
    testSubtractionCase(0, 0);
    //testSubtractionCase(0,132);
    //testSubtractionCase(132, 880);
    //testSubtractionCase(1012,15400);
    //testSubtractionCase(16412, 198000);
    //testSubtractionCase(4123, 6999);
    testSubtractionCase(1000, 1);
    testSubtractionCase(10000, 2);
    testSubtractionCase(1000, 55);
    testSubtractionCase(1000, 888);
    testSubtractionCase(100000, 777);
    testSubtractionCase(100000, 99999);
    cout << endl;
}



void testAdditionNegative(){
    cout << "Tests for Addition: " << endl;
    cout << "-------------------" << endl;
    
    /*
    testAdditionCase(10, 5);
    testAdditionCase(10, -5);
    testAdditionCase(-10, -5);
    testAdditionCase(-10, 5);
    
    testAdditionCase(5, 10);
     */
    //testAdditionCase(5, -10);//Broken
    //testAdditionCase(6, -12);//Broken
    testAdditionCase(4, -10);
    //testAdditionCase(-5, -10);
    //testAdditionCase(-5, 10);


    cout <<endl;
}

void testSubtractionNegative(){
    cout << "Tests for Subtraction: " << endl;
    cout << "----------------------" << endl;

    testSubtractionCase(10, 5);
    testSubtractionCase(10, -5);
    testSubtractionCase(-10, -5);
    testSubtractionCase(-10, 5);


    cout << endl;
}

void testMultiply(){
    cout << "Tests for Multiplication: " << endl;
    cout << "-------------------------" << endl;
    testMultiplicationCase(7, 5678);
    testMultiplicationCase(5678, 7);
    testMultiplicationCase(39746, 22);
    testMultiplicationCase(22, 39746);
    testMultiplicationCase(0, 39746);
    testMultiplicationCase(39746,0);
    testMultiplicationCase(1, 39746);
    testMultiplicationCase(39746, 1);
    testMultiplicationCase(9909, 9);
    testMultiplicationCase(9, 9909);
    testMultiplicationCase(9999, 109);
    testMultiplicationCase(109, 9999);
    testMultiplicationCase(70007, 7007);
    testMultiplicationCase(7007, 70007);
    testMultiplicationCase(5000, 900);
    testMultiplicationCase(900, 5000);
    testMultiplicationCase(120009, 5906);
    testMultiplicationCase(5906, 120009);
    cout << endl;
}

void testDivide(){
    cout << "Tests for Division: " << endl;
    cout << "-------------------" << endl;
    testDivideCase(1, 55);
    testDivideCase(5, 5556);
    testDivideCase(1315451, 55);
    testDivideCase(11115451, 222);
    testDivideCase(1545451, 12);
    testDivideCase(1545451, 12);
    testDivideCase(1545451, 2312);
    testDivideCase(1545451, 1234);
    testDivideCase(1545451, 54321);
    testDivideCase(792123122, 7940);
    testDivideCase(9999, 99);
    testDivideCase(9999, 9);
    testDivideCase(2222,12);
    testDivideCase(33325500,1025400);
    testDivideCase(6999, 4123);
    testDivideCase(89999, 11111);
    testDivideCase(2222, 2222);
    testDivideCase(500, 500);
    testDivideCase(800000, 800000);
    testDivideCase(2222,1);
    testDivideCase(1,1);
    testDivideCase(0,1);
    testDivideCase(1545451, 154545);
    testDivideCase(1545451, 15);
    testDivideCase(794920, 79492);
    testDivideCase(70007, 7007);
    testDivideCase(7007, 70007);
    testDivideCase(5000, 900);
    testDivideCase(900, 5000);
    cout << endl;
}


vector<string> parseString(string inputString){
    
    vector<string> parsedInput;
    
    string token;
    stringstream stringStream(inputString);
    
    while(getline(stringStream,token,' ')){
        parsedInput.push_back(token);
        //cout << token << " " << endl;
    }
    
    return parsedInput;
}

//if its + * / .... assume it is a operator
// if it is a - .... we need to check to see if there is a following.
TOKEN tokenDetector(string s){
    
    if(s == "+" || s == "*" || s == "x" || s == "X" || s == "/" || s == "\\"  || s == "-" ){
        
        //cout <<  s <<" is an operator "<<  endl;
        
        if(s == "+" ){
            return ADDITION;
        }else if(s == "*" || s == "x" || s == "X" ){
            return MULTIPLICATION;
        }else if (s == "/" || s == "\\" ){
            return DIVISION;
        }else if (s == "-"){
            return SUBTRACTION;
        }else{
            cout << "Error" << endl;
            return NUMBER;
        }
        
    }else{
        //cout <<  s <<" is a number "<< endl;
        return NUMBER;
    }
    
}



void RPNCalcuator(vector<string>parsedInput){
    BigInt* zero = new BigInt();
    zero->assign(0);
    
    vector<BigInt*> myStack;
    for(int i = 0; i < parsedInput.size(); i++){
        if(tokenDetector(parsedInput[i]) != NUMBER){
            //If it is an operator -- Do some math
            
            if(myStack.size() < 2){
                cout << "Error: illegal Reverse Polish Notation Syntax" << endl;
                return;
            }
            //pop last two values
            BigInt* second = new BigInt();
            second->assign(*myStack.back());
            myStack.pop_back();
            
            BigInt* first = new BigInt();
            first->assign(*myStack.back());
            myStack.pop_back();
            
            BigInt* result = new BigInt();
            
            
        
            //Determine which operator &
            //do the calcuation
            TOKEN oper = tokenDetector(parsedInput[i]);
            switch (oper){
                case ADDITION:
                    first->add(*second);
                    result->assign(*first);
                    
                    break;
                case DIVISION:
    
                    if(second->compare(*zero) != 0){
                        first->divide(*second);
                        result->assign(*first);
                        //result = first / second;
                        //delete zero;
                    }else{
                        cout << "Attempted to divide by 0" << endl;
                        delete zero;
                        return;
                    }
                    
                    break;
                case SUBTRACTION:
                    first->subtract(*second);
                    result->assign(*first);
                    //result = first - second;
                    
                    break;
                case MULTIPLICATION:
                    first->multiply(*second);
                    result->assign(*first);
                    //result = first * second;
                    
                    break;
                    
                default:
                    cout<< "Error: Operator not found" << endl;
            }
            //cout <<  result << " " << first << " " << second << endl;
            delete first;
            delete second;
            //Push the result back onto the stack
            myStack.push_back(result);
            
        }else{
            //If it is a number -- just add it to the stack.
            if(i == parsedInput.size() - 1){
                cout << "Error: illegal Reverse Polish Notation Syntax" << endl;
                return;
            }
            BigInt* number = new BigInt();
            number->assign(parsedInput[i].c_str());
            myStack.push_back(number);
            //myStack.push_back(atoi(parsedInput[i].c_str()));
        }
    }
    
    if(zero){
        delete zero;
    }
    
    if(myStack.size() > 1){
        cout << "Error: illegal Reverse Polish Notation Syntax" << endl;
        return;
    }
    
    cout << "My Calculation: ";
    myStack.back()->print();
    
}




void testRPNProvidedUseCases(){
    /*
     input:  123 2 + 50 25 25 + + *
     (123+2) | 25 + 25 + 50|
     125       100
     125 * 100
     output: 12500
     input:  99999999999999999999999999999999999999999999999 2 * 1 -
     2 *  999....  - 1
     output: 199999999999999999999999999999999999999999999997
     input:  -3 -4 *
     output: 12
     */
    
    vector<string> useCases;
    useCases.push_back("5 1 2 + 4 * + 3 -");
    useCases.push_back("123 2 + 50 25 25 + + *");
    useCases.push_back("123 321 +");
    useCases.push_back("123 + 321"); //should fail
    useCases.push_back("123 2 + 50 25 25 + + "); //should fail
    useCases.push_back("123 2 + 50 25 25 + + + + + "); //should fail
    useCases.push_back("99999999999999999999999999999999999999999999999 2 * 1 -");
    //useCases.push_back("123 2 + 50 25 25 + + + + + ");
    
    for (int i = 0; i < useCases.size(); i++){
        vector<string> parsedInput = parseString(useCases[i]);
        RPNCalcuator(parsedInput);
        
    }
    
}

int main(int argc, const char * argv[]) {
    /*
    testAddition();
    testSubtraction();
    testMultiply();
    testDivide();
    testScenarioTwo();
*/
    //testRPNProvidedUseCases();
    
    testAdditionNegative();
    //testSubtractionNegative();
    
    return 0;
}
