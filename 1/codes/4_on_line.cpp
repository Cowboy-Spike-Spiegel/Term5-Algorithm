#include <iostream>
#include <fstream>
#include <windows.h>


int MaxSubsequenceSum(const int data[], int size);


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
        int size;
        std::ifstream fin("../data/data_10000_1000.txt");
        fin >> size;

        int* data = new int[size];
        for(int i = 0; i<size; i++)
            fin >> data[i];
        fin.close();

    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f / cpuFreq.QuadPart);
    std::cout << "Get data in " << runTime << "s." << std::endl;

    QueryPerformanceCounter(&startTime);
    // traverse with violence
        int ans = MaxSubsequenceSum(data, size);
        std::cout << "Answer is " << ans << std::endl;

    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f  / cpuFreq.QuadPart);
    std::cout << "Size: " << size << ", calculate answer in " << runTime << "s." << std::endl;

    delete data;
    return 0;
}


int MaxSubsequenceSum(const int data[], int size)
{
    int ans = 0;
    int sum = 0;
    // scan data
    for(int i=0; i < size; i++) {
        // calculate sum
        sum += data[i];
        // upgrade ans
        if(sum > ans)
            ans = sum;
        // throw away minus sequence
        if(sum < 0)
            sum = 0;
    }
    return ans;
}