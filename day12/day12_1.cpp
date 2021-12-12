#include <fstream>
#include <iostream>
#include <list>
#include <map>

void		readfile(char *file, std::map<std::string, std::list<std::string> > &nodes){
	std::fstream	f(file);
	std::string		line;
	while(getline(f, line)){
		std::string a = line.substr(0, line.find('-'));
		std::string b = line.substr(line.find('-') + 1, line.size());
		if (nodes.find(a) == nodes.end()){
			std::list<std::string>	node;
			node.push_back(b);
			nodes.insert(std::pair<std::string, std::list<std::string> >(a, node));
		}
		else {
			std::list<std::string>	node = nodes[a];
			node.push_back(b);
			nodes[a] = node;
		}
	}
}

void		BFS(std::map<std::string, std::list<std::string> > &nodes){
	
}

int			main(int argc, char **argv){
	std::map<std::string, std::list<std::string> >		nodes;
	readfile(argv[1], nodes);
	BFS(nodes);
	for (auto it = nodes.begin(); it != nodes.end(); it++){
		std::cout << it->first << std::endl;
		std::list<std::string>	x = it->second;
		for (std::string i : x)
			std::cout << "	" << i << std::endl;
		std::cout << std::endl;
	}
}