#include <iostream>
#include <cmath>

using namespace std;

float A, B, C;

float cubeWidth = 10;
int width = 160;
int height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backGroundASCIICode = ' ';

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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
