#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "Person.h"

// INSTRUCTOR INTERFACE
class Instructor : public virtual Person
{
public:
    // Destructor
    virtual ~Instructor(){};
};
#endif