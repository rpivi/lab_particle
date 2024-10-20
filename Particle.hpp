#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include <algorithm>
#include <array>

class Particle
{
 private:
  std::array<double, 3> fP{0., 0., 0.};
  //   double fPx{0.};
  //   double fPy{0.};
  //   double fPz{0.};
  int fIndex{0.};
  static int fNParticleType;
  static const int fMaxNumParticleType{10};
  static std::array<ParticleType*, fMaxNumParticleType> fParticleType;
  int FindParticle(char* Name) const
  {
    auto it  = fParticleType.begin();
    auto it1 = std::find(it, fParticleType.end(), Name == (*it)->getName());
    // for (auto it = fParticleType.begin(); it != fParticleType.end(); ++it) {
    //   if ((*it)->getName()==);
    // }
    return (std::distance(it, it1) - 1); // gli indici partono da 0
  }

 public:
  Particle(char* Name, std::array<double, 3> P);
  int getIndex()
  {
    return fIndex;
  }
  static void AddParticleType(char* const Name, double const Mass, int const Charge, double const Width = {0.});
  void setIndex(int codex){};
  void setIndex(char* Name){};

};
#endif