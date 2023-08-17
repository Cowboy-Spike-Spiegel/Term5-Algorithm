#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>


int Mining(int** const data, int size, int x);
int Max(int a, int b);


int main()
{
    // time clock
    LARGE_INTEGER cpuFreq;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
    QueryPerformanceFrequency(&cpuFreq);
    QueryPerformanceCounter(&startTime);

    double runTime=0;

    // get data_size and data in file
        std::string dataFileName;
        std::cout << "Please input the name of dataFile:\n";
        std::cin >> dataFileName;
        std::ifstream fin("../data/"+dataFileName+".txt");
        if(!fin) {
            std::cout << "File not exist.\n";
            exit(0);
        }

        int size;
        fin >> size;

        int** data = new int*[size];
        for(int i=0; i<size; i++) {
            data[i] = new int[size];
            for(int j=0; j <= i; j++)
                fin >> data[i][j];
        }
        fin.close();

    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f / cpuFreq.QuadPart);
    std::cout << "Get data in " << runTime << "s." << std::endl;

    // get x
        int x;
        std::cout << "Please input the value of x:\n";
        std::cin >> x;
        if(x < 1) {
            std::cout << "x is invalidt.\n";
            exit(0);
        }

    QueryPerformanceCounter(&startTime);
    // traverse with violence
        int ans = Mining(data, size, x);
        std::cout << "Answer is " << ans << ".\n";

    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f  / cpuFreq.QuadPart);
    std::cout << "Size: " << size << ", calculate answer in " << runTime << "s." << std::endl;

    for(int i=0; i<size; i++)
        delete data[i];
    delete data;
    return 0;
}

int Mining(int** const data, int size, int x) {

    // allocate dp space depend on the last line, and initialize
    int** dp = new int*[size];
    for(int i=0; i<size; i++) {
        dp[i] = new int[i+1];
        for(int j=0; j <= i; j++)
            dp[i][j] = 0;
    }
    dp[0][0] = data[0][0];  // has solved the first layer

    // start dp
    int i=0, j=0;
    while(i+1 < size) {
        // generate tmp detection layers = x
        if(i+x >= size-1)
            x = size-1-i;
        std::cout << "\nx=" << x << "\n";

        // generate 
        for(int s=1; s <= x; s++) {
            for(int t=0; t <= s; t++) {
                // the left
                if(j+t == 0)
                    dp[i+s][0] = dp[i+s-1][0]+data[i+s][0];
                // the right
                else if(j+t == i+s)
                    dp[i+s][i+s] = dp[i+s-1][i+s-1]+data[i+s][i+s];
                // the reamin
                else
                    dp[i+s][j+t] += Max(dp[i+s-1][j+t-1], dp[i+s-1][j+t])+data[i+s][j+t];
            }
        }

        // generate i and j (select the biggest one in last layer)
        i += x;
        int target_j = j;
        for(int t=1; t <= x; t++)
            if(dp[i][j+t] > dp[i][target_j])
                target_j = j+t;
        j = target_j;

        // print i, j and dp
        std::cout << "current position: i=" << i << ", j=" << j << "\n";
        for(int s=0; s < size; s++) {
            for(int t=0; t < s; t++)
                std::cout << "\t" << dp[s][t];
            std::cout << "\t" << dp[s][s] << "\n";
        }
    }

    // last layer for answer
    int ans = dp[i][j];
    delete dp;
    return ans;
}


int Max(int a, int b) {
    if(a > b)
        return a;
    return b;
}