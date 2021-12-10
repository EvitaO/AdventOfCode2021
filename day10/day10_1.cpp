#include <fstream>
#include <iostream>
#include <vector>


void    readfile(char *file, std::vector<std::string> &data){
    std::fstream        f(file);
    std::string          line;
    while(getline(f, line))
        data.push_back(line);
}

int    findcorrupt(std::string str, int *x){
    int res = 0;
    for (int i = *x + 1; i < str.size(); i++){
        if (str[i] == '(' || str[i] == '{' || str[i] == '[' || str[i] == '<'){
            res = findcorrupt(str, &i);
            if (res != 0)
                return res;
        }
        else if (str[*x] == '(' && str[i] == ')'){
            *x = i;
            return 0;
        }
        else if (str[*x] == '[' && str[i] == ']'){
            *x = i;
            return 0;
        }
        else if (str[*x] == '{' && str[i] == '}'){
            *x = i;
            return 0;
        }
        else if (str[*x] == '<' && str[i] == '>'){
            *x = i;
            return 0;
        }
        else if (str[i] == ')')
            return 3;
        else if (str[i] == ']')
            return 57;
        else if (str[i] == '}')
            return 1197;
        else if (str[i] == '>')
            return 25137;
    }
    return 0;
}


int     main(int argc, char **argv){
    std::vector<std::string>    data;
    readfile(argv[1], data);
    int         res = 0;
    int x = 0;
    for (std::string i : data){
        res += findcorrupt(i, &x);
        x = 0;
    }
    std::cout << res << std::endl;
}