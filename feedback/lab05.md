# Feedback -- 17 November 2017

## Task 1

The folder `person` contains a header and source file, providing an implementation for `Person`.
Examine it and take note of the provided comments.

One can write `to_string(a_person)` without a `using namespace foo` declaration because of *argument dependent lookup*.
Read through the [corresponding documentation](http://en.cppreference.com/w/cpp/language/adl).

This is also the reason for the lines `using std::to_string` and `using std::swap`.
With them, one can simply write `to_string` (or `swap`) and the compiler will take the function from the `std` namespace for primitives or, for user defined types, iff available from the corresponding namespace.

Regarding *hashing*, see [Combining hash values](http://boost.sourceforge.net/doc/html/hash/combine.html)

It is very important to get all of these things right since they are used and trusted by the standard library.
Algorithms and containers may not work correctly (or inefficiently) if you mess up here.

## Task 2

There are multiple ways one can define comparison operators.
Probably the simplest one is using a dedicated function.

```cpp
bool byAge(const Person& lhs, const Person& rhs) {
    return lhs.getAge() < rhs.getAge();
}

// ...

std::sort(people.begin(), people.end(), byAge);
```

Sometimes people resort to *functors*, but this is only necessary when dealing with templates.

```cpp
struct ByAge {
    bool operator()(const Person& lhs, const Person& rhs) {
        return lhs.getAge() < rhs.getAge();
    }
};

// ...

std::sort(people.begin(), people.end(), ByAge{});
```

Lambdas are also a possible and common way.

```cpp
auto byAge = [](const Person& lhs, const Person& rhs) {
    return lhs.getAge() < rhs.getAge();
};

std::sort(people.begin(), people.end(), byAge);
```

## Task 3

Let me just stress it once more.
Always, Always, ALWAYS use library functions when you can.
Do not write a function yourself which is already provided by the standard library.

It is key to memorise which algorithms are there and how they are meant to be used.
