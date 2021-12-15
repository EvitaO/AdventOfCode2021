#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

struct  data {
    int x,y,cost,cnt;
};

struct  CompareData{
    bool    operator()(data *a, data *b){
        return a->cost > b->cost;
    }
};

void        readfile(char *file, std::vector<std::string> &grid){
    std::fstream        f(file);
    std::string         line;
    while(getline(f, line))
        grid.push_back(line);
    f.close();
}

void        searchpath(std::vector<std::string> &grid, std::priority_queue<data*, std::vector<data*>, CompareData> &open, std::map<int, int> &closed){
    while(!open.empty()){
        data    *tmp = open.top();
        open.pop();
        if (tmp->y + 1 == grid.size() && tmp->x + 1 == grid[0].size()){
            std::cout << tmp->cnt << std::endl;
            return;
        }
        if (tmp->x + 1 < grid[tmp->y].size()){
            data    *a = new data();
            a->x = tmp->x + 1;
            a->y = tmp->y;
            a->cost = tmp->cost + 1 + (grid[a->y][a->x]-48);
            a->cnt = tmp->cnt + (grid[a->y][a->x]-48);
            int x = a->y*grid.size()+a->x;
            auto it = closed.find(x);
            if (it == closed.end()){
                closed.insert(std::pair<int,int>(a->y*grid.size()+a->x, a->cost));
                open.push(a);
            }
        }
        if (tmp->x - 1 >= 0){
            data    *b = new data();
            b->x = tmp->x - 1;
            b->y = tmp->y;
            b->cost = tmp->cost + 1 + (grid[b->y][b->x]-48);
            b->cnt = tmp->cnt + (grid[b->y][b->x]-48);
            int x = b->y*grid.size()+b->x;
            auto it = closed.find(x);
            if (it == closed.end()){
                closed.insert(std::pair<int,int>(b->y*grid.size()+b->x, b->cost));
                open.push(b);
            }
        }
        if (tmp->y + 1 < grid.size()){
            data    *c = new data();
            c->x = tmp->x;
            c->y = tmp->y + 1;
            c->cost = tmp->cost + 1 + (grid[c->y][c->x]-48);
            c->cnt = tmp->cnt + (grid[c->y][c->x]-48);
            int x = c->y*grid.size()+c->x;
            auto it = closed.find(x);
            if (it == closed.end()){
                closed.insert(std::pair<int,int>(c->y*grid.size()+c->x, c->cost));
                open.push(c);
            }
        }
        if (tmp->y - 1 >= 0){
            data    *d = new data();
            d->x = tmp->x;
            d->y = tmp->y - 1;
            d->cost = tmp->cost + 1 + (grid[d->y][d->x]-48);
            d->cnt = tmp->cnt + (grid[d->y][d->x]-48);
            int x = d->y*grid.size()+d->x;
            auto it = closed.find(x);
            if (it == closed.end()){
                closed.insert(std::pair<int,int>(d->y*grid.size()+d->x, d->cost));
                open.push(d);
            }
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
    init.cnt = 0;
    closed.insert(std::pair<int,int>(0,0));
    open.push(&init);
    searchpath(grid, open, closed);
}