
#include "Particle.hpp"
int Particle::fNParticleType{0};
std::array<ParticleType*, Particle::fMaxNumParticleType> Particle::fParticleType;
Particle::Particle(char* Name, std::array<double, 3> P)
    : fIndex{FindParticle(Name)}
    , fP(P)
{
  if (fIndex == -1) {
    std::cout << "No particle with this name" << '\n';
  }
}

void Particle::AddParticleType(char* const Name, double const Mass, int const Charge,
                               double const Width = {0.})
{
  auto it = fParticleType.begin();
  if (fNParticleType < fMaxNumParticleType
      && fParticleType.end()
             == std::find_if(it, fParticleType.end(), Name == (*it)->getName())) {
    ++fNParticleType;
    if (Width == 0) {
      fParticleType[fNParticleType] = &ParticleType(Name, Mass, Charge);
    } else {
      fParticleType[fNParticleType] = &ResonanceType(Name, Mass, Charge, Width);
    }
  }
}
void Particle::setIndex(int codex) {fIndex = codex;}
void Particle::setIndex(char* Name) {}
