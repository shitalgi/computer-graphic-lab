#include <stdio.h>
#include <graphics.h>

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

#define X_MIN 100
#define Y_MIN 100
#define X_MAX 300
#define Y_MAX 300

int computeRegionCode(int x, int y) {
    int code = INSIDE;

    if (x < X_MIN)       // to the left of rectangle
        code |= LEFT;
    else if (x > X_MAX)  // to the right of rectangle
        code |= RIGHT;
    if (y < Y_MIN)       // below the rectangle
        code |= BOTTOM;
    else if (y > Y_MAX)  // above the rectangle
        code |= TOP;

    return code;
}

void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1 = computeRegionCode(x1, y1);
    int code2 = computeRegionCode(x2, y2);
    int accept = 0;

    while (1) {
        if (!(code1 | code2)) {
            accept = 1; // Both endpoints inside window
            break;
        } else if (code1 & code2) {
            // Both endpoints outside window, so reject
            break;
        } else {
            int x, y;
            int codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {           // point is above the clip rectangle
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            } else if (codeOut & BOTTOM) { // point is below the clip rectangle
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            } else if (codeOut & RIGHT) {  // point is to the right of clip rectangle
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            } else if (codeOut & LEFT) {   // point is to the left of clip rectangle
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeRegionCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeRegionCode(x2, y2);
            }
        }
    }

    if (accept) {
        // Drawing the line
        setcolor(RED);
        line(x1, y1, x2, y2);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Drawing the rectangle
    rectangle(X_MIN, Y_MIN, X_MAX, Y_MAX);

    // Line to be clipped
    int x1 = 50, y1 = 50, x2 = 400, y2 = 350;
    // Drawing the original line
    setcolor(WHITE);
    line(x1, y1, x2, y2);

    // Clipping the line
    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}

