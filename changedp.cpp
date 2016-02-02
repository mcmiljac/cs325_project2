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
 ** Function: changedp
 ** Description:
 ** Parameters:
 ***************************************************************************************/
struct change changedp(vector<int> v, int amount){
    struct change myChange;
    int length = v.size();
    int table[amount+1][length+1];
    int tempMin, tempRow, tempCol;

    // Fill in first row of table with 0 entries
    for (int j = 0; j <= length; j++)
        table[0][j] = 0;

    // Fill in table rows 1 through amount
    for (int i = 1; i <= amount; i++){
        tempMin = INT_MAX;
        for (int j=1; j <= length; j++){
            if (v[j-1] <= i && table[i - v[j-1]][0] != -1 && table[i - v[j-1]][0] + 1 < tempMin){
                tempMin = table[i - v[j-1]][0] + 1;
                tempRow = i - v[j-1];
                tempCol = j;
            }
        }
		// If tempMin has been changed, fill in row values by copying the row that was
		// referenced and incrementing the appropriate value by 1.
        if(tempMin < INT_MAX){
            table[i][0] = tempMin;
            for (int j=1; j<= length; j++)
                table[i][j] = table[tempRow][j];
            table[i][tempCol]++;
        }
        // otherwise, fill the rest of the row with zeros
		else {
            table[i][0] = -1;
            for (int j=1; j<= length; j++)
                table[i][j] = 0;
        }
    }

	// Copy file row from table into myChange struct and return
    for (int j = 1; j <= length; j++)
        myChange.coins.push_back(table[amount][j]);
    myChange.minimum = table[amount][0];
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
        myChange = changedp(denominations,amount);

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
