// CS 325 - Project 2: Coin Change
// Group 30
// Courtney Bonn, Jana Gallina, Jacob McMillen

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <sstream>
#include <fstream>
using std::ifstream;
using std::ofstream;

#include<string>
using std::string;

#include<vector>
using std::vector;

struct change{
    vector<int> coins;
    int minimum;
};

/***************************************************************************************
 ** Function:
 ** Description:
 ** Parameters:
 ***************************************************************************************/
struct change changedp(vector<int> v, int amount){
    struct change myChange;
    int size = v.size();
    for(int i = 0; i < size; i++)
        myChange.coins.push_back(0);

    vector<int> table;
    table.push_back(0);

    int temp,j;

    //Fill in the table from index 0 to amount
    for (int i = 1; i <= amount; i++){
        //compute entry i of table
        temp = table[i - v[0]] + 1;
        j = 1;
        while (v[j]<= i && j < size){
            if (table[i - v[j] + 1] < temp)
                temp = table[i - v[j]] + 1;
            j++;
        }
        table.push_back(temp);
    }
    for(int k = 0; k <= amount; k++){
        cout << "Table " << k << ": " << table[k] << endl;
    }
    myChange.minimum = table[amount];
    return myChange;
};

/***************************************************************************************
 ** Function: main
 ** Description: driver function to call algorithms on input
 ** Parameters:
 ***************************************************************************************/
int main(){
    struct change myChange;
    vector<int> denominations;
    denominations.push_back(1);
    denominations.push_back(3);
    denominations.push_back(5);
    myChange = changedp(denominations,10);
    cout << "Minumum: " << myChange.minimum << endl;
    cout << myChange.coins[0] << "," << myChange.coins[1] << "," << myChange.coins[2];
    return 0;
}
