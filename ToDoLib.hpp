#ifndef TODOLIB_HPP
#define TODOLIB_HPP

#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Task.hpp"

#define LOG_READ_WRITE false

using namespace std;

vector<Task> LoadTasksFromFile()
{
    string file_name = "ToDoList.txt";
    vector<Task> tasks;
    fstream file(file_name);

    if (!file.good()) {
        cout << "\nFile " << file_name << " does not exist and will be created";
        ofstream{file_name};
    }
        

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

    if (tasks.size() > 0)
        cout << "\nSuccessfully loaded " << tasks.size() << " tasks!\n\n";
    else
        cout << "\nNo tasks have been loaded!\n\n";

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

    cout.rdbuf(coutbuf);

    if (count > 0)
        cout << "\nSuccessfully saved " << count << " tasks!\n\n";
    else
        cout << "\nNo tasks have been saved!\n\n";

    return count;
}

#endif