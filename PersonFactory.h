#include "UndergraduateStudent.h"
#include "GraduateStudent.h"
#include "Faculty.h"

enum class PersonType
{
    UNDERGRADUATE,
    GRADUATE,
    FACULTY
};

// FACTORY DESIGN PATTERN
// Person Interface for creating object and let subclasses decide which class to instantiate
class PersonFactory
{
public:
    // Constructor
    PersonFactory(){};

    // Destructor
    virtual ~PersonFactory(){};

    // Factory Method
    // Let the Person class defer the instantiation to subclasses
    shared_ptr<Person> CreatePerson(PersonType Type, string Id)
    {
        switch (Type)
        {
        case PersonType::UNDERGRADUATE:
            return make_shared<UndergraduateStudent>(Id);
        case PersonType::GRADUATE:
            return make_shared<GraduateStudent>(Id);
        case PersonType::FACULTY:
            return make_shared<Faculty>(Id);
        default:
            throw invalid_argument("Unknown PersonType");
            return nullptr;
        }
    }
};
