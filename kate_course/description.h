#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
class Date {
public:
    int day, month, year;
    friend std::istream& operator>>(std::istream& is, Date& date);
};

class Student {
private:
    std::string fullName;
    Date birthDate;
    int enrollmentYear;
    std::string faculty, department, group, recordBookNumber, gender;
    std::map<int, std::map<std::string, int>> grades;

public:
    bool hasNoGrades(const std::vector<int>& gradesList) const {
        for (const auto& session : grades) {
            for (const auto& subjectGrade : session.second) {
                if (std::find(gradesList.begin(), gradesList.end(), subjectGrade.second) != gradesList.end()) {
                    return false;
                }
            }
        }
        return true;
    }

    friend std::istream& operator>>(std::istream& is, Student& student);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

class University {
private:
    std::vector<Student> students;

public:
    void loadStudents(const std::string &filename);

    void printFilteredStudents(std::ostream &console, std::ostream &file, int option);

    static void encrypt (const std::string filenameIn, const std::string filenameOut);

    static void decrypt (const std::string filenameIn, const std::string filenameOut);
    
};
#endif