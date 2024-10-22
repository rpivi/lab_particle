
#include "Particle.hpp"
#include<iostream>
#include<cmath>

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
void Particle::setIndex(int Index) {
  if(Index <= fMaxNumParticleType){
  fIndex = Index;}}

void Particle::setIndex(char* Name) {
    fIndex = Particle::FindParticle(Name);
  }

void Particle::PrintParticleType()const {
   for(auto const& p: fParticleType){
      p->Print();
      std::cout<<"/n";
    }
}

void Particle::PrintParticle() const {
  std::cout<<"Index: "<<fIndex<<"/n";
  std::cout<<"Name: "<<*(fParticleType[fIndex]->getName())<<"/n";
  std::cout<<"Momentum x:"<< fP[0]<<"/n Momentum y:"<<fP[1]<<"/n Momentum z:"<<fP[2]<<"/n";
}

double Particle::NormP() const{
  double NormP = std::sqrt(std::pow(this->getPx(),2)+std::pow(this->getPy(),2)+std::pow(this->getPz(),2));
  return NormP;
}

double Particle::TotalEnergy() const{
  double E = std::sqrt(std::pow(this->getMass(), 2) + std::pow(this->NormP(),2));
  return E;
}

double Particle::InvMass(Particle &p){
  double InvM = std::sqrt(std::pow(this->TotalEnergy()+p.TotalEnergy(),2)-std::pow(this->NormP()+p.NormP(),2));
  return InvM;
}

void setP(double px, double py, double pz){
  Particle::fP ={ px, py, pz};
}