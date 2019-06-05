{
    gStyle->SetOptStat(0);
    //gStyle->SetOptFit(1111);

    TCanvas* c = new TCanvas("c","c",800,600);
    TFile* f = TFile::Open("training_sample_new2.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float dead, up, down, layer;
    t->SetBranchAddress("MLdead",&dead);
    t->SetBranchAddress("MLndown",&down);
    t->SetBranchAddress("MLnup",&up);
    t->SetBranchAddress("MLlayer",&layer);
    TH2F* h1 = new TH2F("h1","MLup vs MLdead;MLdead [GeV];MLup/MLdead",80,2,40,80,0,8);
    TH2F* h2 = new TH2F("h2","MLdown vs MLdead;MLdead [GeV];MLdown/MLdead",80,2,40,80,0,8);

    for (long i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        if (dead > 0 && up > 0 ) {
            h1->Fill(dead,up/dead);
            h2->Fill(dead,down/dead);
        }
    }
    h1->Draw("colz");
    TProfile* pp1 = h1->ProfileX();
    TProfile* pp2 = h2->ProfileX();
    pp2->SetLineColor(kRed);
    pp2->SetMarkerColor(kRed);
    THStack* hs = new THStack("hs","Ratio profiles;MLdead [GeV]");
    hs->Add(pp1);
    hs->Add(pp2);
    //hs->Draw("nostack");
    TLegend* l = new TLegend(0.5,0.7,0.85,0.85);
    l->AddEntry(pp1,"Profile of MLup/MLdead vs MLdead","l");
    l->AddEntry(pp2,"Profile of MLdown/MLdead vs MLdead","l");
    l->SetBorderSize(0);
    //l->Draw()
}
