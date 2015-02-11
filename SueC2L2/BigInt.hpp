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
    void assign(const BigInt & a);
    void assign(int a);              // various ways to initialise
    void assign(string a);
    void print();
    void add(const BigInt & a);
    void subtract(const BigInt & a);
    int compare(const BigInt & a);
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
void BigInt::assign(const BigInt & a){
    //TODO: Chris - Give structure and hints
}

void BigInt::assign(int a){

    //In this case it will take an integer\
    //Hint is Modulus  -- Loop until until no remainder
    // e.g.            54321
    //      break into 5 4 3 2 1
    int b = a;
    int length = 1;
    while ( b /= 10 )
        length++;
    int digit;
    this->digits.changeSize(length);
    for(int i = 0; i < this->digits.getSize(); i++){
        digit = a % 10;
        a = a / 10;
        this->digits.setItem(digit,length-1-i);
    }

    
}

void BigInt::assign(string a){

    //In this case it will take a string
    //like in the last class lab 3 - you'll need to break apart the number and put it in the the "this->digits"
    //1) Loop through each character in string
    //2) covert that character to an integer
    //3) add that integer into the "this->digits" array
    //How to add: this->digits.pushItem(value)
    this->digits.changeSize((int)a.size());  //FIXME: Cast to int (unsigned int)
    for(int i = 0; i < a.size(); i++){
        char myChar = a.at(i);
        int myTempInt = this->convertCharToInt(myChar);
        this->digits.setItem(myTempInt, i);
    }

}

/*
 void BigInt::removeLeadingZeros(const BigInt & a){
 for (int i = 0; i < this->digits.getSize(); i++){
 b = a;
 if(b->getItem() == 0){
 //remove that leading 0;
 b str.erase(a str.begin()+0);
 }else{
 return a;
 }
 }
 return a.at;
 }
 */


//Print the bigInt
void BigInt::print(){
    for (int i  = 0; i < this->digits.getSize() ; i++){
        cout << this->digits.getItem(i);
    }
    cout << endl;
}


void BigInt::add(const BigInt & a){
    //TODO:
    //HINT : this->digits           == myDigits
    // this->digits.getSize()       == myDigits.size()
    // b.digits.getItem(i)          == numVector[i]->getValue()
    // this->digits.getItem(i-newIndex) == myDigits[i-newIndex]->getValue()
    // b.digits.setItem(sumNum, i ) == numVector[i]->setValue(sumNum);
    // getItem(i)                   == getValue(i)
    // setItem(value, index)        == setValue
    
    //Refer to last assignment
    BigInt b = a; //Use b to prevent frustration
    int carry = 0;
    int newIndex, index;   //Index is right index -- consider changing the name to lastIndex
    int sumNum = 0;
    index = this->digits.getSize()-1;
    newIndex = abs(this->digits.getSize() - b.digits.getSize());
    
    //If myDigits is less than, store numbers in numVector
    if(this->digits.getSize() <= b.digits.getSize()){
        index = b.digits.getSize()-1;
        for(int i = index; i >= newIndex; i--){
            sumNum = b.digits.getItem(i) + this->digits.getItem(i-newIndex) + carry;
            if(sumNum >= 10){
                carry = (sumNum/10) % 10;
                sumNum=sumNum-10;
            }else{
                carry = 0;
            }
            
            b.digits.setItem(sumNum, i);
        }
        if(carry == 1) {
            b.digits.setItem(b.digits.getItem(newIndex-1)+1 , newIndex-1);
        }
        
        this->digits = b.digits;
        
    }else if(this->digits.getSize() > b.digits.getSize()){

        for(int i = this->digits.getSize()-1; i >= newIndex; i--){
            sumNum = this->digits.getItem(i-newIndex) + b.digits.getItem(i) + carry;
            if(sumNum >= 10){
                carry = sumNum / 10;
                sumNum = sumNum % 10;
            }
            else{
                carry = 0;
            }
            this->digits.setItem(sumNum, i );
        }
        //
        if(carry==1){
            this->digits.setItem(this->digits.getItem(newIndex-1)+1 , newIndex-1);
        }
    }
}


void BigInt::subtract(const BigInt & a){
    //Refer to last assignment
    BigInt b = a; //Use b to prevent frustration
    int maxindex=0;
    int index=0;
    int diffNum=0;
   
    /*
    if(isGreaterThan(numVector)) {
        cout << "Error, negative result." << endl; //Return error
        return;
    }*/
    
    index = this->digits.getSize() - 1;
    maxindex = this->digits.getSize() - b.digits.getSize();
    
    for(int i = index; i >= maxindex;){
        if(this->digits.getItem(i) < b.digits.getItem(i-maxindex)){
            this->digits.setItem(this->digits.getItem(i) + 10, i);
            this->digits.setItem(this->digits.getItem(i-1)-1, i-1);
        }
       diffNum = this->digits.getItem(i) -  b.digits.getItem(i-maxindex);
        this->digits.setItem(diffNum, i);
        i=i-1;
        
    }
    //Remove Leading zeros
    //this->digits = removeLeadingZeros(this->digits);

}


//TODO: Comments
//TODO: Test cases
int BigInt::compare(const BigInt & a){
    //Refer to last semester assignment
    BigInt b = a; //Copy for manipulation purposes
    //
    if(this->digits.getSize() < b.getSize()){
        return 1;
    }else if(this->digits.getSize() > b.getSize()){
        return -1;
    }else{
        
        //The numbers of digits must equal
        //Loop through each digit and determine which BigInt is larger
        //Number 123456334322
        //Number 123457335322 <-- This number is greater
        for(int i = 0; i < this->digits.getSize(); i++){
            //cout << i << " i " << myDigits.size() << endl;
            if(this->digits.getItem(i) > b.digits.getItem(i)){
                //If these are equal to each other continue
                return 1;
                
            }else if(this->digits.getItem(i) < b.digits.getItem(i) ) {
                return -1;
            }
            //if else continue;
        }
        return 0;  //Did not find any numbers that were < >, the numbers are equal
    }
}

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
