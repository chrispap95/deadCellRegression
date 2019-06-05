{
    // Import tree & variables
    TCanvas* c = new TCanvas("c","c",1);
    gStyle->SetOptStat(0);
    gPad->SetLogz();
    TFile* f = TFile::Open("data/training_sample_full_8samples.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float dead, down, up, layer;
    t->SetBranchAddress("MLlayer",&layer);
    t->SetBranchAddress("MLdead",&dead);
    t->SetBranchAddress("MLndown",&down);
    t->SetBranchAddress("MLnup",&up);

    TH1F* h_layer = new TH1F("h_layer","Rechits on each layer; layer;",28,0,28);
    for (int i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        h_layer->Fill(layer);
    }
    h_layer->Draw();
}
