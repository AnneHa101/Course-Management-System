#include "School.h"

// Constructor
School::School()
{
    Persons.clear();
    Courses.clear();
}

// Destructor
School::~School()
{
    Persons.clear();
    Courses.clear();
}

// ADD COURSES
// Add a new course to the system
// (Courses can be created without instructor or students)
// (The course must not be the prerequisite of itself)
// (Graduate courses cannot be the prerequisite for an undergraduate courses)
// If the course already exists, throw an exception
void School::AddCourse(string CourseId, string CourseName, bool GraduateLevel)
{
    // Make sure Course to add is unique
    for (int i = 0; i < Courses.size(); i++)
    {
        if (CourseId == Courses[i].first->GetCourseId())
        {
            LoggerSingleton::GetInstance().AddMessage("Failed to ADD Course " + CourseId + " (ERROR: " + CourseId + " already exists)");
            return;
        }
    }

    shared_ptr<Course> NewCourse = make_shared<Course>(CourseId, CourseName, GraduateLevel);
    vector<shared_ptr<Person>> StudentList;
    StudentList.clear();
    Courses.push_back(make_pair(NewCourse, make_pair(nullptr, StudentList)));
    LoggerSingleton::GetInstance().AddMessage("Successfully ADD Course " + CourseId);
}

void School::AddPrerequisite(string CourseId, string RequiredCourse)
{
    if (CourseId == RequiredCourse)
    {
        LoggerSingleton::GetInstance().AddMessage("Failed to ADD Course " + RequiredCourse + " as Prerequisite of " + CourseId + " (ERROR: Course must not be prerequisite of itself)");
        return;
    }

    shared_ptr<Course> CourseToAdd;
    shared_ptr<Course> PrerequisiteCourse;

    for (int i = 0; i < Courses.size(); i++)
    {
        if (CourseToAdd != nullptr && PrerequisiteCourse != nullptr)
        {
            CourseToAdd->AddPrerequisite(PrerequisiteCourse);
            return;
        }
        if (CourseId == Courses[i].first->GetCourseId())
            CourseToAdd = Courses[i].first;
        else if (RequiredCourse == Courses[i].first->GetCourseId())
            PrerequisiteCourse = Courses[i].first;
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to ADD Course " + RequiredCourse + " as Prerequisite of " + CourseId + " (ERROR: " + CourseId + " or " + RequiredCourse + " not exist)");
    return;
}

// ADD STUDENTS
// Add a new student who must be enrolled in 1 course to the system
// (StudentId must be unique)
// (All students must be enrolled in at least 1 class and at their level)
// If the student already exists, throw an exception
// If the student does not exist but enrolls an unqualified course or an available course, throw an exception
void School::AddStudent(string StudentId, string CourseId, bool isGraduate)
{
    // Make sure StudentId to add is unique
    for (int i = 0; i < Persons.size(); i++)
    {
        if (StudentId == Persons[i]->GetId())
        {
            LoggerSingleton::GetInstance().AddMessage("Failed to ADD Student " + StudentId + " (ERROR: " + StudentId + " already exists)");
            return;
        }
    }

    PersonFactory NewPerson;
    shared_ptr<Person> NewStudent;
    if (isGraduate == false)
        NewStudent = NewPerson.CreatePerson(PersonType::UNDERGRADUATE, StudentId);
    else
        NewStudent = NewPerson.CreatePerson(PersonType::GRADUATE, StudentId);

    Persons.push_back(NewStudent);
    bool isAdded = AssignStudentToCourse(StudentId, CourseId);
    if (isAdded == true)
        LoggerSingleton::GetInstance().AddMessage("Successfully ADD Student " + StudentId);
    else
    {
        Persons.pop_back();
        LoggerSingleton::GetInstance().AddMessage("Failed to ADD Student " + StudentId);
    }
}

// ASSIGN STUDENTS TO COURSES - AddPersonToCourse()
// Assign an existing student to an available course
// (Courses have at most 40 students)
// (All classes enrolled must be different from courses they have already taken)
// (Graduate students cannot enroll in classes they are teaching)
// If the student does not exist, throw an exception
// If the course does not exist, throw an exception
// If the course is not at his level, throw an exception
// If the number of students enrolled in the course exceeds 40, throw an exception
bool School::AssignStudentToCourse(string StudentId, string CourseId)
{
    // Make sure StudentId exists, Course exists

    for (int i = 0; i < Courses.size(); i++)
    {
        if (Courses[i].first->GetCourseId() == CourseId && Courses[i].first->GetSeatsAvailable() > 0)
        {
            for (int j = 0; j < Persons.size(); j++)
            {
                if (Persons[j]->GetId() == StudentId)
                {
                    if (Persons[j]->GetPersonType() == "UNDERGRADUATE" || Persons[j]->GetPersonType() == "GRADUATE")
                    {
                        // Add Course to Person
                        bool isAdded = Persons[j]->SetCourse(Courses[i].first, "ENROLL");

                        if (isAdded == true)
                        {
                            // Add Person to Course
                            Courses[i].second.second.push_back(Persons[j]);
                            Courses[i].first->DecrementSeatsAvailable();
                            return true;
                        }
                    }
                    else
                    {
                        LoggerSingleton::GetInstance().AddMessage("PersonType: " + Persons[j]->GetPersonType());
                        LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Student " + StudentId + " to " + CourseId + " (ERROR: " + StudentId + " not Undergraduate or Graduate)");
                        return false;
                    }
                }
            }

            LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Student " + StudentId + " to " + CourseId + " (ERROR: " + StudentId + " not exist)");
            return false;
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Student " + StudentId + " to " + CourseId + " (ERROR: " + CourseId + " not exist or unavailable)");
    return false;
}

// ADD FACULTIES
// Add a new faculty to the system
// If the faculty already exists, throw an exception
void School::AddFaculty(string FacultyId)
{
    // Make sure Faculty to add is unique
    for (int i = 0; i < Persons.size(); i++)
    {
        if (FacultyId == Persons[i]->GetId())
        {
            LoggerSingleton::GetInstance().AddMessage("Failed to ADD Faculty " + FacultyId + " (ERROR: " + FacultyId + " already exists)");
            return;
        }
    }

    PersonFactory NewPerson;
    shared_ptr<Person> NewFaculty = NewPerson.CreatePerson(PersonType::FACULTY, FacultyId);
    Persons.push_back(NewFaculty);
    LoggerSingleton::GetInstance().AddMessage("Successfully ADD Faculty " + FacultyId);
}

// ASSIGN INSTRUCTORS TO COURSES
// Assign an existing instructor (a Graduate Student or a Faculty) to an available course
// (Graduate student can teach at most 1 course; Faculty can teach at most 3 courses)
// (Graduate student cannot teach the class that he is enrolled in)
// (Graduate student cannot teach graduate courses)
// (Undergraduate student cannot teach)
// If the instructor does not exist, throw an exception
// If the course does not exist, throw an exception
// If another instructor is already assigned to the course, throw an exception
// If the number of courses the instructor is teaching exceeds maximum number, throw an exception
// If the graduate student is assigned to the class he is enrolled in, throw an exception
// If the graduate student is assigned to a graduate class, throw an exception
void School::AssignInstructorToCourse(string InstructorId, string CourseId)
{
    // Make sure Instructor exists, Course exists
    for (int i = 0; i < Courses.size(); i++)
    {
        if (Courses[i].first->GetCourseId() == CourseId)
        {
            if (Courses[i].second.first != nullptr)
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Instructor " + InstructorId + " to " + CourseId + " (ERROR: " + Courses[i].second.first->GetId() + " is teaching " + CourseId + ")");
                return;
            }

            for (int j = 0; j < Persons.size(); j++)
            {
                if (Persons[j]->GetId() == InstructorId)
                {

                    if (Persons[j]->GetPersonType() == "GRADUATE" || Persons[j]->GetPersonType() == "FACULTY")
                    {
                        // Add Course to Person
                        bool isAdded = Persons[j]->SetCourse(Courses[i].first, "TEACH");

                        if (isAdded)
                            // Add Person to Course
                            Courses[i].second.first = Persons[j];
                    }
                    else
                    {
                        LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Instructor " + InstructorId + " to " + CourseId + " (ERROR: " + InstructorId + " not allowed to teach)");
                        return;
                    }
                }
            }

            LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Instructor " + InstructorId + " to " + CourseId + " (ERROR: " + InstructorId + " not exist)");
            return;
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to ASSIGN Instructor " + InstructorId + " to " + CourseId + " (ERROR: " + CourseId + " not exist)");
    return;
}

// REMOVE STUDENTS FROM COURSES
// Remove an existing student from an available course
// (Update the course's SeatAvailability and Status if needed)
// (If a student is no longer enrolled in any class after removal, he is deleted too)
// If the student does not exist, throw an exception
// If the course does not exist, throw an exception
// If the student does not in the course list, throw an exception
void School::RemoveStudentFromCourse(string StudentId, string CourseId)
{
    // Make sure StudentId exists, Course exists
    for (int i = 0; i < Courses.size(); i++)
    {
        if (Courses[i].first->GetCourseId() == CourseId)
        {

            for (int j = 0; j < Persons.size(); j++)
            {
                if (Persons[j]->GetId() == StudentId)
                {
                    if (Persons[j]->GetPersonType() == "UNDERGRADUATE" || Persons[j]->GetPersonType() == "GRADUATE")
                    {
                        // Remove Course from Person
                        bool isAdded = Persons[j]->RemoveCourseFromPerson(Courses[i].first, "REMOVE_ENROLLED");

                        if (isAdded == true)
                        {
                            // Remove Person from Course
                            for (int k = 0; k < Courses[i].second.second.size(); k++)
                            {
                                if (Courses[i].second.second[k]->GetId() == StudentId)
                                {
                                    Courses[i].second.second.erase(Courses[i].second.second.begin() + k);
                                    Courses[i].first->IncrementSeatsAvailable();
                                    return;
                                }
                            }
                        }
                    }
                    else
                    {
                        LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Student " + StudentId + " from " + CourseId + " (ERROR: " + StudentId + " not Undergraduate or Graduate)");
                        return;
                    }
                }
            }

            LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Student " + StudentId + " from " + CourseId + " (ERROR: " + StudentId + " not exist)");
            return;
        }
        LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Student " + StudentId + " from " + CourseId + " (ERROR: " + CourseId + " not exist)");
        return;
    }
}

// REMOVE INSTRUCTORS FROM COURSES
// Remove an existing instructor from an available course
// If the instructor does not exist, throw an exception
// If the course does not exist, throw an exception
// If the instructor is not assigned to the course, throw an exception
void School::RemoveInstructorFromCourse(string InstructorId, string CourseId)
{
    // Make sure Instructor exists, Course exists
    for (int i = 0; i < Courses.size(); i++)
    {
        if (Courses[i].first->GetCourseId() == CourseId)
        {

            for (int j = 0; j < Persons.size(); j++)
            {
                if (Persons[j]->GetId() == InstructorId)
                {
                    if (Persons[j]->GetPersonType() == "FACULTY" || Persons[j]->GetPersonType() == "GRADUATE")
                    {
                        // Remove Course from Person
                        bool isAdded = Persons[j]->RemoveCourseFromPerson(Courses[i].first, "REMOVE_TEACHING");

                        if (isAdded == true)
                        {
                            // Remove Person from Course
                            Courses[i].second.first = nullptr;
                            return;
                        }
                    }
                    else
                    {
                        LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Instructor " + InstructorId + " from " + CourseId + " (ERROR: " + InstructorId + " not Faculty or Graduate)");
                        return;
                    }
                }
            }

            LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Instructor " + InstructorId + " from " + CourseId + " (ERROR: " + InstructorId + " not exist)");
            return;
        }
        LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Instructor " + InstructorId + " from " + CourseId + " (ERROR: " + CourseId + " not exist)");
        return;
    }
}

// REMOVE STUDENTS
// Remove an existing student from the system
// (The student will be removed from all the courses that he is enrolled in)
// (The removal does not affect the previous courses they have already taken)
// If the student does not exist, throw an exception
void School::RemoveStudent(string StudentId)
{
    // Make sure StudentId exists
    for (int i = 0; i < Persons.size(); i++)
    {
        if (Persons[i]->GetId() == StudentId)
        {
            if (Persons[i]->GetPersonType() == "UNDERGRADUATE" || Persons[i]->GetPersonType() == "GRADUATE")
            {
                // Remove student from all courses he is taking
                vector<shared_ptr<Course>> ClassesTaking = Persons[i]->GetCurrentCourses("TAKING");
                for (int j = 0; j < ClassesTaking.size(); j++)
                    RemoveStudentFromCourse(StudentId, ClassesTaking[j]->GetCourseId());

                // Remove student from the system
                Persons.erase(Persons.begin() + i);
                LoggerSingleton::GetInstance().AddMessage("Successfully REMOVE Student " + StudentId + " from the system");
                return;
            }
            else
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Student " + StudentId + " (ERROR: " + StudentId + " not Undergraduate or Graduate)");
                return;
            }
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Student " + StudentId + " (ERROR: " + StudentId + " not exist)");
    return;
}

// REMOVE COURSES
// Remove an existing course from the system
// (The course will be removed from all the students who have already enrolled in it)
// (If a student is no longer enrolled in any class after removal, he is deleted too)
// (If the course is the prerequisite of another course, it is removed from that course's prerequisite as well)
// If the course does not exist, throw an exception
void School::RemoveCourse(string CourseId)
{
    bool canRemoved = false;

    // Make sure Course exists
    for (int i = 0; i < Courses.size(); i++)
    {
        if (Courses[i].first->GetCourseId() == CourseId)
        {
            vector<shared_ptr<Person>> StudentList = Courses[i].second.second;
            for (int j = 0; j < StudentList.size(); j++)
            {
                // Remove students who are taking only this course from the system
                // Remove course from students who are taking at least this course
                if (StudentList[j]->GetCurrentCourses("TAKING").size() == 1)
                    RemoveStudent(StudentList[j]->GetId());
                else
                    RemoveStudentFromCourse(StudentList[j]->GetId(), CourseId);
            }
            Courses[i].second.second.clear();
            canRemoved = true;
        }

        if (canRemoved)
        {
            vector<shared_ptr<Course>> AllPrerequisites = Courses[i].first->GetPrerequisites();
            for (int k = 0; k < AllPrerequisites.size(); k++)
            {
                if (AllPrerequisites[k]->GetCourseId() == CourseId)
                {
                    AllPrerequisites.erase(AllPrerequisites.begin() + k);
                    break;
                }
            }
            LoggerSingleton::GetInstance().AddMessage("Successfully REMOVE Course " + CourseId);
            return;
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to REMOVE Course " + CourseId + " (ERROR: " + CourseId + " not exist)");
    return;
}

// PRINT ALL COURSES A STUDENT IS TAKING
// Each student is taking at least 1 course
// If the student does not exist, throw an exception
void School::PrintCoursesTaking(string StudentId)
{
    // Make sure StudentId exists
    for (int i = 0; i < Persons.size(); i++)
    {
        if (Persons[i]->GetId() == StudentId)
        {
            if (Persons[i]->GetPersonType() == "UNDERGRADUATE" || Persons[i]->GetPersonType() == "GRADUATE")
            {
                cout << "Courses " << StudentId << " is taking: " << endl;
                vector<shared_ptr<Course>> ClassesTaking = Persons[i]->GetCurrentCourses("TAKING");
                for (int j = 0; j < ClassesTaking.size(); j++)
                    cout << ClassesTaking[j]->GetCourseId() << endl;

                LoggerSingleton::GetInstance().AddMessage("Successfully PRINT Courses Student " + StudentId + " is taking");
                return;
            }
            else
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Courses Student " + StudentId + " is taking (ERROR: " + StudentId + " not Undergraduate or Graduate)");
                return;
            }
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Courses Student " + StudentId + " is taking (ERROR: " + StudentId + " not exist)");
    return;
}

// PRINT ALL STUDENTS IN A COURSE
// If the course does not exist, throw an exception
void School::PrintStudentsInCourse(string CourseId)
{
    // Make sure StudentId exists
    for (int i = 0; i < Courses.size(); i++)
    {
        if (Courses[i].first->GetCourseId() == CourseId)
        {
            cout << "Students in Course " << CourseId << ":" << endl;
            vector<shared_ptr<Person>> StudentList = Courses[i].second.second;
            for (int j = 0; j < StudentList.size(); j++)
                cout << StudentList[j]->GetId() << endl;

            LoggerSingleton::GetInstance().AddMessage("Successfully PRINT Students in Course " + CourseId);
            return;
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Students in Course " + CourseId + " (ERROR: " + CourseId + " not exist)");
    return;
}

// PRINT ALL COURSES AN INSTRUCTOR IS TEACHING
// If the instructor does not exist, throw an exception
void School::PrintCoursesTeaching(string InstructorId)
{
    // Make sure InstructorId exists
    for (int i = 0; i < Persons.size(); i++)
    {
        if (Persons[i]->GetId() == InstructorId)
        {
            if (Persons[i]->GetPersonType() == "FACULTY" || Persons[i]->GetPersonType() == "GRADUATE")
            {
                cout << "Courses " << InstructorId << " is teaching: " << endl;
                vector<shared_ptr<Course>> ClassesTeaching = Persons[i]->GetCurrentCourses("TEACHING");
                for (int j = 0; j < ClassesTeaching.size(); j++)
                    cout << ClassesTeaching[j]->GetCourseId() << endl;

                LoggerSingleton::GetInstance().AddMessage("Successfully PRINT Courses Instructor " + InstructorId + " is teaching");
                return;
            }
            else
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Courses Instructor " + InstructorId + " is taking (ERROR: " + InstructorId + " not Faculty or Graduate)");
                return;
            }
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Courses Student " + InstructorId + " is teaching (ERROR: " + InstructorId + " not exist)");
    return;
}

// PRINT ALL COURSES A STUDENT HAS TAKEN
// If the student does not exist, throw an exception
void School::PrintCoursesTaken(string StudentId)
{
    // Make sure StudentId exists
    for (int i = 0; i < Persons.size(); i++)
    {
        if (Persons[i]->GetId() == StudentId)
        {
            if (Persons[i]->GetPersonType() == "UNDERGRADUATE" || Persons[i]->GetPersonType() == "GRADUATE")
            {
                cout << "Courses " << StudentId << " has taken: " << endl;
                vector<shared_ptr<Course>> ClassesTaken = Persons[i]->GetPreviousCourses("TAKEN");
                for (int j = 0; j < ClassesTaken.size(); j++)
                    cout << ClassesTaken[j]->GetCourseId() << endl;

                LoggerSingleton::GetInstance().AddMessage("Successfully PRINT Courses Student " + StudentId + " has taken");
                return;
            }
            else
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Courses Student " + StudentId + " has taken (ERROR: " + StudentId + " not Undergraduate or Graduate)");
                return;
            }
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Courses Student " + StudentId + " has taken (ERROR: " + StudentId + " not exist)");
    return;
}

// PRINT ALL COURSES AN INSTRUCTOR HAS TAUGHT
// If the instructor does not exist, throw an exception
void School::PrintCoursesHasTaught(string InstructorId)
{
    // Make sure InstructorId exists
    for (int i = 0; i < Persons.size(); i++)
    {
        if (Persons[i]->GetId() == InstructorId)
        {
            if (Persons[i]->GetPersonType() == "FACULTY" || Persons[i]->GetPersonType() == "GRADUATE")
            {
                cout << "Courses " << InstructorId << " has taught: " << endl;
                vector<shared_ptr<Course>> ClassesHasTaught = Persons[i]->GetCurrentCourses("TAUGHT");
                for (int j = 0; j < ClassesHasTaught.size(); j++)
                    cout << ClassesHasTaught[j]->GetCourseId() << endl;

                LoggerSingleton::GetInstance().AddMessage("Successfully PRINT Courses Instructor " + InstructorId + " has taught");
                return;
            }
            else
            {
                LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Courses Instructor " + InstructorId + " has taught (ERROR: " + InstructorId + " not Faculty or Graduate)");
                return;
            }
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Courses Student " + InstructorId + " has taught (ERROR: " + InstructorId + " not exist)");
    return;
}

// PRINT ALL COURSES CURRENTLY BEING TAUGHT
// Print to the screen or a file
// If the course does not exist, throw an exception
void School::PrintCoursesAvailableDetails(string CourseId)
{
    // Make sure StudentId exists
    for (int i = 0; i < Courses.size(); i++)
    {
        if (Courses[i].first->GetCourseId() == CourseId)
        {
            cout << "COURSE " << CourseId << " DETAILS:" << endl;
            cout << "Instructor: " << Courses[i].second.first->GetId() << endl;
            cout << "Students: " << endl;
            vector<shared_ptr<Person>> StudentList = Courses[i].second.second;
            for (int j = 0; j < StudentList.size(); j++)
                cout << StudentList[j]->GetId() << endl;

            cout << "Total Number of Students: " << Courses[i].first->MAX_STUDENTS - Courses[i].first->GetSeatsAvailable() << endl;
            cout << "Number of Seats Available: " << Courses[i].first->GetSeatsAvailable() << endl;

            LoggerSingleton::GetInstance().AddMessage("Successfully PRINT Course " + CourseId + " details");
            return;
        }
    }

    LoggerSingleton::GetInstance().AddMessage("Failed to PRINT Course " + CourseId + " details (ERROR: " + CourseId + " not exist)");
    return;
}

// DELETE THE ENTIRE UNIVERSITY COURSE MANAGEMENT SYSTEM
// Prompt a notification before the deletion
void School::DeleteSystem()
{
    char answer;
    cout << "Are you sure you want to delete the system? (Y/N): ";
    cin >> answer;

    if (toupper(answer) == 'Y')
    {
        this->~School();
        LoggerSingleton::GetInstance().AddMessage("Successfully DELETE System");
        return;
    }
    else if (toupper(answer) == 'N')
        return;
    else
    {
        cout << answer << " is not a valid answer" << endl;
        return;
    }
}
