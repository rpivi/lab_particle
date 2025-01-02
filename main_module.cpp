#include "Particle.hpp"
#include "TMath.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TMatrixD.h"
#include "TFitResult.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TApplication.h"
#include <cmath>

int main_module()
{

  // setting the seed for ghRandom
  gRandom->SetSeed();
  // Recreate the file
  TFile *file = new TFile("Particles.root", "Recreate");

  // the particles type of the main module                Index
  Particle::AddParticleType(const_cast<char *>("pion+"), 0.13957, 1, 0);     // 0
  Particle::AddParticleType(const_cast<char *>("pion-"), 0.13957, -1, 0);    // 1
  Particle::AddParticleType(const_cast<char *>("kaon+"), 0.49367, 1, 0);     // 2
  Particle::AddParticleType(const_cast<char *>("kaon-"), 0.49367, -1, 0);    // 3
  Particle::AddParticleType(const_cast<char *>("proton+"), 0.93827, 1, 0);   // 4
  Particle::AddParticleType(const_cast<char *>("proton-"), 0.93827, -1, 0);  // 5
  Particle::AddParticleType(const_cast<char *>("kaon*"), 0.89166, 0, 0.050); // 6

  // histograms of the events (particletypes, polar angle, azimuthal angle, etc..) and generation of the events
  TH1F *h = new TH1F("h", "histo_particletypes", Particle::getNparticleType(), 0, Particle::getNparticleType());
  TH1F *h1 = new TH1F("h1", "histo_polar_angle", 200, 0, M_PI);
  TH1F *h2 = new TH1F("h2", "histo_azimuthal_angle", 300, 0, 2 * M_PI);
  TH1F *h3 = new TH1F("h3", "histo_impulse", 100, 0., 3.);
  TH1F *h4 = new TH1F("h4", "histo_trasversal_impulse", 100, 0., 3.);
  TH1F *h5 = new TH1F("h5", "histo_energy", 100, 0, 5);
  TH1F *h6 = new TH1F("h6", "histo_invariant_mass", 200, 0., 3.);
  TH1F *h7 = new TH1F("h7", "histo_invariant_mass_discordant", 200, 0., 3.);
  TH1F *h8 = new TH1F("h8", "histo_invariant_mass_concordant", 200, 0., 3.);
  TH1F *h9 = new TH1F("h9", "histo_invariant_mass_disc_pi_ka", 200, 0., 3.);
  TH1F *h10 = new TH1F("h10", "histo_invariant_mass_conc_pi_ka", 200, 0., 3.);
  TH1F *h11 = new TH1F("h11", "histo_invariant_mass_decay", 200, 0., 3.);

  std::array<TH1F *, 12> hist{h, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11};
  
  for (int i = 7; i < 11; ++i) //for the analysis
  {
    hist[i]->Sumw2();
  }

  for (int i = 0; i < 12; ++i) //cosmetic
  {
    hist[i]->SetFillColor(9);
  }

  int const Nsafe = 120;
  int const Nparticles = 100;
  double x = 0; // used for Rndm
  for (int i = 0; i < 100000; ++i) //10e5 event
  {
    int counter_decay{0};
    Particle EventParticles[Nsafe]; // default constructor used here
    for (int j = 0; j < Nparticles; ++j) //100 particles for each event
    {
      double phi = gRandom->Uniform(0., 2. * M_PI);
      double theta = gRandom->Uniform(0., M_PI);
      double modp = gRandom->Exp(1);
      std::array<double, 3> cartesian_momentum{modp * sin(theta) * cos(phi), modp * sin(theta) * sin(phi),
                                               modp * cos(theta)};
      EventParticles[j]
          .setP(cartesian_momentum[0], cartesian_momentum[1], cartesian_momentum[2]);

      h1->Fill(theta);
      h2->Fill(phi);
      h3->Fill(modp);
      h4->Fill(std::sqrt(std::pow(cartesian_momentum[0], 2) + std::pow(cartesian_momentum[1], 2)));

      x = gRandom->Rndm();
      if (x < 0.4)
      {
        h->Fill(0);
        EventParticles[j].setIndex(0);
      }
      else if (x < 0.8)
      {
        h->Fill(1);
        EventParticles[j].setIndex(1);
      }
      else if (x < 0.85)
      {
        h->Fill(2);
        EventParticles[j].setIndex(2);
      }
      else if (x < 0.9)
      {
        h->Fill(3);
        EventParticles[j].setIndex(3);
      }
      else if (x < 0.945)
      {
        h->Fill(4);
        EventParticles[j].setIndex(4);
      }
      else if (x < 0.99)
      {
        h->Fill(5);
        EventParticles[j].setIndex(5);
      }
      else
      {
        h->Fill(6);
        EventParticles[j].setIndex(6);
        double y = gRandom->Rndm();
        if (y < 0.5)
        {
          EventParticles[100 + 2 * counter_decay].setIndex(0);
          EventParticles[101 + 2 * counter_decay].setIndex(3);
          EventParticles[j].Decay2body(EventParticles[100 + 2 * counter_decay], EventParticles[101 + 2 * counter_decay]);
          // filling the histo of the invariant mass of the decay
          h11->Fill(EventParticles[100 + 2 * counter_decay].InvMass(EventParticles[101 + 2 * counter_decay]));
        }
        else
        {
          EventParticles[100 + 2 * counter_decay].setIndex(1);
          EventParticles[101 + 2 * counter_decay].setIndex(2);
          EventParticles[j].Decay2body(EventParticles[100 + 2 * counter_decay], EventParticles[101 + 2 * counter_decay]);
          // filling the histo of invariant mass of the decay
          h11->Fill(EventParticles[100 + 2 * counter_decay].InvMass(EventParticles[101 + 2 * counter_decay]));
        }
        ++counter_decay;
      }
      // filling the histo of the Energy
      h5->Fill(EventParticles[j].TotalEnergy());
    } // out of the generation for of each event

    for (int k = 0; k < Nparticles + 2 * counter_decay; ++k)
    {
      if (EventParticles[k].getIndex() == 6)
      {
        k++;
      }
      for (int j = k + 1; j < Nparticles + 2 * counter_decay; ++j)
      {
        if (EventParticles[j].getIndex() == 6)
        {
          j++;
        }
        // filling the histo of invariant mass (all the particles of the event)
        h6->Fill(EventParticles[k].InvMass(EventParticles[j]));
        if (EventParticles[j].getCharge() * EventParticles[k].getCharge() < 0)
        {
          // filling the histo of invariant mass (discordant)
          h7->Fill(EventParticles[k].InvMass(EventParticles[j]));
        }
        if (EventParticles[j].getCharge() * EventParticles[k].getCharge() > 0)
        {
          // filling the histo of invariant mass (concordant)
          h8->Fill(EventParticles[k].InvMass(EventParticles[j]));
        }
        if ((EventParticles[k].getIndex() == 0 && EventParticles[j].getIndex() == 3) ||
            (EventParticles[k].getIndex() == 1 && EventParticles[j].getIndex() == 2) ||
            (EventParticles[k].getIndex() == 3 && EventParticles[j].getIndex() == 0) ||
            (EventParticles[k].getIndex() == 2 && EventParticles[j].getIndex() == 1))
        {
          // filling the histo of invariant mass (discordant pi ka)
          h9->Fill(EventParticles[k].InvMass(EventParticles[j]));
        }
        if ((EventParticles[k].getIndex() == 0 && EventParticles[j].getIndex() == 2) ||
            (EventParticles[k].getIndex() == 1 && EventParticles[j].getIndex() == 3) ||
            (EventParticles[k].getIndex() == 2 && EventParticles[j].getIndex() == 0) ||
            (EventParticles[k].getIndex() == 3 && EventParticles[j].getIndex() == 1))
        {
          // filling the histo of invariant mass (concordant pi ka)
          h10->Fill(EventParticles[k].InvMass(EventParticles[j]));
        }
      }
    }
  } // out of the for of the 10e5 events
  // Writing all the histograms and than closing the file
  h->Write();
  h1->Write();
  h2->Write();
  h3->Write();
  h4->Write();
  h5->Write();
  h6->Write();
  h7->Write();
  h8->Write();
  h9->Write();
  h10->Write();
  h11->Write();

  file->Close();

  // destruction of the ParticleType
  Particle::ClearParticleTypes();

  return 0;
}
