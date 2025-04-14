#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string ToDoFile = "db.txt";

struct Task{
     
};

void App(){
    string input;

    while(true){
        cout << "a" << endl;
        cin >> input;
        if(input == "exit" || input == "EXIT"){
            return;
        }
        else if(input == "add" || input == "ADD"){

        }
    }
}

void AddTask(){
    ofstream file;
    file.open(ToDoFile);
    if(!file.is_open()){
        cout << "ERROR!";
        return;
    }

}

int main(){
    cout << "Hello!" << endl;
    

    return 0;
}