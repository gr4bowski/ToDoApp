#include <bits/stdc++.h>

using namespace std;

#define LOG_READ_WRITE false

class Task
{
    private:
    string name;
    bool state;

    public:
    Task()
    {
        this->name = "";
        this->state = 0;
    }

    Task(string name)
    {
        this->name = name;
        this->state = 0;
    }

    Task(string name, bool state)
    {
        this->name = name;
        this->state = state;
    }

    ~Task()
    {

    }

    bool State() const
    {
        return state;
    }

    void ChangeState()
    {
        this->state = !this->state;
    }

    string Name() const
    {
        return name;
    }

    static void PrintList(vector<Task> tasks)
    {
        if (!tasks.empty()) {
            unsigned int count = 1;
            for (Task task : tasks)
                cout << count++ << ". " << task << endl;
        } else
            cout << "\nToDo list is empty!\n";
    }

    friend ostream& operator<<(ostream& os, const Task& task)
    {
        return os << task.Name() << " - " << (task.State() ? "done" : "not done");
    }
};

vector<Task> LoadTasksFromFile();
int SaveTasksToFile(vector<Task> tasks);

int main()
{
    set<string> names;
    vector<Task> tasks;
    string input;
    int action = -1;

    tasks = LoadTasksFromFile();
    for (Task task : tasks)
        names.insert(task.Name());

    while (true) {
        cout << "Press a key to take one of the following actions:\n"
             << "0 - List all tasks                               \n"
             << "1 - Create a new task                            \n"
             << "2 - Mark task                                    \n"
             << "3 - Delete a task                                \n"
             << "4 - Delete all tasks                             \n"
             << "X - Save & Exit                                  \n";
        
        getline(cin, input);

        if (input == "x" || input == "X")
            break;

        // Try/catch to make sure that a number has been given
        try {
            action = stoi(input);
        }
        catch (...) {
            cout << "\nIncorrect input, number is needed!\n\n";
            continue;
        }
        
        switch (action) {
        case 0: // List all tasks
            if (!tasks.empty())
                cout << "\nYour ToDo list:\n";
            Task::PrintList(tasks);
            cout << endl;
            break;
        case 1: // Creating new task
            {
                string name = "";

                CreateInput: {
                    cout << "\nPlease input new task's name:\n";

                    getline(cin, name);

                    if (names.contains(name)) {
                        cout << "Task - \"" << name << "\" already exists, use a different name!";
                        goto CreateInput;
                    }
                }

                Task new_task(name);

                tasks.push_back(new_task);
                names.insert(name);

                cout << "Task with name: \"" << tasks.back().Name() << "\" has been successfully added to Your ToDo list!\n\n";
            }
            break;
        case 2: // Mark chosen task
            {
            if (tasks.empty()) {
            cout << "\nNothing to mark, create a task first!\n\n";
            continue;
            }
            MarkInput: { // Goes back to retake user input
                cout << "\nWhich task do You want to mark/unmark?\n";
                Task::PrintList(tasks);
                cout << "X - Cancel\n";

                action = -1;

                getline(cin, input);

                if (input == "x" || input == "X")
                    continue;

                // Try/catch to make sure that a number has been given
                try {
                    action = stoi(input);
                }
                catch (...) {
                    cout << "\nIncorrect input, number is needed!\n\n";
                    goto MarkInput;
                }
                if (action < 0 || action > (int)tasks.size()) {
                    cout << "\nIncorrect input, number given has no corresponding task!\n\n";
                    goto MarkInput;
                }
            }
            tasks[action-1].ChangeState();
            cout << "\nTask - \"" << tasks[action-1].Name() << "\" successfully marked as " << (tasks[action-1].State() ? "done" : "not done") << "!\n\n";
            }
            break;

        case 3: // Delete chosen task
            {
                if (tasks.empty()) {
                    cout << "\nNothing to delete, create a task first!\n\n";
                    continue;
                }
                DeleteInput: { // Goes back to retake user input
                    cout << "\nWhich task do You want to delete?\n";
                    Task::PrintList(tasks);
                    cout << "X - Cancel\n";

                    action = -1;

                    getline(cin, input);

                    if (input == "x" || input == "X")
                        continue;

                    // Try/catch to make sure that a number has been given
                    try {
                        action = stoi(input);
                    }
                    catch (...) {
                        cout << "\nIncorrect input, number is needed!\n\n";
                        goto DeleteInput;
                    }
                    if (action < 0 || action > (int)tasks.size()) {
                        cout << "\nIncorrect input, number given has no corresponding task!\n\n";
                        goto DeleteInput;
                    }
                }

                if (action != 0) {
                    string deleted_name = tasks[action-1].Name();
                    names.erase(deleted_name);
                    tasks.erase(tasks.begin() + action-1);
                    cout << "\nTask - \"" << deleted_name << "\" successfully deleted!\n\n";
                }
            }
            break;
        case 4: // Delete all tasks
            {
                tasks.clear();
                names.clear();
                cout << "\nSuccessfully deleted all tasks!\n\n";
            }
            break;
        default: // User has given wrong input
            cout << "\nIncorrect input, number given has no corresponding action!\n\n";
        }
    } // Main loop

    SaveTasksToFile(tasks);
}

vector<Task> LoadTasksFromFile()
{
    vector<Task> tasks;
    fstream file;
    file.open("ToDoList.txt");
    
    while (file.peek() != EOF) {
        string name = "";
        int state = -1;

        file >> name >> state;

        if (name != "" && (state == 0 || state == 1)) {
            Task new_task(name, state);
            tasks.push_back(new_task);

            if (LOG_READ_WRITE)
                cout << "Loaded task: " << new_task << endl;
        }

    }

    cout << "\nSuccessfully loaded " << tasks.size() << " tasks!\n\n";

    return tasks;
}

int SaveTasksToFile(vector<Task> tasks)
{
    unsigned int count = 0;
    fstream file;

    file.open("ToDoList.txt");
    streambuf *coutbuf = std::cout.rdbuf();
    cout.rdbuf(file.rdbuf());

    for (Task task : tasks) {
        cout << task.Name() << " " << task.State() << endl;
        count++;
    }

    std::cout.rdbuf(coutbuf);

    cout << "\nSuccessfully saved " << count << " tasks!\n\n";

    return count;
}