{
    // Import tree & variables
    TCanvas* c = new TCanvas("c","c",1);
    gStyle->SetOptStat(0);
    gPad->SetTopMargin(0.10);
    gPad->SetLeftMargin(0.1);
    gPad->SetLogy();
    TFile* f = TFile::Open("data/training_sample_full_8samples.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float n1, n2, n3, n4, n5, n6, dead, down, up, phi;
    float un1, un2, un3, un4, un5, un6;
    float dn1, dn2, dn3, dn4, dn5, dn6;
    t->SetBranchAddress("MLphi",&phi);
    t->SetBranchAddress("MLn1",&n1);
    t->SetBranchAddress("MLn2",&n2);
    t->SetBranchAddress("MLn3",&n3);
    t->SetBranchAddress("MLn4",&n4);
    t->SetBranchAddress("MLn5",&n5);
    t->SetBranchAddress("MLn6",&n6);
    t->SetBranchAddress("MLdead",&dead);
    t->SetBranchAddress("MLndown",&down);
    t->SetBranchAddress("MLnup",&up);
    t->SetBranchAddress("MLun1",&un1);
    t->SetBranchAddress("MLun2",&un2);
    t->SetBranchAddress("MLun3",&un3);
    t->SetBranchAddress("MLun4",&un4);
    t->SetBranchAddress("MLun5",&un5);
    t->SetBranchAddress("MLun6",&un6);
    t->SetBranchAddress("MLdn1",&dn1);
    t->SetBranchAddress("MLdn2",&dn2);
    t->SetBranchAddress("MLdn3",&dn3);
    t->SetBranchAddress("MLdn4",&dn4);
    t->SetBranchAddress("MLdn5",&dn5);
    t->SetBranchAddress("MLdn6",&dn6);

    TH1F* h1 = new TH1F("h1","abs(#sum_{layer i} - #sum_{layer i+1});|#Delta sum| [GeV];Entries",100,0,50);
    TH1F* h2 = new TH1F("h2","abs(#sum_{layer i} - #sum_{layer i-1});|#Delta sum| [GeV];Entries",100,0,50);

    for (long i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        h1->Fill(abs(n1+n2+n3+n4+n5+n6+dead-(un1+un2+un3+un4+un5+un6+up)));
        h2->Fill(abs(n1+n2+n3+n4+n5+n6+dead-(dn1+dn2+dn3+dn4+dn5+dn6+down)));
    }
    //h1->Draw();
    h1->GetYaxis()->SetTitleOffset(1.2);
    //h2->Draw();
    h2->GetYaxis()->SetTitleOffset(1.2);
    THStack* hs = new THStack("hs","#Delta(layer sum);#||{#Delta sum} [GeV];Entries");
    hs->Add(h1);
    hs->Add(h2);
    h1->SetLineColor(kRed);
    h2->SetLineColor(kBlue);
    hs->Draw("nostack");
    TLegend* lg = new TLegend(0.5,0.5,0.8,0.8);
    lg->AddEntry("h1","#left| #sum _{layer i} - #sum _{layer i+1} #right|","l");
    lg->AddEntry("h2","#left| #sum _{layer i} - #sum _{layer i-1} #right|","l");
    lg->SetBorderSize(0);
    lg->Draw();
}
