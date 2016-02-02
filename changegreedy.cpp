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
 ** Function: changegreedy
 ** Description: Making change with a greedy algorithm.
 ** Parameters: Input: vector v, containing values of the coins and int amount, the amount of change we are asked to make.
 **     Output: vector containing the number of coins of each value and int minimum, the number of coins
 ***************************************************************************************/
struct change changegreedy(vector<int> v, int amount){
    struct change myChange;

    // Initialize myChange.minimum and myChange.coins to zero.
    myChange.minimum = 0;
    for(int i = 0; i < (int) v.size(); i++)
        myChange.coins.push_back(0);

    /* Starting with largest coin value, repeated subtract this value from amount so long
       as it remains positive. Repeat for each coin value moving from largest to
       smallest. When a coin is subtracted, increase the minimum count and corresponding
       entry in the myChange.coin vector.
    */
    for(int i = v.size() - 1; i >= 0; i--){
        while (amount >= v[i]){
            amount -= v[i];
            myChange.coins[i]++;
            myChange.minimum++;
        }
    }
    return myChange;
};

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
        myChange = changegreedy(denominations,amount);

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
