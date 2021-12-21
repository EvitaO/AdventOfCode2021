#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<numeric>
#include <algorithm>

int version = 0;
unsigned long long result = 0;

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

unsigned long long   convertBinary(std::string str){
    return strtoull(str.c_str(), NULL, 2);
}

int    openPackets(std::string &line){
    int x;
    if (line[0] == '0'){
        x = convertBinary(line.substr(1,15).c_str());
        line.erase(0,16);
    }
    else if (line[0] == '1'){
        x = convertBinary(line.substr(1,11).c_str()) * -1;
        line.erase(0,12);
    }
    return x;
}

unsigned long long     literalValue(std::string &str){
    std::string         lv;
    std::string         tmp;
    for (int i = 0; str[i] == '1'; ){
        lv += str.substr(1, 4);
        str.erase(0,5);
    }
    lv += str.substr(1, 4);
    str.erase(0,5);

    return convertBinary(lv);
}

bool    onlyzero(std::string line){
    for (int i = 0; i < line.size(); i++){
        if (line[i] != '0')
            return false;
    }
    return true;
}

unsigned long long    processID(std::vector<unsigned long long>  res, int id){
    unsigned long long sum = 0;
    if (id == 0){
        for (auto i : res)
            sum += i;
        return sum;
    }
    else if (id == 1){
        sum = res[0];
        for (int i = 1; i < res.size(); i++){
            sum *= res[i];
        }
        return sum;
    }
    else if (id == 2){
        for (auto i : res){
            if (sum == 0)
                sum = i;
            else if (i < sum)
                sum = i;
        }
        return sum;
    }
    else if (id == 3){
        for (auto i : res){
            if (i > sum)
                sum = i;
        }
        return sum;
    }
    else if (id == 5){
        if (res[0] > res[1])
            return 1;
        return 0;
    }
    else if (id == 6){
        if (res[0] < res[1])
            return 1;
        return 0;
    }
    else if (id == 7){
        if (res[0] == res[1])
            return 1;
        return 0;
    }
}

void    process(std::string &line){
    version += std::stoi(line.substr(0,3).c_str(), 0, 2);
    line.erase(0, 3);
    int id = std::stoi(line.substr(0,3).c_str(), 0, 2);
    line.erase(0, 3);
    if (id == 4){
        result = literalValue(line);
        // return ;
    }
    else {
        int length_id = openPackets(line);
        std::vector<unsigned long long>    res;
        if (length_id < 0){
            while (length_id < 0){
                process(line);
                res.push_back(result);
                length_id++;
            }
        }
        else{
            int tmp = line.size();
            std::cout << length_id << "=" << std::endl;
            int test = 0;
            while(length_id > 0){
                process(line);
                res.push_back(result);
                length_id -= (tmp - line.size());
                test += tmp - line.size();
                tmp = line.size();
            }
            std::cout << test << "?" << std::endl;
        }
        result = processID(res, id);
        // return ;
    }    
}

int     main(int argc, char **argv){
    std::string         line;
    readfile(argv[1], line);
    convertString(line);
    process(line);
    std::cout << version << std::endl;
    std::cout << result << std::endl;
}