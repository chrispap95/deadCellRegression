/// \file
/// \ingroup tutorial_tmva
/// \notebook -nodraw
/// This macro provides a simple example on how to use the trained regression MVAs
/// within an analysis module
///
///  - Project   : TMVA - a Root-integrated toolkit for multivariate data analysis
///  - Package   : TMVA
///  - Exectuable: TMVARegressionApplication
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

using namespace TMVA;

void TMVARegressionApplication( TString myMethodList = "" )
{
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDEFoam"]         = 0;
   Use["KNN"]             = 0;
   //
   // --- Linear Discriminant Analysis
   Use["LD"]		        = 0;
   //
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   //
   // --- Neural Network
   Use["MLP"] = 0;
   Use["DNN_CPU"] = 1;
   //
   // --- Support Vector Machine
   Use["SVM"]             = 0;
   //
   // --- Boosted Decision Trees
   Use["BDT"]             = 0;
   Use["BDTG"]            = 0;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVARegressionApplication" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   Float_t layer, eta, phi, n1, n2, n3, n4, n5, n6, nup, ndown, dead;
   Float_t un1, un2, un3, un4, un5, un6;
   Float_t dn1, dn2, dn3, dn4, dn5, dn6;
   reader->AddVariable( "MLlayer", &layer);
   reader->AddVariable( "MLn1", &n1);
   reader->AddVariable( "MLn2", &n2);
   reader->AddVariable( "MLn3", &n3);
   reader->AddVariable( "MLn4", &n4);
   reader->AddVariable( "MLn5", &n5);
   reader->AddVariable( "MLn6", &n6);
   reader->AddVariable( "MLnup", &nup);
   reader->AddVariable( "MLndown", &ndown);
   reader->AddVariable( "MLun1", &un1);
   reader->AddVariable( "MLun2", &un2);
   reader->AddVariable( "MLun3", &un3);
   reader->AddVariable( "MLun4", &un4);
   reader->AddVariable( "MLun5", &un5);
   reader->AddVariable( "MLun6", &un6);
   reader->AddVariable( "MLdn1", &dn1);
   reader->AddVariable( "MLdn2", &dn2);
   reader->AddVariable( "MLdn3", &dn3);
   reader->AddVariable( "MLdn4", &dn4);
   reader->AddVariable( "MLdn5", &dn5);
   reader->AddVariable( "MLdn6", &dn6);

   // Spectator variables declared in the training have to be added to the reader, too
   //Float_t spec1,spec2;
   //reader->AddSpectator( "spec1:=var1*2",  &spec1 );
   //reader->AddSpectator( "spec2:=var1*3",  &spec2 );

   // --- Book the MVA methods

   TString dir    = "dataset/weights/";
   TString prefix = "TMVAReg_6Layers_340K";

   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = it->first + " method";
         TString weightfile = dir + prefix + "_" + TString(it->first) + ".weights.xml";
         reader->BookMVA( methodName, weightfile );
      }
   }

   // Book output histograms
   TH1* hists[100];
   Int_t nhists = -1;
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
     TH1* h = new TH1F( it->first.c_str(), TString(it->first) + " method", 100, 0.,40.);
      if (it->second) hists[++nhists] = h;
   }
   nhists++;

   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //
   TFile *input(0);
   TString fname = "data/training_sample_full_8samples.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }
   //else {
   //   TFile::SetCacheFileDir(".");
   //   input = TFile::Open("http://root.cern.ch/files/tmva_reg_example.root", "CACHEREAD"); // if not: download from ROOT server
   // }
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegressionApp        : Using input file: " << input->GetName() << std::endl;

   // --- Event loop

   // Prepare the tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   TTree* theTree = (TTree*)input->Get("t1");
   std::cout << "--- Select signal sample" << std::endl;
   theTree->SetBranchAddress( "MLlayer", &layer );
   theTree->SetBranchAddress( "MLn1", &n1 );
   theTree->SetBranchAddress( "MLn2", &n2 );
   theTree->SetBranchAddress( "MLn3", &n3 );
   theTree->SetBranchAddress( "MLn4", &n4 );
   theTree->SetBranchAddress( "MLn5", &n5 );
   theTree->SetBranchAddress( "MLn6", &n6 );
   theTree->SetBranchAddress( "MLnup", &nup );
   theTree->SetBranchAddress( "MLndown", &ndown );
   theTree->SetBranchAddress( "MLdead", &dead);
   theTree->SetBranchAddress( "MLun1", &un1 );
   theTree->SetBranchAddress( "MLun2", &un2 );
   theTree->SetBranchAddress( "MLun3", &un3 );
   theTree->SetBranchAddress( "MLun4", &un4 );
   theTree->SetBranchAddress( "MLun5", &un5 );
   theTree->SetBranchAddress( "MLun6", &un6 );
   theTree->SetBranchAddress( "MLdn1", &dn1 );
   theTree->SetBranchAddress( "MLdn2", &dn2 );
   theTree->SetBranchAddress( "MLdn3", &dn3 );
   theTree->SetBranchAddress( "MLdn4", &dn4 );
   theTree->SetBranchAddress( "MLdn5", &dn5 );
   theTree->SetBranchAddress( "MLdn6", &dn6 );


   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();

   TH2F* hscatter = new TH2F("hscatter", "Regression vs true rechit;Rechit_{true} [GeV];Rechit_{ML} [GeV]", 100, 0, 40, 100, 0, 40);
   TH2F* hscatter2 = new TH2F("hscatter2", "ML bias;Rechit_{true} [GeV]; (Rechit_{true}-Rechit_{ML})/Rechit_{true}", 100, 0, 40, 100, -35, 35);

   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

      if (ievt%50000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }

      theTree->GetEntry(ievt);

      // Retrieve the MVA target values (regression outputs) and fill into histograms
      // NOTE: EvaluateRegression(..) returns a vector for multi-target regression

      for (Int_t ih=0; ih<nhists; ih++) {
         TString title = hists[ih]->GetTitle();
         Float_t val = (reader->EvaluateRegression( title ))[0];
         hists[ih]->Fill( val );
         hscatter->Fill(dead,val);
         hscatter2->Fill(dead,(val-dead));
         if(abs(val-dead) > 27){
             std::cout << "\nLarge discrepancy at:" << "\nEntry: " << ievt << ", layer: " << layer
             << "\nin layer: " << dead << ", " << n1 << ", " << n2 << ", " << n3 << ", "
             << n4 << ", " << n5 << ", " << n6
             << "\ndn layer: " << ndown << ", " << dn1 << ", " << dn2 << ", " << dn3 << ", "
             << dn4 << ", " << dn5 << ", " << dn6
             << "\nup layer: " << nup << ", " << un1 << ", " << un2 << ", " << un3 << ", "
             << un4 << ", " << un5 << ", " << un6
             << "\nML prediction: " << val << std::endl;
         }
      }
   }
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   // --- Write histograms
   gStyle->SetOptStat(0);
   TCanvas* c1 = new TCanvas("c1","c1",1);
   c1->SetLogz();
   hscatter->Draw("colz");
   TCanvas* c2 = new TCanvas("c2","c2",1);
   c2->SetLogz();
   hscatter2->Draw("colz");

   TFile *target  = new TFile( "TMVARegApp.root","RECREATE" );
   for (Int_t ih=0; ih<nhists; ih++) hists[ih]->Write();
   hscatter->Write();
   hscatter2->Write();
   target->Close();

   std::cout << "--- Created root file: \"" << target->GetName()
             << "\" containing the MVA output histograms" << std::endl;

   delete reader;

   std::cout << "==> TMVARegressionApplication is done!" << std::endl << std::endl;
}

int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   TMVARegressionApplication(methodList);
   return 0;
}
