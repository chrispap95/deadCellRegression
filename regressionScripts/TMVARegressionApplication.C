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
    Float_t sameLayer, nextLayer, previousLayer, pnCells, sum1, sum2, sum3, sum4, sum
    reader->AddVariable( "layer", &layer);
    reader->AddVariable( "n1", &n1);
    reader->AddVariable( "n2", &n2);
    reader->AddVariable( "n3", &n3);
    reader->AddVariable( "n4", &n4);
    reader->AddVariable( "n5", &n5);
    reader->AddVariable( "n6", &n6);
    reader->AddVariable( "nup", &nup);
    reader->AddVariable( "ndown", &ndown);
    reader->AddVariable( "un1", &un1);
    reader->AddVariable( "un2", &un2);
    reader->AddVariable( "un3", &un3);
    reader->AddVariable( "un4", &un4);
    reader->AddVariable( "un5", &un5);
    reader->AddVariable( "un6", &un6);
    reader->AddVariable( "dn1", &dn1);
    reader->AddVariable( "dn2", &dn2);
    reader->AddVariable( "dn3", &dn3);
    reader->AddVariable( "dn4", &dn4);
    reader->AddVariable( "dn5", &dn5);
    reader->AddVariable( "dn6", &dn6);

    // Spectator variables declared in the training have to be added to the reader, too
    //Float_t spec1,spec2;
    //reader->AddSpectator( "spec1:=var1*2",  &spec1 );
    //reader->AddSpectator( "spec2:=var1*3",  &spec2 );

    // --- Book the MVA methods

    TString dir    = "dataset/weights/";
    TString prefix = "TMVAReg_6Layers_340K_90range";

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
    TString fname = "data/converted_training_sample_full_8samples.root";
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
    theTree->SetBranchAddress( "layer", &layer );
    theTree->SetBranchAddress( "n1", &n1 );
    theTree->SetBranchAddress( "n2", &n2 );
    theTree->SetBranchAddress( "n3", &n3 );
    theTree->SetBranchAddress( "n4", &n4 );
    theTree->SetBranchAddress( "n5", &n5 );
    theTree->SetBranchAddress( "n6", &n6 );
    theTree->SetBranchAddress( "nup", &nup );
    theTree->SetBranchAddress( "ndown", &ndown );
    theTree->SetBranchAddress( "dead", &dead);
    theTree->SetBranchAddress( "un1", &un1 );
    theTree->SetBranchAddress( "un2", &un2 );
    theTree->SetBranchAddress( "un3", &un3 );
    theTree->SetBranchAddress( "un4", &un4 );
    theTree->SetBranchAddress( "un5", &un5 );
    theTree->SetBranchAddress( "un6", &un6 );
    theTree->SetBranchAddress( "dn1", &dn1 );
    theTree->SetBranchAddress( "dn2", &dn2 );
    theTree->SetBranchAddress( "dn3", &dn3 );
    theTree->SetBranchAddress( "dn4", &dn4 );
    theTree->SetBranchAddress( "dn5", &dn5 );
    theTree->SetBranchAddress( "dn6", &dn6 );
    theTree->SetBranchAddress( "pnCells", &pnCells );
    theTree->SetBranchAddress( "previousLayer", &previousLayer );
    theTree->SetBranchAddress( "nextLayer", &nextLayer );
    theTree->SetBranchAddress( "sameLayer", &sameLayer );
    theTree->SetBranchAddress( "sum1", &sum1 );
    theTree->SetBranchAddress( "sum2", &sum2 );
    theTree->SetBranchAddress( "sum3", &sum3 );
    theTree->SetBranchAddress( "sum4", &sum4 );
    theTree->SetBranchAddress( "sum5", &sum5 );
    theTree->SetBranchAddress( "sum6", &sum6 );


    std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();

    TH2F* hscatter = new TH2F("hscatter", "Regression vs true rechit;Rechit_{true} [GeV];Rechit_{ML} [GeV]", 100, 0, 0.4, 100, 0, 0.4);
    TH2F* hscatter2 = new TH2F("hscatter2", "ML bias;Rechit_{true} [GeV]; Rechit_{true}-Rechit_{ML} [GeV]", 100, 0, 0.4, 100, -3, 1);
    TH2F* hscatter3 = new TH2F("hscatter3", "Averege bias;Rechit_{true} [GeV]; Rechit_{true}-Rechit_{ML} [GeV]", 100, 0, 0.4, 100, -9, 1);
    TH2F* hscatter2r = new TH2F("hscatter2r", "ML bias vs Rechit_{ML};Rechit_{ML} [GeV]; Rechit_{true}-Rechit_{ML} [GeV]", 200, 0, 0.4, 200, -0.6, 0.6);
    TH2F* hscatter3r = new TH2F("hscatter3r", "Average bias vs Rechit_{av};Rechit_{av} [GeV]; Rechit_{true}-Rechit_{av} [GeV]", 200, 0, 0.4, 200, -0.6, 0.6);

    float avdevquad = 0;
    int n = 0;
    for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

        if (ievt%50000 == 0) {
            std::cout << "--- ... Processing event: " << ievt << std::endl;
        }

        theTree->GetEntry(ievt);

        // Retrieve the MVA target values (regression outputs) and fill into histograms
        // NOTE: EvaluateRegression(..) returns a vector for multi-target regression

        for (Int_t ih=0; ih<nhists; ih++) {
            if(dead < 0.4){
                TString title = hists[ih]->GetTitle();
                Float_t val = (reader->EvaluateRegression( title ))[0];
                Float_t avrechit = nup/2+ndown/2;
                hists[ih]->Fill(val);
                hscatter->Fill(dead,val);
                avdevquad += pow(dead-val,2);
                n++;
                hscatter2->Fill(dead,(dead-val));
                hscatter3->Fill(dead,(dead-avrechit));
                hscatter2r->Fill(val,(dead-val));
                hscatter3r->Fill(avrechit,(dead-avrechit));
            }
        }
    }
    sw.Stop();
    std::cout << "--- End of event loop: "; sw.Print();

    std::cout << "average quadratic deviation = " << sqrt(avdevquad/(float)n) << std::endl;

    TProfile* pf1 = hscatter2->ProfileX();
    TProfile* pf2 = hscatter3->ProfileX();

    // --- Write histograms
    gStyle->SetOptStat(0);
    TCanvas* c1 = new TCanvas("c1","c1",1);
    c1->SetLogz();
    hscatter->Draw("colz");
    TCanvas* c2 = new TCanvas("c2","c2",1);
    c2->SetLogz();
    hscatter2->Draw("colz");
    gPad->SetTickx();
    gPad->SetTicky();
    TLine* l = new TLine(0,0,0.4,0);
    hscatter2->GetXaxis()->SetTitleOffset(1.2);
    TLatex ltx;
    l->Draw();
    ltx.SetTextSize(0.035);
    ltx.DrawLatex(0.003,hscatter2->GetYaxis()->GetXmax()*1.05,
    "HGCAL#scale[0.8]{#font[12]{Internal}}");


    TFile *target  = new TFile( "TMVARegApp.root","RECREATE" );
    for (Int_t ih=0; ih<nhists; ih++) hists[ih]->Write();
    hscatter->Write();
    hscatter2->Write();
    hscatter3->Write();
    hscatter2r->Write();
    hscatter3r->Write();
    pf1->Write();
    pf2->Write();
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
