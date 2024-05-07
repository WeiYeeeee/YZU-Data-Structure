#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;
int shopID, sum = 0, i, j = 0, k, l, m, n, confirmed_ID, num_date, num_days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
vector<vector<vector<vector<int>>>> data_case;
vector<vector <int>> output;
struct case_data {
	int year = 0, month = 0, day = 0, times = 0, plus_year = 0, plus_month = 0, plus_day = 0, plus_times = 0;
};
case_data cd_begin, cd_end;
// 一般版本
case_data sort_up_process_1(case_data cd)
{
	while (cd.times >= 86400)
	{
		cd.times -= 86400;
		cd.day++;
	}
	while (cd.month > 12)
	{
		cd.month -= 12;
		cd.year++;
	}
	while (cd.day > num_days[cd.month])
	{
		cd.day -= num_days[cd.month];
		cd.month++;
	}
	while (cd.month > 12)
	{
		cd.month -= 12;
		cd.year++;
	}
	return cd;
}
// plus版本
case_data sort_up_process_2(case_data cd)
{
	while (cd.plus_times >= 86400)
	{
		cd.plus_times -= 86400;
		cd.plus_day++;
	}
	while (cd.plus_month > 12)
	{
		cd.plus_month -= 12;
		cd.plus_year++;
	}
	while (cd.plus_day > num_days[cd.plus_month])
	{
		cd.plus_day -= num_days[cd.plus_month];
		cd.plus_month++;
	}
	while (cd.plus_month > 12)
	{
		cd.plus_month -= 12;
		cd.plus_year++;
	}
	return cd;
}
case_data plus_process(case_data cd, int num_day, int num_minute)
{
	cd.plus_day = cd.day + num_day;
	cd.plus_month = cd.month;
	cd.plus_year = cd.year;
	cd.plus_times += (num_minute * 60);
	cd = sort_up_process_2(cd);
	return cd;
}
// 一般版本
int minus_process_1(case_data cc_begin, case_data cc_end)
{
	sum = 0;
	while (cc_end.day < cc_begin.day)
	{
		if (cc_end.month == 1)
		{
			cc_end.year--;
			cc_end.month = 12;
		}
		else
			cc_end.month--;
		cc_end.day += num_days[cc_end.month];
	}
	cc_end.day -= cc_begin.day;
	while (cc_end.month < cc_begin.month)
	{
		cc_end.year--;
		cc_end.month += 12;
	}
	cc_end.month--;
	for (i = cc_end.month; i >= cc_begin.month; i--)
		sum += num_days[i];
	cc_end.year -= cc_begin.year;
	sum += (cc_end.year * 365 + cc_end.day);
	return sum;
}
// plus版本
int minus_process_2(case_data cc_begin, case_data cc_end)
{
	sum = 0;
	while (cc_end.plus_day < cc_begin.day)
	{
		if (cc_end.plus_month == 1)
		{
			cc_end.plus_year--;
			cc_end.plus_month = 12;
		}
		else
			cc_end.plus_month--;
		cc_end.plus_day += num_days[cc_end.plus_month];
	}
	cc_end.plus_day -= cc_begin.day;
	while (cc_end.plus_month < cc_begin.month)
	{
		cc_end.plus_year--;
		cc_end.plus_month += 12;
	}
	cc_end.plus_month--;
	for (i = cc_end.plus_month; i >= cc_begin.month; i--)
		sum += num_days[i];
	cc_end.plus_year -= cc_begin.year;
	sum += (cc_end.plus_year * 365 + cc_end.plus_day);
	return sum + 1;
}
// 一般版本
bool related_1(case_data cd, case_data begin, case_data end)
{
	if (cd.year > end.year)
		return false;
	else if (cd.year == end.year)
	{
		if (cd.month > end.month)
			return false;
		else if (cd.month == end.month)
		{
			if (cd.day > end.day)
				return false;
			else if (cd.day == end.day)
			{
				if (cd.times > end.times)
					return false;
			}
		}
	}
	if (cd.year < begin.year)
		return false;
	else if (cd.year == begin.year)
	{
		if (cd.month < begin.month)
			return false;
		else if (cd.month == begin.month)
		{
			if (cd.day < begin.day)
				return false;
			else if (cd.day == begin.day)
			{
				if (cd.times < begin.times)
					return false;
			}
		}
	}
	return true;
}
// plus版本
bool related_2(case_data cd, case_data begin, case_data end)
{
	if (cd.year > end.plus_year)
		return false;
	else if (cd.year == end.plus_year)
	{
		if (cd.month > end.plus_month)
			return false;
		else if (cd.month == end.plus_month)
		{
			if (cd.day > end.plus_day)
				return false;
			else if (cd.day == end.plus_day)
			{
				if (cd.times > end.times)
					return false;
			}
		}
	}
	if (cd.year < begin.year)
		return false;
	else if (cd.year == begin.year)
	{
		if (cd.month < begin.month)
			return false;
		else if (cd.month == begin.month)
		{
			if (cd.day < begin.day)
				return false;
			else if (cd.day == begin.day)
			{
				if (cd.times < begin.times)
					return false;
			}
		}
	}
	return true;
}
int main(int argc, char* argv[])
{
	ifstream fin;
	fin.open("in5.txt");
	if (!fin.is_open())
		cout << "Can' t open the file!\n";
	else 
	{
		string str;
		case_data cd;
		data_case.resize(50);
		output.resize(52);
		//OK // 分配記憶體給output和data_case
		for (i = 0; i < 50; i++)
		{
			data_case[i].resize(10);
			output[i].resize(1);
		}
		// 建構 data_case
		while (getline(fin, str))
		{
			if (j == 3)
			{
				k = 10 * (str[2] - '0') + (str[3] - '0') - 1;
				cd.year = 1000 * (str[30] - '0') + 100 * (str[31] - '0') + 10 * (str[32] - '0') + (str[33] - '0');
				cd.month = 10 * (str[35] - '0') + (str[36] - '0');
				cd.day = 10 * (str[38] - '0') + (str[39] - '0');
				cd.times = 3600 * (10 * (str[21] - '0') + (str[22] - '0')) + 60 * (10 * (str[24] - '0') + (str[25] - '0')) + 10 * (str[27] - '0') + (str[28] - '0');
				cd = sort_up_process_1(cd);
				if ((k == confirmed_ID && related_1(cd, cd_begin, cd_end)) || (k != confirmed_ID && related_2(cd, cd_begin, cd_end)))
				{
					shopID = 10 * (str[7] - '0') + (str[8] - '0') - 1;
					l = minus_process_1(cd_begin, cd);
					data_case[k][shopID][l].resize(data_case[k][shopID][l].size() + 1);
					data_case[k][shopID][l].back() = cd.times;
				}
			}
			else if (j == 0)
			{
				confirmed_ID = 10 * (str[2] - '0') + (str[3] - '0') - 1;
				j++;
			}
			else if (j == 1)
			{
				cd_begin.year = 1000 * (str[0] - '0') + 100 * (str[1] - '0') + 10 * (str[2] - '0') + (str[3] - '0');
				cd_begin.month = 10 * (str[5] - '0') + (str[6] - '0');
				cd_begin.day = 10 * (str[8] - '0') + (str[9] - '0');
				while (true)
				{
					if (cd_begin.month > 12)
					{
						cd_begin = sort_up_process_1(cd_begin);
						break;
					}
					if (cd_begin.day > num_days[cd_begin.month])
					{
						cd_begin = sort_up_process_1(cd_begin);
						break;
					}
					break;
				}
				j++;
			}
			else
			{
				cd_end.year = 1000 * (str[0] - '0') + 100 * (str[1] - '0') + 10 * (str[2] - '0') + (str[3] - '0');
				cd_end.month = 10 * (str[5] - '0') + (str[6] - '0');
				cd_end.day = 10 * (str[8] - '0') + (str[9] - '0')+1;
				while (true)
				{
					if (cd_end.month > 12)
					{
						cd_end = sort_up_process_1(cd_end);
						break;
					}
					if (cd_end.day > num_days[cd_end.month])
					{
						cd_end = sort_up_process_1(cd_end);
						break;
					}
					break;
				}
				cd_end = plus_process(cd_end, 4, 0);
				num_date = minus_process_2(cd_begin, cd_end);
				for (k = 0; k < 50; k++)
				{
					for (l = 0; l < 10; l++)
					{
						data_case[k][l].resize(num_date);
					}
				}
				j++;

			}
		}
		// 輸出 data_case
		/*for (i = 0; i < 50; i++)
		{
			cout << "A1" << setw(2) << setfill('0') << i + 1 << endl;
			for (j = 0; j < 10; j++)
			{
				cout << "	S1" << setw(2) << setfill('0') << j + 1 << endl;
				for (k = 0; k < num_date; k++)
				{

					for (m = 0; m < data_case[i][j][k].size(); m++)
					{
						if(m==0)
							cout << "		date" << setw(2) << setfill('0') << k + cd_begin.day << " ";
						cout << data_case[i][j][k][m] << " ";
						if(m== data_case[i][j][k].size()-1)
							cout << endl;
					}
				}
			}
		}*/
		
		// 尋找第一層接觸者
		for (i = 0; i < 50; i++)
		{
			if (i != confirmed_ID)
			{
				vector<vector<int>> trigged_time;
				for (j = 0; j < 10; j++)
				{
					for (k = 0; k < num_date; k++)
					{
						if ((output[i][0] == -1) || (data_case[confirmed_ID][j][k].size() != 0 && data_case[i][j][k].size() != 0))
						{
							for (l = 0; l < data_case[confirmed_ID][j][k].size(); l++)
							{
								for (m = 0; m < data_case[i][j][k].size(); m++)
								{
									//兩個相減小於30
									if (data_case[i][j][k][m] > data_case[confirmed_ID][j][k][l])
									{
										if (data_case[i][j][k][m] - data_case[confirmed_ID][j][k][l] <= 1800)
										{
											if (output[i][0] == 0)
											{
												output[i][0] = -1;
												output[50].resize(output[50].size() + 1);
												output[51].resize(output[51].size() + 1);
												output[50].back() = i;
												output[51].back() = i;
												trigged_time.resize(trigged_time.size() + 1);
												trigged_time.back().resize(2);
												trigged_time.back()[0] = k;
												trigged_time.back()[1] = data_case[i][j][k][m];
											}
											else
											{
												trigged_time.resize(trigged_time.size() + 1);
												trigged_time.back().resize(2);
												trigged_time.back()[0] = k;
												trigged_time.back()[1] = data_case[i][j][k][m];
											}
										}
									}
								}
							}
						}
					}
				}
				// 做事情
				if (trigged_time.size() == 1)
				{
					for (j = 0; j < 10; j++)
					{
						//     5   6   7   8  
						for (k = 0; k < trigged_time[0][0]; k++)
							data_case[i][j][k].clear();
						for (k = trigged_time[0][0] + 4; k < num_date; k++)
							data_case[i][j][k].clear();
						for (k = 0; k < data_case[i][j][trigged_time[0][0]].size(); k++)
						{
							if (data_case[i][j][trigged_time[0][0]][k] < trigged_time[0][1])
							{
								data_case[i][j][trigged_time[0][0]].erase(data_case[i][j][trigged_time[0][0]].begin() + k, data_case[i][j][trigged_time[0][0]].begin() + k + 1);
							}
						}
						for (k = 0; k < data_case[i][j][trigged_time[0][0] + 3].size(); k++)
						{
							if (data_case[i][j][trigged_time[0][0] + 3][k] > trigged_time[0][1])
							{
								if (data_case[i][j][trigged_time[0][0] + 3][k] - trigged_time[0][1] > 1800)
									data_case[i][j][trigged_time[0][0] + 3].erase(data_case[i][j][trigged_time[0][0] + 3].begin() + k, data_case[i][j][trigged_time[0][0] + 3].begin() + k + 1);
							}
						}
					}
				}
				else if (trigged_time.size() > 1)
				{
					vector<vector<vector<int>>> temp;
					temp.resize(10);
					for (j = 0; j < 10; j++)
						temp[j].resize(num_date);
					for (k = 0; k < trigged_time.size(); k++)
					{
						for (j = 0; j < 10; j++)
						{
							if (data_case[i][j][trigged_time[k][0]].size() != 0)
							{
								for (l = 0; l < data_case[i][j][trigged_time[k][0]].size(); l++)
								{
									if (data_case[i][j][trigged_time[k][0]][l] >= trigged_time[k][1])
									{
										temp[j][trigged_time[k][0]].resize(temp[j][trigged_time[k][0]].size() + 1);
										temp[j][trigged_time[k][0]].back() = data_case[i][j][trigged_time[k][0]][l];
									}
								}
							}
							else if (data_case[i][j][trigged_time[k][0] + 1].size() != 0)
								temp[j][trigged_time[k][0] + 1] = data_case[i][j][trigged_time[k][0] + 1];
							else if (data_case[i][j][trigged_time[k][0] + 2].size() != 0)
								temp[j][trigged_time[k][0] + 2] = data_case[i][j][trigged_time[k][0] + 2];
							else if (data_case[i][j][trigged_time[k][0] + 3].size() != 0)
							{
								for (l = 0; l < data_case[i][j][trigged_time[k][0]+3].size(); l++)
								{
									if (data_case[i][j][trigged_time[k][0] + 3][l] > trigged_time[k][1])
									{
										if (data_case[i][j][trigged_time[k][0] + 3][l] - trigged_time[k][1] <= 1800)
										{
											temp[j][trigged_time[k][0] + 3].resize(temp[j][trigged_time[k][0] + 3].size() + 1);
											temp[j][trigged_time[k][0] + 3].back() = data_case[i][j][trigged_time[k][0] + 3][l];
										}
									}
									else
									{
										temp[j][trigged_time[k][0]+3].resize(temp[j][trigged_time[k][0]+3].size() + 1);
										temp[j][trigged_time[k][0]+3].back() = data_case[i][j][trigged_time[k][0] + 3][l];
									}
								}
							}
						}
					}
					data_case[i] = temp;
					temp.clear();
				}

			}
		}
		// 第一層接觸者輸出
		/*for (i = 0; i < output[50].size(); i++)
			cout << output[50][i] << endl;*/
		// 輸出找到第一層接觸者後，整理過的data_case
		/*
		for (i = 0; i < 50; i++)
		{
			cout << "A1" << setw(2) << setfill('0') << i + 1 << endl;
			for (j = 0; j < 10; j++)
			{
				cout << "	S1" << setw(2) << setfill('0') << j + 1 << endl;
				for (k = 0; k < num_date; k++)
				{

					for (m = 0; m < data_case[i][j][k].size(); m++)
					{
						if(m==0)
							cout << "		date" << setw(2) << setfill('0') << k + cd_begin.day << " ";
						cout << data_case[i][j][k][m] << " ";
						if(m== data_case[i][j][k].size()-1)
							cout << endl;
					}
				}
			}
		}
		*/
		// 尋找第二層接觸者
		for (i = 0; i < 50; i++)
		{
			if (output[i][0] != -1 || i != confirmed_ID)
			{
				for (j = 0; j < 10; j++)
				{
					for (k = 0; k < num_date; k++)
					{
						for (l = 0; l < output[50].size(); l++)
						{
							if ((output[i][0] != -1) && (data_case[(output[50][l])][j][k].size() != 0))
							{
								for (m = 0; m < data_case[i][j][k].size(); m++)
								{
									for (n = 0; n < data_case[output[50][l]][j][k].size(); n++)
									{
										if (data_case[i][j][k][m] > data_case[output[50][l]][j][k][n])
										{
											if (data_case[i][j][k][m] - data_case[output[50][l]][j][k][n] <= 1800)
											{
												output[i][0] = -1;
												output[51].resize(output[51].size() + 1);
												output[51].back() = i;

												m = data_case[i][j][k].size();
												n = data_case[output[50][l]][j][k].size();
											}
										}
									}
								}
								
							}					
						}
					}
				}
			}
		}
		// 第二層接觸者輸出
		output[51].resize(output[51].size() + 1);
		output[51].back() = confirmed_ID;
		sort(output[51].begin(), output[51].end());

		for (i = 0; i < output[51].size(); i++)
			cout << "A1" << setw(2) << setfill('0') << output[51][i]+1 << endl;
		/*
		cout << "confirmed_ID: A1" << setw(2) << setfill('0') << confirmed_ID + 1 << endl << endl;
		cout << "begin -> " << cd_begin.year << "/" << setw(2) << setfill('0') << cd_begin.month << "/" << setw(2) << setfill('0') << cd_begin.day << endl;
		cout << "end   -> " << cd_end.year << "/" << setw(2) << setfill('0') << cd_end.month << "/" << setw(2) << setfill('0') << cd_end.day << endl << endl;
		cout << "end+4 -> " << cd_end.plus_year << "/" << setw(2) << setfill('0') << cd_end.plus_month << "/" << setw(2) << setfill('0') << cd_end.plus_day << endl << endl;
		cout << "distance " << setw(10) << setfill(' ') << num_date << endl << endl;
		*/

	}
}
