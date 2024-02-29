#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#define DELAY 10000 // Adjust speed of animation by changing this value

int main() {
    int gd = DETECT, gm;
    int x = 100, y = 100; // Initial position of the circle
    int dx = 5, dy = 3;   // Movement steps in x and y directions

    // Initialize graphics mode
    initgraph(&gd, &gm, "");

    while (!kbhit()) { // Continue animation until a key is pressed
        // Clear previous position of the circle
        cleardevice();

        // Update position of the circle
        x += dx;
        y += dy;

        // Draw the circle at the updated position
        circle(x, y, 30); // Change radius as needed

        // Delay to control animation speed
        delay(DELAY);

        // Boundary checking - if circle hits the screen boundary, change direction
        if (x >= getmaxx() || x <= 0) {
            dx = -dx;
        }
        if (y >= getmaxy() || y <= 0) {
            dy = -dy;
        }
    }

    // Close graphics mode
    closegraph();
    return 0;
}

