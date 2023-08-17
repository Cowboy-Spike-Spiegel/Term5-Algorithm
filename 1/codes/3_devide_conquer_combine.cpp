#include <iostream>
#include <fstream>
#include <windows.h>
#include <queue>

#define max(a,b) (((a) > (b)) ? (a) : (b))


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

    // initialize each queue unit for devide
    std::queue<int*> myQueue;
    for(int i=0; i < size; i++) {
        /*
            each unit has four respo:
            { ans, l_max, r_max, sum }
        */
        int* cur = new int[4];
        cur[0] = (data[i]>0) ? data[i] : 0;
        cur[1] = data[i];   // has one number at least
        cur[2] = data[i];   // has one number at least
        cur[3] = data[i];
        myQueue.push(cur);
    }

    // combine
    int capicity = myQueue.size();
    while(capicity > 1) {
        // size is odd, select first one to pop and push
        if(capicity&1) {
            myQueue.push(myQueue.front());
            myQueue.pop();
        }

        // select pair to combine
        for(int i=0; i < capicity/2; i++) {
            int* tmp_1 = myQueue.front();
            myQueue.pop();
            int* tmp_2 = myQueue.front();
            myQueue.pop();

            // generate { ans, l_max, r_max, sum } into tmp_1
            tmp_1[0] = max(tmp_1[0], tmp_2[0]);
            tmp_1[0] = max(tmp_1[0], tmp_1[2]+tmp_2[1]);
            tmp_1[1] = max(tmp_1[1], tmp_1[3]+tmp_2[1]);
            tmp_1[2] = max(tmp_2[2], tmp_2[3]+tmp_1[2]);
            tmp_1[3] = tmp_1[3] + tmp_2[3];

            // delete tmp_2 and push tmp_1
            delete tmp_2;
            myQueue.push(tmp_1);
        }

        capicity = myQueue.size();
    }

    ans = myQueue.front()[0];
    delete myQueue.front();
    return ans;
}