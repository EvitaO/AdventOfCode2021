#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <vector>

void       readfile(char *str, std::vector<std::string> &x){
    std::fstream file(str);
    std::string line;
    while (getline(file, line))
        x.push_back(line);
    file.close();
}

void     getMostCommonBit(std::vector<int> &data, std::vector<std::string> &x){
    int size = strlen(x[0].c_str());
    for (int i =0; i < x.size(); i++){
        for (int j = 0; j < size; j++){
            if (x[i][j] == '1')
                data[j] += 1;
        }
    }
}

int     main(int argc, char **argv){
    std::vector<std::string>    x;
    readfile(argv[1], x);

    int strlength = strlen(x[0].c_str());
    std::string gamma(strlength, '0');
    std::string epsilon(strlength, '1');
    std::vector<int> data(strlength, 0);
    getMostCommonBit(data, x);
    for (int i = 0; i < strlength; i++){
        if (data[i] >= x.size()/2){
            gamma[i] = '1';
            epsilon[i] = '0';
        }
    }
    std::cout << stoi(gamma, 0, 2) * stoi(epsilon, 0, 2) << std::endl;
}