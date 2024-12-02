#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include <algorithm>
#include <array>
#include <iterator>
#include <cstring>

class Particle
{
private:
  std::array<double, 3> fP{0., 0., 0.};
  int fIndex{0};
  static int fNParticleType;
  static const int fMaxNumParticleType{10};
  static std::array<ParticleType *, fMaxNumParticleType> fParticleType;

  static int FindParticle(char *Name) //it searches for the index of a specific ParticleType inside fParticleType array
                                      //used in several method
  {
    if (fNParticleType == 0)
    {
      return -1;
    }
    else
    {
      for (int i = 0; i < fNParticleType; ++i)
      {
        if ((fParticleType[i]->getName()) == Name)
        {
          return i;
        }
      }
      return -1;
    }
  }

  void Boost(double bx, double by, double bz); //used in decay2body

public:
  Particle() = default;

  Particle(char *Name, std::array<double, 3> P);

  int getIndex()
  {
    return fIndex;
  }

  static void AddParticleType(char *const Name, double const Mass, int const Charge,
                              double const Width = 0.);

  void setIndex(int codex);
  void setIndex(char *Name);

  void PrintParticleType() const;

  void PrintParticle() const;

  inline double getPx() const
  {
    return fP[0];
  };

  inline double getPy() const
  {
    return fP[1];
  };

  inline double getPz() const
  {
    return fP[2];
  };

  inline double getMass() const
  {
    return fParticleType[fIndex]->getMass();
  };

  inline int getCharge() const
  {
    return fParticleType[fIndex]->getCharge();
  };

  inline static int getNparticleType()
  {
    return fNParticleType;
  }

  double NormP() const;

  double TotalEnergy() const;

  double InvMass(Particle &p);

  void setP(double px, double py, double pz);

  static void ClearParticleTypes();

  int Decay2body(Particle &dau1, Particle &dau2) const;
};
#endif