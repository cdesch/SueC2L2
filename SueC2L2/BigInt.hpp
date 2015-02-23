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

class BigInt{
protected:
    SmcArray<int> digits;
    
public:
    BigInt();                        // initialise to zero.
    ~BigInt(); //Deconstructor
    void assign(const BigInt & a);
    void assign(int a);              // various ways to initialise
    void assign(string a);
    void print();
    void add(const BigInt & a);
    void subtract(const BigInt & a);
    void multiply(const BigInt & a);
    void divide(const BigInt & a);
    int compare(const BigInt & a);
    int getSize() const;
    int convertCharToInt(char c);
    void removeLeadingZeros(const BigInt & a);
};

//Constructor
BigInt::BigInt(){
    //Initialize an array object
    this->digits.setItem(1, 0); //intialize with 0
}
//Constructor
BigInt::~BigInt(){
}

//Assigning a big int
void BigInt::assign(const BigInt & a){
    //Change the existing size to the new size
    this->digits.changeSize(a.getSize());
    
    //Iterate through the array and copy everything over
    for (int i = 0; i < a.getSize(); i++){
        this->digits.setItem(a.digits.getItem(i), i);
    }
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
    this->digits.changeSize((int) a.size());
    for(int i = 0; i < a.size(); i++){
        char myChar = a.at(i);
        int myTempInt = this->convertCharToInt(myChar);
        this->digits.setItem(myTempInt, i);
    }
}

//Print bigInt
void BigInt::print(){
    for (int i  = 0; i < this->digits.getSize() ; i++){
        cout << this->digits.getItem(i);
    }
    cout << endl;
}

//Adding two large integers that have been split into an array of large digits
void BigInt::add(const BigInt & a){
    int carry = 0;
    int newIndex, index;
    int sumNum = 0;
    index = this->digits.getSize()-1;
    newIndex = abs(this->digits.getSize() - a.digits.getSize());
    
    //Determines the size of loop if a.digits is less than digits then index is one less than a.digits
    if(this->digits.getSize() < a.digits.getSize()){
        this->digits.changeSize(a.digits.getSize()); //Change digits to be the size of the larger number, which happens to be 'a'
        index = a.digits.getSize()-1;
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
        //Determines the size of loop if a.digits is greater than digits
    }else if(this->digits.getSize() >= a.digits.getSize()){
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
void BigInt::subtract(const BigInt & a){
    int maxindex = 0;  //maximum index
    int index = 0;
    int diffNum = 0;
    
    index = this->digits.getSize() - 1;
    maxindex = this->digits.getSize() - a.digits.getSize();
    
    //Compares two numbers to determine if the the result will be a negative number. If negative result, program ends.
    if(this->compare(a) < 0){
        cerr << "Error, negative result and returns early without performing subtraction operation." << endl; //Return error
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
            if(digits.getItem(i) == 0)
                this->digits.removeItem(i);
        }
        i=i;
    }
}

void BigInt::multiply(const BigInt & a){
    int maxindex = 0;  //maximum index
    int multNum = 0;
    int carry = 0;
    int index = 0;
    
    index = digits.getSize() - 1;
    maxindex = a.digits.getSize() - 1;
    
    cout << " index = " << index << " maxindex = " << maxindex << endl;
    cout << " a = " << a.digits.getSize()<< endl;
    
    for( int j = maxindex; j >= 0;){
        carry =0;
        for(int i = index; i >= 0;){
            cout << " IIIII ==== " << i << endl;
            cout << " a.digits.getItem(i) = " << digits.getItem(i) << endl;
            multNum = this->digits.getItem(i) * a.digits.getItem(j) + carry;
            cout << " Multiplication:  " << multNum << endl;
            if(multNum >= 10){
                carry = multNum / 10;
                multNum = multNum % 10;
            }else{
                carry = 0;
            }
            //this->digits.setItem(this->digits.getItem(i) + carry, i); // need to do push
            cout << "digits.getItem(i) " << digits.getItem(i) << endl;
            cout << "carry " << carry << endl;
            cout << " multNum " << multNum << endl;
            cout << " ******" << endl;
            this->digits.setItem(multNum, i);
            i=i-1;
        }
        j=j-1;
        //TODO: need to do push back and then add rows
        if(carry!= 0){ //If there is a carry
            this->digits.insertItem(carry, 0);
        }
    }
    for(int i = 0; i <= this->digits.getSize()-1;){ //Remove Leading zeros
        //if the number is not equal to 0 or there is only 1 element left in the array, stop removing zeros
        if(digits.getItem(i) != 0 || this->digits.getSize() <= 1){
            return;
        }else{
            if(digits.getItem(i) == 0)
                this->digits.removeItem(i);
        }
        i=i;
    }
}
void BigInt::divide(const BigInt & a){
    
}

//Comparing two numbers to check if they are >, <, =
int BigInt::compare(const BigInt & a){
    //Compares the size of the arrays
    if(this->digits.getSize() > a.getSize()){
        return 1;
    }else if(this->digits.getSize() < a.getSize()){
        return -1;
    }else{
        //The numbers of digits must equal
        //Loop through each digit and determine which BigInt is larger
        for(int i = 0; i < this->digits.getSize(); i++){
            if(this->digits.getItem(i) > a.digits.getItem(i)){
                //If these are equal to each other continue
                return 1;
                
            }else if(this->digits.getItem(i) < a.digits.getItem(i) ) {
                return -1;
            }
        }
        return 0;  //Did not find any numbers that were < >, the numbers are equal
    }
}

//Gets the size of an array
int BigInt::getSize() const{
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
