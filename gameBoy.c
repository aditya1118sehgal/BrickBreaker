/*
	CS 2110
	HW9, gameBoy.c
	Aditya Sehgal (asehgal6)
*/
#include"gameBoy.h"

u16* videoBuffer = (u16*)0x6000000;
void setPixel(int r, int c, u16 color){
	*(videoBuffer + OFFSET(r, c)) = color;
}

void drawRect(int r, int c, int height, int width, u16 color){
	int i , j;
	for( i = 0; i < height; i ++)
		for( j  = 0 ; j < width; j ++)
			setPixel( (i+r), (j+c), color);
}

void waitForVblank(){
	while(SCANLINECOUNTER > MAX_ROW);
	while(SCANLINECOUNTER < MAX_ROW);
}
void drawImage3(int r, int c, int width, int height, const u16* image){
	int i, j;
	for( i = r; i <= (height + r); i ++){
		DMA[3].src = image + (width*(i-r));
		DMA[3].dst = videoBuffer + (240*i) + c;
		DMA[3].cnt = DMA_ON | width;
	}
}
