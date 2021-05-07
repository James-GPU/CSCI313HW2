#include <iostream>
#include <vector>
using namespace std;
//James Ng CSCI 313 Question 9
void printNorth(int planes) {
    cout << endl;
    vector <int> northside;
    int roundNorth = ceil(planes * .1);//Roundes the number of planes up
    cout << "There are " << roundNorth << " planes travelling north" << endl;
    for (int i = 0; i < roundNorth; i++) {
        northside.push_back(i + 1);//Adds to the vector
        cout << "|" << northside.at(i) << "|" << endl;//This is the runway for north
    }
}
void printSouth(int planes) {
    vector <int> southside;
    int roundSouth = floor(planes * .7);//Rounds the number of planes down
    cout << "There are " << roundSouth << " planes travelling south" << endl;
    for (int i = 0; i < roundSouth; i++) {//70% of planes will only head into one direction which I designate as the south side
        southside.push_back(i + 1);//Cannot make i=1 unless there's an error
        cout << "|" << southside.at(i) << "| " << endl;//This is the runway for south 
    }
}
void printEast(int planes) {
    vector <int> eastside;
    int roundEast = floor(planes * .2);//Rounds the number of planes down
    cout << "There are " << roundEast << " planes travelling east" << endl;
    for (int e = 0; e < roundEast; e++) {
        cout << "--";
    }
    cout << endl;
    for (int e = 0; e < roundEast; e++) {//20% of planes will head in another direction
        eastside.push_back(e + 1);
        cout << eastside[e] << " "; //Prints the east planes
    }
    cout << endl;
    for (int e = 0; e < roundEast; e++) {
        cout << "--";
    }
    cout << endl;
}
void printWest(int planes) {
    vector <int> westside;
    int roundWest = floor(planes * .1);//Rounds the number of planes down
    cout << "There are " << roundWest << " planes travelling west" << endl;
    for (int w = 0; w < roundWest; w++) {
        cout << "---";
    }
    cout << endl;
    for (int w = 0; w < roundWest; w++) {//20% of planes will head in another direction
        westside.push_back(w + 1);
        cout <<" "<< westside[w] << " "; //Prints the west planes
    }
    cout << endl;
    for (int w = 0; w < roundWest; w++) {
        cout << "---";
    }
    cout << endl;//West section
}
void printRunway(int planes) {
    cout << "Entire Runway:" << endl;
    vector <int> westside;
    int roundWest = floor(planes * .1);//Rounds the number of planes down
    cout << "      ";//This prevents the runways intersecting and potentially crashing into each other
    for (int w = 0; w < roundWest + 8; w++) {//+ 8 is to make the runway look more complete
        cout << "--";//Prints top of the runway
    }
    cout << endl;//West Section
    cout << "      ";//This prevents the runways intersecting and potentially crashing into each other
    for (int w = 0; w < roundWest; w++) {//20% of planes will head in another direction
        westside.push_back(w + 1);//Stores west vector with the number of planes
        cout << "" << westside[w] << " "; //Prints the east planes
    }
    cout << " <--W"<< endl;//Marks West
    cout << "      ";//This prevents the runways intersecting and potentially crashing into each other
    for (int w = 0; w < roundWest + 8; w++) {//+ 8 is to make the runway look more complete
        cout << "--";//Prints the bottom of the runway
    }
    cout << endl;//West section
    vector <int> southside;
    int roundSouth = floor(planes * .7);//Rounds the number of planes down
    for (int i = 0; i < roundSouth; i++) {//70% of planes will only head into one direction which I designate as the south side
        southside.push_back(i + 1);//Cannot make i 1 unless there's an error
        cout << "|" << southside.at(i) << "|                            | |" << endl;
    }
    cout << "|" << "S " << "|                            |^|" << endl;
    cout << "|" << "| " << "|" <<"                            |||" <<endl;
    cout << "|" << "| " << "|" <<"                            |||" <<endl;
    cout << "|" << "V " << "|" <<"                            |N|" <<endl;
    //South Section
    vector <int> eastside;
    int roundEast = floor(planes * .2);//Rounds the number of planes left
    cout << "      ";//This prevents the runways intersecting and potentially crashing into each other
    for (int e = 0; e < roundEast + 8; e++) {//+ 8 is to make the runway look more complete
        cout << "--";
    }
    cout <<endl;
    cout << "      ";//This prevents the runways intersecting and potentially crashing into each other
    for (int e = 0; e < roundEast; e++) {//10% of planes will head in another direction
        eastside.push_back(e + 1);
        cout << "" << eastside[e] << " "; //Prints the east planes
    }
    cout << "E -->";//Marks East
    cout <<  endl;
    cout << "      ";//This prevents the runways intersecting and potentially crashing into each other
    for (int e = 0; e < roundEast + 8; e++) {//+ 8 is to make the runway look more complete
        cout << "--";
    }
    cout << endl;//East section
}
int main() {
    int planes = 0;
    cout << "How many planes are there?" << endl;//Prompts user to submit a number of planes
    cin >> planes;
    while (planes < 0) {//Checks if the input is negative, loops if it is negative
        cout << "Please put in a positive number."<< endl;
        cin >> planes;
    }
    printSouth(planes);//Prints South
    printWest(planes);//Prints West
    printEast(planes);//Prints East
    printRunway(planes);//Prints all runways at once
    return 0;
}

