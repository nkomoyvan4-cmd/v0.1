
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

class Person {
private:
    std::string firstName;
    std::string surname;
    std::vector<double> homework;
    double examGrade;

public:
    // Constructors and destructor
    Person();
    Person(std::string first, std::string last,
           std::vector<double> hw, double exam);

    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    // Grade calculations
    double average() const;
    double median() const;

    double finalAverage() const;
    double finalMedian() const;

    // Getters
    std::string getFirstName() const;
    std::string getSurname() const;

    // Random grade generation
    void randomGrades();

    // Input and output operators
    friend std::istream& operator>>(std::istream& in,
                                    Person& p);

    friend std::ostream& operator<<(std::ostream& out,
                                    const Person& p);
};

#endif
