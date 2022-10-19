#include <iostream>
#include <cmath>
#include <cstring>
#include <unistd.h>

using namespace std;

float A, B, C;
float x, y, z;
float ooz;
int xp, yp;
int idx;

float cubeWidth = 10;
int width = 160;
int height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backGroundASCIICode = ' ';
int distanceCam = 60;
float K1 = 40;

float incrementSpeed = 0.6;

float calcX(int i, int j, int k){
    return  j * sin(A) * cos(C) - k * cos(A) * sin(B) * cos(C) +
            j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calcY(int i, int j, int k){
    return  j * cos(A) * cos(C) + k * sin(A) * cos(C) -
            j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
            i * cos(B) * sin(C);
}

float calcZ(int i, int j, int k){
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calcSurface(float cubeX, float cubeY, float cubeZ, int ch){
    x = calcX(cubeX,cubeY, cubeZ);
    y = calcY(cubeX,cubeY, cubeZ);
    z = calcZ(cubeX,cubeY, cubeZ) + distanceCam;

    ooz = 1/z;
    xp = (int)(width/2 + K1 * ooz * x *2);
    yp = (int)(height/2 + K1 * ooz * y *2);

    idx = xp + yp  * width;
    if (idx >= 0 && idx < width * height)
    {
        if (ooz > zBuffer[idx])
        {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main() {
    printf("\x1b[2J");

    while(1){
        memset(buffer, backGroundASCIICode, width * height);
        memset(zBuffer, 0, width * height * 4);
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed)
        {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed)
            {
                calcSurface(cubeX, cubeY, -cubeWidth, '#');
            }
        }
        printf("\x1b[H");
        for (int k  = 0; k < width * height; k++)
        {
            putchar(k % width ? buffer[k] : 10);
        }
        
        A += 0.05;
        B += 0.05;
        usleep(8000 * 2);
    }

    return 0;
}
