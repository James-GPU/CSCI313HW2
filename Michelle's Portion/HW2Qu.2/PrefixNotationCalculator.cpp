#include <iostream>
#include <stack>
#include <string>
#include <cctype>   // for isspace(), isdigit()
#include <cmath>    // for pow()
#include <cstdlib>  // for exit()

using namespace std;

// Polish Notation (prefix expression) evaluator.
// Only good for single digit numbers.
// No error checking.

int main()
{
  stack<double> calc_stack;//initiates the stack for the calculator
  double result;

  cout << "Enter a prefix expression: ";//ask the user for input
  string expression;//accept input from the user
  getline(cin, expression);
  for (int i = expression.length() - 1 ; i >= 0 ; --i) {
    char c = expression[i]; //goes through the user input
    if (isspace(c)) continue;  // skips rest of code and returns
                               // to top of loop.

    if (isdigit(c)) {
      calc_stack.push(c - '0'); //pushes any digit encountered on the stack
    } else {
      // In PN, operands pop in given order.
      double op1 = calc_stack.top();
      calc_stack.pop();
      double op2 = calc_stack.top();
      calc_stack.pop();
      switch (c) { //switch the value with the cases coded below
      case '+':
        result = op1 + op2;//in the case that there is a plus sign, instead add them
	calc_stack.push(result);//then push the result on the stack
	break;
      case '-':
        result = op1 - op2;//in the case that there is a minus sign, instead subtract op1 % op2
	calc_stack.push(result);//then push the result on the stack
	break;
      case '*':
        result = op1 * op2;//in the case that there is a multiplication sign, instead multiply op1 & op2
	calc_stack.push(result);//then push the result on the stack
	break;
      case '/':
        result = op1 / op2;//in the case that there is a division sign, divide op1 & op2
	calc_stack.push(result);//then push the result on the stack.
	break;
      case '^'://in the case that the exponent symbol is given, raise op2 to op1. 
        result = pow(op1, op2);//using the pow function
	calc_stack.push(result);//then push the result on the stack.
	break;
      default:
        cout << "I don't understand " << c << '\n';//accounts for the case the user inputs something strange 
	exit(-1);//so then the program will terminate. 
      }
    }
  }

  // Result should be on stack.
  cout << "Result: " << calc_stack.top() << '\n';
  calc_stack.pop();
  // Something went wrong if stack is not empty.
  if (!calc_stack.empty())
    cerr << "Stack not empty.\n";
}

