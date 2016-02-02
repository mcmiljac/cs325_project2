// CS 325 - Project 2: Coin Change
// Group 30
// Courtney Bonn, Jana Gallina, Jacob McMillen

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <climits>
#include <sstream>
#include <fstream>
using std::ifstream;
using std::ofstream;

#include<string>
using std::string;

#include<vector>
using std::vector;

#include<algorithm>
using std::min;

struct change{
    vector<int> coins;
    int minimum;
};

/***************************************************************************************
 ** Function: changeslow
 ** Description:
 ** Parameters:
 ***************************************************************************************/
struct change changeslow(vector<int> v, int amount){
    struct change myChange, tempChange1, tempChange2;
    int length = v.size();
    int tempMin;

    // Initialize myChange.minimum and myChange.coins.
    myChange.minimum = INT_MAX;
    for(int i = 0; i < (int) v.size(); i++)
        myChange.coins.push_back(0);

    /* Check if any single coin value exactly equals the amount. If so, return min of 1.
       Could do this with bin search since v is sorted to make slightly more efficient.
    */
    for (int i = 0; i < length; i++){
        if (v[i] == amount){
            myChange.minimum = 1;
            myChange.coins[i]++;
            return myChange;
        }
    }

    /* If no single coin equals amount, recursively call changeslow on each possible pair
       i and amount - i and determine their sum. Take the value i that minimizes the sum
       and return value with corresponding coin vector.
    */
    for (int i = 1; i <= amount/2; i++){
        tempChange1 = changeslow(v,i);
        tempChange2 = changeslow(v,amount-i);
        tempMin = tempChange1.minimum + tempChange2.minimum;
        if(tempMin < myChange.minimum){
            myChange.minimum = tempMin;
            for(int j = 0; j < length; j++)
                myChange.coins[j] = tempChange1.coins[j] + tempChange2.coins[j];
        }
    }
    return myChange;
}

/***************************************************************************************
 ** Function: main
 ** Description: driver function to call algorithms on input
 ** Parameters:
 ***************************************************************************************/
int main(int argc, char *args[]){
    string fileName, baseName, outputFile, inputStr;
    struct change myChange;
    vector<int> denominations;
    int value,amount;

    if (argc > 1){
        fileName = args[1];
    }
    else{
        cout << "Please enter a string." << endl << endl;
        return 1;
    }

    baseName = fileName.substr(0, fileName.find_last_of("."));
    outputFile = baseName + "change.txt";

    ifstream inFile;
    inFile.open(fileName.c_str());

    //Validates that input file can be opened.
    if (!inFile.is_open())
    {
        cout << "Error: Could not open file." << endl << endl;
        return 1;
    }

    ofstream outFile;
    outFile.open(outputFile.c_str());

    // Read file line-by-line.
    while (std::getline(inFile, inputStr))
    {
        // Place integers into vector, ignoring commas, until closing brace is reached.
        std::istringstream iss(inputStr);
        iss.ignore();
        while (iss >> value){
            denominations.push_back(value);
            if (iss.peek() == ',')
                iss.ignore();
            else if (iss.peek() == ']')
                break;
        }

        if(denominations.size()==0){
            cout << "Error: Incorrectly formatted input file." << endl << endl;
            break;
        }

        std::getline(inFile, inputStr);
        std::istringstream iss2(inputStr);
        iss2 >> amount;

        // Output the maximum sum subarray and display its sum.
        myChange = changeslow(denominations,amount);

        // Output the starting array.
        outFile << "[";
        for (int i = 0; i < (int) myChange.coins.size() - 1; i++)
            outFile << myChange.coins[i] << ",";
        outFile << myChange.coins[myChange.coins.size() - 1] << "]" << endl;
        outFile << myChange.minimum << endl;
        //Clear vector and sum for computations on next array in input file.
        denominations.clear();
    }
    inFile.close();
    outFile.close();
    return 0;
}
