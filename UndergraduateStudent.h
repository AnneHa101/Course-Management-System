#ifndef UNDERGRADUATE_STUDENT_H
#define UNDERGRADUATE_STUDENT_H

#include "Student.h"

class UndergraduateStudent : public Student
{
private:
    string StudentId; // Unique identifier
    vector<shared_ptr<Course>> CoursesTaken;
    vector<shared_ptr<Course>> CoursesEnrolled; // Not empty

public:
    // Constructor
    UndergraduateStudent(string UndergraduateStudentId);

    // Destructor
    ~UndergraduateStudent();

    // Override SetCourse()
    // Action is to enroll student in a course
    // Cannot enroll course in CoursesTaken
    // Course must be at student's level
    // Return true if the addition is successful; otherwise, return false
    bool SetCourse(shared_ptr<Course> Course, string Action);

    // Override RemoveCourseFromPerson()
    // Action is to remove course in CourseEnrolled
    // Return true if the removal is successful; otherwise, return false
    // If student is not taking the course, throw exception
    bool RemoveCourseFromPerson(shared_ptr<Course> Course, string Action);

    // Override GetCurrentCourses()
    // Action is to get courses in CoursesEnrolled
    // Return CoursesEnrolled vector
    vector<shared_ptr<Course>> GetCurrentCourses(string Action);

    // Override GetPreviousCourses()
    // Action is to get courses in CourseTaken
    // Return CoursesTaken vector
    vector<shared_ptr<Course>> GetPreviousCourses(string Action);

    // Getters and Setters
    string GetId();
    void SetId(string UndergraduateStudentId);
    string GetPersonType();
};
#endif