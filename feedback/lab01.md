# Feedback -- 20 October 2017

## Include Path / Shared Libraries

- read the ld.so(8) man-page
- take a look at the `ldd`, `nm`, and `objdump` utilities
- keep the following environment variables in mind and what they do:
    - `INCLUDE_PATH`
    - `LIBRARY_PATH`
    - `LD_LIBRARY_PATH`

## Initialisation

- read through the related *cppreference* pages:
    - [aggregate_initialization](http://en.cppreference.com/w/cpp/language/aggregate_initialization)
    - [list_initialization](http://en.cppreference.com/w/cpp/language/list_initialization)
    - [initializer_list](http://en.cppreference.com/w/cpp/utility/initializer_list)

## Task4

I apologise for not being as precise as possible in the instructions of task 4.
Each of the directories should correspond to one shared library, resulting in three shared libraries: `libFoo.so`, `libBar.so`, and `libBaz.so`.

## CMake

As we have seen some CMake code during the presentations I'd like to share my `CMakeLists.txt` regarding task 4 with some comments.
After running CMake take a look at the generated `CMakeCache.txt` file.
Try setting the environment variable `VERBOSE` to `1` before calling `make`.

```cmake
cmake_minimum_required(VERSION 3.5)
project(task4 LANGUAGES CXX)

# First we state the wanted compile flags. Here we assume GCC or Clang as
# compiler.
# Your set of compiler flags may depend on which compiler you are actually
# using.
# For simplificty we do not allow the user to override them here.
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror")

# Compiler flags specific for release and debug builds follow.
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")

# Typically by default we want a release build.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "CMake Build Type" FORCE)
endif()

# BUILD_SHARED_LIBS determines the default behaviour of add_library.
# It is a common CMake variable and the user should be able to override it
# when calling CMake.
# Try setting it to OFF by passing `-DBUILD_SHARED_LIBS=OFF` to cmake.
if(NOT DEFINED BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build Shared Libraries" FORCE)
endif()

# Since all three libraries are built in exactly the same manner, we can use a
# foreach loop.
# If the setup gets more complicated it is a good idea to put a dedicated
# CMakeLists.txt in each directory and include them using add_subdirectory.
foreach(name Foo Bar Baz)

    # Note that CMake does not recommend globbing for source files as you have
    # to rerun CMake upon adding a new source file.
    # This is necessary because the globbing happens during the CMake
    # invocation rather than during the make call.
    #
    # Never-the-less I prefer re-running CMake by hand when a new file was
    # added to managing a list of source files inside a CMakeLists.txt file.
    file(GLOB_RECURSE _srcs lib${name}/*.cc)

    # This defines our library, note that the STATIC / SHARED directive is
    # omitted as we want to depend on BUILD_SHARED_LIBS.
    add_library(${name} ${_srcs})

    # Since we now have defined our library, we can add certain properties to
    # this target.
    # Mainly the associated include direcotires.
    # Here we only have one and giving it PUBLIC visibilty will forward it to
    # each target linking against this library.
    # Please do not use include_directories, always associate an include
    # directory with a specific target.
    target_include_directories(${name} PUBLIC lib${name})

endforeach(name)

# Next we need to state the dependency between libBaz.so and libBar.so. Note
# that the public include directories are forwarded automatically.
target_link_libraries(Baz Bar)

# Finally we can define our executable.
add_executable(app app/app.cc)

# Followed by the dependency to our libraries.
target_link_libraries(app Foo Bar Baz)
```

This is just one of many possible solutions and certainly not the *best* one.
But it should give you something to think about given you are into CMake.

## Assertions

- read the assert(3) man-page and note the `NDEBUG` define
- have a look at CMake's default compiler flags for release and debug builds

## Presentation

As already stated by the main README, please ensure your computer works with the installed projector *before* the lab starts.

Furthermore, please adjust your font-size and colour-theme accordingly.
A light colour-theme is preferred as a higher contrast is typically achieved with a dark font on a light background.
