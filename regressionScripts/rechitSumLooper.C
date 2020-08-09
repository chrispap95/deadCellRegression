#include "rechitSum.C"

void rechitSumLooper(int df, TString method = "none", bool printCanvases = 1){
  /* Input section
  ** This section needs editing.
  ** energies: put the discrete energies you have in this list
  ** bins: 100 is usually okay but you may optimize it
  ** histRange: rows are for dead fractions,
  **            columns are for the range around the nominal energy value.
  **            You will need to optimize this manually.
  ** fitRange: range around mean to be used for fitting. Also needs manual optimization.
  ** deadfrac: maps a dead fraction number (in %) to the row number
  */
  double energies[] = { 10, 50,100,200,300,500};
  int bins[]        = {100,100,100,100,100,100};
  const int nEnergies = sizeof(energies)/sizeof(energies[0]);
  int histRange[][nEnergies] = {
    {5, 15, 15, 25, 40, 50},
    {5, 15, 20, 40, 70,120},
    {5, 17, 20, 50, 80,100},
    {5, 17, 30, 60,100,150}
  };
  double fitRange[][nEnergies] = {
    {1.6,1.6,1.6,1.2,1.2,1.1},
    {1.6,1.6,1.6,1.6,1.6,1.6},
    {1.6,1.5,1.5,1.2,1.0,1.0},
    {1.6,1.6,1.6,1.6,1.6,1.6}
  };
  std::map<int,int> deadfrac;
  // deadfrac[ dead fraction in % ] = (row index)
  deadfrac[0] = 0;
  deadfrac[1] = 0;
  deadfrac[3] = 1;
  deadfrac[5] = 2;
  deadfrac[7] = 3;

  // Define all regression methods and check for sane input
  TString methods[] = {"none","MLregr","aver","LSaver"};
  int nMeth = sizeof(methods)/sizeof(methods[0]);
  for (int i = 0; i < nMeth; i++) {
    if (method == methods[i]) break;
    if (i == nMeth-1) {
      std::cerr << "Error: Regression method " + method + " not known." << std::endl;;
      return;
    }
  }

  double scemean[nEnergies];
  double scemeane[nEnergies];
  double sceres[nEnergies];
  double scerese[nEnergies];
  double energiese[nEnergies];

  for(int i = 0; i < nEnergies; ++i) {
    scemean[i]   = 0;
    scemeane[i]  = 0;
    sceres[i]    = 0;
    scerese[i]   = 0;
    energiese[i] = 0;
  }

  gStyle->SetOptStat(0);
  gStyle->SetOptFit();

  // Find how many canvases are needed and create them
  int nCanv = nEnergies/4;
  if (nCanv%4 != 0) nCanv++;
  TCanvas* c[nCanv];
  for (int i = 0; i < nCanv; ++i) {
    char canvName[] = {(char)i};
    c[i] = new TCanvas(canvName,canvName,1000,800);
    c[i]->Divide(2,2);
  }

  for(int j = 0; j < nEnergies; ++j){
    if(j%4 == 0) c[j/4]->cd(j%4+1);
    else if(j%4 == 1) c[j/4]->cd(j%4+1);
    else if(j%4 == 2) c[j/4]->cd(j%4+1);
    else if(j%4 == 3) c[j/4]->cd(j%4+1);
    std::vector<double> temp = rechitSum(
      energies[j],
      df,
      histRange[deadfrac[df]][j],
      bins[j],
      fitRange[deadfrac[df]][j],
      method
    );
    // Get mean and width of the peak
    scemean[j]  = temp[1];
    scemeane[j] = temp[4];
    // Calculate resolution: res = mean/width
    // Error propagation for the uncertainty
    sceres[j]   = temp[2]/temp[1];
    scerese[j]  = sceres[j]*sqrt(pow(temp[5]/temp[2],2)+pow(temp[4]/temp[1],2));
    std::cout << " fit results for "  << energies[j]
    << " mean " << scemean[j] << "+-" << scemeane[j]
    << " res "  << sceres[j]  << "+-" << scerese[j] << std::endl;
  }

  // Plot and fit the resolutioin vs energy
  TCanvas* c_res = new TCanvas("c_res","c_res",1);
  TGraphErrors *gr = new TGraphErrors(nEnergies,energies,sceres,energiese,scerese);
  gr->SetTitle("gamma resolution versus energy;E [GeV];width/mean");
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  TF1  *f2 = new TF1("f2","sqrt(([0]/sqrt(x))**2+([1]/x)**2+([2])**2)");
  f2->SetNpx(1000);
  gr->Fit("f2");
  gr->Draw("AP");

  TString outname = "outputFiles/out0"+(TString)to_string(df)+"_"+method+"r.root";
  TFile* out = new TFile(outname,"RECREATE");
  gr->Write();
  out->Close();

  //Print PDFs
  if (printCanvases) {
    TString cname[nCanv];
    for (int i = 0; i < nCanv; i++) {
      c[i]->Print("outputFiles/canvas"+(TString)to_string(i)+"_df0"+(TString)to_string(df)+"_"+method+".pdf");
    }
    TString cnamegr = "outputFiles/resplot_df0"+(TString)to_string(df)+"_"+method+".pdf";
    c_res->Print(cnamegr);
  }
  return;
}
