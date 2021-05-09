//Header File: linkedStack.h 

#ifndef H_StackType
#define H_StackType

#include <iostream>
#include <cassert> 

#include "stackADT.h"

using namespace std;

//we will define the the node here.
template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type>* link;
};

template <class Type>
class linkedStackType : public stackADT<Type>
{
public:
    const linkedStackType<Type>& operator=
        (const linkedStackType<Type>&);
    //this will overload the assignment operator

    bool isEmptyStack() const;
    //this function will tell us if the stack has anything in it
    //if the stack has nothing, it will return true. in all other cases, it will return false
    bool isFullStack() const;
    //this function determines if there is no more space in the stack. 
    //in all other cases this will be false
    void initializeStack();
    //this function will initialise an empty stack
    //The stack elements are removed and stackTop is set to null
    void push(const Type& newItem);
    //this function will add a new item to the stack.
    //for the parametres: there has to be a pre-existing stack that isn't full.
    //After the function, newItem is added to the top of the stack so stack is fundamentally changed.

    Type top() const;
    //this function returns what the top element of the stack is
    //For this function to run, there must be a pre-existing nonempty stack.
    void pop();
    //this function removes the top element of the stack.
    //For this function to run, there must be a pre-existing nonempty stack.
    //The top element is taken down from the stack and the stack is fundamentally changed
    linkedStackType();
    //this is the default constructor
    //stackTop will equal nullptr;

    linkedStackType(const linkedStackType<Type>& otherStack);
    //this is the copy constructor

    ~linkedStackType();//destructor
    //All elements of the stack are taken out of the stack 

private:
    nodeType<Type>* stackTop; //pointer to the stack

    void copyStack(const linkedStackType<Type>& otherStack);
    //this function will replicate otherStack.
    //so then a copy of otherStack is created and assigned to this stack. 
};


//this is the default constructor
template <class Type>
linkedStackType<Type>::linkedStackType()
{
    stackTop = nullptr;
}

template <class Type>

bool linkedStackType<Type>::isEmptyStack() const
{
    return(stackTop == nullptr); //checks if the value of stackTop is null.
} //this ends isEmptyStack

template <class Type>
bool linkedStackType<Type>::isFullStack() const //this calls the aforementioned isFullStack function
{
    return false;  //this returns false ??
}//this ends isFullStack

template <class Type>
void linkedStackType<Type>::initializeStack()
{
    nodeType<Type>* temp; //this ptr will delete the node

    while (stackTop != nullptr) //while there are elements in the stack left
    {
        temp = stackTop; //set temp to point to the current node

        stackTop = stackTop->link; //move stackTop to the next node which essentially destroys the stack.

        delete temp; //free up the memory that is occupied by temp
    }
} //end initializeStack function

template <class Type>
void linkedStackType<Type>::push(const Type& newElement)
{
    nodeType<Type>* newNode; //this pointer creates a new node

    newNode = new nodeType<Type>; //make a new node 
    
    newNode->info = newElement; //put newElement in newNode
    //the new node is gonna be stackTop because that is where it should be pointing to
    newNode->link = stackTop; //insert newNode before stackTop
    
    stackTop = newNode; //stackTop will now point to the top node

} //end push function


template <class Type>
Type linkedStackType<Type>::top() const
{
    assert(stackTop != nullptr);//if stackTop is empty, end the program.

    return stackTop->info; //return the first element of the stack
}//end top

template <class Type>
void linkedStackType<Type>::pop()
{
    nodeType<Type>* temp;  //this pointer will freeup the memory from temp

    if (stackTop != nullptr) //if the first element isnt null...
    {
        temp = stackTop; //set the temp variable to point to the top node

        stackTop = stackTop->link; //move stackTop to the next node

        delete temp; //delete the temporary variable
    }
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
void linkedStackType<Type>::copyStack
(const linkedStackType<Type>& otherStack)
{
    nodeType<Type>* newNode, * current, * last;

    if (stackTop != nullptr) //if the stack still has elements in it, 
        initializeStack();//calling this function will empty it.

    if (otherStack.stackTop == nullptr) //if the first element of the other stack is null, then their stackTop has a value of nullptr.
        stackTop = nullptr;
    else
    {
        current = otherStack.stackTop; //set the current variable to point to the stack 
        //so it can be copied over. 

        //this will copy the stackTop element of the stack
        stackTop = new nodeType<Type>; //creates a new node 

        stackTop->info = current->info;//copy the info
        stackTop->link = nullptr; //set the link part of the node to null

        last = stackTop;  //set the last variable to point to stackTop
        current = current->link; //set the current variable to point to the next node in the list

        //copy over whatever is left of the stack
        while (current != nullptr)//while the current variable isn't null. 
        {
            newNode = new nodeType<Type>;

            newNode->info = current->info; //both newNode and current are set to the value of info
            newNode->link = nullptr;//
            last->link = newNode;
            last = newNode;
            current = current->link;
        }//end the while loop
    }//end else statement
}//end copystack

//this is the copy constructor
template <class Type>
linkedStackType<Type>::linkedStackType(
    const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}//end copy constructor

//destructor
template <class Type>
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}//ends the destructor

//here we overload the assignment operator
template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator=
(const linkedStackType<Type>& otherStack)
{
    if (this != &otherStack)//this is done to avoid a mirror copy
        copyStack(otherStack);

    return *this;
}//end operator=

#endif
