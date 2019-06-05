{
    // Import tree & variables
    TCanvas* c = new TCanvas("c","c",1);
    gStyle->SetOptStat(0);
    TFile* f = TFile::Open("data/training_sample_100_8samples.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float dead, down, up, layer;
    t->SetBranchAddress("MLlayer",&layer);
    t->SetBranchAddress("MLdead",&dead);
    t->SetBranchAddress("MLndown",&down);
    t->SetBranchAddress("MLnup",&up);

    TH1F* h1 = new TH1F("h1","Integrated rechit spectrum (100 GeV sample);rechit [GeV];"
    "number of rechits/Event",40,0,0.1);
    TH1F* h2 = new TH1F("h2","Rechit spectrum (100 GeV sample); rechit [GeV];"
    "number of rechits/Event",40,0,0.1);
    for (long i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        h2->Fill(dead,1.0/(80.0));
    }

    Double_t norm1 = 1;
    Double_t scale1 = norm1/(h2->Integral());
    h2->Scale(scale1);
    //h2->Scale(1/h2->GetEntries());
    cout << h2->GetEntries() << endl;
    //h2->Draw();

    TFile* f2 = TFile::Open("noise.root");
    TH1F* h_noise = (TH1F*)f2->Get("h_noise");
    TH1F* h_noise2 = new TH1F("h_noise2","noise spectrum; rechit [GeV]; number of rechits/Event/2.5MeV",40,0,0.1);
    for (int i = 0; i <= 50; i++) {
        h_noise2->SetBinContent(i,h_noise->GetBinContent(i)/(9500*1000.0));
    }
    h_noise2->Scale(12);
    h_noise->GetXaxis()->SetTitle("rechit [GeV]");
    h_noise->GetYaxis()->SetTitle("number of rechits/Event/2.5MeV");
    h_noise->GetXaxis()->SetRangeUser(0,0.1);
    cout << h_noise->GetEntries() << endl;
    h_noise2->SetLineColor(kRed);
    h_noise->SetLineColor(kRed);
    Double_t norm2 = 1;
    Double_t scale2 = norm2/(h_noise->Integral());
    h->Scale(scale2);

    THStack* h_stack = new THStack();
    h_stack->Add(h2);
    h_stack->Add(h_noise2);
    h_stack->Draw("hist nostack");
    h_stack->SetTitle("spectrum overlay (normalized); rechit [GeV];number of rechits/Event/2.5MeV");

    TLegend* lg = new TLegend(0.6,0.6,0.8,0.8);
    lg->SetBorderSize(0);
    lg->AddEntry(h2,"signal","l");
    lg->AddEntry(h_noise2,"noise","l");
    lg->Draw();
}
