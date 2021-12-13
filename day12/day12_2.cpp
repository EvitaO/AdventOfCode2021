#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <deque>
#include <vector>

int i = 0;

void		readfile(char *file, std::map<std::string, std::list<std::string> > &nodes){
	std::fstream	f(file);
	std::string		line;
	while(getline(f, line)){
		std::string a = line.substr(0, line.find('-'));
		std::string b = line.substr(line.find('-') + 1, line.size());
		if (nodes.find(a) == nodes.end() && a != "end" && b != "start"){
			std::list<std::string>	node;
			node.push_back(b);
			nodes.insert(std::pair<std::string, std::list<std::string> >(a, node));
		}
		else if (a != "end" && b != "start"){
			std::list<std::string>	node = nodes[a];
			node.push_back(b);
			nodes[a] = node;
		}
		if (nodes.find(b) == nodes.end() && a != "start" && b != "end"){
			std::list<std::string>	node;
			node.push_back(a);
			nodes.insert(std::pair<std::string, std::list<std::string> >(b, node));
		}
		else if (a != "start" && b != "end") {
			std::list<std::string>	node = nodes[b];
			node.push_back(a);
			nodes[b] = node;
		}
	}
}

void		addNodes(std::string key, std::deque<std::string> &queue, std::map<std::string, std::list<std::string> > &nodes){
	std::list<std::string> tmp = nodes[key];
	for (std::string i : tmp){
		if (std::find(queue.begin(), queue.end(), i) == queue.end())
			queue.push_back(i);
	}
}

bool		UpperCase(std::string str){
	for (int i = 0; i < str.size(); i++){
		if (!isupper(str[i]))
			return false;
	}
	return true;
}

bool		lowerCase(std::string str){
	for (int i = 0; i < str.size(); i++){
		if (!islower(str[i]))
			return false;
	}
	return true;	
}

bool		twosmall(std::string s, std::list<std::string> &lst){
	std::map<std::string, int>		values;
	if (!lowerCase(s))
		return true;
	for (std::string x : lst){
		if (values.find(x) == values.end())
			values.insert(std::pair<std::string, int>(x, 1));
		else
			values[x]++;
	}
	if (values.find(s) == values.end())
		return true;
	for (std::string x : lst){
		if (values[x] > 1 && values.find(s) != values.end() && lowerCase(x))
			return false;
	}	
	if (values[s] == 1)
		return true;
	return false;
}

bool		notinPaths(std::list<std::string> lst, std::vector<std::list<std::string> > &paths){
	int check = 0;
	for (int x = 0; x < paths.size(); x++){
		if (lst == paths[x])
			return false;
	}
	return true;
}

void		DFS(std::string key, std::map<std::string, std::list<std::string> > &nodes, std::vector<std::list<std::string> > &paths, std::list<std::string> lst)
{
	std::list<std::string> list = nodes[key];
	for (auto it = list.begin(); it != list.end(); it++){
		std::string x = *it;
		if (x == "end"){
			std::list<std::string> tmp = lst;
			tmp.push_back(x);
			paths.push_back(tmp);
			i++;
		}
		else if (std::find(lst.begin(), lst.end(), x) == lst.end() || UpperCase(x)){
			std::list<std::string> tmp = lst;
			tmp.push_back(x);
			DFS(x, nodes, paths, tmp);
		}
		else if (twosmall(x, lst)){
			std::list<std::string> tmp = lst;
			tmp.push_back(x);
			DFS(x, nodes, paths, tmp);
		}
	}
}

int			main(int argc, char **argv){
	std::map<std::string, std::list<std::string> >		nodes;
	readfile(argv[1], nodes);
	std::vector<std::list<std::string> > paths;
	std::list<std::string>	list;
	list.push_back("start");
	DFS("start", nodes, paths, list);
	std::cout << i << std::endl;
}