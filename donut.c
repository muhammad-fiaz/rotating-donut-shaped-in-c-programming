#include <stdio.h>   // Standard library
#include <string.h>  // Used for string operations
#include <math.h>    // Used for mathematical operations like sin, cos
#include <unistd.h>  // Used for usleep function

int main() {  // Main function
    float A = 0, B = 0;  // Rotation angles
    float i, j;
    int k;
    float z[1760];  // Z-buffer
    char b[1760];   // Buffer for storing the ASCII characters

    // Clear the screen and set cursor to home
    printf("\x1b[2J");

    for(;;) { // Infinite loop to keep the donut spinning
        memset(b, 32, 1760);  // Fill buffer with spaces
        memset(z, 0, 7040);   // Reset Z-buffer

        for(j = 0; j < 6.28; j += 0.07) {  // Loop over the donut's latitude
            for(i = 0; i < 6.28; i += 0.02) {  // Loop over the donut's longitude
                // Calculate the coordinates of the surface point
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

                // Check if the point is within bounds and update the buffers
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        // Return the cursor to the home position
        printf("\x1b[H");

        // Print the buffer
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;  // Increment the rotation angle A
            B += 0.00002;  // Increment the rotation angle B
        }
        usleep(30000);  // Sleep for a short period to control the rotation speed
    }

    return 0; // Return
}
