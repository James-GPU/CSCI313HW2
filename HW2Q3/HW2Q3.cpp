#ifndef H_StackType 
#define H_StackType
#include <iostream> 
#include <cassert>
#include <chrono>
#include <stack>
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
using namespace std;
#include "stackADT.h"
#include "linkedADT.h"
#include "linkedListIterator.h"
//James Ng CSCI 313 Question 3
template <typename Func>
long long TimeFunc(Func f)//code from HW1
{
    auto begin = steady_clock::now();
    f();
    auto end = steady_clock::now();

    return duration_cast<milliseconds>(end - begin).count();
}
template <class Type>
class stackType : public stackADT<Type>
{//code from Blackboard
public:
    const stackType<Type>& operator=(const stackType<Type>&);
    //Overload the assignment operator.

    void initializeStack();
    //Function to initialize the stack to an empty state.
    //Postcondition: stackTop = 0

    bool isEmptyStack() const;
    //Function to determine whether the stack is empty.
    //Postcondition: Returns true if the stack is empty,
    //               otherwise returns false.

    bool isFullStack() const;
    //Function to determine whether the stack is full.
    //Postcondition: Returns true if the stack is full,
    //               otherwise returns false.

    void push(const Type& newItem);
    //Function to add newItem to the stack.
    //Precondition: The stack exists and is not full.
    //Postcondition: The stack is changed and newItem 
    //               is added to the top of the stack.

    Type top() const;
    //Function to return the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: If the stack is empty, the program 
    //               terminates; otherwise, the top element
    //               of the stack is returned.

    void pop();
    //Function to remove the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: The stack is changed and the top 
    //               element is removed from the stack.

    stackType(int stackSize = 100);
    //constructor
    //Create an array of the size stackSize to hold 
    //the stack elements. The default stack size is 100.
    //Postcondition: The variable list contains the base
    //               address of the array, stackTop = 0, and  
    //               maxStackSize = stackSize.

    stackType(const stackType<Type>& otherStack);
    //copy constructor

    ~stackType();
    //destructor
    //Remove all the elements from the stack.
    //Postcondition: The array (list) holding the stack 
    //               elements is deleted.

private:
    int maxStackSize; //variable to store the maximum stack size
    int stackTop;     //variable to point to the top of the stack
    Type* list;       //pointer to the array that holds the
                      //stack elements

    void copyStack(const stackType<Type>& otherStack);
    //Function to make a copy of otherStack.
    //Postcondition: A copy of otherStack is created and
    //               assigned to this stack.
};

template <class Type>
void stackType<Type>::initializeStack()
{
    stackTop = 0;
}//end initializeStack

template <class Type>
bool stackType<Type>::isEmptyStack() const
{
    return (stackTop == 0);
}//end isEmptyStack

template <class Type>
bool stackType<Type>::isFullStack() const
{
    return (stackTop == maxStackSize);
} //end isFullStack

template <class Type>
void stackType<Type>::push(const Type& newItem)
{
    if (!isFullStack())
    {
        list[stackTop] = newItem;   //add newItem to the 
                                    //top of the stack
        stackTop++; //increment stackTop
    }
    else
        cout << "Cannot add to a full stack." << endl;
}//end push

template <class Type>
Type stackType<Type>::top() const
{
    assert(stackTop != 0);      //if stack is empty, 
                                //terminate the program
    return list[stackTop - 1];  //return the element of the
                                //stack indicated by 
                                //stackTop - 1
}//end top

template <class Type>
void stackType<Type>::pop()
{
    if (!isEmptyStack())
        stackTop--;      //decrement stackTop 
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
stackType<Type>::stackType(int stackSize)
{
    if (stackSize <= 0)
    {
        cout << "Size of the array to hold the stack must "
            << "be positive." << endl;
        cout << "Creating an array of size 100." << endl;

        maxStackSize = 100;
    }
    else
        maxStackSize = stackSize;   //set the stack size to 
                                    //the value specified by
                                    //the parameter stackSize

    stackTop = 0;                   //set stackTop to 0
    list = new Type[maxStackSize];  //create the array to
                                    //hold the stack elements
}//end constructor

template <class Type>
stackType<Type>::~stackType() //destructor
{
    delete[] list; //deallocate the memory occupied 
                    //by the array
}//end destructor

template <class Type>
void stackType<Type>::copyStack
(const stackType<Type>& otherStack)
{
    delete[] list;
    maxStackSize = otherStack.maxStackSize;
    stackTop = otherStack.stackTop;

    list = new Type[maxStackSize];

    //copy otherStack into this stack
    for (int j = 0; j < stackTop; j++)
        list[j] = otherStack.list[j];
} //end copyStack


template <class Type>
stackType<Type>::stackType(const stackType<Type>& otherStack)
{
    list = nullptr;

    copyStack(otherStack);
}//end copy constructor

template <class Type>
const stackType<Type>& stackType<Type>::operator=
(const stackType<Type>& otherStack)
{
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);

    return *this;
} //end operator=         
//Linked List section
template <class Type>
class linkedStackType : public linkedADT<Type>
{
public:
    const linkedStackType<Type>& operator=(const linkedStackType<Type>&);

    bool isEmptyStack() const;


    bool isFullStack() const;


    void initializeStack();


    void push(const Type& newItem);


    Type top() const;


    void pop();


    linkedStackType();


    linkedStackType(const linkedStackType<Type>& otherStack);


    ~linkedStackType();

private:
    nodeType<Type>* stackTop; //pointer to the stack

    void copyStack(const linkedStackType<Type>& otherStack);

};

template <class Type>
linkedStackType<Type>::linkedStackType()
{
    stackTop = nullptr;
}

template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{
    return(stackTop == nullptr);
}

template <class Type>
bool linkedStackType<Type>::isFullStack() const
{
    return false;
}

template <class Type>
void linkedStackType<Type>::initializeStack()
{
    nodeType<Type>* temp;

    while (stackTop != nullptr)
    {
        temp = stackTop;

        stackTop = stackTop->link;

        delete temp;
    }
}

template <class Type>
void linkedStackType<Type>::push(const Type& newElement)
{
    nodeType<Type>* newNode;

    newNode = new nodeType<Type>;

    newNode->info = newElement;
    newNode->link = stackTop;
    stackTop = newNode;

} //end push


template <class Type>
Type linkedStackType<Type>::top() const
{
    assert(stackTop != nullptr);

    return stackTop->info;
}//end top

template <class Type>
void linkedStackType<Type>::pop()
{
    nodeType<Type>* temp;

    if (stackTop != nullptr)
    {
        temp = stackTop;

        stackTop = stackTop->link;

        delete temp;
    }
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
void linkedStackType<Type>::copyStack(const linkedStackType<Type>& otherStack)
{
    nodeType<Type>* newNode, * current, * last;

    if (stackTop != nullptr)
        initializeStack();

    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    else
    {
        current = otherStack.stackTop;


        stackTop = new nodeType<Type>;

        stackTop->info = current->info;
        stackTop->link = nullptr;

        last = stackTop;
        current = current->link;


        while (current != nullptr)
        {
            newNode = new nodeType<Type>;

            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }
}


template <class Type>
linkedStackType<Type>::linkedStackType(const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}


template <class Type>
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}

template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator=
(const linkedStackType<Type>& otherStack)
{
    if (this != &otherStack)
        copyStack(otherStack);

    return *this;
}
#endif
auto arrayOps(stackADT<int>& array) {//We perform operations in a stack
    int operation = 123456789;//A value that tests millions of operations
    cout << "Currently starting to perform " << operation << " operations based on array stack." << endl;
    auto start = chrono::high_resolution_clock::now();//Starts a timer
    for (int i = 0; i < operation; i++) {//We test the speed with millions of operations here
            array.push(i);//Adds current value to the stack
            array.top();//Returns reference value to the top element in the stack
            array.pop(); //Gets rid of current value to the stack
    }
    auto end = chrono::high_resolution_clock::now();//Ends the timer so we know the duration
    chrono::duration<float, milli> duration = end - start;//We subtract the end with the beginning points to see how long it lasts.
    cout << "The time it took for Array-based stack to compute " << operation <<" operations was " << duration.count() << " milliseconds." << endl;//Prints in milliseconds
    cout << endl;
    return duration;//Returns the time it took
}
auto linkedOps(linkedADT<int>& link) {//We perform operations in a stack
    int operation = 123456789;//A value that tests millions of operations
    cout << "Currently starting to perform " << operation << " operations based on linked list stack." << endl;
    auto start = chrono::high_resolution_clock::now();//Starts a timer
    for (int i = 0; i < operation; i++) {//We test the speed with millions of operations here
            link.push(i);//Adds current value to the stack
            link.top();//Returns reference value to the top element in the stack
            link.pop(); //Gets rid of current value to the stack
    }
    auto end = chrono::high_resolution_clock::now();//Ends the timer so we know the duration
    chrono::duration<float, milli> duration = end - start;//We subtract the end with the beginning points to see how long it lasts.
    cout << "The time it took for Linked List-based stack to compute " << operation <<" operations was " << duration.count() << " milliseconds." << endl;//Prints in milliseconds
    cout << endl;
    return duration;//Returns the time it took
}
int main() {
    stackType<int> arrayStack;
    auto arraytime = arrayOps(arrayStack);
    linkedStackType<int> linkedStack;
    auto linktime = linkedOps(linkedStack);//Had a tiny issue with override and virtual
    if (arraytime < linktime) {//Compares the times of Array and Linked List
        cout << "The Array Based Stack is faster than the Linked List Stack." << endl;//Prints if array if faster
    }
    if (linktime < arraytime) {
        cout << "The Linked List Stack is faster than the Array Based Stack." << endl;;//Prints if linked list is faster
    }
    if(arraytime == linktime) {
        cout << "The Array-Based Stack and the Linked List-based take the same amount of time." << endl;;//Prints if both times are the same
    }
    return 0;
}