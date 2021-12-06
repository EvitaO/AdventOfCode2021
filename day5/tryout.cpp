#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>

struct      xy{
    int x, y;
};

struct Compare{
    bool    operator()(const xy &b, const xy &e) const{
        std::cout << "check " << b.x << "  " << b.y << "    e   " << e.x << " " << e.y << std::endl;
        if (b.x == e.x && b.y == e.y)
            return false;
        return true;
    }
};


void        addElem(xy x, std::map<xy, int, Compare> &diagram){
    std::cout << x.x << "   " << x.y << std::endl;
    
    std::cout << "aaa\n";
    for (auto i : diagram)
        std::cout << i.first.x << " " << i.first.y << "   " << i.second << std::endl;
    auto  i = diagram.find(x);

    if (i != diagram.end()){
        std::cout << i->second << std::endl;
        i->second++;
        std::cout << i->second << std::endl;

    }
    else
        diagram.insert({x, 1});
}

void        verticalline(xy end, xy start, std::map<xy, int, Compare> &diagram){
    xy      tmp;
    
    addElem(end, diagram);
    addElem(start, diagram);
    if (end.y < start.y){
        for (int i = end.y + 1; i < start.y; i++){
            tmp.x = end.x;
            tmp.y = i;
            addElem(tmp, diagram);
        }
    }
    else{
        for (int i = start.y + 1; i < end.y; i++){
            tmp.x = start.x;
            tmp.y = i;
            addElem(tmp, diagram);
        }
    }
}

void        horizontalline(xy end, xy start, std::map<xy, int, Compare> &diagram){
    xy      tmp;
    
    addElem(end, diagram);
    addElem(start, diagram);
    // for (auto i : diagram)
    //     std::cout << i.first.x << " " << i.first.y << "   " << i.second << std::endl;
    if (end.x < start.x){
        for (int i = end.x + 1; i < start.x; i++){
            tmp.y = end.y;
            tmp.x = i;
            addElem(tmp, diagram);
            // for (auto i : diagram)
            //     std::cout << i.first.x << " " << i.first.y << "   " << i.second << std::endl;
        }
    }
    else{
        for (int i = start.x + 1; i < end.x; i++){
            tmp.y = start.y;
            tmp.x = i;
            addElem(tmp, diagram);
        }
    }
}

void        createline(std::map<xy, int, Compare> &diagram, std::string s, std::string e){
    xy      start;
    xy      end;
    
    std::cout << "x "  << s << std::endl;
    std::cout << "y " << e << std::endl;

    start.x = stoi(s.substr(0, s.find(",")));
    start.y = stoi(s.substr(s.find(",") + 1, strlen(s.c_str())));

    end.x = stoi(e.substr(0, e.find(",")));
    end.y = stoi(e.substr(e.find(",") + 1, strlen(e.c_str())));

    if (start.x == end.x)
        verticalline(end, start, diagram);
    else if (start.y == end.y)
        horizontalline(end, start, diagram);


}

void        readfile(char *file, std::map<xy, int, Compare> &diagram){
    std::fstream        f(file);
    std::stringstream   buf;
    std::string         line_start;
    std::string         line_end;
    buf << f.rdbuf();
    while (buf >> line_start){
        if (line_start.find(",") != std::string::npos && line_end.find(",") != std::string::npos){
            createline(diagram, line_start, line_end);
            // for (auto i : diagram)
            //     std::cout << i.first.x << " " << i.first.y << "   " << i.second << std::endl;
            line_end = "";
        }
        else if (line_start.find(",") != std::string::npos)
            line_end = line_start;

    }
}

int         main(int argc, char **argv){
    std::map<xy, int, Compare>       diagram;
    readfile(argv[1], diagram);
    for (auto i : diagram)
        std::cout << i.first.x << " " << i.first.y << "   " << i.second << std::endl;
}