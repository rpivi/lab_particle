#include "ParticleType.hpp"

ParticleType::ParticleType(char* const Name, double const Mass, int const Charge)
    : fName{Name}
    , fMass{Mass}
    , fCharge{Charge} {};

void ParticleType::Print() const
{
  std::cout << "\n Charge is: " << fCharge << "\n " << "Mass is: " << fMass << "\n "
            << "Name is: " << *fName << "\n";
};