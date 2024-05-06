#include "description.h"

std::istream& operator>>(std::istream& is, Date& date) {
    char delim1, delim2;
    is >> date.day >> delim1 >> date.month >> delim2 >> date.year;
    return is;
}

std::istream& operator>>(std::istream& is, Student& student) {
    std::string line;
    std::getline(is, line);
    std::istringstream lineStream(line);
    std::string segment;
    std::getline(lineStream, student.fullName, ';');
    lineStream >> student.birthDate;
    lineStream.ignore();
    lineStream >> student.enrollmentYear;
    lineStream.ignore();
    std::getline(lineStream, student.faculty, ';');
    std::getline(lineStream, student.department, ';');
    std::getline(lineStream, student.group, ';');
    std::getline(lineStream, student.recordBookNumber, ';');
    std::getline(lineStream, student.gender, ';');

    int session;
    std::string subject;
    int grade;
    while (lineStream >> session) {
        lineStream.ignore();
        while (std::getline(lineStream, subject, '=')) {
            lineStream >> grade;
            lineStream.ignore();
            student.grades[session][subject] = grade;
            if (lineStream.peek() == ';') {
                lineStream.ignore();
                break;
            }
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Student Name: " << student.fullName << "\n"
       << "Birthdate: " << student.birthDate.day << "/" << student.birthDate.month << "/" << student.birthDate.year << "\n"
       << "Enrollment Year: " << student.enrollmentYear << "\n"
       << "Faculty: " << student.faculty << "\n"
       << "Department: " << student.department << "\n"
       << "Group: " << student.group << "\n"
       << "Record Book Number: " << student.recordBookNumber << "\n"
       << "Gender: " << student.gender << "\n";
    for (const auto& session : student.grades) {
        os << "Session " << session.first << ":\n";
        for (const auto& grade : session.second) {
            os << "  " << grade.first << ": " << grade.second << "\n";
        }
    }
    return os;
}

void University::loadStudents(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    Student student;
    while (inputFile >> student) {
        students.push_back(student);
    }
}

void University::printFilteredStudents(std::ostream& console, std::ostream& file, int option) {
    std::vector<int> gradesToCheck;
    switch (option) {
        case 1: gradesToCheck = {3}; break;
        case 2: gradesToCheck = {3, 4}; break;
        case 3: gradesToCheck = {5}; break;
        case 4: gradesToCheck = {3, 5}; break;
        case 5: gradesToCheck = {4, 5}; break;
        default:
            console << "Invalid option selected." << std::endl;
            file << "Invalid option selected." << std::endl;
            return;
    }

    for (const auto& student : students) {
        if (student.hasNoGrades(gradesToCheck)) {
            console << student << std::endl;
            file << student << std::endl;
        }
    }
}
