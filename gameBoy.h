/*
	CS 2110
	HW9, gameBoy.h
	Aditya Sehgal (asehgal6)
*/
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
//for the game boy
#define REG_DISPCTL *(u16*)0x4000000
#define MODE3 3
#define BG2_ENABLE (1 << 10)
//colors
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define RED COLOR(31, 0, 0)
#define BLUE COLOR(0,0, 31)
#define GREEN COLOR(0, 31, 0)
#define BLACK COLOR(0, 0, 0)
#define WHITE COLOR(31, 31, 31)
//
//offset used for drawing
#define OFFSET(r, c) ((r*240) + c)
//gameboy buttons
#define BUTTON_A 	(1<<0)
#define BUTTON_B	(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT	(1<<5)
#define BUTTON_UP	(1<<6)
#define BUTTON_DOWN	(1<<7)
#define BUTTON_R	(1<<8)
#define BUTTON_L	(1<<9)
//screen
#define MAX_ROW 160
#define MAX_COL 240
//
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)
#define BUTTONS (*(volatile unsigned int *)0x4000130)
//checks if button is pressed
#define KEY_DOWN_NOW(key) (~(BUTTONS) & key)
//
typedef struct{
	const volatile void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMAREC;
//DMA
#define DMA ((volatile DMAREC *)0x40000B0)
//DMA source, destination, control
#define REG_DMA0SAD *(vu32*)0x40000B0
#define REG_DMA0DAD *(vu32*)0x40000B4
#define REG_DMA0CNT *(vu32*)0x40000B8
#define REG_DMA1SAD *(vu32*)0x40000BC
#define REG_DMA1DAD *(vu32*)0x40000C0
#define REG_DMA1CNT *(vu32*)0x40000C4
#define REG_DMA2SAD *(vu32*)0x40000C8
#define REG_DMA2DAD *(vu32*)0x40000CC
#define REG_DMA2CNT *(vu32*)0x40000D0
#define REG_DMA3SAD *(vu32*)0x40000D4
#define REG_DMA3DAD *(vu32*)0x40000D8
#define REG_DMA3CNT *(vu32*)0x40000DC
//DMA CHANNELS
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3
//
#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED	  (2 << 21)
#define DMA_DESTINATION_RESET	  (3 << 21)
//
#define DMA_SOURCE_INCREMENT (0 <<23)
#define DMA_SOURCE_DECREMENT (1 <<23)
#define DMA_SOURCE_FIXED (2 << 23)
//
#define DMA_REPEAT (1 << 25)
//
#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)
//
#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK ( 2 << 28)
#define DMA_AT_REFRESH (3 << 28)
//
#define DMA_IRQ (1 << 30)
#define DMA_ON  (1 << 31)
#define START_ON_FIFO_EMPTY 0x3000000
//
//function prototypes
void setPixel(int , int , u16);
void drawRect(int, int , int , int, u16);
void waitForVblank();
void drawImage3(int , int , int , int , const u16* );
