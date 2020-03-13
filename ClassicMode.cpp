/*
* Name: Benjamin Kahn
* ID: 2316793
* Class: CPSC-350-01
* Assignment: Programming Assignment 2: Game Of Life
* About: ClassicMode.cpp is the file that does everything necessary to simulate the classic mode of Game of Life.
*/

#include "GameOfLife.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

//class constructor
ClassicMode::ClassicMode()
{

}

//class destructor
ClassicMode::~ClassicMode()
{
  cout << "The map is either completely dead, completely crowded, or it is looping, oscillating, or repeating. The game is over." << endl;
}

//creates a random map and takes in the number of rows, the number of columns, and the frequency of cells
void ClassicMode::RandomMap(int rows, int columns, float cellFreq)
{
  numRows = rows; //makes the input global
  numColumns = columns; //makes the input global

  //creates the map for the current generation
  currentMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    currentMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      currentMap[i][j] = '-';
    }
  }

  //creates the map for the previous generation
  previousMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    previousMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      previousMap[i][j] = '-';
    }
  }

  //creates the map for the second previous generation
  oscillateMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    oscillateMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      oscillateMap[i][j] = '-';
    }
  }

  int numSpaces = numRows * numColumns; //calculates the total number of spaces in the map
  int numFull = int(numSpaces * cellFreq); //the number of spaces to be filled
  //rounds 0 up to 1 to ensure no empty maps
  if(numFull == 0)
  {
    numFull = 1;
  }

  //randomly fills the map with the proper number of cells
  for(int i = 0; i < numFull; ++i)
  {
    int randRow = rand() % numRows; //gets a random number bewteen 0 and the number of rows
    int randColumn = rand() % numColumns; //gets a random number bewteen 0 and the number of columns
    //if the cell is currently empty
    if(currentMap[randRow][randColumn] == '-')
    {
      currentMap[randRow][randColumn] = 'X';
    }
    //if the cell is not empty, do not increment
    else
    {
      i--;
    }
  }
}

//creates a random map and takes in the number of rows, the number of columns, and the file name to read from
void ClassicMode::GivenMap(int rows, int columns, string fileName)
{
  numRows = rows; //make the variable global
  numColumns = columns; //makes the variable global

  //creates the map for the current generation
  currentMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    currentMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      currentMap[i][j] = '-';
    }
  }

  //creates the map for the previous generation
  previousMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    previousMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      previousMap[i][j] = '-';
    }
  }

  //creates the map for the second previous generation
  oscillateMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    oscillateMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      oscillateMap[i][j] = '-';
    }
  }

  //opens the file to be read
  ifstream inFS;
  inFS.open(fileName);
  char c; //the current character being read
  int rowCount = -2; //the number of rows in the input
  int columnCount = 0; //the number of columbs in the input
  //while the document is not empty
  while(!inFS.eof())
  {
    inFS >> noskipws >> c;
    //in the event the X are lowercase
    if(c == 'x')
    {
      c = toupper(c);
    }

    //if the character is a cell on the map
    if(c == '-' || c == 'X')
    {
      currentMap[rowCount][columnCount] = c; //sets the current position to equal that character
      columnCount++; //increases the column count
    }
    //if the character signifies a new line
    else if(c == '\n')
    {
      columnCount = 0; //resets the column count number
      rowCount++; //increased the row count
    }
  }
  inFS.close(); //closes the file
}

//counts and returns all of the possible neighbors for the cell in the top left corner (takes in the position of the cell)
int ClassicMode::CheckCornerTL(int row, int column)
{
  int numAround = 0;
  if(previousMap[row][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//counts and returns all of the possible neighbors for the cell in the top right corner (takes in the position of the cell)
int ClassicMode::CheckCornerTR(int row, int column)
{
  int numAround = 0;
  if(previousMap[row+1][column] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row][column-1] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//counts and returns all of the possible neighbors for the cell in the bottom left corner (takes in the position of the cell)
int ClassicMode::CheckCornerBL(int row, int column)
{
  int numAround = 0;
  if(previousMap[row][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//counts and returns all of the possible neighbors for the cell in the bottom right corner (takes in the position of the cell)
int ClassicMode::CheckCornerBR(int row, int column)
{
  int numAround = 0;
  if(previousMap[row-1][column] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row][column-1] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//counts and returns all of the possible neighbors for the cells on the top side (takes in the position of the cell)
int ClassicMode::CheckSideT(int row, int column)
{
  int numAround = 0;
  if(previousMap[row][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column+1] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//counts and returns all of the possible neighbors for the cells on the right side (takes in the position of the cell)
int ClassicMode::CheckSideR(int row, int column)
{
  int numAround = 0;
  if(previousMap[row-1][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column] == 'X')
  {
    numAround++;
  }
  if(previousMap[row][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//counts and returns all of the possible neighbors for the cells on the bottom side (takes in the position of the cell)
int ClassicMode::CheckSideB(int row, int column)
{
  int numAround = 0;
  if(previousMap[row][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column+1] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//counts and returns all of the possible neighbors for the cells on the left side (takes in the position of the cell)
int ClassicMode::CheckSideL(int row, int column)
{
  int numAround = 0;
  if(previousMap[row-1][column] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//counts and returns all of the possible neighbors for the cells in the middle (takes in the position of the cell)
int ClassicMode::CheckMiddle(int row, int column)
{
  int numAround = 0;
  if(previousMap[row][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column] == 'X')
  {
    numAround++;
  }
  if(previousMap[row-1][column+1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column-1] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column] == 'X')
  {
    numAround++;
  }
  if(previousMap[row+1][column+1] == 'X')
  {
    numAround++;
  }
  return numAround;
}

//creates the next generation
void ClassicMode::NewGen()
{
  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j)
    {
      oscillateMap[i][j] = previousMap[i][j]; //sets the previous map to the second previous map
      previousMap[i][j] = currentMap[i][j]; //sets the current map to the previous map
    }
  }

  int numAround; //tracks the number of neighbors for the cell

  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j){
      numAround = 0; //resets the number of neighbors
      //if in row 1
      if(i == 0){
        //if in row 1, column 1
        if(j == 0){
          numAround = CheckCornerTL(i, j);
        }
        //if in row 1, last column
        else if(j == (numColumns - 1)){
          numAround = CheckCornerTR(i, j);
        }
        //anywhere else in row 1
        else
        {
          numAround = CheckSideT(i, j);
        }
      }
      //if in last row
      else if(i == (numRows - 1))
      {
        //if in last row, column 1
        if(j == 0)
        {
          numAround = CheckCornerBL(i, j);
        }
        //if in last row, last column
        else if(j == (numColumns - 1))
        {
          numAround = CheckCornerBR(i, j);
        }
        //anywhere else in the last row
        else
        {
          numAround = CheckSideB(i, j);
        }
      }
      //if column 0
      else if(j == 0)
      {
        //if any other row, column 0
        if(i != 0 && i != (numRows -1))
        {
          numAround = CheckSideL(i, j);
        }
      }
      //if last column
      else if(j == (numColumns - 1))
      {
        //if any other row, last column
        if(i != 0 && i != (numRows -1))
        {
          numAround = CheckSideR(i, j);
        }
      }
      //if it is not on the border anywhere
      else
      {
        numAround = CheckMiddle(i, j);
      }

      //if the cell has one or zero neighbors it dies
      if(numAround <= 1)
      {
        currentMap[i][j] = '-';
      }
      //if the cell has two neighbors it remains the same
      else if(numAround < 3)
      {

      }
      //if the cell has three neighbors it gets filled
      else if(numAround < 4)
      {
        currentMap[i][j] = 'X';
      }
      //if the cell has four, five, six, seven, or eight neighbors it dies
      else
      {
        currentMap[i][j] = '-';
      }
    }
  }
}

//prints the current map (takes in the user's print option choice and the file they wish to output the results to)
void ClassicMode::PrintMap(string choice, string outputFile)
{
  //if the user wants print option pause
  if(choice == "pause")
  {
    //pauses for .5 seconds every time
    usleep(500000);
    //if this is the original map
    if(genNum == 0)
    {
      cout << "0" << endl;
      //prints the map
      genNum++;
      for(int i = 0; i < numRows; ++i)
      {
        for(int j = 0; j < numColumns; ++j)
        {
          cout << currentMap[i][j];
        }
        cout << endl;
      }
      cout << "Generation Number: 1" << endl;
    }
    //if this is any simulated generation
    else
    {
      cout << "Generation Number: " << genNum << endl;
    }

    //prints the map
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        cout << currentMap[i][j];
      }
      cout << endl;
    }
    genNum++; //increments the generation counter
  }
  //if the user wants to use the enter print option
  else if(choice == "enter")
  {
    int enterCheck = 0; //checks if the user inputted enter

    //if at the created map
    if(genNum != 0 || genNum != 1)
    {
      //cotninues to check until the user presses enter
      while(enterCheck == 0)
      {
        cout << "Press enter to continue." << endl;
        //if the input is an enter
        if(cin.get() == '\n')
        {
          enterCheck = 1; //exit the while loop
        }
      }
    }

    //if at the created map
    if(genNum == 0)
    {
      cout << "0" << endl;
      //prints the map
      genNum++;
      for(int i = 0; i < numRows; ++i)
      {
        for(int j = 0; j < numColumns; ++j)
        {
          cout << currentMap[i][j];
        }
        cout << endl;
      }
      cout << "Generation Number: 1" << endl;
    }
    //if at a generated map
    else
    {
      cout << "Generation Number: " << genNum << endl;
    }

    //prints the map
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        cout << currentMap[i][j];
      }
      cout << endl;
    }

    genNum++; //increments the generation counter
  }
  else if(choice == "write")
  {
    //opens the file output to the file name of the user's choice
    ofstream outFS;
    outFS.open(outputFile, ios::app);

    //if at the default map
    if(genNum == 0)
    {
      outFS << "0" << endl;
      //prints the map
      genNum++;
      for(int i = 0; i < numRows; ++i)
      {
        for(int j = 0; j < numColumns; ++j)
        {
          outFS << currentMap[i][j];
        }
        outFS << endl;
      }
      outFS << "Generation Number: 1" << endl;
    }
    //if at a generated map
    else
    {
      outFS << "Generation Number: " << genNum << endl;
    }

    //prints the map
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        outFS << currentMap[i][j];
      }
      outFS << endl;
    }
    genNum++; //increments the generation counter
    outFS.close(); //closes the file output
  }
}

//checks if the generation is either full, empty, or looping (returns false if full, empty, or looping and true otherwise)
bool ClassicMode::CheckValid()
{
  bool isValid = false; //stores the value that says if the generation is valid
  int loopCheck = 0; //checks if there is looping occurring
  int numSpaces = (numRows * numColumns); //calculates the total number of cells in the map

  //if the top left corner is empty
  if(currentMap[0][0]  == '-')
  {
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        //if the current cell is full
        if(currentMap[i][j] == 'X')
        {
          isValid = true; //the generation is valid
        }
      }
    }
  }
  //if the top left corner is full
  else
  {
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        //if the current cell is empty
        if(currentMap[i][j] == '-')
        {
          isValid = true; //the generation is valid
        }
      }
    }
  }

  //checks if the map is looping
  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j)
    {
      //if the cells at each position are the same
      if(currentMap[i][j] == previousMap[i][j])
      {
        loopCheck++; //increment the loop check counter
      }
    }
  }
  //if the maps have all of their spaces in common
  if(loopCheck == numSpaces)
  {
    isValid = false; //the generation is not valid
  }

  loopCheck = 0;  //resets the loop check value

  //checks if the map is oscillating
  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j)
    {
      //if the cells at each position are the same
      if(currentMap[i][j] == oscillateMap[i][j])
      {
        loopCheck++; //increment the loop check counter
      }
    }
  }
  //if the maps have all of their spaces in common
  if(loopCheck == numSpaces)
  {
    isValid = false; //the generation is not valid
  }

  //if there have been over 1000 generations (a sign of pattern looping)
  if(genNum > 1000)
  {
    isValid = false; //the generation is not valid
  }

  return isValid; //returns whether or not the generation is valid or not
}
