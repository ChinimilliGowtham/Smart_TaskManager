#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

struct Task {
    string title;
    string description;
    string deadline;
    int estimatedTime;
};

queue<Task> taskQueue;

void addTask() {
    Task newTask;
    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, newTask.title);
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    cout << "Enter deadline date: ";
    cin >> newTask.deadline;
    cout << "Enter estimated time required (in hours): ";
    cin >> newTask.estimatedTime;
    taskQueue.push(newTask);
}

void updateTask() {
    if (taskQueue.empty()) {
        cout << "No tasks to update." << endl;
        return;
    }

    string searchTitle;
    cout << "Enter the title of the task to update: ";
    cin.ignore();
    getline(cin, searchTitle);

    queue<Task> tempQueue;
    while (!taskQueue.empty()) {
        Task currentTask = taskQueue.front();
        taskQueue.pop();

        if (currentTask.title == searchTitle) {
            Task updatedTask;
            cout << "Enter updated task title: ";
            getline(cin, updatedTask.title);
            cout << "Enter updated task description: ";
            getline(cin, updatedTask.description);
            cout << "Enter updated deadline date: ";
            cin >> updatedTask.deadline;
            cout << "Enter updated estimated time required (in hours): ";
            cin >> updatedTask.estimatedTime;
            tempQueue.push(updatedTask);
        } else {
            tempQueue.push(currentTask);
        }
    }

    taskQueue = tempQueue;
}

void deleteTask() {
    if (taskQueue.empty()) {
        cout << "No tasks to delete." << endl;
        return;
    }

    string searchTitle;
    cout << "Enter the title of the task to delete: ";
    cin.ignore();
    getline(cin, searchTitle);

    queue<Task> tempQueue;
    while (!taskQueue.empty()) {
        Task currentTask = taskQueue.front();
        taskQueue.pop();

        if (currentTask.title != searchTitle) {
            tempQueue.push(currentTask);
        }
    }

    taskQueue = tempQueue;
}

void displayAllTasks() {
    if (taskQueue.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    queue<Task> tempQueue = taskQueue;
    while (!tempQueue.empty()) {
        Task currentTask = tempQueue.front();
        tempQueue.pop();
        cout << "Title: " << currentTask.title << endl;
        cout << "Description: " << currentTask.description << endl;
        cout << "Deadline: " << currentTask.deadline << endl;
        cout << "Estimated Time: " << currentTask.estimatedTime << " hours" << endl;
        cout << "----------------------" << endl;
    }
}

void displayByPriority() {
    if (taskQueue.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    vector<Task> taskVector;
    priority_queue<Task, vector<Task>, function<bool(const Task&, const Task&)>> taskPriorityQueue(
        [](const Task& a, const Task& b) { return a.deadline > b.deadline; }
    );

    // Create a copy of taskQueue to avoid modifying the original queue
    queue<Task> tempQueue = taskQueue;

    while (!tempQueue.empty()) {
        Task currentTask = tempQueue.front();
        tempQueue.pop();
        taskPriorityQueue.push(currentTask);
    }

    while (!taskPriorityQueue.empty()) {
        taskVector.push_back(taskPriorityQueue.top());
        taskPriorityQueue.pop();
    }

    for (const Task& task : taskVector) {
        cout << "Title: " << task.title << endl;
        cout << "Description: " << task.description << endl;
        cout << "Deadline: " << task.deadline << endl;
        cout << "Estimated Time: " << task.estimatedTime << " hours" << endl;
        cout << "----------------------" << endl;
    }
}

void displayShortestJobFirst() {
    if (taskQueue.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    vector<Task> taskVector;
    priority_queue<Task, vector<Task>, function<bool(const Task&, const Task&)>> taskPriorityQueue(
        [](const Task& a, const Task& b) { return a.estimatedTime > b.estimatedTime; }
    );

    // Create a copy of taskQueue to avoid modifying the original queue
    queue<Task> tempQueue = taskQueue;

    while (!tempQueue.empty()) {
        Task currentTask = tempQueue.front();
        tempQueue.pop();
        taskPriorityQueue.push(currentTask);
    }

    while (!taskPriorityQueue.empty()) {
        taskVector.push_back(taskPriorityQueue.top());
        taskPriorityQueue.pop();
    }

    for (const Task& task : taskVector) {
        cout << "Title: " << task.title << endl;
        cout << "Description: " << task.description << endl;
        cout << "Deadline: " << task.deadline << endl;
        cout << "Estimated Time: " << task.estimatedTime << " hours" << endl;
        cout << "----------------------" << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "===== Smart Task Manager =====" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Update Task" << endl;
        cout << "3. Delete Task" << endl;
        cout << "4. Display All Tasks" << endl;
        cout << "5. Display by Priority" << endl;
        cout << "6. Display Shortest Job First" << endl;
        cout << "7. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                updateTask();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                displayAllTasks();
                break;
            case 5:
                displayByPriority();
                break;
            case 6:
                displayShortestJobFirst();
                break;
            case 7:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 7);

    return 0;
}
