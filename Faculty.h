#ifndef FACULTY_H
#define FACULTY_H

#include "Instructor.h"

class Faculty : public Instructor
{
private:
    string FacultyId;

    int MAX_COURSES_TEACHING; // 1 for Graduate Student, 3 for Faculty
    vector<shared_ptr<Course>> CoursesHasTaught;
    vector<shared_ptr<Course>> CoursesTeaching;

public:
    // Constructor
    Faculty(string FacultyId);

    // Destructor
    ~Faculty();

    // Override SetCourse()
    // Action is to assign faculty a course to teach
    // Can take at most 3 courses
    // Return true if the addition is successful; otherwise, return false
    bool SetCourse(shared_ptr<Course> Course, string Action);

    // Override RemoveCourseFromPerson()
    // Action is to remove course in CourseTeaching
    // Return true if the removal is successful; otherwise, return false
    // If faculty is not teaching the course, throw exception
    bool RemoveCourseFromPerson(shared_ptr<Course> Course, string Action);

    // Override GetCurrentCourses()
    // Action is to get courses in CoursesTeaching
    // Return CoursesTeaching vector
    vector<shared_ptr<Course>> GetCurrentCourses(string Action);

    // Override GetPreviousCourses()
    // Action is to get courses in CoursesHasTaught
    // Return CoursesHasTaught vector
    vector<shared_ptr<Course>> GetPreviousCourses(string Action);

    // Getters and Setters
    string GetId();
    void SetId(string FacultyId);
    string GetPersonType();
};
#endif