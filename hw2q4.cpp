#include <iostream>
#include <stack>
#include <ctime>
#include <iterator>
using namespace std;


void PrintStack(stack<int> myStack){//function that prints out elements of stack
    if (myStack.empty())
        return;
    int x=myStack.top();

    myStack.pop();

    PrintStack(myStack);
    cout << x << " " ;
    myStack.push(x);
}
int main (){
    stack<int> myStack, tempStack;
    int target_index=2;
    int current_index=0;
    

    srand(time(0));
    for (int i=0;i<5;i++){//filling my stack with five 1 digit random numbers
        myStack.push(rand()%10 +1 );
    }
    cout << "These are the elements in my stack: ";//this is what my stack looks like now
    PrintStack(myStack);
    cout << endl;

    while(current_index!=target_index){//while loops to transfer our unwanted position to temporary stack
        int k=myStack.top();
        myStack.pop();
        tempStack.push(k);
        current_index++;
    }
    //change our current top value to 69
    myStack.pop();
    myStack.push(69);

    while(!tempStack.empty()){//while loop totransfereverything back into myStack
        int k=tempStack.top();
        tempStack.pop();
        myStack.push(k);
    }

    cout << "These are the new elements in my stack: ";//this is what my stack looks like after changing the last value
    PrintStack(myStack);



    return 0;
}