/*
	CS 2110
	HW9, myGame.c
	Aditya Sehgal (asehgal6)
*/
#include"myGame.h"
void clearScreen(){
	drawRect(0, 0, MAX_ROW, MAX_COL, BLACK);
}
void drawBorder(){
	//borders:
	drawRect(0, 0, 10, 230, BLUE);
	drawRect(10, 0, 150, 10, BLUE);
	drawRect(0, 230 ,150, 10, BLUE);
	drawRect(150, 0, 10, 240, BLUE);
}
void initialize()
{
	moveR = -1;
	moveC = 2;
	ball.row = PADDLE_ROW-1;
	ball.col = 120;
	ball.color = WHITE;
	paddle.row = PADDLE_ROW;
	paddle.col = 110;
	paddle.color = PADDLE_COLOR;
	lives = MAX_LIVES;
	saveOldPositions();
	
}
void drawTitleScreen(){
	drawImage3(0, 0, 240, 160, title);
}
void drawEndScreen(){
	if( status == DEAD)
		drawImage3(0, 0, 240, 160, lost);
	if( status == WON)
		drawImage3(0, 0, 240, 160, won);
}
void drawPaddle(){
	//clear old paddle
	drawRect(PADDLE_ROW, oldPaddle.col, PADDLE_HEIGHT, PADDLE_WIDTH, BLACK);
	//draw paddle
	drawRect(PADDLE_ROW, paddle.col, PADDLE_HEIGHT, PADDLE_WIDTH, paddle.color);
}
void drawBall(){
	//clear old ball
	setPixel(oldBall.row, oldBall.col, BLACK);
	//draw ball
	setPixel(ball.row, ball.col, ball.color);
}
void saveOldPositions(){
	oldBall.row = ball.row;
	oldBall.col = ball.col;
	oldPaddle.row = paddle.row;
	oldPaddle.col = paddle.col;
}
void resetDisplay(){
	clearScreen();
	drawBall();
	drawBorder();
	drawPaddle();
}
void setBlocks(){
	int i, j = 0, r, g, b;
	for( i = 15; j < 5;j ++,  i += (BLOCK_WIDTH + BLOCK_SPACE)){
		blocks[j].row = 15;
		blocks[j].col = i;
		do{
			r = rand()%32;
			g = rand()%32;
			b = rand()%32;
		} while( (r == g) && (g == b) && (b == r ) && (r < 10 && g < 10 && b < 10));
		blocks[j].color = COLOR( r, g, b);
		blocks[j].visible = 1;
	}
	for( j = 5, i = 15; j < 10; i +=(BLOCK_WIDTH + BLOCK_SPACE), j ++){
		blocks[j].row = 30;
		blocks[j].col = i;
		do{
			r = rand()%32;
			g = rand()%32;
			b = rand()%32;
		}
		while( (r == g) && (b == g) && (b == r ) && (r < 10 && g < 10 && b < 10));
		
		blocks[j].color = COLOR(r, g, b);
		blocks[j].visible = 1;
	}
}
void drawBlocks(){
	int i = 0;
	for( ; i < 10; i ++)
		drawRect(blocks[i].row, blocks[i].col, BLOCK_HEIGHT, BLOCK_WIDTH, blocks[i].color);
	updateBlocks();
}
void blockHit(){
	int i = 0;
	for( ; i < 10; i ++){
		if( blocks[i].visible == 1){
			//side collision
			if( ball.row >= blocks[i].row && ball.row <= (blocks[i].row + BLOCK_HEIGHT) )
				if( ball.col == blocks[i].col || (ball.col == (blocks[i].col + BLOCK_WIDTH) )){
					moveC = -moveC;
					blocks[i].visible = 0;
					updateBlocks();
					break;
			}
			//top or bottom collision
			if( (ball.col >= blocks[i].col ) && (ball.col <= (blocks[i].col + BLOCK_WIDTH) )){
				if( ball.row == blocks[i].row || (ball.row == (blocks[i].row + BLOCK_HEIGHT))){
					moveR = -moveR;
					blocks[i].visible = 0;
					updateBlocks();
					break;
				}
			}

		}
	}
}
void updateBlocks(){
	int i =0;
	for( ; i < 10 ; i ++)
		if( blocks[i].visible == 0)
			drawRect(blocks[i].row, blocks[i].col, BLOCK_HEIGHT, BLOCK_WIDTH, BLACK);
}
int checkWin(){
	int i  = 0;
	for( ; i < 10 ; i ++)
		if( blocks[i].visible == 1)
			return 0;
	return 1;
}
void updatePaddle(){
	if( KEY_DOWN_NOW(BUTTON_LEFT)){
		paddle.col -= PADDLE_MOVE;
		if( paddle.col <= (LEFT_BOUND - 1))
			paddle.col = oldPaddle.col;
	}
	if( KEY_DOWN_NOW(BUTTON_RIGHT)){
		paddle.col += PADDLE_MOVE;
		if( (paddle.col + PADDLE_WIDTH) >= (RIGHT_BOUND -1))
		paddle.col = oldPaddle.col;
	}
}
void updateBall(){
	if( ball.col <= (LEFT_BOUND + 1) || ( ball.col >= (RIGHT_BOUND - 1)) ){
		ball.col = oldBall.col;
		moveC = -moveC;
	}
	if( ball.row <= (UPPER_BOUND + 1) || (ball.row >= (LOWER_BOUND - 1))){
		ball.row = oldBall.row;
		moveR = -moveR;
	}
}
void displayLives(){
	//
	drawImage3(120, 30, 48, 20, livesText);
	int i = 130;
	int j = 110;
	int s = 10;
	int l = 0;
	while( l < lives ){
		setPixel(i, j + (l*s), RED);
		l ++;
		
	}
	
}
void drawMessage(){
	drawImage3(60, 60, 120, 40, press);
}
void clearMessage(){
	drawRect(60, 60, 50, 120, BLACK);
}
