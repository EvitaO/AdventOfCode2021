#include <fstream>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

void        readfile(char *file, std::vector<int> &data){
    std::fstream    f(file);
    std::string     line;
    getline(f, line);
    f.close();
    
    int pos = line.find(",");
    while (pos != std::string::npos){
        data.push_back(stoi(line.substr(0, pos)));
        line.erase(0, pos+1);
        pos = line.find(",");
    }
    data.push_back(stoi(line));
}

int         calculateavg(std::vector<int> &data){
    long    i = 0;
    for (int x : data)
        i += x;
    return (i/data.size());
}

int         calculatefuel(std::vector<int> &data, int goal){
    int f = 0;
    for (int i : data){
        if (i - goal >= 0)
            f += (i - goal);
        else if (goal - i >= 0)
            f += (goal - i);
    }
    return f;
}

int         main(int argc, char **argv){
    std::vector<int>    data;
    readfile(argv[1], data);
    int average = calculateavg(data);

    std::vector<int>    fuels(average - 1, 0);
    for (int i = 0; i <= average; i++){
        fuels[i] = calculatefuel(data, i);
    }
    int res = *min_element(fuels.begin(), fuels.end());
    std::cout << res << std::endl;
}