#include "Course.h"

// Constructor
Course::Course(string CourseId, string CourseName, bool GraduateLevel) : CourseId(CourseId), CourseName(CourseName), GraduateLevel(GraduateLevel)
{
    SeatsAvailable = MAX_STUDENTS; // Courses can have at most 40 students
    Prerequisites.clear();
}

// Destructor
Course::~Course() {}

// Add prerequisite to the course
// The course must not be the prerequisite of itself
// Graduate courses cannot be the prerequisite for an undergraduate courses
// Cannot add course that does not exist in the system
void Course::AddPrerequisite(shared_ptr<Course> Course)
{
    if (Course->GetCourseLevel() == true && this->GetCourseLevel() == false)
    {
        LoggerSingleton::GetInstance().AddMessage("Failed to ADD Course " + Course->GetCourseId() + " as prerequisite of Course " + this->GetCourseId() + " (ERROR: Graduate Courses cannot be prerequisite of Undergraduate Courses)");
        return;
    }

    if (Course->CourseId != this->CourseId)
    {
        this->Prerequisites.push_back(Course);
        LoggerSingleton::GetInstance().AddMessage("Successfully ADD Course " + Course->GetCourseId() + " as prerequisite of " + this->GetCourseId());
        return;
    }
}

// Remove prerequisite from the course
// Cannot remove course that does not exist
void Course::RemovePrerequisite(shared_ptr<Course> Course)
{
    for (int i = 0; i < Prerequisites.size(); i++)
    {
        if (Prerequisites[i]->GetCourseId() == Course->GetCourseId())
            Prerequisites.erase(Prerequisites.begin() + i);
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Prerequisite " + Course->GetCourseId() + " of " + this->GetCourseId() + " (ERROR: " + Course->GetCourseId() + " not Prerequisite)");
    return;
}

// Getters and Setters
string Course::GetCourseId()
{
    return CourseId;
}

bool Course::GetCourseLevel()
{
    return GraduateLevel;
}

int Course::GetSeatsAvailable()
{
    return SeatsAvailable;
}

vector<shared_ptr<Course>> Course::GetPrerequisites()
{
    return Prerequisites;
}

void Course::DecrementSeatsAvailable()
{
    SeatsAvailable -= 1;
}

void Course::IncrementSeatsAvailable()
{
    SeatsAvailable += 1;
}
