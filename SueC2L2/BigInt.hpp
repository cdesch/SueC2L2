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
    bool negative; //Indicates a negative number
    bool negativeHandled;
public:
    BigInt();                        // initialise to zero.
    ~BigInt(); //Deconstructor
    void assign(const BigInt & a);
    void assign(int a);              // various ways to initialise
    void assign(long a);              // various ways to initialise
    void assign(string a);
    void print() const;
    void add(const BigInt & a);
    void subtract(const BigInt & a);
    void multiply(const BigInt & a);
    void divide(const BigInt & a);
    int compare(const BigInt & a) const;
    int compareAbsoluteValue(const BigInt & a) const;
    int getSize() const;
    void setDigits(SmcArray<int> a);
    int convertCharToInt(char c);
    void removeLeadingZeros();
    
    bool handleNegativesForAddition(const BigInt & a);
    bool handleNegativesForSubtraction(const BigInt & a);
    //TODO: move these below to be consistent in this class
    void setNegative(bool negative){
        this->negative = negative;
    }
    
    bool getNegative() const{
        return this->negative;
    }
    
    bool getPositive() const{
        return !this->getNegative();
    }
    
};

//Constructor
BigInt::BigInt(){
    //Initialize an array object
    this->digits.setItem(0, 0); //intialize with 0
    this->negative = false;
    this->negativeHandled = false;
}
//Constructor
BigInt::~BigInt(){
}

//Assigning a big int
void BigInt::assign(const BigInt & a){
    //Change the existing size to the new size
    this->digits.changeSize(a.getSize());
    
    this->negative = a.getNegative();
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
    
    if(a < 0){
        this->negative = true;
    }
    a = abs(a);
    
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

//Take an integer and split into digits
void BigInt::assign(long a){
    //Modulus  -- Loop until until no remainder
    // e.g.            54321
    //      breaks into 5 4 3 2 1
    if(a < 0){
        this->negative = true;
    }
    
    a = abs(a);
    
    long b = a;
    int length = 1;
    while (b /= 10)
        length++;
    int digit;
    this->digits.changeSize(length);
    for(int i = 0; i < this->digits.getSize(); i++){
        digit = (int) (a % 10);
        a = a / 10;
        this->digits.setItem(digit,length-1-i);
    }
}


//Take a string and split into digits
void BigInt::assign(string a){
    //1) Loop through each character in string
    //2) covert that character to an integer
    //3) add that integer into the "this->digits" array by using setItem
    
    if(a[0] == '-'){
        this->negative = true;
        a.erase(0,1);
    }
    
    
    this->digits.changeSize((int) a.size());
    for(int i = 0; i < a.size(); i++){
        char myChar = a.at(i);
        int myTempInt = this->convertCharToInt(myChar);
        this->digits.setItem(myTempInt, i);
    }
}

//Print bigInt
void BigInt::print() const{
    if(this->negative){
        cout << "-" ;
    }
    for (int i  = 0; i < this->digits.getSize() ; i++){
        
        cout << this->digits.getItem(i);
    }
    cout << endl;
}


bool BigInt::handleNegativesForAddition(const BigInt & a){
    
    //cout << __PRETTY_FUNCTION__ << endl;
    this->negativeHandled = true;
    
    if(this->getPositive() && a.getPositive()){
        return false;
    }else if(this->getPositive() && a.getNegative()){
        this->subtract(a);
        return true;
    }else if(this->getNegative() && a.getNegative()){
        return false;
    }else if(this->getNegative() && a.getPositive()){
        this->subtract(a);
        return true;
    }else{
        //satisfy compiler
        cout << "warning: should not have reached this" << endl;
        return false;
    }
}

//Adding two large integers that have been split into an array of large digits
void BigInt::add(const BigInt & a){
    
    //cout << __PRETTY_FUNCTION__ << endl;
 
    if(!this->negativeHandled){
        if(this->handleNegativesForAddition(a)){
            return;
        }
    }
    
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
    
    int indexDifference = abs(this->digits.getSize() - a.digits.getSize()); //Indexdifference is the difference between the two nubers 5 and 2 --- difference is 3
    int indexSpread = this->digits.getSize() - a.digits.getSize(); //
    
    //Determines the size of loop if a.digits is less than digits then index is one less than a.digits
    if(this->digits.getSize() < a.digits.getSize()){
        //Insert leading 0's to change the size of this->digits
        for (int k = 0; k < indexDifference; k++){
            this->digits.insertItem(0, 0);
        }
        indexDifference = 0;
    }
    
    int startingIndex = this->digits.getSize()-1;
    //cout << endl << "          starting index " << startingIndex << " indexDifference " << indexDifference << endl;
    for(int i = startingIndex; i >= indexDifference; i--){
        if(this->digits.getSize() >= a.digits.getSize()){
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
        //cout << "Index Difference:  " << indexDifference << "... " << indexDifference -1 << endl;
        //Check if the carry needs to be inserted at the beginning of the array at in 0
        if(indexDifference - 1 < 0){
            this->digits.insertItem(carry, 0);
        }else{
            if(indexDifference - 1 >= 1){
                while (indexDifference - 1 >= 0 && carry ==1){
                    //cout << "Index Difference:  " << indexDifference << "... " << indexDifference -1 << endl;
                    int firstDigit = this->digits.getItem(indexDifference-1);
                    if((firstDigit + carry) > 9){
                        //Move it up one
                        //If the carry in addition to the existing digit is larger than 9, we need to carry over to the next number
                        this->digits.setItem(firstDigit + carry - 10, indexDifference-1);
                        
                        if(indexDifference - 1 == 0 && carry ==1){
                            this->digits.insertItem(carry, 0);
                            break;
                        }
                        
                    }else{
                        
                        //Add the carry to the first digit in the array
                        this->digits.setItem(this->digits.getItem(indexDifference-1)+1, indexDifference-1);
                        break;
                    }
                    indexDifference --;
                }
            }else{
                int firstDigit = this->digits.getItem(indexDifference-1);
                if((firstDigit + carry) > 9){
                    //Move it up one
                    //If the carry in addition to the existing digit is larger than 9, we need to carry over to the next number
                    this->digits.setItem(firstDigit + carry - 10, indexDifference-1);
                    this->digits.insertItem(carry, 0);
                }else{
                    //Add the carry to the first digit in the array
                    this->digits.setItem(this->digits.getItem(indexDifference-1)+1, indexDifference-1);
                }
            }
    
        }
    }
    this->negativeHandled = false;
    //this->removeLeadingZeros();
    //check
}
bool BigInt::handleNegativesForSubtraction(const BigInt & a){
    
    //cout << __PRETTY_FUNCTION__ << endl;
    this->negativeHandled = true;
    
    if(this->getPositive() && a.getPositive()){
        return false;
    }else if(this->getPositive() && a.getNegative()){
        this->add(a);
        return true;
    }else if(this->getNegative() && a.getNegative()){
        this->negativeHandled = false;
        return false;
    }else if(this->getNegative() && a.getPositive()){
        this->add(a);
        return true;
    }else{
        //satisfy compiler
        cout << "warning: should not have reached this" << endl;
        return false;
    }
}


//Subtracting two integers, results must be positive.
void BigInt::subtract(const BigInt & a){
    
    //cout << __PRETTY_FUNCTION__ << endl;
    if(!this->negativeHandled){
        if(this->handleNegativesForSubtraction(a)){
            return;
        }
    }
    
    //cout << "should be here" << endl;
    
    
    int maxindex = 0;  //maximum index
    int index = 0;
    int diffNum = 0;
    
    index = this->digits.getSize() - 1;
    maxindex = this->digits.getSize() - a.digits.getSize();
    
    //Compares two numbers to determine if the the result will be a negative number. If negative result, program ends.
    
    if(this->compareAbsoluteValue(a) < 0){
        
        

        
        BigInt tempInt;
        tempInt.assign(a);
        
        if(this->getPositive() && tempInt.getPositive()){
            tempInt.setNegative(true);
        }
        index = tempInt.digits.getSize() - 1;
        maxindex = tempInt.digits.getSize() - this->digits.getSize();

        for(int i = index; i >= 0; i--){

            if(this->digits.getItem(i-maxindex) > tempInt.digits.getItem(i)){

                tempInt.digits.setItem(tempInt.digits.getItem(i) + 10, i);
                tempInt.digits.setItem(tempInt.digits.getItem(i-1)-1, i-1);
            }
            diffNum = tempInt.digits.getItem(i) -  this->digits.getItem(i-maxindex);
            
            //diffNum = digitPlaceHolder - this->digits.getItem(i-maxindex);
            tempInt.digits.setItem(diffNum, i);
        }
        
        //cout << "print temp" ;
        //tempInt.print();
        this->assign(tempInt);
        this->removeLeadingZeros();
        
        if(!this->negativeHandled){
            if(this->getNegative() && a.getNegative()){
                this->setNegative(false);
            }
        }
    }else{
        index = this->digits.getSize() - 1;
        maxindex = this->digits.getSize() - a.digits.getSize();
        
        for(int i = index; i >= 0; i--){
            //
            if(this->digits.getItem(i) < a.digits.getItem(i-maxindex)){
                this->digits.setItem(this->digits.getItem(i) + 10, i);
                this->digits.setItem(this->digits.getItem(i-1)-1, i-1);
            }
            diffNum = this->digits.getItem(i) -  a.digits.getItem(i-maxindex);
            this->digits.setItem(diffNum, i);
        }
        
        this->removeLeadingZeros();
    }
    


    
    //this->digits.printArray(true);
    

    this->negativeHandled = false;
}

//Multiplying two numbers
void BigInt::multiply(const BigInt & a){
    
    int multNum = 0;
    int carry = 0;
    int zeroIndex = 0;
    
    //cout << " index = " << this->digits.getSize() - 1 << " maxindex = " << a.digits.getSize() - 1 << endl;
    //cout << " a size = " << a.digits.getSize()<< endl;
    
    vector <BigInt> middleStepNumbers;
    
    for( int j = a.digits.getSize() - 1 ; j >= 0; j--){
        
        //Middle Line
        SmcArray<int> middleLine(0);
        
        for(int z = 0; z < zeroIndex; z++){
            middleLine.pushItem(0);
        }
        
        carry = 0;
        for(int i = this->digits.getSize() - 1; i >= 0; i--){
            
            multNum = this->digits.getItem(i) * a.digits.getItem(j) + carry;
            //cout << " multNum:  " << multNum << endl;
            if(multNum >= 10){
                carry = multNum / 10;
                multNum = multNum % 10;
            }else{
                carry = 0;
            }
            middleLine.insertItem(multNum, 0);
            
        }
        if(carry!= 0){ //If there is a carry
            middleLine.insertItem(carry, 0);
        }
        zeroIndex++;
        
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

//Dividing two numbers
void BigInt::divide(const BigInt & a){
    //Assumption 1: there are no negatives
    //Assumption 2: A will always be bigger than B. A is divisable by B
    
    BigInt frontPart;
    SmcArray<int> frontDigits;
    for(int i = 0; i < a.getSize(); i++){ //Looping to get digits
        frontDigits.setItem(this->digits.getItem(i), i);
    }
    
    if(a.compare(frontPart) == -1){ //Checking to see if numerator is less than the denominator
        return;
    }
    
    SmcArray<int> result;
    result.changeSize(this->digits.getSize());
    int numTimesSubtracted = 0; //Initializing variable that counts the number of times subtracting
    int numeratorIndex = a.getSize(); //Getting size of numberator
    
    frontPart.digits = frontDigits; //Copying front digits into part digits
    
    //When the number of digits in numerator and denominator are the same and making sure the numbers are different
    while (numeratorIndex == this->digits.getSize() && (a.compare(frontPart) != 1)){
        frontPart.subtract(a);
        //frontPart.print(); // for debugging
        numTimesSubtracted = numTimesSubtracted + 1;
        result.setItem(numTimesSubtracted,numeratorIndex);
        //result.printArray(true); // for debugging
    }
    
    //When the number of digits in numerator is greater than the number of digits in the denominator
    while(numeratorIndex < this->digits.getSize()){
        //If denominator is larger than the front part of numerator then add a digit to numerator number
        numTimesSubtracted = 0; //Setting counter equal to zero
        while(a.compare(frontPart) == 1 ){ //Do while the
            if(frontPart.digits.getSize() > this->digits.getSize()){ //Checking to make sure length of numbers is okay
                cout << "Problem with length " << endl; //Error message
            }
            //cout << this->digits.getItem(frontPart.digits.getSize()) << endl; //Debugging statements
            //cout << "NUMERATOR INDEX " << numeratorIndex << endl; //Debugging statements
            frontPart.digits.setItem(this->digits.getItem(numeratorIndex),frontPart.digits.getSize()); //Setting the digit in the answer array
            numeratorIndex ++; //Increment the numeratorIndex if we add another digits
        }
        //frontPart.print(); // for debugging
        
        while (a.compare(frontPart) != 1 && numeratorIndex <= this->digits.getSize()){ //Comparing the numerator and denominator front part are not equal and the numerator index is less than or equal to the digit size
            frontPart.subtract(a); //Subtract the front part from the numerator
            //frontPart.print(); // for debugging
            numTimesSubtracted ++; //Incrementing the counter that is counting the number of times the denominator is subtracted from teh denominator
        }
        
        //cout << "times subtracted " << numTimesSubtracted << " Numerator index: " << numeratorIndex << endl; // debugging statement
        //Storeing the result
        if(numeratorIndex < 0) numeratorIndex = numeratorIndex + 1; // Incrementing the numerator index if index becomes negative
        result.setItem(numTimesSubtracted,numeratorIndex); //Setting the digit in the answer array
        //result.printArray(true); // for debugging
    }
    this->digits = result; //Putting the result into the digits array
    this->removeLeadingZeros(); //Callling function that removes the leading zeroes
}


//Comparing two numbers to check if they are >, <, =
// -1 if a is greater than this->digits
// 0 if they are equal
// 1 if this-> digits is greater than 'a'
int BigInt::compare(const BigInt & a) const{
    
    //this->digits.printArray(true); // for debugging
    
    if(this->getNegative() && a.getPositive()){
        return -1;
    }else if(this->getPositive() && a.getNegative()){
        return 1;
    }
    
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

//Comparing two numbers to check if they are >, <, =
// -1 if a is greater than this->digits
// 0 if they are equal
// 1 if this-> digits is greater than 'a'
int BigInt::compareAbsoluteValue(const BigInt & a) const{
    
    //this->digits.printArray(true); // for debugging
    
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
