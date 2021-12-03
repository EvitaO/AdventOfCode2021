#include <fstream>
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
    for (int idx = 0; idx < x.size(); idx++)
        idx != 0 && x[idx] > x[idx - 1] ? i++ : i = i;
    std::cout << i << std::endl;
}