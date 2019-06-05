{
    TFile* f = TFile::Open("noise.root");
    TH1F* h1 = (TH1F*)f->Get("h_noise");
    for (int i = 0; i < 800; i++) {
        h1->SetBinContent(i,h1->GetBinContent(i)/1000.0);
    }
    h1->GetXaxis()->SetTitle("rechit [GeV]");
    h1->GetYaxis()->SetTitle("number of rechits/Event/2.5MeV");
    h1->GetXaxis()->SetRangeUser(0,0.1);
    h1->Draw();
}
