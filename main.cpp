#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>
using namespace std;

// The file where the tasks will be stored. You can change the name:
const string ToDoFile = "db.txt";
const string temp = "temp.txt";
const string deadlines = "dead.txt";

struct Task
{
    string task;
    bool Progress;
    bool Priority;
    time_t deadline;
    
    Task()
    {
        Progress = false;
        Priority = false;
    }
};

// Comparing two strings, the starting point is optional
bool compare(string str1, string str2, int start = 0)
{
    int end = str2.length();
    for (int i = start, j = 0; i <= end, j < str2.length(); i++, j++)
    {
        if (str1[i] != str2[j])
        {
            return false;
        }
    }
    return true;
}

void Help(string func = "none")
{
    if (func == "add" || func == "none")
    {
        cout << "  > add - adds a task" << endl;
        cout << "    -c - the task is completed" << endl;
        cout << "    -p - the task is a priority" << endl;
    }
    if (func == "remove" || func == "none")
    {
        cout << "  > remove - removes a task" << endl;
        cout << "    . - removes everything" << endl;
        cout << "    -n - the line number" << endl;
        cout << "    -w - the first task with that word" << endl;
        cout << "    -c - completed tasks" << endl;
        cout << "    -p - priority tasks" << endl;
    }
    if (func == "view" || func == "none")
    {
        cout << "  > view - show all current tasks" << endl;
        cout << "    -c - show only completed" << endl;
        cout << "    -nc - show only incompleted" << endl;
        cout << "    -p - show only priority tasks" << endl;
        cout << "    -np - show only nonpriority tasks" << endl;
    }
    if (func == "change" || func == "none")
    {
        cout << "  > change - changes the process" << endl;
        cout << "    -l - which line to change" << endl;
        cout << "    -w - which task to change" << endl;
        cout << "      -c - changes the task from incompleted to completed" << endl;
        cout << "      -nc - changes the task from completed to incompleted" << endl;
        cout << "      -p - changes the task from nonpriority to priority" << endl;
        cout << "      -np - changes the task from priority to nonpriority" << endl;
    }
    if (func == "find" || func == "none")
    {
        cout << "  > find [word] - finds the first task with that word" << endl;
    }
    if (func == "exit" || func == "none")
    {
        cout << "  > exit - closes the program" << endl;
    }
}


time_t DeadlineMake(){
    string input;
    time_t timeRN, deadline;
    size_t AddTime;
    const map<string, size_t> timeUnits = {
        {"hour", 60},
        {"day", 1440},
        {"week", 10080},
        {"month", 43800},
        {"year", 525600}
    };
    string litl;
    int counter;
    cout << endl;
    fstream fileDL;
    fileDL.open(deadlines, ios::in);
    string line;
    int currentline = 1;
    while (getline(fileDL, line))
    {
        currentline = currentline + 1;
    }
    fileDL.close();
    fileDL.open(deadlines, ios::app);
    if(!fileDL.is_open()){
        cout << "Error! Could not open file!";
        return -1;
    }
    while(true){
        cout << "When will the deadline be? ";
        getline(cin, input);
        timeRN = time(NULL);

        for(const auto& [unit, minutes] : timeUnits){
            if(input.find(unit) != string::npos){
                litl = input.substr(0, (input.find("hour") - 1));
                counter = stoi(litl);

                deadline = timeRN + (minutes * 60 * counter);
                fileDL << currentline << " " << ctime(&deadline);
                return deadline;
            }
    }
    }
}

string DeadlineTime(time_t deadline){
    time_t timeRN = time(NULL);
    difftime(deadline, timeRN);
    const map<string, size_t> TimeUnits = {
        
    };

}

string DeadlineAdder(int numline){
    fstream fileDL(deadlines, ios::in);
    if(!fileDL.is_open()){
        cout << "Error!";
        return "Error!";
    }
    string line;
    int curline = 1;
    while(getline(fileDL, line)){
        if(curline == numline){

        }
        curline++;
    }
    time_t timeRN = time(NULL);
    
}

void Sort(){
    fstream file, tempf, deadl;
    file.open(ToDoFile, ios::in);
    deadl.open(deadlines, ios::in);
    tempf.open(temp, ios::out);

    string line, line2;
    while(getline(file, line) && getline(deadl, line2)){
        if(line.find("Priority") != string::npos){
            tempf << line.substr(2, line.length()) << endl;
            tempf << line2.substr(2, line2.length()) << endl;
        }
    }
    file.close();
    deadl.close();
    file.open(ToDoFile, ios::in);
    deadl.open(deadlines, ios::in);
    while(getline(file, line) && getline(deadl, line2)){
        if(line.find("Priority") == string::npos){
            tempf << line.substr(2, line.length()) << endl;
            tempf << line2.substr(2, line2.length()) << endl;
        }
    }
    file.close();
    deadl.close();
    tempf.close();

    file.open(ToDoFile, ios::out);
    deadl.open(deadlines, ios::out);
    tempf.open(temp, ios::in);
    int count = 1;
    int count1 = 1, count2 = 1;
    while(getline(tempf, line)){
        if(count % 2 == 0){
            deadl << count2 << " " << line << endl;
            count2++;
        }
        if(count % 2 == 1){
            file << count1 << " " << line << endl;
            count1++;
        }
        count++;
    }
    file.close();
    tempf.close();
    
}

// adding a task
void AddTask(Task &task, bool Priority = false)
{
    
    // task.deadline = DeadlineMake();
    // time_t timeRN = time(NULL);
    // difftime(timeRN, task.deadline);

    // string timetest = ctime(&task.deadline);
    // timetest.erase(timetest.end() - 1);
    DeadlineMake();
    fstream file;
    file.open(ToDoFile, ios::in);
    if (!file.is_open())
    {
        cout << "ERROR!" << endl;
        return;
    }
    if (!file.is_open())
    {
        cout << "ERROR!" << endl;
        return;
    }
    // checks which lines we're currently on
    string line;
    int currentline = 1;
    while (getline(file, line))
    {
        currentline = currentline + 1;
    }

    file.close();
    file.open(ToDoFile, ios::app);
    if (task.Progress)
    {
        file << currentline << " ";
        file << task.task << " Completed ";
    }
    else
    {
        file << currentline << " ";
        file << task.task << " Not done ";
    }
    if(Priority){
        file << " Priority";
    }
    file << endl;

    file.close();
    
}

// finds the task. At least the first one the string match
int Find(string word)
{
    fstream rfile;
    rfile.open(ToDoFile, ios::in);
    if (!rfile.is_open())
    {
        cout << "Error!" << endl;
        return -1;
    }
    string line;
    int currline = 1;
    while (getline(rfile, line))
    {
        if (line.find(word) != string::npos)
        {
            rfile.close();
            return currline;
        }
        currline++;
    }
    rfile.close();
    return -1;
}
// Deletes everything or one line of our choosing
void Remove(int line = -1)
{
    // rm everything
    if (line == -1)
    {
        ofstream file;
        file.open(ToDoFile);
        if (!file.is_open())
        {
            cout << "ERROR!" << endl;
            return;
        }
        file.close();
        file.open(deadlines);
        if (!file.is_open())
        {
            cout << "ERROR!" << endl;
            return;
        }
        file.close();
    }
    // rm specific line
    else if (line > 0)
    {
        // copies the mainFile's tasks onto the tempFile, just ignoring the specific line
        fstream file1;
        file1.open(ToDoFile, ios::in);
        fstream tempf;
        tempf.open(temp, ios::out);
        string linestr;
        int curline = 1; // current line
        if (!file1.is_open())
        {
            cout << "ERROR!" << endl;
            return;
        }
        if (!tempf.is_open())
        {
            cout << "ERROR!" << endl;
            return;
        }

        while (getline(file1, linestr))
        {
            if (line != curline)
            {
                tempf << linestr.substr(2, linestr.length()) << endl;
            }
            curline++;
        }
        tempf.close();
        file1.close();
        // replaces the mainFile's tasks with the temp one
        tempf.open(temp, ios::in);
        file1.open(ToDoFile, ios::out);
        curline = 1;
        while (getline(tempf, linestr))
        {
            file1 << curline << " " << linestr << endl;
            curline++;
        }
        file1.close();
        tempf.close();
        //now for the deadlines, just a complete copy-paste from what you see up there ^
        //just maybe making this with classes would of been better
        file1.open(deadlines, ios::in);
        tempf.open(temp, ios::out);
        curline = 1; // current line
        if (!file1.is_open())
        {
            cout << "ERROR!" << endl;
            return;
        }
        if (!tempf.is_open())
        {
            cout << "ERROR!" << endl;
            return;
        }

        while (getline(file1, linestr))
        {
            if (line != curline)
            {
                tempf << linestr.substr(0, linestr.length()) << endl;
            }
            curline++;
        }
        tempf.close();
        file1.close();
        // replaces the deadline's tasks with the temp one
        tempf.open(temp, ios::in);
        file1.open(deadlines, ios::out);
        curline = 1;
        while (getline(tempf, linestr))
        {
            file1 << curline << " " << linestr << endl;
            curline++;
        }
        file1.close();
        tempf.close();
    }
}

// Just shows whats currently in the database text/todolist/
// The stages -> 0 - shows every task, 1 - shows only the completed tasks, 2 - shows only the incompleted tasks
void View(int stage = 0)
{
    fstream rfile(ToDoFile, ios::in);
    if (!rfile.is_open())
    {
        cout << "ERROR!" << endl;
        return;
    }
    string line;
    cout << "----------------------------------------" << endl;
    if (stage == 0)
    { // all
        while (getline(rfile, line))
        {
            cout << line << endl;
        }
        cout << "----------------------------------------" << endl;
    }
    else if (stage == 1)
    { // completed
        while (getline(rfile, line))
        {
            if (line.find("Completed") != string::npos)
            {
                cout << line << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
    else if (stage == 2)
    { // incompleted
        while (getline(rfile, line))
        {
            if (line.find("Completed") == string::npos)
            {
                cout << line << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
    else if (stage == 3)
    { // priority
        while (getline(rfile, line))
        {
            if (line.find("Priority") != string::npos)
            {
                cout << line << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
    else if (stage == 4)
    { // priority
        while (getline(rfile, line))
        {
            if (line.find("Priority") == string::npos)
            {
                cout << line << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
    else
    { // if possibly there is something else instead of the stages
        cout << "Error!! Unknown stage.";
        return;
    }
}

// changes the tasks progress(from the bool - true - from incompleted to completed, false - from completed to incompleted)
//stages are for the progress/priority
void Change(int numline, int stage, bool ToCompleted)
{
    fstream file1;
    fstream tempf;
    file1.open(ToDoFile, ios::in);
    tempf.open(temp, ios::out);
    if (!file1.is_open())
    {
        cout << "ERROR!" << endl;
        return;
    }
    if (!tempf.is_open())
    {
        cout << "ERROR!" << endl;
        return;
    }

    // seeing which task needs to be changed and saving the changes in a temporary file
    string line;
    int curline = 1;
    while (getline(file1, line))
    {
        if (curline == numline)
        {
            if(stage == 1){ // progress
                if (ToCompleted){
                    tempf << line.replace(line.find("Not done"), 8, "Completed");
                }
                else{
                    tempf << line.replace(line.find("Completed"), 9, "Not done");
                }
            }
            if(stage == 2){ // priority 
                if (ToCompleted){
                    tempf << line << " Priority";
                }
                else{
                    tempf << line.replace(line.find("Priority"), 8, "");
                }
            }
            tempf << endl;
        }
        else
        {
            tempf << line << endl;
        }
        curline++;
    }
    file1.close();
    tempf.close();

    // replacing the tasks from the temporary to the main one
    tempf.open(temp, ios::in);
    file1.open(ToDoFile, ios::out);
    curline = 1;
    while (getline(tempf, line))
    {
        file1 << line << endl;
        curline++;
    }
    file1.close();
    tempf.close();
}

// The program. The help line explains all the functions
void App()
{
    string input;
    while (true)
    {
        cout << "# ";
        getline(cin, input);

        // help
        if (input == "help" || input == "h")
        {
            Help();
        }
        // exit
        if (compare(input, "exit"))
        {
            return;
        }
        // add
        else if (compare(input, "add"))
        {
            Task task;
            string tsk;
            if (compare(input, "-c", 4))
            {
                
                if (compare(input, "-p", 7))
                {
                
                task.Progress = true;
                task.task = input.substr(10, input.length());
                AddTask(task, true);
                }
                else{
                    
                    task.Progress = true;
                    task.task = input.substr(7, input.length());
                    AddTask(task);
                }

            }
            else if (compare(input, "-p", 4))
            {
                
                task.Progress = true;
                task.task = input.substr(7, input.length());
                AddTask(task, true);
            }
            else if ("add" != input)
            {
                
                task.task = input.substr(4, input.length());
                AddTask(task);
            }
            else
            {
                Help("add");
            }
        }
        // remove - not completed
        else if (compare(input, "remove"))
        {
            if (compare(input, " .", 6))
            { // everything
                Remove();
            }
            else if (compare(input, " -w", 6))
            {
                string word = input.substr(10, input.length());
                Remove(Find(word));
            }
            else if (compare(input, " -l", 6))
            { // specific line
                int rmline = stoi(input.substr(10, input.length()));
                Remove(rmline);
            }
            else if (compare(input, " -c", 6))
            {
                while(Find("Completed") != -1){
                    Remove(Find("Completed"));
                }
            }
            else if (compare(input, " -nc", 6))
            {
                while(Find("Not done") != -1){
                    Remove(Find("Not done"));
                }
            }
            else if (compare(input, " -p", 6))
            {
                while(Find("Priority") != -1){
                    Remove(Find("Priority"));
                }
            }
            else
            {
                Help("remove");
            }
        }
        // View
        else if (compare(input, "view"))
        {
            if (compare(input, " -c", 4))
            {
                View(1);
            }
            else if (compare(input, " -nc", 4))
            {
                View(2);
            }
            else if (compare(input, " -p", 4))
            {
                View(3);
            }
            else if (compare(input, " -np", 4))
            {
                View(4);
            }
            else
            {
                View();
            }
        }
        // finds the exact task
        else if (compare(input, "find"))
        {
            if (input != "find")
            {
                string word = input.substr(5, input.length());
                cout << "The word is at line " << Find(word) << endl;
            }
            else
            {
                Help("find");
            }
        }
        // change the tasks progress
        else if (compare(input, "change"))
        {
            if (compare(input, " -l", 6))
            {
                if (compare(input, " -c", 9))
                {
                    Change(stoi(input.substr(13, input.length())), 1, true);
                }
                else if (compare(input, " -nc", 9))
                {
                    Change(stoi(input.substr(14, input.length())), 1, false);
                }
                else if (compare(input, " -p", 9))
                {
                    Change(stoi(input.substr(13, input.length())), 2, true);
                }
                else if (compare(input, " -np", 9))
                {
                    Change(stoi(input.substr(14, input.length())), 2, false);
                }
            }
            else if (compare(input, " -w", 6))
            {
                string word = input.substr(13, input.length());
                if (compare(input, " -c", 9))
                {
                    Change(Find(word), 1, true);
                }
                else if (compare(input, " -nc", 9))
                {
                    Change(Find(word), 1, false);
                }
                else if (compare(input, " -p", 9))
                {
                    Change(Find(word), 2, true);
                }
                else if (compare(input, " -np", 9))
                {
                    Change(Find(word), 2, false);
                }
            }
            else
            {
                Help("change");
            }
        }
        Sort();
    }
}

int main()
{
    cout << "Hello! Write 'h' or 'help' for help!" << endl;
    App();
    cout << "Goodbye!";
    return 0;
}