#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

void    readfile(char *file, std::vector<std::string> &grid){
    std::fstream        f(file);
    std::string         line;
    while (getline(f, line)){
        grid.push_back(line);
    }
}

void    getLowestPoint(std::vector<std::string> &grid, std::vector<int> &lowestpoints){
    for (int y = 0; y < grid.size(); y++){
        for (int x = 0, z; x < grid[y].size(); x++){
            z = 0;
            if (grid[y][x+1]){
                if (grid[y][x+1] > grid[y][x])
                    z++;
            }
            else
                z++;
            if (grid[y][x-1]){
                if (grid[y][x-1] > grid[y][x])
                    z++;
            }
            else
                z++;                
            if (grid[y+1][x]){
                if (grid[y+1][x] > grid[y][x])
                    z++;
            }
            else
                z++;                
            if (grid[y-1][x]){
                if (grid[y-1][x] > grid[y][x])
                    z++;
            }
            else
                z++;
            if (z == 4)
                lowestpoints.push_back(y*grid[y].size() + x);
        }
    }
}

void     calculateBasin(int i, std::vector<std::string> &grid, std::map<int, int> &map, int key){
    int size = 100;
    int keyx = key % size;
    int keyy = key / size;

    int ix = i % size;
    int iy = i / size;

    int check = 9;
    if (i == key)
        check = 0;
    if (keyx + 1 < size  && keyx + 1 >= 0 && ix + 1 < size && ix + 1 >= 0){
        if (isdigit(grid[iy][ix + 1]) && grid[iy][ix + 1] > grid[iy][ix]-check && grid[iy][ix + 1] - 48 < 9){
            map[key]++;
            grid[iy][ix + 1] += 9;
            calculateBasin(iy*size+ix+1, grid, map, key);
        }
    }
    if (keyx - 1 < size && ix - 1 < size && keyx - 1 >= 0 && ix - 1 >= 0){
        if (isdigit(grid[iy][ix - 1]) && grid[iy][ix - 1] > grid[iy][ix]-check && grid[iy][ix - 1] - 48 < 9){
            map[key]++;
            grid[iy][ix - 1] += 9;
            calculateBasin(iy*size+ix-1, grid, map, key);
        }
    }
    if (keyy+1 < grid.size() && iy+1 < grid.size() && keyy+1 >= 0 && iy+1 >= 0){
        if (isdigit(grid[iy+1][ix]) && grid[iy+1][ix] > grid[iy][ix]-check && grid[iy+1][ix] - 48 < 9){
            map[key]++;
            grid[iy+1][ix] += 9;
            calculateBasin((iy+1)*size+ix, grid, map, key);
        }
    } 
    if (keyy-1 < grid.size() && iy-1 < grid.size() && keyy-1 >= 0 && iy-1 >= 0){
        if (isdigit(grid[iy-1][ix]) && grid[iy-1][ix] > grid[iy][ix]-check && grid[iy-1][ix] - 48 < 9){
            map[key]++;
            grid[iy-1][ix] += 9;
            calculateBasin((iy-1)*size+ix, grid, map, key);
        }
    }       
}

int     main(int argc, char **argv){
    std::vector<std::string>    grid;
    std::vector<int>    lowestpoints;
    std::vector<int>    basins;
    std::map<int,int>   map;

    readfile(argv[1], grid);
    getLowestPoint(grid, lowestpoints);
    for (int i : lowestpoints){
        map.insert(std::pair<int, int>(i, 1));
        calculateBasin(i, grid, map, i);
    }
    int x[3] = {0, 0, 0};
    for (auto i : map){
        if (i.second > x[0]){
            x[2] = x[1];
            x[1] = x[0];
            x[0] = i.second;
        }
    }
    std::cout << x[0] << " " << x[1] << " " << x[2] << std::endl;
}