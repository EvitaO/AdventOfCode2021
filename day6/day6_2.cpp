#include <fstream>
#include <iostream>
#include <vector>


void    readfile(char *file, std::vector<long long> &fishes){
    std::fstream    f(file);
    std::string     line;
    getline(f, line);
    f.close();
    int pos = 0;
    while (line.find(",") != std::string::npos){
        pos = line.find(",");
        fishes[stoi(line.substr(0, pos))] += 1;
        line.erase(0, pos+1);
    }
    fishes[stoi(line.substr(0, strlen(line.c_str())))] += 1;
}

void    simulation(std::vector<long long> &fishes){
    std::vector<long long>    tmp(9, 0);
    for (int i = 0; i < fishes.size(); i++){
        if (i == 0){
            long long x = fishes[i];
            tmp[6] += x;
            tmp[8] += x;
        }
        else{
            long long x = fishes[i];
            tmp[i-1] += x;
        }
    }
    for (int i = 0; i < tmp.size(); i++)
        fishes[i] = tmp[i];
}

int     main(int argc, char **argv){
    std::vector<long long>    fishes(9, 0);
    readfile(argv[1], fishes);
    for (int i = 0; i < 256; i++)
        simulation(fishes);
    long long fish = 0;
    for (int i = 0; i < fishes.size(); i++)
        fish += fishes[i];
    std::cout << fish << std::endl;
}