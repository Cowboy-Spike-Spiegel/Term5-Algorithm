#include<iostream>
#include<vector>
#include <windows.h>

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


    // create devide path -----------------------------------------------------
    vector<int> devide; // devide size
    int cur = size;
    do {
        devide.push_back(cur);
        cur = (cur+1)/2;
    } while(cur > 2);


    // initialize as size 2 ---------------------------------------------------
    int** ans;
    ans = new int*[size+1];
    for(int i=0; i < size+1; i++) {
        ans[i] = new int[size+1];
        for(int j=0; j < size+1; j++)
            ans[i][j] = 0;
    }
    ans[0][0] = 1;
    ans[0][1] = 2;
    ans[1][0] = 2;
    ans[1][1] = 1;


    // start generate ---------------------------------------------------------
    int tmp_size = 2;
    for(int target_index=devide.size()-1; target_index >= 0; target_index--) {
        //cout << "devide = " << devide[target_index] << endl;
        /*
            generate answer is always even, but what we need perhaps be odd
            so generate odd devide, we should do:
                1. generate right && 0 unit inserting the rest couple-rival
                2. insert the rest lines with INPORTANT swap_insert
                3. clear last column and clear number need[target_index]
        */

        // 1 -- odd size to combine as even
        if(tmp_size&1) {
            // 1.1 -- generate right
            for(int i=0; i < tmp_size+1; i++) {
                for(int j = 0; j < tmp_size; j++) {
                    // 1.1.1 -- 0 to insert the rest rival( left 0-insert with relative right insert )
                    if(ans[i][j] == 0) {
                        ans[i][j] = j+1+tmp_size;
                        ans[i][tmp_size+j] = j+1;
                    }
                    // 1.1.2 -- normal add tmp_size moving to relative location
                    else
                        ans[i][tmp_size+j] = ans[i][j]+tmp_size;
                }
            }

            // 1.2 -- generate under, right-under
            for(int i=tmp_size+1; i < tmp_size*2; i++) {
                // 1.2.1 -- traverse into line = [tmp_size+2, tmp_size*2] for inserting all units
                for(int j=0; j < tmp_size; j++) {
                    /*
                        1.2.1.1 -- left index is i, calculate right index to swap_insert
                        THIS IS THE MOST IMPORTANT SOLUTION
                    */
                    int right_index = (i+j)%tmp_size+tmp_size;
                    
                    ans[i][j] = right_index+1;  // left insert
                    ans[i][right_index] = j+1;  // right insert
                }
            }
        }

        // 2 -- even size to combine as even
        else {
            // 2.1 -- generate right, under, right-under (scopy to the three square perhaps with adding tmp_size)
            for(int i=0; i < tmp_size; i++) {
                for(int j = 0; j < tmp_size; j++) {
                    ans[i][tmp_size+j] = ans[i][j] + tmp_size;  // right
                    ans[tmp_size+i][j] = ans[i][j] + tmp_size;  // under
                    ans[tmp_size+i][tmp_size+j] = ans[i][j];    // right-under
                }
            }
        }
        
        // 3 -- dgenerate size is even and delete something to match odd devide size
        if(devide[target_index]&1) {
            // 3.1 -- traverse into each line=devide[target_index]+1 for deleting
            for(int i=0; i < devide[target_index]+1; i++) {
                // 3.1.1 -- clear last column
                ans[i][devide[target_index]] = 0;
                
                // 3.1.2 -- clear number need[target_index]
                for(int j=0; j < devide[target_index]+1; j++)
                    if(ans[i][j] == devide[target_index]+1)
                        ans[i][j] = 0;
            }
        }
        
        // 4 -- refresh tmp_size
        tmp_size = devide[target_index];
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


    // delete memory
    for(int i=0; i < size+1; i++)
        delete ans[i];
    delete ans;
}