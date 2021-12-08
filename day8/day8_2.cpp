#include <fstream>
#include <iostream>
#include <vector>

std::string getnum(std::vector<std::string> &numbers, int x){
    for (int i = 0; i < numbers.size(); i++){
        if (numbers[i].size() == x){
            return numbers[i];
        }
    }
}

void        setspecials(std::vector<std::string> &numbers, std::vector<std::string> &table){
    table[1] = getnum(numbers, 2);
    table[4] = getnum(numbers, 4);
    table[7] = getnum(numbers, 3);
    table[8] = getnum(numbers, 7);
}

bool        check6(std::string str, std::vector<std::string> &table){
    std::string     six = table[6];
    std::string     one = table[1];
    char            x;
    for (int i = 0; i < six.size(); i++){
        if (one.find(six[i]) != std::string::npos){
            x = six[i];
        }
    }
    if (str.find(x) != std::string::npos)
        return true;
    return false;
}

bool        check9(std::string str, std::vector<std::string> &table){
    std::string     four = table[4];
    for (int i = 0; i < four.size(); i++){
        if (str.find(four[i]) == std::string::npos)
            return false;
    }
    return true;
}

void        set3(std::vector<std::string> &numbers, std::vector<std::string> &table){
    for (std::string i : numbers){
        if (strlen(i.c_str()) == 5){
            if (i.find(table[1][0]) != std::string::npos && i.find(table[1][1]) != std::string::npos)
                table[3] = i;
        }
    }
}

void        set6(std::vector<std::string> &numbers, std::vector<std::string> &table){
    for (std::string i : numbers){
        if (strlen(i.c_str()) == 6){
            if (i.find(table[1][0]) == std::string::npos || i.find(table[1][1]) == std::string::npos)
                table[6] = i;
        }
    }
}

void        set5_2(std::vector<std::string> &numbers, std::vector<std::string> &table){
    for (std::string i : numbers){
        if (strlen(i.c_str()) == 5){
            if (check6(i, table) && i != table[3])
                table[5] = i;
            else if (i != table[3])
                table[2] = i;
        }
    }
}

void        set9_0(std::vector<std::string> &numbers, std::vector<std::string> &table){
    for (std::string i : numbers){
        if (strlen(i.c_str()) == 6){
            if (check9(i, table) && i != table[6])
                table[9] = i;
            else if (i != table[6])
                table[0] = i;
        }
    }
}

void        filltable(std::vector<std::string> &table, std::vector<std::string> &numbers){
    setspecials(numbers, table);    
    set3(numbers,table);
    set6(numbers, table);
    set5_2(numbers, table);
    set9_0(numbers, table);
}

bool        equal(std::string a, std::string b){
    if (a.size() == b.size()){
        for (int i = 0; i < a.size(); i++){
            if (b.find(a[i]) == std::string::npos)
                return false;
        }
        return true;
    }
    return false;
}

int         searchvalue(std::string x, std::vector<std::string> &table){
    for (int i = 0; i < table.size();i++){
        if (equal(table[i], x))
            return i;
    }
}

int         getanswer(std::string answer, std::vector<std::string> &table){
    std::vector<std::string>    numbers;
    int                         ret = 0;
    while (answer.find(" ") != std::string::npos){
        int pos = answer.find(" ");
        numbers.push_back(answer.substr(0, pos));
        answer.erase(0,pos+1);
    }
    numbers.push_back(answer);
    for (int i = 0; i < numbers.size(); i++){
        ret += searchvalue(numbers[i], table);
        if (i + 1 < numbers.size())
            ret = ret * 10;
    }
    return ret;
}

int         getvalues(std::string answer, std::string input){
    std::vector<std::string>   numbers;
    std::vector<std::string>   table(10);
    while (input.find(" ") != std::string::npos){
        int pos = input.find(" ");
        numbers.push_back(input.substr(0, pos));
        input.erase(0,pos+1);
    }
    filltable(table, numbers);
    return getanswer(answer, table);
}

void        readfile(char *file, int &i){
    std::fstream        f(file);
    std::string         line;
    std::string         line_answer;

    while (getline(f, line)){
        line_answer = line.substr(line.find("|")+2, strlen(line.c_str()));
        line = line.substr(0,line.find("|"));
        i += getvalues(line_answer, line);
        line = "";
    }
}

int         main(int argc, char **argv){
    int i = 0;
    readfile(argv[1], i);
    std::cout << i << std::endl;
}