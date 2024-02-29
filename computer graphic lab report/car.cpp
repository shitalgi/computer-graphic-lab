#include <stdio.h>
#include <unistd.h> // for sleep function

#define SCREEN_WIDTH 80

// Function to print the car at the specified position
void printCar(int position) {
    printf("\033[2J\033[1;1H"); // Clear screen
    for (int i = 0; i < position; i++)
        printf(" ");
    printf("  ______\n");
    for (int i = 0; i < position; i++)
        printf(" ");
    printf(" /|_||_\\`.__\n");
    for (int i = 0; i < position; i++)
        printf(" ");
    printf("(   _    _ _\\_");
    for (int i = 0; i < SCREEN_WIDTH - position - 26; i++)
        printf(" ");
    printf("___\n");
}

int main() {
    int carPos = 0; // Initial position of the car

    while (1) { // Infinite loop for animation
        printCar(carPos);
        carPos = (carPos + 1) % SCREEN_WIDTH; // Update car position
        usleep(100000); // Adjust the delay (in microseconds) to control speed
    }

    return 0;
}

