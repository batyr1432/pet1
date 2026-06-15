#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student {
    int id;           // 4 bites
    char name[32];    // 32 bites
    float gpa;        //4 bites
};

int getLastId()
{
    ifstream file("students.dat", ios::binary | ios::ate);
    

    if (!file.is_open()) 
        return 0;

    long size = file.tellg();

    if (size <= 0) 
        return 0;

    file.seekg(size - sizeof(Student));

    Student s;
    file.read(reinterpret_cast<char*>(&s), sizeof(Student));
    file.close();

    return s.id;
}


void addStudent(const string& name, float gpa)
{
    int cnt = getLastId();
    Student s;
    s.id = cnt + 1;
    strncpy(s.name, name.c_str(), 31);
    s.name[31] = '\0';
    s.gpa = gpa;
    ofstream file("students.dat", 
        ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&s), sizeof(Student));
    file.close();
}

bool getStudent(int index, Student& s)
{
    ifstream file("students.dat", ios::binary);
    if (!file.is_open()) {
        return false; 
    }

    file.seekg(0, ios::end); //check size of file to check boundaries
    long long fileSize = file.tellg();
    
    long long offset = (long long)index * sizeof(Student);


    if (offset < 0 || offset >= fileSize) {
        file.close();
        return false;
    }

    file.seekg(offset, ios::beg);
    if (!file.read(reinterpret_cast<char*>(&s), sizeof(Student)))
    {
        file.close();
        return false;
    }
    
    file.close();
    return true;
}

void showAll()
{
    ifstream file("students.dat", ios::binary);
    Student s;

    while (file.read(reinterpret_cast<char*>(&s),
                      sizeof(Student)))
    {
        cout << "ID: " << s.id << ", Name: " << s.name << ", GPA: " << s.gpa << endl;
    }

    file.close();
}


int main() {

    cout << "--- All students in base ---" << endl;
    showAll();
    cout << "---------------------------" << endl;

    int targetIndex = 8;
    Student foundStudent;

    if (getStudent(targetIndex, foundStudent)) {
        cout << "\nFound information for targeted index " << targetIndex << ":" << endl;
        cout << "Inner ID: " << foundStudent.id << endl;
        cout << "Name: " << foundStudent.name << endl;
        cout << "GPA: " << foundStudent.gpa << endl;
    } else {
        cout << "\nError: Student with index  " << targetIndex << " is not found" << endl;
    }

    return 0;
}