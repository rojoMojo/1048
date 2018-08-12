//region CONSTANT DEFINITIONS
#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_UP 3
#define MOVE_DOWN 4
//endregion



//region FUNCTIONS
void moveTileRight(short int* tiles, char rowStart, char tileToMove, char fieldSize);
void moveTileLeft(short int* tiles, char rowStart, char tileToMove);
void moveTileDown(short int* tiles, char colStart, char tileToMove, char fieldSize);
void moveTileUp(short int* tiles, char colStart, char tileToMove, char fieldSize);
void moveRowRight(short int* tiles, char rowStart, char fieldSize);
void moveRowLeft(short int* tiles, char rowStart, char fieldSize);
void moveColUp(short int* tiles, char colStart, char fieldSize);
void moveColDown(short int* tiles, char colStart, char fieldSize);
void doMoveRight(short int* tiles, char fieldSize);


char decideMove(short int* tiles);
void playGame(short int* tiles, char fieldSize, char decideMove(short int* tiles));
void render(short int* tiles, char fieldSize, std::ostream& out);
//endregion
