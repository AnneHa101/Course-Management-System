#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

// STUDENT INTERFACE
class Student : public virtual Person
{
public:
    // Destructor
    virtual ~Student(){};
};
#endif
