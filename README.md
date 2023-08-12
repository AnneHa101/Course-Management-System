For this assignment you will be building a course management system.   You will design it based on SOLID principles and submit your UML diagram(s).  You are expected to research and use Design Patterns. Then you will implement the system and submit it as your final project.

You are given the following informal specification --

1) Your software should allow undergraduates in undergraduate courses and graduate students in graduate courses. 
2) All students must have unique identifiers. 
3) Courses can have prerequisites, but they don't have to. 
4) Both faculty and graduate students can be instructors for courses.
5) Students cannot enroll in a class they have already taken. 
6) Grad students cannot enroll in classes they are teaching. 
7) All students must be enrolled in at least 1 class. 
8) Faculty can teach at most 3 courses at one time. 
9) Grad students can teach at most 1 course. 
10) Courses can have at most 40 students. 

There are some facts that are implied in the informality that need to be made explicit in the formal model since the computer does not understand the semantics of English (hint/example:  a course cannot be its own prerequisite).

You will design and implement this as object oriented code with a set of rules that guarantee the properties listed above.  Additionally, you will need the following functionality --

1) Add/Remove Courses
2) Add/Remove Students
3) Assign or Remove students to/from courses
4) Assign or Remove instructor to/from courses
5) Print all courses a student is taking
6) Print all students in a course
7) Print all courses an instructor is teaching
8) Print all courses a student has taken
9) Print all courses an instructor has taught
10) Print all courses currently being taught, who their instructor is, and which students are in them.  This should have to option to print to the screen or a file.
11) Delete the entire university course management system

12)  You will log all actions to a log file, both successful and failed. 


You will write a driver program that demonstrates all 10 items in the specification (both the positive -- eg, Faculty can teach up to 3 courses, and the negative -- eg, faculty cannot teach 4 courses) and the 11 functions that demonstrate the functionality.

 

 

 

For the DESIGN, turn in your UML diagrams, the .h files for your classes, and pseudocode that demonstrates how the objects will interact (the pseudocode for your driver program).

 

Does the design make use of SOLID design strategies?    (no, 0 points.  barely, 15 points, somewhat, 30 points, almost completely 40 points)
Does the design use design patterns where useful.  (no, 0 points, used, but inappropriately, 15 points, used somewhat appropriately, 30 points.  used well 40 points).

Does the design capture the requirements (no, 0 points, somewhat, 10 points, mostly/completely 20 points)
