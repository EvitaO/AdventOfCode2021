#include <iostream>
#include <fstream>
#include <map>
#include <vector>

void        readfile(char *file, std::multimap<int, int> &coordinates){
    std::fstream        f(file);
    std::string         line;
    while (getline(f, line) && line.find(',') != std::string::npos){
        int a = stoi(line.substr(0, line.find(',')));
        int b = stoi(line.substr(line.find(',') + 1, line.size()));
        coordinates.insert(std::pair<int,int>(a,b));
    }
}

void        readFolds(char *file, std::vector<std::pair<std::string, int> > &folds){
    std::fstream        f(file);
    std::string         line;
    while(getline(f, line) && line.find(',') != std::string::npos);
    while(getline(f, line)){
        int pos = line.find("g") + 2;
        line = line.substr(pos, line.size());
        std::string i = line.substr(0, line.find('='));
        int j = stoi(line.substr(line.find('=') + 1, line.size()));
        folds.push_back(std::pair<std::string, int>(i,j));
    }
}

int         highestX(std::multimap<int, int> &coordinates){
    int x = 0;
    for (auto it = coordinates.begin(); it != coordinates.end(); it++){
        if (it->first > x)
            x = it->first;
    }
    return x;
}

int         highestY(std::multimap<int, int> &coordinates){
    int y = 0;
    for (auto it = coordinates.begin(); it != coordinates.end(); it++){
        if (it->second > y)
            y = it->second;
    }
    return y;
}

void        putCoordinates(std::multimap<int, int> &coordinates, std::vector<std::vector<char> > &grid){
    for (auto it = coordinates.begin(); it != coordinates.end(); it++){
        grid[it->second][it->first] = '#';
    }
}

void        fold(std::string direc, int line, std::vector<std::vector<char> > &grid){
    if (direc == "y"){
        int y = line;
        int x = grid[0].size();
        std::vector<std::vector<char> > grid2(y, std::vector<char>(x, '.'));
        for (int i = 0; i < grid2.size(); i++){
            grid2[i] = grid[i];
            int k = grid2.size() * 2 - i;
            for (int l = 0; l < grid[k].size(); l++){
                if (grid[k][l] == '#')
                    grid2[i][l] = '#';
            }
        }
        grid.resize(y, std::vector<char>(x,'.'));
        for (int i = 0; i < grid.size(); i++)
            grid[i] = grid2[i];
    }  
    else {
        int y = grid.size();
        int x = line;
        std::vector<std::vector<char> > grid2(y, std::vector<char>(x, '.'));
        for (int i = 0; i < grid2.size(); i++){
            for (int j = 0; j < grid2[i].size(); j++){
                grid2[i][j] = grid[i][j];
                int k = grid[i].size()-1-j;
                if (grid[i][k] == '#')
                    grid2[i][j] = '#';
            }
        }
        grid.resize(y, std::vector<char>(x,'.'));
        for (int i = 0; i < grid.size(); i++)
            grid[i] = grid2[i];
    } 
}

void        print(std::vector<std::vector<char> > &grid){
    for (int y = 0; y < grid.size(); y++){
        for (int x = 0; x < grid[y].size(); x++){
            std::cout << grid[y][x] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int         main(int argc, char **argv){
    std::multimap<int, int>  coordinates;
    readfile(argv[1], coordinates);
    int x = highestX(coordinates);
    int y = highestY(coordinates);
    std::vector<std::pair<std::string, int> >  folds;
    readFolds(argv[1], folds);

    std::vector<std::vector<char> > grid(y+1, std::vector<char>(x+1, '.'));
    putCoordinates(coordinates, grid);
    for (auto it = folds.begin(); it != folds.end(); it++){
        fold(it->first, it->second, grid);
    }
    print(grid);
}