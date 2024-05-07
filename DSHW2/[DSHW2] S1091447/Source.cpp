#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;
int array_num = -1;
struct list_object {
	string title, attribute, value, name;
};
vector<string> case_nodename, case_endname, case_element, stack_operator, stack_variable;
vector<list_object> case_list, stack_list;
vector<vector<list_object>> case_final, case_check, case_variable;
string delete_space(string str_case)
{
	int index = 0;
	if (!str_case.empty()) {
		while ((index = str_case.find(' ', index)) != string::npos)
			str_case.erase(index, 1);
	}
	return str_case;
}
bool dont_link(vector<list_object> case_list)
{
	bool do_not_link = false;
	int count = 0;
	for (int i = 0; i < case_check.size(); i++)
	{
		if (case_list.size() == case_check[i].size())
		{
			for (int j = 0; j < case_list.size(); j++)
			{
				if (case_list[j].attribute == case_check[i][j].attribute && case_list[j].name == case_check[i][j].name && case_list[j].title == case_check[i][j].title && case_list[j].value == case_check[i][j].value && case_list[j].value == "")
				{
					count++;
				}
			}
			if (count == case_list.size())
			{
				do_not_link = true;
			}
		}
	}
	if (do_not_link == true)
		return true;
	else
		return false;
}
void list_process(vector<string> case_vector)
{

	if (case_vector.size() > 1)
	{
		string tmep_title, tmep_attribute, tmep_value, tmep_name;
		list_object lo;
		for (int i = 0; i < case_vector.size(); i++)
		{

			if (case_vector[i].find("<strong>") != string::npos && case_vector[i].find("</strong>") != string::npos)
			{
				tmep_value = case_vector[i];
			}
			else if (case_vector[i].find('<') != string::npos && case_vector[i].find('>') != string::npos)
			{
				if (i != 0)
				{
					lo.title = tmep_title;
					lo.attribute = tmep_attribute;
					lo.value = tmep_value;
					lo.name = tmep_name;
					case_list.push_back(lo);
					tmep_title = "", tmep_attribute = "", tmep_value = "", tmep_name = "";
				}
				int pos_less_than = find(case_vector[i].begin(), case_vector[i].end(), '<') - case_vector[i].begin();
				int pos_greater_than = find(case_vector[i].begin(), case_vector[i].end(), '>') - case_vector[i].begin();
				string temp = case_vector[i].substr(pos_less_than + 1, pos_greater_than - pos_less_than - 1);
				if (case_vector[i].find('\"') != string::npos)
				{
					int index1 = 0, index2 = 0, index3 = 0;
					index1 = temp.find(' ', index1);
					tmep_title = temp.substr(0, index1);
					index2 = temp.find('=', index2);
					tmep_name = temp.substr(index1 + 1, index2 - index1 - 1);
					tmep_name = delete_space(tmep_name);
					for (int j = index3; j < case_vector[i].length(); j++)
					{
						if (case_vector[i][j] != '"' && index3 == 1)
							tmep_attribute += case_vector[i][j];
						else if (case_vector[i][j] == '"')
							index3++;
					}
				}
				else
				{

					tmep_title = temp;
				}
			}
			else
			{
				tmep_value = case_vector[i];
			}
		}
		case_check.push_back(case_list);
		lo.title = tmep_title;
		lo.attribute = tmep_attribute;
		lo.value = tmep_value;
		lo.name = tmep_name;
		case_list.push_back(lo);

		if (dont_link(case_list) == false)
		{

			/*家array_num*/
			case_final.push_back(case_list);
			/*for (int i = 0; i < case_final.back().size(); i++)
			{
				cout << case_final.back()[i].title << endl;
				cout << case_final.back()[i].name << endl;
				cout << case_final.back()[i].attribute << endl;
				cout << case_final.back()[i].value << endl;
			}*/
		}
		while (case_list.size() != 0)
			case_list.pop_back();
	}
}
void function_process(string str_case) {
	// 遇到<>存  </> pop
	// 先找到一開始的
	int judge = 0;
	int pos_less_than = find(str_case.begin(), str_case.end(), '<') - str_case.begin();
	int pos_greater_than = find(str_case.begin(), str_case.end(), '>') - str_case.begin();
	string str_nodename = str_case.substr(pos_less_than, pos_greater_than - pos_less_than + 1);
	str_nodename = delete_space(str_nodename);
	string str_end = str_nodename;
	str_end.insert(1, "/");
	case_endname.push_back(str_end);
	case_element.push_back(str_nodename);
	case_nodename.push_back(str_nodename);
	str_case.erase(0, pos_greater_than + 1);
	string str_value;
	while (str_case.find(str_end) != string::npos)
	{

		int pos_less_than = find(str_case.begin(), str_case.end(), '<') - str_case.begin();
		int pos_greater_than = find(str_case.begin(), str_case.end(), '>') - str_case.begin();
		string str_nodename = str_case.substr(pos_less_than, pos_greater_than - pos_less_than + 1);
		// <meta charset = "utf-8">
		if (str_nodename.find('\"') != string::npos)
		{
			string str_temp = str_nodename, str_end;
			int index = 0;
			index = str_nodename.find(' ', index);
			str_nodename = str_temp.substr(0, index) + '>';
			if (str_nodename == "<meta>")
			{
				//cout << "element " << str_temp << endl;
				// 丟到list_process
				case_element.push_back(str_temp);
				list_process(case_element);
				case_element.pop_back();
			}
			// <a b=" ">
			else
			{
				str_end = str_nodename;
				str_end.insert(1, "/");
				case_endname.push_back(str_end);
				case_element.push_back(str_temp);
				case_nodename.push_back(str_nodename);
			}
			str_case.erase(0, pos_greater_than + 1);
			judge = 0;
		}
		else
		{
			str_nodename = delete_space(str_nodename);
			// </ >
			if (str_nodename.find('/') != string::npos && str_nodename != "</strong>" && str_nodename.find('<') != string::npos && str_nodename.find('>') != string::npos) {
				if (pos_less_than != 0 && judge == 0)
				{
					str_value += str_case.substr(0, pos_less_than);
					case_element.push_back(str_value);
					str_value = "";
				}
				if (str_value != "")
				{
					case_element.push_back(str_value);
					str_value = "";
				}
				if (str_nodename == case_endname.back()) {
					// 丟到list_process
					list_process(case_element);
					while (case_element.back() != case_nodename.back())
					{
						if (case_element.back().find('\"') != string::npos)
						{
							string sstr_temp = case_element.back(), sstr_nodename;
							int index = 0;
							index = sstr_temp.find(' ', index);
							sstr_nodename = sstr_temp.substr(0, index) + '>';
							if (sstr_nodename == case_nodename.back())
							{
								break;
							}
						}
						else
						{
							//cout << "element " << case_element.back() << endl;
							case_element.pop_back();
						}
					}
					//cout << "element " << case_element.back() << endl;
					case_element.pop_back();
					case_nodename.pop_back();
					case_endname.pop_back();
					str_case = str_case.erase(0, pos_greater_than + 1);
				}
				judge = 1;
			}
			else if (str_nodename != "<strong>" && str_nodename != "</strong>")
			{
				string str_end;
				str_end = str_nodename;
				str_end.insert(1, "/");
				case_endname.push_back(str_end);
				case_element.push_back(str_nodename);
				case_nodename.push_back(str_nodename);
				str_case.erase(0, pos_greater_than + 1);
				judge = 0;
			}
			else if (str_nodename == "<strong>")
			{
				str_value += str_nodename;
				str_case.erase(0, pos_greater_than + 1);
				judge = 0;
			}
			else
			{
				str_value += str_case.substr(0, pos_less_than);
				str_value += str_nodename;
				str_case.erase(0, pos_greater_than + 1);
				judge = 0;
			}
		}
	}
}
void variable_process()
{
	//div[@class='title']/a/value
	//div[@class='date']/value
	//div[@class]/attribute
	string tmep_title, tmep_attribute, tmep_value, tmep_name;

	for (int i = 0; i < stack_variable.size(); i++)
	{
		int count = 0;
		list_object lo;
		if (stack_variable[i].find('\'') != string::npos)
		{
			//div[@class='date']/value
			//0   34    10 17
			//3
			int left_bracket = find(stack_variable[i].begin(), stack_variable[i].end(), '[') - stack_variable[i].begin();
			//17
			int right_bracket = find(stack_variable[i].begin(), stack_variable[i].end(), ']') - stack_variable[i].begin();
			//10
			int equal_sign = find(stack_variable[i].begin(), stack_variable[i].end(), '=') - stack_variable[i].begin();
			//4
			int at = find(stack_variable[i].begin(), stack_variable[i].end(), '@') - stack_variable[i].begin();
			lo.title = stack_variable[i].substr(0, left_bracket);
			lo.name = stack_variable[i].substr(at + 1, equal_sign - at - 1);

			for (int j = equal_sign; j < stack_variable[i].length(); j++)
			{
				if (stack_variable[i][j] != '\'' && count == 1)
					lo.attribute += stack_variable[i][j];
				else if (stack_variable[i][j] == '\'')
					count++;
			}
		}
		else if (stack_variable[i].find('@') != string::npos)
		{
			//div[@class]/attribute
			//0  34
			//3
			int left_bracket = find(stack_variable[i].begin(), stack_variable[i].end(), '[') - stack_variable[i].begin();
			//10
			int right_bracket = find(stack_variable[i].begin(), stack_variable[i].end(), ']') - stack_variable[i].begin();
			//4
			int at = find(stack_variable[i].begin(), stack_variable[i].end(), '@') - stack_variable[i].begin();
			lo.title = stack_variable[i].substr(0, left_bracket);
			lo.name = stack_variable[i].substr(at + 1, right_bracket - at - 1);

		}
		else if (stack_variable[i].find('[') != string::npos && stack_variable[i].find(']') != string::npos)
		{
			string str;
			int left_bracket = find(stack_variable[i].begin(), stack_variable[i].end(), '[') - stack_variable[i].begin();
			int right_bracket = find(stack_variable[i].begin(), stack_variable[i].end(), ']') - stack_variable[i].begin();
			lo.title = stack_variable[i].substr(0, left_bracket);
			str = stack_variable[i].substr(left_bracket + 1, right_bracket - left_bracket - 1);
				//  0   1   3     8 
			array_num = stoi(delete_space(str));
		}
		else
		{
			lo.title = stack_variable[i];
		}
		stack_list.push_back(lo);
	}
	case_variable.push_back(stack_list);
	stack_list.clear();
}
void output_process(string str)
{
	string str_temp;
	if (str[0] == '/' && str[1] != '/')
	{
		stack_operator.push_back("/");
		str.erase(0, 1);
	}
	else
	{
		if (str[0] == '/')
			str.erase(0, 2);
		stack_operator.push_back("//");
	}
	int index = 0;
	if (!str.empty()) {
		while ((index = str.find("/", index)) != string::npos)
		{
			if (index != 0)
			{
				str_temp = str.substr(0, index);
				stack_variable.push_back(str_temp);
				stack_operator.push_back("/");
				str.erase(0, index + 1);
			}
			else
			{
				stack_operator.pop_back();
				stack_operator.push_back("//");
				str.erase(0, 1);
			}
			index = 0;
		}
		stack_variable.push_back(str);
	}
	variable_process();
	vector<vector<list_object>> case_final_temp = case_final;
	bool change = false;
	// case_variable, stack_operator, case_final
	for (int i = 0; i < stack_operator.size(); i++)
	{
		if (i != stack_operator.size() - 1)
		{
			if (stack_operator[i] == "//")
			{

				for (int j = 0; j < case_final_temp.size(); j++)// vector<vector<>
				{
					for (int k = 0; k < case_final_temp[j].size(); k++)// vector<>
					{
						bool find = true;
						if (case_variable.back()[i].attribute != "")
						{
							if (case_variable.back()[i].attribute != case_final_temp[j][k].attribute)
								find = false;
						}
						if (case_variable.back()[i].name != "")
						{
							if (case_variable.back()[i].name != case_final_temp[j][k].name)
								find = false;
						}
						if (case_variable.back()[i].title != "")
						{
							if (case_variable.back()[i].title != case_final_temp[j][k].title)
								find = false;
						}
						if (case_variable.back()[i].value != "")
						{
							if (case_variable.back()[i].value != case_final_temp[j][k].value)
								find = false;
						}
						if (find == true)
						{
							case_final_temp[j].erase(case_final_temp[j].begin(), case_final_temp[j].begin() + k);
							break;
						}
						if (find == false && k == case_final_temp[j].size() - 1)
						{
							case_final_temp.erase(case_final_temp.begin() + j, case_final_temp.begin() + j + 1);
							j--;
							break;
						}
					}
				}
			}
			else
			{
				for (int j = 0; j < case_final_temp.size(); j++)// vector<vector<>
				{
					if (case_final_temp[j].size() > 1)
					{
						bool find = true;
						if (case_variable.back()[i].attribute != "")
						{
							if (case_variable.back()[i].attribute != case_final_temp[j][1].attribute)
								find = false;
						}
						if (case_variable.back()[i].name != "")
						{
							if (case_variable.back()[i].name != case_final_temp[j][1].name)
								find = false;
						}
						if (case_variable.back()[i].title != "")
						{
							if (case_variable.back()[i].title != case_final_temp[j][1].title)
								find = false;
						}
						if (case_variable.back()[i].value != "")
						{
							if (case_variable.back()[i].value != case_final_temp[j][1].value)
								find = false;
						}
						if (find == true)
						{
							case_final_temp[j].erase(case_final_temp[j].begin(), case_final_temp[j].begin() + 1);
						}
						else
						{
							case_final_temp.erase(case_final_temp.begin() + j, case_final_temp.begin() + j + 1);
							j--;
						}
					}
					else
					{
						case_final_temp.erase(case_final_temp.begin() + j, case_final_temp.begin() + j + 1);
						j--;
						break;
					}
				}
			}
		}
		else
		{
			if (case_variable.back()[i].title == "value")
			{
				if (array_num == -1)
				{
					for (int j = 0; j < case_final_temp.size(); j++)
					{
						cout << case_final_temp[j][0].value << endl;
					}
				}
				else
				{
					cout << case_final_temp[array_num][0].value << endl;
				}
			}
			else if (case_variable.back()[i].title == "attribute")
			{
				if (array_num == -1)
				{
					for (int j = 0; j < case_final_temp.size(); j++)
					{
						cout << case_final_temp[j][0].attribute << endl;
					}
				}
				else
				{
					cout << case_final_temp[array_num][0].attribute << endl;
				}
				
			}
		}
	}


}
int main(int argc, char* argv[])
{
	ifstream fin1, fin2;
	fin1.open("test1.txt");
	fin2.open("test2.txt");
	if (!fin1.is_open() || !fin2.is_open())
		cout << "Can' t open the file!\n";
	else
	{
		vector <string> str_case;
		string str1, str2;
		stringstream ss;
		ss << fin1.rdbuf();
		string temp_str_cs1(ss.str());
		int count = 0;
		for (int i = 0; i < temp_str_cs1.length(); i++)
		{
			if (temp_str_cs1[i] != '\n')
				str1 += temp_str_cs1[i];
		}
		function_process(str1);
		while (getline(fin2, str2))
		{
			if (count != 0)
				cout << endl << endl;
			output_process(str2);
			case_variable.clear();
			stack_operator.clear();
			stack_variable.clear();
			count++;
			array_num = -1;
		}
	}
}