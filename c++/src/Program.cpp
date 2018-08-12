#include <iostream>
#include <iomanip>
#include <vector>
#include "Program.h"



using namespace std;







//region moveTileFunctions
bool canMove(short int* tiles, char fieldSize) {
  for(char i = 0, len = fieldSize*fieldSize; i<len; ++i) {
    //1. If we have a zero, we can for sure move
    if(tiles[i]==0) return true;

    //2. Check the tile on the rights, if any
    if((i+1)%fieldSize!=0 && tiles[i] == tiles[i+1]) return true;

    //3. Check the tile on the bottom, if any
    if(i<=len-fieldSize && tiles[i] == tiles[i+fieldSize]) return true;
  }

  //all failed. too bad :(
  return false;


}


/* moves and merges one tile, changes state according to direction
tile to move must NOT be last tile of column or row*/

void moveTileRight(short int* tiles, char rowStart, char tileToMove, char fieldSize, bool *moved) {

  //empty tile
  if (tiles[tileToMove] == 0) return;

  //define end of row
  char lastTileOfRow = rowStart + fieldSize -1;

  for(char tileToCheck = tileToMove+1; tileToCheck<=lastTileOfRow; ++tileToCheck) {
    if (tiles[tileToCheck] == 0) continue;//empty space. tile may go further, so we continue looping.

    else if (tiles[tileToCheck]==tiles[tileToMove]) {
      //we have to merge the cells. We will temporarly mark the merged cell with a negative value.
      tiles[tileToCheck] = -(tiles[tileToCheck] + tiles[tileToMove]);
      tiles[tileToMove] = 0;
      *moved = true;
      return;
    }

    else {
      //collision
      if (tileToCheck-1==tileToMove) {
        return;
      }//tile is exactly before colliding tile, do nothing
      tiles[tileToCheck-1] = tiles[tileToMove];//move tile until colliding tile
      tiles[tileToMove] = 0;//empty previous position
      *moved = true;
      std::cout << *moved << std::endl;
      return;
    }
  }

  //no other tile in whole row found, just move to the end
  tiles[lastTileOfRow] = tiles[tileToMove];
  tiles[tileToMove] = 0;
  *moved = true;
  std::cout << *moved << std::endl;
  return;
}



void moveTileLeft(short int* tiles, char rowStart, char tileToMove, bool *moved) {
  if (tiles[tileToMove] == 0) return;

  for(char tileToCheck = tileToMove-1; tileToCheck>=rowStart; --tileToCheck) {
    if (tiles[tileToCheck]==0) continue; //empty space. tile may go further, so we continue looping.

    else if (tiles[tileToCheck]==tiles[tileToMove]) {
      //we have to merge the cells. We will temporarly mark the merged cell with a negative value.
      tiles[tileToCheck] = -(tiles[tileToCheck] + tiles[tileToMove]);
      tiles[tileToMove] = 0;
      *moved = true;
      return;
    }

    else {
      //collision
      if (tileToCheck+1==tileToMove) return; //tile is exactly before colliding tile, do nothing
      tiles[tileToCheck+1] = tiles[tileToMove];//move tile until colliding tile
      tiles[tileToMove] = 0;//empty previous position
      *moved = true;
      return;
    }
  }

  //no other tile in whole row found, just move to the end
  tiles[rowStart] = tiles[tileToMove];
  tiles[tileToMove] = 0;
  *moved = true;
}

void moveTileUp(short int* tiles, char colStart, char tileToMove, char fieldSize, bool *moved) {
  if (tiles[tileToMove] == 0) return;

  for(char tileToCheck = tileToMove-fieldSize; tileToCheck>=colStart; tileToCheck = tileToCheck - fieldSize) {
    if (tiles[tileToCheck]==0) continue; //empty space. tile may go further, so we continue looping.

    else if (tiles[tileToCheck]==tiles[tileToMove]) {
      //we have to merge the cells. We will temporarly mark the merged cell with a negative value.
      tiles[tileToCheck] = -(tiles[tileToCheck] + tiles[tileToMove]);
      tiles[tileToMove] = 0;
      *moved = true;
      return;
    }

    else {
      //collision
      if (tileToCheck+fieldSize==tileToMove) return; //tile is exactly before colliding tile, do nothing
      tiles[tileToCheck+fieldSize] = tiles[tileToMove];//move tile until colliding tile
      tiles[tileToMove] = 0;//empty previous position
      *moved = true;
      return;
    }
  }

  //no other tile in whole row found, just move to the end
  tiles[colStart] = tiles[tileToMove];
  tiles[tileToMove] = 0;
  *moved = true;
}



void moveTileDown(short int* tiles, char colStart, char tileToMove, char fieldSize, bool *moved) {

  //empty tile
  if (tiles[tileToMove] == 0) return;

  //define end of row
  char lastTileOfCol = colStart + fieldSize * (fieldSize -1);

  for(char tileToCheck = tileToMove+fieldSize; tileToCheck<=lastTileOfCol; tileToCheck = tileToCheck + fieldSize) {
    if (tiles[tileToCheck] == 0) continue;//empty space. tile may go further, so we continue looping.

    else if (tiles[tileToCheck]==tiles[tileToMove]) {
      //we have to merge the cells. We will temporarly mark the merged cell with a negative value.
      tiles[tileToCheck] = -(tiles[tileToCheck] + tiles[tileToMove]);
      tiles[tileToMove] = 0;
      *moved = true;
      return;
    }

    else {
      //collision
      if (tileToCheck-fieldSize==tileToMove) {
        return; //tile is exactly before colliding tile, do nothing
      }

      tiles[tileToCheck-fieldSize] = tiles[tileToMove];//move tile until colliding tile
      tiles[tileToMove] = 0;//empty previous position
      *moved = true;
      return;
    }
  }

  //no other tile in whole row found, just move to the end
  tiles[lastTileOfCol] = tiles[tileToMove];
  tiles[tileToMove] = 0;
  *moved = true;
  return;
}
//endregion


//region moveRowsandColumns
void moveRowRight(short int* tiles, char rowStart, char fieldSize, bool *moved) {
  char firstTileToMove = rowStart + (fieldSize-2);
  for (char tileToMove = firstTileToMove; tileToMove >= rowStart; --tileToMove) {
    moveTileRight(tiles, rowStart, tileToMove, fieldSize, moved);
  }
}

void moveRowLeft(short int* tiles, char rowStart, char fieldSize, bool *moved) {
  char lastTileToMove = rowStart + (fieldSize-1);
  for (char tileToMove = rowStart+1; tileToMove <= lastTileToMove; ++tileToMove) {
    moveTileLeft(tiles, rowStart, tileToMove, moved);
  }
}

void moveColUp(short int* tiles, char colStart, char fieldSize, bool *moved) {
  char lastTileToMove = colStart + (fieldSize-1)*fieldSize;
  for (char tileToMove = colStart+fieldSize; tileToMove <= lastTileToMove; tileToMove+=fieldSize) {
    moveTileUp(tiles, colStart, tileToMove, fieldSize, moved);
  }
}

void moveColDown(short int* tiles, char colStart, char fieldSize, bool *moved) {
  char firstTileToMove = colStart + (fieldSize-2)*fieldSize;
  for (char tileToMove = firstTileToMove; tileToMove >= colStart; tileToMove-=fieldSize) {
    moveTileDown(tiles, colStart, tileToMove, fieldSize, moved);
  }
}
//endregion



//region PERFORM MOVE
void makePositive(short int* tiles, char fieldSize) {
  for (char i = 0, len = fieldSize*fieldSize; i < len; i++) {
    if (tiles[i] < 0) tiles[i] = -tiles[i];
  }
}


void doMoveRight(short int* tiles, char fieldSize, bool* moved) {
  char lastRowStart = (fieldSize-1)*fieldSize;
  for (char rowStart = 0; rowStart <= (fieldSize-1)*fieldSize; rowStart+=fieldSize) {
    moveRowRight(tiles, rowStart, fieldSize, moved);
  }

  makePositive(tiles, fieldSize);
}

void doMoveLeft(short int* tiles, char fieldSize, bool *moved) {
  char lastRowStart = (fieldSize-1)*fieldSize;
  for (char rowStart = 0; rowStart <= (fieldSize-1)*fieldSize; rowStart+=fieldSize) {
    moveRowLeft(tiles, rowStart, fieldSize, moved);
  }
  makePositive(tiles, fieldSize);
}

void doMoveUp(short int* tiles, char fieldSize, bool *moved) {
  for (char colStart = 0; colStart < fieldSize; colStart++) {
    moveColUp(tiles, colStart, fieldSize, moved);
  }
  makePositive(tiles, fieldSize);
}

void doMoveDown(short int* tiles, char fieldSize, bool *moved) {
  for (char colStart = 0; colStart < fieldSize; colStart++) {
    moveColDown(tiles, colStart, fieldSize, moved);
  }
  makePositive(tiles, fieldSize);
}
//endregion



//region ROUND RELATED FUNCTIONS
void doMove(short int* tiles, char dir, char fieldSize, bool *moved) {
  switch(dir) {
    case MOVE_RIGHT:
      doMoveRight(tiles,fieldSize,moved);
      break;

    case MOVE_LEFT:
      doMoveLeft(tiles,fieldSize,moved);
      break;

    case MOVE_DOWN:
      doMoveDown(tiles,fieldSize,moved);
      break;

    case MOVE_UP:
      doMoveUp(tiles,fieldSize,moved);
      break;
  }
}


/*adds new tiles (4 or 2) randomly at empty space, returns -1 if no empty space available*/
char addNewTiles(short int* tiles, char whichTile, char fieldSize) {
  char lengthOfTile = fieldSize*fieldSize;
  //1. gather all empty indexes
  std::vector<char> emptyPositions;
  for (char i = 0; i < lengthOfTile; i++) {
    if (tiles[i] == 0) emptyPositions.push_back(i);
  }

  //2. Choose the index to insert the tile
  if(emptyPositions.size()==0) return -1; //no free space was found
  char indexToInsertTile = emptyPositions[  rand() % emptyPositions.size() ];

  //3. Insert the tile
  tiles[indexToInsertTile] = whichTile;
  return 0;
}
//endregion









//region PLAYER
char decideMove(short int* tiles) {

  while(1) {
      //1. Get the next character
      std::string command;
      getline(std::cin, command);

      //2. Decide action based on the given character
      switch(command[0]) {
        case 's': return MOVE_LEFT;
        case 'f': return MOVE_RIGHT;
        case 'd': return MOVE_DOWN;
        case 'e': return MOVE_UP;
      }

      //3. We did not have a match. Print help message and loop again
      std::cout << "Please enter one of s, d, f or e" << std::endl;
  }

  return 0;
}


void playGame(short int* tiles, char fieldSize, char decideMove(short int* tiles)) {
  //initialize boolean
  bool moved = false;


  //add first two tiles
  addNewTiles(tiles, 2, fieldSize);
  addNewTiles(tiles, 2, fieldSize);

  while(1) {
    //1. Render
    render(tiles, fieldSize, std::cout);
    std::cout << std::endl << std::endl;

    //2. Check game over
    if(!canMove(tiles, fieldSize)) {
      std::cout << "GAME OVER." << std::endl;
      return;
    }

    //3. Decide direction of move
    char nextMove = decideMove(tiles);

    //4. Perform move; boolean will be changed to true, if something has moved
    moved = false;
    doMove(tiles, nextMove, fieldSize, &moved);

    //5. Add new tile only if something has moved
    if (moved) addNewTiles(tiles, 2, fieldSize);
  }
}
//endregion


//region OUTPUT functions
/*visualizes gamefield (array)*/
void render(short int* tiles, char fieldSize, std::ostream& out) {
  for (char i=0, len=fieldSize*fieldSize; i<len; ++i) {
    //1. print the numberout
    if(tiles[i]) out << std::setw(7) << std::right << tiles[i];
    else out << std::setw(7) << std::right << ".";

    //2. Change line, if needed
    if ((i+1)%fieldSize == 0) out << std::endl;
  }
}
//endregion

//region start main and utilities


//endregion
