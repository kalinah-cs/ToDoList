#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// The file where the tasks will be stored. You can change the name:
const string ToDoFile = "db.txt";
const string temp = "temp.txt";

struct Task
{
    string task;
    bool Progress;

    Task()
    {
        Progress = false;
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
    }
    if (func == "remove" || func == "none")
    {
        cout << "  > remove - removes a task" << endl;
        cout << "    . - removes everything" << endl;
        cout << "    -n - the line number" << endl;
        cout << "    -w - the first task with that word" << endl;
    }
    if (func == "view" || func == "none")
    {
        cout << "  > view - show all current tasks" << endl;
        cout << "    -c - show only completed" << endl;
        cout << "    -d - show only incompleted" << endl;
    }
    if (func == "change" || func == "none")
    {
        cout << "  > change - changes the process" << endl;
        cout << "    -l - which line to change" << endl;
        cout << "    -w - which task to change" << endl;
        cout << "      -c - changes the task from incompleted to completed" << endl;
        cout << "      -d - changes the task from completed to incompleted" << endl;
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

// adding a task
void AddTask(Task &task)
{
    fstream rfile(ToDoFile, ios::in);
    fstream file(ToDoFile, ios::app);
    if (!file.is_open())
    {
        cout << "ERROR!" << endl;
        return;
    }
    if (!rfile.is_open())
    {
        cout << "ERROR!" << endl;
        return;
    }
    // checkes which lines we're currently on
    string line;
    int currentline = 1;
    while (getline(rfile, line))
    {
        currentline = currentline + 1;
    }

    if (task.Progress)
    {
        file << currentline << " ";
        file << task.task << " Completed";
        file << endl;
    }
    else
    {
        file << currentline << " ";
        file << task.task << " Not done";
        file << endl;
    }

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
    cout << "Error! Cannot find a task like that!" << endl;
    cout << "Error ";
    return -1;
}
// Deletes everything or one line of our choosing
void Remove(int line = -1)
{
    // rm everything
    if (line == -1)
    {
        ofstream file(ToDoFile);
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
    else
    { // if possibly there is something else instead of the stages
        cout << "Error!! Unknown stage.";
        return;
    }
}

// changes the tasks progress(from the bool - true - from incompleted to completed, false - from completed to incompleted)
void Change(int numline, bool ToCompleted)
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
            if (ToCompleted)
                tempf << line.replace(line.find("Not done"), line.length(), "Completed") << endl;
            else
                tempf << line.replace(line.find("Completed"), line.length(), "Not done") << endl;
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
            string tsk;
            if (compare(input, "-c", 4))
            {
                Task task;
                task.Progress = true;
                task.task = input.substr(7, input.length());
                AddTask(task);
            }
            else if ("add" != input)
            {
                Task task;
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
            else if (compare(input, " -d", 4))
            {
                View(2);
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
                    Change(stoi(input.substr(13, input.length())), true);
                }
                else if (compare(input, " -d", 9))
                {
                    Change(stoi(input.substr(13, input.length())), false);
                }
            }
            else if (compare(input, " -w", 6))
            {
                string word = input.substr(13, input.length());
                if (compare(input, " -c", 9))
                {
                    Change(Find(word), true);
                }
                if (compare(input, " -d", 9))
                {
                    Change(Find(word), false);
                }
            }
            else
            {
                Help("change");
            }
        }
    }
}

int main()
{
    cout << "Hello! Write 'h' or 'help' for help!" << endl;
    App();
    cout << "Goodbye!";
    return 0;
}