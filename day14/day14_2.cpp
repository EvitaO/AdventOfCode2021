#include <iostream>
#include <fstream>
#include <map>
#include <climits>

void        updateTable(std::map<std::string, long> & table_cnt, std::string tmp, long i){
    if (table_cnt.find(tmp) == table_cnt.end()){
        table_cnt.insert(std::pair<std::string, long>(tmp, i));
    }
    else
        table_cnt[tmp] += i;
}

void        updateTable(std::map<char, long> & table_cnt, char x, long i){
    if (table_cnt.find(x) == table_cnt.end()){
        table_cnt.insert(std::pair<char, long>(x, i));
    }
    else
        table_cnt[x] += i;
}

void        readfile(char *file, std::string &template_poly, std::map<std::string, long> &table_cnt, std::map<std::string, std::string> &table){
    std::fstream            f(file);
    std::string             line;
    getline(f, line);
    template_poly = line;
    for (int i = 1; i < line.size(); i++){
        std::string tmp;
        tmp.push_back(line[i-1]);
        tmp.push_back(line[i]);
        updateTable(table_cnt, tmp, 1);
    }
    while(getline(f, line)){
        if (line.find('>') != std::string::npos){
            std::string a = line.substr(0, line.find(' '));
            std::string b = line.substr(line.find('>')+2, line.size());
            table.insert(std::pair<std::string,std::string>(a,b));
        }
    }
    f.close();
}

void        updateTemplate(std::map<std::string, std::string> &table, std::map<std::string, long> &table_cnt){
    std::map<std::string, long>              tmp;
    std::map<std::string, long>::iterator    it;
    for (it = table_cnt.begin(); it != table_cnt.end();it++){
        std::string a = it->first;
        std::string b = table[a];
        std::string c;
        std::string d;
        c.push_back(a[0]);
        c += b;
        d += b;
        d.push_back(a[1]);
        updateTable(tmp, c, it->second);
        updateTable(tmp, d, it->second);
    }
    table_cnt = tmp;
}

void        cntLetters(std::map<std::string, long> &table_cnt, std::map<char, long> &cnt){
    std::map<std::string, long>::iterator    it;
    for (it = table_cnt.begin(); it != table_cnt.end();it++){
        std::string a = it->first;
        updateTable(cnt, a[0], it->second);
        updateTable(cnt, a[1], it->second);
    }
}

int         main(int argc, char **argv){
    std::map<std::string, std::string>      table;
    std::map<std::string, long>             table_cnt;
    std::map<char, long>                    cnt;
    std::string                             template_poly;
    readfile(argv[1], template_poly, table_cnt, table);
    for (int i = 0; i < 40; i++){
        updateTemplate(table, table_cnt);
    }
    cntLetters(table_cnt, cnt);
    cnt[template_poly[0]]++;
    cnt[template_poly[template_poly.size()-1]]++;
    long high = 0;
    long low = LONG_MAX;
    for (auto i : cnt){
        if(i.second/2 > high)
            high = i.second/2;
        else if (i.second/2 < low)
            low = i.second/2;
    }
    std::cout << high - low << std::endl;
}