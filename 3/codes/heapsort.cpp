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
CountType count_swap=0;


// swap with count-----------------------------------------
void swap(DataType* a, DataType* b);
// create big heap-----------------------------------------
void adjust(DataType data[], SizeType len, SizeType index);
// heapsort------------------------------------------------
void heapsort(DataType data[], SizeType size);
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
    heapsort(data, size);
    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f  / cpuFreq.QuadPart);
    std::cout << "Size: " << size << ", calculate in " << runTime << "s." << std::endl;
    std::cout << "Compare: " << count_compare << std::endl;
    std::cout << "Swap: " << count_swap << std::endl;

    output(data, size);
    delete data;
    return 0;
}


void swap(DataType* a, DataType* b)
{
    DataType tmp = *a;
    *a = *b;
    *b = tmp;
    count_swap++;
}

void adjust(DataType data[], SizeType len, SizeType index)
{
    SizeType left = 2*index + 1;    // index的左子节点
    SizeType right = 2*index + 2;   // index的右子节点
    
    SizeType maxIdx = index;
    count_compare += 3;             // left<len, right<len, maxIdx != index
    if(left<len) {
        count_compare++;            // data[left] > data[maxIdx]
        if(data[left] > data[maxIdx])
            maxIdx = left;
    }
    if(right<len) {
        count_compare++;            // data[right] > data[maxIdx]
        if(data[right] > data[maxIdx])
            maxIdx = right;
    }
    if(maxIdx != index) {
        swap(&data[maxIdx], &data[index]);
        adjust(data, len, maxIdx);
    }
}

void heapsort(DataType data[], SizeType size)
{
    // 构建大根堆（从最后一个非叶子节点向上）
    for(SizeType i=size/2 - 1; i >= 0; i--) {
        adjust(data, size, i);
    }
 
    // 调整大根堆
    for(SizeType i = size - 1; i >= 1; i--) {
        swap(&data[0], &data[i]);           // 将当前最大的放置到数组末尾
        adjust(data, i, 0);                 // 将未完成排序的部分继续进行堆排序
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