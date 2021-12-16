#include <iostream>
#include <fstream>
#include <string>

int version = 0;

void    readfile(char *file, std::string &line){
    std::fstream    f(file);
    getline(f, line);
    f.close();
}

void    convertString(std::string &line){
    std::string         bit;
    for(int i = 0; i < line.size();i++){
        switch(line[i]){
            case '0':
                bit += "0000";
                break;
            case '1':
                bit += "0001";
                break;
            case '2':
                bit += "0010";
                break;
            case '3':
                bit += "0011";
                break;
            case '4':
                bit += "0100";
                break;
            case '5':
                bit += "0101";
                break;
            case '6':
                bit += "0110";
                break;
            case '7':
                bit += "0111";
                break;
            case '8':
                bit += "1000";
                break;
            case '9':
                bit += "1001";
                break;
            case 'A':
                bit += "1010";
                break;
            case 'B':
                bit += "1011";
                break;
            case 'C':
                bit += "1100";
                break;
            case 'D':
                bit += "1101";
                break;
            case 'E':
                bit += "1110";
                break;
            case 'F':
                bit += "1111";
                break;
        }
    }
    line = bit;
}

int    toBinary(std::string str){
    int         num = strtoull(str.c_str(), NULL, 2);
    return num;
}

int    openPackets(std::string &line){
    int x;
    if (line[0] == '0'){
        x = toBinary(line.substr(1,15).c_str());
        line.erase(0,16);
    }
    else if (line[0] == '1'){
        x = toBinary(line.substr(1,11).c_str()) * -1;
        line.erase(0,12);
    }
    return x;
}

void     literalValue(std::string &str){
    std::string         lv;
    std::string         tmp;
    for (int i = 0; str[i] == '1'; ){
        lv += str.substr(1, 4);
        str.erase(0,5);
    }
    lv += str.substr(1, 4);
    str.erase(0,5);
}

bool    onlyzero(std::string line){
    for (int i = 0; i < line.size(); i++){
        if (line[i] != '0')
            return false;
    }
    return true;
}

void    process(std::string &line){
    if (onlyzero(line)){
        std::cout << version << std::endl;
        exit(1);
    }
    version += std::stoi(line.substr(0,3).c_str(), 0, 2);
    line.erase(0, 3);
    int id = std::stoi(line.substr(0,3).c_str(), 0, 2);
    line.erase(0, 3);
    if (id == 4){
        literalValue(line);
        return;
    }
    else {
        int length_id = openPackets(line);
        if (length_id < 0){
            length_id = length_id * -1;
            while (length_id > 0){
                process(line);
                length_id--;
            }
        }
        else{
            int tmp = line.size();
            while(length_id > 0){
                process(line);
                length_id -= (tmp - line.size());
            }
        }
    }
    if (!line.empty() && !onlyzero(line))
        process(line);
}

int     main(int argc, char **argv){
    std::string         line;
    readfile(argv[1], line);
    convertString(line);
    process(line);
}