/*
	CS 2110
	HW9, myGame.h
	Aditya Sehgal
*/
#include"gameBoy.h"
#include"title.h"
#include"lost.h"
#include"won.h"
#include"press.h"
#include"livesText.h"
#define MAX_LIVES 3
//paddle:
#define PADDLE_COLOR COLOR(21, 10, 24)
#define LEFT_BOUND 11
#define RIGHT_BOUND 229
#define PADDLE_ROW 110
#define PADDLE_HEIGHT 5
#define PADDLE_WIDTH 20
#define PADDLE_MOVE 3
//ball:
#define LOWER_BOUND 110
#define UPPER_BOUND 10
//blocks:
#define BLOCK_WIDTH 36
#define BLOCK_SPACE 5
#define BLOCK_HEIGHT 3
int lives;
int moveR;
int moveC;
enum gameScreen{
	TITLE,
	PLAY,
	END
} screen;

enum gameStatus{
	READY,
	IN_PLAY,
	WON,
	DEAD
} status;
	
struct Block{
	int row;
	int col;
	u16* color;
	int visible;
} blocks[10];
struct Position{
	int row;
	int col;
	 u16* color;
} paddle, ball, oldPaddle, oldBall;
//function prototypes:
void clearScreen();
void drawBorder();
void initialize();
void drawTitleScreen();
void drawEndScreen();
void drawPaddle();
void drawBall();
void saveOldPositions();
void resetDisplay();
void setBlocks();
void updateBlocks(); 
int checkWin();
void updateBall();
void updatePaddle();
void displayLives();
void drawMessage();
void clearMessage();
