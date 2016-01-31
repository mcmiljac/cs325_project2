// CS 325 - Project 2: Coin Change
// Group 30
// Courtney Bonn, Jana Gallina, Jacob McMillen

#include <iostream>
#include <climits>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std; 

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
   struct change myChange;
   int length = v.size();
   int *tempArr = new int[amount + 1];
   int tempMin = 0, i, j, k;

   tempArr[0] = 0;
   for (i = 1; i <= amount; i++) {
	tempMin = INT_MAX;
	if (v[i] == amount) {
		tempArr[i] = 1;
		tempMin = 1;
        }
	for (j = 0; j < length; j++) {
		if (v[j] <= i) {
			tempMin = min(tempMin, tempArr[i-v[j]]);
		}
	}
	if (tempMin < INT_MAX) {
		tempArr[i] = tempMin + 1;
	} else {
		tempArr[i] = INT_MAX;
	}
   }

    tempMin = tempArr[amount];
    for (k = 1; k <= length; k++){
        myChange.coins.push_back(tempArr[k]);
   }
    myChange.minimum = tempMin;
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
    while (getline(inFile, inputStr))
    {
        // Place integers into vector, ignoring commas, until closing brace is reached.
        istringstream iss(inputStr);
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

        getline(inFile, inputStr);
        istringstream iss2(inputStr);
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
