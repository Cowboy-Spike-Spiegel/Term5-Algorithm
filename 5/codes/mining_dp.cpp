#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>


int Mining(int** const data, int size);
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
            data[i] = new int[i+1];
            for(int j=0; j <= i; j++)
                fin >> data[i][j];
        }
        fin.close();

    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f / cpuFreq.QuadPart);
    std::cout << "Get data in " << runTime << "s." << std::endl;

    QueryPerformanceCounter(&startTime);
    // traverse with violence
        int ans = Mining(data, size);
        std::cout << "Answer is " << ans << ".\n";

    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f  / cpuFreq.QuadPart);
    std::cout << "Size: " << size << ", calculate answer in " << runTime << "s." << std::endl;

    for(int i=0; i<size; i++)
        delete data[i];
    delete data;
    return 0;
}

int Mining(int** const data, int size) {
    // allocate dp space depend on the last line, and initialize
    int* dp = new int[size];
    dp[0] = data[0][0];
    //std::cout  << "\t" << dp[0] << "\n";

    for(int i=1; i < size; i++) {
        // the right
        dp[i] = dp[i-1]+data[i][i];
        // the remain
        for(int j=i-1; j >= 1; j--)
            dp[j] = Max(dp[j-1], dp[j])+data[i][j];
        // the left
        dp[0] += data[i][0];

        // print
        /*
        for(int j=0; j < i; j++)
            std::cout << "\t" << dp[j];
        std::cout  << "\t" << dp[i] << "\n";
        */
    }

    int ans = dp[0];
    for(int i=1; i < size; i++)
        ans = Max(ans, dp[i]);
    delete dp;
    return ans;
}

int Max(int a, int b) {
    if(a > b)
        return a;
    return b;
}