#include <iostream>
#include <vector>
#include <array>
using namespace std;
 
//LIS = Longest Increasing Ssubsequence
void printLIS(vector<int>& arr)//utility function that prints LIS
{
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

void constructPrintLIS(int arr[], int n)//function that constructs and prints LIS
{
    
    vector<vector<int> > L(n);//L[i] - The longest increasing sub-sequence ends with arr[i]
 
    L[0].push_back(arr[0]);//L[0]=arr[0] 
    
    for (int i = 1; i < n; i++)//starting from index 1
    {
        // do for every j less than i
        for (int j = 0; j < i; j++)
        {
            /* L[i] = {Max(L[j])} + arr[i]
            where j < i and arr[j] < arr[i] */
            if ((arr[i] > arr[j]) &&
                    (L[i].size() < L[j].size() + 1))
                L[i] = L[j];
        }
 
        // L[i] ends with arr[i]
        L[i].push_back(arr[i]);
    }
 
    vector<int> max = L[0];// L[i] now stores increasing sub-sequence of arr[0..i] that ends with arr[i]
 
    // LIS will be max of all increasing sub-
    // sequences of arr
    for (vector<int> x : L)
        if (x.size() > max.size())
            max = x;
 
    // max will contain LIS
    printLIS(max);
}

int main()
{
    int arr[] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    // construct and print LIS of arr
    constructPrintLIS(arr, n);
 
    return 0;
}