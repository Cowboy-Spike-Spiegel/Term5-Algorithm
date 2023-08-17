#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>


void Mining(int** const data, int size, int i, int j, int sum, int& ans);

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
        int ans = data[0][0];
        int sum = ans;
        Mining(data, size, 0, 0, sum, ans);
        std::cout << "Answer is " << ans << ".\n";

    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f  / cpuFreq.QuadPart);
    std::cout << "Size: " << size << ", calculate answer in " << runTime << "s." << std::endl;

    for(int i=0; i<size; i++)
        delete data[i];
    delete data;
    return 0;
}

void Mining(int** const data, int size, int i, int j, int sum, int& ans) {
    if(i == size)
        return;
    
    // left
    if(data[i][j] > data[i][j+1]) {
        if(sum+data[i][j] > ans)
            ans = sum+data[i][j];
        Mining(data, size, i+1, j, sum+data[i][j], ans);
    }
    // right
    else if(data[i][j] < data[i][j+1]) {
        if(sum+data[i][j+1] > ans)
            ans = sum+data[i][j+1];
        Mining(data, size, i+1, j+1, sum+data[i][j], ans);
    }
    // left and right
    else {
        if(sum+data[i][j] > ans)
            ans = sum+data[i][j];
        Mining(data, size, i+1, j, sum+data[i][j], ans);
        Mining(data, size, i+1, j+1, sum+data[i][j], ans);
    }
}