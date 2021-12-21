#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int		dice = 1;
int 	rolls = 0;

void	readfile(char *file, std::vector<std::pair<int,int> > &players){
	std::fstream		f(file);
	std::string			line;
	while(getline(f, line)){
		line.erase(0, line.find(" ")+1);
		int player_id = std::stoi(line.substr(0, line.find(" ")).c_str());
		int start = std::stoi(line.substr(line.find(":")+1, line.size()).c_str());
		players[player_id - 1] = std::make_pair(start, 0);
	}
}

bool	not1000(std::vector<std::pair<int,int> > &players){
	for (auto i : players){
		// std::cout << i.first << "|" << i.second << std::endl;
		if (i.second >= 1000)
			return false;
	}
	return true;
}

int		calculatedice(){
	int sum = 0;
	if (dice > 100)
		dice = 1;
	sum += dice;
	dice++;
	if (dice > 100)
		dice = 1;
	sum += dice;
	dice++;
	if (dice > 100)
		dice = 1;
	sum += dice;
	dice++;
	return sum;
}

int		takeSteps(int pos, int steps){
	int res = steps % 10;
	if (res + pos > 10)
		res = (res + pos) % 10;
	else 
		res = pos + res;
	return res;
}

std::pair<int,int>	rollDices(std::pair<int,int> &player){
	int sum = 0;
	if (dice + 2 <= 100){
		sum = dice + dice + 1 + dice + 2;
		dice += 3;
	}
	else
		sum = calculatedice();
	rolls += 3;
	player.first = takeSteps(player.first, sum);
	player.second += player.first;
	return player;
}

int		main(int argc, char **argv){
	std::vector<std::pair<int,int> >	players(2);
	readfile(argv[1], players);
	std::cout << players.size() << std::endl;
	while (not1000(players)){
		for (int i = 0; i < players.size(); i++){
			if (not1000(players))
				players[i] = rollDices(players[i]);
			else
				break;
		}
	}
	for (int i = 0; i < players.size();i++){
		std::cout << i << "|" << players[i].first << "|" << players[i].second << std::endl;
	}
	std::cout << rolls << "	JA\n";
}