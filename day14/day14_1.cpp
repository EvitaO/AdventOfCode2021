#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

void        readfile(char *file, std::string &template_poly, std::map<std::string, std::string> &table){
    std::fstream            f(file);
    std::string             line;
    getline(f, template_poly);
    while(getline(f, line)){
        if (line.find('>') != std::string::npos){
            std::string a = line.substr(0, line.find(' '));
            std::string b = line.substr(line.find('>')+2, line.size());
            table.insert(std::pair<std::string,std::string>(a,b));
        }
    }
    f.close();
}

void        updateTemplate(std::string &template_poly, std::map<std::string, std::string> &table){
    std::string         newTemplate = "";
    for (int i = 1; i < template_poly.size();i++){
        std::string tmp;
        tmp.push_back(template_poly[i-1]);
        tmp.push_back(template_poly[i]);
        std::string x = table[tmp];
        newTemplate.push_back(template_poly[i-1]);
        newTemplate += x;
        if (i + 1 == template_poly.size())
            newTemplate.push_back(template_poly[i]);
    }
    template_poly = newTemplate;
}

int         main(int argc, char **argv){
    std::string                             template_poly;
    std::map<std::string, std::string>      table;
    readfile(argv[1], template_poly, table);
    for (int i = 0; i < 40; i++){
        updateTemplate(template_poly, table);
    }
    sort(template_poly.begin(), template_poly.end());
    std::vector<std::pair<int, char> >            cnt;
    for (int i = 0; i < template_poly.size();){
        char x = template_poly[i];
        int c = 0;
        while (i < template_poly.size() && template_poly[i] == x){
            i++;
            c++;
        }
        cnt.push_back(std::pair<int, char>(c, template_poly[i-1]));
    }
    sort(cnt.begin(),cnt.end());
    std::cout << cnt[cnt.size()-1].first - cnt[0].first << std::endl; 
}