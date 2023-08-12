#ifndef COURSE_H
#define COURSE_H

#include "LoggerSingleton.h"

using namespace std;

class Course
{
protected:
    string CourseId; // Unique identifier
    string CourseName;
    int SeatsAvailable;
    vector<shared_ptr<Course>> Prerequisites; // Not required, does not include itself
    bool GraduateLevel;                       // Undergraduate or Graduate

public:
    const int MAX_STUDENTS = 40;

    // Constructor
    Course(string CourseId, string CourseName, bool GraduateLevel);

    // Destructor
    ~Course();

    // Add prerequisite to the course
    // The course must not be the prerequisite of itself
    // Graduate courses cannot be the prerequisite for an undergraduate courses
    // Cannot add course that does not exist in the system
    void AddPrerequisite(shared_ptr<Course> Course);

    // Remove prerequisite from the course
    // Cannot remove course that does not exist
    void RemovePrerequisite(shared_ptr<Course> Course);

    // Getters and Setters
    string GetCourseId();
    bool GetCourseLevel();
    int GetSeatsAvailable();
    vector<shared_ptr<Course>> GetPrerequisites();
    void DecrementSeatsAvailable();
    void IncrementSeatsAvailable();
};
#endif