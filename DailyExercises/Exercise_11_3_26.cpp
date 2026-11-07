#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <limits>

enum class Grade {
    A,
    B,
    C,
    D,
    F,
};

struct Student {
    std::string name;
    std::vector<int> scores {};
};

class Gradebook {
private:
    std::vector<Student> m_students;
    const Student* findStudent(const std::string& name) const;
    Student* findStudent(const std::string& name);
public: 
    void addStudent(const std::string& name);
    bool addScore(const std::string& name, int score);
    double average(const std::string& name) const;
    Grade letterGrade(const std::string& name) const;
    void printReport() const;
};
const Student* Gradebook::findStudent(const std::string& name) const{
    for (const auto& student : m_students) {
        if (student.name == name) {
            return &student;
        }
    }
    return nullptr;
}
Student* Gradebook::findStudent(const std::string& name) {
    for (auto& student : m_students) {
        if (student.name == name) {
            return &student;
        }
    }
    return nullptr;
}

void Gradebook::addStudent(const std::string& name) {
    const Student* student {Gradebook::findStudent(name)};
    if (student != nullptr) {
        std::cout << "Student already exists!";
        return;
    } else {
        m_students.push_back(Student {name});
    }  
}
bool Gradebook::addScore(const std::string& name, int score) {
    Student* student {Gradebook::findStudent(name)};
    if (student == nullptr) {
        std::cout << "No student found\n";
        return false;
    } else if (score < 0 || score > 100) {
        std::cout << "Invalid score. Must be between 0 & 100\n";
        return false;
    } else {
        student->scores.push_back(score);
        std::cout << "Score of " << score << " added.\n"; 
        return true;
    }   
}
double calculateAverage(const std::vector<int>& scores) {
    if (scores.empty()) {
        std::cout << "Student has no scores!\n";
        return 0.0;
    }
    double sum { 0.0 };
    for (const auto& score: scores) {
        sum = sum + score;
    }
    return sum/scores.size();
}

double Gradebook::average(const std::string& name) const {
    const Student* student {Gradebook::findStudent(name)};
    if (student == nullptr) {
        return 0.0;
    }
    return calculateAverage(student->scores);
}
Grade calcLetterGrade(double score) {
    if (score >= 90) {
        return Grade::A;
    } else if (score >= 80) {
        return Grade::B;
    } else if (score >= 70) {
        return Grade::C;
    } else if (score >= 60) {
        return Grade::D;
    } else {
        return Grade::F;
    }
}

Grade Gradebook::letterGrade(const std::string& name) const {
    const Student* student{Gradebook::findStudent(name)};
    if (student == nullptr) {
        std::cout << "Student does not exist!\n";
        return Grade::F;
    }
    double grade {calculateAverage(student->scores)};
    return calcLetterGrade(grade);
}
char printLetter(Grade grade) {
    switch (grade)
    {
    case Grade::A:
        return 'A';
        break;
    case Grade::B:
        return 'B';
        break;
    case Grade::C:
        return 'C';
        break;
    case Grade::D:
        return 'D';
        break;
    case Grade::F:
        return 'F';
        break;
    default:
        break;
    }
    return '?';
}

void Gradebook::printReport() const {
    double sum { 0.0 };
    for (const auto& student : m_students) {
        sum = calculateAverage(student.scores);
        std::cout << student.name << ": " << sum << " "<< printLetter(calcLetterGrade(sum)) << "\n";
    }
}
void gradebookMenu() {
    std::cout << "Select an option: \n";
    std::cout << "1. Add Student\n2. Add Grade to Student\n3. Get Student Average\n4. Generate Class Report Card.\n";
}

void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Gradebook myGradebook {};
    int choice { 0 };
    std::string studentName;
    int score { };
    bool gradeadded;
    double average;
    std::cout << "----------Welcome to the Gradebook Menu!----------\n";
    do {
        gradebookMenu();
        std::cout << "Your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) // If the previous extraction failed
        {       
            std::cin.clear(); 
            ignoreLine();
            continue;    
        }


        switch (choice) {
            case 1:
                std::cout << "Enter name of new student: ";
                std::cin >> studentName;
                myGradebook.addStudent(studentName);
                break;
            case 2:
                std::cout << "Enter name of student: ";
                std::cin >> studentName;
                std::cout << "Enter score: ";
                std::cin >> score;
                gradeadded = myGradebook.addScore(studentName, score);
                if (!gradeadded) {
                    std::cout << "Grade was not added!\n";
                } else {
                    std::cout << "Grade added!\n";
                }
                break;
            case 3:
                std::cout << "Enter name of student: ";
                std::cin >> studentName;
                average = myGradebook.average(studentName);
                if (average <= 0) {
                    std::cout << "Student does not exists!\n";
                }
                else {
                    std::cout << studentName << "'s average: " << average << "\n"; 
                }
                break;
            case 4:
                myGradebook.printReport();
                break;
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                break;
        }

    } while (choice != 0);
    return 0;
}

/*
Day 2: Gradebook Class (~45 min)

Goal: Practice designing a small class with private data, a public interface, and std::vector, plus const correctness and enum class.

Requirements

Define an enum class Grade { A, B, C, D, F }.
Define a struct Student with a std::string name and a std::vector<int> scores.
Define a class Gradebook with a private std::vector<Student> and these public member functions:
void addStudent(const std::string& name): returns nothing; ignore the call if the name already exists.
bool addScore(const std::string& name, int score): returns false if the student doesn’t exist or the score isn’t 0 to 100, otherwise adds it and returns true.
double average(const std::string& name) const: returns 0.0 if the student doesn’t exist or has no scores.
Grade letterGrade(const std::string& name) const: 90+ is A, 80+ B, 70+ C, 60+ D, else F.
void printReport() const: prints each student as name: avg (letter), e.g. Alice: 87.5 (B).
Add a private helper const Student* findStudent(const std::string& name) const that returns a pointer to the matching student, or nullptr if none. Use it inside the other functions rather than repeating the search loop.
Write a free function char gradeToChar(Grade g) that uses a switch for the printing.

Test in main()

Add three students, give them a few scores each, and include these cases:

a student with no scores
a duplicate addStudent
addScore with an invalid score (e.g. 150 or -5)
addScore for a name that doesn’t exist

Constraints

Mark member functions const wherever they don’t modify the object.
Pass std::string by const&.
Data members stay private.
Compile with -Wall -Wextra -std=c++17 and fix every warning.

Suggested time split

10 min: struct, enum, class skeleton
15 min: findStudent, addStudent, addScore
10 min: average and letterGrade
10 min: printReport, main tests

Stretch goals

double classAverage() const
const Student* topStudent() const, returning nullptr if the gradebook is empty
Print averages to one decimal place with std::fixed and std::setprecision(1) from <iomanip>

*/