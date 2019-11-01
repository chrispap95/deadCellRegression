{
    gStyle->SetOptStat(0);
    TFile* f = TFile::Open("data/flatTraining.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));

    TH1F* h1 = new TH1F("h1","Rechit spectrum; Energy [GeV]",100,0,600);
    float event, rechitsum;
    t->SetBranchAddress("MLevent",&event);
    t->SetBranchAddress("MLrechitsum",&rechitsum);

    float temp_rechit = 0;
    for (long i = 1; i < t->GetEntries(); ++i) {
        t->GetEntry(i-1);
        if(temp_rechit != rechitsum) h1->Fill(rechitsum);
        temp_rechit = rechitsum;
    }
    h1->Draw();
}
