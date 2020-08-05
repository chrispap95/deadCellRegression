#include "RootStyle.cc"

void deadComparison(){
    //set_root_style();
    //set_tdr_style();
    //set_vasu_style();
    setTDRStyle();

    TCanvas* c = new TCanvas("c","canvas",1);
    TFile* f0 = TFile::Open("outputFiles2/out00_noCorr.root");
    TFile* f1 = TFile::Open("outputFiles2/out05_noCorr.root");
    TFile* f2 = TFile::Open("outputFiles2/out05_aver.root");
    TFile* f3 = TFile::Open("outputFiles2/out05_lSaver.root");
    TFile* f4 = TFile::Open("outputFiles2/out05_MLregr.root");

    TGraphErrors* gr0 = (TGraphErrors*)f0->Get("Graph");
    TGraphErrors* gr1 = (TGraphErrors*)f1->Get("Graph");
    TGraphErrors* gr2 = (TGraphErrors*)f2->Get("Graph");
    TGraphErrors* gr3 = (TGraphErrors*)f3->Get("Graph");
    TGraphErrors* gr4 = (TGraphErrors*)f4->Get("Graph");
    TMultiGraph* g = new TMultiGraph();

    gr0->SetTitle("deadfrac = 0%");
    gr1->SetTitle("deadfrac = 5%");
    gr2->SetTitle("deadfrac = 5% + average corr.");
    gr3->SetTitle("deadfrac = 5% + LS average corr.");
    gr4->SetTitle("deadfrac = 5% + ML regression corr.");

    gr0->SetMarkerColor(kBlack);
    gr1->SetMarkerColor(kGreen);
    gr2->SetMarkerColor(kBlue);
    gr3->SetMarkerColor(kRed);
    gr4->SetMarkerColor(kMagenta);
    gr0->SetLineColor(kBlack);
    gr1->SetLineColor(kGreen);
    gr2->SetLineColor(kBlue);
    gr3->SetLineColor(kRed);
    gr4->SetLineColor(kMagenta);

    gr0->GetFunction("f2")->SetLineColor(kBlack);
    gr1->GetFunction("f2")->SetLineColor(kGreen);
    gr2->GetFunction("f2")->SetLineColor(kBlue);
    gr3->GetFunction("f2")->SetLineColor(kRed);
    gr4->GetFunction("f2")->SetLineColor(kMagenta);

    g->Add(gr0,"P");
    g->Add(gr1,"P");
    g->Add(gr2,"P");
    g->Add(gr3,"P");
    g->Add(gr4,"P");
    g->SetTitle("Resolution vs Energy");
    g->Draw("AP");

    g->GetXaxis()->SetTitle("E [GeV]");
    g->GetYaxis()->SetTitle("#frac{width}{mean}");

    TLegend* lg = new TLegend(0.5,0.5,0.88,0.88);
    lg->SetBorderSize(0);
    lg->AddEntry(gr0,"deadfrac = 0%","lp");
    lg->AddEntry(gr1,"deadfrac = 5%","lp");
    lg->AddEntry(gr2,"deadfrac = 5% + average corr.","lp");
    lg->AddEntry(gr3,"deadfrac = 5% + LS average corr.","lp");
    lg->AddEntry(gr4,"deadfrac = 5% + ML regression corr.","lp");
    lg->Draw();
    gPad->Update();
    //c->Print("presentation/deadfrac_comparison05_noadj.eps")
}
