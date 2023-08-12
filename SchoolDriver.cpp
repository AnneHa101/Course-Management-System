#include "School.h"

int main()
{
    School UW;

    // ADD COURSES - AddPrerequisites()
    UW.AddCourse("CSS342", "Data Structures and Algorithms 1", false);
    UW.AddCourse("CSS343", "Data Structures and Algorithms 2", false);
    UW.AddCourse("CSS497", "CSSE Capstone", false);
    UW.AddCourse("CSS517", "Information Assurance and Cybersecurity", true);
    UW.AddCourse("CSS586", "Deep Learning and Artificial Intelligence", true);
    UW.AddCourse("CSS430", "Operating System", false);
    UW.AddCourse("CSS342", "Data Structures and Algorithms 1", false); // Cannot add a course that already exists
    UW.AddPrerequisite("CSS343", "CSS342");
    UW.AddPrerequisite("CSS586", "CSS517");
    UW.AddPrerequisite("CSS497", "CSS342");
    UW.AddPrerequisite("CSS497", "CSS343");
    UW.AddPrerequisite("CSS497", "CSS497"); // Courses cannot be the prerequisite of itself
    UW.AddPrerequisite("CSS497", "CSS517"); // Graduate courses cannot be the prerequisite of undergraduate courses

    // ADD STUDENTS
    UW.AddStudent("anne101", "CSS343", false);
    UW.AddStudent("bob202", "CSS586", true);
    UW.AddStudent("chloe303", "CSS342", false);
    UW.AddStudent("dave404", "CSS517", true);
    UW.AddStudent("dave404", "CSS517", true);  // Cannot add a student that already exists
    UW.AddStudent("emma505", "CSS586", false); // Cannot add a new student who enrolls a wrong class
    UW.AddStudent("emma505", "CSS310", false); // Cannot add a new student who enrolls a non-existing class

    // ASSIGN STUDENTS TO COURSES
    UW.AssignStudentToCourse("anne101", "CSS342");
    UW.AssignStudentToCourse("bob202", "CSS343"); // Cannot assign a student to an unqualified course
    UW.AssignStudentToCourse("bob202", "CSS350"); // Cannot assign a student to a course that does not exist
    UW.AssignStudentToCourse("bob202", "CSS517");
    UW.AssignStudentToCourse("chloe303", "CSS343");
    UW.AssignStudentToCourse("michael909", "CSS342"); // Cannot assign a student that does not exist

    // ADD FACULTIES
    UW.AddFaculty("brent_lagesse");
    UW.AddFaculty("kevin_sung");
    UW.AddFaculty("pisan");

    // ASSIGN INSTRUCTORS TO COURSES
    UW.AssignInstructorToCourse("brent_lagesse", "CSS342");
    UW.AssignInstructorToCourse("kevin_sung", "CSS343");
    UW.AssignInstructorToCourse("brent_lagesse", "CSS586");
    UW.AssignInstructorToCourse("brent_lagesse", "CSS497");
    UW.AssignInstructorToCourse("brent_lagesse", "CSS517"); // Cannot assign the same instructor to more than 3 classes
    UW.AssignInstructorToCourse("pisan", "CSS517");
    UW.AssignInstructorToCourse("bob202", "CSS342");
    UW.AssignInstructorToCourse("bob202", "CSS517"); // Cannot assign the graduate student to the course he is enrolled in

    // REMOVE STUDENTS FROM COURSES
    UW.RemoveStudentFromCourse("anne101", "CSS342");
    UW.RemoveStudentFromCourse("michael909", "CSS342"); // Cannot remove a student that does not exist
    UW.RemoveStudentFromCourse("bob202", "CSS360");     // Cannot remove a course that does not exist
    UW.RemoveStudentFromCourse("bob202", "CSS497");     // Cannot remove a student from course that he did not enroll in
    UW.AssignStudentToCourse("anne101", "CSS342");

    // REMOVE INSTRUCTOR FROM COURSES
    UW.RemoveInstructorFromCourse("brent_lagesse", "CSS586");
    UW.RemoveInstructorFromCourse("pisan", "CSS342"); // Cannot remove an instructor from the course that he is not teaching
    UW.AssignInstructorToCourse("brent_lagesse", "CSS586");

    // REMOVE STUDENTS
    UW.RemoveStudent("anne101");
    UW.RemoveStudent("emma250"); // Cannot remove a student that does not exist
    UW.AddStudent("anne101", "CSS343", false);
    UW.AssignStudentToCourse("anne101", "CSS342");

    // REMOVE COURSES
    UW.RemoveCourse("CSS430");
    UW.RemoveCourse("CSS360"); // Cannot remove a course that does not exist

    // PRINT ALL COURSES A STUDENT IS TAKING
    UW.PrintCoursesTaking("anne101");

    // PRINT ALL STUDENTS IN A COURSE
    UW.PrintStudentsInCourse("CSS342");

    // PRINT ALL COURSES AN INSTRUCTOR IS TEACHING
    UW.PrintCoursesTeaching("brent_lagesse");

    // PRINT ALL COURSES A STUDENT HAS TAKEN
    UW.PrintCoursesTaken("anne101");

    // PRINT ALL COURSES AN INSTRUCTOR HAS TAUGHT
    UW.PrintCoursesHasTaught("brent_lagesse");

    // PRINT ALL COURSES CURRENTLY BEING TAUGHT
    UW.PrintCoursesAvailableDetails("CSS342");

    // DELETE THE ENTIRE UNIVERSITY COURSE MANAGEMENT SYSTEM
    UW.DeleteSystem();

    LoggerSingleton::GetInstance().WriteLogFile();

    return 0;
}