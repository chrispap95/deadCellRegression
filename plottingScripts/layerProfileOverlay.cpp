{
    TCanvas* c = new TCanvas("c","c",1);
    gStyle->SetOptStat(0);

    TFile* f1 = TFile::Open("data/layerShape_10.root");
    TFile* f2 = TFile::Open("data/layerShape_40.root");
    TFile* f3 = TFile::Open("data/layerShape_100.root");
    TFile* f4 = TFile::Open("data/layerShape_150.root");
    TFile* f5 = TFile::Open("data/layerShape_200.root");

    TH2F* hf1 = (TH2F*)f1->Get("h_layerSum_nodead");
    TH2F* hf2 = (TH2F*)f2->Get("h_layerSum_nodead");
    TH2F* hf3 = (TH2F*)f3->Get("h_layerSum_nodead");
    TH2F* hf4 = (TH2F*)f4->Get("h_layerSum_nodead");
    TH2F* hf5 = (TH2F*)f5->Get("h_layerSum_nodead");

    TH1F* pf1 = (TH1F*)hf1->ProfileX("p10",1,-1,"hs");
    TH1F* pf2 = (TH1F*)hf2->ProfileX("p40",1,-1,"hs");
    TH1F* pf3 = (TH1F*)hf3->ProfileX("p100",1,-1,"hs");
    TH1F* pf4 = (TH1F*)hf4->ProfileX("p150",1,-1,"hs");
    TH1F* pf5 = (TH1F*)hf5->ProfileX("p200",1,-1,"hs");

    pf1->SetTitle("10 GeV; layer; Energy [GeV]");
    pf2->SetTitle("40 GeV; layer; Energy [GeV]");
    pf3->SetTitle("100 GeV; layer; Energy [GeV]");
    pf4->SetTitle("150 GeV; layer; Energy [GeV]");
    pf5->SetTitle("200 GeV; layer; Energy [GeV]");

    double sceeta=1.7;
    double sinscetheta = sin(2.*atan(exp(-sceeta)));

    pf1->Sumw2();
    pf2->Sumw2();
    pf3->Sumw2();
    pf4->Sumw2();
    pf5->Sumw2();

    pf1->Scale(sinscetheta/10.0);
    pf2->Scale(sinscetheta/40.0);
    pf3->Scale(sinscetheta/100.0);
    pf4->Scale(sinscetheta/150.0);
    pf5->Scale(sinscetheta/200.0);

    THStack* hs = new THStack("hs","stack of profiles");

    hs->Add(pf1);
    hs->Add(pf2);
    hs->Add(pf3);
    hs->Add(pf4);
    hs->Add(pf5);
    hs->SetTitle("Average Energy vs Layer (Normalized); layer; Energy fraction");
    hs->Draw("nostack PLC");
    c->BuildLegend();
}
