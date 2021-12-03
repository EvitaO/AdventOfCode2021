#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

void       readfile(char *str, std::map<std::string, int> &data){
    std::fstream file(str);
    std::string line;
    std::stringstream   l;
    int n;
    l << file.rdbuf();
    while (l >> line >> n){
        if (data.find(line) == data.end())
            data.insert(std::pair<std::string,int>(line, n));
        else
            data[line] += n;
    }
    file.close();
}

int     main(int argc, char **argv){
    std::map<std::string, int>   data;
    readfile(argv[1], data);
    std::cout << data["forward"]*(data["down"] - data["up"]) << std::endl;
}