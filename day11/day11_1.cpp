#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>

void		readfile(char *file, std::vector<std::string> &data){
	std::fstream		f(file);
	std::string			line;
	while (getline(f, line))
		data.push_back(line);
	f.close();
}

void		increaseAll(std::vector<std::string> &data){
	for (int y = 0; y < data.size(); y++){
		for (int x = 0; x < data[y].size(); x++){
			if (data[y][x] == '9')
				data[y][x] = 'a';
			else
				data[y][x] = data[y][x] - 48 + 1 + 48;
		}
	}
}

int			findFlash(std::vector<std::string> &data){
	for (int y = 0; y < data.size(); y++){
		for (int x = 0; x < data[y].size(); x++){
			if (data[y][x] == 'a')
				return y * data.size() + x;
		}
	}
	return -1;
}		

void		flashes(std::vector<std::string> &data, int i, int *cnt){
	int		y = i / data.size();
	int		x = i % data.size();

	if (data[y][x] == 'a'){
		(*cnt)++;
		data[y][x] = 'b';
		if (x+1 < data[y].size())
		{
			if (data[y][x+1] < 57)
				data[y][x+1] = data[y][x+1] + 1;
			else if (data[y][x+1] == '9'){
				data[y][x+1] = 'a';
				flashes(data, y*data.size()+x+1, cnt);
			}
		}
		if (x-1 >= 0){
			if (data[y][x-1] < 57)
				data[y][x-1] = data[y][x-1] + 1;
			else if (data[y][x-1] == '9'){
				data[y][x-1] = 'a';
				flashes(data, y*data.size()+x-1, cnt);
			}
		}
		if (y+1 < data.size()){
			if (data[y+1][x] < 57)
				data[y+1][x] = data[y+1][x] + 1;
			else if (data[y+1][x] == '9'){
				data[y+1][x] = 'a';
				flashes(data, (y+1)*data.size()+x, cnt);
			}
		}
		if (y-1 >= 0){
			if (data[y-1][x] < 57)
				data[y-1][x] = data[y-1][x] + 1;
			else if (data[y-1][x] == '9'){
				data[y-1][x] = 'a';
				flashes(data, (y-1)*data.size()+x, cnt);
			}
		}
		if (x-1 >= 0 && y-1 >= 0){
			if (data[y-1][x-1] < 57)
				data[y-1][x-1] = data[y-1][x-1] + 1;
			else if (data[y-1][x-1] == '9'){
				data[y-1][x-1] = 'a';
				flashes(data, (y-1)*data.size()+x-1, cnt);
			}
		}
		if (x+1 < data[y].size() && y-1 >= 0){
			if (data[y-1][x+1] < 57)
				data[y-1][x+1] = data[y-1][x+1] + 1;
			else if (data[y-1][x+1] == '9'){
				data[y-1][x+1] = 'a';
				flashes(data, (y-1)*data.size()+x+1, cnt);
			}
		}
		if (x+1 < data[y].size() && y+1 < data.size()){
			if (data[y+1][x+1] < 57)
				data[y+1][x+1] = data[y+1][x+1] + 1;
			else if (data[y+1][x+1] == '9'){
				data[y+1][x+1] = 'a';
				flashes(data, (y+1)*data.size()+x+1, cnt);
			}
		}
		if (x-1 >= 0 && y+1 < data.size()){
			if (data[y+1][x-1] < 57)
				data[y+1][x-1] = data[y+1][x-1] + 1;
			else if (data[y+1][x-1] == '9'){
				data[y+1][x-1] = 'a';
				flashes(data, (y+1)*data.size()+x-1, cnt);
			}
		}
	}
}

void		reset(std::vector<std::string> &data){
	for (int y = 0; y < data.size(); y++){
		for (int x = 0; x < data[y].size(); x++){
			if (data[y][x] == 'b')
				data[y][x] = '0';
		}
	}
}

int			main(int argc, char**argv){
	std::vector<std::string>	data;
	readfile(argv[1], data);
	int cnt = 0;
	for (int i = 0; i < 100; i++){
		increaseAll(data);
		while (findFlash(data) != -1){
			int x = findFlash(data);
			flashes(data, x, &cnt);
		}
		reset(data);
	}
	std::cout << cnt << std::endl;
}