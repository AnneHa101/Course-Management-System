#include "PersonFactory.h"
#include "LoggerSingleton.h"

class School
{
protected:
    vector<shared_ptr<Person>> Persons;
    vector<pair<shared_ptr<Course>, pair<shared_ptr<Person>, vector<shared_ptr<Person>>>>> Courses;
    vector<pair<shared_ptr<Course>, pair<shared_ptr<Person>, vector<shared_ptr<Person>>>>> PastCourses;

public:
    // Constructor
    School();

    // Destructor
    ~School();

    // ADD COURSES - AddPrerequisites()
    // Add a new course to the system
    // (Courses can be created without instructor or students)
    // (The course must not be the prerequisite of itself)
    // (Graduate courses cannot be the prerequisite for an undergraduate courses)
    // (Cannot add course that does not exist in the system)
    // If the course already exists, throw an exception
    void AddCourse(string CourseId, string CourseName, bool GraduateLevel);
    void AddPrerequisite(string CourseId, string RequiredCourse);

    // ADD STUDENTS
    // Add a new student who must be enrolled in 1 course to the system
    // (StudentId must be unique)
    // (All students must be enrolled in at least 1 class and at their level)
    // If the student already exists, throw an exception
    // If the student does not exist but enrolls an unqualified course or an available course, throw an exception
    void AddStudent(string StudentId, string CourseId, bool isGraduate);

    // ASSIGN STUDENTS TO COURSES - AddPersonToCourse()
    // Assign an existing student to an available course
    // (Courses have at most 40 students)
    // (All classes enrolled must be different from courses they have already taken)
    // (Graduate students cannot enroll in classes they are teaching)
    // If the student does not exist, throw an exception
    // If the course does not exist, throw an exception
    // If the course is not at his level, throw an exception
    // If the number of students enrolled in the course exceeds 40, throw an exception
    bool AssignStudentToCourse(string StudentId, string CourseId);

    // ADD FACULTIES
    // Add a new faculty to the system
    // If the faculty already exists, throw an exception
    void AddFaculty(string FacultyId);

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
    void AssignInstructorToCourse(string InstructorId, string CourseId);

    // REMOVE STUDENTS FROM COURSES
    // Remove an existing student from an available course
    // (Update the course's SeatAvailability and Status if needed)
    // (If a student is no longer enrolled in any class after removal, he is deleted too)
    // If the student does not exist, throw an exception
    // If the course does not exist, throw an exception
    // If the student does not in the course list, throw an exception
    void RemoveStudentFromCourse(string StudentId, string CourseId);

    // REMOVE INSTRUCTORS FROM COURSES
    // Remove an existing instructor from an available course
    // If the instructor does not exist, throw an exception
    // If the course does not exist, throw an exception
    // If the instructor is not assigned to the course, throw an exception
    void RemoveInstructorFromCourse(string InstructorId, string CourseId);

    // REMOVE STUDENTS
    // Remove an existing student from the system
    // (The student will be removed from all the courses that he is enrolled in)
    // (The removal does not affect the previous courses they have already taken)
    // If the student does not exist, throw an exception
    void RemoveStudent(string StudentId);

    // REMOVE COURSES
    // Remove an existing course from the system
    // (The course will be removed from all the students who have already enrolled in it)
    // (If a student is no longer enrolled in any class after removal, he is deleted too)
    // (If the course is the prerequisite of another course, it is removed from that course's prerequisite as well)
    // If the course does not exist, throw an exception
    void RemoveCourse(string CourseId);

    // PRINT ALL COURSES A STUDENT IS TAKING
    // Each student is taking at least 1 course
    // If the student does not exist, throw an exception
    void PrintCoursesTaking(string StudentId);

    // PRINT ALL STUDENTS IN A COURSE
    // If the course does not exist, throw an exception
    void PrintStudentsInCourse(string CourseId);

    // PRINT ALL COURSES AN INSTRUCTOR IS TEACHING
    // If the instructor does not exist, throw an exception
    void PrintCoursesTeaching(string InstructorId);

    // PRINT ALL COURSES A STUDENT HAS TAKEN
    // If the student does not exist, throw an exception
    void PrintCoursesTaken(string StudentId);

    // PRINT ALL COURSES AN INSTRUCTOR HAS TAUGHT
    // If the instructor does not exist, throw an exception
    void PrintCoursesHasTaught(string InstructorId);

    // PRINT ALL COURSES CURRENTLY BEING TAUGHT
    // Print to the screen or a file
    // If the course does not exist, throw an exception
    void PrintCoursesAvailableDetails(string CourseId);

    // DELETE THE ENTIRE UNIVERSITY COURSE MANAGEMENT SYSTEM
    // Prompt a notification before the deletion
    void DeleteSystem();
};