#include "round13.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

void round13() {
	std::ifstream input("inputs/round13.txt");
	std::set<std::pair<int, int>> dots;
	int a, b;
	char comma;
	while (input >> a >> comma >> b) {
		dots.insert({ a,b });
	}
	std::vector<std::pair<char, int>> instructions;
	input.clear();
	std::string s;
	while (std::getline(input, s)) {
		instructions.push_back({ s[11],std::stoi(s.substr(13)) });
	}
	int n = INT32_MAX;
	int m = INT32_MAX;
	int nMax = INT32_MAX;
	int mMax = INT32_MAX;
	int i = 0;
	for (int i = 0; i < instructions.size(); i++) {
		if (instructions[i].first == 'x') {
			n = instructions[i].second;
			for (auto it = dots.begin(); it != dots.end(); it++) {
				if (it->first > n && it->first < nMax) {
					dots.insert({ n - (it->first - n),it->second });
				}
			}
			nMax = n;
		}
		else if (instructions[i].first == 'y') {
			m = instructions[i].second;
			for (auto it = dots.begin(); it != dots.end(); it++) {
				if (it->second > m && it->second < mMax) {
					dots.insert({ it->first, m - (it->second - m) });
				}
			}
			mMax = m;
		}
	}
	int numberOfDots = std::count_if(dots.begin(), dots.end(), [nMax, mMax](auto& x) {
		if (x.first < nMax && x.second < mMax) {
			//std::cout << x.first << "," << x.second << std::endl;
			return true;
		}
		return false;
		});
	for (int i = 0; i < mMax; i++) {
		for (int j = 0; j < nMax; j++) {
			if (dots.contains({ j, i })) {
				std::cout << "#";
			}
			else std::cout << ".";
		}
		std::cout << std::endl;
	}
	std::cout << "There are " << numberOfDots << " dots.";

	input.close();
}