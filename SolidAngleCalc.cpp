#include <TMath.h>
#include <TGraph.h>
#include <cmath>
#include <iostream>


double r0 = 0.5*(862.801+862.27);
double alpha = 30.1;

double PhiMax(double theta, double chi)
{
  double result = 0, cos_result = 0;
  cos_result = 1/sin(theta)/sin(chi) * (r0/sqrt(alpha*alpha + r0*r0) - cos(theta)*cos(chi));
  result = acos(cos_result);
  return result;
}

void PlotPhiMax(double theta_min, double theta_max, double chi)
{
  TGraph *g = new TGraph();
  g->SetName("PhiMax");
  
  int counter=0;

  for(double theta = theta_min;theta<=theta_max;theta+=0.01)
    {
      g->SetPoint(counter,theta,180./TMath::Pi()*PhiMax(theta*TMath::Pi()/180.,chi*TMath::Pi()/180.));
      counter++;
    }
  g->Draw("AL");
}

void PlotSolidAngle(double theta_min, double theta_max, double chi)
{
  double TotalSolidAngle = 0;

  TGraph *g = new TGraph();
  g->SetName("SolidAngle");

  int counter=0;

  for(double theta=theta_min;theta<=theta_max;theta+=0.01)
    {
      double dOmega = sin(theta*TMath::Pi()/180.)*0.01*TMath::Pi()/180.*2*PhiMax(theta*TMath::Pi()/180.,chi*TMath::Pi()/180.);
      g->SetPoint(counter,theta,dOmega);
      counter++;
      TotalSolidAngle += dOmega;
    }
  cout << "Total Solid Angle: " << TotalSolidAngle*1000. << " msr" << endl;
  g->Draw("AL");
}
