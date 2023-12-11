#include <iostream>
using namespace std;

// Виключення (порожній клас)
class ExEmpty {};

// Виключення (клас з полями-параметрами)
class ExPar {
public:
    ExPar(int year) : year(year) {}
    int getYear() const { return year; }

private:
    int year;
};

// Власне виключення (спадкування стандартного виключення)
class MyDerivedException : public exception {
public:
    MyDerivedException(const char* msg, int year) : exception(msg), year(year) {}
    int getYear() const { return year; }

private:
    int year;
};

// Функція без специфікації виключень
bool isLeapYearNoSpec(int year) {
    if (year % 100 == 0) {
        if (year % 400 == 0) {
            return true;
        }
        else {
            throw ExEmpty();
        }
    }
    else {
        if (year % 4 == 0) {
            return true;
        }
        else {
            throw ExPar(year); 
        }
    }
}

// Функція зі спеціфікацією throw()
bool isLeapYearThrowSpec(int year) throw(ExEmpty, ExPar) {
    if (year % 100 == 0) {
        if (year % 400 == 0) {
            return true;
        }
        else {
            throw ExEmpty();
        }
    }
    else {
        if (year % 4 == 0) {
            return true;
        }
        else {
            throw ExPar(year);
        }
    }
}

// Функція з конкретною спеціфікацією 
bool isLeapYearStdSpec(int year) noexcept(false) {
    if (year % 100 == 0) {
        if (year % 400 == 0) {
            return true;
        }
        else {
            throw invalid_argument("Not a leap year");
        }
    }
    else {
        if (year % 4 == 0) {
            return true;
        }
        else {
            throw out_of_range("Not a leap year");
        }
    }
}

// Функція з власним реалізованим виключенням
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

int main() {
    try {
        int year;
        cout << "Enter a year: ";
        cin >> year;

        cout << "Without exception specification: " << isLeapYearNoSpec(year) << endl;
        cout << "With throw() specification: " << isLeapYearThrowSpec(year) << endl;
        cout << "With standard specification: " << isLeapYearStdSpec(year) << endl;
        cout << "With custom exception: " << isLeapYearCustomException(year) << endl;

    }
    catch (const ExEmpty&) {
        cerr << "Caught MyExceptionEmpty: Not a leap year." << endl;
    }
    catch (const ExPar& e) {
        cerr << "Caught MyExceptionParams: " << e.getYear() << " is not a leap year." << endl;
    }
    catch (const exception& e) {
        cerr << "Caught standard exception: " << e.what() << endl;
    }

    return 0;
}
