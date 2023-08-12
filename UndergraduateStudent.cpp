#include "UndergraduateStudent.h"

// Constructor
UndergraduateStudent::UndergraduateStudent(string UndergraduateStudentId) : StudentId(UndergraduateStudentId)
{
    CoursesTaken.clear();
    CoursesEnrolled.clear();
}

// Destructor
UndergraduateStudent::~UndergraduateStudent(){};

// Override SetCourse()
// Action is to enroll student in a course
// Cannot enroll course in CoursesTaken
// Course must be at student's level
// Return true if the addition is successful; otherwise, return false
bool UndergraduateStudent::SetCourse(shared_ptr<Course> Course, string Action)
{
    if (Action == "ENROLL")
    {
        for (int i = 0; i < CoursesTaken.size(); ++i)
        {
            if (CoursesTaken[i]->GetCourseId() == Course->GetCourseId())
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Student " + this->GetId() + " to " + Course->GetCourseId() + " (ERROR: " + this->GetId() + " has already taken Course " + Course->GetCourseId() + ")");
                return false;
            }
        }

        if (Course->GetCourseLevel() == false)
        {
            CoursesEnrolled.push_back(Course);
            LoggerSingleton::GetInstance().AddMessage("Successfully ASSIGN Student " + this->GetId() + " to " + Course->GetCourseId());
            return true;
        }

        else
        {
            LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Student " + this->GetId() + " to " + Course->GetCourseId() + " (ERROR: " + this->GetId() + " is not at level of " + Course->GetCourseId() + ")");
            return false;
        }
    }
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return false;
    }
}

// Override RemoveCourseFromPerson()
// Action is to remove course in CourseEnrolled
// Return true if the removal is successful; otherwise, return false
// If student is not taking the course, throw exception
bool UndergraduateStudent::RemoveCourseFromPerson(shared_ptr<Course> Course, string Action)
{
    if (Action == "REMOVE_ENROLLED")
    {
        for (int i = 0; i < CoursesEnrolled.size(); i++)
        {
            if (Course->GetCourseId() == CoursesEnrolled[i]->GetCourseId())
            {
                CoursesEnrolled.erase(CoursesEnrolled.begin() + i);
                LoggerSingleton::GetInstance().AddMessage("Successfully REMOVE Student " + this->GetId() + " from " + Course->GetCourseId());
                return true;
            }
        }

        LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Student " + this->GetId() + " from " + Course->GetCourseId() + " (ERROR: " + this->GetId() + " not taking " + Course->GetCourseId() + ")");
        return false;
    }
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return false;
    }

    return false;
}

// Override RetrieveCurrentCourses()
// Action is to get courses in CoursesEnrolled
// Return CoursesEnrolled vector
vector<shared_ptr<Course>> UndergraduateStudent::GetCurrentCourses(string Action)
{
    if (Action == "TAKING")
        return CoursesEnrolled;
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return vector<shared_ptr<Course>>();
    }
}

// Override RetrievePreviousCourses()
// Action is to get courses in CourseTaken
// Return CoursesTaken vector
vector<shared_ptr<Course>> UndergraduateStudent::GetPreviousCourses(string Action)
{
    if (Action == "TAKEN")
        return CoursesTaken;
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return vector<shared_ptr<Course>>();
    }
}

// Getters and Setters
string UndergraduateStudent::GetId()
{
    return StudentId;
}

void UndergraduateStudent::SetId(string UndergraduateStudentId)
{
    StudentId = UndergraduateStudentId;
}

string UndergraduateStudent::GetPersonType()
{
    return "UNDERGRADUATE";
}