#include "ClassicMode.h"
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
  if(previousMap[row][column-1] == 'X')
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
      previousMap[i][j] = currentMap[i][j];
    }
  }

  int numAround;

  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j){
      numAround = 0;
      if(previousMap[i][j] == 'X'){
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
}

void ClassicMode::PrintMap(string choice)
{
  cout << "Generation Number: " << genNum << endl;
  for(int i = 0; i < numRows; ++i)
  {
    for(int j = 0; j < numColumns; ++j)
    {
      cout << currentMap[i][j];
    }
    cout << endl;
  }
  genNum++;
  cout << endl;
}

bool ClassicMode::CheckValid()
{
  bool isValid = false;
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
  return isValid;
}
