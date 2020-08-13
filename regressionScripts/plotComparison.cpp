#include "../RootStyle.cc"

void plotComparison(){
    //set_root_style();
    //set_tdr_style();
    //set_vasu_style();
    setTDRStyle();

    TCanvas* c = new TCanvas("c","canvas",1);
    TFile* f0 = TFile::Open("outputFiles/out00_noner.root");
    TFile* f1 = TFile::Open("outputFiles/out01_noner.root");
    TFile* f2 = TFile::Open("outputFiles/out03_noner.root");
    TFile* f3 = TFile::Open("outputFiles/out05_noner.root");
    TFile* f4 = TFile::Open("outputFiles/out07_noner.root");

    TGraphErrors* gr0 = (TGraphErrors*)f0->Get("Graph;1");
    TGraphErrors* gr1 = (TGraphErrors*)f1->Get("Graph;1");
    TGraphErrors* gr2 = (TGraphErrors*)f2->Get("Graph;1");
    TGraphErrors* gr3 = (TGraphErrors*)f3->Get("Graph;1");
    TGraphErrors* gr4 = (TGraphErrors*)f4->Get("Graph;1");
    TMultiGraph* g = new TMultiGraph();

    gr0->SetTitle("deadfrac = 0%");
    gr1->SetTitle("deadfrac = 1%");
    gr2->SetTitle("deadfrac = 3%");
    gr3->SetTitle("deadfrac = 5%");
    gr4->SetTitle("deadfrac = 7%");

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
    lg->AddEntry(gr1,"deadfrac = 1%","lp");
    lg->AddEntry(gr2,"deadfrac = 3%","lp");
    lg->AddEntry(gr3,"deadfrac = 5%","lp");
    lg->AddEntry(gr4,"deadfrac = 7%","lp");
    lg->Draw();
    gPad->Update();
    //c->Print("presentation/deadfrac_comparison05_noadj.eps")
}
