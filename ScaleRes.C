#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<map>
#include "TH1.h"
#include "TH1F.h"
#include "vector"

void ScaleRes(unsigned imode)
{
  if(imode>2) std::cout<<"invalid imode choice "<<imode<<std::endl;
  if(imode<1) std::cout<<"invalid imode choice "<<imode<<std::endl;

  gStyle->SetOptStat(0);
  gStyle->SetOptFit();

  //set up canvas
  int W = 800;
  int H = 600;
  TString canvName = "resplot";
  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  // references for T, B, L, R
  float T = 0.08*H;
  float B = 0.12*H;
  float L = 0.12*W;
  float R = 0.04*W;

  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);


  //set up legend
  float x1_l = 0.75;
  float y1_l = 0.60;

  float dx_l = 0.60;
  float dy_l = 0.1;
  float x0_l = x1_l-dx_l;
  float y0_l = y1_l-dy_l;
  TLegend *lgd = new TLegend(x0_l,y0_l,x1_l, y1_l);
  lgd->SetBorderSize(0); lgd->SetTextSize(0.04); lgd->SetTextFont(62); lgd->SetFillColor(0);


  //get data
  const unsigned n_f=19;
  double ets[n_f]={5.,10.,15,20.,30,40.,60.,80,100.,140,200,280,400,550,750,1000,1400,2000,2800};
  double scemean[n_f]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
  double scemeane[n_f]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
  double sceres[n_f]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
  double scerese[n_f]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
  double energies[n_f]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
  double energiese[n_f]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};

  double sceeta=1.7;
  double scetheta = 2.*atan(exp(-sceeta));

  std::cout<<"will robinson"<<std::endl;
  for(int i(0);i<19;i++) {
    //if(imode==0) {energies[i]=ets[i]/sin(scetheta);}
    if(0) {energies[i]=ets[i]/sin(scetheta);}
    else {energies[i]=ets[i];}
    std::cout<<" energy is "<<energies[i]<<std::endl;
    std::ostringstream sceName;
    sceName << "data/cmssw/RegressionResults/flatRegressionResult_"
    << ets[i] << "GeV_d010.root";
    std::cout<<"opening "<<sceName.str().c_str()<<std::endl;
    TFile *f1 = new TFile(sceName.str().c_str());
    TH1F *AAA = static_cast<TH1F*>(f1->Get("h_nodead")->Clone());

    if (i == 0) AAA->Rebin(10);
    else if (i == 1) AAA->Rebin(8);
    else if (i == 2) AAA->Rebin(8);
    else if (i == 3) AAA->Rebin(8);
    else if (i == 4) AAA->Rebin(8);
    else if (i == 5) AAA->Rebin(4);
    else if (i == 6) AAA->Rebin(4);
    else if (i == 7) AAA->Rebin();
    else if (i == 8) AAA->Rebin();
    else if (i == 9) AAA->Rebin();
    else if (i == 10) AAA->Rebin();
    else if (i == 11) AAA->Rebin();
    else if (i == 12) AAA->Rebin();
    else if (i == 13) AAA->Rebin();
    else if (i == 14) AAA->Rebin();
    else if (i == 15) AAA->Rebin();
    else if (i == 16) AAA->Rebin();
    else if (i == 17) AAA->Rebin();
    else if (i == 18) AAA->Rebin();

    TFitResultPtr r = AAA->Fit("gaus","S");
    if (i == 0) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 1) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 2) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 3) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 4) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 5) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 6) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 7) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 8) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 9) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 10) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 11) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.6*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 12) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.4*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 13) r = AAA->Fit("gaus","S","",r->Parameter(1)-1.0*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));
    else if (i == 14) r = AAA->Fit("gaus","S","",r->Parameter(1)-3.0*r->Parameter(2),r->Parameter(1)+0.8*r->Parameter(2)); //reverse
    else if (i == 15) r = AAA->Fit("gaus","S","",r->Parameter(1)-3.0*r->Parameter(2),r->Parameter(1)+0.8*r->Parameter(2)); //reverse
    else if (i == 16) r = AAA->Fit("gaus","S","",r->Parameter(1)-3.0*r->Parameter(2),r->Parameter(1)+0.8*r->Parameter(2)); //reverse
    else if (i == 17) r = AAA->Fit("gaus","S","",r->Parameter(1)-3.0*r->Parameter(2),r->Parameter(1)+0.8*r->Parameter(2)); //reverse
    else if (i == 18) r = AAA->Fit("gaus","S","",r->Parameter(1)-3.0*r->Parameter(2),r->Parameter(1)+0.8*r->Parameter(2)); //reverse

    double a0 = r->Parameter(0);
    double a1 = r->Parameter(1);
    double a2 = r->Parameter(2);
    double a0e = r->ParError(0);
    double a1e = r->ParError(1);
    double a2e = r->ParError(2);

    scemean[i]=a1;
    scemeane[i] = a1e;
    sceres[i]=a2/a1;
    //sceres[i]=a2/energies[i];
    scerese[i] = sceres[i]*sqrt(pow(a2e/a2,2)+pow(a1e/a1,2));

    std::cout<<" fit results for "<<energies[i]<<" mean "<<scemean[i]<<"+-"<<scemeane[i]<<" res "<<sceres[i]<<"+-"<<scerese[i]<<std::endl;
  }

  TGraphErrors *gr = new TGraphErrors(19,energies,sceres,energiese,scerese);
  gr->SetTitle("gamma resolution versus energy");
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  TF1  *f2 = new TF1("f2","sqrt(([0]/sqrt(x))**2+([1]/x)**2+([2])**2)");
  f2->SetNpx(1000);
  gr->Fit("f2","q");
  gr->Draw("AP");

  TLatex* t = new TLatex();
  t->SetTextFont(62);
  t->SetTextColor(36);
  t->SetTextSize(0.04);
  if(1) t->DrawLatex(450.,-0.008," energy (GeV)");
  if(imode==1) t->DrawLatex(450.,-0.008," ET (GeV)");
  t->SetTextAngle(90);
  t->DrawLatex(-50.,0.08," width/mean");

  canv->Update();
  //canv->Print(canvName+".pdf",".pdf");
  return;
}
