#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"
#include <array>
#include <cmath>
#include <iostream>

void analysis()
{

  // cosmetic
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);

  // reading from the data of the simulation
  TFile *file = new TFile("Particles.root", "READ");
  TH1F *h = (TH1F *)file->Get("h");
  TH1F *h1 = (TH1F *)file->Get("h1");
  TH1F *h2 = (TH1F *)file->Get("h2");
  TH1F *h3 = (TH1F *)file->Get("h3");
  TH1F *h4 = (TH1F *)file->Get("h4");
  TH1F *h5 = (TH1F *)file->Get("h5");
  TH1F *h6 = (TH1F *)file->Get("h6");
  TH1F *h7 = (TH1F *)file->Get("h7");
  TH1F *h8 = (TH1F *)file->Get("h8");
  TH1F *h9 = (TH1F *)file->Get("h9");
  TH1F *h10 = (TH1F *)file->Get("h10");
  TH1F *h11 = (TH1F *)file->Get("h11");

  // the entris of each histo
  std::array<TH1F *, 12> hist{h, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11};
  for (int i = 0; i < 12; ++i)
  {
    std::cout << "For the " << i << "th histogram the number of entries is: "
              << hist[i]->GetEntries() << "\n";
  }

  // the content of each bin of h, the histo of the partycles types
  for (int i = 1; i < 8; ++i)
  {
    std::cout << "For the " << i << "th bin, of the numbers of particles,the number of entries is:"
              << h->GetBinContent(i) << " " << "+/-" << " "
              << h->GetBinError(i) << '\n';
  }

  // fitting the Azimutal and Polar Angles with a costant fuction

  TF1 *f1 = new TF1("f1", "[0]", 0, M_PI);
  h1->Fit(f1);
  std::cout << "\n First Fit: \n The parameter is:" << f1->GetParameter(0) << " " << "+/-"
            << " " << f1->GetParError(0) << " , the probability is: " << f1->GetProb()
            << " and the reduced chisquare:" << f1->GetChisquare() / f1->GetNDF() << '\n';

  TF1 *f2 = new TF1("f2", "[0]", 2 * M_PI);
  h2->Fit(f2);
  std::cout << "\n Second Fit: \n The parameter is:" << f2->GetParameter(0) << " " << "+/-" << " "
            << f2->GetParError(0) << " , the probability is: " << f2->GetProb()
            << " and the reduced chisquare:" << f2->GetChisquare() / f2->GetNDF() << '\n';

  TCanvas *cAngles = new TCanvas("Angles", "angles");
  cAngles->Divide(1, 2);

  cAngles->cd(1);

  h1->SetTitle("Angolo Polare");
  h1->GetXaxis()->SetTitle("Angolo [Rad]");
  h1->GetYaxis()->SetTitle("Occorrenze");
  h1->SetFillColor(9);
  gPad->SetGrid();
  gPad->SetFrameFillColor(44);
  h1->Draw();
  f1->Draw("same");

  cAngles->cd(2);
  h2->SetTitle("Angolo Azimutale");
  h2->GetXaxis()->SetTitle("Angolo [Rad]");
  h2->GetYaxis()->SetTitle("Occorrenze");
  h2->SetFillColor(9);
  gPad->SetGrid();
  gPad->SetFrameFillColor(44);
  h2->Draw();
  f2->Draw("same");

  cAngles->Update();

  // fitting the Impulse with an exponenitial
  TCanvas *cImpulse = new TCanvas("Impulse", "impulse");

  TF1 *f3 = new TF1("f3", "[0]*exp([1]*x)", 0, 5);
  h3->Fit(f3);
  std::cout << "\n Third Fit: \n The mean is:" << h3->GetMean() << " +/- " << h3->GetMeanError() << "\n the parameter 0:" << f3->GetParameter(0) << " "
            << "\n the parameter 1:" << f3->GetParameter(1) << " "
            << ", the probability is: " << f3->GetProb()
            << " and the reduced chisquare:" << f3->GetChisquare() / f3->GetNDF() << '\n';

  h3->SetTitle("Impulso");
  h3->GetXaxis()->SetTitle("Modulo dell'impulso");
  h3->GetYaxis()->SetTitle("Occorrenze");
  h3->SetFillColor(9);
  gPad->SetGrid();
  gPad->SetFrameFillColor(44);
  h3->Draw();
  f3->Draw("same");
  cImpulse->Update();

  // creating the histograms of the subtractions: discordant & concordant, pion+ kaon- & pion- kaon+
  TH1F *hSub1 = new TH1F("hSub1", "histo_subtraction_1", 200, 0., 3.);
  TH1F *hSub2 = new TH1F("hSub2", "histo_subtraction_2", 200, 0., 3.);

  hSub1->Sumw2();
  hSub2->Sumw2();

  hSub1->Add(h7, h8, 1, -1);
  hSub2->Add(h9, h10, 1, -1);

  // setting the correct number of entris
  hSub1->SetEntries(std::abs(h7->GetEntries() - h8->GetEntries()));
  hSub2->SetEntries(std::abs(h7->GetEntries() - h8->GetEntries()));

  // fitting with a gaussian
  TF1 *f4 = new TF1("f4", "gaus", 0., 3.);
  TF1 *f5 = new TF1("f5", "gaus", 0., 3.);

  hSub1->Fit(f4);
  std::cout << "\n Fourth Fit: \n Mean is " << f4->GetParameter(1) << "+/-" << f4->GetParError(1)
            << " and the width is " << f4->GetParameter(2) << "+/-" << f4->GetParError(2)
            << " , the probability is: " << f4->GetProb()
            << " and chisquare reduced is: " << f4->GetChisquare() / f4->GetNDF() << '\n';

  hSub2->Fit(f5);
  std::cout << "\n Fifth Fit: \n Mean is " << f5->GetParameter(1) << "+/-" << f5->GetParError(1)
            << " and the width is " << f5->GetParameter(2) << "+/-" << f5->GetParError(2)
            << " , the probability is: " << f5->GetProb()
            << " and chisquare reduced is: " << f5->GetChisquare() / f5->GetNDF() << '\n';

  TCanvas *cSubtraction = new TCanvas("Analysis", "analysis");
  cSubtraction->Divide(1, 3);

  cSubtraction->cd(1);
  h11->Fit("gaus", "", "", 0, 3);
  h11->SetTitle("K* Vere");
  h11->GetXaxis()->SetTitle("Massa Invariante");
  h11->GetYaxis()->SetTitle("Occorrenze");
  h11->SetFillColor(9);
  gPad->SetGrid();
  gPad->SetFrameFillColor(44);
  h11->Draw("same");
  cSubtraction->cd(2);
  hSub1->SetTitle("Prima Sottrazione");
  hSub1->GetXaxis()->SetTitle("Massa Invariante");
  hSub1->GetYaxis()->SetTitle("Occorrenze");
  gPad->SetGrid();
  gPad->SetFrameFillColor(44);
  hSub1->SetFillColor(9);
  hSub1->Draw("same");
  cSubtraction->cd(3);
  hSub2->SetTitle("Seconda Sottrazione");
  hSub2->GetXaxis()->SetTitle("Massa Invariante");
  hSub2->GetYaxis()->SetTitle("Occorrenze");
  hSub2->SetFillColor(9);
  gPad->SetGrid();
  gPad->SetFrameFillColor(44);
  hSub2->Draw("same");
  cSubtraction->Update();

  // Printing and closing the file of the data of the simulation
  cSubtraction->Print("Subtraction.gif");
    cAngles->Print("Angles.gif");

  cSubtraction->Print("Subtraction.pdf");
  cAngles->Print("Angles.pdf");
  cImpulse->Print("Impulse.pdf");
  file->Close();
}