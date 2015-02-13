//
//  BigInt.h
//  SueC2L2
//
//  Created by cj on 2/10/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

#ifndef SueC2L2_BigInt_h
#define SueC2L2_BigInt_h

#include "SmcArray.hpp"

const int kDefaultBigIntSize = 10;

class BigInt
{
protected:
    SmcArray<int> digits;    // ass you created for assignment 1
    // any other members you need
    
public:
    BigInt();                        // initialise to zero.
    ~BigInt(); //Deconstructor
    void assign( BigInt & a);
    void assign(int a);              // various ways to initialise
    void assign(string a);
    void print();
    void add( BigInt & a);
    void subtract( BigInt & a);
    int compare( BigInt & a);
    int compare( BigInt * a);
    
    int getSize();
    int convertCharToInt(char c);
    void removeLeadingZeros(const BigInt & a);
    // any "helper methods" you want
};

//Constructor
BigInt::BigInt(){
    //Initialize an array object
    //cout << __PRETTY_FUNCTION__ << " Starts " << endl;
    this->digits = SmcArray<int>(1);
    this->digits.setItem(1, 0);  //FIXME : Chris
    //cout << __PRETTY_FUNCTION__ << " Ends " << endl;
}
//Constructor
BigInt::~BigInt(){
    //Delete the digits object
}

//Assigning a big int
void BigInt::assign( BigInt & a){
    //TODO: Chris - Give structure and hints
}

//Take an integer and split into digits
void BigInt::assign(int a){
    //Modulus  -- Loop until until no remainder
    // e.g.            54321
    //      breaks into 5 4 3 2 1
    int b = a;
    int length = 1;
    while (b /= 10)
        length++;
    int digit;
    this->digits.changeSize(length);
    for(int i = 0; i < this->digits.getSize(); i++){
        digit = a % 10;
        a = a / 10;
        this->digits.setItem(digit,length-1-i);
    }
}

//Take a string and split into digits
void BigInt::assign(string a){
    //1) Loop through each character in string
    //2) covert that character to an integer
    //3) add that integer into the "this->digits" array by using setItem
    this->digits.changeSize((int)a.size());  //FIXME: Cast to int (unsigned int)
    for(int i = 0; i < a.size(); i++){
        char myChar = a.at(i);
        int myTempInt = this->convertCharToInt(myChar);
        this->digits.setItem(myTempInt, i);
    }
}

//Print the bigInt
void BigInt::print(){
    for (int i  = 0; i < this->digits.getSize() ; i++){
        cout << this->digits.getItem(i);
    }
    cout << endl;
}

//Adding two large integers that have been split into an array of large digits
void BigInt::add( BigInt & a){
    int carry = 0;
    int newIndex, index;
    int sumNum = 0;
    index = this->digits.getSize()-1;
    newIndex = abs(this->digits.getSize() - a.digits.getSize());
    
    //Determines the size of loop if a.digits is less than digits then index is one less than a.digits
    if(this->digits.getSize() <= a.digits.getSize()){
        index = a.digits.getSize()-1;
        for(int i = index; i >= newIndex; i--){
            //Sums the digits and any carry
            sumNum = a.digits.getItem(i) + this->digits.getItem(i-newIndex) + carry;
            if(sumNum >= 10){
                carry = (sumNum/10) % 10;
                sumNum=sumNum-10;
            }else{
                //Setting carry back to zero
                carry = 0;
            }
            
            a.digits.setItem(sumNum, i);
        }
        //If there is a carry
        if(carry != 0) {
            a.digits.insertItem(carry, 0);
        }
        //Storing added vectors in digits
        this->digits = a.digits;
        
        //Determines the size of loop if a.digits is greater than digits
    }else if(this->digits.getSize() > a.digits.getSize()){
        index = digits.getSize()-1;
        for(int i = index; i >= newIndex; i--){
            sumNum = this->digits.getItem(i) + a.digits.getItem(i-newIndex) + carry;
            if(sumNum >= 10){
                carry = sumNum / 10;
                sumNum = sumNum % 10;
            }else{
                carry = 0;
            }
            this->digits.setItem(sumNum, i);
        }
        //If there is a carry
        if(carry!= 0){
            this->digits.insertItem(carry, 0);
        }
    }
}

//Subtracting two integers, results must be positive.
void BigInt::subtract( BigInt & a){
    int maxindex = 0;  //maximum index
    int index = 0;
    int diffNum = 0;
    
    index = this->digits.getSize() - 1;
    maxindex = this->digits.getSize() - a.digits.getSize();
    
    //Compares two numbers to determine if the the result will be a negative number. If negative result, program ends.
    if(this->compare(a) < 0){
        cerr << "Error, negative result." << endl; //Return error
        return; //Return early
    }
    
    for(int i = index; i >= maxindex;){
        if(this->digits.getItem(i) < a.digits.getItem(i-maxindex)){
            this->digits.setItem(this->digits.getItem(i) + 10, i);
            this->digits.setItem(this->digits.getItem(i-1)-1, i-1);
        }
        diffNum = this->digits.getItem(i) -  a.digits.getItem(i-maxindex);
        this->digits.setItem(diffNum, i);
        i=i-1;
    }
    //Remove Leading zeros
    for(int i = 0; i <= this->digits.getSize()-1;){
        //if the number is not equal to 0 or there is only 1 element left in the array, stop removing zeros
        if(digits.getItem(i) != 0 || this->digits.getSize() <= 1){
            return;
        }else{
            if(digits.getItem(i) == 0 )
                this->digits.removeItem(i);
        }
        i=i;
    }
}

//Comparing two numbers to check if they are >, <, =
int BigInt::compare( BigInt & a){
    
    //Compares the size of the arrays
    if(this->digits.getSize() > a.getSize()){
        return 1;
    }else if(this->digits.getSize() < a.getSize()){
        return -1;
    }else{
        //The numbers of digits must equal
        //Loop through each digit and determine which BigInt is larger
        for(int i = 0; i < this->digits.getSize(); i++){
            //cout << i << " i " << myDigits.size() << endl;
            if(this->digits.getItem(i) > a.digits.getItem(i)){
                //If these are equal to each other continue
                return 1;
                
            }else if(this->digits.getItem(i) < a.digits.getItem(i) ) {
                return -1;
            }
            //if else continue;
        }
        return 0;  //Did not find any numbers that were < >, the numbers are equal
    }
}

//Using pointer instead of pass by reference
int BigInt::compare(BigInt * a){
    //Compares the size of the arrays
    if(this->digits.getSize() > a->getSize()){
        return 1;
    }else if(this->digits.getSize() < a->getSize()){
        return -1;
    }else{
        //The numbers of digits must equal
        //Loop through each digit and determine which BigInt is larger
        for(int i = 0; i < this->digits.getSize(); i++){
            //cout << i << " i " << myDigits.size() << endl;
            if(this->digits.getItem(i) > a->digits.getItem(i)){
                //If these are equal to each other continue
                return 1;
                
            }else if(this->digits.getItem(i) < a->digits.getItem(i) ) {
                return -1;
            }
            //if else continue;
        }
        return 0;  //Did not find any numbers that were < >, the numbers are equal
    }
}

//Gets the size of an array
int BigInt::getSize(){
    return this->digits.getSize();
}

//Simple char to int converter via ASCII indexs
int BigInt::convertCharToInt(char c){
    int myTempInt = (int)c;
    if(myTempInt < 48 || myTempInt > 57) {
        std::cout << "Error: Not an integer!\n";
        return -1; //Error checking
    }
    return myTempInt - 48;
}

#endif
