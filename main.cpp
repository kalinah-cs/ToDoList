#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//The file where the tasks will be stored. You can change the name:
const string ToDoFile = "db.txt";
const string temp = "temp.txt";

struct Task{
    string task;
    bool Progress;

    Task(){
        Progress = false;
    }
};

//Comparing two strings, optional where to start[from the first string]
bool compare(string str1, string str2, int start = 0){
    int end = str2.length();
    for(int i = start, j = 0; i <= end, j < str2.length(); i++, j++){
        if(str1[i] != str2[j]){
            return false;
        }
    }
    return true;
}

void AddTask(Task &task){
    fstream file(ToDoFile, ios::app);
    if(!file.is_open()){
        cout << "ERROR!";
        return;
    }
    if(task.Progress){
        file << task.task << " Completed";
        file << endl;
    }
    else{
        file << task.task << " Not done";
        file << endl;
    }

    file.close();
}

//not finished
void Remove(int line = 0){
    //rm everything
    if(line == 0){
        ofstream file(ToDoFile);
        if(!file.is_open()){
            cout << "ERROR!";
            return;
        }
        file.close();
    }
    //rm specific line
    else if(line > 0){
        line = line - 1;
        ifstream file1(ToDoFile);
        ofstream tempf(temp);
        string linestr;
        int curline = 0;

        while(getline(file1, linestr)){
            if(line != curline){
                tempf << linestr << endl;
            }
            curline++;
        }
        file1.close();
        tempf.close();
    }
}

void App(){
    string input;

    while(true){
        cout << "# ";
        getline(cin, input);

        if(input == "help" || input == "h"){
            cout << "  > add - adds a task -> add -c [task]";
            cout << endl << "    -c - the task is completed";
            cout << endl << "  > remove - removes a task";
            cout << endl << "    . - removes everything";
            cout << endl << "    -n - the line number";
            cout << endl << "  > exit - closes the program" << endl;
        }
        //exit
        if(compare(input, "exit")){
            return;
        }

        //add
        else if(compare(input, "add")){
            //add -c This is a task.
            cout << input.length() << endl;
            string tsk;
            if(compare(input, "-c", 4)){
                Task task;
                task.Progress = true;
                task.task = input.substr(7, input.length());
                AddTask(task);
            }
            else{
                Task task;
                task.task = input.substr(4, input.length());
                AddTask(task);
            }
        }

        //remove - not completed
        else if(compare(input, "remove ")){
            if(compare(input, ".", 7)){
                Remove();
            }
            else{
                int rmline = stoi(input.substr(7, input.length()));
                Remove(rmline);
            }
        }


    }
}


int main(){
    cout << "Hello!" << endl;
    App();
    cout << "Goodbye!";
    return 0;
}