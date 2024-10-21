#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP


#include "ParticleType.hpp"

class ResonanceType : public ParticleType
{
 private:
  double const fWidth;

 public:
  ResonanceType(char* const Name, double const Mass, int const Charge,
                double const Width);

  double getWidth() const
  {
    return fWidth;
  }

  void Print() const override;
};

#endif