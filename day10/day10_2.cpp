#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


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

void     makecomplete(std::string str, int *x, std::string *tmp){
    int res = 0;
    for (int i = *x + 1; i < str.size(); i++){
        if (str[i] == '(' || str[i] == '{' || str[i] == '[' || str[i] == '<'){
            makecomplete(str, &i, tmp);
        }
        else if (str[*x] == '(' && str[i] == ')'){
            *x = i;
            return ;
        }
        else if (str[*x] == '[' && str[i] == ']'){
            *x = i;
            return;
        }
        else if (str[*x] == '{' && str[i] == '}'){
            *x = i;
            return;
        }
        else if (str[*x] == '<' && str[i] == '>'){
            *x = i;
            return;
        }
    }
    if (str[*x] == '<'){
        *tmp += '>';
        *x = str.size();
        return;
    }
    if (str[*x] == '('){
        *tmp += ')';
        *x = str.size();
        return;
    }
    if (str[*x] == '{'){
        *tmp += '}';
        *x = str.size();
        return;
    }
    if (str[*x] == '['){
        *tmp += ']';
        *x = str.size();
        return;
    }
}

long     calculatescore(std::string str){
    long res = 0;
    for (int i = 0; i < str.size(); i++){
        if (str[i] == ')')
            res = res * 5 + 1;
        if (str[i] == ']')
            res = res * 5 + 2;
        if (str[i] == '}')
            res = res * 5 + 3;
        if (str[i] == '>')
            res = res * 5 + 4;
    }
    return res;
}

int     main(int argc, char **argv){
    std::vector<std::string>    data;
    readfile(argv[1], data);

    int         res = 0;
    int         x = 0;
    std::vector<std::string>    incomplete;
    std::vector<std::string>    complete;
    std::vector<long>            sum;
    for (std::string i : data){
        res = findcorrupt(i, &x);
        if (res == 0)
            incomplete.push_back(i);
        x = 0;
    }
    std::string    tmp = "";
    for (std::string i : incomplete){
        makecomplete(i, &x, &tmp);
        if (x != i.size())
            makecomplete(i, &x, &tmp);
        complete.push_back(tmp);
        tmp = "";
        x = 0;
    }
    for (std::string i : complete){
        sum.push_back(calculatescore(i));
    }
    std::sort(sum.begin(), sum.end());
    std::cout << sum[sum.size()/2] << std::endl;
}