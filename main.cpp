#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//The file where the tasks will be stored. You can change the name:
const string ToDoFile = "db.txt";

struct Task{
    string task;
    bool Process;

    Task(){
        Process = false;
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

void App(){
    string input;

    while(true){
        cout << "# ";
        getline(cin, input);

        //cannot use substr, find another way
        if(compare(input, "exit")){
            return;
        }
        else if(compare(input, "add")){
            //add -c This is a task.
            cout << input.length() << endl;
            string tsk;
            if(compare(input, "-c", 4)){
                Task task;
                task.Process = true;
                task.task = input.substr(6, input.length());
                AddTask(task);
            }
            else{
                cout << ":<" << endl;
            }
        }
    }
}


void AddTask(Task &task){

    fstream file(ToDoFile, ios::in);
    if(!file.is_open()){
        cout << "ERROR!";
        return;
    }

    

    file.close();
    fstream file(ToDoFile, ios::app);
    if(!file.is_open()){
        cout << "ERROR!";
        return;
    }



    file.close();
}

int main(){
    cout << "Hello!" << endl;
    App();
    cout << "Goodbye!";
    return 0;
}