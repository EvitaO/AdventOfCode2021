#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void    readfile(char *file, std::vector<int> &grid){
    std::fstream        f(file);
    std::string         line;
    while (getline(f, line)){
        for(int i = 0; i < line.size(); i++)
            grid.push_back(line[i] - 48);
    }
}

void    getLowestPoint(std::vector<int> &grid, int &res){
    for (int i = 0; i < grid.size(); i++){
        if (grid[i] == 9);
        else if (i == 0){
            if (grid[i+1] > grid[i]  && grid[i+100] > grid[i])
            res += grid[i] + 1;
        }
        else if (i == 99){
            if (grid[i-1] > grid[i] && grid[i+100] > grid[i])
                res += grid[i] + 1;
        }
        else if (i == 9999){
            if (grid[i-100] > grid[i] & grid[i-1] > grid[i])
                res += grid[i] + 1;
        }
        else if (i == 9900){
            if (grid[i-100] > grid[i] & grid[i+1] > grid[i])
                res += grid[i] + 1;            
        }
        else if (i % 100 == 0){
            if (grid[i+1] > grid[i] && grid[i-100] > grid[i] && grid[i+100] > grid[i])
                res += grid[i] + 1;
        }
        else if (i % 100 == 99){
            if (grid[i-1] > grid[i] && grid[i+100] > grid[i] && grid[i-100] > grid[i])
                res += grid[i] + 1;
        }
        else if (i < 99){
            if (grid[i+1] > grid[i] && grid[i-1] > grid[i] && grid[i+100] > grid[i])
                res += grid[i] + 1;
        }
        else if (i > 9900){
            if (grid[i+1] > grid[i] && grid[i-1] > grid[i] && grid[i-100] > grid[i])
                res += grid[i] + 1;            
        }
        else{
            if (grid[i+1] > grid[i] && grid[i-1] > grid[i] && grid[i+100] > grid[i] && grid[i-100] > grid[i])
                res += grid[i] + 1;
        }
    }
}

int     main(int argc, char **argv){
    std::vector<int>    grid;
    int                 res = 0;
    readfile(argv[1], grid);
    getLowestPoint(grid, res);
    std::cout << res << std::endl;
}