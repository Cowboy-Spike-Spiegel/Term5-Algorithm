#include <iostream>
#include <fstream>
#include <time.h>


int MaxSubsequenceSum(const int data[], int size);


int main()
{
    // time clock
    clock_t start=clock(), finish;
    double duration;

    // get data_size and data in file
        int size;
        std::ifstream fin("../data/data_10000_1000.txt");
        fin >> size;

        int* data = new int[size];
        for(int i = 0; i<size; i++)
            fin >> data[i];
        fin.close();

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "Get data in " << duration << "s." << std::endl;

    start=clock();
    // traverse with violence
        int ans = MaxSubsequenceSum(data, size);
        std::cout << "Answer is " << ans << std::endl;

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "Size: " << size << ", calculate answer in " << duration << "s." << std::endl;

    delete data;
    return 0;
}


int MaxSubsequenceSum(const int data[], int size)
{
    int ans = 0;
    // generate start-i and end-j
    for(int i=0; i < size; i++) {
        // calculate sum
        int tmpAns = 0;
        for(int j=i; j < size; j++) {
            // add end
            tmpAns += data[j];
            // upgrade ans
            if(tmpAns > ans) {
                ans = tmpAns;
                // std::cout << i << " " << j << " " << ans << "\n";
            }
        }
    }
    return ans;
}