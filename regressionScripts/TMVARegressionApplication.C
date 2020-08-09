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

void TMVARegressionApplication_dnn(int energy, int deadfrac) {
    //---------------------------------------------------------------
    // This loads the library
    TMVA::Tools::Instance();

    std::cout << std::endl;
    std::cout << "==> Start TMVARegressionApplication" << std::endl;

    // --------------------------------------------------------------------------------------------------
    // --- Create the Reader object

    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

    // Create a set of variables and declare them to the reader
    // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
    Float_t layer, eta, phi, n1, n2, n3, n4, n5, n6, nup, ndown, dead, rechitsum, event;
    Float_t un1, un2, un3, un4, un5, un6;
    Float_t dn1, dn2, dn3, dn4, dn5, dn6;
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

    TString dir    = "trainedNNs/dataset/weights/";
    TString prefix = "cmsswTrain_full_E0to3000_4cores_6M_65nodes_3hl_excludeDead";

    // Book method(s)
    TString methodName = "DNN_CPU method";//it->first + " method";
    TString weightfile = dir + prefix + "_" + "DNN_CPU" + ".weights.xml";
    reader->BookMVA( methodName, weightfile );

    // Book output histograms
    TH1* hists[100];
    Int_t nhists = -1;
    TH1* h = new TH1F( "DNN_CPU","DNN_CPU method", 100, 0.,40.);
    hists[++nhists] = h;
    nhists++;

    // Prepare input tree (this must be replaced by your data source)
    // in this example, there is a toy tree with signal and one with background events
    // we'll later on use only the "signal" events for the test in this example.
    //
    string energy_str = to_string(energy);
    string deadfrac_str = to_string(deadfrac);
    TFile *input(0);
    //TString fname = "data/cmssw/EvaluationSamples/out_E"+energy_str+"Eta1p7_df0"+deadfrac_str+".root";
    TString fname = "data/cmssw/EvaluationSamples_excludeDead2/out_E"+energy_str+"Eta1p7_df0"+deadfrac_str+"_excludeDead.root";
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
    theTree->SetBranchAddress( "dead", &dead);
    theTree->SetBranchAddress( "rechitsum", &rechitsum);
    theTree->SetBranchAddress( "event", &event);

    TString foutname = "data/cmssw/RegressionResults/flatRegressionResult_"+energy_str+"GeV_d0"+deadfrac_str+"0_excludeDead2.root";
    TFile *target  = new TFile( foutname,"RECREATE" );
    TTree* t1 = new TTree("t1","sample");
    Float_t val;
    t1->Branch( "layer", &layer, "layer/F");
    t1->Branch( "n1"   , &n1   , "n1/F"   );
    t1->Branch( "n2"   , &n2   , "n2/F"   );
    t1->Branch( "n3"   , &n3   , "n3/F"   );
    t1->Branch( "n4"   , &n4   , "n4/F"   );
    t1->Branch( "n5"   , &n5   , "n5/F"   );
    t1->Branch( "n6"   , &n6   , "n6/F"   );
    t1->Branch( "nup"  , &nup  , "nup/F"  );
    t1->Branch( "ndown", &ndown, "ndown/F");
    t1->Branch( "un1"  , &un1  , "un1/F"  );
    t1->Branch( "un2"  , &un2  , "un2/F"  );
    t1->Branch( "un3"  , &un3  , "un3/F"  );
    t1->Branch( "un4"  , &un4  , "un4/F"  );
    t1->Branch( "un5"  , &un5  , "un5/F"  );
    t1->Branch( "un6"  , &un6  , "un6/F"  );
    t1->Branch( "dn1"  , &dn1  , "dn1/F"  );
    t1->Branch( "dn2"  , &dn2  , "dn2/F"  );
    t1->Branch( "dn3"  , &dn3  , "dn3/F"  );
    t1->Branch( "dn4"  , &dn4  , "dn4/F"  );
    t1->Branch( "dn5"  , &dn5  , "dn5/F"  );
    t1->Branch( "dn6"  , &dn6  , "dn6/F"  );
    t1->Branch( "dead" , &dead , "dead/F" );
    t1->Branch( "rechitsum", &rechitsum , "rechitsum/F");
    t1->Branch( "event", &event, "event/F");
    t1->Branch( "regression", &val, "regression/F");

    std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();

    TString s_dead_nocorr = deadfrac_str+"% dead";
    TString s_dead_mlcorr = deadfrac_str+"% dead + ML correction";
    TString s_dead_avcorr = deadfrac_str+"% dead + average correction";

    TH1F* h_dead_nocorr = new TH1F("h_dead_nocorr",s_dead_nocorr,1000,0.15*energy,1.5*energy);
    TH1F* h_dead_mlcorr = new TH1F("h_dead_mlcorr",s_dead_mlcorr,1000,0.15*energy,1.5*energy);
    TH1F* h_dead_avcorr = new TH1F("h_dead_avcorr",s_dead_avcorr,1000,0.15*energy,1.5*energy);
    TH1F* h_nodead = new TH1F("h_nodead","0% dead",1000,0.15*energy,1.5*energy);
    TH2F* hscatter2 = new TH2F("hscatter2", "ML bias;recHit_{true} [GeV]; recHit_{ML}-recHit_{true} [GeV]", 100, 0, 40, 100, -30, 20);
    TH2F* hscatter3 = new TH2F("hscatter3", "Averege bias;recHit_{true} [GeV]; recHit_{ML}-recHit_{true} [GeV]", 100, 0, 40, 100, -30, 20);
    TH2F* hscatter2r = new TH2F("hscatter2r", "ML bias vs recHit_{ML};recHit_{ML} [GeV]; recHit_{ML}-recHit_{true} [GeV]", 200, 0, 40, 200, -30, 20);
    TH2F* hscatter3r = new TH2F("hscatter3r", "Average bias vs recHit_{av};recHit_{av} [GeV]; recHit_{av}-recHit_{true} [GeV]", 200, 0, 40, 200, -30, 20);
    TH2F* hvslayer = new TH2F("hvslayer", "ML regression vs layer",28,0,28,100, -30, 20);

    float avdevquad = 0;
    int n = 0;
    int tempEv = 0;
    Float_t tempRechitsum = 0;
    Float_t tempRechitsum0 = 0;
    Float_t tempRechitsum1 = 0;
    Float_t tempRechitsum2 = 0;
    for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
        if (ievt%50000 == 0) {
            std::cout << "--- ... Processing event: " << ievt << std::endl;
        }

        theTree->GetEntry(ievt);

        if (ievt == 0) {
            tempRechitsum = rechitsum;
            tempRechitsum0 = rechitsum;
            tempRechitsum1 = rechitsum;
            tempRechitsum2 = rechitsum;
        }

        // Retrieve the MVA target values (regression outputs) and fill into histograms
        // NOTE: EvaluateRegression(..) returns a vector for multi-target regression
        for (Int_t ih=0; ih<nhists; ih++) {
            TString title = hists[ih]->GetTitle();
            if (layer > -1) {
                val = (reader->EvaluateRegression( title ))[0];
                avdevquad += pow(dead-val,2);
                n++;
            }else {
                val = 0;
            }
            Float_t avrechit = (nup/2+ndown/2);
            hists[ih]->Fill(val);
            hscatter2->Fill(dead,(val-dead));
            hscatter3->Fill(dead,(avrechit-dead));
            hscatter2r->Fill(val,(val-dead));
            hscatter3r->Fill(avrechit,(avrechit-dead));
            hvslayer->Fill(layer,avrechit-dead);
            if(tempEv == event) {
                tempRechitsum+=val;
                tempRechitsum1+=dead;
                tempRechitsum2+=avrechit;
            }else{
                h_dead_nocorr->Fill(tempRechitsum0);
                h_dead_mlcorr->Fill(tempRechitsum);
                h_dead_avcorr->Fill(tempRechitsum2);
                h_nodead->Fill(tempRechitsum1);
                tempRechitsum = rechitsum;
                tempRechitsum0 = rechitsum;
                tempRechitsum1 = rechitsum;
                tempRechitsum2 = rechitsum;
                tempEv = event;
            }
            t1->Fill();
        }
    }
    sw.Stop();
    std::cout << "--- End of event loop: "; sw.Print();

    std::cout << "average quadratic deviation = " << sqrt(avdevquad/(float)n) << std::endl;

    TProfile* pf1 = hscatter2->ProfileX();
    TProfile* pf2 = hscatter3->ProfileX();

    // --- Write histograms
    gStyle->SetOptStat(0);
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
    "HGCAL#scale[0.8]{#font[12]{Simulation work in progress}}");

    for (Int_t ih=0; ih<nhists; ih++) hists[ih]->Write();
    hscatter2->Write();
    hscatter3->Write();
    hscatter2r->Write();
    hscatter3r->Write();
    pf1->Write();
    pf2->Write();
    h_dead_nocorr->Write();
    h_dead_mlcorr->Write();
    h_dead_avcorr->Write();
    h_nodead->Write();
    hvslayer->Write();
    t1->Write();
    target->Close();

    std::cout << "--- Created root file: \"" << target->GetName()
    << "\" containing the MVA output histograms" << std::endl;

    delete reader;

    std::cout << "==> TMVARegressionApplication is done!" << std::endl << std::endl;
}
