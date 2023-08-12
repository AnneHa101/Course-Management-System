g++ -g LoggerSingleton.cpp Course.cpp UndergraduateStudent.cpp GraduateStudent.cpp Faculty.cpp School.cpp SchoolDriver.cpp -std=c++17 -o UniversityCourseManagement
./UniversityCourseManagement
valgrind --leak-check=yes ./UniversityCourseManagement