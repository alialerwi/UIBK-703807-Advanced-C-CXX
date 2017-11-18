// Always start with including the corresponding header file.
#include "person.h"

#include <cassert>

#include <tuple>

namespace foo {

Person::Person(const std::string& firstname, const std::string& lastname,
               int age)
    : firstname(firstname), lastname(lastname), age(age) {
    // For simplicity I use `assert`. But depending on the use-case, more
    // sophisticated checks would be more appropriate.
    assert(age >= 0);
}

bool operator==(const Person& lhs, const Person& rhs) {
    // Keep it simple, no need for a multi-line if / else structure.
    return lhs.firstname == rhs.firstname && lhs.lastname == rhs.lastname &&
           lhs.age == rhs.age;
}

bool operator!=(const Person& lhs, const Person& rhs) {
    // Do not violate DRY (do not repeat yourself)!
    return !(lhs == rhs);
}

bool operator<(const Person& lhs, const Person& rhs) {
    // Correct lexicographic ordering can be a pain to implement, resort to
    // `std::tie` for this. The small overhead is usually worth the improvement
    // in readability and maintainability.
    //
    // Also, include `all` fields which define your object as these functions
    // model *equivalence*. Equivalence is used by associative containers (eg
    // `std::set`).
    //
    // You don't want to have a `std::set` only include Person{"Peter",
    // "Jackson", 42} or Person{"John", "Smith", 42} just because they have the
    // same age.
    return std::tie(lhs.firstname, lhs.lastname, lhs.age) <
           std::tie(rhs.firstname, rhs.lastname, rhs.age);
}

bool operator<=(const Person& lhs, const Person& rhs) {
    return std::tie(lhs.firstname, lhs.lastname, lhs.age) <=
           std::tie(rhs.firstname, rhs.lastname, rhs.age);
}

bool operator>(const Person& lhs, const Person& rhs) {
    return std::tie(lhs.firstname, lhs.lastname, lhs.age) >
           std::tie(rhs.firstname, rhs.lastname, rhs.age);
}

bool operator>=(const Person& lhs, const Person& rhs) {
    return std::tie(lhs.firstname, lhs.lastname, lhs.age) >=
           std::tie(rhs.firstname, rhs.lastname, rhs.age);
}

void swap(Person& lhs, Person& rhs) {
    using std::swap;

    swap(lhs.firstname, rhs.firstname);
    swap(lhs.lastname, rhs.lastname);
    swap(lhs.age, rhs.age);
}

// This should be the fastest way to build the wanted string. See
// https://stackoverflow.com/a/18892355
std::string to_string(const Person& p) {
    using std::to_string;

    std::string s{"Person{\""};
    s += p.firstname;
    s += "\",\"";
    s += p.lastname;
    s += "\",";
    s += to_string(p.age);
    s += "}";
    return s;
}

std::ostream& operator<<(std::ostream& out, const Person& p) {
    // Again, do not violate DRY!
    return out << to_string(p);
}

}  // end namespace foo
