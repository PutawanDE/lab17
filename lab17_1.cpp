#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string fName, vector<string> &names, vector<int> &scores, vector<char> &grades){
    string text;
    const char format[] = "%[^:]: %d %d %d";

    ifstream src(fName);

    while(getline(src, text)){
        char name[25];
        char grade;
        int score1, score2, score3;
        int totalScore;

        const char *txt = text.c_str();
        sscanf(txt, format, name, &score1, &score2, &score3);

        totalScore = score1 + score2 + score3;
        grade = score2grade(totalScore);

        names.push_back(name);
        scores.push_back(totalScore);
        grades.push_back(grade);
    }
}

void getCommand(string &cmd, string &key){
    cout << "Please input your command: ";
    string input;
    getline(cin, input);
    int end = input.find_first_of(" ");
    cmd = input.substr(0, end);
    key = input.substr(end + 1, input.length());
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool flag = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            flag = true;
            cout << names[i] << "'s score = " << scores[i] << "\n"; 
            cout << names[i] << "'s grade = " << grades[i] << "\n"; 
        }
    }
    
    if(!flag) cout << "Cannot found.\n";
    cout << "---------------------------------\n";

}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    char keyCh = key[0];
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(grades[i] == keyCh)
            cout << names[i] << " (" << scores[i] << ")\n";
    }
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
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
    }while(true);
    
    return 0;
}
