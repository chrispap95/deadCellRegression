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

void TMVARegressionApplication_dnn() {
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
    Float_t sameLayer, nextLayer, previousLayer, pnCells, sum1, sum2, sum3, sum4, sum5, sum6;
    reader->AddVariable( "layer", &layer);
    reader->AddVariable( "previousLayer", &previousLayer);
    reader->AddVariable( "nextLayer", &nextLayer);
    reader->AddVariable( "sameLayer", &sameLayer);
    reader->AddVariable( "pnCells", &pnCells);
    reader->AddVariable( "sum1", &sum1);
    reader->AddVariable( "sum2", &sum2);
    reader->AddVariable( "sum3", &sum3);
    reader->AddVariable( "sum4", &sum4);
    reader->AddVariable( "sum5", &sum5);
    reader->AddVariable( "sum6", &sum6);
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
    TString prefix = "TMVAReg_flat";

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
    string energy_str = "10";
    string deadfrac_str = "5";
    TFile *input(0);
    TString fname = "data/regression_sample_et"+energy_str+"_eta1.7_layerSumMVA_d0"+deadfrac_str+"0.root";
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
    theTree->SetBranchAddress( "MLdead", &dead);
    theTree->SetBranchAddress( "MLrechitsum", &rechitsum);
    theTree->SetBranchAddress( "MLevent", &event);

    std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();

    TH1F* h_dead_nocorr = new TH1F("h_dead_nocorr","1% dead",700,0,700);
    TH1F* h_dead_mlcorr = new TH1F("h_dead_mlcorr","1% dead + ML correction",700,0,700);
    TH1F* h_dead_avcorr = new TH1F("h_dead_avcorr","1% dead + average correction",700,0,700);
    TH1F* h_nodead = new TH1F("h_nodead","0% dead",700,0,700);
    TH2F* hscatter2 = new TH2F("hscatter2", "ML bias;Rechit_{true} [GeV]; Rechit_{true}-Rechit_{ML} [GeV]", 100, 0, 40, 100, -15, 15);
    TH2F* hscatter3 = new TH2F("hscatter3", "Averege bias;Rechit_{true} [GeV]; Rechit_{true}-Rechit_{ML} [GeV]", 100, 0, 40, 100, -15, 15);
    TH2F* hscatter2r = new TH2F("hscatter2r", "ML bias vs Rechit_{ML};Rechit_{ML} [GeV]; Rechit_{true}-Rechit_{ML} [GeV]", 200, 0, 40, 200, -15, 15);
    TH2F* hscatter3r = new TH2F("hscatter3r", "Average bias vs Rechit_{av};Rechit_{av} [GeV]; Rechit_{true}-Rechit_{av} [GeV]", 200, 0, 40, 200, -15, 15);
    TH2F* hvslayer = new TH2F("hvslayer", "ML regression vs layer",28,0,28,100,-15,15);

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
        /*n1=n1/rechitsum;
        n2=n2/rechitsum;
        n3=n3/rechitsum;
        n4=n4/rechitsum;
        n5=n5/rechitsum;
        n6=n6/rechitsum;
        dn1=dn1/rechitsum;
        dn2=dn2/rechitsum;
        dn3=dn3/rechitsum;
        dn4=dn4/rechitsum;
        dn5=dn5/rechitsum;
        dn6=dn6/rechitsum;
        un1=un1/rechitsum;
        un2=un2/rechitsum;
        un3=un3/rechitsum;
        un4=un4/rechitsum;
        un5=un5/rechitsum;
        un6=un6/rechitsum;
        nup=nup/rechitsum;
        ndown=ndown/rechitsum;*/

        previousLayer = dn1 + dn2 + dn3 + dn4 + dn5 + dn6 + ndown;
        nextLayer = un1 + un2 + un3 + un4 + un5 + un6 + nup;
        sameLayer = n1 + n2 + n3 + n4 + n5 + n6;
        pnCells = ndown + nup;
        sum1 = n1 + un1 + dn1;
        sum2 = n2 + un2 + dn2;
        sum3 = n3 + un3 + dn3;
        sum4 = n4 + un4 + dn4;
        sum5 = n5 + un5 + dn5;
        sum6 = n6 + un6 + dn6;

        for (Int_t ih=0; ih<nhists; ih++) {
            TString title = hists[ih]->GetTitle();
            Float_t val = (reader->EvaluateRegression( title ))[0];//*rechitsum;
            Float_t avrechit = (nup/2+ndown/2);//*rechitsum;
            hists[ih]->Fill(val);
            avdevquad += pow(dead-val,2);//*rechitsum,2);
            n++;
            hscatter2->Fill(dead,(dead-val));
            hscatter3->Fill(dead,(dead-avrechit));
            hscatter2r->Fill(val,(dead-val));
            hscatter3r->Fill(avrechit,(dead-avrechit));
            hvslayer->Fill(layer,dead-avrechit);
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
    "HGCAL#scale[0.8]{#font[12]{Internal}}");

    TString foutname = "data/flat_regressionResult_"+energy_str+"GeV_d0"+deadfrac_str+"0.root";
    TFile *target  = new TFile( foutname,"RECREATE" );
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
    target->Close();

    std::cout << "--- Created root file: \"" << target->GetName()
    << "\" containing the MVA output histograms" << std::endl;

    delete reader;

    std::cout << "==> TMVARegressionApplication is done!" << std::endl << std::endl;
}
