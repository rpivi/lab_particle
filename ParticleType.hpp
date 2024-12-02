#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iostream>

class ParticleType
{
private:
  char *const fName;
  double const fMass;
  int const fCharge;

public:
  ParticleType(char *const Name, double const Mass, int const Charge);

  inline char *getName() const
  {
    return fName;
  }

  inline double getMass() const
  {
    return fMass;
  }

  inline int getCharge() const
  {
    return fCharge;
  }

  virtual void Print() const;

  inline virtual double getWidth() const
  {
    return 0.;
  };
};

#endif
