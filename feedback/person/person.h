#ifndef PERSON_H
#define PERSON_H

#include <ostream>
#include <string>

namespace foo {

class Person {
    // As the interface is more important than the implementation details, we
    // start off with the public part rather than the declaration of private
    // members.

  public:
    Person(const std::string& firstname, const std::string& lastname, int arg);

    // Getters and setters are defined here so they can be *inlined*. Inlining
    // allows us to have function (which can be changed later on) without the
    // actual overhead of a function call.
    //
    // As `firstname` and `lastname` is a string, and can therefore be rather
    // expensive to copy, we return a *const reference*. The *const* is
    // important so that someone cannot change `firstname` without using the
    // corresponding setter. The caller can create a copy on his end from the
    // *const reference* if needed.
    //
    // Furthermore, as getters do not mutate any fields, we mark them as
    // *const*. This allows us to use it while holding a `const Person&`. Such
    // `const Person&` are used in the operators below.

    const std::string& getFirstname() const {
        return firstname;
    }

    void setFirstname(const std::string& firstname) {
        this->firstname = firstname;
    }

    const std::string& getLastname() const {
        return lastname;
    }

    void setLastname(const std::string& lastname) {
        this->lastname = lastname;
    }

    // As the `age` is a primitive data type (`int`) we do not have to resort
    // to references. Simply returning / taking the `int` directly is
    // efficient.

    int getAge() const {
        return age;
    }

    void setAge(int age) {
        this->age = age;
    }

    // The operators follow. Here we declare them as *friend functions* for two
    // reasons:
    //
    // 1) Since they are regular functions rather than member functions (ie
    //    methods) automatic conversion can happen for both, the left-hand-side
    //    (lhs) and right-hand-side (rhs). See
    //    https://stackoverflow.com/a/4622467
    //
    // 2) Declaring that function as *friend* gives it access to its private
    //    (and protected) members. We could use the provided getters for this,
    //    but if member fields are changed at a later point in time, we should
    //    probably also change the definition of these operators.

    friend bool operator==(const Person&, const Person&);
    friend bool operator!=(const Person&, const Person&);

    friend bool operator<(const Person&, const Person&);
    friend bool operator<=(const Person&, const Person&);
    friend bool operator>(const Person&, const Person&);
    friend bool operator>=(const Person&, const Person&);

    // For almost every object a `swap` function can be pretty handy, we
    // therefore also add this one.

    friend void swap(Person&, Person&);

    // Providing a way to print (or *stringify*) an object is helpful for all
    // sorts of operations: debugging, logging, etc. Here we define a
    // `to_string` function similar to `std::to_string`.

    friend std::string to_string(const Person&);

  private:
    std::string firstname;
    std::string lastname;
    int age;
};

// Providing an output stream operator is also a good idea, so we do not have
// to write:
//
//     std::cout << to_string(a_person) << "\n";
//
// , but can just resort to
//
//     std::cout << a_person << "\n";
//
// Again, not that we use a *const reference*.

std::ostream& operator<<(std::ostream&, const Person&);

}  // end namespace foo

#endif  // PERSON_H
