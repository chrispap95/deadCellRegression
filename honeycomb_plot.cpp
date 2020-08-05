{
    TCanvas* c = new TCanvas("c","c",800,800);
    gStyle->SetOptStat(0);
    TFile* f = TFile::Open("out.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float n1, n2, n3, n4, n5, n6, dead;
    t->SetBranchAddress("MLun1",&n1);
    t->SetBranchAddress("MLun2",&n2);
    t->SetBranchAddress("MLun3",&n3);
    t->SetBranchAddress("MLun4",&n4);
    t->SetBranchAddress("MLun5",&n5);
    t->SetBranchAddress("MLun6",&n6);
    t->SetBranchAddress("MLnup",&dead);

    TH2Poly* h_honeycomb = new TH2Poly();
    h_honeycomb->Honeycomb(0,0,1,5,5);
    h_honeycomb->SetTitle("Energy ");
    h_honeycomb->GetXaxis()->SetLabelOffset(999);
    h_honeycomb->GetXaxis()->SetLabelSize(0);
    h_honeycomb->GetXaxis()->SetTickLength(0);
    h_honeycomb->GetYaxis()->SetLabelOffset(999);
    h_honeycomb->GetYaxis()->SetLabelSize(0);
    h_honeycomb->GetYaxis()->SetTickLength(0);

    int n=0;
    for (long i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        if(dead > 1) {
            n++;
            h_honeycomb->Fill(3.5,2.5,n1);
            h_honeycomb->Fill(2.5,4,n2);
            h_honeycomb->Fill(3.5,5.5,n3);
            h_honeycomb->Fill(5,5.5,n4);
            h_honeycomb->Fill(6,4,n5);
            h_honeycomb->Fill(5,2.5,n6);
            h_honeycomb->Fill(4,4,dead);
            break;
        }
    }
    cout << n << endl;
    h_honeycomb->Draw("colz 0");
}
