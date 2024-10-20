#include "ParticleType.hpp"

ParticleType::ParticleType(char* const Name, double const Mass, int const Charge)
: fName{Name}, fMass{Mass} , fCharge{Charge} {}; 

// To see if error from getting the private members
void ParticleType::Print() const {
    std::cout<< "Charge is: "<<fCharge << "\n " << "Mass is: "<<fMass << "\n " << "Name is: " << *fName << "\n" ;
};

