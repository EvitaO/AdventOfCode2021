#include <fstream>
#include <iostream>
#include <vector>


void    readfile(char *file, std::vector<int> &fishes){
    std::fstream    f(file);
    std::string     line;
    getline(f, line);
    f.close();
    int pos = 0;
    while (line.find(",") != std::string::npos){
        pos = line.find(",");
        fishes.push_back(stoi(line.substr(0, pos)));
        line.erase(0, pos+1);
    }
    fishes.push_back(stoi(line.substr(0, strlen(line.c_str()))));
}

void    simulation(std::vector<int> &fishes){
    long len = fishes.size();
    for (long i = 0; i < len; i++){
        fishes[i]--;  
        if (fishes[i] < 0){
            fishes[i] = 6;
            fishes.push_back(8);
        }
    }
}

int     main(int argc, char **argv){
    std::vector<int>    fishes;
    readfile(argv[1], fishes);
    for (int i = 0; i < 80; i++)
        simulation(fishes);
    std::cout << fishes.size() << std::endl;
}