#include <iostream>
#include "Assert.h"
#include "../src/Program.h"


void compareArr(short int* expected, short int* tiles, const std::string& label) {
  for(int i=0; i<9; i++) {
    Assert::equals(expected[i], tiles[i], label + "_" + std::to_string(i));
  }
}

void testRightMovement(const std::string& t) {
  //don't move empty tile
  short int tiles[] = {
    0,0,0,
    0,2,0,
    2,0,0
  };

  short int copy[9];
  memcpy(copy, tiles, 9*sizeof(short int));


  moveTileRight(tiles, 0, 0, 3);
  compareArr(copy, tiles, t+"R1");

  // tests moving
  short int expected[] = {
    0,0,0,
    0,0,2,
    2,0,0
  };


  moveTileRight(tiles, 3, 4, 3);
  compareArr(expected, tiles, t+"R2");



  short int expected2[] = {
    0,0,0,
    0,0,2,
    0,0,2
  };


  moveTileRight(tiles, 6, 6, 3);
  compareArr(expected2, tiles, t+"R3");
}

void testLeftMovement(const std::string& t) {
  //don't move empty tile
  short int tiles[] = {
    0,0,0,
    0,2,0,
    2,0,0
  };

  short int copy[9];
  memcpy(copy, tiles, 9*sizeof(short int));


  moveTileLeft(tiles, 0, 0);
  compareArr(copy, tiles, t+"L1");

  // tests moving
  short int expected[] = {
    0,0,0,
    2,0,0,
    2,0,0
  };


  moveTileLeft(tiles, 3, 4);
  compareArr(expected, tiles, t+"L2");

}

void testDownMovement(const std::string& t) {
  short int tiles[] = {
    0,2,2,
    2,2,0,
    0,0,0
  };

  short int expected[] = {
    0,2,0,
    2,2,0,
    0,0,2
  };

  moveTileDown(tiles, 2, 2, 3);
  compareArr(expected, tiles, t+"D1");
}

void testUpMovement(const std::string& t) {
  short int tiles[] = {
    0,2,0,
    2,2,0,
    0,0,2
  };

  short int expected[] = {
    0,2,2,
    2,2,0,
    0,0,0
  };

  moveTileUp(tiles, 2, 8, 3);
  compareArr(expected, tiles, t+"U1");
}

void testMerging(const std::string& t) {
  short int tiles[] = {
    0,2,2,
    2,2,0,
    0,0,0
  };

  short int expected[] = {
    0,0,-4,
    2,2,0,
    0,0,0
  };
  //test testright
  moveTileRight(tiles, 0, 1, 3);
  compareArr(expected, tiles, t+"R1");
  //test left
  short int expected2[] = {
    0,0,-4,
    -4,0,0,
    0,0,0
  };

  moveTileLeft(tiles, 3, 4);
  compareArr(expected2, tiles, t+"L1");

  //test testDownMovement
  short int tiles1[] = {
    0,2,2,
    2,2,0,
    0,4,0
  };

  short int expected1[] = {
    0,0,2,
    2,-4,0,
    0,4,0
  };

  moveTileDown(tiles1, 1, 1, 3);
  compareArr(expected1, tiles1, t +"D1");

  //test testUpMovement
  short int tilesUp[] = {
    0,2,2,
    2,2,0,
    0,4,0
  };

  short int expectedUp[] = {
    0,-4,2,
    2,0,0,
    0,4,0
  };

  moveTileUp(tilesUp, 1, 4, 3);
  compareArr(expectedUp, tilesUp, t +"U1");
}

void testCollision(const std::string& t) {
  short int tiles[] = {
    0,2,4,
    2,4,-4,
    0,2,0
  };

  short int expected[] = {
    0,2,4,
    2,4,-4,
    0,2,0
  };
  //test testright
  moveTileRight(tiles, 0, 1, 3);
  compareArr(expected, tiles, t+"R1");

  moveTileRight(tiles, 3, 4, 3);
  compareArr(expected, tiles, t+"R2");



  //test left
  moveTileLeft(tiles, 0, 2);
  compareArr(expected, tiles, t+"L1");

  moveTileLeft(tiles, 3, 4);
  compareArr(expected, tiles, t+"L2");

  moveTileLeft(tiles, 3, 5);
  compareArr(expected, tiles, t+"L2");

  //test testDownMovement
  moveTileDown(tiles, 1, 4, 3);
  compareArr(expected, tiles, t+"D1");

  //test testUpMovement
  moveTileUp(tiles, 1, 7, 3);
  compareArr(expected, tiles, t +"U1");
}

void testMoveRowRight(const std::string& t) {
  short int tiles[] = {
    0,0,2,
    2,2,2,
    2,2,0
  };

  short int expected[] = {
    0,0,2,
    0,2,-4,
    2,2,0
  };

  moveRowRight(tiles, 3, 3);
  compareArr(expected, tiles, t + "RR1");
}

void testMoveRowLeft(const std::string& t) {
  short int tiles[] = {
    0,0,2,
    2,2,2,
    2,2,0
  };

  short int expected[] = {
    0,0,2,
    -4,2,0,
    2,2,0
  };

  moveRowLeft(tiles, 3, 3);
  compareArr(expected, tiles, t + "RL1");
}

void testMoveColUp(const std::string& t) {
  short int tiles[] = {
    0,2,2,
    2,0,2,
    2,2,0
  };

  short int expected[] = {
    0,-4,2,
    2, 0,2,
    2, 0,0
  };

  moveColUp(tiles, 1, 3);
  compareArr(expected, tiles, t + "CU1");
}

void testMoveColDown(const std::string& t) {
  short int tiles[] = {
    0,2,2,
    2,0,2,
    2,2,0
  };

  short int expected[] = {
    0, 0,2,
    2, 0,2,
    2,-4,0
  };

  moveColDown(tiles, 1, 3);
  compareArr(expected, tiles, t + "CD1");
}

void testDoMoveRight(const std::string& t) {
  short int tiles[] = {
    0,2,2,
    2,0,2,
    2,2,0
  };

  short int expected[] = {
    0,0,-4,
    0,0,-4,
    0,0,-4
  };

  doMoveRight(tiles, 3);
  compareArr(expected, tiles, t + "DR1");

}


int main() {
  testRightMovement("testRightMovement ");
  testLeftMovement("testLeftMovement ");
  testMerging("testMerging ");
  testCollision("testCollision ");
  testDownMovement("testDownMovement ");
  testUpMovement("testUpMovement ");
  testMoveRowRight("testMoveRowRight ");
  testMoveRowLeft("testMoveRowLeft ");
  testMoveColUp("testMoveColUp ");
  testMoveColDown("testMoveColDown ");
  testDoMoveRight("testDoMoveRight ");

  std::cout << "I run all tests successfully." << std::endl;
}
