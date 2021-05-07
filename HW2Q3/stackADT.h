#pragma once
template<class Type>
class stackADT {//Created a header file for stackADT
public:
    void initializeStack();//Since an ADT is a class that has a defined set of values, we provide base values
    virtual void push(const Type& newItem) = 0;// So we provide 0 as the base standard as we provide any function that requires a value
    virtual Type top() const = 0;//All of these are const 0 so that it'll run
    virtual void pop() = 0;//We make all stack operations 0
};