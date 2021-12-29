#include <iostream>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h> 
#include <sstream>
using namespace std;

//**argv = {{"hello", "welcome" "good day"}};
//argv is a pointer to "hello";
//*argv is a pointer to first character of "hello";
// **argv = "h";

bool sortByPriority(const pair<int, string>&a, const pair<int, string>&b){
	if(a.first == b.first){
		return &a < &b;
	}
	return (a.first < b.first);
}

vector<pair<int, string>> splitter(vector<int>&index, vector<pair<int, string>> &vect,string line){
	int num1 = line.find(".");
	int num2 = line.find_last_of("[");
	if(num1 != -1 && num2 != -1){
		string word1 = line.substr(0, num1);
		index.push_back(stoi(word1));
		string word2 = line.substr(num2);
		word2.erase(word2.begin());
		word2.erase(word2.end()-1);
		string word3 = line.substr(num1 + 2, (num2-num1-3));
		vect.push_back(make_pair(stoi(word2), word3));
	}
	return vect; 
}

void help(){
	cout << "Usage :-" << endl;
	cout << "$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list" << "\n";
	cout << "$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order" << "\n";
	cout << "$ ./task del INDEX            # Delete the incomplete item with the given index" << "\n";
	cout << "$ ./task done INDEX           # Mark the incomplete item with the given index as complete" << "\n";
	cout << "$ ./task help                 # Show usage" << "\n";
	cout << "$ ./task report               # Statistics" << "\n";	
}

void add(char **argv){
	fstream fin;
	fin.open("task.txt");
	string line;
	vector<int> index;
	// vector<string> task;
	// vector<int> priority;
	vector<pair<int, string>> vect;
	while(fin){
		getline(fin, line);
		vect = splitter(index, vect, line);
		// cout << "num1 = " << num1 << " num2 = " << num2 << endl;
	}
	vect.push_back(make_pair(stoi(argv[2]), argv[3]));
	sort(vect.begin(), vect.end(), sortByPriority);
	// for(auto x : vect) cout << x.first << " " << x.second << "\n";
	ofstream fout;
	fout.open("task.txt");
	for(size_t j = 0; j < vect.size(); j++){
		fout << j+1 << ". "<< vect[j].second << " [" << vect[j].first << "]\n";	
	}
	cout << "Added: " << "\""<<argv[3] << "\""<< " with priority " << argv[2] << "\n";
}

void ls(){
	ifstream fin;
	fin.open("task.txt");
	string line;
	while(fin){
		getline(fin, line);
		if(line != "\0")cout << line << "\n"; 
	}	
}


void del(char **argv){
	ifstream fin;
	string line;
	fin.open("task.txt");
	vector<int> index;
	vector<pair<int, string>> vect;
	while(fin){
		getline(fin, line);
		vect = splitter(index, vect, line);
	}
	fin.close();
	int flag = 0;
	auto it2 = vect.begin();
	index[index.size()] = -1;
	for (auto it = index.begin(); *it != -1; ++it)
	{
		if(*it == stoi(argv[2])){
			flag = 1;
			index.erase(it);
			vect.erase(it2);
		}
		it2++;
	}
	// for(auto x : vect){
	// 	cout << x.first << " " << x.second << "\n"; 
	// }
	// cout << flag << "\n";
	if(flag == 0){
		cout << "Error: item with index " << argv[2] << " does not exist. Nothing deleted.\n"; 
	}
	else{
		sort(vect.begin(), vect.end(), sortByPriority);
		fstream fout;
		fout.open("task.txt", ios::out | ios::trunc);
		int j = 0;
		for(auto x : vect){
			fout << j+1 << ". "<< x.second << " [" << x.first << "]\n";	
			j++;
		}
		fout.close();	
	}
}

void done(char** argv){
	// cout << ind;
	ifstream fin;
	fin.open("task.txt");
	string line;
	int flag = 0;
	while(fin){
		getline(fin, line);
		stringstream ss(line);
		string word;
		ss >> word;
		word.erase(word.end()-1);
		if(word == argv[2]){
			flag = 1; 
			ofstream fout;
			fout.open("completed.txt", ios::app);
			int num1 = line.find(".");
			int num2 = line.find_last_of("[");
			string word3 = line.substr(num1 + 2, (num2-num1-3));
			fout << word3 << "\n";
			fout.close();
			cout << "Marked item as done" << "\n";
			del(argv);
		}
	}
	fin.close();
	if(flag == 0){
		cout << "Error: no incomplete item with index "<< argv[2] <<" exists.\n";
	}
}

void report(){
	ifstream fin;
	int count = 0;
	fin.open("task.txt");
	string line;
	vector<string> pending;
	while(fin){
		getline(fin, line);
		if(line != "\0"){
			pending.push_back(line);
			count++;
		}
	}
	cout << "Pending : " << count << "\n";
	fin.close();
	for(auto x : pending){
		cout << x << "\n";
	}
	ifstream fin2;
	fin2.open("completed.txt");
	int count2 = 0;
	string line2;
	vector<string> completed;
	while(fin2){
		getline(fin2, line2);
		if(line2 != "\0"){
			count2++;
			completed.push_back(line2);
		}
	}
	cout << "\nCompleted : " << count2 << "\n";
	int i = 1;
	for(auto x : completed){
		cout << i << ". " << x << "\n";
		i++;
	}
	fin2.close();
	// cout << "\nCompleted : " << count2 << "\n";
	// string line2;
	// int i = 0;
	// while(fin2){
	// 	 getline(fin, line2);
	// 	 cout << (i+1) <<". "<< line2 << "\n"; 
	// }

}

int main(int argc, char **argv)
{
	if (argc == 1){
		help();
	}

	else {
		if(!strcmp(argv[1], "help")){
			help();
		}	

		if(!strcmp(argv[1], "add")){
			add(argv);
		}
		if(!strcmp(argv[1], "ls")){
			ls();
		}
		if(!strcmp(argv[1], "del")){
			cout << "Deleted task #" << argv[2] << "\n";
			del(argv);
		}
		if(!strcmp(argv[1], "done")){
			done(argv);
		}
		if(!strcmp(argv[1], "report")){
			report();
		}
	}
	return 0;
}