{
    // Import tree & variables
    TCanvas* c = new TCanvas("c","c",1);
    gStyle->SetOptStat(0);
    gPad->SetLogz();
    TFile* f = TFile::Open("data/training_sample_200_8samples.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float dead, down, up, layer;
    t->SetBranchAddress("MLlayer",&layer);
    t->SetBranchAddress("MLdead",&dead);
    t->SetBranchAddress("MLndown",&down);
    t->SetBranchAddress("MLnup",&up);

    TH2F* h_layer = new TH2F("h_layer","Rechits vs layer (200 GeV); layer; rechit [GeV]",28,0,28,200,0,40);
    for (int i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        h_layer->Fill(layer,dead);
    }
    h_layer->Draw("colz");
    TH1F* prf = (TH1F*)h_layer->ProfileX();
    prf->GetYaxis()->SetTitle("rechit [GeV]");
    prf->Draw();
    TFile* fout = new TFile("layer_profile200.root","RECREATE");
    prf->Write();
    fout->Close();
}
