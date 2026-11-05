
#include "Person.h"

#include <algorithm>
#include <iomanip>
#include <random>

// Default constructor
Person::Person() : examGrade(0) {}

// Parameterized constructor
Person::Person(std::string first, std::string last,
               std::vector<double> hw, double exam)
    : firstName(first), surname(last),
      homework(hw), examGrade(exam) {}

// Copy constructor
Person::Person(const Person& other)
    : firstName(other.firstName),
      surname(other.surname),
      homework(other.homework),
      examGrade(other.examGrade) {}

// Assignment operator
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        firstName = other.firstName;
        surname = other.surname;
        homework = other.homework;
        examGrade = other.examGrade;
    }
    return *this;
}

// Destructor
Person::~Person() {}

// Calculate homework average
double Person::average() const {
    if (homework.empty())
        return 0;

    double sum = 0;

    for (double grade : homework)
        sum += grade;

    return sum / homework.size();
}

// Calculate homework median
double Person::median() const {
    if (homework.empty())
        return 0;

    std::vector<double> grades = homework;

    std::sort(grades.begin(), grades.end());

    int n = static_cast<int>(grades.size());

    if (n % 2 == 1)
        return grades[n / 2];

    return (grades[n / 2 - 1] +
            grades[n / 2]) / 2.0;
}

// Final grade using average
double Person::finalAverage() const {
    return 0.4 * average() + 0.6 * examGrade;
}

// Final grade using median
double Person::finalMedian() const {
    return 0.4 * median() + 0.6 * examGrade;
}

// Getters
std::string Person::getFirstName() const {
    return firstName;
}

std::string Person::getSurname() const {
    return surname;
}

// Read student information
std::istream& operator>>(std::istream& in, Person& p) {
    std::cout << "First name: ";
    in >> p.firstName;

    std::cout << "Surname: ";
    in >> p.surname;

    int count;

    std::cout << "Number of homework grades: ";
    in >> count;

    if (!in)
        return in;

    if (count < 0) {
        in.setstate(std::ios::failbit);
        return in;
    }

    p.homework.clear();

    for (int i = 0; i < count; i++) {
        double grade;

        std::cout << "Homework grade " << i + 1 << ": ";
        in >> grade;

        if (!in)
            return in;

        p.homework.push_back(grade);
    }

    std::cout << "Exam grade: ";
    in >> p.examGrade;

    return in;
}

// Display student results
std::ostream& operator<<(std::ostream& out,
                          const Person& p) {
    out << std::left << std::setw(15) << p.surname
        << std::setw(15) << p.firstName
        << std::right << std::fixed << std::setprecision(2)
        << std::setw(12) << p.finalAverage()
        << std::setw(12) << p.finalMedian();

    return out;
}

// Generate random grades
void Person::randomGrades() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 10);

    homework.clear();

    for (int i = 0; i < 5; i++)
        homework.push_back(dist(gen));

    examGrade = dist(gen);
}
