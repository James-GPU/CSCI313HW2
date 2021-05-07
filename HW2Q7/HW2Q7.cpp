#include <iostream> 
#include <stack>
using namespace std;
//James Ng CSCI 313 Question 7
struct Position {
    int row ,col;
    Position() {//Default constructor
        row = 0;//Current starting place on row
        col = 6;//Current starting place on column
    }
};
void print(char maze[][11]) {
    for (int i = 0; i < 10; i++) {//Prints row
        for (int j = 0; j < 11; j++) {//Prints column
            cout << maze[i][j];//Prints the maze line
        }
        cout << endl;//Makes sure the maze is properly spaced
    }
    cout << endl;//Makes sure the maze is separated from the other printed maze
}

int main() {
    cout << "This is the base maze: ";
    cout << "'S' is the starting point, 'E' is the endpoint." << endl;
    char maze[10][11] =
    {
     "------S---",
     "-    - - -",
     "- --   - -",
     "-    -- -",
     "- -   -  -",
     "-  ----- -",
     "-        -",
     "- --  -- -",
     "-   -   --",
     "-------E--"
    };
    print(maze);//Prints base maze
    stack<Position> placement;//Creates a variable that we can access the stack from
    Position current;//Accesses the current position on the stack
    bool exit = true;//Declares for the while loop
    while (exit == true) {//Continues throughout the maze until our maze is solved
        if (maze[current.row - 1][current.col] == ' ') {//Checks if current position can go up, Cannot use " " because it is a char array, not a string
            placement.push(current);//Adds current placement to the stack
            maze[current.row][current.col] = char(173);
            current.row--; //Subtracts row to move up;
            continue;
        }
        if (maze[current.row][current.col + 1] == ' ') {//Checks if current position can go right
            placement.push(current);//Adds current placement to the stack
            maze[current.row][current.col] = char(173);//Prints current placement with a marker
            current.col++; //Adds the column to move right;
            continue;
        }
        if (maze[current.row + 1][current.col] == ' ') {//Checks if current position can go down
            placement.push(current);//Adds current placement to the stack
            maze[current.row][current.col] = char(173);
            current.row++; //Adds the row to move down;
            continue;
        }
        if (maze[current.row][current.col - 1] == ' ') {//Checks if current position can go left
            placement.push(current);//Adds current placement to the stack
            maze[current.row][current.col] = char(173);//Prints current placement with a marker
            current.col--; //Subtracts the column to move left;
            continue;
        }
        if (maze[current.row + 1][current.col] == 'E') {//Designated our maze exit
            cout << "Final Outcome: ";//Prints out the final outcome
            cout << "'B' means backtrack and '" << char(173) << "' means progression" << endl;
            maze[current.row][current.col] = char(173);//Prints the current position with an upside exclaimation point
            maze[current.row + 1][current.col] = char(173);//Makes sure that E gets replaced
            print(maze);//Prints maze
            return 0;//Ends program, this has to be before checking if the space is empty otherwise it will keep going on a loop
        }
        if (!placement.empty()) {//If placement is full, it'll mark its current placement to indicate backtracking
            maze[current.row][current.col] = 'B';//B for backtracking
            current = placement.top();//Removes the element on top of the stack for backtracking
            placement.pop();//Removes the current placement from the stack
            continue;
        }
    }
    return 0;
}