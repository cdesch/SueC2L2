//
//  SmcArray.h
//  SueC2L2
//
//  Created by cj on 2/10/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

#ifndef __SueC2L2__SmcArray__
#define __SueC2L2__SmcArray__

using namespace std;

//Constants
const int defaultSize = 1; //default size is 1
const int minSize = 0; //min size of array is 0
const int maxSize = 100; //max size of array is 100
const int kDefaultValue = 0; //default value is set to 0

//Reference: http://www.cplusplus.com/forum/windows/88843/
//String Sample Context
static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

//Length of the string sample context
int stringLength = sizeof(alphanum) - 1;

// Random Character Generator Function
// returns a random character
char genRandomChar(){
    return alphanum[rand() % stringLength]; //character generator and returns a random charater
}

//Class Template of Element for each item
template<class Element>
class SmcArray{
    
public:
    SmcArray(); // Default Constructor
    SmcArray(int s); //  Constructor with params
    ~SmcArray(); // Deconstructor
    
    int getSize() const; // Get size of array
    void pushItem(Element value); //inserts item on end of the array
    void setItem(Element value, int index); //sets an item  (overwrites) at given index
    Element getItem(int index); //retrieves an item at a given index - This item can be of Type Element, which can be several different types
    
    Element getItem(int index) const; //retrieves an item at a given index w/const
    void insertItem(Element value, int index); //inserts an item at a given index
    void removeItem(int index); // Delete array item
    void printArray(bool linear) const; // Print Array
    void setDefault(Element value); //Sets a default value for out of bounds index expansions via changeSize
    Element getDefault(); //Returns the default value
    void changeSize(unsigned int newSize); //Changes the array size
    
protected:
    int size; // Size of array (elements)
    Element * items; //Array of items of type element
    Element defaultValue;// Default value
    void allocateArray();//Allocates an array of given size
    void copyArrayIncreasedSize(int s); //Copies an array with increased size
    bool checkIndexBounds(int index) const;//Checks the array is within bounds
};

//Default Constructor
template <class Element>
SmcArray<Element>::SmcArray(){
    //cout << __PRETTY_FUNCTION__ << endl;
    //Set the array using the defaults
    this->size = defaultSize;
    
    //Allocate an array of this->size
    this->defaultValue = kDefaultValue;
    this->allocateArray();
    this->setItem(0,0);
    
}

//Constructor with params
template <class Element>
SmcArray<Element>::SmcArray(int s){
    //cout << __PRETTY_FUNCTION__ << endl;
    this->size = s;
    
    //Allocate an array of this->size
    this->defaultValue = kDefaultValue;
    this->allocateArray();
    
}

//Deletes the items in array
template <class Element>
SmcArray<Element>::~SmcArray(){
    //delete [] this->items;
}

//Allocates an array of given size
template <class Element>
void SmcArray<Element>::allocateArray(){
    //Allocate an array of this->size
    this->items = new Element[this->size];
}

//Gets size of the array
template <class Element>
int SmcArray<Element>::getSize() const{
    return this->size; //returns the size fo the array
}

//Add an item to the end of the array
template <class Element>
void SmcArray<Element>::pushItem(Element value){
    
    //Increase the size of array
    this->copyArrayIncreasedSize(this->size + 1);
    
    //Add our new value into the last slot in the array
    this->items[this->size - 1] = value;
}

//sets an item in the array (overwrite)
template <class Element>
void SmcArray<Element>::setItem(Element value, int index){
    
    //Check to see if the index can be written to/if the index is a valid index
    if(this->checkIndexBounds(index)){
        
        //Write to the array
        this->items[index] = value; //writes the value into the item array
        
    }else if(index > this->size-1){
        //cout << "Array is out of bounds, need to resize." << endl;
        //Two Routes can be taken
        //1st -  Use helper function pushItem() to add to end of array
        //this->pushItem(value);  //For the record, this method was a better option.
        //2nd - Adjust the size, then set the item
        this->changeSize(this->size+1); //Increase the size by 1
        this->setItem(value,this->size-1); //Recursive Call, use "this->size-1" in the event that index is n+2 greater than the size of the original size of the array
    }else{
        //Item is not within the bounds of the array
        cerr << "Inserted item is not within the bounds of the array\n";//error statement when item is out of bounds
    }
}

//Gets an item in the array and checks to see if the index is within bounds
template <class Element>
Element SmcArray<Element>::getItem(int index){
    //Check to see if the index can be retrieved
    if(this->checkIndexBounds(index)){
        
        //Write to the array
        return this->items[index]; //writes the value into the item array
        
    }else{
        //Even though this will return the default value the user is prompted with a message indicating that a default value has been returned
        //cerr << __PRETTY_FUNCTION__ << "- WARNING: Returning Default Value\n ";//_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
        
        return this->defaultValue; //returns the default value
    }
}

//Gets an item in the array and checks to see if the index is within bounds
template <class Element>
Element SmcArray<Element>::getItem(int index) const{
    //Check to see if the index can be retrieved
    if(this->checkIndexBounds(index)){
        //Write to the array
        return this->items[index]; //writes the value into the item array
    }else{
        //Even though this will return the default value the user is prompted with a message indicating that a default value has been returned
        //cerr << __PRETTY_FUNCTION__ << "- WARNING: Returning Default Value\n ";//_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
        
        return this->defaultValue; //returns the default value
    }
}


//insert an item to the at the given index of the array
template <class Element>
void SmcArray<Element>::insertItem(Element value, int index){
    
    //extend the array by 1
    //update the size by adding 1 and inserts the value into the array
    
    //Checks that within bounds
    if (minSize <= index &&  index <= this->getSize() ){
        Element * newArray = new Element[this->getSize()+1];
        
        //Copy array that is increased by 1 at given index from the original array into the new array
        if (index < 0 || index >= this->getSize()+1)
            cout << "The index of the item to be removed is out of range." << endl;
        else{
            //sets the values in array before the inserted value
            for (int i = 0; i < index; i++) newArray[i] = items[i];
            
            //inserts the value after the given index
            newArray[index] = value;
            
            //sets the values in the array after the inserted value
            for (int i = index+1; i < this->size+1; i++) newArray[i] = items[i-1];
        }
        
        //Deallocate old memory
        delete [] this->items;
        
        //Copy to new pointer
        this->items = newArray;
        this->size = this->getSize()+1;
        
    }else{
        cerr << "My program is crashing\n"; //Error statement
        throw "array out of bounds exception";
    }
}

//Remove an item at a given index
template <class Element>
void SmcArray<Element>::removeItem(int index){
    //Remove 1 item from the array
    //Decrease the size of the array
    if (index < 0 || index >=size) cout << "The index of the item to be removed is out of range." << endl; //Error statement
    else{
        for (int i = index; i < this->size-1; i++) //starts the loop where the item is removed and goes to one less than original array size
            items[i] = items[i+1]; //sets the values after the item is deleted
        this->size = size-1; //reduces the size of the array by 1
    }
}

//Prints the array
template <class Element>
void SmcArray<Element>::printArray(bool linear) const{
    
    if(linear){
        for (int i=0; i < this->size; i++){
            cout << this->items[i] << " ";
        }
    }else{
        //Prints what is in my array
        //loop through an print each item
        for (int i=0; i < this->size; i++){
            cout << "Index is: " << i << " Array value is: " << this->items[i] << endl;
        }
    }
    cout << endl;
}

//Copies an array in an increased size array
template <class Element>
void SmcArray<Element>::copyArrayIncreasedSize(int s){
    //check to see if new size is within the minSize And MaxSize
    //check if the new size is greater than the existing size
    if ((s > this->size) && s < maxSize){
        Element * newArray = new Element[s];
        //Copy everything from the original array into the new array
        for (int i = 0; i < this->size; i++){
            newArray[i] = this->items[i];
        }
        
        //Deallocate old memory
        delete [] this->items;
        
        //Copy to new pointer
        this->items = newArray;
        this->size = s;
        
    }else{
        cerr << "My program is crashing\n"; //Error statement
        throw "Array out of bounds exception";
    }
}

//Checks if the index is within the bounds of the array
template <class Element>
bool SmcArray<Element>::checkIndexBounds(int index) const{
    if(index >= minSize && index < this->size){ //checks if the index is greater than or equal to the minimum size and less than size of the array
        return true; //if yes then return true
    }else{
        return false; //if no then return false
    }
}

//Sets a default value for out of bounds index expansions via changeSize
template <class Element>
void SmcArray<Element>::setDefault(Element value){
    this->defaultValue = value;
}

//Returns the default value
template <class Element>
Element SmcArray<Element>::getDefault(){
    return this->defaultValue;
}

//Changes the size of the array
template <class Element>
void SmcArray<Element>::changeSize(unsigned int newSize){
    //Check to make sure there is a default value
    //if(this->defaultValue == NULL){
    if (/* DISABLES CODE */ (false)) {
        cerr << __PRETTY_FUNCTION__ << " a default value has not been set\n";////_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
    }
    
    //First check to make sure the new size is within the bounds of the system
    if(newSize > minSize && newSize < maxSize){
        
        Element * newArray = new Element[newSize];
        //Copy array that is decreased by 1 at given index from the original array into the new array
        for (int i = 0; i < newSize; i++){
            //if expanding the array  (10 -> 15), check to see if the current position is going to be outside
            //of the index of the original items array. If it is use the default value
            if(i >= this->size){
                newArray[i] = defaultValue;
            }else{
                newArray[i] = this->items[i];
            }
        }
        
        //Deallocate old memory
        delete[] this->items;
        
        //Copy to new pointer
        this->items = newArray;
        this->size = newSize;
        
    }else{
        cerr << __PRETTY_FUNCTION__ << " Size changed to a illegal size\n"; //_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
    }
}

#endif /* defined(__SueC2L2__SmcArray__) */
