#include<iostream>
#include<math.h>
#include<string>
#include<algorithm>
#include<windows.h>
#include"string_operation.h"

using namespace std;


// divide and conquer
string divideConquer(string x, string y);


int main()
{
    // time clock
    LARGE_INTEGER cpuFreq;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
    QueryPerformanceFrequency(&cpuFreq);
    QueryPerformanceCounter(&startTime);

    double runTime=0;
    QueryPerformanceCounter(&startTime);

    string x, y;
    cin >> x >> y;
    string ans = divideConquer(x, y);
    cout << "x multiply y: " << ans << endl;
    cout << "calculate answer in " << runTime << "s." << endl;
}


// 分治法
string divideConquer(string x, string y) {
    if(x == "0" || y == "0")
        return "0";
    else if (x.length() <= 10 || y.length() <= 10)
        return str_multiply(x, y);
    else {
        // calculate digit for x and y
        int pow_x = x.length()/2;
        int pow_y = y.length()/2;
        //cout << x << " " << y << endl;

        // (A+B) * (C+D) = AC + AD + BC + BD
        string A="", B="", C="", D="";
        int i;
        for(i=0; i < x.length()-pow_x; i++)
            A.append(to_string(x[i]-'0'));
        if(A == "") A = "0";
        for(; i < x.length(); i++)
            B.append(to_string(x[i]-'0'));
        if(B == "") B = "0";
        for(i=0; i < y.length()-pow_y; i++)
            C.append(to_string(y[i]-'0'));
        if(C == "") C = "0";
        for(; i < y.length(); i++)
            D.append(to_string(y[i]-'0'));
        if(D == "") D = "0";

        string AC = str_pow(divideConquer(A, C), pow_x+pow_y);
        string A10_B = str_minus(str_pow(A, pow_x), B);
        string C10_D = str_minus(str_pow(C, pow_y), D);
        string BD = divideConquer(B, D);

        /*
        cout << endl << "calculate:" << x << " " << y << endl;
        cout << pow_x << ": " << A << " " << B << " " << pow_y << ": " << C << " " << D << endl;
        cout << "10A: " << str_pow(A, pow_x) << " A10^-B:" << str_minus(str_pow(A, pow_x), B) << endl;
        cout << "10B: " << str_pow(C, pow_y) << " B10^-D:" << str_minus(str_pow(C, pow_y), D) << endl;
        cout << AC << " " << BD << " " << A10_B << " " << C10_D << endl;
        cout << str_add( str_add(AC, AC), str_add(BD, BD) ) << " "
            << str_multiply(A10_B, C10_D) << " "
            << str_minus( str_add( str_add(AC, AC), str_add(BD, BD) ) , divideConquer(A10_B, C10_D) ) << endl;
        */
        return str_minus( str_add( str_add(AC, AC), str_add(BD, BD) ) , str_multiply(A10_B, C10_D) );
        return str_minus( str_add( str_add(AC, AC), str_add(BD, BD) ) , divideConquer(A10_B, C10_D) );
    }
}