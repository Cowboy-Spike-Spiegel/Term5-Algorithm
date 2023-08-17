#include <iostream>
#include <fstream>
#include <windows.h>
#include <queue>


// data type define----------------------------------------
#define DataType int
#define SizeType int
#define CountType long
#define TimeType double

// global variables----------------------------------------
CountType count_compare=0;
CountType count_insert=0;


// struct of pair------------------------------------------
typedef struct {
    SizeType l_index;
    SizeType r_index;
} Pair, *PairPtr;

// quicksort-----------------------------------------------
void quicksort(DataType data[], SizeType size);
// output to file------------------------------------------
void output(DataType data[], SizeType size);


int main()
{
    // time clock
    LARGE_INTEGER cpuFreq;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
    QueryPerformanceFrequency(&cpuFreq);
    QueryPerformanceCounter(&startTime);

    TimeType runTime=0;

    // get data_size and data in file------------------------------------------
        SizeType size;
        std::ifstream fin("../data/data_100000_10000.txt");
        fin >> size;

        DataType* data = new DataType[size];
        for(SizeType i = 0; i<size; i++)
            fin >> data[i];
        fin.close();

    // get data----------------------------------------------------------------
    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f / cpuFreq.QuadPart);
    std::cout << "Get data in " << runTime << "s." << std::endl;

    // start sort--------------------------------------------------------------
    QueryPerformanceCounter(&startTime);
    quicksort(data, size);
    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f  / cpuFreq.QuadPart);
    std::cout << "Size: " << size << ", calculate in " << runTime << "s." << std::endl;
    std::cout << "Compare: " << count_compare << std::endl;
    std::cout << "Insert: " << count_insert << std::endl;

    output(data, size);
    delete data;
    return 0;
}


void quicksort(DataType data[], SizeType size)
{
    // initialize
    std::queue<Pair> myQueue;
    Pair first;
    first.l_index = 0, first.r_index = size-1;
    myQueue.push(first);

    // sort
    SizeType left, right, i, j;
    while(myQueue.size()) {
        left = myQueue.front().l_index;
        right = myQueue.front().r_index;
        i = left, j = right;
        myQueue.pop();

        int x = data[left]; // fisrt as 
        while (i < j)
        {
            // right->left
            while(1) {
                count_compare++;
                if(i >= j)
                    break;
                count_compare++;
                if(data[j] < x)
                    break;
                j--;  
            }
            count_compare++;
            if(i < j)
             {
                data[i++] = data[j];
                count_insert++;
            }
            // left->right
            while(1) {
                count_compare++;
                if(i >= j)
                    break;
                count_compare++;
                if(data[i] >= x)
                    break;
                i++;
            }
            count_compare++;  
            if(i < j) {
                data[j--] = data[i];
                count_insert++;
            }
        }
        // insert the last one
        data[i] = x;
        count_insert++;

        // create two pair into queue
        count_compare++;
        if(i-1 > left) {
            Pair l_pair;
            l_pair.l_index = left, l_pair.r_index = i-1;
            myQueue.push(l_pair);
        }
        count_compare++;
        if(i+1 < right) {
            Pair r_pair;
            r_pair.l_index = i+1, r_pair.r_index = right;
            myQueue.push(r_pair);
        }
    }
}


void output(DataType data[], SizeType size)
{
    std::ofstream fout("output.txt");
    fout << size << std::endl;
    for(SizeType i = 0; i<size; i++) {
        fout << data[i] << " ";
    }
}