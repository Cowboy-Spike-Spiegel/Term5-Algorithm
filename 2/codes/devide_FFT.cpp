#include<iostream>
#include<cstdio>
#include<cmath>
#include<time.h>

using namespace std;

const int MAXN = 1e7 + 10;
inline int read() 
{
    char c = getchar(); int x = 0, f = 1;
    while (c < '0' || c > '9') {
        if (c == '-')f = -1;
        c = getchar(); }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
const double Pi = acos(-1.0);


struct complex 
{
    double x, y;
    complex(double xx = 0, double yy = 0) { x = xx, y = yy; }
} a[MAXN], b[MAXN];


complex operator + (complex a, complex b) {
    return complex(a.x + b.x, a.y + b.y);
}
complex operator - (complex a, complex b) {
    return complex(a.x - b.x, a.y - b.y);
}
complex operator * (complex a, complex b) {
    return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

int N, M;
int l, r[MAXN];
int limit = 1;

void fast_fast_tle(complex* A, int type) 
{
    //Find out the sequence to iterate
    for (int i = 0; i < limit; i++)
        if (i < r[i]) swap(A[i], A[r[i]]);
    for (int mid = 1; mid < limit; mid <<= 1) { //Half the length of the interval to be combined
        complex Wn(cos(Pi / mid), type * sin(Pi / mid)); //Unit root
        for (int R = mid << 1, j = 0; j < limit; j += R) { //R is the length of the interval, and j is where it has been before
            complex w(1, 0); //power
            for (int k = 0; k < mid; k++, w = w * Wn) { //Enumerate the left half
                complex x = A[j + k], y = w * A[j + mid + k]; 
                A[j + k] = x + y;
                A[j + mid + k] = x - y;
            }
        }
    }
}


int main() {
    // read data
    cout << "Please input two numbers started with bit\n";
    int N = read(), M = read();
    for (int i = 0; i <= N; i++) a[i].x = read();
    for (int i = 0; i <= M; i++) b[i].x = read();

    // start timer
    clock_t start, end;
    start = clock(); 
    while (limit <= N + M) limit <<= 1, l++;
    for (int i = 0; i < limit; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    
    // start fft
    fast_fast_tle(a, 1);
    fast_fast_tle(b, 1);
    for (int i = 0; i <= limit; i++)
        a[i] = a[i] * b[i];
    fast_fast_tle(a, -1);
    string temp;
    int* ntemp = new int[N + M + 2];
    for (int i = 0;i < N + M + 2;i++)
        ntemp[i] = 0;
    int t = 0;
    for (int i = N + M; i >=0 ; i--) {
        t= (int)(a[i].x / limit + 0.5);
        ntemp[i] = (ntemp[i+1]+t) / 10;
        ntemp[i+1] = (ntemp[i+1] + t) % 10;
    }
    bool flag = true;
    for (int i = 0;i < N + M + 2;i++) {
        if (flag)
            ntemp[i] != 0 ? flag = false : flag = true;
        if(!flag)
            temp += ntemp[i]+'0';
    }

    // output time and answer
    cout << temp<<endl;
    end = clock();   
    cout << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}