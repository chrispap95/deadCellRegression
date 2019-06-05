{
    TCanvas* c = new TCanvas("c","c",1);

    TFile* f1 = TFile::Open("layer_profile5.root");
    TFile* f2 = TFile::Open("layer_profile10.root");
    TFile* f3 = TFile::Open("layer_profile20.root");
    TFile* f4 = TFile::Open("layer_profile30.root");
    TFile* f5 = TFile::Open("layer_profile40.root");
    TFile* f6 = TFile::Open("layer_profile60.root");
    TFile* f7 = TFile::Open("layer_profile100.root");
    TFile* f8 = TFile::Open("layer_profile150.root");
    TFile* f9 = TFile::Open("layer_profile200.root");

    TProfile* pf1 = (TProfile*)f1->Get("h_layer_pfx");
    TProfile* pf2 = (TProfile*)f2->Get("h_layer_pfx");
    TProfile* pf3 = (TProfile*)f3->Get("h_layer_pfx");
    TProfile* pf4 = (TProfile*)f4->Get("h_layer_pfx");
    TProfile* pf5 = (TProfile*)f5->Get("h_layer_pfx");
    TProfile* pf6 = (TProfile*)f6->Get("h_layer_pfx");
    TProfile* pf7 = (TProfile*)f7->Get("h_layer_pfx");
    TProfile* pf8 = (TProfile*)f8->Get("h_layer_pfx");
    TProfile* pf9 = (TProfile*)f9->Get("h_layer_pfx");

    pf1->Scale(1/5.0);
    pf2->Scale(1/10.0);
    pf3->Scale(1/20.0);
    pf4->Scale(1/30.0);
    pf5->Scale(1/40.0);
    pf6->Scale(1/60.0);
    pf7->Scale(1/100.0);
    pf8->Scale(1/150.0);
    pf9->Scale(1/200.0);

    THStack* hs = new THStack();

    //hs->Add(pf1);
    hs->Add(pf2);
    //hs->Add(pf3);
    //hs->Add(pf4);
    hs->Add(pf5);
    //hs->Add(pf6);
    hs->Add(pf7);
    hs->Add(pf8);
    hs->Add(pf9);
    hs->Draw("nostack PLC");

    c->BuildLegend();
}
