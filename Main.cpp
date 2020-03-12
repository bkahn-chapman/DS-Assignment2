#include "GameOfLife.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
  GameOfLife *gol = new GameOfLife();

  int fileCheck = 0;

  cout << "Welcome to the Game of Life!" << endl;

  while(fileCheck == 0)
  {
    string mapInput = "";
    std::string inputRows = "";
    std::string inputColumns = "";
    int numRows;
    int numColumns;
    float cellFreq = 0;

    cout << "If you would like to use a provide a map file for the simulation to use, please type the name of the file. Otherwise, please type 'random' for a random map." << endl;
    cin >> mapInput;

    for(int i = 0; i < mapInput.length(); ++i)
    {
      mapInput[i] = tolower(mapInput[i]);
    }

    ifstream inFS;
    inFS.open(mapInput);


    if(mapInput == "random")
    {
      fileCheck = 1;
      cout << "How many rows would you like your game board to have?" << endl;
      cin >> numRows;
      cout << "How many columns would you like your game board to have?" << endl;
      cin >> numColumns;
      while(cellFreq <= 0 || cellFreq > 1)
      {
        cout << "What would you like the frequency of filled cells to be? (decimal greater than 0 and less than or equal to 1)" << endl;
        cin >> cellFreq;
        if(cellFreq <= 0 || cellFreq > 1)
        {
          cout << "Cell frequency must be a decimal greater than 0 and less than or equal to 1." << endl;
          cellFreq = 0;
        }
      }
      cout << endl;
      gol -> RandomMap(numRows, numColumns, cellFreq);
    }
    else if(inFS)
    {
      fileCheck = 1;
      cout << endl;
      int numLines = 1;
      char c;
      while(!inFS.eof() && numLines < 3)
      {
        inFS >> noskipws >> c;
        if(c == '\n')
        {
          numLines++;
        }
        else if(numLines == 1)
        {
          inputRows.append(1, c);
        }
        else if(numLines == 2)
        {
          inputColumns.append(1, c);
        }
        else
        {
          break;
        }
      }
      inFS.close();
      numRows = std::stoi(inputRows);
      numColumns = std::stoi(inputColumns);
      gol -> GivenMap(numRows, numColumns, mapInput);
    }
    else
    {
      cout << "That file could not be found. Please try another." << endl;
    }
  }
  bool isValid = true;
  while(isValid)
  {
    gol -> PrintMap();
    gol -> NewGen();
    if(!(gol -> CheckValid()))
    {
      isValid = false;
      gol -> PrintMap();
    }
  }

}
