#include <iostream>
#include <fstream>
#include <sstream>	// for istringstream
#include <string>
#include <stack>
#include <cstdlib>	// for exit()

using namespace std;

int main()
{
  ifstream input{"chucknorris.txt"};//input prompt for the txt file
  if (!input) {  //if there is an error with the file
    cerr << "Error: Can't open chucknorris.txt for input.\n";
    exit(-1);
  }

  string line;
  getline(input, line);  // Get an entire line, excluding newline.
  while (!input.eof()) {
    istringstream ist{line};  // Convert a string to an I/O stream.
    string s;
    while (!ist.eof()) {
      ist >> s;               // >> stops reading at whitespace
                              // (it can break a sentence into words)
      std::stack<char> stk;
      // Put the characters of the word on the stack.
      for (int i = 0 ; i < s.length() ; ++i)
        stk.push(s[i]);
      // And they come off in reverse order.
      for (int i = 0 ; i < s.length() ; ++i) {
        cout << stk.top();
	stk.pop();
      }
      cout << ' ';  // Put back the space that >> skipped.
    }
    cout << '\n';  // Put back the newline that getline() skipped.
    getline(input, line);  // Read the next line.
  }
}
