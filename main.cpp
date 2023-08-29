
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
 
void showPuzzle();
 
using namespace std;
 
vector<int> sudokuRow = {};
 
string selectedRow;
string cleanRow;
bool valid = true;
bool puzzleValidity = true;
 
int objectNum;
string currentObj;
int increment = 0;
 
 
/*
int puzzle[][9] =
    {
    { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
    { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
    { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
    { 2, 3, 4, 5, 6, 7, 8, 9, 1 },
    { 5, 6, 7, 8, 9, 1, 2, 3, 4 },
    { 8, 9, 1, 2, 3, 4, 5, 6, 7 },
    { 3, 4, 5, 6, 7, 8, 9, 1, 2 },
    { 6, 7, 8, 9, 1, 2, 3, 4, 5 },
    { 9, 1, 2, 3, 4, 5, 6, 7, 8 }
    };
*/
 
int puzzle[][9] =
{
{ 1, 2, 3, 4, 5, 6, 7, 8, 9,},
{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
{ 7, 8, 9, 1, 2, 3, 4, 5, 6 },
{ 2, 1, 4, 3, 6, 5, 8, 9, 7 },
{ 3, 6, 5, 8, 9, 7, 2, 1, 4 },
{ 8, 9, 7, 2, 1, 4, 3, 6, 5 },
{ 5, 3, 1, 6, 4, 2, 9, 7, 8 },
{ 6, 4, 2, 9, 7, 8, 5, 3, 1 },
{ 9, 7, 8, 5, 3, 1, 6, 4, 2,}
};
 

void lastCheck(bool validity)
{
    if (puzzleValidity)
    {
        cout << "RESULT: The Sudoku Puzzle is VALID! No errors were found in the puzzle." << endl;
        cout << "-----------------------------------" << endl;
    }
    else
    {
        cout << "RESULT: The Sudoku Puzzle is INVALID! Errors were detected in the puzzle." << endl;
        cout << "-----------------------------------" << endl;
    }
}

void changeRow(int number)
{
    for (int i = 0; i < 9; i++)
    {
        sudokuRow.push_back(puzzle[number][i]);
    }
 
    stringstream vectorString;
    for (size_t i = 0; i < sudokuRow.size(); ++i)
    {
        if (i != 0)
            vectorString << ",";
        vectorString << sudokuRow[i];
    }
    selectedRow = vectorString.str();
}

void changeColumn(int number)
{
    for (int i = 0; i < 9; i++)
    {
        sudokuRow.push_back(puzzle[i][number]);
    }
 
    stringstream vectorString;
    for (size_t i = 0; i < sudokuRow.size(); ++i)
    {
        if (i != 0)
            vectorString << ",";
        vectorString << sudokuRow[i];
    }
    selectedRow = vectorString.str();
}

void changeBox(int number)
{
    for (int v = 0; v < 3; v++)
    {
        for (int i = 0; i < 3; i++)
        {
            sudokuRow.push_back(puzzle[(number + v)][i + increment]);
        }
    }
    stringstream vectorString;
    for (size_t i = 0; i < sudokuRow.size(); ++i)
    {
        if (i != 0)
            vectorString << ",";
        vectorString << sudokuRow[i];
    }
    selectedRow = vectorString.str();
}

void deleteChars(string bit)
{
    string::iterator spa_pos = remove(bit.begin(), bit.end(), ' ');
      bit.erase(spa_pos, bit.end());
  
    string::iterator com_pos = remove(bit.begin(), bit.end(), ',');
      bit.erase(com_pos, bit.end());
  
    cleanRow = bit;
}

void NumsCount(string clean)
{
    valid = true;
    cout << "-----------------------------------" << endl;
    cout << currentObj << " " << objectNum << ":" << endl;
    cout << "-----------------------------------" << endl;
    int flag;
    for (int x = 1; x <= 9; x++)
    {
        flag = 0;
        char aChar = '0' + x;
        for (int i = 0; i < clean.size(); i++)
        {
            if (clean[i] == aChar) flag++;
        }
        if (flag > 1) {
            cout << "Problem: " << currentObj << " contains more than one digits of the number \"" << x << "\".\n";
            valid = false;
        }
        else if (flag < 1)
        {
            cout << "Problem: " << currentObj << " contains fewer than one digits of the number \"" << x << "\".\n";
            valid = false;
        }
    }
    flag = 0;
}

void checkRow()
{
    deleteChars(selectedRow);
    if (cleanRow.length() > 9)
    {
        if (sudokuRow.size() > 9)
        {
            cout << "Error: Row contains too many digits to fit in the puzzle." << endl;
            cout << "-----------------------------------" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            cout << "Error: Row contains digit(s) with values less than one and/or higher than nine." << endl;
            cout << "-----------------------------------" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (cleanRow.length() < 9)
    {
        cout << "Error: Row contains fewer digits than are required to complete the puzzle." << endl;
        cout << "-----------------------------------" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        NumsCount(cleanRow);
    }
    if (valid)
    {
        cout << "RESULT: Success! " << currentObj << " " << objectNum << " [" << selectedRow << "] is valid!" << endl;
        cout << "-----------------------------------" << endl;
        selectedRow.clear();
        cleanRow.clear();
        sudokuRow.clear();
    }
    else
    {
        cout << "RESULT: Failure! " << currentObj << " " << objectNum << " [" << selectedRow << "] is not valid!" << endl;
        cout << "-----------------------------------" << endl;
        puzzleValidity = false;
        selectedRow.clear();
        cleanRow.clear();
        sudokuRow.clear();
    }
}

int main()
{
    cout << endl;
    cout << "----------------------------------"<<endl;
    cout << "|        SUDOKU PUZZLE           |" <<endl;
    cout << "----------------------------------"<<endl;
    showPuzzle();
    cout << endl << endl;
 
    cout << "----------------------------------"<<endl;
    cout <<"|     VALIDATING THE PUZZLE       |" <<endl;
    cout << "----------------------------------"<<endl;

    cout <<endl<<endl;
    currentObj = "Row";
    objectNum = 0;
    for (int r = 0; r < 9; r++)
    {
        changeRow(r);
        objectNum++;
        checkRow();
    }
    
    currentObj = "Column";
    objectNum = 0;
    for (int r = 0; r < 9; r++)
    {
        changeColumn(r);
        objectNum++;
        checkRow();
    }
    
    currentObj = "Box";
    objectNum = 0;
    for (int k = 0; k < 3; k++)
    {
        for (int r = 0; r < 3; r++)
        {
            changeBox(3 * r);
            objectNum++;
            checkRow();
        }
        increment += 3;
    }
    
    lastCheck(puzzleValidity);
    
    string terminate;
    cout << "Press any key to closs the function" << endl;
    cin >> terminate;
}

void showPuzzle()
{
    int a, b;
    for (a = 0; a < 9; a++)
    {
        for (b = 0; b < 9; b++)
        {
            printf("%d ", puzzle[a][b]);
        }
        printf("\n");
    }
    return;
}