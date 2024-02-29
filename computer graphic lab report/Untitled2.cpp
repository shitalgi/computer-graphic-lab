#include <stdio.h>
#include <graphics.h>

// Function to draw ellipse using Mid-point Ellipse drawing Algorithm
void drawEllipse(int x_center, int y_center, int rx, int ry) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x = 0, y = ry;
    int rxSquare = rx * rx;
    int rySquare = ry * ry;
    int twoRxSquare = 2 * rxSquare;
    int twoRySquare = 2 * rySquare;
    int p, px = 0, py = twoRxSquare * y;

    // Plot the initial point in each quadrant
    drawPixel(x_center + x, y_center + y);
    drawPixel(x_center - x, y_center + y);
    drawPixel(x_center + x, y_center - y);
    drawPixel(x_center - x, y_center - y);

    // Region 1
    p = rySquare - (rxSquare * ry) + (0.25 * rxSquare);
    while (px < py) {
        x++;
        px += twoRySquare;
        if (p < 0)
            p += rySquare + px;
        else {
            y--;
            py -= twoRxSquare;
            p += rySquare + px - py;
        }
        drawPixel(x_center + x, y_center + y);
        drawPixel(x_center - x, y_center + y);
        drawPixel(x_center + x, y_center - y);
        drawPixel(x_center - x, y_center - y);
    }

    // Region 2
    p = rySquare * (x + 0.5) * (x + 0.5) + rxSquare * (y - 1) * (y - 1) - rxSquare * rySquare;
    while (y > 0) {
        y--;
        py -= twoRxSquare;
        if (p > 0)
            p += rxSquare - py;
        else {
            x++;
            px += twoRySquare;
            p += rxSquare - py + px;
        }
        drawPixel(x_center + x, y_center + y);
        drawPixel(x_center - x, y_center + y);
        drawPixel(x_center + x, y_center - y);
        drawPixel(x_center - x, y_center - y);
    }

    closegraph();
}

// Function to draw a pixel at given x, y coordinates
void drawPixel(int x, int y) {
    putpixel(x, y, WHITE);
}

int main() {
    int x_center, y_center, rx, ry;
    printf("Enter the center of the ellipse (x y): ");
    scanf("%d %d", &x_center, &y_center);
    printf("Enter the major and minor axes (rx ry): ");
    scanf("%d %d", &rx, &ry);

    drawEllipse(x_center, y_center, rx, ry);

    return 0;
}






