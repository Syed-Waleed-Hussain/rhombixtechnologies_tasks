#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure to hold question data
struct Question {
    string questionText;
    string options[4];
    char correctAnswer;
};

// Function prototypes
void showWelcomeScreen();
string getUserName();
int selectQuizTopic();
void runQuiz(const Question questions[], int size, string userName, string topic);
void saveScore(string userName, string topic, int score);
void showCorrectAnswers(const Question questions[], int size);

// Quiz questions
Question osQuestions[] = {
    {"Which of the following is NOT a function of the Operating System?", {"a) Memory management", "b) Virus protection", "c) File system management", "d) Process management"}, 'b'},
    {"What is a process in an operating system?", {"a) A program in ROM", "b) A program in execution", "c) A compiler error", "d) An operating system service"}, 'b'},
    {"Which of the following is not a type of scheduling algorithm?", {"a) First-Come, First-Served (FCFS)", "b) Round Robin (RR)", "c) Random Scheduling (RS)", "d) Shortest Job First (SJF)"}, 'c'},
    {"What is the main function of a device driver?", {"a) Format hard drives", "b) Manage memory", "c) Act as an interface between hardware and OS", "d) Schedule processes"}, 'c'},
    {"In which scheduling algorithm is a time quantum used?", {"a) FCFS", "b) SJF", "c) Priority Scheduling", "d) Round Robin"}, 'd'},
    {"Which of the following is a non-preemptive scheduling algorithm?", {"a) Round Robin", "b) Shortest Job First (non-preemptive)", "c) Priority Scheduling (preemptive)", "d) Multilevel Queue"}, 'b'},
    {"What does a page table contain?", {"a) File locations", "b) Page numbers and their corresponding frame numbers", "c) Stack size", "d) Process priorities"}, 'b'},
    {"What is thrashing in OS?", {"a) Sudden power failure", "b) Excessive CPU usage", "c) High paging activity with low performance", "d) File system crash"}, 'c'},
    {"Which of the following is a condition for deadlock?", {"a) Mutual exclusion", "b) Preemption", "c) Resource release", "d) None of the above"}, 'a'},
    {"Which of these memory management techniques uses both segmentation and paging?", {"a) Swapping", "b) Contiguous allocation", "c) Virtual memory", "d) Segmentation with paging"}, 'd'},
    {"Which of these is not a valid state in the process life cycle?", {"a) New", "b) Blocked", "c) Waiting", "d) Exiting"}, 'b'},
    {"Which file system is used by default in most Linux distributions?", {"a) FAT32", "b) NTFS", "c) ext4", "d) HFS+"}, 'c'},
    {"What is the role of the kernel in an OS?", {"a) Manage file systems only", "b) Manage user interfaces", "c) Manage hardware and system resources", "d) Run only web-based programs"}, 'c'},
    {"What does context switching mean in an OS?", {"a) Switching between different hard drives", "b) Moving files between folders", "c) Switching CPU from one process to another", "d) Changing the OS version"}, 'c'},
    {"Which scheduling algorithm gives minimum average waiting time for a given set of processes?", {"a) FCFS", "b) Round Robin", "c) SJF", "d) Priority Scheduling"}, 'c'}
};

Question dsaQuestions[] = {
    {"What is the time complexity of linear search in the worst case?", {"a) O(log n)", "b) O(n²)", "c) O(n)", "d) O(1)"}, 'c'},
    {"Which data structure uses FIFO (First In First Out) principle?", {"a) Stack", "b) Queue", "c) Tree", "d) Graph"}, 'b'},
    {"Which sorting algorithm is best suited for nearly sorted arrays?", {"a) Quick Sort", "b) Selection Sort", "c) Insertion Sort", "d) Bubble Sort"}, 'c'},
    {"What is the time complexity of binary search in a sorted array?", {"a) O(n)", "b) O(log n)", "c) O(n log n)", "d) O(1)"}, 'b'},
    {"Which of the following is not a linear data structure?", {"a) Array", "b) Stack", "c) Tree", "d) Queue"}, 'c'},
    {"What is the maximum number of nodes in a binary tree of height h?", {"a) 2ʰ", "b) 2ʰ - 1", "c) h²", "d) h × 2"}, 'b'},
    {"Which data structure is used in recursion?", {"a) Queue", "b) Heap", "c) Stack", "d) Tree"}, 'c'},
    {"In which traversal is the root visited between the left and right subtrees?", {"a) Preorder", "b) Postorder", "c) Inorder", "d) Level-order"}, 'c'},
    {"Which of the following is true for a circular queue?", {"a) Last node always points to NULL", "b) Front = Rear always", "c) It overcomes the limitations of a linear queue", "d) It uses two stacks"}, 'c'},
    {"What is the best-case time complexity of Quick Sort?", {"a) O(n²)", "b) O(n log n)", "c) O(n)", "d) O(log n)"}, 'b'},
    {"What is the height of a complete binary tree with n nodes?", {"a) log₂(n+1)", "b) log₂(n)", "c) n", "d) √n"}, 'b'},
    {"Which algorithm is used for finding the shortest path in a graph (with non-negative weights)?", {"a) Kruskal's Algorithm", "b) Dijkstra's Algorithm", "c) DFS", "d) Prim's Algorithm"}, 'b'},
    {"Which traversal gives elements in ascending order in a Binary Search Tree (BST)?", {"a) Preorder", "b) Postorder", "c) Inorder", "d) Level-order"}, 'c'},
    {"Which of the following is a divide-and-conquer algorithm?", {"a) Linear Search", "b) Bubble Sort", "c) Merge Sort", "d) Hashing"}, 'c'},
    {"What does a hash function do in a hash table?", {"a) Deletes a value", "b) Maps a key to an index", "c) Reverses data", "d) Encrypts the data"}, 'b'}
};

Question mathQuestions[] = {
    {"What is the value of: 7 + (6 × 5² + 3)?", {"a) 160", "b) 158", "c) 190", "d) 155"}, 'b'},
    {"What is 25% of 200?", {"a) 25", "b) 40", "c) 50", "d) 100"}, 'c'},
    {"If 5x = 35, what is the value of x?", {"a) 6", "b) 8", "c) 7", "d) 5"}, 'c'},
    {"What is the area of a rectangle with length 12 and width 5?", {"a) 60", "b) 17", "c) 24", "d) 50"}, 'a'},
    {"Solve: √144 = ?", {"a) 14", "b) 11", "c) 12", "d) 10"}, 'c'},
    {"What is the value of π (pi) up to 2 decimal places?", {"a) 3.13", "b) 3.14", "c) 3.15", "d) 3.16"}, 'b'},
    {"A triangle has angles of 60° and 70°. What is the third angle?", {"a) 50°", "b) 40°", "c) 30°", "d) 60°"}, 'a'},
    {"What is the square of -9?", {"a) -81", "b) 81", "c) 18", "d) -18"}, 'b'},
    {"If a = 4 and b = 2, what is the value of a² + b²?", {"a) 20", "b) 18", "c) 16", "d) 12"}, 'a'},
    {"Which of the following is a prime number?", {"a) 21", "b) 33", "c) 37", "d) 39"}, 'c'},
    {"What is the perimeter of a square with side length 9?", {"a) 18", "b) 36", "c) 27", "d) 81"}, 'b'},
    {"3(x - 2) = 12. Find x.", {"a) 6", "b) 4", "c) 5", "d) 2"}, 'a'},
    {"A car travels 180 km in 3 hours. What is its average speed?", {"a) 50 km/h", "b) 60 km/h", "c) 55 km/h", "d) 65 km/h"}, 'b'},
    {"What is the next number in the pattern: 2, 4, 8, 16, __ ?", {"a) 20", "b) 24", "c) 30", "d) 32"}, 'd'},
    {"What is 8% of 500?", {"a) 30", "b) 35", "c) 40", "d) 45"}, 'c'}
};

Question cppQuestions[] = {
    {"What is the correct way to declare a variable in C++?", {"a) int x;", "b) integer x;", "c) x: int;", "d) declare int x;"}, 'a'},
    {"Which of the following is used to create a constant variable in C++?", {"a) permanent int x = 10;", "b) const int x = 10;", "c) int const x = 10;", "d) Both b and c"}, 'd'},
    {"What is the output of: int x = 10; x += 5; cout << x;", {"a) 10", "b) 5", "c) 15", "d) Error"}, 'c'},
    {"Which loop is guaranteed to execute at least once?", {"a) for loop", "b) while loop", "c) do-while loop", "d) foreach loop"}, 'c'},
    {"What will: int a = 5; int b = a++; cout << b; print?", {"a) 5", "b) 6", "c) 0", "d) Error"}, 'a'},
    {"How do you define a function that returns an integer and takes two integer parameters?", {"a) function int add(int a, int b)", "b) int add(int a, int b)", "c) int add(a, b)", "d) void add(int, int)"}, 'b'},
    {"Which keyword is used to define a class in C++?", {"a) define", "b) struct", "c) class", "d) object"}, 'c'},
    {"Which is the correct way to access a member function of an object?", {"a) object->function();", "b) object::function();", "c) object.function();", "d) object->function;"}, 'c'},
    {"What is the output of: int arr[] = {1, 2, 3}; cout << sizeof(arr)/sizeof(arr[0]);", {"a) 3", "b) 6", "c) 12", "d) Error"}, 'a'},
    {"What is the purpose of the 'this' pointer in C++?", {"a) It refers to the class itself", "b) It refers to the current object", "c) It stores memory address of any object", "d) It calls another constructor"}, 'b'},
    {"What will: vector<int> v = {10, 20, 30}; v.push_back(40); cout << v.size(); print?", {"a) 3", "b) 4", "c) 5", "d) Error"}, 'b'},
    {"Which header file is required for file input/output in C++?", {"a) <fstream>", "b) <file>", "c) <iostream>", "d) <stdio.h>"}, 'a'},
    {"What does: ifstream file(\"data.txt\"); if(file.is_open()) { cout << \"Opened!\"; } do?", {"a) Writes to a file", "b) Reads from a file", "c) Opens a file for writing only", "d) Opens a file for reading"}, 'd'},
    {"Which is a correct way to define a constructor?", {"a) void constructor() {}", "b) ClassName() {}", "c) int ClassName() {}", "d) constructor ClassName() {}"}, 'b'},
    {"Which feature allows the same function name to be used for different purposes?", {"a) Inheritance", "b) Encapsulation", "c) Polymorphism", "d) Abstraction"}, 'c'}
};

int main() {
    string userName;
    int choice;
    bool running = true;
    
    showWelcomeScreen();
    userName = getUserName();
    
    while(running) {
        choice = selectQuizTopic();
        
        switch(choice) {
            case 1:
                runQuiz(cppQuestions, 15, userName, "C++");
                break;
            case 2:
                runQuiz(osQuestions, 15, userName, "Operating Systems");
                break;
            case 3:
                runQuiz(dsaQuestions, 15, userName, "Data Structures");
                break;
            case 4:
                runQuiz(mathQuestions, 15, userName, "Mathematics");
                break;
            case 5:
                running = false;
                cout << "\nThank you for playing, " << userName << "! Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}

void showWelcomeScreen() {
    cout << "***************************************\n";
    cout << "*                                     *\n";
    cout << "*       WELCOME TO QUIZ GAME!         *\n";
    cout << "*                                     *\n";
    cout << "***************************************\n";
    cout << "\nTest your knowledge in various topics!\n";
    cout << "Answer questions and see how you score.\n\n";
}

string getUserName() {
    string name;
    cout << "Please enter your name: ";
    getline(cin, name);
    return name;
}

int selectQuizTopic() {
    int choice;
    cout << "\nSelect a quiz topic:\n";
    cout << "1. C++ Programming\n";
    cout << "2. Operating Systems\n";
    cout << "3. Data Structures & Algorithms\n";
    cout << "4. Mathematics\n";
    cout << "5. Quit\n";
    cout << "Enter your choice (1-5): ";
    cin >> choice;
    cin.ignore(); // Clear the input buffer
    return choice;
}

void runQuiz(const Question questions[], int size, string userName, string topic) {
    int score = 0;
    char answer;
    
    cout << "\nStarting " << topic << " Quiz!\n";
    cout << "There are " << size << " questions. Good luck!\n\n";
    
    for(int i = 0; i < size; i++) {
        cout << "Question " << (i+1) << ": " << questions[i].questionText << "\n";
        for(int j = 0; j < 4; j++) {
            cout << questions[i].options[j] << "\n";
        }
        cout << "Your answer (a-d): ";
        cin >> answer;
        cin.ignore(); // Clear the input buffer
        
        if(tolower(answer) == questions[i].correctAnswer) {
            cout << "Correct!\n\n";
            score++;
        } else {
            cout << "Incorrect!\n\n";
        }
    }
    
    cout << "\nQuiz completed!\n";
    cout << "Your score: " << score << "/" << size << "\n";
    saveScore(userName, topic, score);
    
    char showAnswers;
    cout << "\nWould you like to see the correct answers? (y/n): ";
    cin >> showAnswers;
    if(tolower(showAnswers) == 'y') {
        showCorrectAnswers(questions, size);
    }
}

void saveScore(string userName, string topic, int score) {
    ofstream outFile("score.txt", ios::app);
    if(outFile.is_open()) {
        outFile << "User: " << userName << " | Topic: " << topic << " | Score: " << score << "/15\n";
        outFile.close();
    } else {
        cout << "Unable to save score to file.\n";
    }
}

void showCorrectAnswers(const Question questions[], int size) {
    cout << "\nCorrect Answers:\n";
    for(int i = 0; i < size; i++) {
        cout << "Q" << (i+1) << ": " << questions[i].correctAnswer << "\n";
    }
    cout << "\n";
}