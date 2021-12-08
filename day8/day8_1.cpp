#include <fstream>
#include <iostream>
#include <vector>

void        readfile(char *file, std::vector<int> &data){
    std::fstream        f(file);
    int                 pos;
    std::string         line;

    while (getline(f, line)){
        line = line.substr(line.find("|")+2, strlen(line.c_str()));
        pos = line.find(" ");
        while (pos != std::string::npos){
            std::string tmp = line.substr(0, pos);
            data[strlen(tmp.c_str())]++;
            line.erase(0, pos + 1);
            pos = line.find(" ");
        }
        data[strlen(line.c_str())]++;
        line = "";
    }
}

int         main(int argc, char **argv){
    std::vector<int>        data(8, 0);
    readfile(argv[1], data);

    int cnt = 0;
    for (int i = 0; i < data.size(); i++){
        if (i == 2 || i == 4 || i == 7 || i == 3)
            cnt += data[i];
    }
    std::cout << cnt << std::endl;
}