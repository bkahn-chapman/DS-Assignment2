#include "GameOfLife.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

ClassicMode::ClassicMode()
{

}

ClassicMode::~ClassicMode()
{
  cout << "The map is either completely dead, completely crowded, or in a loop. The game is over." << endl;
}

void ClassicMode::RandomMap(int rows, int columns, float cellFreq)
{
  numRows = rows;
  numColumns = columns;
  currentMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    currentMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      currentMap[i][j] = '-';
    }
  }

  previousMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    previousMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      previousMap[i][j] = '-';
    }
  }

  oscillateMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    oscillateMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      oscillateMap[i][j] = '-';
    }
  }

  int numSpaces = numRows * numColumns;
  int numFull = int(numSpaces * cellFreq);
  if(numFull == 0)
  {
    numFull = 1;
  }

  for(int i = 0; i < numFull; ++i)
  {
    int randRow = rand() % numRows;
    int randColumn = rand() % numColumns;
    if(currentMap[randRow][randColumn] == '-')
    {
      currentMap[randRow][randColumn] = 'X';
    }
    else
    {
      i--;
    }
  }
}

void ClassicMode::GivenMap(int rows, int columns, string fileName)
{
  numRows = rows;
  numColumns = columns;
  currentMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    currentMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      currentMap[i][j] = '-';
    }
  }

  previousMap = new char*[numRows];

  for(int i = 0; i < numRows; ++i)
  {
    previousMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      previousMap[i][j] = '-';
    }
  }

  oscillateMap = new char*[numRows];
  for(int i = 0; i < numRows; ++i)
  {
    oscillateMap[i] = new char[numColumns];
    for(int j = 0; j < numColumns; ++j)
    {
      oscillateMap[i][j] = '-';
    }
  }

  ifstream inFS;
  inFS.open(fileName);
  char c;
  int rowCount = -2;
  int columnCount = 0;
  while(!inFS.eof())
  {
    inFS >> noskipws >> c;
    if(c == '-' || c == 'X')
    {
      currentMap[rowCount][columnCount] = c;
      columnCount++;
    }
    else if(c == '\n')
    {
      columnCount = 0;
      rowCount++;
    }
  }
  inFS.close();
}

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

void ClassicMode::NewGen()
{
  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j)
    {
      oscillateMap[i][j] = previousMap[i][j];
      previousMap[i][j] = currentMap[i][j];
    }
  }

  int numAround;

  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j){
      numAround = 0;
      if(i == 0){
        if(j == 0){
          numAround = CheckCornerTL(i, j);
        }
        else if(j == (numColumns - 1)){
          numAround = CheckCornerTR(i, j);
        }
        else
        {
          numAround = CheckSideT(i, j);
        }
      }
      else if(i == (numRows - 1))
      {
        if(j == 0)
        {
          numAround = CheckCornerBL(i, j);
        }
        else if(j == (numColumns - 1))
        {
          numAround = CheckCornerBR(i, j);
        }
        else
        {
          numAround = CheckSideB(i, j);
        }
      }
      else if(j == 0)
      {
        if(i != 0 && i != (numRows -1))
        {
          numAround = CheckSideL(i, j);
        }
      }
      else if(j == (numColumns - 1))
      {
        if(i != 0 && i != (numRows -1))
        {
          numAround = CheckSideR(i, j);
        }
      }
      else
      {
        numAround = CheckMiddle(i, j);
      }

      if(numAround <= 1)
      {
        currentMap[i][j] = '-';
      }
      else if(numAround < 3)
      {

      }
      else if(numAround < 4)
      {
        currentMap[i][j] = 'X';
      }
      else
      {
        currentMap[i][j] = '-';
      }
    }
  }
}

void ClassicMode::PrintMap(string choice, string outputFile)
{
  if(choice == "pause")
  {
    usleep(500000);
    if(genNum == 0)
    {
      cout << "0" << endl;
      genNum++;
    }
    else
    {
      cout << "Generation Number: " << genNum << endl;
    }
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        cout << currentMap[i][j];
      }
      cout << endl;
    }
    genNum++;
  }
  else if(choice == "enter")
  {
    int enterCheck = 0;
    if(genNum != 0)
    {
      while(enterCheck == 0)
      {
        string enterInput = "";
        cout << "Press enter to continue." << endl;
        if(cin.get() == '\n')
        {
          enterCheck = 1;
        }
      }
    }
    if(genNum == 0)
    {
      cout << "0" << endl;
      genNum++;
    }
    else
    {
      cout << "Generation Number: " << genNum << endl;
    }
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        cout << currentMap[i][j];
      }
      cout << endl;
    }
    genNum++;
  }
  else if(choice == "write")
  {
    ofstream outFS;
    outFS.open(outputFile, ios::app);
    if(genNum == 0)
    {
      outFS << "0" << endl;
      genNum++;
    }
    else
    {
      outFS << "Generation Number: " << genNum << endl;
    }
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        outFS << currentMap[i][j];
      }
      outFS << endl;
    }
    genNum++;
    outFS.close();
  }
}

bool ClassicMode::CheckValid()
{
  bool isValid = false;
  int loopCheck = 0;
  int numSpaces = (numRows * numColumns);
  if(currentMap[0][0]  == '-')
  {
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        if(currentMap[i][j] == 'X')
        {
          isValid = true;
        }
      }
    }
  }
  else
  {
    for(int i = 0; i < numRows; ++i)
    {
      for(int j = 0; j < numColumns; ++j)
      {
        if(currentMap[i][j] == '-')
        {
          isValid = true;
        }
      }
    }
  }

  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j)
    {
      if(currentMap[i][j] == previousMap[i][j])
      {
        loopCheck++;
      }
    }
  }
  if(loopCheck == numSpaces)
  {
    isValid = false;
  }

  loopCheck = 0;
  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j)
    {
      if(currentMap[i][j] == oscillateMap[i][j])
      {
        loopCheck++;
      }
    }
  }
  if(loopCheck == numSpaces)
  {
    isValid = false;
  }

  if(genNum > 100)
  {
    isValid = false;
  }
  return isValid;
}
