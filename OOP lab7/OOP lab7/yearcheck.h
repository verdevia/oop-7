#include <iostream>

class MyExceptionEmpty {};

class MyExceptionParams {
public:
    MyExceptionParams(int year) : year(year) {}
    int getYear() const { return year; }

private:
    int year;
};

class MyDerivedException : public std::exception {
public:
    MyDerivedException(const char* msg, int year) : std::exception(msg), year(year) {}
    int getYear() const { return year; }

private:
    int year;
};

bool isLeapYearNoSpec(int year) {
    if (year % 100 == 0) {
        if (year % 400 == 0) {
            return true;
        }
        else {
            throw MyExceptionEmpty();
        }
    }
    else {
        if (year % 4 == 0) {
            return true;
        }
        else {
            throw MyExceptionParams(year);
        }
    }
}

bool isLeapYearThrowSpec(int year) throw(MyExceptionEmpty, MyExceptionParams) {
    if (year % 100 == 0) {
        if (year % 400 == 0) {
            return true;
        }
        else {
            throw MyExceptionEmpty();
        }
    }
    else {
        if (year % 4 == 0) {
            return true;
        }
        else {
            throw MyExceptionParams(year);
        }
    }
}

bool isLeapYearStdSpec(int year) noexcept(false) {
    if (year % 100 == 0) {
        if (year % 400 == 0) {
            return true;
        }
        else {
            throw std::invalid_argument("Not a leap year");
        }
    }
    else {
        if (year % 4 == 0) {
            return true;
        }
        else {
            throw std::out_of_range("Not a leap year");
        }
    }
}

bool isLeapYearCustomException(int year) {
    if (year % 100 == 0) {
        if (year % 400 == 0) {
            return true;
        }
        else {
            throw MyDerivedException("Not a leap year", year);
        }
    }
    else {
        if (year % 4 == 0) {
            return true;
        }
        else {
            throw MyDerivedException("Not a leap year", year);
        }
    }
}
