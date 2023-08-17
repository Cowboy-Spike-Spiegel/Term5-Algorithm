#include <iostream>
#include <fstream>
#include <direct.h> 
#include <time.h>
#include <math.h>

int main()
{
    // get path
    char   buffer[100];   
    getcwd(buffer, 100);
    std::string path;
    for(int i=0; buffer[i] != '\0'; i++)
        path.push_back(buffer[i]);
    std::cout << path << std::endl;


    // get parameters
    int upper, size;
    std::string name;
    std::cout << "Please input the upper of data:" << std::endl;
    std::cin >> upper;
    std::cout << "Please input the size of data:" << std::endl;
    std::cin >> size;
    std::cout << "Please input the name of file:" << std::endl;
    std::cin >> name;


    // generate
    path.append("\\lack_"+name+".txt");
    std::cout << path << std::endl;
    std::ofstream fout(path);
    
    fout << size << "\n";
    
    srand((unsigned int)time(NULL));
    int randomNum;
    for(int i=0; i < size; i++) {
        for(int j=0; j < i; j++) {
            randomNum=rand()%(upper)-((int)sqrt(upper));
            fout << randomNum << " ";
        }
        randomNum=rand()%(upper)-((int)sqrt(upper));
        fout << randomNum << "\n";
    }
    fout.close();

    return 0;
}