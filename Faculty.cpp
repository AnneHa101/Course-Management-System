#include "Faculty.h"

// Constructor
Faculty::Faculty(string FacultyId) : FacultyId(FacultyId), MAX_COURSES_TEACHING(3)
{
    CoursesHasTaught.clear();
    CoursesTeaching.clear();
}

// Destructor
Faculty::~Faculty(){};

// Override AddCourseToPerson() in Base class
// Action is to assign faculty a course to teach
// Can take at most 3 courses
// Return true if the addition is successful; otherwise, return false
bool Faculty::SetCourse(shared_ptr<Course> Course, string Action)
{
    if (Action == "TEACH")
    {
        if (CoursesTeaching.size() == MAX_COURSES_TEACHING)
        {
            LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Instructor " + this->GetId() + " to " + Course->GetCourseId() + " (ERROR: " + this->GetId() + " is teaching maximum number of Course allowed)");
            return false;
        }
        else
        {
            CoursesTeaching.push_back(Course);
            LoggerSingleton::GetInstance().AddMessage("Successfully ASSIGN Instructor " + this->GetId() + " to " + Course->GetCourseId());
            return true;
        }
    }
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return false;
    }
}

// Override RemoveCourseFromPerson()
// Action is to remove course in CourseTeaching
// Return true if the removal is successful; otherwise, return false
// If faculty is not teaching the course, throw exception
bool Faculty::RemoveCourseFromPerson(shared_ptr<Course> Course, string Action)
{
    if (Action == "REMOVE_TEACHING")
    {
        for (int i = 0; i < CoursesTeaching.size(); i++)
        {
            if (Course->GetCourseId() == CoursesTeaching[i]->GetCourseId())
            {
                CoursesTeaching.erase(CoursesTeaching.begin() + i);
                LoggerSingleton::GetInstance().AddMessage("Successfully REMOVE Instructor " + this->GetId() + " from " + Course->GetCourseId());
                return true;
            }
        }

        LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Instructor " + this->GetId() + " from " + Course->GetCourseId() + " (ERROR: " + this->GetId() + " not teaching " + Course->GetCourseId() + ")");
        return false;
    }
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return false;
    }

    return false;
}

// Override GetCurrentCourses()
// Action is to get courses in CoursesTeaching
// Return CoursesTeaching vector
vector<shared_ptr<Course>> Faculty::GetCurrentCourses(string Action)
{
    if (Action == "TEACHING")
        return CoursesTeaching;
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return vector<shared_ptr<Course>>();
    }
}

// Override GetPreviousCourses()
// Action is to get courses in CoursesHasTaught
// Return CoursesHasTaught vector
vector<shared_ptr<Course>> Faculty::GetPreviousCourses(string Action)
{
    if (Action == "TAUGHT")
        return CoursesHasTaught;
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return vector<shared_ptr<Course>>();
    }
}

// Getters and Setters
string Faculty::GetId()
{
    return FacultyId;
}

void Faculty::SetId(string FacultyId)
{
    FacultyId = FacultyId;
}

string Faculty::GetPersonType()
{
    return "FACULTY";
}