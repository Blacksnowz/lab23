#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

char score2grade(int score) {
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    return 'F';
}

string toUpperStr(string x) {
    string y = x;
    for(unsigned i = 0; i < y.size(); i++) {
        y[i] = toupper(y[i]);
    }
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades) {
    ifstream file(filename);
    if(!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while(getline(file, line)) {
        if(line.empty()) continue;
        // Each line format: Name: score1 score2 score3
        size_t pos = line.find(':');
        if(pos == string::npos) continue; // skip invalid line
        string name = line.substr(0, pos);
        string scorePart = line.substr(pos + 1);
        // Remove any leading spaces in scorePart
        if(!scorePart.empty() && scorePart[0] == ' ')
            scorePart.erase(0, scorePart.find_first_not_of(" "));
        istringstream iss(scorePart);
        int s1, s2, s3;
        iss >> s1 >> s2 >> s3;
        int total = s1 + s2 + s3;
        names.push_back(name);
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
    file.close();
}

void getCommand(string &command, string &key) {
    cout << "Please input your command:" << endl;
    string line;
    getline(cin, line);
    if(line.empty()){
        command = "";
        key = "";
        return;
    }
    istringstream iss(line);
    iss >> command;
    getline(iss, key);
    // Trim leading spaces from key if any
    if(!key.empty()){
        size_t start = key.find_first_not_of(" ");
        if(start != string::npos)
            key = key.substr(start);
        else
            key = "";
    }
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key) {
    bool found = false;
    for(size_t i = 0; i < names.size(); i++) {
        // Compare in a case-insensitive manner
        if(toUpperStr(names[i]) == key) {
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;
            found = true;
            break;
        }
    }
    if(!found) {
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key) {
    bool found = false;
    if(key.empty()){
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
        return;
    }
    // key is already in uppercase in main()
    char gradeKey = key[0];
    cout << "---------------------------------" << endl;
    for(size_t i = 0; i < grades.size(); i++) {
        if(grades[i] == gradeKey) {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if(!found) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command, key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    } while(true);
    
    return 0;
}
