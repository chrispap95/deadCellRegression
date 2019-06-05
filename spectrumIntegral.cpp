{
    // Import tree & variables
    TCanvas* c = new TCanvas("c","c",1);
    gStyle->SetOptStat(0);
    gPad->SetLogy();
    TFile* f = TFile::Open("data/training_sample_100_8samples.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float dead, down, up, layer;
    t->SetBranchAddress("MLlayer",&layer);
    t->SetBranchAddress("MLdead",&dead);
    t->SetBranchAddress("MLndown",&down);
    t->SetBranchAddress("MLnup",&up);

    TH1F* h1 = new TH1F("h1","Integrated rechit spectrum (100 GeV sample);rechit [GeV];"
    "number of rechits larger than rechit value/Event",200,0,20);
    for (int n = 1; n <= 200; ++n){
        float bincont = 0;
        for (long i = 0; i < t->GetEntries(); ++i) {
            t->GetEntry(i);
            if (dead > n*0.1) bincont+=1.0/80.0;
        }
        h1->SetBinContent(n,bincont);
    }
    h1->Draw();
}
