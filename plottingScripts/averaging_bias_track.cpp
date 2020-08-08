{
    gStyle->SetOptStat(0);
    TCanvas* c = new TCanvas("c","c",1);
    gPad->SetTickx();
    gPad->SetTicky();
    gPad->SetLogz();
    TFile* f = TFile::Open("data/tracking_sample.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float cellid, layer, n1, n2, n3, n4, n5, n6, track, phi, eta, cellx, celly;
    float nn1, nn2, nn3, nn4, nn5, nn6, nn7, nn8, nn9, nn10, nn11, nn12;
    t->SetBranchAddress("Trlayer",&layer);
    t->SetBranchAddress("Trcellid",&cellid);
    t->SetBranchAddress("Trphi",&phi);
    t->SetBranchAddress("Treta",&eta);
    t->SetBranchAddress("Trn1",&n1);
    t->SetBranchAddress("Trn2",&n2);
    t->SetBranchAddress("Trn3",&n3);
    t->SetBranchAddress("Trn4",&n4);
    t->SetBranchAddress("Trn5",&n5);
    t->SetBranchAddress("Trn6",&n6);
    t->SetBranchAddress("Trtrack",&track);
    t->SetBranchAddress("cellx",&cellx);
    t->SetBranchAddress("celly",&celly);
    t->SetBranchAddress("Tr2n1",&nn1);
    t->SetBranchAddress("Tr2n2",&nn2);
    t->SetBranchAddress("Tr2n3",&nn3);
    t->SetBranchAddress("Tr2n4",&nn4);
    t->SetBranchAddress("Tr2n5",&nn5);
    t->SetBranchAddress("Tr2n6",&nn6);
    t->SetBranchAddress("Tr2n7",&nn7);
    t->SetBranchAddress("Tr2n8",&nn8);
    t->SetBranchAddress("Tr2n9",&nn9);
    t->SetBranchAddress("Tr2n10",&nn10);
    t->SetBranchAddress("Tr2n11",&nn11);
    t->SetBranchAddress("Tr2n12",&nn12);

    float xstart = 0;
    TH2F* h_avbias = new TH2F("h_avbias",
        "Averaging 2.0 method bias;Rechit_{true} [GeV];Rechit_{true}-Rechit_{av} [GeV]",
        100,xstart,20,100,-20,20);
    float avdevquad = 0;
    int n = 0;
    TLine* l = new TLine(xstart,0,20,0);

    for (long i = 1; i < t->GetEntries(); ++i) {
        t->GetEntry(i-1);
        if(track > xstart){
            float rechit1, rechit2, rechit3, rechit4, rechit5, rechit6, rechit7;
            float rechit8, rechit9, rechit10, rechit11, rechit12, rechit13, rechit14;
            float rechit15, rechit16, rechit17, rechit18, rechit19, rechit20, rechit21;
            rechit1 = n1/2; rechit2 = n2/2; rechit3 = n3/2; rechit4 = n4/2;
            rechit5 = n5/2; rechit6 = n6/2; rechit7 = track/2; rechit8 = nn1/2;
            rechit9 = nn2/2; rechit10 = nn3/2; rechit11 = nn4/2; rechit12 = nn5/2;
            rechit13 = nn6/2; rechit14 = nn7/2; rechit15 = nn8/2; rechit16 = nn9/2;
            rechit17 = nn10/2; rechit18 = nn11/2; rechit19 = nn12/2;
            t->GetEntry(i+1);
            rechit1 += n1/2; rechit2 += n2/2; rechit3 += n3/2; rechit4 += n4/2;
            rechit5 += n5/2; rechit6 += n6/2; rechit7 += track/2; rechit8 += nn1/2;
            rechit9 += nn2/2; rechit10 += nn3/2; rechit11 += nn4/2; rechit12 += nn5/2;
            rechit13 += nn6/2; rechit14 += nn7/2; rechit15 += nn8/2; rechit16 += nn9/2;
            rechit17 += nn10/2; rechit18 += nn11/2; rechit19 += nn12/2;
            t->GetEntry(i);
            h_avbias->Fill(n1,n1-rechit1); h_avbias->Fill(n2,n2-rechit2);
            h_avbias->Fill(n3,n3-rechit3); h_avbias->Fill(n4,n4-rechit4);
            h_avbias->Fill(n5,n5-rechit5); h_avbias->Fill(n6,n6-rechit6);
            h_avbias->Fill(track,track-rechit7);
            h_avbias->Fill(nn1,nn1-rechit8); h_avbias->Fill(nn2,nn2-rechit9);
            h_avbias->Fill(nn3,nn3-rechit10); h_avbias->Fill(nn4,nn4-rechit11);
            h_avbias->Fill(nn5,nn5-rechit12); h_avbias->Fill(nn6,nn6-rechit13);
            h_avbias->Fill(nn7,nn7-rechit14); h_avbias->Fill(nn8,nn8-rechit15);
            h_avbias->Fill(nn9,nn9-rechit16); h_avbias->Fill(nn10,nn10-rechit17);
            h_avbias->Fill(nn11,nn11-rechit18); h_avbias->Fill(nn12,nn12-rechit19);
            avdevquad += pow(n1-rechit1,2); avdevquad += pow(n2-rechit2,2);
            avdevquad += pow(n3-rechit3,2); avdevquad += pow(n4-rechit4,2);
            avdevquad += pow(n5-rechit5,2); avdevquad += pow(n6-rechit6,2);
            avdevquad += pow(track-rechit7,2);
            avdevquad += pow(nn1-rechit8,2); avdevquad += pow(nn2-rechit9,2);
            avdevquad += pow(nn3-rechit10,2); avdevquad += pow(nn4-rechit11,2);
            avdevquad += pow(nn5-rechit12,2); avdevquad += pow(nn6-rechit13,2);
            avdevquad += pow(nn7-rechit14,2); avdevquad += pow(nn8-rechit15,2);
            avdevquad += pow(nn9-rechit16,2); avdevquad += pow(nn10-rechit17,2);
            avdevquad += pow(nn11-rechit18,2); avdevquad += pow(nn12-rechit19,2);
            n++;
        }
    }
    avdevquad = sqrt(avdevquad/(float)n);
    h_avbias->GetXaxis()->SetTitleOffset(1.2);
    TLatex ltx;
    h_avbias->Draw("colz");
    l->Draw();
    ltx.SetTextSize(0.035);
    ltx.DrawLatex(xstart+0.3,h_avbias->GetYaxis()->GetXmax()*1.05,
    "HGCAL#scale[0.8]{#font[12]{Internal}}");
    cout << "average quadratic deviation = " << avdevquad << endl;
}
