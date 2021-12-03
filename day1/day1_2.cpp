#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

void       readfile(char *str, std::vector<int> &x){
    std::fstream file(str);
    std::string line;
    while (getline(file, line))
        x.push_back(stoi(line));
    file.close();
}

int     main(int argc, char **argv){
    int i = 0;
    std::vector<int>    x;
    readfile(argv[1], x);
    int old = 0;
    for (int idx = 0; idx+2 < x.size(); idx++){
        x[idx] + x[idx+1] + x[idx+2] > old && old != 0 ? i++ : i = i;
        old = x[idx] + x[idx+1] + x[idx+2];
    }
    std::cout << i << std::endl;
}