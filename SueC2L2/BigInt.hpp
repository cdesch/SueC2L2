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
#include <vector> //Fixme: use smcarray


//const int kDefaultBigIntSize = 10;

class BigInt{
protected:
    SmcArray<int> digits;
    
public:
    BigInt();                        // initialise to zero.
    ~BigInt(); //Deconstructor
    void assign(const BigInt & a);
    void assign(int a);              // various ways to initialise
    void assign(string a);
    void print() const;
    void add(const BigInt & a);
    void subtract(const BigInt & a);
    void multiply(const BigInt & a);
    void divide(const BigInt & a);
    int compare(const BigInt & a) const;
    int getSize() const;
    void setDigits(SmcArray<int> a);
    int convertCharToInt(char c);
    void removeLeadingZeros();
};

//Constructor
BigInt::BigInt(){
    //Initialize an array object
    this->digits.setItem(0, 0); //intialize with 0
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
void BigInt::print() const{
    for (int i  = 0; i < this->digits.getSize() ; i++){
        cout << this->digits.getItem(i);
    }
    cout << endl;
}

//Adding two large integers that have been split into an array of large digits
void BigInt::add(const BigInt & a){
    int carry = 0;
    int sumNum = 0;
    //Check if equal to 0
    if(this->digits.getSize() == 1 || a.digits.getSize() == 1){
        if(this->digits.getItem(0) == 0){
            this->assign(a);
            return;
        }else if(a.digits.getItem(0) == 0){
            return;
        }
    }
    int indexDifference = abs(this->digits.getSize() - a.digits.getSize());
    int indexSpread = this->digits.getSize() - a.digits.getSize();
    
    //Determines the size of loop if a.digits is less than digits then index is one less than a.digits
    if(this->digits.getSize() < a.digits.getSize()){
        //Insert leading 0's to change the size of this->digits
        for (int k = 0; k < indexDifference; k++){
            this->digits.insertItem(0, 0);
        }
    }
    
    int startingIndex = this->digits.getSize() - 1;

    for(int i = startingIndex; i >= indexDifference; i--){
        if(this->digits.getSize() > a.digits.getSize()){
            sumNum = this->digits.getItem(i) + a.digits.getItem(i-indexDifference) + carry;
        }else{
            sumNum = this->digits.getItem(i) + a.digits.getItem(i) + carry;
        }
        
        if(sumNum >= 10){
            carry = (sumNum/10) % 10;
            sumNum= sumNum-10;
        }else{
            carry = 0;
        }
        
        //cout << "Set: " << sumNum << " at index: " << i << endl;
        this->digits.setItem(sumNum, i);
        
    }
    
    //if A was the larger, copy the rest of the items down into the this->digits
    if(indexSpread < 0){
        for (int k = indexDifference -1; k >= 0; k--){
            this->digits.setItem(a.digits.getItem(k), k);
        }
    }

    //If there is a carry
    if(carry == 1){
        //Check if the carry needs to be inserted at the beginning of the array at in 0
        if(indexDifference - 1 < 0){
           this->digits.insertItem(carry, 0);
        }else{
           this->digits.setItem(this->digits.getItem(indexDifference-1)+1, indexDifference-1);
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

    this->removeLeadingZeros();
}

//TODO: Some awesome comments
void BigInt::multiply(const BigInt & a){
    
    int multNum = 0;
    int carry = 0;
    int zeroIndex = 0;
    
    cout << " index = " << this->digits.getSize() - 1 << " maxindex = " << a.digits.getSize() - 1 << endl;
    cout << " a size = " << a.digits.getSize()<< endl;
    
    vector <BigInt> middleStepNumbers;
    
    for( int j = a.digits.getSize() - 1 ; j >= 0; j--){
        
        //Middle Line
        //SmcArray<int> middleLine;
        SmcArray<int> middleLine(0);
        //middleLine.setItem(0, 0);
        
        for(int z = 0; z < zeroIndex; z++){
            middleLine.pushItem(0);
        }
        
        carry = 0;
        for(int i = this->digits.getSize() - 1; i >= 0; i--){
            
            //cout << " IIIII ==== " << i << endl;
            //cout << " a.digits.getItem(j) = " << a.digits.getItem(j) << endl;
            //cout << " this->digits.getItem(i) = " << this->digits.getItem(i) << endl;
            multNum = this->digits.getItem(i) * a.digits.getItem(j) + carry;
            //cout << " multNum:  " << multNum << endl;
            if(multNum >= 10){
                carry = multNum / 10;
                multNum = multNum % 10;
            }else{
                carry = 0;
            }
            //cout << " carry: " << carry << "+ multnum: " << multNum << endl;
            middleLine.insertItem(multNum, 0);
         //   middleLine.printArray(true);

        }

        //TODO: need to do push back and then add rows
        if(carry!= 0){ //If there is a carry
            middleLine.insertItem(carry, 0);
        }
        zeroIndex++;
        //cout << "middleLine: " ;
        //middleLine.printArray(true);

        BigInt myMiddleLine;
        myMiddleLine.setDigits(middleLine);
        middleStepNumbers.push_back(myMiddleLine);
    }

    BigInt result;
    result.assign(0);
    
    for(int i = 0; i< middleStepNumbers.size(); i++ ){
        //cout << "middle Step num: ";
        //middleStepNumbers[i].print();
        BigInt myInt = middleStepNumbers[i];
        //cout << "middle step bignum: " ;
        //myInt.print();
        
        result.add(myInt);
    }
    //cout << "Myresult: " ;
    //result.print();
    this->assign(result);
    this->removeLeadingZeros();
    
}


void BigInt::divide(const BigInt & a){
    //Assumption 1: there are no negatives
    //Assumption 2: A will always be bigger than B. A is divisable by B
    //TODO: Compare and test for 0
    
    BigInt frontPart;
    SmcArray<int> frontDigits;
    for(int i = 0; i < a.getSize(); i++){
        frontDigits.setItem(this->digits.getItem(i), i);
    }

    
    SmcArray<int> result;
    result.changeSize(this->digits.getSize());
    int numTimesSubtracted = 0;
    int numeratorIndex = a.getSize();
    
    //copy them over //FIXME LATER
    frontPart.digits = frontDigits;

    //FIXEME Adjust language
    
    while(numeratorIndex < this->digits.getSize()){
        //If denomiator larger than the front part, front end of the numerator, then add a digit
        numTimesSubtracted = 0;
        while(a.compare(frontPart) == 1 ){
            //TODO Check for length
            if(frontPart.digits.getSize() > this->digits.getSize()){
                cout << "Huge problem with length " << endl;
            }
            //cout << "numerator index: " <<numeratorIndex << endl;
            //cout << this->digits.getItem(frontPart.digits.getSize()) << endl;
            frontPart.digits.setItem(this->digits.getItem(numeratorIndex) , frontPart.digits.getSize());
            numeratorIndex ++; //Increment the numeratorIndex if we add another digits
        }
        
        
        cout << "front part ";
        frontPart.print();
        while (a.compare(frontPart) == -1 ){
            frontPart.subtract(a);
            cout << "front part ";
            frontPart.print();
            numTimesSubtracted ++;
        }
        
        
        
        cout << "times subtracted " << numTimesSubtracted << " Numerator index: " << numeratorIndex << endl;
        //store the result
        result.setItem(numTimesSubtracted,numeratorIndex);
        result.printArray(true);
    }
    

    this->digits = result;
    this->removeLeadingZeros();
    
}



//Comparing two numbers to check if they are >, <, =
int BigInt::compare(const BigInt & a) const{
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

void BigInt::setDigits(SmcArray<int> a){
    this->digits = a;
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

void BigInt::removeLeadingZeros(){
    for(int i = 0; i <= this->digits.getSize()-1;){ //Remove Leading zeros
        //if the number is not equal to 0 or there is only 1 element left in the array, stop removing zeros
        if(digits.getItem(i) != 0 || this->digits.getSize() <= 1){
            return;
        }else{
            if(digits.getItem(i) == 0)
                this->digits.removeItem(i);
        }
        i = i;
    }
}

#endif
