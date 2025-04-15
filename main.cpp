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

//Comparing two strings, the starting point is optional
bool compare(string str1, string str2, int start = 0){
    int end = str2.length();
    for(int i = start, j = 0; i <= end, j < str2.length(); i++, j++){
        if(str1[i] != str2[j]){
            return false;
        }
    }
    return true;
}

//adding a task
void AddTask(Task &task){
    fstream rfile(ToDoFile, ios::in);
    fstream file(ToDoFile, ios::app);
    if(!file.is_open()){
        cout << "ERROR!";
        return;
    }
    if(!rfile.is_open()){
        cout << "ERROR!";
        return;
    }
    //checkes which lines we're currently on
    string line;
    int currentline = 1;
    while(getline(rfile, line)){
        currentline = currentline + 1;
    }
    
    if(task.Progress){
        file << currentline << " ";
        file << task.task << " Completed";
        file << endl;
    }
    else{
        file << currentline << " ";
        file << task.task << " Not done";
        file << endl;
    }

    file.close();
}

//Deletes everything or one line of our choosing
void Remove(int line = -1){
    //rm everything
    if(line == -1){
        ofstream file(ToDoFile);
        if(!file.is_open()){
            cout << "ERROR!";
            return;
        }
        file.close();
    }
    //rm specific line
    else if(line > 0){
        //copies the mainFile's tasks onto the tempFile, just ignoring the specific line
        fstream file1;
        file1.open(ToDoFile, ios::in);
        fstream tempf;
        tempf.open(temp, ios::out);
        string linestr; 
        int curline = 1; //current line

        while(getline(file1, linestr)){
            if(line != curline){
                tempf << linestr.substr(2, linestr.length()) << endl;
            }
            curline++;
        }
        tempf.close();
        file1.close();
        //replaces the mainFile's tasks with the temp one
        tempf.open(temp, ios::in);
        file1.open(ToDoFile, ios::out);
        curline = 1;
        while(getline(tempf, linestr)){
            file1 << curline << " " << linestr << endl;
            curline++;
        }
        file1.close();
        tempf.close();
    }
}

//Just shows whats currently in the database text/todolist/
//The stages -> 0 - shows every task, 1 - shows only the completed tasks, 2 - shows only the incompleted tasks
void View(int stage = 0){
    fstream rfile(ToDoFile, ios::in);
    string line;
    cout << "----------------------------------------"<< endl;
    if(stage == 0){ //all
        while(getline(rfile, line)){
            cout << line << endl;
        }
        cout << "----------------------------------------" << endl;
    }
    else if(stage == 1){ //completed
        while(getline(rfile, line)){
            if(line.find("Completed") != string::npos){
                cout << line << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
    else if(stage == 2){ //incompleted
        while(getline(rfile, line)){
            if(line.find("Completed") == string::npos){
                cout << line << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
    else{ //if possibly there is something else instead of the stages
        cout << "Error!! Unknown stage.";
        return;
    }
}


//The program. The help line explains all the functions

// write a post func
void App(){
    string input;

    while(true){
        cout << "# ";
        getline(cin, input);

        //help
        if(input == "help" || input == "h"){
            cout << "  > add - adds a task"; 
            cout << endl << "    -c - the task is completed"; 
            cout << endl << "  > remove - removes a task";
            cout << endl << "    . - removes everything";
            cout << endl << "    -n - the line number";
            cout << endl << "  > view - show all current tasks";
            cout << endl << "    -c - show only completed";
            cout << endl << "    -d - show only incompleted";
            cout << endl << "  > change - changes the process";
            cout << endl << "    -c - changes the task from incompleted to completed";
            cout << endl << "    -d - changes the task from completed to incompleted";
            cout << endl << "  > exit - closes the program" << endl;
        }

        //exit
        if(compare(input, "exit")){
            return;
        }

        //add
        else if(compare(input, "add")){
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
            if(compare(input, ".", 7)){ //everything
                Remove();
            }
            else{ //specific line
                int rmline = stoi(input.substr(7, input.length()));
                Remove(rmline);
            }
        }
        //View
        else if(compare(input, "view")){
            if(compare(input, " -c", 4)){
                View(1);
            }
            else if(compare(input, " -d", 4)){
                View(2);
            }
            else{
                View();
            }
        }
        //change not completed
        else if(compare(input, "change")){
            if(compare(input, " -c", 6)){

            }
            else if(compare(input, " -d", 6)){

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