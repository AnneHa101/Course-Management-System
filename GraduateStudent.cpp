#include "GraduateStudent.h"

// Constructor
GraduateStudent::GraduateStudent(string GraduateStudentId) : StudentId(GraduateStudentId), MAX_COURSES_TEACHING(1)
{
    CoursesTaken.clear();
    CoursesEnrolled.clear();
    CoursesHasTaught.clear();
    CoursesTeaching.clear();
}

// Destructor
GraduateStudent::~GraduateStudent(){};

// Override AddCourseToPerson() in Base class
// Action is to enroll student in a course or to assign student to a course to teach
// Cannot teach course in CoursesEnrolled
// Cannot teach Graduate Courses
// Cannot take course in CoursesTeaching
// Return true if the addition is successful; otherwise, return false
bool GraduateStudent::SetCourse(shared_ptr<Course> Course, string Action)
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

        for (int i = 0; i < CoursesTeaching.size(); i++)
        {
            if (CoursesTeaching[i]->GetCourseId() == Course->GetCourseId())
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Student " + this->GetId() + " to " + Course->GetCourseId() + " (ERROR: " + this->GetId() + " is teaching Course " + Course->GetCourseId() + ")");
                return false;
            }
        }

        if (Course->GetCourseLevel() == true)
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
    else if (Action == "TEACH")
    {
        if (CoursesTeaching.size() == MAX_COURSES_TEACHING)
        {
            LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Instructor " + this->GetId() + " to " + Course->GetCourseId() + " (ERROR: " + this->GetId() + " is teaching maximum number of Course allowed)");
            return false;
        }

        if (Course->GetCourseLevel() == true)
        {
            CoursesEnrolled.push_back(Course);
            LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Instructor " + this->GetId() + " to " + Course->GetCourseId() + " (ERROR: Graduate Students cannot teach Graduate Courses)");
            return false;
        }

        for (int i = 0; i < CoursesEnrolled.size(); i++)
        {
            if (CoursesEnrolled[i]->GetCourseId() == Course->GetCourseId())
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Instructor " + this->GetId() + " to " + Course->GetCourseId() + " (ERROR: " + this->GetId() + " is enrolled in Course " + Course->GetCourseId() + ")");
                return false;
            }
        }

        CoursesTeaching.push_back(Course);
        LoggerSingleton::GetInstance().AddMessage("Successfully ASSIGN Instructor " + this->GetId() + " to " + Course->GetCourseId());
        return true;
    }
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return false;
    }
}

// Override RemoveCourseFromPerson()
// Action is to remove course in CourseEnrolled or to remove course in CourseTeaching
// Return true if the removal is successful; otherwise, return false
// If student is not taking / teaching the course, throw exception
bool GraduateStudent::RemoveCourseFromPerson(shared_ptr<Course> Course, string Action)
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
    else if (Action == "REMOVE_TEACHING")
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
// Action is to get courses in CoursesEnrolled or CoursesTeaching
// Return CoursesEnrolled / CoursesTeaching vector
vector<shared_ptr<Course>> GraduateStudent::GetCurrentCourses(string Action)
{
    if (Action == "TAKING")
        return CoursesEnrolled;
    else if (Action == "TEACHING")
        return CoursesTeaching;
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return vector<shared_ptr<Course>>();
    }
}

// Override GetPreviousCourses()
// Action is to get courses in CourseTaken or CoursesHasTaught
// Return CoursesTaken / CoursesHasTaught vector
vector<shared_ptr<Course>> GraduateStudent::GetPreviousCourses(string Action)
{
    if (Action == "TAKEN")
        return CoursesTaken;
    else if (Action == "TAUGHT")
        return CoursesHasTaught;
    else
    {
        LoggerSingleton::GetInstance().AddMessage("Action " + Action + " not allowed for " + this->GetId());
        return vector<shared_ptr<Course>>();
    }
}

// Getters and Setters
string GraduateStudent::GetId()
{
    return StudentId;
}

void GraduateStudent::SetId(string GraduateStudentId)
{
    StudentId = GraduateStudentId;
}

string GraduateStudent::GetPersonType()
{
    return "GRADUATE";
}
