#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string FILE_NAME = "tasks.txt";

int loadTasks(string tasks[]) {
    ifstream file(FILE_NAME);
    int i = 0;
    if (file.is_open()) {
        while (getline(file, tasks[i])) {
            i++;
        }
        file.close();
    }
    return i;
}

void saveTasks(string tasks[], int count) {
    ofstream file(FILE_NAME);
    if (file.is_open()) {
        for (int j = 0; j < count; j++) {
            file << tasks[j] << endl;
        }
        file.close();
    }
}

int main() {
    string tasks[100];
    int i = loadTasks(tasks);
    int option = -1;

    while (true) {
        cout << "\n----------- Welcome to To-Do List Program ------------" << endl;
        cout << "1- Add New Task" << endl;
        cout << "2- View Tasks" << endl;
        cout << "3- Delete Task" << endl;
        cout << "4- Update Task" << endl;
        cout << "5- Mark Task as Complete/Incomplete" << endl;
        cout << "6- Exit" << endl;
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                if (i < 100) {
                    cout << "Enter your task: ";
                    string task;
                    getline(cin, task);
                    tasks[i] = "[ ] " + task;
                    i++;
                    saveTasks(tasks, i);
                    cout << "Task Added Successfully" << endl;
                } else {
                    cout << "Task list is full!" << endl;
                }
                break;

            case 2:
                if (i == 0) {
                    cout << "No Tasks Available" << endl;
                } else {
                    for (int j = 0; j < i; j++) {
                        cout << j + 1 << ". " << tasks[j] << endl;
                    }
                }
                break;

            case 3:
                cout << "Enter the task number to delete: ";
                int num;
                cin >> num;
                if (num > 0 && num <= i) {
                    for (int j = num - 1; j < i - 1; j++) {
                        tasks[j] = tasks[j + 1];
                    }
                    i--;
                    saveTasks(tasks, i);
                    cout << "Task Deleted Successfully" << endl;
                } else {
                    cout << "Invalid Task Number" << endl;
                }
                break;

            case 4:
                cout << "Enter the task number to update: ";
                int num1;
                cin >> num1;
                cin.ignore();
                if (num1 > 0 && num1 <= i) {
                    cout << "Enter your new task: ";
                    string updatedTask;
                    getline(cin, updatedTask);
                    tasks[num1 - 1] = "[ ] " + updatedTask;
                    saveTasks(tasks, i);
                    cout << "Task Updated Successfully" << endl;
                } else {
                    cout << "Invalid Task Number" << endl;
                }
                break;

            case 5:
                cout << "Complete Task will shown as [X] and Incomplete Task will shown as [ ]"<<endl<<" Enter the task number to mark as complete/incomplete: ";
                int num2;
                cin >> num2;
                cin.ignore();
                if (num2 > 0 && num2 <= i) {
                    if (tasks[num2 - 1][1] == ' ') {  
                        tasks[num2 - 1][1] = 'X';  
                        cout << "Task marked as COMPLETE!" << endl;
                    } else {
                        tasks[num2 - 1][1] = ' ';  
                        cout << "Task marked as INCOMPLETE!" << endl;
                    }
                    saveTasks(tasks, i);
                } else {
                    cout << "Invalid Task Number" << endl;
                }
                break;

            case 6:
                cout << "Exiting the program. Tasks saved!" << endl;
                return 0;

            default:
                cout << "Invalid option! Please try again." << endl;
        }
    }
}
