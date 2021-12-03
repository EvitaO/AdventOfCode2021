#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

std::stringstream      readfile(char *str){
    std::fstream file(str);
    std::stringstream   l;
    l << file.rdbuf();
    return l;
}

void       calculate(std::stringstream l){
    std::string line;
    int x = 0, y = 0, aim = 0;
    for (int n = 0; l >> line >> n;){
        if (line == "forward"){
            x += n;
            y += aim * n;
        }
        else
            line == "up" ? aim -= n : aim += n;
    }
    std::cout << x * y << std::endl;
}

int     main(int argc, char **argv){
    calculate(readfile(argv[1]));
}