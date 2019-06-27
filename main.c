#include <stdbool.h>

#include "myLib.h"

#include "img/bird.h"
#include "img/background.h"
#include "img/start.h"
#include "text.h"

#include "shapes.h"
#include <stdlib.h>
#include "img/gameover.h"
#include "stdio.h"

#define OFFSET(r, c, rowlen) ((c) + (rowlen)*(r))
// u16* videoBuffer = (u16*)0x6000000;

u16* green = (u16*)GREEN;



void waitForVBlank();
void drawFullscreenImage3(const unsigned short *image);

volatile unsigned short *videoBuffer = (unsigned short *)0x6000000;



void drawImage(int row, int col, int width, int height, const u16* image) {
	if (col < 240)
	{
		    for (int r = 0; r < height; r++) {
        DMA[3].src = image + OFFSET(r, 0, width);
        DMA[3].dst = videoBuffer + OFFSET(row + r, col, 240);
        DMA[3].cnt = width | DMA_ON ;    
    }
	}
}




enum GBAState {
	STATE_ONE,
	STATE_START,
	STATE_GAME,
	STATE_END,
};


//prototypes
void delay(int n);
// void setPixel(int , int , unsigned short );
void drawPipe(int col, int width, int height);


int score = 0;

int main()
{

	// char result[50] = "";
	// int score = 0;
	REG_DISPCNT = MODE3 | BG2_ENABLE;

	enum GBAState state = STATE_ONE;

		//bird's original points
				Vector tony;
				tony.x = 20;
				tony.y = 20;

	//limits that the bird can go
	 int top_limit = 0;
	 int bot_limit = 125;
	 int left_limit = 0;
	 int right_limit = 50;

	while(1) {
		waitForVBlank();


		switch(state) {

		case STATE_ONE:
            drawImage(0,0,240,160,start);
            drawString(80, 90, "Press START", RED);
            state = STATE_START;
            char result[50] = "";
			score = 0;
            break;


		case STATE_START:
			if (KEY_DOWN_NOW(BUTTON_START)) {
				drawImage(0,0,240,160,background);
                state = STATE_GAME;
			} 
			break;


		case STATE_GAME:

				tony.x = 20;
				tony.y = 20;

				Vector Pipe1;
					Pipe1.x = 240;
					Pipe1.y = 50;
				Vector Pipe2;
					Pipe2.x = 360;
					Pipe2.y = 110;
				Vector Pipe3;
					Pipe3.x = 480;
					Pipe3.y = 70;
				Vector Pipe4;
					Pipe4.x = 600;
					Pipe4.y = 100;
				Vector Pipe5;
					Pipe5.x = 720;
					Pipe5.y = 125;



			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
                state = STATE_ONE;
			} else {
				while(!KEY_DOWN_NOW(BUTTON_SELECT)){


					//actual game
					drawString(150, 45, result, 0x7773);
					sprintf(result, "%d", score);

					drawImage(tony.y, tony.x, 28, 10, bird);

					//draw all of the pipes
					drawPipe(Pipe1.x, 15, Pipe1.y);					
					drawPipe(Pipe2.x, 15, Pipe2.y);					
					drawPipe(Pipe3.x, 15, Pipe3.y);					
					drawPipe(Pipe4.x, 15, Pipe4.y);					
					drawPipe(Pipe5.x, 15, Pipe5.y);
		            drawString(150, 5, "Score: ", RED);
		            drawString(150, 45, result, RED);
					
					

					//if the bird's four corners are touching green
					if ((videoBuffer[OFFSET(tony.y, tony.x, 240)] == GREEN) | (videoBuffer[OFFSET(tony.y + 10, tony.x + 26, 240)] == GREEN) |
						(videoBuffer[OFFSET(tony.y + 10, tony.x, 240)] == GREEN) | (videoBuffer[OFFSET(tony.y, tony.x + 26, 240)] == GREEN) |
						(videoBuffer[OFFSET(tony.y + 10, tony.x + 14, 240)] == GREEN) | (videoBuffer[OFFSET(tony.y, tony.x + 14, 240)] == GREEN))
					{
						state = STATE_END;
						break;
					}
					waitForVblank();
					drawImage(tony.y, tony.x, 28, 10, background);
					drawImage(0, Pipe1.x, 15,160,background);
					drawImage(0, Pipe2.x, 15,160,background);
					drawImage(0, Pipe3.x, 15,160,background);
					drawImage(0, Pipe4.x, 15,160,background);
					drawImage(0, Pipe5.x, 15,160,background);


					//movement
					//up
					if (KEY_DOWN_NOW(BUTTON_UP) && (tony.y > (unsigned int) top_limit))
					{
						tony.y--;
						// delay(1);
					}
					//down
					if (KEY_DOWN_NOW(BUTTON_DOWN))
					{
						tony.y++;
//						delay(1);
					}
					//right
					if (KEY_DOWN_NOW(BUTTON_RIGHT) && (tony.x < (unsigned int) right_limit))
					{
						tony.x++;
//						delay(1);
					}
					//left
					if (KEY_DOWN_NOW(BUTTON_LEFT) && (tony.x > (unsigned int) left_limit))
					{
						tony.x--;
//						delay(1);
					}


					//if the bird is touching the ground
					if (tony.y > (unsigned int) bot_limit) {
						state = STATE_END;
						break;
					}

					//move the pipes to the left
					//if the pipes are going past the screen, replace them to x = 600
					Pipe1.x--;
					if ((signed int) Pipe1.x + 15 < 0)
					{
						Pipe1.x = 600;
					}

					// drawPipe(Pipe2.y, Pipe2.x, false);
					Pipe2.x--;
					if ((signed int) Pipe2.x + 15 < 0)
					{
						Pipe2.x = 600;
					}
					// drawPipe(Pipe3.y, Pipe3.x, false);
					Pipe3.x--;
					if ((signed int) Pipe3.x + 15 < 0)
					{
						Pipe3.x = 600;
					}
					// drawPipe(Pipe4.y, Pipe4.x, false);
					Pipe4.x--;
					if ((signed int) Pipe4.x + 15 < 0)
					{
						Pipe4.x = 600;
					}
					// drawPipe(Pipe5.y, Pipe5.x, false);
					Pipe5.x--;
					if ((signed int) Pipe5.x + 15 < 0)
					{
						Pipe5.x = 600;
					}
					// waitForVblank();
					// drawImage(0,0,240,160,background);

					score++;





				}
			}
			break;



		case STATE_END:
			drawImage(0,0,240,160,gameover);
			drawString(135, 65, "Your Final Score: ", RED);
	        drawString(135, 168, result, RED);
			if (KEY_DOWN_NOW(BUTTON_SELECT))
			{
				state = STATE_ONE;
			}
			break;
			
		}
	}


	return 0;






}
// Delay for about n tenths of a second

void delay(int n) {
		int x = 0;
		for(int i = 0; i < n*8000; i++) {
			x++;
		}
	}

void waitForVblank() {
	while(*(volatile unsigned short *)SCANLINECOUNTER > 160);
	while(*(volatile unsigned short *)SCANLINECOUNTER < 160);
}



void drawPipe(int col, int width, int height) {
	if (col < 225) {
		int row = 160-height;
		//bottom pipe
		for (int r = 0; r < height; r++) {
			DMA[3].src = &green;
       		DMA[3].dst = videoBuffer + OFFSET(row + r, col, 240);
        	DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
        }
        //top pipe
        	row-=40;
        for (int r = 0; r < row; r++)
        {
        	DMA[3].src = &green;
       		DMA[3].dst = videoBuffer + OFFSET(row-r, col, 240);
        	DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;

			}

		}
	}

