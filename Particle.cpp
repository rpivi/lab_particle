#include "Particle.hpp"
#include <cmath>
#include <iostream>
#include <array>

int Particle::fNParticleType{0};

std::array<ParticleType *, 10> Particle::fParticleType;

Particle::Particle(char *Name, std::array<double, 3> P)
    : fIndex{FindParticle(Name)}, fP(P)
{
  if (fIndex == -1)
  {
    std::cout << "No particle with this name" << '\n';
  }
}

void Particle::AddParticleType(char *const Name, double const Mass, int const Charge,
                               double const Width)  //it adds a new ParticleType to the array fParticleType
{
  if ((fNParticleType < fMaxNumParticleType) && (FindParticle(Name) == -1))
  {
    if (Width > 0)
    {
      ResonanceType *r = new ResonanceType(Name, Mass, Charge, Width);
      fParticleType[fNParticleType] = r;
      ++fNParticleType;
    }
    else
    {
      ParticleType *p = new ParticleType(Name, Mass, Charge); // dynamic allocation
      fParticleType[fNParticleType] = p;
      ++fNParticleType;
    }
  }
}

void Particle::setIndex(int Index)  //overloaded
{
  if (Index < fNParticleType)
  {
    fIndex = Index;
  }
  else
  {
    std::cout << "There is no particle in that Index \n";
  }
}

void Particle::setIndex(char *Name) //overloaded
{
  fIndex = Particle::FindParticle(Name);
}

void Particle::PrintParticleType() const
{
  for (int i = 0; i < fNParticleType; ++i)
  {
    fParticleType[i]->Print();
    std::cout << "\n";
  }
}

void Particle::PrintParticle() const
{
  if (fIndex != -1 && fIndex < fNParticleType)
  {
    std::cout << "Index: " << fIndex << "\n";
    std::cout << "Name: " << *(fParticleType[fIndex]->getName()) << "\n";
    std::cout << "Momentum x: " << fP[0] << "\n"
              << "Momentum y: " << fP[1] << "\n"
              << "Momentum z: " << fP[2] << "\n";
  }
  else
  {
    std::cout << "\n The Particle has no data about Mass, Charge, Width!";
  }
}

double Particle::NormP() const
{
  double NormP = std::sqrt(std::pow(this->getPx(), 2) + std::pow(this->getPy(), 2) + std::pow(this->getPz(), 2));
  return NormP;
}

double Particle::TotalEnergy() const
{

  if (fIndex != -1 && fIndex < fNParticleType)
  {
    double E = std::sqrt(std::pow(this->getMass(), 2) + std::pow(this->NormP(), 2));
    return E;
  }
  else
  {
    std::cout << "\n The Particle has no data about Mass, Charge, Width! TotalEnergy return -1";
    return -1;
  }
}

double Particle::InvMass(Particle &p)
{
  if ((fIndex != -1) && (fIndex < fNParticleType) &&  (p.fIndex != -1) && (p.fIndex < fNParticleType))
  {
    double InvM = std::sqrt(std::pow(this->TotalEnergy() + p.TotalEnergy(), 2) - ( std::pow(this->getPz() + p.getPz(), 2)  + std::pow( this->getPy() + p.getPy(), 2) + std::pow(p.getPx() + this->getPx(), 2))); //somma vettoriale non delle norme dei vettori
    return InvM;
  }
  else
  {
    std::cout << "\n The Particle has no data about Mass, Charge, Width! InvMass return -1";
    return -1;
  }
}

void Particle::setP(double px, double py, double pz)
{
  Particle::fP = {px, py, pz};
}

void Particle::ClearParticleTypes()
{
  for (size_t i = 0; i < size_t(fNParticleType); ++i)
  {
    delete fParticleType[i];    // deallocation of memory for each pointer
    fParticleType[i] = nullptr; // sets pointer to nullptr in order to avoid dangling pointers
  }
  fNParticleType = 0; // resets the number of elemts 
}

int Particle::Decay2body(Particle &dau1, Particle &dau2) const
{
  if (getMass() == 0.0)
  {
    std::cout << "Decayment cannot be preformed if mass is zero" << '\n';
    return 1;
  }

  double massMot = getMass();
  double massDau1 = dau1.getMass();
  double massDau2 = dau2.getMass();

  if (fIndex > -1)
  { // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;

    double invnum = 1. / RAND_MAX;
    do
    {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;

    massMot += fParticleType[fIndex]->getWidth() * y1;
  }

  if (massMot < massDau1 + massDau2)
  {
    std::cout << "Decayment cannot be preformed because mass is too low in this channel"
              << '\n';
    return 2;
  }

  double pout =
      sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) * (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) / massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.setP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
            pout * cos(theta));
  dau2.setP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
            -pout * cos(theta));

  double energy = sqrt(std::pow((this->NormP()), 2) + massMot * massMot);

  double bx = fP[0] / energy;
  double by = fP[1] / energy;
  double bz = fP[2] / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}

void Particle::Boost(double bx, double by, double bz)
{
  double energy = TotalEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fP[0] + by * fP[1] + bz * fP[2];
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  fP[0] += gamma2 * bp * bx + gamma * bx * energy;
  fP[1] += gamma2 * bp * by + gamma * by * energy;
  fP[2] += gamma2 * bp * bz + gamma * bz * energy;
}