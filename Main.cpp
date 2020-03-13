#include "GameOfLife.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
  int fileCheck = 0;
  string modeChoice;
  string mapChoice;
  string mapInput;
  int numRows;
  int numColumns;
  float cellFreq = 0;

  cout << "Welcome to the Game of Life!" << endl;

  while(fileCheck == 0)
  {
    mapInput = "";
    std::string inputRows = "";
    std::string inputColumns = "";

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
      mapChoice = "random";
    }
    else if(inFS)
    {
      fileCheck = 1;
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
      mapChoice = "given";
    }
    else
    {
      cout << "That file could not be found. Please try another or type 'random'." << endl;
    }
  }

  int modeCheck = 0;
  int waitCheck = 0;
  int outputCheck = 0;
  bool isValid = true;
  string waitChoice;
  string outputFile;
  while(modeCheck == 0)
  {
    cout << "What boundary mode would you like to simulate? Please type 'classic', 'doughnut', or 'mirror'." << endl;
    cin >> modeChoice;

    for(int i = 0; i < modeChoice.length(); ++i)
    {
      modeChoice[i] = tolower(modeChoice[i]);
    }

    if(modeChoice == "classic" || modeChoice == "doughnut" || modeChoice == "mirror")
    {
      while(waitCheck == 0)
      {
        cout << "Would you like the program to 'pause' between generations, wait for you to press 'enter', or 'write' out to a file?" << endl;
        cin >> waitChoice;
        for(int i = 0; i < waitChoice.length(); ++i)
        {
          waitChoice[i] = tolower(waitChoice[i]);
        }
        if(waitChoice == "write")
        {
          cout << "What would you like your output file to be named?" << endl;
          cin >> outputFile;
          cout << endl;
          waitCheck = 1;
        }
        else if(waitChoice == "enter" || waitChoice == "pause")
        {
          waitCheck = 1;
          cout << endl;
        }
        else
        {
          cout << "This was not one of the choices. Please type one of the words in single quotation marks." << endl;
        }
      }
    }
    if(modeChoice == "classic")
    {
      ClassicMode *clm = new ClassicMode();
      if(mapChoice == "random")
      {
        clm -> RandomMap(numRows, numColumns, cellFreq);
      }
      else if(mapChoice == "given")
      {
        clm -> GivenMap(numRows, numColumns, mapInput);
      }
      while(isValid)
      {
        clm -> PrintMap(waitChoice, outputFile);
        clm -> NewGen();
        if(!(clm -> CheckValid()))
        {
          isValid = false;
          clm -> PrintMap(waitChoice, outputFile);
        }
      }
      modeCheck = 1;
      delete clm;
    }
    else if(modeChoice == "doughnut")
    {
      DoughnutMode *dom = new DoughnutMode();
      if(mapChoice == "random")
      {
        dom -> RandomMap(numRows, numColumns, cellFreq);
      }
      else if(mapChoice == "given")
      {
        dom -> GivenMap(numRows, numColumns, mapInput);
      }
      while(isValid)
      {
        dom -> PrintMap(waitChoice, outputFile);
        dom -> NewGen();
        if(!(dom -> CheckValid()))
        {
          isValid = false;
        }
      }
      modeCheck = 1;
      delete dom;
    }
    else if(modeChoice == "mirror")
    {
      MirrorMode *mim = new MirrorMode();
      if(mapChoice == "random")
      {
        mim -> RandomMap(numRows, numColumns, cellFreq);
      }
      else if(mapChoice == "given")
      {
        mim -> GivenMap(numRows, numColumns, mapInput);
      }
      while(isValid)
      {
        mim -> PrintMap(waitChoice, outputFile);
        mim -> NewGen();
        if(!(mim -> CheckValid()))
        {
          isValid = false;
        }
      }
      modeCheck = 1;
      delete mim;
    }
    else
    {
      cout << "This is not a valid mode. Please try again." << endl;
      modeCheck = 0;
    }
  }
  cout << "Thank you for using my program!" << endl;
}
