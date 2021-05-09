//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************
  
#include <iostream>  
#include <iomanip>
#include <fstream> //necessary to operate on external files in c++
#include "mystack.h"
 
using namespace std; 

/*The functions are declared before main to avoid errors. 
Explanations of the functions to come later.*/
void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);

void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    //variable declarations used for parameters later 
    bool expressionOk;
    char ch;
    //declaration of stack used for calculator
    stackType<double> stack(100);
    //declaration of special variables for reading from external variables
    ifstream infile;
    ofstream outfile;
    //opens the file with the expressions
    infile.open("RpnData.txt");
    
    //if the file format is incorrect or there is something wrong with it, an error msg will show
    if (!infile)
    {
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }
    //this allows reading from the output file 
    outfile.open("RpnOutput.txt");
    //this sets the specifications for the outfile
    outfile << fixed << showpoint;
    outfile << setprecision(2); 

    infile >> ch;
    //while there is still more to be read in the infile...
    while (infile)
    {
        //you initialise the stack you declared
        stack.initializeStack();
        //you say the value of the expression in question is valid
        expressionOk = true;
        outfile << ch;
 
        //the evaluate expression is called so the expression can be evaluated
        evaluateExpression(infile, outfile, stack, ch, 
                           expressionOk);
        printResult(outfile, stack, expressionOk);
        infile >> ch; //begin processing the next expression
    } //end while 

    infile.close();
    outfile.close();

    return 0;

} //end main

/*This function will read the postfix expressions given to the program. 
It is the "first gate" of the program*/
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;
    //while the char value isn't =
    while (ch != '=')
    {
        //prepare a switch
        switch (ch)
        {
        case '#'://in the case that one of the chars is: #
            inpF >> num;
            outF << num << " ";//both the inpF and outF are set to num
            if (!stack.isFullStack())//if the stack isn't full, push the value of num to be the first element of the stack
                stack.push(num);
            else
            {
                //it is full and can not be added so an error message is shown. 
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break;
        default: 
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch

        if (isExpOk) //if no error
        {
            inpF >> ch;
            outF << ch;

            if (ch != '#')
                outF << " ";
        }
        else
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression

//This function deals with all the other symbols 
void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2;

    if (stack.isEmptyStack())//if the stack doesn't have enough chars, an error msg is thrown and 
    //the value of isExpOk is changed to false.
    {
        out << " (Not enough operands)";
        isExpOk = false;
    }
    else
    {
        //else save the top element of the stack in op2 and then proceed to purge the value
        op2 = stack.top();
        stack.pop();
        //check again if the stack is empty and throw an error msg if it is.
        if (stack.isEmptyStack())
        {
            out << " (Not enough operands)";
            isExpOk = false;
        } 
        else
        { //save the first element of the stack as op1 and then proceed to remove it. 
            op1 = stack.top();
            stack.pop();
            //Now that you have your first two operands, prepare a switch so u can analyse the terms.
            switch (ch)
            {
            //in the case the sign is add, replace symbol with sum
            case '+': 
                stack.push(op1 + op2);
                break;
            //in the case the sign is subtraction, replace symbol with the difference
            case '-': 
                stack.push(op1 - op2);
                break;
            //in the case the sign is multiplication, replace symbol with product
            case '*': 
                stack.push(op1 * op2);
                break;
            //in the case the sign is division, replace symbol with quotient if op2 isnt 0.
            case '/': 
                if (op2 != 0)
                    stack.push(op1 / op2);
            //in the case it is 0, isExpOk is changed to false. 
                else
                {
                    out << " (Division by 0)";
                    isExpOk = false;
                }
                break;
            //in the other cases, it is an illegal operator and isExpOk is made false.
            default:  
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr

//this function gets rid of bogus entries while the char value isnt '=' by calling the out case
void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp

//this is the function to print the result
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack()) //if the stack isn't empty 
        {
            result = stack.top();// result is set to the 1st element of the stack
            stack.pop();//the first element is then expunged. 

            if (stack.isEmptyStack())
                outF << result << endl; //if the stack is empty, outF and then the result is displayed
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} //end printResult. The four above print statements are to address possible exceptions. 
