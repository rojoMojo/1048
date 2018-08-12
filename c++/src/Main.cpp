#include <iostream>
#include "Program.h"
using namespace std;

int main() {
  cout << "Enter Field size:\n";
  int fieldSize;
  cin >> fieldSize;
  short int tiles[fieldSize*fieldSize];
  for (char i = 0; i < fieldSize*fieldSize; i++) tiles[i] = 0;

  playGame(tiles, fieldSize, decideMove);
}
