#ifndef PERSON_H
#define PERSON_H

#include "Course.h"

// PERSON INTERFACE
class Person
{
protected:
public:
    // Destructor
    virtual ~Person(){};

    // Add Person to Course
    // Return true if the addition is successful; otherwise, return false
    virtual bool SetCourse(shared_ptr<Course> Course, string Action) = 0; // Action = "ENROLL" or "TEACH"

    // Add Person to Previous Course

    
    // Return true if the addition is successful; otherwise, return false
    virtual bool SetCourse(shared_ptr<Course> Course, string Action) = 0;

    // Remove Person from Course
    // Return true if the removal is successful; otherwise, return false
    virtual bool RemoveCourseFromPerson(shared_ptr<Course> Course, string Action) = 0; // Action = "REMOVE_ENROLLED" or "REMOVE_TEACHING"

    // Get Course Person is taking / teaching
    // Return CoursesEnrolled / CoursesTeaching vector
    virtual vector<shared_ptr<Course>> GetCurrentCourses(string Action) = 0; // Action = "TAKING" or "TEACHING"

    // Get Course Person has taken / taught
    // Return CoursesTaken / CoursesHasTaught vector
    virtual vector<shared_ptr<Course>> GetPreviousCourses(string Action) = 0; // Action = "TAKEN" or "TAUGHT"

    // Getters and Setters
    virtual string GetId() = 0;
    virtual void SetId(string Id) = 0;
    virtual string GetPersonType() = 0;
};
#endif