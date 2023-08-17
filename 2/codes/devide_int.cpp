#include<iostream>
#include<math.h>
#include<string>
#include<windows.h>

using namespace std;

// 正负符号
#define SIGN(A) ((A > 0) ? 1 : -1)


// divide and conquer
int countDigit(int number);
int divideConquer(int X, int Y);


// string 


int main() {
    // time clock
    LARGE_INTEGER cpuFreq;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
    QueryPerformanceFrequency(&cpuFreq);
    QueryPerformanceCounter(&startTime);

    double runTime=0;
    QueryPerformanceCounter(&startTime);

    int x, y;
    cin >> x >> y;
    cout << "x multiply y: " << divideConquer(x, y) << endl;
    cout << "calculate answer in " << runTime << "s." << endl;
}


int countDigit(int number) {
    int digit = 1;
    number = abs(number);
    while(number > 9) {
        digit++;
        number /= 10;
    }
    return digit;
}

// 分治法
int divideConquer(int X, int Y) {
    // calculate sign
    int sign = SIGN(X) * SIGN(Y);
    
    int x = abs(X);
    int y = abs(Y);
    //cout << x << y << endl;

    if(x == 0 || y == 0)
        return 0;
    else if (x < 10 && y < 10)
        return sign * x * y;
    else {
        // calculate digit for x and y
        int pow_x = pow(10, countDigit(X)/2);
        int pow_y = pow(10, countDigit(Y)/2);

        // (A+B) * (C+D) = AC + AD + BC + BD
        int A = x / pow_x;
        int B = x - A * pow_x;
        int C = y / pow_y;
        int D = y - C * pow_y;

        int AC = divideConquer(A, C)*pow_x*pow_y;
        int AD = divideConquer(A, D)*pow_x;
        int BC = divideConquer(B, C)*pow_y;
        int BD = divideConquer(B, D);

        return sign * (AC + AD + BC + BD);
    }
}
