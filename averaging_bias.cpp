{
    gStyle->SetOptStat(0);
    TCanvas* c = new TCanvas("c","c",1);
    gPad->SetTickx();
    gPad->SetTicky();
    gPad->SetLogz();
    TFile* f = TFile::Open("data/training_sample_full_8samples.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    Float_t n1, n2, n3, n4, n5, n6, nup, ndown, dead;
    Float_t un1, un2, un3, un4, un5, un6;
    Float_t dn1, dn2, dn3, dn4, dn5, dn6;
    t->SetBranchAddress( "MLn1", &n1 );
    t->SetBranchAddress( "MLn2", &n2 );
    t->SetBranchAddress( "MLn3", &n3 );
    t->SetBranchAddress( "MLn4", &n4 );
    t->SetBranchAddress( "MLn5", &n5 );
    t->SetBranchAddress( "MLn6", &n6 );
    t->SetBranchAddress( "MLnup", &nup );
    t->SetBranchAddress( "MLndown", &ndown );
    t->SetBranchAddress( "MLdead", &dead);
    t->SetBranchAddress( "MLun1", &un1 );
    t->SetBranchAddress( "MLun2", &un2 );
    t->SetBranchAddress( "MLun3", &un3 );
    t->SetBranchAddress( "MLun4", &un4 );
    t->SetBranchAddress( "MLun5", &un5 );
    t->SetBranchAddress( "MLun6", &un6 );
    t->SetBranchAddress( "MLdn1", &dn1 );
    t->SetBranchAddress( "MLdn2", &dn2 );
    t->SetBranchAddress( "MLdn3", &dn3 );
    t->SetBranchAddress( "MLdn4", &dn4 );
    t->SetBranchAddress( "MLdn5", &dn5 );
    t->SetBranchAddress( "MLdn6", &dn6 );

    float xstart = 0;
    TH2F* h_avbias = new TH2F("h_avbias",
        "Averaging method 2.0 bias;Rechit_{true} [GeV];Rechit_{true}-Rechit_{av}",
        100,xstart,40,100,-20,20);
    float avdevquad = 0;
    int n = 0;
    TLine* l = new TLine(xstart,0,0.4,0);

    for (long i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        if(dead > xstart){
            float layer_down = dn1+dn2+dn3+dn4+dn5+dn6+ndown;
            float layer_up = un1+un2+un3+un4+un5+un6+nup;
            float av_layer = layer_down/2+layer_up/2;
            float rechit = av_layer-n1-n2-n3-n4-n5-n6;
            h_avbias->Fill(dead,dead-rechit);
            avdevquad += pow(dead-rechit,2);
            n++;
        }
    }
    avdevquad = sqrt(avdevquad/(float)n);
    h_avbias->GetXaxis()->SetTitleOffset(1.2);
    TLatex ltx;
    h_avbias->Draw("colz");
    l->Draw();
    ltx.SetTextSize(0.035);
    ltx.DrawLatex(xstart+0.003,h_avbias->GetYaxis()->GetXmax()*1.05,
    "HGCAL#scale[0.8]{#font[12]{Internal}}");
    cout << "average quadratic deviation = " << avdevquad << endl;
}
