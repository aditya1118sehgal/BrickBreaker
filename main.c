/*
	CS 2110
	HW9, main.c
	Aditya Sehgal (asehgal6)
*/
#include "myGame.h"

int main()
{

	//set MODE3 and enable BG2
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	//initialize start of the game
	screen = TITLE;
	status = READY;
	drawTitleScreen();
	//game loop
	while(1){
		//if SELECT is pressed
		//always RESET
		if( KEY_DOWN_NOW(BUTTON_SELECT)){
			screen = TITLE;
			status = READY;
			drawTitleScreen();
		}
		//
		//if the game is at the title screen
		if(screen == TITLE){
			//if START is pressed
			//display the PLAY screen
			if( KEY_DOWN_NOW(BUTTON_START)){
				screen = PLAY;
				status = READY;
				initialize();
				resetDisplay();
				setBlocks();
			}
		}
		//
		//if the game screen is on the display
		if( screen == PLAY){
			//game hasn't started yet, but ready to start
			if( status == READY){
				drawMessage();
				//start the game if START is pressed
				if( KEY_DOWN_NOW(BUTTON_START)){
					status = IN_PLAY;
					clearMessage();
					drawBlocks();
				}
			}
			//game is not is play
			//player is dead
			if( status == DEAD ){
				// no lives remaining
				if( lives <1 ){
					//game over
					screen = END;
					drawEndScreen();
				}
				// at least 1 life remaining
				else{
					drawMessage();
					//ready to resume play with the next remaining life
					if( KEY_DOWN_NOW(BUTTON_START)){
						status = READY;
						//save life before reinitializing
						int s = lives;
						initialize();
						lives = s;
						resetDisplay();
						drawBlocks();
						updateBlocks();
					}
				}
			}
			//
			// game is in play
			if( status == IN_PLAY ){
				//check the winning condition
				if( checkWin() == 1){
					//game is won
					status = WON;
					screen = END;
				}
				saveOldPositions();
				ball.col += moveC;
				ball.row += moveR;
				//player is dead
				//paddle is not beneath the ball
				//ball falls below the lower bound limit
				if( ball.row >= (LOWER_BOUND - 1) && !(ball.col >= paddle.col && ball.col <= paddle.col + PADDLE_WIDTH)){
					status = DEAD;
					lives --;
					
				}
				//if the player did not die
				if( status == IN_PLAY){
					//update ball position
					updateBall();
					blockHit();
					updateBlocks();
				}
				//check paddle movements and update
				updatePaddle();
				//redraw ball and paddle
				waitForVblank();
				drawPaddle();
				drawBall();
				displayLives();
			}
			
		}
		//game over
		if( screen == END)
			drawEndScreen();
		

					
	}	
	return 0;
}
