#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

struct  data {
    int x,y,cost,manhat;
};

struct  CompareData{
    bool    operator()(data *a, data *b){
        return (a->cost+a->manhat) > (b->cost+b->manhat);
    }
};

void        readfile(char *file, std::vector<std::string> &grid){
    std::fstream        f(file);
    std::string         line;
    while(getline(f, line))
        grid.push_back(line);
    f.close();
}

int         manHattan(int x, int y, int size){
    int xman = abs(size - x);
    int yman = abs(size - y);
    return xman+yman;
}

data*       addNode(int x, int y, std::vector<std::string> &grid, data *tmp){
    data    *a = new data();
    a->x = x;
    a->y = y;
    a->cost = grid[y][x]-48 + tmp->cost;
    a->manhat = manHattan(a->x, a->y, grid.size()-1);
    return a;
}

void        addToOpen(data *newElem, int s, std::priority_queue<data*, std::vector<data*>, CompareData> &open, std::map<int, int> &closed){
    int x = newElem->y*s+newElem->x;
    auto it = closed.find(x);
    if (it == closed.end()){
        closed.insert(std::pair<int,int>(x, newElem->cost));
        open.push(newElem);
    }
    else if (it->second > newElem->cost){
        closed[x] = newElem->cost;
        open.push(newElem);
    }
}

void        searchpath(std::vector<std::string> &grid, std::priority_queue<data*, std::vector<data*>, CompareData> &open, std::map<int, int> &closed){
    while(!open.empty()){
        data    *tmp = open.top();
        open.pop();
        data    *newElem;
        if (tmp->x != 0 && tmp->manhat == 0){
            std::cout << tmp->cost << std::endl;
            return;
        }
        if (tmp->x + 1 < grid.size()){
            newElem = addNode(tmp->x+1, tmp->y, grid, tmp);
            addToOpen(newElem, grid.size(), open, closed);
        }
        if (tmp->x - 1 >= 0){
            newElem = addNode(tmp->x-1, tmp->y, grid, tmp);
            addToOpen(newElem, grid.size(), open, closed);
        }
        if (tmp->y + 1 < grid.size()){
            newElem = addNode(tmp->x, tmp->y+1, grid, tmp);
            addToOpen(newElem, grid.size(), open, closed);
        }
        if (tmp->y - 1 >= 0){
            newElem = addNode(tmp->x, tmp->y-1, grid, tmp);
            addToOpen(newElem, grid.size(), open, closed);
        }
    }
}

int         main(int argc, char **argv){
    std::vector<std::string>    grid;
    readfile(argv[1], grid);

    std::priority_queue<data*, std::vector<data*>, CompareData>    open;
    std::map<int, int>         closed;

    data    init;
    init.x = 0;
    init.y = 0;
    init.cost = 0;
    init.manhat = 0;
    closed.insert(std::pair<int,int>(0,0));
    open.push(&init);
    searchpath(grid, open, closed);
}