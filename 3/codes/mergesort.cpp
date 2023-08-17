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

// mergesort-----------------------------------------------
void mergesort(DataType data[], SizeType size);
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
        std::ifstream fin("../data/ascend_100000_10000.txt");
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
    mergesort(data, size);
    QueryPerformanceCounter(&endTime);
    runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f  / cpuFreq.QuadPart);
    std::cout << "Size: " << size << ", calculate in " << runTime << "s." << std::endl;
    std::cout << "Compare: " << count_compare << std::endl;
    std::cout << "Insert: " << count_insert << std::endl;

    output(data, size);
    delete data;
    return 0;
}


void mergesort(DataType data[], SizeType size)
{
    // initialize queue with each unit(devide)
    std::queue<Pair> myQueue;
    for(SizeType i=0; i < size; i++) {
        Pair tmp;
        tmp.l_index = i, tmp.r_index = i;
        myQueue.push(tmp);
    }

    // merge
    SizeType l_left, l_right, r_left, r_right;
    DataType* tempArr = new DataType[size]; // memory temp merge
    while(myQueue.size() > 1) {

        // even: skip merging the first one------------------------------------
        count_compare++;
        if(myQueue.size()&1) {
            myQueue.push(myQueue.front());
            myQueue.pop();
        }
        SizeType times = myQueue.size()/2;

        for(SizeType i=0; i < times; i++) {
            // get index of start and end & push merged one--------------------
            l_left = myQueue.front().l_index;
            l_right = myQueue.front().r_index;
            myQueue.pop();
            r_left = myQueue.front().l_index;
            r_right = myQueue.front().r_index;
            myQueue.pop();
            Pair tmp;
            tmp.l_index = l_left, tmp.r_index = r_right;
            myQueue.push(tmp);

            // merge into tempArr(combine)-------------------------------------
            SizeType left = l_left, j=0;

            while(1) {
                count_compare++;        // l_left > l_right
                if(l_left > l_right)
                    break;
                
                count_compare++;        // r_left > r_right
                if(r_left > r_right)
                    break;
                
                count_compare++;        // l_left <= l_right, r_left <= r_right, data[l_left] < data[r_left]
                if(data[l_left] < data[r_left])
                    tempArr[j++] = data[l_left++];
                else
                    tempArr[j++] = data[r_left++];
            }
            
            while(1) {
                count_compare++;        // l_left <= l_right
                if(l_left > l_right)
                    break;
                tempArr[j++] = data[l_left++];
            }
            while(1) {
                count_compare++;        // r_left <= r_right
                if(r_left > r_right)
                    break;
                tempArr[j++] = data[r_left++];
            }

            // insert into data------------------------------------------------
            j=0;
            while(1) {
                if(left+j > r_right)
                    break;
                count_insert++;
                //std::cout << data[left+j] << " ";
                data[left+j++] = tempArr[j];
            }
            //std::cout << "\n";
        }
    }

    delete tempArr;
}


void output(DataType data[], SizeType size)
{
    std::ofstream fout("output.txt");
    fout << size << std::endl;
    for(SizeType i = 0; i<size; i++) {
        fout << data[i] << " ";
    }
} 