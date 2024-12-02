#include "ResonanceType.hpp"
#include <iostream>

void ResonanceType::Print() const
{
  ParticleType::Print();
  std::cout << "Width: " <<fWidth<<"\n";
}

ResonanceType::ResonanceType(char* const Name, double const Mass, int const Charge,
                             double const Width)
    : ParticleType(Name, Mass, Charge)
    , fWidth{Width} {};