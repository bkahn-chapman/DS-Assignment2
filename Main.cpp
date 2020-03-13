/*
* Name: Benjamin Kahn
* ID: 2316793
* Class: CPSC-350-01
* Assignment: Programming Assignment 2: Game Of Life
* About: Main.cpp gets all of the user's input and loops through the specified game mode with the specified settings until the game ends.
*/

#include "GameOfLife.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
  int fileCheck = 0; //checks if the file given is available and valid
  string modeChoice; //the user's game mode choice
  string mapChoice; //the user's map style choice
  string mapInput; //the file to accept map input from
  int numRows; //the number of rows in the map
  int numColumns; //the number of columns in the map
  float cellFreq = 0; //how frequently the user wants cell to be placed in the original map

  cout << "Welcome to the Game of Life!" << endl;

  //continues until valid user input is received
  while(fileCheck == 0)
  {
    mapInput = ""; //users's map file
    std::string inputRows = ""; //the number of rows from the map file
    std::string inputColumns = ""; //the number of columns from the map file

    cout << "If you would like to use a provide a map file for the simulation to use, please type the name of the file. Otherwise, please type 'random' for a random map." << endl;
    cin >> mapInput; //user's map file

    //turns the input to lowercase
    for(int i = 0; i < mapInput.length(); ++i)
    {
      mapInput[i] = tolower(mapInput[i]);
    }

    //opens the map file
    ifstream inFS;
    inFS.open(mapInput);

    //if the user wants a random map
    if(mapInput == "random")
    {
      fileCheck = 1; //exits the while loop
      cout << "How many rows would you like your game board to have?" << endl;
      cin >> numRows; //number of rows the user wants
      cout << "How many columns would you like your game board to have?" << endl;
      cin >> numColumns; //number of columns the user wants
      //not in between 0 and 1 (including 1)
      while(cellFreq <= 0 || cellFreq > 1)
      {
        cout << "What would you like the frequency of filled cells to be? (decimal greater than 0 and less than or equal to 1)" << endl;
        cin >> cellFreq; //the frequency of cells the user wants
        if(cellFreq <= 0 || cellFreq > 1) //not in between 0 and 1 (including 1)
        {
          cout << "Cell frequency must be a decimal greater than 0 and less than or equal to 1." << endl;
          cellFreq = 0; //resets the cell frequency to continue the loop
        }
      }
      mapChoice = "random"; //sets the map choice to random
    }
    //if the user has an input file that exists
    else if(inFS)
    {
      fileCheck = 1; //exits the while loop
      int numLines = 1; //number of lines in the file
      char c; //input character
      while(!inFS.eof() && numLines < 3) //only searches the first two lines for row and column input
      {
        inFS >> noskipws >> c; //gets the next character
        if(c == '\n') //new line
        {
          numLines++;
        }
        else if(numLines == 1) //row line
        {
          inputRows.append(1, c); //appends in the event it is a double digit number
        }
        else if(numLines == 2) //column line
        {
          inputColumns.append(1, c); //appends in the event it is a double digit number
        }
        else //once it gets past the row and column lines
        {
          break;
        }
      }
      inFS.close();
      numRows = std::stoi(inputRows); //turns the string into an int
      numColumns = std::stoi(inputColumns); //turns the string into an int
      mapChoice = "given"; //changes the map creation to input
    }
    else //if the file does not exist
    {
      cout << "That file could not be found. Please try another or type 'random'." << endl;
    }
  }

  int modeCheck = 0; //tracks if a proper game mode has been inputted
  int waitCheck = 0; //tracks if a proper wait option has been inputted
  bool isValid = true; //checks if the next generation is empty, full, or looping
  string waitChoice; //stores the user's choice of wait option
  string outputFile; //stores the user's output file name
  //while a valid mode has not yet been chosen
  while(modeCheck == 0)
  {
    cout << "What boundary mode would you like to simulate? Please type 'classic', 'doughnut', or 'mirror'." << endl;
    cin >> modeChoice; //gets the user's mode choice input

    //converts the input to lowercase
    for(int i = 0; i < modeChoice.length(); ++i)
    {
      modeChoice[i] = tolower(modeChoice[i]);
    }

    //if the mode is listed
    if(modeChoice == "classic" || modeChoice == "doughnut" || modeChoice == "mirror")
    {
      //while a valid wait option has not been chosen
      while(waitCheck == 0)
      {
        cout << "Would you like the program to 'pause' between generations, wait for you to press 'enter', or 'write' out to a file?" << endl;
        cin >> waitChoice; // gets the user's wait choice input

        //turns the input to lowercase
        for(int i = 0; i < waitChoice.length(); ++i)
        {
          waitChoice[i] = tolower(waitChoice[i]);
        }

        //if the user wants to write to a file
        if(waitChoice == "write")
        {
          cout << "What would you like your output file to be named?" << endl;
          cin >> outputFile; //gets the user's output file name
          cout << endl;
          waitCheck = 1; //ends the while loop
        }
        //if the user wants to press enter to continue or have consistent pauses
        else if(waitChoice == "enter" || waitChoice == "pause")
        {
          waitCheck = 1; //ends the while loop
          cout << endl;
        }
        //if the user does not input a possible choice
        else
        {
          cout << "This was not one of the choices. Please type one of the words in single quotation marks." << endl;
        }
      }
    }

    //if the user wants classic mode
    if(modeChoice == "classic")
    {
      ClassicMode *clm = new ClassicMode(); //creates a new classic mode object
      //classic mode, random map
      if(mapChoice == "random")
      {
        clm -> RandomMap(numRows, numColumns, cellFreq);
      }
      //classic mode, given map
      else if(mapChoice == "given")
      {
        clm -> GivenMap(numRows, numColumns, mapInput);
      }
      //while there are still future generations
      while(isValid)
      {
        clm -> PrintMap(waitChoice, outputFile); //prints the current map
        clm -> NewGen(); //creates the next generation
        //if the next generation is not valud
        if(!(clm -> CheckValid()))
        {
          isValid = false; //breaks the while loop
          clm -> PrintMap(waitChoice, outputFile); //prints out the final generation
        }
      }
      modeCheck = 1; //ends the while loop
      delete clm; //deletes the object
    }
    //if the user chooses doughnut mode
    else if(modeChoice == "doughnut")
    {
      DoughnutMode *dom = new DoughnutMode(); //creates a new doughnut mode object
      //doughnut mode, random map
      if(mapChoice == "random")
      {
        dom -> RandomMap(numRows, numColumns, cellFreq);
      }
      //doughnut mode, given map
      else if(mapChoice == "given")
      {
        dom -> GivenMap(numRows, numColumns, mapInput);
      }
      //while future generations can still be made
      while(isValid)
      {
        dom -> PrintMap(waitChoice, outputFile); //print the current map
        dom -> NewGen(); //create the next generation
        //if the next generation is not valid
        if(!(dom -> CheckValid()))
        {
          isValid = false; //ends the while loop
          dom -> PrintMap(waitChoice, outputFile); //prints out the final generation
        }
      }
      modeCheck = 1; //ends the while loop
      delete dom; //delets the object
    }
    //if the user chooses mirror mode
    else if(modeChoice == "mirror")
    {
      MirrorMode *mim = new MirrorMode(); //creates a new mirror mode object
      //mirror mode, random map
      if(mapChoice == "random")
      {
        mim -> RandomMap(numRows, numColumns, cellFreq);
      }
      //mirror mode, given map
      else if(mapChoice == "given")
      {
        mim -> GivenMap(numRows, numColumns, mapInput);
      }
      //while there is another generation that can be created
      while(isValid)
      {
        mim -> PrintMap(waitChoice, outputFile); //print the current generation
        mim -> NewGen(); //creates the next generation
        //if the next generation is not valid
        if(!(mim -> CheckValid()))
        {
          isValid = false; //ends the while loop
          mim -> PrintMap(waitChoice, outputFile); //prints out the final generation
        }
      }
      modeCheck = 1; //ends the while loop
      delete mim; //deletes the object
    }
    //if the user does not enter a valid game mode
    else
    {
      cout << "This is not a valid mode. Please try again." << endl;
      modeCheck = 0;
    }
  }
  cout << "Thank you for using my program!" << endl;
}
