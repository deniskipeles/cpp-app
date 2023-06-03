cmake_minimum_required(VERSION 3.12)
project(cppsum)

set(CMAKE_CXX_STANDARD 11)

# Add the executable
add_executable(cppsum main.cpp html2text.cpp)

# Add any additional dependencies or flags
# For example, if you are using the HTML parsing library, you can add:
# target_link_libraries(cppsum YourHTMLParsingLibrary)

# Specify any additional include directories
# For example, if you have additional header files in a directory called "include",
# you can add:
# target_include_directories(cppsum PUBLIC include)
