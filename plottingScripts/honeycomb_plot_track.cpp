{
    TCanvas* c = new TCanvas("c","c",1280,800);
    c->Divide(4,3);
    gStyle->SetOptStat(0);
    TFile* f = TFile::Open("tracking_sample.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float cellid, layer, n1, n2, n3, n4, n5, n6, track, phi, eta, cellx, celly;
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

    TH2Poly* h_honeycomb[27];
    TMarker* mrkr[27];

    float ay = 1.5;
    float ax = sqrt(3)/2;
    float a[] = {0,2*ax,2*ax,4*ax,4*ax,5*ax,6*ax,7*ax,7*ax,9*ax,9*ax,11*ax,11*ax,
        11*ax,13*ax,13*ax,13*ax,15*ax,15*ax,17*ax,17*ax,18*ax,19*ax,20*ax};
    float b[] = {0,0   ,0   ,0   ,0   ,ay  ,0   ,ay  ,ay  ,ay  ,ay  ,ay   ,ay   ,
        ay   ,ay   ,ay   ,ay   ,ay   ,ay   ,ay   ,ay   ,2*ay ,ay   ,2*ay };

    int pad = 0;
    for (unsigned iL(1); iL < 13; ++iL) {
        t->GetEntry(iL);
        h_honeycomb[iL] = new TH2Poly();
        h_honeycomb[iL]->Honeycomb(0,0,1,13,10);
        h_honeycomb[iL]->GetZaxis()->SetTitle("Rechit [GeV]");
        char hname[20];
        sprintf(hname,"Layer %d, hit at %d",(int)layer, (int)cellid);
        h_honeycomb[iL]->SetTitle(hname);
        h_honeycomb[iL]->GetXaxis()->SetLabelOffset(999);
        h_honeycomb[iL]->GetXaxis()->SetLabelSize(0);
        h_honeycomb[iL]->GetXaxis()->SetTickLength(0);
        h_honeycomb[iL]->GetYaxis()->SetLabelOffset(999);
        h_honeycomb[iL]->GetYaxis()->SetLabelSize(0);
        h_honeycomb[iL]->GetYaxis()->SetTickLength(0);
        h_honeycomb[iL]->Fill(2*ax+a[iL-1],5.5+b[iL-1],n1);
        h_honeycomb[iL]->Fill(1*ax+a[iL-1],7+b[iL-1],n3);
        h_honeycomb[iL]->Fill(2*ax+a[iL-1],8.5+b[iL-1],n5);
        h_honeycomb[iL]->Fill(4*ax+a[iL-1],8.5+b[iL-1],n6);
        h_honeycomb[iL]->Fill(5*ax+a[iL-1],7+b[iL-1],n4);
        h_honeycomb[iL]->Fill(4*ax+a[iL-1],5.5+b[iL-1],n2);
        h_honeycomb[iL]->Fill(3*ax+a[iL-1],7+b[iL-1],track);
        //cout << phi << endl;
        double theta = 2*atan(exp(-eta));
        //lines[iL] = new TLine(5*ax-4.4*sin(phi),4-4.4*cos(phi),5*ax+13*sin(phi),4+13*cos(phi));
        c->cd(pad)->SetRightMargin(0.13);
        c->cd(++pad);
        if(pad > 11) pad = 0;
        h_honeycomb[iL]->Draw("colz 0");
        //lines[iL]->SetLineColor(kRed);
        //lines[iL]->Draw();
        char angletxt[20];
        sprintf(angletxt,"#phi = %d^{o}",(int)(round(phi*180/TMath::Pi())));
        TLatex ltx;
        ltx.SetTextAngle(5);
        //if(iL>4) ltx.DrawLatex(0.5,3.8,angletxt);
        //else ltx.DrawLatex(14.5,5.4,angletxt);
        mrkr[iL] = new TMarker(3*ax+a[iL-1]+celly,7+b[iL-1]+cellx,3);
        cout << celly << ", " << cellx << endl;
        mrkr[iL]->Draw();
    }
    c->cd(pad)->SetRightMargin(0.13)
}
