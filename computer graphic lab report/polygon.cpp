#include <stdio.h>

typedef struct {
    float x, y;
} Point;

// Function to calculate the dot product of two points
float dotProduct(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

// Function to calculate the intersection point of two lines
Point getIntersection(Point p1, Point p2, Point cp1, Point cp2) {
    Point intersect;
    float d = (cp1.x - cp2.x) * (p1.y - p2.y) - (cp1.y - cp2.y) * (p1.x - p2.x);
    intersect.x = ((cp1.x * p2.y - cp1.y * p2.x) * (p1.x - p2.x) - (cp1.x - cp2.x) * (p1.x * p2.y - p1.y * p2.x)) / d;
    intersect.y = ((cp1.x * p2.y - cp1.y * p2.x) * (p1.y - p2.y) - (cp1.y - cp2.y) * (p1.x * p2.y - p1.y * p2.x)) / d;
    return intersect;
}

// Function to clip polygon against a single edge of the clipping window
int clipAgainstEdge(Point *input, int inputSize, Point cp1, Point cp2, Point *output) {
    int outputSize = 0;
    Point S = input[inputSize - 1];
    for (int i = 0; i < inputSize; i++) {
        Point E = input[i];
        if (dotProduct(cp2, E) >= dotProduct(cp2, cp1)) {
            if (dotProduct(cp1, S) < dotProduct(cp2, cp1))
                output[outputSize++] = getIntersection(S, E, cp1, cp2);
            output[outputSize++] = E;
        } else if (dotProduct(cp1, S) >= dotProduct(cp2, cp1)) {
            output[outputSize++] = getIntersection(S, E, cp1, cp2);
        }
        S = E;
    }
    return outputSize;
}

// Function to implement Sutherland-Hodgman clipping algorithm
void sutherlandHodgman(Point *polygon, int polySize, Point *clippingWindow, int winSize) {
    Point output[100]; // Assuming max output size
    int outputSize = polySize;
    Point *input = polygon;
    
    for (int i = 0; i < winSize; i++) {
        Point cp1 = clippingWindow[i];
        Point cp2 = clippingWindow[(i + 1) % winSize];
        outputSize = clipAgainstEdge(input, outputSize, cp1, cp2, output);
        input = output;
    }

    printf("Clipped polygon vertices:\n");
    for (int i = 0; i < outputSize; i++) {
        printf("(%.2f, %.2f)\n", output[i].x, output[i].y);
    }
}

int main() {
    Point polygon[] = {{50, 150}, {200, 50}, {350, 150}, {350, 300}, {250, 300}, {200, 250}, {150, 350}, {100, 250}, {100, 200}};
    int polySize = sizeof(polygon) / sizeof(polygon[0]);
    Point clippingWindow[] = {{100, 100}, {300, 100}, {300, 300}, {100, 300}};
    int winSize = sizeof(clippingWindow) / sizeof(clippingWindow[0]);
    
    sutherlandHodgman(polygon, polySize, clippingWindow, winSize);

    return 0;
}

