#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;
vector <int> case_label, num_erase, case_merge, anser;
vector<vector <int>> check_merge;
int intermediate_point = -1;
string delete_space(string str_case){
    int index = 0;
    if (!str_case.empty()) {
        while ((index = str_case.find(' ', index)) != string::npos)
            str_case.erase(index, 1);
    }
    return str_case;
}
void function_process_1(string merge){
    int pos_comma = find(merge.begin(), merge.end(), ',') - merge.begin(), num1 = stoi(delete_space(merge.substr(0, pos_comma))), num2 = stoi(delete_space(merge.substr(pos_comma + 1)));
    if (num1 > 0 && num2 > 0)
        case_merge[num1] < case_merge[num2] ? case_merge.push_back(case_merge[num1]) : case_merge.push_back(case_merge[num2]);
    else if (num1 > 0 && num2 < 0){
        num2 = -num2;
        case_merge[num1] < case_label[num2] ? case_merge.push_back(case_merge[num1]) : case_merge.push_back(case_label[num2]);
    }
    else if (num1 < 0 && num2 > 0){
        num1 = -num1;
        case_label[num1] < case_merge[num2] ? case_merge.push_back(case_label[num1]) : case_merge.push_back(case_merge[num2]);
    }
    else if (num1 < 0 && num2 < 0){
        num1 = -num1;
        num2 = -num2;
        case_label[num1] < case_label[num2] ? case_merge.push_back(case_label[num1]) : case_merge.push_back(case_label[num2]);
    }
}
void function_process_2(string merge){
    int pos_comma = find(merge.begin(), merge.end(), ',') - merge.begin(), num1 = stoi(delete_space(merge.substr(0, pos_comma))), num2 = stoi(delete_space(merge.substr(pos_comma + 1)));
    vector<int> temp;
    if (num1 > 0 && num2 > 0){
        if (case_merge[num1] < case_merge[num2]){
            temp.push_back(case_merge[num1]);
            temp.push_back(case_merge[num2]);
        }
        else        {
            temp.push_back(case_merge[num2]);
            temp.push_back(case_merge[num1]);
        }
    }
    else if (num1 > 0 && num2 < 0){
        num2 = -num2;
        if (case_merge[num1] < case_label[num2]){
            temp.push_back(case_merge[num1]);
            temp.push_back(case_label[num2]);
        }
        else{
            temp.push_back(case_label[num2]);
            temp.push_back(case_merge[num1]);
        }
    }
    else if (num1 < 0 && num2 > 0){
        num1 = -num1;
        if (case_label[num1] < case_merge[num2]){
            temp.push_back(case_label[num1]);
            temp.push_back(case_merge[num2]);
        }
        else{ 
            temp.push_back(case_merge[num2]);        
            temp.push_back(case_label[num1]);
        }
    }
    else if (num1 < 0 && num2 < 0){
        num1 = -num1;
        num2 = -num2;
        if (case_label[num1] < case_label[num2]){
            temp.push_back(case_label[num1]);
            temp.push_back(case_label[num2]);
        }
    }
    check_merge.push_back(temp);
    case_merge.push_back(temp[0]);
}
int main(int argc, char* argv[]){
    ifstream fin1, fin2, fin3;
    fin1.open("10_merge.txt");
    fin2.open("10_labels.txt");
    fin3.open("10_height.txt");
    if (!fin1.is_open() || !fin2.is_open() || !fin3.is_open())
        cout << "Can' t open the file!\n";
    else{
        case_label.push_back(0);
        case_merge.push_back(0);
        string merge, labels, height;
        int count = 1;
        while (getline(fin3, height)){
            if (height[0] != '0'){
                if (intermediate_point == -1){
                    intermediate_point = count;
                    break;
                }
            }
            count++;
        }
        count = 1;
        while (getline(fin2, labels)){
            int index = 0;
            labels = delete_space(labels);
            if (!labels.empty()){
                while ((index = labels.find('"', index)) != string::npos)
                    labels.erase(index, 1);
            }
            case_label.push_back(stoi(labels));
        }
        while (getline(fin1, merge)){
            if (count < intermediate_point){
                function_process_1(merge);
            }
            else{
                function_process_2(merge);
            }
            count++;
        }
        anser.push_back(check_merge.back()[0]);
        anser.push_back(check_merge.back()[1]);
        check_merge.pop_back();
        while (anser.size() != 10){
            anser.push_back(check_merge.back()[1]);
            check_merge.pop_back();
        }
        sort(anser.begin(), anser.end());
        for (int i = 0; i < anser.size(); i++){
            if (i != 0)
                cout << " ";
            cout << anser[i];
        }
    }
}