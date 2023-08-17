#include<iostream>
#include<vector>
#include <windows.h>

#define rest(x, size) ((x+size)%size)

using namespace std;


void round_robin(int size);


int main()
{
    // time clock
    LARGE_INTEGER cpuFreq;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
    QueryPerformanceFrequency(&cpuFreq);
    QueryPerformanceCounter(&startTime);


    int size;
    while(1) {
        cout << "Please input the size of participants.\n";
        cin >> size;

        QueryPerformanceCounter(&startTime);
        round_robin(size);
        QueryPerformanceCounter(&endTime);
        double runTime = ((endTime.QuadPart - startTime.QuadPart)*1.0f / cpuFreq.QuadPart);
        cout << "Calculate in " << runTime << "s.\n" << endl;
    }
    

    return 0;
}


void round_robin(int size)
{
    // basic args: row, column ------------------------------------------------
    if(size <= 2) {
        cout << "\t1\t2\n------------------------\n\t2\t1" << endl;
        return;
    }
    int row=size, column=size;
    if(size&1)
        row = size+1;

    // generate ---------------------------------------------------------------
    // allocate space
    int** ans;
    ans = new int*[row];
    for(int i=0; i < row; i++) {
        ans[i] = new int[column];
        for(int j=0; j < column; j++)
            ans[i][j] = 0;
    }
    for(int i=0; i < column; i++)
        ans[0][i] = i+1;

    // odd size
    if(size&1) {
        int index_left, index_right;
        for(int i=0; i < size; i++) {
            index_left = i;
            index_right = rest(i+1, column);
            
            while(index_left != index_right) {
                ans[i+1][index_left] = index_right+1;
                ans[i+1][index_right] = index_left+1;
                index_left = rest(index_left-1, size);
                index_right = rest(index_right+1, size);
            }
        }
    }

    // even size
    else {
        int index_left, index_right;
        for(int i=0; i < size-1; i++) {
            index_left = i;
            index_right = rest(i+1, size);
            
            do {
                ans[i+1][index_left] = index_right+1;
                ans[i+1][index_right] = index_left+1;
                index_left = rest(index_left-1, size);
                index_right = rest(index_right+1, size);
            } while(index_left != index_right-1);
        }
    }

    /*
    // output -- first line
    for(int i=0; i < column; i++)
        cout << "\t" << i+1;
    cout << endl;

    // output -- "--------"
    for(int i=0; i < column+1; i++)
        cout << "--------";
    cout << endl;

    // output -- table
    for(int i=1; i < row; i++) {
        for(int j=0; j < column; j++)
            cout << "\t" << ans[i][j];
        cout << endl;
    }
    */

}