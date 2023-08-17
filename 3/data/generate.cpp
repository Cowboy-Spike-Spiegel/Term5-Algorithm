#include <iostream>
#include <fstream>
#include <direct.h> 
#include <time.h>

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
    int upper, size, type;
    std::string name;
    std::cout << "Please input the type of data: (1 for ascending, 2 for descending, else for disorder)" << std::endl;
    std::cin >> type;
    std::cout << "Please input the upper of data:" << std::endl;
    std::cin >> upper;
    std::cout << "Please input the size of data:" << std::endl;
    std::cin >> size;
    std::cout << "Please input the name of file:" << std::endl;
    std::cin >> name;
    


    // generate
    path.append("\\"+name+".txt");
    std::cout << path << std::endl;
    std::ofstream fout(path);
    
    fout << size << "\n";
    
    if(type == 1) {
        for(int i=0; i < size; i++) {
            fout << i-size/2 << " ";
        }
    }
    else if(type == 2) {
        for(int i=0; i < size; i++) {
            fout << size/2-i << " ";
        }
    }
    else {
        srand((unsigned int)time(NULL));
        for(int i=0; i < size; i++) {
            int randomNum=rand()%(2*upper)-upper;//产生[-upper, upper]的随机数
            fout << randomNum << " ";
        }
    }
    fout.close();

    return 0;
}