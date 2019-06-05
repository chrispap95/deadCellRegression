{
    // Import tree & variables
    TCanvas* c = new TCanvas("c","c",1);
    gStyle->SetOptStat(0);
    TFile* f = TFile::Open("data/training_sample_full_8samples.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float dead, down, up, layer;
    t->SetBranchAddress("MLlayer",&layer);
    t->SetBranchAddress("MLdead",&dead);
    t->SetBranchAddress("MLndown",&down);
    t->SetBranchAddress("MLnup",&up);

    gPad->SetLogz();
    TH2F* h1 = new TH2F("h1","Bias vs Layer;layer;bias [GeV]",28,0,28,50,-9,1);
    for (long i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        if (dead < 0.4) h1->Fill(layer,dead-up/2-down/2);
    }
    h1->Draw("colz");

    gPad->SetTickx();
    gPad->SetTicky();
    TLine* l = new TLine(0,0,0.4,0);
    h1->GetXaxis()->SetTitleOffset(1.2);
    TLatex ltx;
    l->Draw();
    ltx.SetTextSize(0.035);
    ltx.DrawLatex(0+0.003,h1->GetYaxis()->GetXmax()*1.05,
    "HGCAL#scale[0.8]{#font[12]{Internal}}");
}
