#ifndef GRADUATE_STUDENT_H
#define GRADUATE_STUDENT_H

#include "Student.h"
#include "Instructor.h"

class GraduateStudent : public Student, public Instructor
{
private:
    string StudentId; // Unique identifier
    vector<shared_ptr<Course>> CoursesTaken;
    vector<shared_ptr<Course>> CoursesEnrolled; // Not empty

    int MAX_COURSES_TEACHING; // 1 for Graduate Student, 3 for Faculty
    vector<shared_ptr<Course>> CoursesHasTaught;
    vector<shared_ptr<Course>> CoursesTeaching;

public:
    // Constructor
    GraduateStudent(string GraduateStudentId);

    // Destructor
    ~GraduateStudent();

    // Override SetCourse()
    // Action is to enroll student in a course or to assign student to a course to teach
    // Cannot teach course in CoursesEnrolled
    // Cannot teach Graduate Courses
    // Cannot take course in CoursesTeaching
    // Return true if the addition is successful; otherwise, return false
    bool SetCourse(shared_ptr<Course> Course, string Action);

    // Override RemoveCourseFromPerson()
    // Action is to remove course in CourseEnrolled or to remove course in CourseTeaching
    // Return true if the removal is successful; otherwise, return false
    // If student is not taking / teaching the course, throw exception
    bool RemoveCourseFromPerson(shared_ptr<Course> Course, string Action);

    // Override GetCurrentCourses()
    // Action is to get courses in CoursesEnrolled or CoursesTeaching
    // Return CoursesEnrolled / CoursesTeaching vector
    vector<shared_ptr<Course>> GetCurrentCourses(string Action);

    // Override GetPreviousCourses()
    // Action is to get courses in CourseTaken or CoursesHasTaught
    // Return CoursesTaken / CoursesHasTaught vector
    vector<shared_ptr<Course>> GetPreviousCourses(string Action);

    // Getters and Setters
    string GetId();
    void SetId(string GraduateStudentId);
    string GetPersonType();
};
#endif