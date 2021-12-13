#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <set>
#include <stack>

void round1() {
	std::ifstream input("inputs/round1.txt");
	int a, b, c, d;
	int increasedCounter = 0;
	bool first = true;
	input >> a >> b >> c;
	while (input >> d) {
		if (b + c + d > a + b + c) {
			increasedCounter++;
		}
		a = b;
		b = c;
		c = d;
	}
	input.close();
	std::cout << "In this example, there are " << increasedCounter << " measurements that are larger than the previous measurement.";
}

void round2() {
	int depth = 0;
	int horizontalPosition = 0;
	int aim = 0;
	std::ifstream input("inputs/round2.txt");
	std::string direction;
	int value;
	while (input >> direction >> value) {
		if (direction == "up") {
			aim = aim - value;
		}
		if (direction == "down") {
			aim = aim + value;
		}
		if (direction == "forward") {
			horizontalPosition = horizontalPosition + value;
			depth = depth + aim * value;
		}
	}

	std::cout << "Depth and position multiplied: " << depth * horizontalPosition;
	input.close();

}

void round3() {
	std::ifstream input("inputs/round3.txt");
	int ones[12] = {};
	int zeros[12] = {};
	long long n;
	std::vector<long long> numbers;

	for (unsigned int i = 0; input >> n; i++) {
		long long temp = n;
		numbers.push_back(temp);
		for (unsigned int j = 0; j < 12; j++) {
			int bit = temp % 10;
			temp = temp / 10;
			if (bit) {
				ones[j]++;
			}
			else {
				zeros[j]++;
			}
		}
	}
	int gamma = 0;
	int epsilon = 0;
	for (unsigned int i = 0; i < 12; i++) {
		if (ones[i] > zeros[i]) {
			gamma = gamma + pow(2, i);
		}
		else {
			epsilon = epsilon + pow(2, i);
		}
	}


	std::vector<long long> numbers2 = numbers;
	for (int i = 11; i >= 0; i--) {
		int n1count1 = std::count_if(numbers.begin(), numbers.end(), [i](const long long& x) {
			if (((long long)(x / pow(10, i))) % 10 == 1)
				return true;
			return false; });

		int n1count0 = std::count_if(numbers.begin(), numbers.end(), [i](const long long& x) {
			if (((long long)(x / pow(10, i))) % 10 == 0)
				return true;
			return false; });

		int n2count1 = std::count_if(numbers2.begin(), numbers2.end(), [i](const long long& x) {
			if (((long long)(x / pow(10, i))) % 10 == 1)
				return true;
			return false; });

		int n2count0 = std::count_if(numbers2.begin(), numbers2.end(), [i](const long long& x) {
			if (((long long)(x / pow(10, i))) % 10 == 0)
				return true;
			return false; });
		if (numbers.size() != 1)
			numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [i, n1count1, n1count0](const long long& x) {
			if (n1count0 > n1count1) {
				if (((long long)(x / pow(10, i))) % 10 == 0)
					return false;
				else return true;
			}
			else {
				if (((long long)(x / pow(10, i))) % 10 == 1)
					return false;
				else return true;
			}
				}), numbers.end());
		if (numbers2.size() != 1)
			numbers2.erase(std::remove_if(numbers2.begin(), numbers2.end(), [i, n2count1, n2count0](const long long& x) {
			if (n2count1 < n2count0) {
				if (((long long)(x / pow(10, i))) % 10 == 1)
					return false;
				else return true;
			}
			else {
				if (((long long)(x / pow(10, i))) % 10 == 0)
					return false;
				else return true;
			}
				}), numbers2.end());

	}
	long long temp1 = numbers[0];
	long long temp2 = numbers2[0];
	int n1 = 0;
	int n2 = 0;
	for (unsigned int i = 0; i < 12; i++) {
		n1 = n1 + pow(2, i) * (temp1 % 10);
		n2 = n2 + pow(2, i) * (temp2 % 10);
		temp1 = temp1 / 10;
		temp2 = temp2 / 10;
	}

	std::cout << "Life support rating of the submarine is: " << n1 * n2;

	input.close();
}

void round4() {
	std::ifstream input("inputs/round4.txt");
	std::vector<short> numbers;
	std::vector<std::vector<std::vector<std::pair<short, bool>>>> boards;
	short n;
	char znak;
	while (input >> n) {
		numbers.push_back(n);
		if (input.peek() != ',') {
			break;
		}
		input >> znak;
	}

	while (input >> n) {
		std::vector<std::vector<std::pair<short, bool>>> temp(5, { 5, std::make_pair(0,false) });
		bool first = true;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (!first) {
					input >> n;
				}
				temp[i][j].first = n;
				first = false;
			}
		}
		boards.push_back(temp);
	}
	bool kraj = false;
	for (short x : numbers) {
		if (kraj)
			return;
		std::for_each(boards.begin(), boards.end(), [&x, &kraj](auto& el) {
			int kolona[5] = { 0,0,0,0,0 };
			int red[5] = { 0,0,0,0,0 };
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (el[i][j].first == x) {
						el[i][j].second = true;
					}
					if (el[i][j].second == true) {
						red[i]++;
						kolona[j]++;
					}
				}
			}
			for (int i = 0; i < 5; i++) {
				if (red[i] == 5 || kolona[i] == 5) {
					short suma = 0;
					for (int k = 0; k < 5; k++)
						for (int j = 0; j < 5; j++)
							if (el[k][j].second == false)
								suma = suma + el[k][j].first;
					std::cout << "The score is: " << suma * x;
					kraj = true;
				}
			}
			});

	}

	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)
				std::cout << "{" << boards[k][i][j].first << ", " << boards[k][i][j].second << "} ";
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
	input.close();
}

void round4_2() {
	std::ifstream input("inputs/round4.txt");
	std::vector<short> numbers;
	std::vector<std::vector<std::vector<std::pair<short, bool>>>> boards;
	short n;
	char znak;
	while (input >> n) {
		numbers.push_back(n);
		if (input.peek() != ',') {
			break;
		}
		input >> znak;
	}

	while (input >> n) {
		std::vector<std::vector<std::pair<short, bool>>> temp(5, { 5, std::make_pair(0,false) });
		bool first = true;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (!first) {
					input >> n;
				}
				temp[i][j].first = n;
				first = false;
			}
		}
		boards.push_back(temp);
	}
	bool kraj = false;
	for (short x : numbers) {
		if (!boards.size())
			return;
		boards.erase(std::remove_if(boards.begin(), boards.end(), [&x, &boards](auto& el) {
			int kolona[5] = { 0,0,0,0,0 };
			int red[5] = { 0,0,0,0,0 };
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (el[i][j].first == x) {
						el[i][j].second = true;
					}
					if (el[i][j].second == true) {
						red[i]++;
						kolona[j]++;
					}
				}
			}
			for (int i = 0; i < 5; i++) {
				if (red[i] == 5 || kolona[i] == 5) {
					if (boards.size() != 1)
						return true;
					else {
						short suma = 0;
						for (int k = 0; k < 5; k++)
							for (int j = 0; j < 5; j++)
								if (boards[0][k][j].second == false)
									suma = suma + boards[0][k][j].first;
						std::cout << "The score is: " << suma * x;
						return true;
					}
				}
			}
			return false;
			}), boards.end());

	}
	input.close();
}

void round5() {
	std::map<std::pair<int, int>, int> points;
	int x1, y1, x2, y2;
	char znak;
	std::ifstream input("inputs/npr.txt");
	while (input >> x1) {
		input >> znak >> y1 >> znak >> znak >> x2 >> znak >> y2;
		if (x1 == x2) {
			if (y1 < y2) {
				while (y1 <= y2) {
					points[{x1, y1}]++;
					y1++;
				}
			}
			else if (y2 < y1) {
				while (y2 <= y1) {
					points[{x2, y2}]++;
					y2++;
				}
			}
		}
		else if (y1 == y2) {
			if (x1 < x2) {
				while (x1 <= x2) {
					points[{x1, y1}]++;
					x1++;
				}
			}
			else if (x2 < x1) {
				while (x2 <= x1) {
					points[{x2, y2}]++;
					x2++;
				}
			}
		}
		else if (x1 < x2) {
			if (y1 < y2) {
				while (y1 <= y2) {
					points[{x1, y1}]++;
					x1++;
					y1++;
				}
			}
			else if (y2 < y1) {
				while (y2 <= y1) {
					points[{x1, y1}]++;
					x1++;
					y1--;
				}
			}

		}
		else if (x2 < x1) {
			if (y1 < y2) {
				while (y1 <= y2) {
					points[{x2, y2}]++;
					x2++;
					y2--;
				}
			}
			else if (y2 < y1) {
				while (y2 <= y1) {
					points[{x2, y2}]++;
					x2++;
					y2++;
				}
			}

		}
	}
	int overlaps = 0;
	for (auto const& [key, val] : points) {
		if (val > 1)
			overlaps++;
	}
	std::cout << "Number of points where at least two lines overlap is: " << overlaps;
	input.close();
}

void round6() {
	std::ifstream input("inputs/npr.txt");
	std::vector<int> fish{};
	int k;
	char comma;
	while (input >> k >> comma) {
		fish.push_back(k);
	}
	int n = 256;
	int br = 0;
	for (int i = 0; i < n; i++) {
		for (int& x : fish) {
			if (x != 0) {
				x--;
			}
			else {
				x = 6;
				br++;
			}
		}
		while (br != 0) {
			fish.push_back(8);
			br--;
		}
	}
	std::cout << "There are a total of: " << fish.size() << " fish.";
	input.close();
}
void round6_2(int n) {
	std::ifstream input("inputs/round6.txt");
	int k;
	char comma;
	long long fish[9]{};
	while (input >> k >> comma) {
		fish[k]++;
	}

	for (int i = 0; i < n; i++) {
		long long newFish = fish[0];
		for (int j = 0; j < 8; j++)
			fish[j] = fish[j + 1];
		fish[6] = fish[6] + newFish;
		fish[8] = newFish;
	}

	long long sum = 0;
	for (int i = 0; i < 9; i++)
		sum = sum + fish[i];
	std::cout << "There are a total of: " << sum << " fish.";
}

void round7() {
	std::ifstream input("inputs/round7.txt");
	int k;
	char comma;
	std::multiset<int> positions;
	while (input >> k >> comma) {
		positions.insert(k);
	}
	int median;
	if (positions.size() % 2 == 0) {
		median = positions.size() / 2;
	}
	else {
		median = ((positions.size() - 1) / 2 + (positions.size() + 1) / 2) / 2;
	}
	int point = *std::next(positions.begin(), median);
	int fuel = 0;
	for (auto& x : positions) {
		fuel = fuel + (int)abs(x - point);
	}
	std::cout << "The optimal position is: " << point << ", an the total cost of fuel is: " << fuel << std::endl;
	input.close();
}
void round7_2() {
	std::ifstream input("inputs/round7.txt");
	int k;
	char comma;
	std::multiset<int> positions;
	while (input >> k >> comma) {
		positions.insert(k);
	}

	int minFuel = INT_MAX;
	int optimalPosition = 0;
	for (int x = 0; x < positions.size(); x++) {
		int fuel = 0;
		for (auto& point : positions) {
			fuel = fuel + ((int)abs(x - point) * (int)(abs(x - point) + 1)) / 2;
		}
		if (fuel < minFuel) {
			minFuel = fuel;
			optimalPosition = x;
		}
	}
	std::cout << "The optimal position is: " << optimalPosition << ", an the total cost of fuel is: " << minFuel << std::endl;
	input.close();
}

std::string stringAND(const std::string& a, const std::string& b) {
	std::string temp = "";
	for (char x : a) {
		if (b.find(x) != std::string::npos)
			temp = temp + x;
	}
	return temp;
}
std::string stringOR(const std::string& a, const std::string& b) {
	std::string temp = a;
	for (char x : b) {
		if (temp.find(x) == std::string::npos)
			temp = temp + x;
	}
	return temp;
}
std::string stringNOT(const std::string& a, const std::string& b) {
	std::string temp = "";
	for (char x : a) {
		if (b.find(x) == std::string::npos)
			temp = temp + x;
	}
	return temp;
}
bool stringEQUALS(const std::string& a, const std::string& b) {
	if (a.size() == b.size()) {
		for (char x : a) {
			if (b.find(x) == std::string::npos)
				return false;
		}
		for (char x : b) {
			if (a.find(x) == std::string::npos)
				return false;
		}
		return true;
	}
	return false;
}
void round8() {
	std::ifstream input("inputs/round8.txt");
	std::string n;
	std::vector<std::vector<std::string>> patterns;
	std::vector<std::vector<std::string>> outputs;
	char sign;
	std::vector<std::string> temp;
	while (input >> n) {
		temp.clear();
		temp.push_back(n);
		for (int i = 0; i < 9; i++) {
			input >> n;
			temp.push_back(n);
		}
		patterns.push_back(temp);
		temp.clear();
		input >> sign;
		for (int i = 0; i < 4; i++) {
			input >> n;
			temp.push_back(n);
		}
		outputs.push_back(temp);
	}
	int sum = 0;
	for (unsigned int i = 0; i < patterns.size(); i++) {
		std::vector<std::string> digits(10, "");
		for (auto s : patterns[i]) {
			if (s.size() == 2)
				digits[1] = s;
			if (s.size() == 4)
				digits[4] = s;
			if (s.size() == 3)
				digits[7] = s;
			if (s.size() == 7)
				digits[8] = s;
		}
		for (auto s : patterns[i]) {
			if (s.size() == 6 && stringAND(s, digits[4]).size() == 4) {
				digits[9] = s;
				break;
			}
		}
		for (auto s : patterns[i]) {
			if (s.size() == 6 && !stringEQUALS(s, digits[9]) && stringAND(s, digits[1]).size() == 2) {
				digits[0] = s;
				break;
			}
		}
		for (auto s : patterns[i]) {
			if (s.size() == 6 && !stringEQUALS(s, digits[9]) && !stringEQUALS(s, digits[0])) {
				digits[6] = s;
				break;
			}
		}
		for (auto s : patterns[i]) {
			if (s.size() == 5 && stringAND(s, digits[1]).size() == 2) {
				digits[3] = s;
				break;
			}
		}
		for (auto s : patterns[i]) {
			if (s.size() == 5 && !stringEQUALS(s, digits[3])) {
				if (stringAND(s, digits[4]).size() == 2)
					digits[2] = s;
				if (stringAND(s, digits[4]).size() == 3)
					digits[5] = s;
			}
		}
		std::string finalNumber = "";
		for (auto& x : outputs[i]) {
			for (int i = 0; i < digits.size(); i++)
				if (stringEQUALS(x, digits[i])) {
					finalNumber = finalNumber + std::to_string(i);
				}
		}
		sum = sum + std::stoi(finalNumber);
	}
	std::cout << "The final value is: " << sum;
	input.close();
}

void basinF(int i, int j, std::vector<std::vector<std::pair<int, bool>>>& points, int& basin) {
	int n = points.size();
	int m = points[0].size();
	if (i == 0 && j == 0) {
		if (!points[i + 1][j].second && points[i + 1][j].first != 9 && points[i + 1][j].first > points[i][j].first) {
			points[i + 1][j].second = true;
			basin++;
			basinF(i + 1, j, points, basin);
		}
		if (!points[i][j + 1].second && points[i][j + 1].first != 9 && points[i][j + 1].first > points[i][j].first) {
			points[i][j + 1].second = true;
			basin++;
			basinF(i, j + 1, points, basin);
		}
	}
	else if (i == 0 && j == m - 1) {
		if (!points[i + 1][j].second && points[i + 1][j].first != 9 && points[i + 1][j].first > points[i][j].first) {
			points[i + 1][j].second = true;
			basin++;
			basinF(i + 1, j, points, basin);
		}
		if (!points[i][j - 1].second && points[i][j - 1].first != 9 && points[i][j - 1].first > points[i][j].first) {
			points[i][j - 1].second = true;
			basin++;
			basinF(i, j - 1, points, basin);
		}
	}
	else if (i == n - 1 && j == 0) {
		if (!points[i - 1][j].second && points[i - 1][j].first != 9 && points[i - 1][j].first > points[i][j].first) {
			points[i - 1][j].second = true;
			basin++;
			basinF(i - 1, j, points, basin);
		}
		if (!points[i][j + 1].second && points[i][j + 1].first != 9 && points[i][j + 1].first > points[i][j].first) {
			points[i][j + 1].second = true;
			basin++;
			basinF(i, j + 1, points, basin);
		}
	}
	else if (i == n - 1 && j == m - 1) {
		if (!points[i - 1][j].second && points[i - 1][j].first != 9 && points[i - 1][j].first > points[i][j].first) {
			points[i - 1][j].second = true;
			basin++;
			basinF(i - 1, j, points, basin);
		}
		if (!points[i][j - 1].second && points[i][j - 1].first != 9 && points[i][j - 1].first > points[i][j].first) {
			points[i][j - 1].second = true;
			basin++;
			basinF(i, j - 1, points, basin);
		}
	}
	else if (i == 0) {
		if (!points[i + 1][j].second && points[i + 1][j].first != 9 && points[i + 1][j].first > points[i][j].first) {
			points[i + 1][j].second = true;
			basin++;
			basinF(i + 1, j, points, basin);
		}
		if (!points[i][j + 1].second && points[i][j + 1].first != 9 && points[i][j + 1].first > points[i][j].first) {
			points[i][j + 1].second = true;
			basin++;
			basinF(i, j + 1, points, basin);
		}
		if (!points[i][j - 1].second && points[i][j - 1].first != 9 && points[i][j - 1].first > points[i][j].first) {
			points[i][j - 1].second = true;
			basin++;
			basinF(i, j - 1, points, basin);
		}
	}
	else if (j == 0) {
		if (!points[i + 1][j].second && points[i + 1][j].first != 9 && points[i + 1][j].first > points[i][j].first) {
			points[i + 1][j].second = true;
			basin++;
			basinF(i + 1, j, points, basin);
		}
		if (!points[i][j + 1].second && points[i][j + 1].first != 9 && points[i][j + 1].first > points[i][j].first) {
			points[i][j + 1].second = true;
			basin++;
			basinF(i, j + 1, points, basin);
		}
		if (!points[i - 1][j].second && points[i - 1][j].first != 9 && points[i - 1][j].first > points[i][j].first) {
			points[i - 1][j].second = true;
			basin++;
			basinF(i - 1, j, points, basin);
		}
	}
	else if (i == n - 1) {
		if (!points[i - 1][j].second && points[i - 1][j].first != 9 && points[i - 1][j].first > points[i][j].first) {
			points[i - 1][j].second = true;
			basin++;
			basinF(i - 1, j, points, basin);
		}
		if (!points[i][j + 1].second && points[i][j + 1].first != 9 && points[i][j + 1].first > points[i][j].first) {
			points[i][j + 1].second = true;
			basin++;
			basinF(i, j + 1, points, basin);
		}
		if (!points[i][j - 1].second && points[i][j - 1].first != 9 && points[i][j - 1].first > points[i][j].first) {
			points[i][j - 1].second = true;
			basin++;
			basinF(i, j - 1, points, basin);
		}
	}
	else if (j == m - 1) {
		if (!points[i + 1][j].second && points[i + 1][j].first != 9 && points[i + 1][j].first > points[i][j].first) {
			points[i + 1][j].second = true;
			basin++;
			basinF(i + 1, j, points, basin);
		}
		if (!points[i][j - 1].second && points[i][j - 1].first != 9 && points[i][j - 1].first > points[i][j].first) {
			points[i][j - 1].second = true;
			basin++;
			basinF(i, j - 1, points, basin);
		}
		if (!points[i - 1][j].second && points[i - 1][j].first != 9 && points[i - 1][j].first > points[i][j].first) {
			points[i - 1][j].second = true;
			basin++;
			basinF(i - 1, j, points, basin);
		}
	}
	else {
		if (!points[i + 1][j].second && points[i + 1][j].first != 9 && points[i + 1][j].first > points[i][j].first) {
			points[i + 1][j].second = true;
			basin++;
			basinF(i + 1, j, points, basin);
		}
		if (!points[i][j + 1].second && points[i][j + 1].first != 9 && points[i][j + 1].first > points[i][j].first) {
			points[i][j + 1].second = true;
			basin++;
			basinF(i, j + 1, points, basin);
		}
		if (!points[i - 1][j].second && points[i - 1][j].first != 9 && points[i - 1][j].first > points[i][j].first) {
			points[i - 1][j].second = true;
			basin++;
			basinF(i - 1, j, points, basin);
		}
		if (!points[i][j - 1].second && points[i][j - 1].first != 9 && points[i][j - 1].first > points[i][j].first) {
			points[i][j - 1].second = true;
			basin++;
			basinF(i, j - 1, points, basin);
		}
	}
}
void round9() {
	std::ifstream input("inputs/round9.txt");
	std::vector<std::vector<std::pair<int, bool>>> points;
	std::string s;
	while (std::getline(input, s)) {
		std::vector<std::pair<int, bool>> temp;
		for (int i = 0; i < s.size(); i++) {
			temp.push_back({ s[i] - '0',false });
		}
		points.push_back(temp);
		temp.clear();
	}
	int n = points.size();
	int m = points[0].size();
	int sum = 0;
	int numb = 0;
	std::vector<int> basin;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == 0 && j == 0) {
				if (points[i + 1][j].first > points[i][j].first && points[i][j + 1].first > points[i][j].first) {
					points[i][j].second = true;
					sum = sum + points[i][j].first + 1;
					int t = 1;
					basinF(i, j, points, t);
					basin.push_back(t);
				}
			}
			else if (i == 0 && j == m - 1) {
				if (points[i + 1][j].first > points[i][j].first && points[i][j - 1].first > points[i][j].first) {
					points[i][j].second = true;
					int t = 1;
					basinF(i, j, points, t);
					sum = sum + points[i][j].first + 1;
					basin.push_back(t);
				}
			}
			else if (i == n - 1 && j == 0) {
				if (points[i - 1][j].first > points[i][j].first && points[i][j + 1].first > points[i][j].first) {
					points[i][j].second = true;
					sum = sum + points[i][j].first + 1;
					int t = 1;
					basinF(i, j, points, t);
					basin.push_back(t);
				}
			}
			else if (i == n - 1 && j == m - 1) {
				if (points[i - 1][j].first > points[i][j].first && points[i][j - 1].first > points[i][j].first) {
					points[i][j].second = true;
					sum = sum + points[i][j].first + 1;
					int t = 1;
					basinF(i, j, points, t);
					basin.push_back(t);
				}
			}
			else if (i == 0) {
				if (points[i + 1][j].first > points[i][j].first && points[i][j + 1].first > points[i][j].first && points[i][j - 1].first > points[i][j].first) {
					points[i][j].second = true;
					sum = sum + points[i][j].first + 1;
					int t = 1;
					basinF(i, j, points, t);
					basin.push_back(t);
				}
			}
			else if (j == 0) {
				if (points[i + 1][j].first > points[i][j].first && points[i][j + 1].first > points[i][j].first && points[i - 1][j].first > points[i][j].first) {
					points[i][j].second = true;
					sum = sum + points[i][j].first + 1;

					int t = 1;
					basinF(i, j, points, t);
					basin.push_back(t);
				}
			}
			else if (i == n - 1) {
				if (points[i - 1][j].first > points[i][j].first && points[i][j + 1].first > points[i][j].first && points[i][j - 1].first > points[i][j].first) {
					points[i][j].second = true;
					sum = sum + points[i][j].first + 1;
					int t = 1;
					basinF(i, j, points, t);
					basin.push_back(t);
				}
			}
			else if (j == m - 1) {
				if (points[i + 1][j].first > points[i][j].first && points[i][j - 1].first > points[i][j].first && points[i - 1][j].first > points[i][j].first) {
					points[i][j].second = true;
					sum = sum + points[i][j].first + 1;
					int t = 1;
					basinF(i, j, points, t);
					basin.push_back(t);
				}
			}
			else {
				if (points[i - 1][j].first > points[i][j].first && points[i + 1][j].first > points[i][j].first && points[i][j + 1].first > points[i][j].first
					&& points[i][j - 1].first > points[i][j].first) {
					points[i][j].second = true;
					sum = sum + points[i][j].first + 1;
					int t = 1;
					basinF(i, j, points, t);
					basin.push_back(t);
				}
			}
		}
	}
	std::cout << basin.size();
	std::sort(basin.begin(), basin.end(), [](int& a, int& b) {return a > b; });
	std::cout << " " << basin[0] * basin[1] * basin[2];
}

void round10() {
	std::ifstream input("inputs/round10.txt");
	std::vector<std::string> lines;
	std::string s;
	std::vector<long long> values;
	while (std::getline(input, s)) {
		lines.push_back(s);
	}
	int round = 0;
	int box = 0;
	int curly = 0;
	int angle = 0;
	for (std::string& s : lines) {
		std::stack<char> stack;
		for (char c : s) {
			if (c == '{' || c == '[' || c == '(' || c == '<') {
				stack.push(c);
			}
			else if (!stack.empty()) {
				if (c == '}' && stack.top() == '{') {
					stack.pop();
				}
				else if (c == ']' && stack.top() == '[') {
					stack.pop();
				}
				else if (c == ')' && stack.top() == '(') {
					stack.pop();
				}
				else if (c == '>' && stack.top() == '<') {
					stack.pop();
				}
				else {
					if (c == '}') curly++;
					if (c == ']') box++;
					if (c == ')') round++;
					if (c == '>') angle++;
					while (!stack.empty())
						stack.pop();
					break;
				}
			}
			else {
				break;
			}
		}
		long long value = 0;
		if (!stack.empty()) {
			while (!stack.empty()) {
				value = value * (long long)5;
				if (stack.top() == '{') {
					value = value + (long long)3;
				}
				if (stack.top() == '[') {
					value = value + (long long)2;
				}
				if (stack.top() == '(') {
					value = value + (long long)1;
				}
				if (stack.top() == '<') {
					value = value + (long long)4;
				}
				stack.pop();
			}
			values.push_back(value);
		}
	}
	std::sort(values.begin(), values.end());
	std::cout << values[(values.size() - 1) / 2] << " " << values.size();
	input.close();
}

void flash(std::vector<std::vector<int>>& v, int i, int j, int n, int m, std::set<std::pair<int, int>>& flashed) {
	flashed.insert({ i,j });
	for (int k = i - 1; k <= i + 1; k++) {
		for (int l = j - 1; l <= j + 1; l++) {
			if (k < 0 || k >= n || l < 0 || l >= m || flashed.contains({ k,l })) {
				continue;
			}
			else {
				v[k][l]++;
				if (v[k][l] > 9) {
					flash(v, k, l, n, m, flashed);
				}
			}
		}
	}
}
void round11() {
	std::ifstream input("inputs/round11.txt");
	std::vector<std::vector<int>> octopuses;
	std::string s;
	while (std::getline(input, s)) {
		std::vector<int> temp;
		for (int i = 0; i < s.size(); i++) {
			temp.push_back(s[i] - '0');
		}
		octopuses.push_back(temp);
		temp.clear();
	}
	std::set<std::pair<int, int>> alreadyFlashed;
	int n = octopuses.size();
	int m = octopuses[0].size();
	int flashes = 0;
	for (int steps = 0; steps < 300; steps++) {
		alreadyFlashed.clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				octopuses[i][j]++;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (octopuses[i][j] > 9 && !alreadyFlashed.contains({ i,j }))
					flash(octopuses, i, j, n, m, alreadyFlashed);
			}
		}
		for_each(alreadyFlashed.begin(), alreadyFlashed.end(), [&octopuses](auto& x) {
			octopuses[x.first][x.second] = 0;
			});
		flashes = flashes + alreadyFlashed.size();
		if (alreadyFlashed.size() == 100) {
			std::cout << "All octopuses have just flashed at the same time after " << steps + 1 << " steps." << std::endl;
		}
	}
	std::cout << "After 10 steps there have been a total of " << flashes << " flashes.";
	input.close();
}

void findPaths(std::string s, std::map<std::string, std::vector<std::string>> branches, int& totalPaths, std::string twice, int visited, std::vector<std::string> path = {}) {
	path.push_back(s);
	if (s == "end") {
		if (twice != " ") {
			std::map<std::string, int> countMap;
			for (auto& elem : path)
			{
				if (std::any_of(elem.begin(), elem.end(), &::islower)) {
					auto result = countMap.insert(std::pair<std::string, int>(elem, 1));
					if (result.second == false)
						result.first->second++;
				}
			}
			bool twice = false;
			for (auto& elem : countMap)
			{

				if (elem.second > 1)
				{
					twice = true;
				}
			}
			if (!twice) {
				return;
			}
		}
		totalPaths++;
		/*for (int i = 0; i < path.size(); i++)
			std::cout << path[i] << "-";
		std::cout << "pathend" << std::endl;*/
		return;
	}
	if (s == twice)
		visited--;
	if (std::any_of(s.begin(), s.end(), &::islower)) {
		for (auto it = branches.begin(); it != branches.end(); ++it) {
			auto v = it->second;
			if ((s == twice && visited <= 0) || s != twice) {
				v.erase((std::remove_if(v.begin(), v.end(), [s, visited](std::string x) {
					if (x == s) {
						return true;
					}
					else {
						return false;
					}
					})), v.end());
				it->second = v;
			}
		}
	}
	if (branches.count(s) != 0) {
		for (auto it = branches[s].begin(); it != branches[s].end(); it++) {
			findPaths(*it, branches, totalPaths, twice, visited, path);
		}
	}
}
void round12() {
	std::ifstream input("inputs/round12.txt");
	std::map<std::string, std::vector<std::string>> branches;
	std::string s;
	std::string token1;
	std::string token2;
	size_t pos = 0;
	while (std::getline(input, s)) {
		pos = s.find("-");
		token1 = s.substr(0, pos);
		s.erase(0, pos + 1);
		token2 = s;
		branches[token1].push_back(token2);
		branches[token2].push_back(token1);
	}
	std::set <std::string> smallCells;
	for (auto it = branches.begin(); it != branches.end(); it++) {
		auto v = it->first;
		if (std::any_of(v.begin(), v.end(), &::islower)) {
			smallCells.insert(v);
		}
	}
	int totalPaths = 0;
	std::set<std::string>::iterator it = smallCells.begin();
	while (it != smallCells.end()) {
		if (*it != "start" && *it != "end") {
			findPaths("start", branches, totalPaths, *it, 2);
		}
		//std::cout << "gotovo=" << *it << "=" << std::endl;
		it++;
	}
	findPaths("start", branches, totalPaths, " ", 0);
	std::cout << "There are: " << totalPaths << " paths.";
	input.close();
}

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
int main() {
	round13();
	return 0;
}

