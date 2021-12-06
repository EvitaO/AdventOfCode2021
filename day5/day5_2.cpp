#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct      xy{
    int x, y;
};

void        verticalline(xy end, xy start, std::vector<std::vector<int> > &diagram){
    diagram[start.y][start.x] += 1;
    diagram[end.y][end.x] += 1;
    if (end.y < start.y){
        for (int i = end.y + 1; i < start.y; i++){
            diagram[i][end.x] += 1;
        }
    }
    else{
        for (int i = start.y + 1; i < end.y; i++){
            diagram[i][end.x] += 1;
        }
    }
}

void        horizontalline(xy end, xy start, std::vector<std::vector<int> > &diagram){
    diagram[start.y][start.x] += 1;
    diagram[end.y][end.x] += 1;
    if (end.x < start.x){
        for (int i = end.x + 1; i < start.x; i++){
            diagram[end.y][i] += 1;
        }
    }
    else{
        for (int i = start.x + 1; i < end.x; i++){
            diagram[end.y][i] += 1;
        }
    }
}

void        diagonalline(xy end, xy start, std::vector<std::vector<int> > &diagram){
    diagram[start.y][start.x] += 1;
    diagram[end.y][end.x] += 1;
    int x;
    int y;
    if (end.x < start.x && end.y < start.y){
        for (x = end.x + 1, y = end.y + 1; x < start.x; x++,y++)
            diagram[y][x] += 1;
    }
    else if (end.x >= start.x && end.y >= start.y){
        for (x = start.x + 1, y = start.y + 1; x < end.x; x++,y++)
            diagram[y][x] += 1;
    }
    else if (end.x < start.x && end.y >= start.y){
        for (x = end.x + 1, y = end.y - 1; x < start.x; x++,y--)
            diagram[y][x] += 1;
    }
    else if (end.x >= start.x && end.y < start.y){
        for (x = start.x + 1, y = start.y - 1; x < end.x; x++,y--)
            diagram[y][x] += 1;
    }
}

void        createline(std::vector<std::vector<int> > &diagram, std::string s, std::string e){
    xy      start;
    xy      end;

    start.x = stoi(s.substr(0, s.find(",")));
    start.y = stoi(s.substr(s.find(",") + 1, strlen(s.c_str())));

    end.x = stoi(e.substr(0, e.find(",")));
    end.y = stoi(e.substr(e.find(",") + 1, strlen(e.c_str())));

    if (start.x == end.x)
        verticalline(end, start, diagram);
    else if (start.y == end.y)
        horizontalline(end, start, diagram);
    else
        diagonalline(end, start, diagram);
}

void        readfile(char *file, std::vector<std::vector<int> > &diagram){
    std::fstream        f(file);
    std::stringstream   buf;
    std::string         line_start;
    std::string         line_end;
    buf << f.rdbuf();
    while (buf >> line_start){
        if (line_start.find(",") != std::string::npos && line_end.find(",") != std::string::npos){
            createline(diagram, line_start, line_end);
            line_end = "";
        }
        else if (line_start.find(",") != std::string::npos)
            line_end = line_start;
    }
}

int         main(int argc, char **argv){
    std::vector<std::vector<int> >       diagram(1000, std::vector<int>(1000, 0));
  
    readfile(argv[1], diagram);

    int     res = 0;
    for (int i = 0; i < diagram.size(); i++){
        for (int j = 0; j < diagram[i].size(); j++)
            diagram[i][j] > 1 ? res++ : res=res;
    }
    std::cout << res << std::endl;
    
}