#include <stdio.h>

#define MAX 10

void floodFill4(int screen[][MAX], int x, int y, int prevColor, int newColor) {
    if (x < 0 || x >= MAX || y < 0 || y >= MAX)
        return;
    if (screen[x][y] != prevColor)
        return;

    screen[x][y] = newColor;

    floodFill4(screen, x + 1, y, prevColor, newColor);
    floodFill4(screen, x - 1, y, prevColor, newColor);
    floodFill4(screen, x, y + 1, prevColor, newColor);
    floodFill4(screen, x, y - 1, prevColor, newColor);
}

void floodFill8(int screen[][MAX], int x, int y, int prevColor, int newColor) {
    if (x < 0 || x >= MAX || y < 0 || y >= MAX)
        return;
    if (screen[x][y] != prevColor)
        return;

    screen[x][y] = newColor;

    floodFill8(screen, x + 1, y, prevColor, newColor);
    floodFill8(screen, x - 1, y, prevColor, newColor);
    floodFill8(screen, x, y + 1, prevColor, newColor);
    floodFill8(screen, x, y - 1, prevColor, newColor);
    floodFill8(screen, x + 1, y + 1, prevColor, newColor);
    floodFill8(screen, x + 1, y - 1, prevColor, newColor);
    floodFill8(screen, x - 1, y + 1, prevColor, newColor);
    floodFill8(screen, x - 1, y - 1, prevColor, newColor);
}

int main() {
    int screen[MAX][MAX] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    int x = 3, y = 3, newColor = 2;
    int prevColor = screen[x][y];

    floodFill4(screen, x, y, prevColor, newColor);

    printf("4-connected flood fill result:\n");
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    }

    // Reset the screen for 8-connected flood fill
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            screen[i][j] = (screen[i][j] == newColor) ? prevColor : screen[i][j];
        }
    }

    floodFill8(screen, x, y, prevColor, newColor);

    printf("\n8-connected flood fill result:\n");
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    }

    return 0;
}

