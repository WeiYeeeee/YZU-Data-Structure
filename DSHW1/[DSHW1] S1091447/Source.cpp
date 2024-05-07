#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include<vector>
using namespace std;
struct testcase {
	string name;
	vector<int> value;
};
vector<testcase> declare;
vector<testcase>::iterator findName(string target)
{
	vector<testcase>::iterator it = declare.begin();
	for (; it != declare.end(); ++it)
	{
		if (it->name == target)
			return it;
	}
	return declare.end();
}
bool next_line = false;
bool error_case = false;
bool check_for = false;
bool check_if = false;
bool check_else = false;
bool find_for(string str_case) {
	int index = 0;
	while ((index = str_case.find("for", index)) != string::npos) {
		if ((index = str_case.find('f', index)) != string::npos) {
			if (str_case[index + 1] == 'o' && str_case[index + 2] == 'r') {
				if (index == 0) {
					if (str_case.length() == 3) {
						return  true;
						break;
					}
					else {
						if (str_case[index + 3] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
				}
				else {
					if ((index + 2) == (str_case.length() - 1)) {
						if (str_case[index - 1] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
					else {
						if (str_case[index - 1] == ' ' && str_case[index + 3] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
				}
			}
			else
				index++;
		}
		else {
			return false;
			break;
		}
	}
	return false;
}
bool find_if(string str_case) {
	int index = 0;
	while ((index = str_case.find("if", index)) != string::npos) {
		if ((index = str_case.find('i', index)) != string::npos) {
			if (str_case[index + 1] == 'f') {
				if (index == 0) {
					if (str_case.length() == 2) {
						return  true;
						break;
					}
					else {
						if (str_case[index + 2] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
				}
				else {
					if ((index + 1) == (str_case.length() - 1)) {
						if (str_case[index - 1] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
					else {
						if (str_case[index - 1] == ' ' && str_case[index + 2] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
				}
			}
			else
				index++;
		}
		else {
			return  false;
			break;
		}
	}
	return  false;
}
bool find_else(string str_case)
{
	int index = 0;
	while ((index = str_case.find("else", index)) != string::npos) {
		if ((index = str_case.find('e', index)) != string::npos) {
			if (str_case[index + 1] == 'l' && str_case[index + 2] == 's' && str_case[index + 3] == 'e') {
				if (index == 0) {
					if (str_case.length() == 4) {
						return  true;
						break;
					}
					else {
						if (str_case[index + 4] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
				}
				else {
					if ((index + 3) == (str_case.length() - 1)) {
						if (str_case[index - 1] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
					else {
						if (str_case[index - 1] == ' ' && str_case[index + 4] == ' ') {
							return  true;
							break;
						}
						else
							index++;
					}
				}
			}
			else
				index++;
		}
		else {
			return  false;
			break;
		}
	}
	return  false;
}
bool check_line_up(string str_case_1, string str_case_2)
{
	int size_str_case_1 = str_case_1.length() - 1;
	int size_str_case_2 = str_case_2.length() - 1;
	if ((str_case_1[size_str_case_1] == '+') || (str_case_1[size_str_case_1] == '-') || (str_case_1[size_str_case_1] == '*') || (str_case_1[size_str_case_1] == '/') || (str_case_1[size_str_case_1] == '%') || (str_case_1[size_str_case_1] == '(') || (str_case_1[size_str_case_1] == '[') || (str_case_1[size_str_case_1] == '{') || (str_case_1[size_str_case_1] == ',') || (str_case_1[size_str_case_1] == ':'))
	{
		return true;
	}
	else if ((str_case_2[0] == '+') || (str_case_2[0] == '-') || (str_case_2[0] == '*') || (str_case_2[0] == '/') || (str_case_2[0] == '%') || (str_case_2[0] == ')') || (str_case_2[0] == ']') || (str_case_2[0] == '}') || (str_case_2[0] == ',') || (str_case_2[0] == ':'))
	{
		return true;
	}
	return false;
}
string delete_hashtag(string str_case) {
	int pos_hashtag = find(str_case.begin(), str_case.end(), '#') - str_case.begin();
	if (pos_hashtag != str_case.length())
		str_case.erase(pos_hashtag);
	return str_case;
}
string delete_space(string str_case)
{
	int index = 0;
	if (!str_case.empty()) {
		while ((index = str_case.find(' ', index)) != string::npos)
			str_case.erase(index, 1);
	}
	return str_case;
}
string simplify_operator(string str_case) {
	int index = 0;
	if (!str_case.empty()) {
		while ((index = str_case.find("%/%", index)) != string::npos) {
			str_case[index] = '/';
			str_case.erase(++index, 2);
		}
		index = 0;
		while ((index = str_case.find("%%", index)) != string::npos) {
			str_case[index] = '%';
			str_case.erase(++index, 1);
		}
	}
	return str_case;
}
int prec(char c) {
	if (c == '/' || c == '*' || c == '%')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}
vector<string> postfix(string str) {
	vector<char> symbol_operation;
	vector<string> str1;
	string temp;
	for (int i = 0; i < str.length(); i++) {
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
			temp += str[i];
		else if (str[i] == '(')
			symbol_operation.push_back('(');
		else if (str[i] == ')') {
			str1.push_back(temp);
			temp = "";
			while (symbol_operation.back() != '(') {
				temp += symbol_operation.back();
				str1.push_back(temp);
				temp = "";
				symbol_operation.pop_back();
			}
			if (temp != "") {
				str1.push_back(temp);
				temp = "";
			}
			symbol_operation.pop_back();
		}
		else {
			if (temp != "") {
				str1.push_back(temp);
				temp = "";
			}
			while (!symbol_operation.empty() && prec(str[i]) <= prec(symbol_operation.back())) {
				temp += symbol_operation.back();
				str1.push_back(temp);
				temp = "";
				symbol_operation.pop_back();
			}
			if (temp != "") {
				str1.push_back(temp);
				temp = "";
			}
			symbol_operation.push_back(str[i]);
		}
	}
	while (!symbol_operation.empty()) {
		if (temp != "") {
			str1.push_back(temp);
			temp = "";
		}
		temp += symbol_operation.back();
		str1.push_back(temp);
		temp = "";
		symbol_operation.pop_back();
	}
	return str1;
}
vector<int> plus_sign(vector<int> num1, vector<int>num2)
{
	if (num1.size() > num2.size()) {
		for (int i = 0; i < num1.size(); i++)
			num1[i] += num2[i % num2.size()];
		return num1;
	}
	else {
		for (int i = 0; i < num2.size(); i++)
			num2[i] += num1[i % num1.size()];
		return num2;
	}
}
vector<int> minus_sign(vector<int> num1, vector<int>num2)
{
	if (num1.size() > num2.size())
	{
		for (int i = 0; i < num1.size(); i++)
		{
			num1[i] -= num2[i % num2.size()];
		}
		return num1;
	}
	else
	{
		for (int i = 0; i < num2.size(); i++)
		{
			num2[i] = num1[i % num1.size()] - num2[i];
		}
		return num2;
	}
}
vector<int> multiplication_sign(vector<int> num1, vector<int>num2)
{
	if (num1.size() > num2.size())
	{
		for (int i = 0; i < num1.size(); i++)
		{
			num1[i] *= num2[i % num2.size()];
		}
		return num1;
	}
	else
	{
		for (int i = 0; i < num2.size(); i++)
		{
			num2[i] *= num1[i % num1.size()];
		}
		return num2;
	}
}
vector<int> division_sign(vector<int> num1, vector<int>num2)
{
	if (num1.size() > num2.size())
	{
		for (int i = 0; i < num1.size(); i++)
		{
			num1[i] /= num2[i % num2.size()];
		}
		return num1;
	}
	else
	{
		for (int i = 0; i < num2.size(); i++)
		{
			num2[i] = num1[i % num1.size()] / num2[i];
		}
		return num2;
	}
}
vector<int> modulo_sign(vector<int> num1, vector<int>num2)
{
	if (num1.size() > num2.size())
	{
		for (int i = 0; i < num1.size(); i++)
		{
			num1[i] %= num2[i % num2.size()];
		}
		return num1;
	}
	else
	{
		for (int i = 0; i < num2.size(); i++)
		{
			num2[i] = num1[i % num1.size()] % num2[i];
		}
		return num2;
	}
}
vector<int> math(string str1)
{
	vector<string> str;
	vector<vector<int>> num;
	vector <int> temp;
	vector<int> error_value;
	error_value.push_back(-1);
	str = postfix(str1);
	for (int i = 0; i < str.size(); i++)
	{
		if (error_case == false)
		{
			if (str[i] == "+")
			{
				if (num.size() < 2)
					error_case = true;
				else
					temp = plus_sign(num[num.size() - 2], num[num.size() - 1]);
				num.pop_back();
				num.pop_back();
				num.push_back(temp);
				temp.clear();
			}
			else if (str[i] == "-")
			{
				if (num.size() < 2)
					error_case = true;
				else
					temp = minus_sign(num[num.size() - 2], num[num.size() - 1]);
				num.pop_back();
				num.pop_back();
				num.push_back(temp);
				temp.clear();
			}
			else if (str[i] == "*")
			{
				if (num.size() < 2)
					error_case = true;
				else
					temp = multiplication_sign(num[num.size() - 2], num[num.size() - 1]);
				num.pop_back();
				num.pop_back();
				num.push_back(temp);
				temp.clear();
			}
			else if (str[i] == "/")
			{
				if (num.size() < 2)
					error_case = true;
				else
					temp = division_sign(num[num.size() - 2], num[num.size() - 1]);
				num.pop_back();
				num.pop_back();
				num.push_back(temp);
				temp.clear();
			}
			else if (str[i] == "%")
			{
				if (num.size() < 2)
					error_case = true;
				else
					temp = modulo_sign(num[num.size() - 2], num[num.size() - 1]);
				num.pop_back();
				num.pop_back();
				num.push_back(temp);
				temp.clear();
			}
			else
			{
				if ((str[i].find("a") != string::npos) || (str[i].find("b") != string::npos) || (str[i].find("c") != string::npos) || (str[i].find("d") != string::npos) || (str[i].find("e") != string::npos) || (str[i].find("f") != string::npos) || (str[i].find("g") != string::npos) || (str[i].find("h") != string::npos) || (str[i].find("i") != string::npos) || (str[i].find("j") != string::npos) || (str[i].find("k") != string::npos) || (str[i].find("l") != string::npos) || (str[i].find("m") != string::npos) || (str[i].find("n") != string::npos) || (str[i].find("o") != string::npos) || (str[i].find("p") != string::npos) || (str[i].find("q") != string::npos) || (str[i].find("r") != string::npos) || (str[i].find("s") != string::npos) || (str[i].find("t") != string::npos) || (str[i].find("u") != string::npos) || (str[i].find("v") != string::npos) || (str[i].find("w") != string::npos) || (str[i].find("x") != string::npos) || (str[i].find("y") != string::npos) || (str[i].find("z") != string::npos) ||
					(str[i].find("A") != string::npos) || (str[i].find("B") != string::npos) || (str[i].find("C") != string::npos) || (str[i].find("D") != string::npos) || (str[i].find("E") != string::npos) || (str[i].find("F") != string::npos) || (str[i].find("G") != string::npos) || (str[i].find("H") != string::npos) || (str[i].find("I") != string::npos) || (str[i].find("J") != string::npos) || (str[i].find("K") != string::npos) || (str[i].find("L") != string::npos) || (str[i].find("M") != string::npos) || (str[i].find("N") != string::npos) || (str[i].find("O") != string::npos) || (str[i].find("P") != string::npos) || (str[i].find("Q") != string::npos) || (str[i].find("R") != string::npos) || (str[i].find("S") != string::npos) || (str[i].find("T") != string::npos) || (str[i].find("U") != string::npos) || (str[i].find("V") != string::npos) || (str[i].find("W") != string::npos) || (str[i].find("X") != string::npos) || (str[i].find("Y") != string::npos) || (str[i].find("Z") != string::npos))
				{
					vector<testcase>::iterator it = findName(str[i]);
					if (it != declare.end())
					{
						num.push_back(it->value);
					}
					else
						error_case = true;
				}
				else if ((str[i].find("0") != string::npos) || (str[i].find("1") != string::npos) || (str[i].find("2") != string::npos) || (str[i].find("3") != string::npos) || (str[i].find("4") != string::npos) || (str[i].find("5") != string::npos) || (str[i].find("6") != string::npos) || (str[i].find("7") != string::npos) || (str[i].find("8") != string::npos) || (str[i].find("9") != string::npos))
				{
					temp.push_back(stoi(str[i]));
					num.push_back(temp);
					temp.clear();
				}
			}
		}
	}
	str.clear();
	temp.clear();
	if (error_case == false)
		return num[0];
	else
		return error_value;
}

void function_process(string str_case_1, string str_case_2)
{
	// 刪除 #以後的字元
	str_case_1 = delete_hashtag(str_case_1);
	str_case_1 = delete_space(str_case_1);
	str_case_1 = simplify_operator(str_case_1);
	if (str_case_2 != "") {
		str_case_2 = delete_hashtag(str_case_2);
		str_case_2 = delete_space(str_case_2);
		str_case_2 = simplify_operator(str_case_2);
		if (check_line_up(str_case_1, str_case_2) == true)
		{
			next_line = true;
			str_case_1 += str_case_2;
		}
		else
		{
			next_line = false;
		}
	}
	if (str_case_1.find('=') != string::npos)
	{
		int pos_equalsign = find(str_case_1.begin(), str_case_1.end(), '=') - str_case_1.begin();
		testcase t1;
		t1.name = str_case_1.substr(0, pos_equalsign);
		str_case_1.erase(0, ++pos_equalsign);
		if ((str_case_1.find("c(") != string::npos) || (str_case_1.find(",") != string::npos) || (str_case_1.find(":") != string::npos))
		{
			if ((str_case_1.find("c(") != string::npos) && (str_case_1.find(",") != string::npos) && (str_case_1.find(":") != string::npos))
			{
				int count = 0;
				string str1 = "", str2 = "";
				int index = 0;
				if (!str_case_1.empty()) {
					while ((index = str_case_1.find("c(", index)) != string::npos) {
						str_case_1.erase(index, 2);
						count++;
					}
				}
				index = 0;
				if (!str_case_1.empty()) {
					while ((index = str_case_1.find(')', index)) != string::npos) {
						str_case_1.erase(index, 1);
						count--;
					}
				}
				if (count != 0)
					error_case = true;
				if (error_case == false) {
					bool find_colon = false;
					for (int i = 0; i < str_case_1.length(); i++) {
						if ((str_case_1[i] == ',') || (i == str_case_1.length() - 1)) {
							if (i == str_case_1.length() - 1)
								str1 += str_case_1[i];
							int a = stoi(str1);
							if (find_colon == true) {
								int b = stoi(str2);
								for (int i = 0; i <= abs(b - a); i++) {
									if (b < a)
										t1.value.push_back(b + i);
									else
										t1.value.push_back(b - i);
								}
								str1 = "";
								str2 = "";
								find_colon = false;
							}
							else {
								t1.value.push_back(a);
								str1 = "";
							}
						}
						else if (str_case_1[i] == ':') {
							find_colon = true;
							str2 = str1;
							str1 = "";
						}
						else
							str1 += str_case_1[i];
					}
					vector<testcase>::iterator it = findName(t1.name);
					if (it != declare.end()) {
						it->value = t1.value;
					}
					else
						declare.push_back(t1);
				}
			}
			else if ((str_case_1.find("c(") != string::npos) && (str_case_1.find(",") != string::npos))
			{
				int count = 0;
				string str1 = "";
				int index = 0;
				if (!str_case_1.empty()) {
					while ((index = str_case_1.find("c(", index)) != string::npos) {
						str_case_1.erase(index, 2);
						count++;
					}
				}
				index = 0;
				if (!str_case_1.empty()) {
					while ((index = str_case_1.find(')', index)) != string::npos) {
						str_case_1.erase(index, 1);
						count--;
					}
				}
				if (count != 0)
					error_case = true;
				if (error_case == false) {
					for (int i = 0; i < str_case_1.length(); i++) {
						if ((str_case_1[i] == ',') || (i == str_case_1.length() - 1)) {
							if (i == str_case_1.length() - 1)
								str1 += str_case_1[i];
							int a = stoi(str1);
							t1.value.push_back(a);
							str1 = "";
						}
						else
							str1 += str_case_1[i];
					}
					vector<testcase>::iterator it = findName(t1.name);
					if (it != declare.end()) {
						it->value = t1.value;
					}
					else
						declare.push_back(t1);
				}
			}
			else if (str_case_1.find(":") != string::npos)
			{
				string str1 = "", str2 = "";
				bool find_colon = false;
				for (int i = 0; i < str_case_1.length(); i++) {
					if (str_case_1[i] != ':')
						str1 += str_case_1[i];
					else {
						str2 = str1;
						str1 = "";
					}
				}
				int a = stoi(str1);
				int b = stoi(str2);
				for (int i = 0; i <= abs(b - a); i++) {
					if (b < a)
						t1.value.push_back(b + i);
					else
						t1.value.push_back(b - i);
				}
				vector<testcase>::iterator it = findName(t1.name);
				if (it != declare.end()) {
					it->value = t1.value;
				}
				else
					declare.push_back(t1);
			}
			else
			{
				error_case = true;
			}
		}
		else if ((str_case_1.find('+') != string::npos) || (str_case_1.find('-') != string::npos) || (str_case_1.find('*') != string::npos) || (str_case_1.find('/') != string::npos) || (str_case_1.find('%') != string::npos)) {
			t1.value = math(str_case_1);
			if (error_case == false)
			{
				vector<testcase>::iterator it = findName(t1.name);
				if (it != declare.end()) {
					it->value = t1.value;
				}
				else
					declare.push_back(t1);
			}
		}
		else
		{
			if ((str_case_1.find('a') != string::npos) || (str_case_1.find('b') != string::npos) || (str_case_1.find('c') != string::npos) || (str_case_1.find('d') != string::npos) || (str_case_1.find('e') != string::npos) || (str_case_1.find('f') != string::npos) || (str_case_1.find('g') != string::npos) || (str_case_1.find('h') != string::npos) || (str_case_1.find('i') != string::npos) || (str_case_1.find('j') != string::npos) || (str_case_1.find('k') != string::npos) || (str_case_1.find('l') != string::npos) || (str_case_1.find('m') != string::npos) || (str_case_1.find('n') != string::npos) || (str_case_1.find('o') != string::npos) || (str_case_1.find('p') != string::npos) || (str_case_1.find('q') != string::npos) || (str_case_1.find('r') != string::npos) || (str_case_1.find('s') != string::npos) || (str_case_1.find('t') != string::npos) || (str_case_1.find('u') != string::npos) || (str_case_1.find('v') != string::npos) || (str_case_1.find('w') != string::npos) || (str_case_1.find('x') != string::npos) || (str_case_1.find('y') != string::npos) || (str_case_1.find('z') != string::npos) ||
				(str_case_1.find('A') != string::npos) || (str_case_1.find('B') != string::npos) || (str_case_1.find('C') != string::npos) || (str_case_1.find('D') != string::npos) || (str_case_1.find('E') != string::npos) || (str_case_1.find('F') != string::npos) || (str_case_1.find('G') != string::npos) || (str_case_1.find('H') != string::npos) || (str_case_1.find('I') != string::npos) || (str_case_1.find('J') != string::npos) || (str_case_1.find('K') != string::npos) || (str_case_1.find('L') != string::npos) || (str_case_1.find('M') != string::npos) || (str_case_1.find('N') != string::npos) || (str_case_1.find('O') != string::npos) || (str_case_1.find('P') != string::npos) || (str_case_1.find('Q') != string::npos) || (str_case_1.find('R') != string::npos) || (str_case_1.find('S') != string::npos) || (str_case_1.find('T') != string::npos) || (str_case_1.find('U') != string::npos) || (str_case_1.find('V') != string::npos) || (str_case_1.find('W') != string::npos) || (str_case_1.find('X') != string::npos) || (str_case_1.find('Y') != string::npos) || (str_case_1.find('Z') != string::npos))
			{
				//有英文字母
				vector<testcase>::iterator it = findName(str_case_1);
				if (it != declare.end()) {
					t1.value = it->value;
				}
				else {
					error_case = true;
				}
			}
			else
			{
				//純數字
				int temp_num1 = stoi(str_case_1);
				t1.value.push_back(temp_num1);
				declare.push_back(t1);
			}
		}
	}
	else
	{

		//沒有等號 1.X 2.x+y 3. z[5] 
		bool negative_integer = false;
		bool need_math = false;
		string str_case_temp;
		if ((str_case_1.find('[') != string::npos) || (str_case_1.find(']') != string::npos))
		{
			if ((str_case_1.find('[') != string::npos) && (str_case_1.find(']') != string::npos))
			{
				testcase t1;
				int pos_square_brackets_left = find(str_case_1.begin(), str_case_1.end(), '[') - str_case_1.begin();
				int pos_square_brackets_right = find(str_case_1.begin(), str_case_1.end(), ']') - str_case_1.begin();

				for (int i = pos_square_brackets_left + 1; i < pos_square_brackets_right; i++)
				{
					if ((str_case_1[i] == '+') || (str_case_1[i] == '-') || (str_case_1[i] == '*') || (str_case_1[i] == '/') || (str_case_1[i] == '%') || (str_case_1[i] == '(') || (str_case_1[i] == ')'))
					{
						if (str_case_1[pos_square_brackets_left + 1] == '-')
							negative_integer = true;
						else
							need_math = true;
					}
					str_case_temp += str_case_1[i];
				}
				int num = 0;
				vector <int> num_temp;
				//弄框框裡面的元素
				if (negative_integer == true && need_math == true)
				{
					str_case_temp.insert(0, "0");
					num_temp = math(str_case_temp);
					if (error_case == false)
					{
						if (num_temp.size() > 1)
							error_case = true;
						else
							num = num_temp[0];
						num_temp.clear();
					}
				}
				else if (need_math == true)
				{
					num_temp = math(str_case_temp);
					if (error_case == false)
					{
						if (num_temp.size() > 1)
							error_case = true;
						else if (error_case == false)
							num = num_temp[0];
						num_temp.clear();
					}
				}
				else if (negative_integer == true)
				{
					num = stoi(str_case_temp);
				}
				else
				{
					num = stoi(str_case_temp);
				}
				if (error_case == false)
				{
					t1.name = str_case_1.substr(0, pos_square_brackets_left);
					str_case_1.erase(0, ++pos_square_brackets_right);
					if (str_case_1.length() != 0)
					{
						vector<testcase>::iterator it = findName(t1.name);
						if (it != declare.end())
						{
							t1.value = it->value;
						}
						else
						{
							error_case = true;
						}
						if (error_case != true)
						{
							if (num < 0)
							{
								int num_temp2 = 0 - num;
								if (num_temp2 - 1 > t1.value.size())
								{
									error_case = true;
								}
								else
								{
									auto iter = t1.value.erase(t1.value.begin() + num_temp2 - 1);
									vector<testcase>::iterator it = findName(t1.name);
									if (it != declare.end())
									{
										it->value = t1.value;
									}
									str_case_1.insert(0, t1.name);
									t1.value = math(str_case_1);
									if (error_case == false)
									{
										for (int i = 0; i < t1.value.size(); i++) {
											cout << t1.value[i];
											if (i != t1.value.size() - 1)
												cout << " ";
											else
												cout << endl;
										}
									}
								}
							}
							else
							{
								if (num - 1 > t1.value.size()) {
									error_case = true;
								}
								else {
									str_case_1.insert(0, to_string(t1.value[--num]));
									for (int i = 0; i < t1.value.size(); i++) {
										cout << t1.value[i];
										if (i != t1.value.size() - 1)
											cout << " ";
										else
											cout << endl;
									}
								}
							}
						}
					}
					else {
						vector<testcase>::iterator it = findName(t1.name);
						if (it != declare.end()) {
							t1.value = it->value;
						}
						else {
							error_case = true;
						}
						if (error_case != true) {
							if (num < 0)
							{
								int num_temp2 = 0 - num;
								if (num_temp2 > t1.value.size()) {
									cout << "NA" << endl;
								}
								else {
									auto iter = t1.value.erase(t1.value.begin() + num_temp2 - 1);
									for (int i = 0; i < t1.value.size(); i++) {
										cout << t1.value[i];
										if (i != t1.value.size() - 1)
											cout << " ";
										else
											cout << endl;
									}
								}
							}
							else
							{
								if (num > t1.value.size()) {
									cout << "NA" << endl;
								}
								else {
									cout << t1.value[--num] << endl;
								}
							}
						}
					}
				}
			}
			else {
				error_case = true;
			}
			str_case_1 = "";
		}
		else if ((str_case_1.find('+') != string::npos) || (str_case_1.find('-') != string::npos) || (str_case_1.find('*') != string::npos) || (str_case_1.find('/') != string::npos) || (str_case_1.find('%') != string::npos) || (str_case_1.find('(') != string::npos) || (str_case_1.find(')') != string::npos))
		{
			testcase t1;
			t1.value = math(str_case_1);
			if (error_case == false)
			{
				for (int i = 0; i < t1.value.size(); i++) {
					cout << t1.value[i];
					if (i != t1.value.size() - 1)
						cout << " ";
					else
						cout << endl;
				}
			}
		}
		else
		{
			testcase t1;
			t1.name = str_case_1;
			vector<testcase>::iterator it = findName(t1.name);
			if (it != declare.end())
			{
				t1.value = it->value;
				for (int i = 0; i < t1.value.size(); i++) {
					cout << t1.value[i];
					if (i != t1.value.size() - 1)
						cout << " ";
					else
						cout << endl;
				}
			}
			else
			{
				error_case = true;
			}
		}
	}
}
int main(int argc, char* argv[])
{
	string str_input;
	ifstream fin;
	fin.open(argv[1]);
	if (!fin.is_open())
		cout << "Can' t open the file!\n";
	else
	{
		stringstream ss;
		ss << fin.rdbuf();
		string str(ss.str());
		int sentence = 1;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '\n' || str[i] == ';')
				sentence++;
		}
		string* str_case;
		str_case = new string[sentence];
		int k = 0, error_sentence = sentence;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '\n' || str[i] == ';')
				k++;
			else
				str_case[k] += str[i];
		}
		for (int i = 0; i < sentence; i++)
		{
			if (error_case == false)
			{
				if (find_if(str_case[i]) == true)
				{
					check_if = true;
					/**/
				}
				else if (find_else(str_case[i]) == true)
				{
					check_else = true;
					/**/
				}
				else if (find_for(str_case[i]) == true)
				{
					check_for = true;
					/**/
				}
				else
				{
					if (i != sentence - 1)
						function_process(str_case[i], str_case[i + 1]);
					else
						function_process(str_case[i], " ");
				}
				check_if = false;
				check_else = false;
				check_for = false;
			}
			if (error_case == true)
			{
				if (error_sentence > i)
					error_sentence = i;
			}
			if (next_line == true)
			{
				next_line = false;
				i++;
			}
		}
		if (error_case == true)
		{
			cout << "SYNTAX ERROR, Line:" << error_sentence + 1 << endl;
		}
		delete[] str_case;
	}
}