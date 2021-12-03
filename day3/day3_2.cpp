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

void     getMostCommonBit(std::vector<int> &commonbit, std::vector<std::string> &x){
    int size = strlen(x[0].c_str());
    for (int i =0; i < x.size(); i++){
        for (int j = 0; j < size; j++){
            if (x[i][j] == '1')
                commonbit[j] += 1;
        }
    }
}

void    checkCommonBit(std::vector<std::string> &oxygen, int bit, int index, int delimiter){
    for (int i = 0; i < oxygen.size();){
        if ((bit * 2 >= delimiter && oxygen[i][index] != '1') || (bit * 2 < delimiter && oxygen[i][index] != '0')){
            oxygen.erase(oxygen.begin()+i);
            i--;
        }     
        i++;
    }
}

void    checkNotCommonBit(std::vector<std::string> &co_2, int bit, int index, int delimiter){
    for (int i = 0; i < co_2.size();){
        if ((bit * 2 < delimiter && co_2[i][index] == '0') || (bit * 2 >= delimiter && co_2[i][index] == '1')){
            co_2.erase(co_2.begin()+i);
            i--;
        }       
        i++;
    }
}

int     main(int argc, char **argv){
    std::vector<std::string>    oxygen;
    readfile(argv[1], oxygen);
    std::vector<std::string>    co_2 = oxygen;

    int strlength = strlen(oxygen[0].c_str());

    std::vector<int> commonbit(strlength, 0);
    getMostCommonBit(commonbit, oxygen);

    std::vector<int> leastbit(strlength, 0);
    getMostCommonBit(leastbit, co_2);
    
    for (int i = 0; i < strlength; i++){
        if (oxygen.size() > 1)
            checkCommonBit(oxygen, commonbit[i], i, oxygen.size());
        if (co_2.size() > 1)
            checkNotCommonBit(co_2, leastbit[i], i, co_2.size());
        commonbit.assign(oxygen.size(), 0);
        leastbit.assign(co_2.size(), 0);
        getMostCommonBit(commonbit, oxygen);
        getMostCommonBit(leastbit, co_2);
    }
    std::cout << stoi(co_2[0], 0, 2) * stoi(oxygen[0], 0, 2) << std::endl;
}