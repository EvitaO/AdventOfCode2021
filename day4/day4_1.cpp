#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

std::string								onlydigets(std::string x){
	int i =0;
	while (isdigit(x[i]))
		i++;
	return x.substr(0, i);
}

std::vector<std::vector<std::string> >	getBoards(std::fstream &file){
	std::string		line;
	std::vector<std::vector<std::string> >	boards;
	std::vector<std::string>				board;
	int pos;
	getline(file, line);
	while (getline(file, line)){
		if (line.find(" ") == std::string::npos ){
			boards.push_back(board);
			board.clear();
		}
		else{
			while (line.find(" ") != std::string::npos){
				pos = line.find(" ");
				if (line.substr(0, pos) != "")
					board.push_back(line.substr(0, pos));
				line.erase(0, pos + 1);
			}
			board.push_back(onlydigets(line.substr(0, strlen(line.c_str()))));
		}
	}
	boards.push_back(board);
	return boards;
}

std::vector<std::vector<std::string> >	readline(char *f, std::vector<std::string> &bingo_numbers){
	std::fstream	file(f);
	std::string		line;
	getline(file, line);
	int pos = 0;
	while (line.find(",") != std::string::npos){
		pos = line.find(",");
		bingo_numbers.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
	}
	bingo_numbers.push_back(onlydigets(line.substr(0, strlen(line.c_str()))));
	return getBoards(file);
}

void	checkNbr(std::vector<std::vector<std::string> > &boards, auto i){
	for (int a = 0; a < boards.size(); a++){
		for (int b = 0; b < boards[a].size(); b++){
			if (boards[a][b] == i){
				int num = 100 + stoi(boards[a][b]);
				boards[a][b] = std::to_string(num);
			}
		}
	}
}

bool	bingorow(std::vector<std::string> &board, int x){
	for (int i = 0; i < 5; i++){
		if (stoi(board[x + i]) < 100)
			return false;
	}
	return true;
}

bool	bingocolumn(std::vector<std::string> &board, int x){
	for (int i = 0; i < 5; i++){
		if (stoi(board[x+i]) < 100)
			return false;
	}
	return true;
}
int		checkBingo(std::vector<std::vector<std::string> > &boards){
	int sum = 0;
	for (int a = 0; a < boards.size(); a++){
		for (int b = 0; b <= boards[a].size() - 5; b++){
			if (b % 5 == 0 && bingorow(boards[a], b)){
				for (int i = 0; i < boards[a].size(); i++)
					stoi(boards[a][i]) < 100 ? sum += stoi(boards[a][i]) : sum = sum;
				return sum;
			}
			else if (b < 5 && bingocolumn(boards[a], b)){
				for (int i = 0; i < boards[a].size(); i++)
					stoi(boards[a][i]) < 100 ? sum += stoi(boards[a][i]) : sum = sum;
				return sum;
			}
		}
	}
	return -1;
}

int	main(int argc, char **argv){
	std::vector<std::string> bingo_numbers;
	std::vector<std::vector<std::string> > boards = readline(argv[1], bingo_numbers);
	for (auto i : bingo_numbers){
		checkNbr(boards, i);
		int x = checkBingo(boards);
		if (x != -1){
			std::cout << x << " " << i << " " << std::endl;
			exit(1);
		}
	}
}