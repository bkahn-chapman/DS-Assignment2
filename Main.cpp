#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
  string mapChoice;
  int numRows;
  int numColumns;
  float cellFreq;
  cout << "Welcome to the Game of Life!" << endl;
  cout << "If you would like to use a provide a map file for the simulation to use, please type the name of the file. Otherwise, please type 'random' for a random map." << endl;
  cin >> mapChoice;
  for(int i = 0; i < mapChoice.length(); ++i)
  {
    mapChoice[i] = tolower(mapChoice[i]);
  }
  if(mapChoice == "random")
  {
    cout << "How many rows would you like the map to have?" << endl;
    cin >> numRows;
    cout << "How many columns would you like the map to have?" << endl;
    cin >> numColumns;
    cout << "What would you like the frequency of filled cells to be? (decimal greater than 0 and less than or equal to 1)" << endl;
    cin >> cellFreq;
  }
  else
  {

  }
}
