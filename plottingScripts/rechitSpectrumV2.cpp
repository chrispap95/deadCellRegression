{
    TFile* f1 = TFile::Open("signal.root");
    TH1F* h_signal = (TH1F*)f1->Get("h_signal");

    TFile* f2 = TFile::Open("noise.root");
    TH1F* h_noise = (TH1F*)f2->Get("h_noise");

    h_signal->Scale(1/1000.0);
    h_noise->Scale(1/1000.0);

    Double_t norm1 = h_signal->GetEntries();
    h_signal->Scale(1/norm1);
    Double_t norm2 = h_noise->GetEntries();
    h_noise->Scale(1/norm2);

    h_noise->SetLineColor(kRed);

    THStack* hs = new THStack();
    hs->Add(h_signal);
    hs->Add(h_noise);
    hs->Draw("hist nostack");
    hs->SetTitle("rechit spectrum normalized;rechit [GeV]");

    TLegend* lg = new TLegend(0.6,0.6,0.8,0.8);
    lg->SetBorderSize(0);
    lg->AddEntry(h_signal,"signal","l");
    lg->AddEntry(h_noise,"noise","l");
    lg->Draw();
}
