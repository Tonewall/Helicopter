#include <stdint.h>
#include "img/bird.h"


typedef uint16_t Pixel;


typedef struct {
	unsigned int x,y;
} Vector;


// typedef struct {
// 	Vector top_left;
// 	Vector center;
// 	const Pixel* buffer;
// } Bird;
// Bird -> top_left.x = 40;
// Bird -> top_left.y = 80;

// Bird -> center.x = Bird -> top_left.x + 12;
// Bird -> center.y = Bird -> top_left.y + 8;
// Bird -> buffer = bird;

typedef struct {
    Vector top_left; // the coordinates of the top left vertex of the rectangle on the screen
    Vector size; // the size of the original image (width, height)
} Bird;
// typedef struct {
// 	Vector vertical;
// 	Vector horizontal;
// } Limit;

typedef struct {
    Vector size; 
    Pixel* buffer; 
} Screen;