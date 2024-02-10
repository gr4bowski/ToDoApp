#ifndef TASK_HPP
#define TASK_HPP

#include <string>

using namespace std;

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

#endif